//! The field shop (`shop`, `shopCash`, `shopCapture`, `shopScrollMark`; JP FIELD.BIN 0x004ded30 .. 0x004e8480, US 0x00522a80 ..).
//!
//! Opened by the script op `SpecialMenu(0x100, id)` (`CField::SpecialMenu` -> `new shop`, `shop::initialize(id, cbShop, field)`, `start`).
//!
//! # What is real
//!
//! * **Data**: the item tables `shopTbl` -> `shopNN_itemTbl` (`{u8 kind, u8 index}` rows, 0-terminated; kinds 1 item, 2 weapon, 3 armour,
//!   4 accessory, 5 one-off bit, 6 ring item), `shopPointTbl` (rank thresholds) and `shopJRingTbl` (discount ring areas) come from the
//!   disc's own `FIELD.BIN` (JP overlay symbols / US addresses found by pattern); texts from the overlay `shopMess_*` tables (JP) or the `msg`
//!   entries of `SHOP/SHOP.DAT` (US); prices, names and equipment stats from `SSHDAT` / `SSHMES`; textures (title, note label, face frames,
//!   digits, party faces) from `SHOP/SHOP.DAT`.
//! * **Rules** (`Polling` JP 0x004df420, `mCheckSelector`, `mCalcCurrentMax`, `mCalcPoint`, `mSetupBuyResultWin`, `mMakeBuyList`, `mMakeSellList`):
//!   the shop *rank* (E..A) comes from the *shop points* kept in the `MENU` save block (+0x2bc); a purchase earns `(price + 99) / 100` points;
//!   buying may *challenge a discount* (up to `(rank + 1) * 10 %`) on a Judgement Ring whose areas come from `shopJRingTbl` (a failure pays
//!   the set price, or, when the cash does not cover it, costs penalty points and the goods); selling may challenge a *price-up* of up to
//!   `(rank + 1) * 5 %`.  The quantity limit is `100 - owned` (buy) / `owned - equipped` (sell) and, when buying, what the cash buys at the best
//!   discount (`mCalcCurrentMax`).  Rank A (the Gold Card) is exempt from the penalty (US).
//! * The ring is the ported [`JRing`] (`SetMode(5,1,1,3,3)`, three step areas, speed `1.6 - 0.1 * rate`).
//!
//! # Approximated
//!
//! The `primWin` windows are drawn as plain translucent panels at the original coordinates; the equipment comparison under the party faces uses
//! the stat sum of `cmd_equip::derived_with` (`GetRealPAtk ..` need the full `BtlSaveSec` rules).

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_gfx::effects::jring::{self, JRing, JrEvent, JrResult, Rng as _, XorShift};
use sh2_gfx::texture::decode_menu_texture;
use sh2_menu::disc::FileSource;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextureId};
use sh2_menu::save::BtlSave;

use crate::cmd::CmdPage;
use crate::cmd_page::{party_view, CmdScenes, Env, PcView};
use crate::cmd_ui::{blit, cfmt, fill, text_right, text_run, BitmapFont, A, SCREEN_H, SCREEN_W};
use crate::fscreen::{coded_text, dim_field, label, label_c, window, wrap_text, FieldScreen, ScreenFlow, ScreenIo, DT_MS};
use crate::overlay_data::OverlayImage;

// ----------------------------------------------------------------------------------------------------------------
// data
// ----------------------------------------------------------------------------------------------------------------

/// `shopPointTbl`: points needed to leave rank 0..4.
pub type PointTbl = [i32; 5];

/// US overlay (`FIELD.BIN` load 0x0045ea80) addresses found by pattern search (`notes/integration/field_systems.md`).
pub mod addr {
    pub const US_SHOP_TBL: u32 = 0x0060_ea60;
    pub const US_SHOP_COUNT: usize = 25;
    pub const US_POINT_TBL: u32 = 0x0061_5210;
    pub const US_JRING_TBL: u32 = 0x0061_5230;
    pub const JP_POINT_TBL: u32 = 0x0055_a600;
    pub const JP_JRING_TBL: u32 = 0x0055_a620;
}

#[derive(Clone, Debug, Default)]
pub struct ShopTables {
    /// per shop id: `(kind, index)` rows
    pub items: Vec<Vec<(u8, u8)>>,
    pub points: PointTbl,
    /// per rank: the three ring area start angles (+ a fourth word, 10)
    pub jring: [[u16; 4]; 5],
    /// highest reachable rank (JP demo: 3 = B, retail: 4 = A / Gold Card)
    pub max_rank: usize,
}

fn rd_rows(img: &OverlayImage, va: u32) -> Vec<(u8, u8)> {
    let mut out = Vec::new();
    let mut a = va;
    while let Some(b) = img.bytes_at(a, 2) {
        if b[0] == 0 {
            break;
        }
        out.push((b[0], b[1]));
        a += 2;
        if out.len() > 120 {
            break;
        }
    }
    out
}

impl ShopTables {
    pub fn from_overlay(img: &OverlayImage, retail: bool) -> Option<Self> {
        let (tbl, count, pt, jr) = if retail {
            (addr::US_SHOP_TBL, addr::US_SHOP_COUNT, addr::US_POINT_TBL, addr::US_JRING_TBL)
        } else {
            (OverlayImage::sym("shopTbl")?.addr, 3, addr::JP_POINT_TBL, addr::JP_JRING_TBL)
        };
        let mut items = Vec::new();
        for i in 0..count as u32 {
            let p = img.u32_at(tbl + i * 4)?;
            items.push(rd_rows(img, p));
        }
        let mut points = [0i32; 5];
        for (i, p) in points.iter_mut().enumerate() {
            *p = img.u32_at(pt + i as u32 * 4)? as i32;
        }
        let mut jring = [[0u16; 4]; 5];
        for (r, row) in jring.iter_mut().enumerate() {
            let b = img.bytes_at(jr + r as u32 * 8, 8)?;
            for k in 0..4 {
                row[k] = u16::from_le_bytes([b[k * 2], b[k * 2 + 1]]);
            }
        }
        Some(ShopTables { items, points, jring, max_rank: if retail { 4 } else { 3 } })
    }
}

/// Every string the shop shows, in canonical order (the JP overlay tables / the US `SHOP.DAT` message table both fill it).
#[derive(Clone, Debug, Default)]
pub struct ShopText {
    /// per shop id: `(name, reading)`
    pub names: Vec<(String, String)>,
    pub title: String,
    pub main_menu: Vec<String>,
    pub rank: Vec<String>,
    pub title_buy_rank: Vec<String>,
    pub title_sell_rank: Vec<String>,
    pub disc_rank: Vec<String>,
    pub up_rank: Vec<String>,
    pub status: Vec<String>,
    /// total, points / next rank, equipment / owned, scroll hint, "------", discount amount, mark-up amount
    pub info: Vec<String>,
    pub popup: Vec<String>,
    pub query_buy: Vec<String>,
    pub query_buy_note: Vec<String>,
    pub disc_select: Vec<String>,
    pub disc_select_prompt: String,
    pub disc_buy: Vec<String>,
    pub disc_miss: Vec<String>,
    pub disc_penalty: Vec<String>,
    pub buy_point: Vec<String>,
    pub item_kind: Vec<String>,
    pub query_sell: Vec<String>,
    pub query_sell_note: Vec<String>,
    pub up_select: Vec<String>,
    pub up_select_prompt: String,
    pub up_sell: Vec<String>,
    pub up_miss: Vec<String>,
    pub normal_buy: String,
    pub normal_sell: String,
    pub cant_sell: String,
    pub challenge: String,
    pub up_challenge: String,
    pub nothing_to_sell: String,
    pub card: Vec<String>,
    pub equip_mark: String,
    pub intro: String,
}

fn strip_bs(s: &str) -> String {
    s.replace('\\', "")
}

impl ShopText {
    pub fn from_jp(img: &OverlayImage) -> Option<Self> {
        let dec = |b: &[u8]| sh2_menu::sjis::decode(b);
        let tbl = |n: &str| -> Option<Vec<String>> { Some(img.strings(n)?.iter().map(|b| dec(b)).collect()) };
        let one = |va: u32| img.cstr_at(va).map(dec).unwrap_or_default();
        let shop_names = tbl("shopMess_shopName_J")?;
        let names = shop_names.chunks(2).map(|c| (c[0].clone(), c.get(1).cloned().unwrap_or_default())).collect();
        let kinds: Vec<String> = {
            let s = OverlayImage::sym("shopMess_itemKindTbl_J")?;
            (0..s.size / 4).map(|i| img.u32_at(s.addr + i * 4).and_then(|p| img.cstr_at(p)).map(dec).unwrap_or_default()).collect()
        };
        Some(ShopText {
            names,
            title: one(0x0055_9070),
            main_menu: tbl("shopMess_mainMenu_J")?,
            rank: tbl("shopMess_rank_J")?,
            title_buy_rank: tbl("shopMess_titleBuyRank_J")?,
            title_sell_rank: tbl("shopMess_titleSellRank_J")?,
            disc_rank: tbl("shopMess_discRank_J")?,
            up_rank: tbl("shopMess_upRank_J")?,
            status: tbl("shopMess_status_J")?,
            info: tbl("shopMess_shopInfo_J")?,
            popup: tbl("shopMess_mainMenuPopup_J")?,
            query_buy: tbl("shopMess_queryBuy_J")?,
            query_buy_note: tbl("shopMess_queryBuyNote_J")?,
            disc_select: tbl("shopMess_discountSelect_J")?[..5].to_vec(),
            disc_select_prompt: tbl("shopMess_discountSelect_J")?.get(5).cloned().unwrap_or_default(),
            disc_buy: tbl("shopMess_discountBuy_J")?,
            disc_miss: tbl("shopMess_discountMiss_J")?,
            disc_penalty: tbl("shopMess_discountPenalty_J")?,
            buy_point: tbl("shopMess_buyPoint_J")?,
            item_kind: kinds,
            query_sell: tbl("shopMess_querySell_J")?,
            query_sell_note: tbl("shopMess_querySellNote_J")?,
            up_select: tbl("shopMess_priceupSelect_J")?[..5].to_vec(),
            up_select_prompt: tbl("shopMess_priceupSelect_J")?.get(5).cloned().unwrap_or_default(),
            up_sell: tbl("shopMess_priceupSell_J")?,
            up_miss: tbl("shopMess_priceupMiss_J")?,
            normal_buy: one(0x0055_9840),
            normal_sell: one(0x0055_a180),
            cant_sell: one(0x0055_9f80),
            challenge: one(0x0055_9810),
            up_challenge: one(0x0055_a150),
            nothing_to_sell: String::new(),
            card: vec![one(0x0055_9670), one(0x0055_9680)],
            equip_mark: one(0x0055_9080),
            intro: String::new(),
        })
    }

    /// The retail message table (`SHOP.DAT` `msg` entries: 123 texts + the 25 shop names).
    pub fn from_us(msgs: &[Vec<u8>], names: &[Vec<u8>]) -> Option<Self> {
        if msgs.len() < 123 {
            return None;
        }
        let m = |i: usize| strip_bs(&sh2_menu::sjis::decode(&msgs[i]));
        let r = |a: usize, b: usize| (a..b).map(m).collect::<Vec<_>>();
        let names = names.chunks(2).map(|c| (strip_bs(&sh2_menu::sjis::decode(&c[0])), c.get(1).map(|b| sh2_menu::sjis::decode(b)).unwrap_or_default())).collect();
        Some(ShopText {
            names,
            title: m(5),
            main_menu: r(1, 5),
            rank: r(7, 12),
            title_buy_rank: r(19, 24),
            title_sell_rank: r(24, 29),
            disc_rank: r(29, 34),
            up_rank: r(34, 39),
            status: r(39, 43),
            info: vec![m(43), m(48), m(49), m(44), m(45), m(46), m(47)],
            popup: r(14, 19),
            query_buy: r(50, 54),
            query_buy_note: r(54, 57),
            disc_select: r(57, 62),
            disc_select_prompt: m(62),
            disc_buy: r(67, 72),
            disc_miss: r(72, 77),
            disc_penalty: r(77, 82),
            buy_point: r(82, 86),
            item_kind: r(90, 96),
            query_sell: r(96, 100),
            query_sell_note: r(100, 103),
            up_select: r(103, 108),
            up_select_prompt: m(108),
            up_sell: r(112, 117),
            up_miss: r(117, 122),
            normal_buy: m(64),
            normal_sell: m(110),
            cant_sell: m(89),
            challenge: m(63),
            up_challenge: m(109),
            nothing_to_sell: m(122),
            card: vec![m(12), m(13)],
            equip_mark: m(6),
            intro: m(0),
        })
    }
}

/// Tables + texts of the disc being played.
#[derive(Clone, Debug, Default)]
pub struct ShopData {
    pub tables: ShopTables,
    pub text: ShopText,
    pub retail: bool,
}

impl ShopData {
    pub fn load(env: &Env) -> Option<Self> {
        let disc = env.assets.disc.as_ref()?;
        let root = std::env::var_os("SH2_DISC_DIR").map(std::path::PathBuf::from)?;
        let retail = sh2_core::boot::is_retail();
        let img = OverlayImage::new(std::fs::read(root.join("FIELD.BIN")).ok()?).ok()?;
        let tables = ShopTables::from_overlay(&img, retail)?;
        let text = if retail {
            let bundle = disc.read("SHOP/SHOP.DAT")?;
            let n = u32::from_le_bytes(bundle.get(0..4)?.try_into().ok()?) as usize;
            let mut msgs = Vec::new();
            for k in 0..n {
                if bundle.get(8 + k * 8..11 + k * 8)? == b"msg" {
                    msgs.push(crate::worldmap::parse_msg_table(crate::worldmap::bundle_entry(&bundle, k)?));
                }
            }
            ShopText::from_us(msgs.first()?, msgs.get(1)?)?
        } else {
            ShopText::from_jp(&img)?
        };
        Some(ShopData { tables, text, retail })
    }
}

// ----------------------------------------------------------------------------------------------------------------
// rules (pure, tested)
// ----------------------------------------------------------------------------------------------------------------

/// One line of the buy / sell list (`shop::mSetupBuySellWin` row struct, 0x1c bytes).
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Row {
    /// unit price, -1 = cannot be sold
    pub price: i32,
    /// 1 item, 2 weapon, 3 armour, 4 accessory, 5 one-off, 6 ring item
    pub kind: u8,
    pub idx: usize,
    /// quantity chosen
    pub qty: i32,
    /// quantity limit + 1 (`piVar[4]`): `100 - owned` when buying, `owned - equipped + 1` when selling, 1 when it cannot be sold
    pub limit: i32,
    pub equipped: i32,
    pub owned: i32,
}

/// Inventory byte arrays of the demo-shaped save (`BtlSave.data`), relative to the bag base.
pub mod inv {
    pub const ITEMS: usize = 0x944;
    pub const WEAPONS: usize = 0x9c4;
    pub const ARMOR: usize = 0xa24;
    pub const ACCESSORY: usize = 0xa54;
    pub const RING_ITEM: usize = 0xab8;
    pub const BITS: usize = 0xaa4;
    pub const SEEN_BITS: usize = 0x984;
    pub const N_ITEMS: usize = 0x40;
    pub const N_WEAPONS: usize = 0x60;
    pub const N_ARMOR: usize = 0x30;
    pub const N_ACCESSORY: usize = 0x50;
    pub const N_RING: usize = 0x50;
}

fn kind_base(kind: u8) -> Option<(usize, usize)> {
    Some(match kind {
        1 => (inv::ITEMS, inv::N_ITEMS),
        2 => (inv::WEAPONS, inv::N_WEAPONS),
        3 => (inv::ARMOR, inv::N_ARMOR),
        4 => (inv::ACCESSORY, inv::N_ACCESSORY),
        6 => (inv::RING_ITEM, inv::N_RING),
        _ => return None,
    })
}

pub fn bag_count(btl: &BtlSave, kind: u8, idx: usize) -> i32 {
    let Some((base, n)) = kind_base(kind) else { return 0 };
    if idx >= n {
        return 0;
    }
    btl.data.get(base + btl.bag() as usize * BtlSave::BAG_STRIDE + idx).copied().unwrap_or(0) as i32
}

pub fn bag_add(btl: &mut BtlSave, kind: u8, idx: usize, delta: i32) {
    let bag = btl.bag() as usize * BtlSave::BAG_STRIDE;
    if let Some((base, n)) = kind_base(kind) {
        if idx < n {
            if let Some(b) = btl.data.get_mut(base + bag + idx) {
                *b = (*b as i32 + delta).clamp(0, 99) as u8;
            }
        }
    } else if kind == 5 || kind == 10 {
        let o = (if kind == 5 { inv::BITS } else { inv::SEEN_BITS }) + bag + (idx >> 3);
        if let Some(b) = btl.data.get_mut(o) {
            *b |= 1 << (idx & 7);
        }
    }
}

fn bit_set(btl: &BtlSave, kind: u8, idx: usize) -> bool {
    let bag = btl.bag() as usize * BtlSave::BAG_STRIDE;
    let o = (if kind == 5 { inv::BITS } else { inv::SEEN_BITS }) + bag + (idx >> 3);
    btl.data.get(o).map(|b| b & (1 << (idx & 7)) != 0).unwrap_or(false)
}

pub fn bit_set_pub(btl: &BtlSave, kind: u8, idx: usize) -> bool {
    bit_set(btl, kind, idx)
}

/// Prices of one record: `(buy, sell)`; `-1` = not for sale.  Offsets of the `GetRegDat` records (demo shaped): items +0x24 / +0x28,
/// weapons +0xc / +0xc, armour +0xc / +0x10, accessories +0x20 / +0x24.
pub fn prices(env: &Env, kind: u8, idx: usize) -> (i32, i32) {
    use sh2_battle::data::{SEC_ACCESSORY, SEC_ARMOR, SEC_ITEM, SEC_JRING, SEC_WEAPON};
    let Some(db) = env.db else { return (-1, -1) };
    let rd = |sec: usize, stride: usize, off: usize| -> Option<i32> { db.dat.record(sec, idx, stride).and_then(|r| r.get(off..off + 4)).map(|b| i32::from_le_bytes(b.try_into().unwrap())) };
    match kind {
        1 => (rd(SEC_ITEM, 0x30, 0x24).unwrap_or(-1), rd(SEC_ITEM, 0x30, 0x28).unwrap_or(-1)),
        2 => {
            let p = rd(SEC_WEAPON, 0x34, 0xc).unwrap_or(-1);
            (p, p)
        }
        3 => (rd(SEC_ARMOR, 0x18, 0xc).unwrap_or(-1), rd(SEC_ARMOR, 0x18, 0x10).unwrap_or(-1)),
        4 => (rd(SEC_ACCESSORY, 0x2c, 0x20).unwrap_or(-1), rd(SEC_ACCESSORY, 0x2c, 0x24).unwrap_or(-1)),
        // `MC_P` (data table 20): buy +0x10, sell +0x14
        5 => (rd(20, 0x1c, 0x10).unwrap_or(-1), rd(20, 0x1c, 0x14).unwrap_or(-1)),
        // `JRCI` judgement ring items: buy +0x14, sell +0x18
        6 => (rd(SEC_JRING, 0x20, 0x14).unwrap_or(-1), rd(SEC_JRING, 0x20, 0x18).unwrap_or(-1)),
        _ => (-1, -1),
    }
}

/// Name of a goods record: `GetRegDat(name kind)` = the `SSHMES` record the data record's u16 at +2 points to.
/// (items 12, weapons 9, armour 10, accessories 11, `MC_P` 16, ring items 20, clothes 14).
pub fn name_of(env: &Env, kind: u8, idx: usize) -> String {
    use sh2_battle::data::{SEC_JRING};
    let (data_sec, stride, mes) = match kind {
        1 => (16usize, 0x30usize, 12usize),
        2 => (13, 0x34, 9),
        3 => (14, 0x18, 10),
        4 => (15, 0x2c, 11),
        5 => (20, 0x1c, 16),
        6 => (SEC_JRING, 0x20, 20),
        _ => return String::new(),
    };
    let via = env.db.and_then(|d| d.dat.record(data_sec, idx, stride)).and_then(|r| r.get(2..4)).map(|b| u16::from_le_bytes([b[0], b[1]]) as usize).filter(|&v| v != 0xffff).unwrap_or(idx);
    // the menu name database decodes full Shift-JIS (JP demo); the retail names are ASCII and come from the battle database view
    let n = env.name(mes, via);
    if n.is_empty() {
        env.db.map(|d| d.name(mes, via)).unwrap_or_default()
    } else {
        n
    }
}

/// `shop::mCalcPoint(up)`: move the rank one step; true when it moved.
pub fn calc_point(rank: &mut usize, points: i32, tbl: &PointTbl, max_rank: usize, up: bool) -> bool {
    if *rank >= max_rank {
        return false;
    }
    if up {
        if tbl[*rank] <= points {
            *rank += 1;
            return true;
        }
    } else if *rank != 0 && points < tbl[*rank - 1] {
        *rank -= 1;
        return true;
    }
    false
}

/// Rank of a point total (`mShopInit`: `do mCalcPoint(true) while (moved)`).
pub fn rank_of(points: i32, tbl: &PointTbl, max_rank: usize) -> usize {
    let mut r = 0;
    while calc_point(&mut r, points, tbl, max_rank, true) {}
    r
}

/// Discount in percent at `rate` (0..=4 -> 10..50 %).
pub fn disc_amount(total: i32, rate: usize) -> i32 {
    total * (rate as i32 + 1) / 10
}
/// Mark-up of a sale at `rate` (0..=4 -> 5..25 %).
pub fn up_amount(total: i32, rate: usize) -> i32 {
    total * (rate as i32 + 1) / 20
}

/// Largest quantity (+1) of `row` the cash allows when buying, counting the best discount the rank allows (`mCalcCurrentMax`).
pub fn current_max_buy(row: &Row, total: i32, cash: i32, rank: usize) -> i32 {
    let unit = row.price - row.price * (rank as i32 + 1) / 10;
    if unit <= 0 {
        return row.limit;
    }
    let m = row.qty + (cash - (total - total * (rank as i32 + 1) / 10)) / unit + 1;
    m.min(row.limit)
}

/// Outcome of a finished transaction.
#[derive(Clone, Debug, PartialEq, Eq, Default)]
pub struct Outcome {
    /// goods change hands (false: the failed challenge could not be paid, `shopMess_discountPenalty_J`)
    pub done: bool,
    /// money paid (buy) / received (sell) at the final price
    pub amount: i32,
    /// points gained (+) or lost (-)
    pub points: i32,
    /// which message of the result tables to show: `0` plain, `1` challenge won, `2` challenge lost (set price), `3` lost and not bought
    pub msg: u8,
}

/// `mSetupBuyResultWin` buying branch: `total` = sum of the chosen rows at the set price, `rate` = chosen discount (0..4) when a challenge was
/// made, `won` = ring result of the challenge.  Returns what happens to cash / points.
pub fn buy_outcome(total: i32, cash: i32, rank: usize, challenge: Option<(usize, bool)>, gold_card_exempt: bool, retail: bool) -> Outcome {
    let mut pay = total;
    let mut msg = 0;
    let mut done = true;
    if let Some((rate, won)) = challenge {
        if won {
            pay = total - disc_amount(total, rate);
            msg = 1;
        } else if cash < total {
            done = false;
            msg = 3;
        } else {
            msg = 2;
        }
    }
    if !done {
        // `iVar8 = ((cash + 9) - (total - total * (rate + 1) / 10)) / 10, at least 1` (retail); the exempt rank loses nothing
        let rate = challenge.map(|c| c.0).unwrap_or(0);
        let disc_total = total - disc_amount(total, rate);
        let pen = if gold_card_exempt && rank == 4 {
            0
        } else if retail {
            (((cash + 9) - disc_total) / 10).max(1)
        } else {
            (((disc_total - cash) + 9) / 10).abs().max(1)
        };
        return Outcome { done: false, amount: 0, points: -pen, msg };
    }
    Outcome { done: true, amount: pay, points: (pay + 99) / 100, msg }
}

/// `mSetupBuyResultWin` selling branch.
pub fn sell_outcome(total: i32, challenge: Option<(usize, bool)>) -> Outcome {
    let (mut amount, mut msg) = (total, 0);
    if let Some((rate, won)) = challenge {
        if won {
            amount = total + up_amount(total, rate);
            msg = 1;
        } else {
            msg = 2;
        }
    }
    Outcome { done: true, amount, points: 0, msg }
}

/// Ring areas of a discount / price-up challenge: `(start, width)` x 3 (`Polling` state 0x11: `AddStepArea(tbl[i] - d, d * 2.5)` with
/// `d = 30 - 5 * (rate + 1)`; the table row is `rand() % 5`).
pub fn challenge_areas(tbl: &[[u16; 4]; 5], row: usize, rate: usize) -> [(i16, i16); 3] {
    let d = 30 - 5 * (rate as i32 + 1);
    let r = &tbl[row.min(4)];
    let mk = |s: u16| ((s as i32 - d) as i16, (d as f32 * 2.5) as i16);
    [mk(r[0]), mk(r[1]), mk(r[2])]
}

/// Ring revolution time of a challenge (`SetRotSpeed(1.6 - rate * 0.1)`).
pub fn challenge_period(rate: usize) -> f32 {
    1.6 - rate as f32 * 0.1
}

// ----------------------------------------------------------------------------------------------------------------
// textures
// ----------------------------------------------------------------------------------------------------------------

#[derive(Default, Clone)]
pub struct ShopTex {
    pub title: Option<(TextureId, (u32, u32))>,
    pub note: Option<(TextureId, (u32, u32))>,
    pub frame: Option<(TextureId, (u32, u32))>,
    pub digits: Option<TextureId>,
    pub cash_label: Option<(TextureId, (u32, u32))>,
    /// party faces by `PcView::face` (entries 6..)
    pub faces: Vec<Option<TextureId>>,
}

pub fn load_tex(env: &mut Env) -> ShopTex {
    let mut t = ShopTex::default();
    let Some(bytes) = env.assets.disc.as_ref().and_then(|d| d.read("SHOP/SHOP.DAT")) else { return t };
    let n = u32::from_le_bytes(bytes.get(0..4).and_then(|b| b.try_into().ok()).unwrap_or([0; 4])) as usize;
    let load = |env: &mut Env, k: usize| -> Option<(TextureId, (u32, u32))> {
        if k >= n || bytes.get(8 + k * 8..11 + k * 8)? == b"fnt" || bytes.get(8 + k * 8..11 + k * 8)? == b"msg" {
            return None;
        }
        let off = u32::from_le_bytes(bytes.get(12 + k * 8..16 + k * 8)?.try_into().ok()?) as usize;
        let img = decode_menu_texture(&bytes, off).ok()?;
        let sz = (img.width, img.height);
        env.reg.add(&img).map(|id| (id, sz))
    };
    t.title = load(env, 1);
    t.note = load(env, 2);
    t.frame = load(env, 3);
    t.digits = load(env, 4).map(|x| x.0);
    t.cash_label = load(env, 5);
    for k in 6..n.min(26) {
        t.faces.push(load(env, k).map(|x| x.0));
    }
    t
}

// ----------------------------------------------------------------------------------------------------------------
// the screen
// ----------------------------------------------------------------------------------------------------------------

#[derive(Clone, Debug, PartialEq)]
enum Phase {
    /// `Polling` state 1..2: the title, cash and main menu fade in
    FadeIn,
    Main,
    List,
    Query,
    Rate,
    /// "The ... Challenge!" shown while the ring is made ready
    RingIntro,
    Ring,
    RingEnd,
    Result,
    Warning,
    /// fade out and leave (state 0x1c)
    Leaving,
}

/// A shop's Judgement Ring (`JRing` with three step areas).
struct ShopRing {
    ring: JRing,
    rng: XorShift,
    result: Option<JrResult>,
    time: f32,
}

impl ShopRing {
    fn start(rate: usize, row: usize, tbl: &[[u16; 4]; 5], seed: u64) -> Self {
        let mut rng = XorShift(seed | 1);
        let mut r = JRing::new(0);
        r.data_loaded = true;
        r.set_mode(5, jring::ring_type::SINGLE, 1, 3, 3);
        for (s, w) in challenge_areas(tbl, row, rate) {
            r.add_step_area(s.rem_euclid(360), w, None, 0);
        }
        r.laps_allowed = 1;
        r.set_callback_mask(0x3ff);
        r.update(1.0 / 60.0, 0, &mut rng);
        r.events.clear();
        r.ring_active(&mut rng);
        r.period = challenge_period(rate);
        r.events.clear();
        ShopRing { ring: r, rng, result: None, time: 0.0 }
    }
    /// true when the ring is over
    fn tick(&mut self, face: u16) -> bool {
        self.time += 1.0 / 60.0;
        self.ring.update(1.0 / 60.0, face & jring::PAD_FACE_MASK, &mut self.rng);
        for e in self.ring.events.drain(..) {
            if let JrEvent::Callback { code: 0x40, result: Some(r) } = e {
                self.result = Some(r);
            }
        }
        (self.result.is_some() && self.ring.state == jring::state::SLEEP) || self.time > 30.0
    }
    /// ring result grade >= 2 (`(flags >> 1 & 3) >= 2`)
    fn won(&self) -> bool {
        self.result.as_ref().map(|r| (r.flags >> 1) & 3 >= 2).unwrap_or(false)
    }
}

pub struct ShopScreen {
    id: i32,
    d: Arc<ShopData>,
    tex: ShopTex,
    sc: Arc<CmdScenes>,
    pcs: Vec<PcView>,
    digits: BitmapFont,
    name: (String, String),
    // state of the original object
    phase: Phase,
    t: f32,
    fade: f32,
    /// main menu cursor (`+0x84` in the menu)
    main_sel: usize,
    buy: bool,
    rank: usize,
    points: i32,
    to_next: i32,
    cash: i32,
    rows: Vec<Row>,
    sel: usize,
    top: usize,
    total: i32,
    cur_max: i32,
    query_sel: usize,
    rate_sel: usize,
    challenge: Option<usize>,
    ring: Option<ShopRing>,
    won: Option<bool>,
    result_text: String,
    result_t: f32,
    warn_text: String,
    anim: f32,
    // cached comparison of the selected goods (per party member: 4 stats, +/-)
    cmp: Vec<[(i32, i8); 4]>,
    can_equip: Vec<bool>,
    equipped_here: Vec<bool>,
    desc: String,
    names: std::collections::HashMap<(u8, usize), String>,
    pub stats_total: (u32, u32),
    seed: u64,
}

const VISIBLE_ROWS: usize = 5;

impl ShopScreen {
    pub fn new(env: &mut Env, id: i32) -> Option<Self> {
        let d = Arc::new(ShopData::load(env)?);
        let sc = env.scenes()?;
        let tex = load_tex(env);
        let pcs: Vec<PcView> = party_view(env.session).into_iter().take(4).collect();
        log::info!("shop {id}: party faces {:?}", pcs.iter().map(|p| (p.id, p.face)).collect::<Vec<_>>());
        let points = shop_points(env);
        let rank = rank_of(points, &d.tables.points, d.tables.max_rank);
        let name = d.text.names.get(id.max(0) as usize).cloned().unwrap_or_default();
        let cash = env.session.cash() as i32;
        let mut s = ShopScreen {
            id,
            digits: BitmapFont::italic(tex.digits),
            d,
            tex,
            sc,
            pcs,
            name,
            phase: Phase::FadeIn,
            t: 0.0,
            fade: 0.0,
            main_sel: 0,
            buy: true,
            rank,
            points,
            to_next: 0,
            cash,
            rows: vec![],
            sel: 0,
            top: 0,
            total: 0,
            cur_max: 1,
            query_sel: 0,
            rate_sel: 0,
            challenge: None,
            ring: None,
            won: None,
            result_text: String::new(),
            result_t: 0.0,
            warn_text: String::new(),
            anim: 0.0,
            cmp: vec![],
            can_equip: vec![],
            equipped_here: vec![],
            desc: String::new(),
            names: Default::default(),
            stats_total: (0, 0),
            seed: 0x5eed ^ env.tick,
        };
        s.calc_to_next();
        env.sound(MenuSe::Other(5));
        Some(s)
    }

    fn calc_to_next(&mut self) {
        self.to_next = self.d.tables.points[self.rank.min(4)] - self.points;
    }

    /// `mMakeBuyList`
    fn make_buy_list(&mut self, env: &Env) {
        self.rows.clear();
        let btl = &env.session.save.btl;
        let rows = self.d.tables.items.get(self.id.max(0) as usize).cloned().unwrap_or_default();
        for (kind, idx) in rows {
            if kind == 5 && bit_set(btl, 5, idx as usize) {
                continue;
            }
            let (price, _) = prices(env, kind, idx as usize);
            let owned = bag_count(btl, kind, idx as usize);
            self.names.insert((kind, idx as usize), name_of(env, kind, idx as usize));
            self.rows.push(Row { price, kind, idx: idx as usize, qty: 0, limit: 100 - owned, equipped: 0, owned });
        }
    }

    /// Number of party members that wear `(kind, idx)`.
    fn equipped_count(&self, env: &Env, kind: u8, idx: usize) -> i32 {
        let mut n = 0;
        for p in &self.pcs {
            let Some(r) = env.session.save.btl.pc(p.id as usize) else { continue };
            match kind {
                2 if r.weapon as i32 == idx as i32 => n += 1,
                3 if r.armor as i32 == idx as i32 => n += 1,
                4 => n += r.accessories.iter().filter(|&&a| a as i32 == idx as i32).count() as i32,
                _ => {}
            }
        }
        n
    }

    /// `mMakeSellList`
    fn make_sell_list(&mut self, env: &Env) {
        self.rows.clear();
        let btl = &env.session.save.btl;
        for (kind, n) in [(1u8, inv::N_ITEMS), (2, inv::N_WEAPONS), (3, inv::N_ARMOR), (4, inv::N_ACCESSORY), (6, inv::N_RING)] {
            for idx in 0..n {
                let owned = bag_count(btl, kind, idx);
                if owned == 0 {
                    continue;
                }
                let equipped = self.equipped_count(env, kind, idx);
                if equipped >= owned && matches!(kind, 2..=4) {
                    continue;
                }
                let (_, price) = prices(env, kind, idx);
                let limit = if price == -1 { 1 } else { owned + 1 - equipped };
                self.names.insert((kind, idx), name_of(env, kind, idx));
                self.rows.push(Row { price, kind, idx, qty: 0, limit, equipped, owned });
            }
        }
    }

    fn rate_count(&self) -> usize {
        self.rank + 1
    }

    fn recalc_max(&mut self) {
        let Some(row) = self.rows.get(self.sel) else { return };
        self.cur_max = if self.buy { current_max_buy(row, self.total, self.cash, self.rank) } else { row.limit };
    }

    fn refresh_selection(&mut self, env: &Env) {
        self.recalc_max();
        let Some(row) = self.rows.get(self.sel).cloned() else { return };
        // description (menu data tables)
        let ty = match row.kind {
            1 => 11,
            2 => 8,
            3 => 9,
            4 => 10,
            _ => 0,
        };
        self.desc = if ty != 0 { crate::cmd_ui::sj(self.sc.mdt.mdt_str(ty, row.idx, 1)).replace('$', "\n") } else { String::new() };
        self.compare(env, &row);
    }

    /// The comparison under the party faces (`mUpdateNoteWin`).
    fn compare(&mut self, env: &Env, row: &Row) {
        use crate::cmd_equip::{derived_with, Loadout};
        self.cmp.clear();
        self.can_equip.clear();
        self.equipped_here.clear();
        for p in &self.pcs {
            let Some(r) = env.session.save.btl.pc(p.id as usize) else {
                self.cmp.push([(0, 0); 4]);
                self.can_equip.push(false);
                self.equipped_here.push(false);
                continue;
            };
            let cur = Loadout { weapon: r.weapon, armor: r.armor, acc: r.accessories };
            let base = derived_with(env, p.id, cur).unwrap_or([0; 4]);
            let mut best = base;
            let mut can = false;
            let bit = 1u16 << (p.id as u32 & 15);
            match row.kind {
                2 => {
                    if let Some(w) = env.db.and_then(|d| d.weapon(row.idx)) {
                        can = w.equip_mask & bit != 0;
                        if can {
                            best = derived_with(env, p.id, Loadout { weapon: row.idx as i8, ..cur }).unwrap_or(base);
                        }
                    }
                }
                3 => {
                    if let Some(a) = env.db.and_then(|d| d.armor(row.idx)) {
                        can = a.equip_mask & bit != 0;
                        if can {
                            best = derived_with(env, p.id, Loadout { armor: row.idx as i8, ..cur }).unwrap_or(base);
                        }
                    }
                }
                4 => {
                    if let Some(a) = env.db.and_then(|d| d.accessory(row.idx)) {
                        can = a.equip_mask & bit != 0;
                        if can {
                            // the slot that gives the best total (`mUpdateNoteWin` tries all three)
                            let mut top = base;
                            let mut top_sum = i32::MIN;
                            for slot in 0..3 {
                                let mut acc = cur.acc;
                                acc[slot] = row.idx as i8;
                                let v = derived_with(env, p.id, Loadout { acc, ..cur }).unwrap_or(base);
                                let sum: i32 = v.iter().sum();
                                if sum > top_sum {
                                    top_sum = sum;
                                    top = v;
                                }
                            }
                            best = top;
                        }
                    }
                }
                _ => {}
            }
            // derived order is P-Atk, S-Atk, P-Def, S-Def; the shop shows P-Atc, P-Def, S-Atc, S-Def
            let reorder = |v: [i32; 4]| [v[0], v[2], v[1], v[3]];
            let (b, n) = (reorder(base), reorder(best));
            let mut cells = [(0, 0i8); 4];
            for k in 0..4 {
                cells[k] = (n[k], if !can || matches!(row.kind, 1 | 5 | 6) { 0 } else { (n[k] - b[k]).signum() as i8 });
                if !can || matches!(row.kind, 1 | 5 | 6) {
                    cells[k].0 = b[k];
                }
            }
            self.cmp.push(cells);
            self.can_equip.push(can && matches!(row.kind, 2..=4));
            let worn = match row.kind {
                2 => r.weapon as i32 == row.idx as i32,
                3 => r.armor as i32 == row.idx as i32,
                4 => r.accessories.iter().any(|&a| a as i32 == row.idx as i32),
                _ => false,
            };
            self.equipped_here.push(worn);
        }
    }

    fn enter_list(&mut self, env: &Env, buy: bool) -> bool {
        self.buy = buy;
        if buy {
            self.make_buy_list(env);
        } else {
            self.make_sell_list(env);
        }
        if self.rows.is_empty() {
            return false;
        }
        self.sel = 0;
        self.top = 0;
        self.total = 0;
        self.refresh_selection(env);
        true
    }

    /// Selling price of the whole selection with the set price rules, for the "total" box (`mUpdateNoteWin`).
    fn shown_amount(&self) -> i32 {
        if self.buy {
            self.total - disc_amount(self.total, self.rank)
        } else {
            self.total + up_amount(self.total, self.rank)
        }
    }

    fn start_result(&mut self, env: &mut Env) {
        let challenge = self.challenge.map(|r| (r, self.won.unwrap_or(false)));
        let t = &self.d.text;
        let kind_msg: String;
        let mut tail = String::new();
        if self.buy {
            let o = buy_outcome(self.total, self.cash, self.rank, challenge, self.d.retail, self.d.retail);
            kind_msg = match (o.msg, self.challenge) {
                (0, _) => t.normal_buy.clone(),
                (1, Some(r)) => t.disc_buy.get(r).cloned().unwrap_or_default(),
                (2, Some(r)) => t.disc_miss.get(r).cloned().unwrap_or_default(),
                (_, Some(r)) => t.disc_penalty.get(r).cloned().unwrap_or_default(),
                _ => t.normal_buy.clone(),
            };
            let old_rank = self.rank;
            if o.done {
                self.cash = (self.cash - o.amount).max(0);
                self.points = (self.points + o.points).min(999_999);
                for r in &self.rows {
                    if r.qty > 0 {
                        bag_add(&mut env.session.save.btl, r.kind, r.idx, r.qty);
                        if r.kind == 5 {
                            // one-off goods are listed once (`mMakeBuyList` skips set bits)
                            bag_add(&mut env.session.save.btl, 10, r.idx, 1);
                        }
                    }
                }
                let mut moved = false;
                while calc_point(&mut self.rank, self.points, &self.d.tables.points, self.d.tables.max_rank, true) {
                    moved = true;
                }
                tail = format!("{}{:7}", t.buy_point.first().cloned().unwrap_or_default(), o.points);
                if moved {
                    tail.push_str(&format!("\n{}{}", t.buy_point.get(1).cloned().unwrap_or_default(), t.rank.get(self.rank).cloned().unwrap_or_default()));
                    if self.rank == 4 && self.d.retail {
                        tail.push_str(&format!("\n{}", t.card.get(1).cloned().unwrap_or_default()));
                    }
                }
            } else {
                self.points = (self.points + o.points).max(0);
                let mut moved = false;
                while calc_point(&mut self.rank, self.points, &self.d.tables.points, self.d.tables.max_rank, false) {
                    moved = true;
                }
                tail = format!("{}{:7}", t.buy_point.get(2).cloned().unwrap_or_default(), -o.points);
                if moved {
                    tail.push_str(&format!("\n{}{}", t.buy_point.get(3).cloned().unwrap_or_default(), t.rank.get(self.rank).cloned().unwrap_or_default()));
                }
            }
            let _ = old_rank;
        } else {
            let o = sell_outcome(self.total, challenge);
            kind_msg = match (o.msg, self.challenge) {
                (0, _) => t.normal_sell.clone(),
                (1, Some(r)) => t.up_sell.get(r).cloned().unwrap_or_default(),
                (_, Some(r)) => t.up_miss.get(r).cloned().unwrap_or_default(),
                _ => t.normal_sell.clone(),
            };
            self.cash = (self.cash + o.amount).min(99_999_999);
            for r in &self.rows {
                if r.qty > 0 {
                    bag_add(&mut env.session.save.btl, r.kind, r.idx, -r.qty);
                }
            }
        }
        self.result_text = if tail.is_empty() { kind_msg } else { format!("{kind_msg}\n\n{tail}") };
        self.result_t = 0.0;
        // write the state back like `~shop` does
        env.session.add_cash(self.cash - env.session.cash() as i32);
        set_shop_points(env, self.points);
        self.calc_to_next();
        env.sound(MenuSe::Other(0));
        self.phase = Phase::Result;
    }

}

/// `MENU + 0x2bc`: the shop points (`mShopInit` reads, `~shop` writes back).
pub const OFF_SHOP_POINTS: usize = 0x2bc;

pub fn shop_points(env: &Env) -> i32 {
    let d = &env.session.save.menu.data;
    d.get(OFF_SHOP_POINTS..OFF_SHOP_POINTS + 4).map(|b| i32::from_le_bytes(b.try_into().unwrap())).unwrap_or(0).clamp(0, 999_999)
}

pub fn set_shop_points(env: &mut Env, v: i32) {
    if let Some(b) = env.session.save.menu.data.get_mut(OFF_SHOP_POINTS..OFF_SHOP_POINTS + 4) {
        b.copy_from_slice(&v.to_le_bytes());
    }
}

impl FieldScreen for ShopScreen {
    fn name(&self) -> &'static str {
        "shop"
    }

    fn menu_closed(&mut self) {
        // the equipment may have changed: refresh the party and comparison
        self.phase = Phase::Main;
    }

    fn state(&self) -> String {
        format!("{:?}", self.phase).to_lowercase()
    }

    fn tick(&mut self, env: &mut Env, keys: u16, press: u16, io: &mut ScreenIo) -> ScreenFlow {
        self.anim += DT_MS;
        self.t += DT_MS;
        match self.phase.clone() {
            Phase::FadeIn => {
                self.fade = (self.t / 240.0).min(1.0);
                if self.fade >= 1.0 {
                    self.phase = Phase::Main;
                    self.t = 0.0;
                }
            }
            Phase::Main => {
                self.fade = 1.0;
                let n = 4;
                if keys & padbit::UP != 0 {
                    self.main_sel = (self.main_sel + n - 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::DOWN != 0 {
                    self.main_sel = (self.main_sel + 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if press & padbit::CIRCLE != 0 {
                    env.sound(MenuSe::Decide);
                    match self.main_sel {
                        0 | 1 => {
                            let buy = self.main_sel == 0;
                            if !self.enter_list(env, buy) {
                                // nothing to sell: the popup of the retail shop, a buzzer in the demo
                                env.sound(MenuSe::Buzzer);
                                self.warn_text = if buy { String::new() } else { self.d.text.nothing_to_sell.clone() };
                            } else {
                                self.phase = Phase::List;
                            }
                        }
                        2 => {
                            io.open_menu = Some(CmdPage::Equipment);
                        }
                        _ => {
                            self.phase = Phase::Leaving;
                            self.t = 0.0;
                        }
                    }
                } else if press & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.phase = Phase::Leaving;
                    self.t = 0.0;
                }
            }
            Phase::List => {
                let n = self.rows.len();
                let mut moved = false;
                if keys & padbit::UP != 0 && self.sel > 0 {
                    self.sel -= 1;
                    moved = true;
                } else if keys & padbit::DOWN != 0 && self.sel + 1 < n {
                    self.sel += 1;
                    moved = true;
                } else if keys & (padbit::L1 | padbit::L2) != 0 {
                    self.sel = self.sel.saturating_sub(VISIBLE_ROWS - 1);
                    moved = true;
                } else if keys & (padbit::R1 | padbit::R2) != 0 {
                    self.sel = (self.sel + VISIBLE_ROWS - 1).min(n - 1);
                    moved = true;
                }
                if moved {
                    env.sound(MenuSe::CursorMove);
                    if self.sel < self.top {
                        self.top = self.sel;
                    }
                    if self.sel >= self.top + VISIBLE_ROWS {
                        self.top = self.sel + 1 - VISIBLE_ROWS;
                    }
                    self.refresh_selection(env);
                }
                // quantity: right = more, left = fewer (wraps through zero like `mCheckSelector`)
                if keys & padbit::RIGHT != 0 {
                    let r = &mut self.rows[self.sel];
                    let unit = r.price.max(0);
                    if r.qty < self.cur_max - 1 {
                        r.qty += 1;
                        self.total += unit;
                        env.sound(MenuSe::CursorMove);
                    } else if r.qty > 0 {
                        self.total -= unit * r.qty;
                        r.qty = 0;
                        env.sound(MenuSe::CursorMove);
                    } else {
                        env.sound(MenuSe::Buzzer);
                    }
                    self.recalc_max();
                } else if keys & padbit::LEFT != 0 {
                    let r = &mut self.rows[self.sel];
                    let unit = r.price.max(0);
                    if r.qty > 0 {
                        r.qty -= 1;
                        self.total -= unit;
                        env.sound(MenuSe::CursorMove);
                    } else if self.cur_max > 1 {
                        r.qty = self.cur_max - 1;
                        self.total += unit * r.qty;
                        env.sound(MenuSe::CursorMove);
                    }
                    self.recalc_max();
                } else if press & padbit::CIRCLE != 0 {
                    let row = self.rows[self.sel].clone();
                    if row.price == -1 {
                        env.sound(MenuSe::Buzzer);
                        let kind = self.d.text.item_kind.get(match row.kind {
                            1 => 0,
                            2 => 1,
                            3 => 2,
                            4 => 3,
                            _ => 5,
                        });
                        self.warn_text = self.d.text.cant_sell.replace("%s", kind.map(|s| s.as_str()).unwrap_or(""));
                        self.phase = Phase::Warning;
                        self.t = 0.0;
                    } else if self.total == 0 {
                        env.sound(MenuSe::Buzzer);
                    } else {
                        env.sound(MenuSe::Decide);
                        self.query_sel = 0;
                        self.phase = Phase::Query;
                        self.t = 0.0;
                    }
                } else if press & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.phase = Phase::Main;
                    self.total = 0;
                    self.rows.iter_mut().for_each(|r| r.qty = 0);
                }
            }
            Phase::Warning => {
                if press & (padbit::CIRCLE | padbit::CROSS) != 0 && self.t > 200.0 {
                    self.phase = Phase::List;
                }
            }
            Phase::Query => {
                if keys & padbit::UP != 0 || keys & padbit::DOWN != 0 {
                    self.query_sel = if keys & padbit::UP != 0 { (self.query_sel + 2) % 3 } else { (self.query_sel + 1) % 3 };
                    env.sound(MenuSe::CursorMove);
                } else if press & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.phase = Phase::List;
                } else if press & padbit::CIRCLE != 0 {
                    env.sound(MenuSe::Decide);
                    match self.query_sel {
                        0 => {
                            self.rate_sel = 0;
                            self.phase = Phase::Rate;
                        }
                        1 => {
                            self.challenge = None;
                            self.won = None;
                            self.start_result(env);
                        }
                        _ => self.phase = Phase::List,
                    }
                }
            }
            Phase::Rate => {
                let n = self.rate_count();
                if keys & padbit::UP != 0 {
                    self.rate_sel = (self.rate_sel + n - 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::DOWN != 0 {
                    self.rate_sel = (self.rate_sel + 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if press & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.phase = Phase::Query;
                } else if press & padbit::CIRCLE != 0 {
                    env.sound(MenuSe::Decide);
                    // the list shows the highest rate first: cursor 0 = rate `rank`
                    self.challenge = Some(self.rank - self.rate_sel);
                    self.phase = Phase::RingIntro;
                    self.t = 0.0;
                }
            }
            Phase::RingIntro => {
                if self.t > 700.0 {
                    let mut rng = XorShift(self.seed | 1);
                    let row = (rng.rand() % 5) as usize;
                    self.ring = Some(ShopRing::start(self.challenge.unwrap_or(0), row, &self.d.tables.jring, self.seed));
                    self.phase = Phase::Ring;
                    self.t = 0.0;
                }
            }
            Phase::Ring => {
                let mut over = false;
                if let Some(r) = self.ring.as_mut() {
                    over = r.tick(press);
                    for e in r.ring.events.iter() {
                        let _ = e;
                    }
                }
                if over {
                    self.won = Some(self.ring.as_ref().map(|r| r.won()).unwrap_or(false));
                    self.phase = Phase::RingEnd;
                    self.t = 0.0;
                }
            }
            Phase::RingEnd => {
                if self.t > 500.0 {
                    self.ring = None;
                    self.start_result(env);
                }
            }
            Phase::Result => {
                self.result_t += DT_MS;
                if press & (padbit::CIRCLE | padbit::CROSS) != 0 && self.result_t > 300.0 {
                    env.sound(MenuSe::Decide);
                    // back to the list (`state 0x16`): rebuild it, or to the main menu when it is empty
                    let buy = self.buy;
                    self.rows.clear();
                    self.total = 0;
                    self.challenge = None;
                    self.won = None;
                    if self.enter_list(env, buy) {
                        self.phase = Phase::List;
                    } else {
                        self.main_sel = if buy { 0 } else { 1 };
                        self.phase = Phase::Main;
                    }
                }
            }
            Phase::Leaving => {
                self.fade = 1.0 - (self.t / 240.0).min(1.0);
                if self.t >= 240.0 {
                    // `~shop`: cash and shop points are written back
                    set_shop_points(env, self.points);
                    return ScreenFlow::Done;
                }
            }
        }
        ScreenFlow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = self.fade.clamp(0.0, 1.0);
        dim_field(g, a);
        // title "Shop" + shop name
        if let Some((t, (w, h))) = self.tex.title {
            blit(g, Some(t), 16.0, 12.0, w as f32, h as f32, (0.0, 0.0, w as f32, h as f32), Rgba::new(0x80, 0x80, 0x80, (128.0 * a) as u8));
        }
        if matches!(self.phase, Phase::FadeIn | Phase::Main | Phase::Leaving) {
            label(g, 24.0, 52.0, &self.name.0, a);
            label_c(g, 24.0, 70.0, &self.name.1, 14, Rgba::new(0x70, 0xc0, 0xff, (128.0 * a) as u8));
        }
        self.draw_cash(g, a);
        match self.phase {
            Phase::FadeIn | Phase::Main | Phase::Leaving => self.draw_main(g, a),
            // the ring and the result window are alone on the screen
            Phase::RingIntro | Phase::Ring | Phase::RingEnd | Phase::Result => {}
            _ => self.draw_list(g, a),
        }
        match self.phase {
            Phase::Query => self.draw_query(g),
            Phase::Rate => self.draw_rate(g),
            Phase::RingIntro => self.draw_msg(g, &(if self.buy { &self.d.text.challenge } else { &self.d.text.up_challenge }).replace("%s", &self.rate_name())),
            Phase::Ring | Phase::RingEnd => self.draw_ring(g),
            Phase::Result => self.draw_msg(g, &self.result_text),
            Phase::Warning => self.draw_msg(g, &self.warn_text),
            _ => {}
        }
    }
}

impl ShopScreen {
    fn rate_name(&self) -> String {
        let r = self.challenge.unwrap_or(0);
        let v = if self.buy { self.d.text.disc_select.get(r) } else { self.d.text.up_select.get(r) };
        crate::cmd_ui::sj(&sh2_menu::sjis::encode(v.map(|s| s.as_str()).unwrap_or("")))
    }

    fn draw_cash(&self, g: &mut dyn MenuGfx, a: f32) {
        let c = Rgba::new(0x80, 0x80, 0x80, (128.0 * a) as u8);
        if let Some((t, (w, h))) = self.tex.cash_label {
            blit(g, Some(t), 330.0, 14.0, w as f32, h as f32, (0.0, 0.0, w as f32, h as f32), c);
        }
        let s = format!("{}", self.cash);
        let wpx = self.digits.width(&s);
        self.digits.draw(g, 492.0 - wpx, 34.0, &s, c);
    }

    fn draw_main(&self, g: &mut dyn MenuGfx, a: f32) {
        let items = &self.d.text.main_menu;
        window(g, 170.0, 110.0, 190.0, 118.0, a);
        for (i, s) in items.iter().take(4).enumerate() {
            let y = 120.0 + 26.0 * i as f32;
            let sel = i == self.main_sel && self.phase == Phase::Main;
            if sel {
                fill(g, 176.0, y - 2.0, 178.0, 22.0, Rgba::new(0x50, 0x70, 0xc0, 0x40));
            }
            label(g, 190.0, y, s, a);
        }
        if self.phase == Phase::Main {
            let y = 120.0 + 26.0 * self.main_sel as f32;
            self.sc_cursor(g, 184.0, y + 10.0);
        }
        // the rank / discount explanation (`mSetupMainMenuWin` popup window at (96, 272))
        window(g, 96.0, 272.0, 320.0, 80.0, a);
        let card = if self.rank >= 4 && self.d.retail { 1 } else { 0 };
        let mut title = self.d.text.card.get(card).cloned().unwrap_or_default();
        if title.is_empty() {
            title = self.d.text.title.clone();
        }
        label_c(g, 106.0, 276.0, &title, 14, Rgba::new(0x70, 0xc0, 0xff, (128.0 * a) as u8));
        let pop = self.d.text.popup.get(self.rank.min(4)).cloned().unwrap_or_default();
        coded_text(g, 106.0, 298.0, &wrap_text(&pop, 38), 14, Rgba::new(0x80, 0x80, 0x80, (128.0 * a) as u8), 17.0, true);
    }

    fn sc_cursor(&self, g: &mut dyn MenuGfx, x: f32, y: f32) {
        if let Some(t) = self.sc.cmn.s.t(2) {
            let k = (self.anim * 0.012).sin().abs().max(0.4);
            blit(g, Some(t), x - 22.0, y - 10.0 * k, 20.0, 20.0 * k, (0.0, 0.0, 20.0, 20.0), Rgba::new(0x80, 0x80, 0x80, 0x80));
        } else {
            label(g, x - 14.0, y - 9.0, ">", 1.0);
        }
    }

    fn draw_list(&self, g: &mut dyn MenuGfx, a: f32) {
        let t = &self.d.text;
        // title window with the rank line
        window(g, 144.0, 32.0, 184.0, 32.0, a);
        let title = if self.buy { &t.title_buy_rank } else { &t.title_sell_rank };
        coded_text(g, 152.0, 38.0, title.get(self.rank.min(4)).map(|s| s.as_str()).unwrap_or(""), 14, Rgba::new(0x80, 0x80, 0x80, 0x80), 17.0, true);
        // goods list (40, 72) 224 x 105
        window(g, 40.0, 72.0, 224.0, 105.0, a);
        for (vi, row) in self.rows.iter().enumerate().skip(self.top).take(VISIBLE_ROWS) {
            let y = 76.0 + 20.0 * (vi - self.top) as f32;
            let sel = vi == self.sel;
            if sel {
                fill(g, 44.0, y - 1.0, 216.0, 19.0, Rgba::new(0x50, 0x70, 0xc0, 0x40));
            }
            let dim = row.limit <= 1 && self.buy || row.price == -1 && !self.buy;
            let c = if dim { Rgba::new(0x50, 0x50, 0x50, 0x80) } else { Rgba::new(0x80, 0x80, 0x80, 0x80) };
            let name = crate::shop::display_name_cache(self, row);
            text_run(g, 56.0, y, &name, 14, c, Some((1, 1)));
            let price = if row.price == -1 { "-------".to_string() } else { cfmt("%7d", &[A::I(row.price as i64)]) };
            text_run(g, 148.0, y, &price, 14, c, None);
            text_run(g, 222.0, y, &cfmt("x%2d", &[A::I(row.qty as i64)]), 14, c, None);
        }
        if self.rows.len() > VISIBLE_ROWS {
            let y0 = 72.0;
            if self.top > 0 {
                label(g, 150.0, y0 - 14.0, "^", a);
            }
            if self.top + VISIBLE_ROWS < self.rows.len() {
                label(g, 150.0, y0 + 105.0, "v", a);
            }
            text_run(g, 232.0, 180.0, &cfmt("%2d/%2d", &[A::I((self.sel / VISIBLE_ROWS + 1) as i64), A::I(self.rows.len().div_ceil(VISIBLE_ROWS) as i64)]), 14, Rgba::new(0x80, 0x80, 0x80, 0x80), Some((1, 1)));
        }
        // quantity and totals (right side)
        let i = &t.info;
        let get = |k: usize| i.get(k).cloned().unwrap_or_default();
        window(g, 300.0, 72.0, 190.0, 112.0, a);
        let amount = self.shown_amount();
        let blue = Rgba::new(0x70, 0xc0, 0xff, 0x80);
        let white = Rgba::new(0x80, 0x80, 0x80, 0x80);
        label_c(g, 308.0, 76.0, &get(0), 14, blue);
        text_right(g, 482.0, 76.0, &cfmt("%d", &[A::I(self.total as i64)]), 14, white, Some((1, 1)));
        if amount != self.total && self.total > 0 {
            label_c(g, 308.0, 94.0, &get(if self.buy { 5 } else { 6 }), 14, blue);
            text_right(g, 482.0, 94.0, &cfmt("%d", &[A::I((amount - self.total).abs() as i64)]), 14, white, Some((1, 1)));
        }
        // points / next rank
        for (k, l) in get(1).split('$').enumerate() {
            label_c(g, 308.0, 114.0 + 16.0 * k as f32, l, 14, blue);
        }
        text_right(g, 482.0, 114.0, &cfmt("%d", &[A::I(self.points as i64)]), 14, white, Some((1, 1)));
        if self.rank < self.d.tables.max_rank {
            text_right(g, 482.0, 130.0, &cfmt("%d", &[A::I(self.to_next.max(0) as i64)]), 14, white, Some((1, 1)));
        } else {
            text_right(g, 482.0, 130.0, "------", 14, white, Some((1, 1)));
        }
        // equipped / owned of the selected goods
        if let Some(r) = self.rows.get(self.sel) {
            for (k, l) in get(2).split('$').enumerate() {
                label_c(g, 308.0, 150.0 + 16.0 * k as f32, l, 14, blue);
            }
            text_right(g, 482.0, 150.0, &format!("{}", r.equipped), 14, white, Some((1, 1)));
            text_right(g, 482.0, 166.0, &format!("{}", r.owned), 14, white, Some((1, 1)));
        }
        // party faces with the equipment comparison
        for (i, p) in self.pcs.iter().enumerate() {
            let x = 62.0 + 54.0 * i as f32;
            // retail `MENU/FACE` numbers start at 6 (`FI_006` = the first portrait of the retail `SHOP.DAT`)
            let fi = if self.d.retail && p.face >= 6 { p.face as usize - 6 } else { p.face as usize };
            if let Some(Some(f)) = self.tex.faces.get(fi) {
                blit(g, Some(*f), x, 190.0, 48.0, 52.0, (0.0, 0.0, 56.0, 70.0), Rgba::new(0x80, 0x80, 0x80, (128.0 * a) as u8));
            }
            if let Some((fr, (w, h))) = self.tex.frame {
                blit(g, Some(fr), x - 4.0, 186.0, 56.0, 64.0 * 56.0 / (h as f32).max(1.0) * (h as f32 / 64.0), (0.0, 0.0, w as f32, h as f32), Rgba::new(0x80, 0x80, 0x80, (128.0 * a) as u8));
            }
            if self.equipped_here.get(i).copied().unwrap_or(false) {
                label_c(g, x + 34.0, 192.0, &self.d.text.equip_mark, 2, Rgba::new(0xff, 0xd0, 0x40, 0x80));
            }
            let dim = !self.can_equip.get(i).copied().unwrap_or(false);
            if let Some(cells) = self.cmp.get(i) {
                for (k, (v, d)) in cells.iter().enumerate() {
                    let col = if dim && self.rows.get(self.sel).map(|r| matches!(r.kind, 2..=4)).unwrap_or(false) {
                        Rgba::new(0x40, 0x40, 0x40, 0x80)
                    } else if *d > 0 {
                        Rgba::new(0xff, 0xd0, 0x40, 0x80)
                    } else if *d < 0 {
                        Rgba::new(0x70, 0xa0, 0xff, 0x80)
                    } else {
                        Rgba::new(0x80, 0x80, 0x80, 0x80)
                    };
                    let mark = if *d > 0 { "+" } else if *d < 0 { "-" } else { " " };
                    text_run(g, x, 258.0 + 18.0 * k as f32, &format!("{:3}{}", v, mark), 14, col, Some((1, 1)));
                }
            }
        }
        for (k, s) in t.status.iter().take(4).enumerate() {
            label_c(g, 8.0, 258.0 + 18.0 * k as f32, s, 2, Rgba::new(0x70, 0xc0, 0xff, 0x80));
        }
        // description note
        window(g, 8.0, 340.0, 496.0, 66.0, a);
        if let Some((nt, (w, h))) = self.tex.note {
            blit(g, Some(nt), 14.0, 344.0, w as f32 * 0.6, h as f32 * 0.6, (0.0, 0.0, w as f32, h as f32), Rgba::new(0x80, 0x80, 0x80, 0x80));
        }
        for (k, l) in self.desc.lines().take(3).enumerate() {
            text_run(g, 70.0, 346.0 + 18.0 * k as f32, &sh2_menu::sjis::strip_codes(l), 14, Rgba::new(0x80, 0x80, 0x80, 0x80), Some((1, 1)));
        }
        // scroll hint
        label_c(g, 380.0, 412.0, &get(3), 14, Rgba::new(0x80, 0x80, 0x80, 0x80));
        if self.phase == Phase::List {
            self.sc_cursor(g, 54.0, 76.0 + 20.0 * (self.sel - self.top) as f32 + 9.0);
        }
    }

    fn draw_query(&self, g: &mut dyn MenuGfx) {
        let (q, note) = if self.buy { (&self.d.text.query_buy, &self.d.text.query_buy_note) } else { (&self.d.text.query_sell, &self.d.text.query_sell_note) };
        window(g, 130.0, 190.0, 252.0, 110.0, 1.0);
        label(g, 142.0, 194.0, q.get(3).map(|s| s.as_str()).unwrap_or(""), 1.0);
        for i in 0..3 {
            let y = 222.0 + 22.0 * i as f32;
            if i == self.query_sel {
                fill(g, 136.0, y - 2.0, 240.0, 21.0, Rgba::new(0x50, 0x70, 0xc0, 0x50));
                self.sc_cursor(g, 150.0, y + 9.0);
            }
            label(g, 160.0, y, q.get(i).map(|s| s.as_str()).unwrap_or(""), 1.0);
        }
        window(g, 8.0, 420.0, 496.0, 22.0, 1.0);
        text_run(g, 16.0, 422.0, note.get(self.query_sel).map(|s| s.as_str()).unwrap_or(""), 14, Rgba::new(0x80, 0x80, 0x80, 0x80), Some((1, 1)));
    }

    fn draw_rate(&self, g: &mut dyn MenuGfx) {
        let sel = if self.buy { &self.d.text.disc_select } else { &self.d.text.up_select };
        let prompt = if self.buy { &self.d.text.disc_select_prompt } else { &self.d.text.up_select_prompt };
        let n = self.rate_count();
        window(g, 150.0, 170.0, 212.0, 40.0 + 22.0 * n as f32, 1.0);
        for i in 0..n {
            let rate = self.rank - i;
            let y = 178.0 + 22.0 * i as f32;
            if i == self.rate_sel {
                fill(g, 156.0, y - 2.0, 200.0, 21.0, Rgba::new(0x50, 0x70, 0xc0, 0x50));
                self.sc_cursor(g, 170.0, y + 9.0);
            }
            label(g, 180.0, y, sel.get(rate).map(|s| s.as_str()).unwrap_or(""), 1.0);
        }
        window(g, 8.0, 420.0, 496.0, 22.0, 1.0);
        text_run(g, 16.0, 422.0, prompt, 14, Rgba::new(0x80, 0x80, 0x80, 0x80), Some((1, 1)));
        // the note of the highlighted rate (`shopMess_discountSelectNote_J` with the rate name)
    }

    fn draw_msg(&self, g: &mut dyn MenuGfx, text: &str) {
        window(g, 40.0, 332.0, 432.0, 110.0, 1.0);
        coded_text(g, 56.0, 340.0, &wrap_text(&text, 50), 14, Rgba::new(0x80, 0x80, 0x80, 0x80), 20.0, true);
    }

    /// The challenge ring: base circle, the three step areas, the pointer (`JRing` drawn on the 512x448 screen at (256, 288)).
    fn draw_ring(&self, g: &mut dyn MenuGfx) {
        let Some(run) = self.ring.as_ref() else { return };
        let r = &run.ring;
        let (cx, cy) = (256.0f32, 288.0f32);
        let (rx, ry) = (112.0 * r.scale_x.max(0.2), 112.0 * r.scale_y.max(0.2));
        window(g, cx - rx - 20.0, cy - ry - 20.0, rx * 2.0 + 40.0, ry * 2.0 + 40.0, 0.5);
        let pt = |ang: f32, k: f32| {
            let a = ang.to_radians();
            (cx + a.sin() * rx * k, cy - a.cos() * ry * k)
        };
        let seg = |g: &mut dyn MenuGfx, a0: f32, a1: f32, k0: f32, k1: f32, c: Rgba| {
            let (p0, p1, p2, p3) = (pt(a0, k0), pt(a0, k1), pt(a1, k0), pt(a1, k1));
            g.draw(sh2_menu::gfx::DrawCmd::Quad {
                tex: None,
                v: [crate::cmd_ui::vtx(p0.0, p0.1, 0.0, 0.0, c), crate::cmd_ui::vtx(p1.0, p1.1, 0.0, 0.0, c), crate::cmd_ui::vtx(p2.0, p2.1, 0.0, 0.0, c), crate::cmd_ui::vtx(p3.0, p3.1, 0.0, 0.0, c)],
                blend: sh2_menu::gfx::Blend::Alpha,
            });
        };
        let ring_c = Rgba::new(0x60, 0x70, 0xa0, 0x80);
        for s in 0..72 {
            let a0 = s as f32 * 5.0;
            seg(g, a0, a0 + 5.2, 0.97, 1.03, ring_c);
        }
        for ar in r.areas.iter().filter(|a| a.kind.is_some()) {
            let n = ((ar.width as f32 / 4.0).ceil() as i32).max(1);
            for s in 0..n {
                let a0 = ar.start as f32 + ar.width as f32 * s as f32 / n as f32;
                let a1 = ar.start as f32 + ar.width as f32 * (s + 1) as f32 / n as f32 + 0.4;
                let hit = ar.result >= 0;
                seg(g, a0, a1, 0.82, 1.0, if hit { Rgba::new(0xff, 0xe0, 0x40, 0x80) } else { Rgba::new(0x10, 0xd0, 0x70, 0x80) });
            }
        }
        if r.pointer_visible || self.phase == Phase::Ring {
            let tip = pt(r.cur_angle, 1.05);
            let c = Rgba::new(0xff, 0xff, 0xa0, 0x80);
            let (p0, p1) = (pt(r.cur_angle - 1.6, 0.2), pt(r.cur_angle + 1.6, 0.2));
            g.draw(sh2_menu::gfx::DrawCmd::Quad {
                tex: None,
                v: [crate::cmd_ui::vtx(p0.0, p0.1, 0.0, 0.0, c), crate::cmd_ui::vtx(p1.0, p1.1, 0.0, 0.0, c), crate::cmd_ui::vtx(tip.0, tip.1, 0.0, 0.0, c), crate::cmd_ui::vtx(tip.0, tip.1, 0.0, 0.0, c)],
                blend: sh2_menu::gfx::Blend::Alpha,
            });
        }
        if self.phase == Phase::RingEnd {
            let won = self.won.unwrap_or(false);
            let s = if won { "OK!" } else { "MISS" };
            text_run(g, cx - 24.0, cy - 12.0, s, 0, if won { Rgba::new(0xff, 0xe0, 0x40, 0x80) } else { Rgba::new(0xc0, 0x60, 0x60, 0x80) }, Some((1, 1)));
        }
        let _ = (SCREEN_W, SCREEN_H);
    }
}

/// Name of a list row.
pub fn display_name_cache(s: &ShopScreen, row: &Row) -> String {
    s.names.get(&(row.kind, row.idx)).cloned().unwrap_or_default()
}

#[cfg(test)]
mod tests {
    use super::*;

    fn tbl() -> PointTbl {
        [5, 12, 25, 99999, 999999]
    }

    #[test]
    fn rank_follows_the_point_table() {
        let t = tbl();
        assert_eq!(rank_of(0, &t, 3), 0);
        assert_eq!(rank_of(4, &t, 3), 0);
        assert_eq!(rank_of(5, &t, 3), 1);
        assert_eq!(rank_of(11, &t, 3), 1);
        assert_eq!(rank_of(13, &t, 3), 2);
        assert_eq!(rank_of(25, &t, 3), 3);
        // the demo caps at B (3), the retail game reaches A (4)
        assert_eq!(rank_of(10_000_000, &t, 3), 3);
        assert_eq!(rank_of(10_000_000, &t, 4), 4);
    }

    #[test]
    fn penalty_lowers_the_rank() {
        let t = tbl();
        let mut r = 2;
        assert!(calc_point(&mut r, 4, &t, 3, false));
        assert!(calc_point(&mut r, 4, &t, 3, false));
        assert!(!calc_point(&mut r, 4, &t, 3, false));
        assert_eq!(r, 0);
    }

    #[test]
    fn quantity_limit_counts_the_best_discount() {
        // 200 each, rank 1 (20 % off at best): cash 1000, nothing chosen yet -> floor(1000 / 160) + 1 = 7
        let row = Row { price: 200, kind: 1, idx: 0, qty: 0, limit: 100, equipped: 0, owned: 0 };
        assert_eq!(current_max_buy(&row, 0, 1000, 1), 7);
        // the stock limit wins
        let row = Row { limit: 3, ..row };
        assert_eq!(current_max_buy(&row, 0, 1000, 1), 3);
    }

    #[test]
    fn discount_and_markup_amounts() {
        assert_eq!(disc_amount(1000, 0), 100);
        assert_eq!(disc_amount(1000, 4), 500);
        assert_eq!(up_amount(1000, 0), 50);
        assert_eq!(up_amount(1000, 4), 250);
    }

    #[test]
    fn buying_without_a_challenge_earns_points() {
        let o = buy_outcome(1250, 5000, 1, None, false, false);
        assert_eq!(o, Outcome { done: true, amount: 1250, points: 13, msg: 0 });
    }

    #[test]
    fn won_challenge_pays_the_discounted_price() {
        let o = buy_outcome(1000, 5000, 2, Some((2, true)), false, false);
        assert_eq!(o.amount, 700);
        assert_eq!(o.points, 7);
        assert_eq!(o.msg, 1);
    }

    #[test]
    fn lost_challenge_pays_the_set_price_when_affordable() {
        let o = buy_outcome(1000, 5000, 2, Some((2, false)), false, false);
        assert!(o.done);
        assert_eq!(o.amount, 1000);
        assert_eq!(o.msg, 2);
    }

    #[test]
    fn lost_challenge_without_the_cash_costs_points_and_the_goods() {
        // retail: ((cash + 9) - discounted total) / 10 clamped to >= 1 points lost; rank A is exempt
        let o = buy_outcome(1000, 300, 1, Some((1, false)), true, true);
        assert!(!o.done);
        assert_eq!(o.msg, 3);
        assert!(o.points <= -1);
        let gold = buy_outcome(1000, 300, 4, Some((1, false)), true, true);
        assert!(!gold.done);
        assert_eq!(gold.points, 0);
    }

    #[test]
    fn selling_with_a_won_price_up() {
        let o = sell_outcome(400, Some((3, true)));
        assert_eq!(o.amount, 400 + 400 * 4 / 20);
        let o = sell_outcome(400, Some((3, false)));
        assert_eq!(o.amount, 400);
    }

    #[test]
    fn challenge_ring_areas_shrink_with_the_rate() {
        let t = [[100u16, 200, 300, 10]; 5];
        let a = challenge_areas(&t, 0, 0);
        assert_eq!(a[0], (75, 62));
        let b = challenge_areas(&t, 0, 4);
        assert_eq!(b[0], (95, 12));
        assert!((challenge_period(4) - 1.2).abs() < 1e-6);
    }

    #[test]
    fn bag_arrays_roundtrip() {
        let mut b = BtlSave::new_zeroed();
        bag_add(&mut b, 1, 3, 5);
        bag_add(&mut b, 2, 7, 1);
        assert_eq!(bag_count(&b, 1, 3), 5);
        assert_eq!(bag_count(&b, 2, 7), 1);
        bag_add(&mut b, 1, 3, -9);
        assert_eq!(bag_count(&b, 1, 3), 0);
        bag_add(&mut b, 5, 11, 1);
        assert!(bit_set(&b, 5, 11));
    }

    /// The real tables of the disc (JP demo / US retail) when `SH2_DISC_DIR` / `SH2_US_DISC_DIR` are set.
    #[test]
    fn real_tables_if_present() {
        for (var, retail, shops, max_rank) in [("SH2_DISC_DIR", false, 3usize, 3usize), ("SH2_US_DISC_DIR", true, 25, 4)] {
            let Some(dir) = std::env::var_os(var) else { continue };
            let Ok(bytes) = std::fs::read(std::path::Path::new(&dir).join("FIELD.BIN")) else { continue };
            let img = OverlayImage::new(bytes).unwrap();
            let t = ShopTables::from_overlay(&img, retail).unwrap();
            assert_eq!(t.items.len(), shops);
            assert!(t.items.iter().all(|s| !s.is_empty()), "{var}: empty shop table");
            assert_eq!(t.max_rank, max_rank);
            assert!(t.points[0] > 0 && t.points.windows(2).all(|w| w[0] < w[1]));
            assert_eq!(t.jring[0][3], 10);
            if !retail {
                let text = ShopText::from_jp(&img).unwrap();
                assert_eq!(text.main_menu.len(), 4);
                assert_eq!(text.title, "ショップ");
            }
        }
    }
}
