//! `TargetInfo` (the target plate, top right): retail geometry of `TargetInfo::MakePacket`.
//!
//! Retail (`SLUS_210.41` + `BATTLE.BIN`, JP demo addresses in brackets):
//! * `TargetInfo::__ct(int, int, int, short, short)` 0x524d90 [0x501fd0] -- fighter `+0x48`, `Entry` into the poller
//! * `TargetInfo::Polling`    0x5250d0 [0x5022c0] -- [`poll_phase`]: the pulse phase `+0x11c` (+2 per second, wrapped at pi) and the status icon frame clocks
//! * `TargetInfo::MakePacket` 0x525350 [0x5024d0] -- [`layout`]
//! * `TargetInfo::EndSet`     0x57df20 [0x54b280] -- virtual call 0x30 of the object (destroys it)
//!
//! Object lifetime: `__dt` 0x524f10 [0x502110] and `Destruct` 0x525070 [0x502270] (`Dispose` from the poller) are the owner's `Option` here (the plate exists while
//! the target page is open).
//!
//! The plate is anchored at `P = (301, 60)` (packet `0x82d, 0x75c` minus the GS centre 1792 / 1824).  Its kind ([`Kind`], `iVar17`): 1 = a party
//! member, 0 = an enemy (HP shown as `?????`), 2 = an enemy whose library bit (`BtlSave + 0xf63`) is set while Anastasia (`BtlChr+0x120 == 4`) is in the
//! party (the plate grows: MP row, class ring with the element, the camera mark).  Width `W = max(0.8 * name image + 37.5, 96)` (168 for kind 2), height
//! `H = 50` (72) plus the status icon rows; the frame is the fill quad `(P.x-4, P.y-5)..(P.x+W+11, P.y+H+5)` and eight sprites of `BTL_000` entry 8
//! (edges and four corner curls), the separator above the status icons, the card (entry 19 capsule + the face), the name, the `HP` label, five digit
//! columns (pitch 8.8, 14 px tall, columns blank by the leading-zero rule), the gauge (track strip + fill) and the extras of kind 2.
//!
//! Flat colours in [`Prim::Flat`] are GS values (0..255 straight); the port's `Rgba` convention for flat quads is half of them (0x80 = 1.0).

use std::f32::consts::{PI, TAU};

/// `BTL_000` entries
pub const T_DIGITS: u8 = 2;
pub const T_GAUGE: u8 = 3;
pub const T_ORNAMENT: u8 = 8;
pub const T_ELEMENT: u8 = 11;
pub const T_RING: u8 = 12;
pub const T_CAMERA: u8 = 13;
pub const T_CARDS: u8 = 19;
pub const T_LETTERS: u8 = 24;

/// Colour of the class ring and the element glyph: the retail packet switches the texture's palette per element (a `TEX0` CLUT change in the lost
/// `switch (element)` tail); the only captured one (`12d`, dark) is lavender, which the port uses for every element until the others are photographed.
pub const RING_TINT: Rgba8 = [0x4a, 0x46, 0x64, 0x80];

/// Plate anchor (screen).
pub const PX: f32 = 301.0;
pub const PY: f32 = 60.0;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Kind {
    /// `iVar17 == 0`
    Enemy,
    /// `iVar17 == 1`
    Party,
    /// `iVar17 == 2`
    Photo,
}

#[derive(Clone, Debug)]
pub struct Input {
    pub kind: Kind,
    /// the HP digits are real values (`false`: `?????`, also for kind 0 where the packet shows `?` unconditionally)
    pub hp_visible: bool,
    /// width of the drawn name in px (the packet uses `0.8 * (name image width)`; the port measures the text it draws)
    pub name_w: f32,
    /// enemy letter 0 = A .. 7 = H
    pub letter: u8,
    pub model: u32,
    pub hp: i32,
    pub max_hp: i32,
    pub mp: i32,
    pub max_mp: i32,
    /// 0 earth, 1 water, 2 fire, 3 wind, 4 light, 5 dark, 6+ none (`kind 2` only)
    pub element: u8,
    /// status icons shown under the HP row
    pub icons: usize,
    /// pulse phase of the object (`+0x11c`)
    pub phase: f32,
}

#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Tex {
    Btl(u8),
    /// a party member's card portrait (36 x 46, the port builds it from `FI_`)
    Card(u32),
}

pub type Rgba8 = [u8; 4];

#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Prim {
    /// untextured gouraud strip (top-left, bottom-left, top-right, bottom-right) with GS colours
    Flat { pos: [(f32, f32); 4], col: [Rgba8; 4] },
    /// textured sprite: `uv` = (u0, v0, u1, v1) texels, `dst` = (x0, y0, x1, y1); a reversed `uv` pair mirrors
    Sprite { tex: Tex, uv: (f32, f32, f32, f32), dst: (f32, f32, f32, f32), rgba: Rgba8 },
    /// textured strip (gauge track): vertices (x, y, u, v) in strip order
    Strip { tex: Tex, v: [(f32, f32, f32, f32); 8], rgba: Rgba8 },
    /// status icon `n` (0-based) of the icon rows at the given top-left
    Icon { n: usize, x: f32, y: f32 },
}

/// `Polling`: the pulse phase advances 2 rad per second and wraps at pi (kind 2 ring / element alpha).
pub fn poll_phase(phase: f32, dt: f32) -> f32 {
    let p = phase + dt * 2.0;
    if p >= PI {
        p - TAU
    } else {
        p
    }
}

/// Plate size `(W, H)` of the packet's first lines.
pub fn size(kind: Kind, name_w: f32, icons: usize) -> (f32, f32) {
    let min_w = if kind == Kind::Photo { 168.0 } else { 96.0 };
    // the original: (int)(name image * 0.8 + 0.5 + 37); the port's measured text stands for `0.8 * name image` plus the circled-number slack (+4.5)
    let w = (name_w + 42.0).floor().max(min_w);
    let mut h = if kind == Kind::Photo { 72.0 } else { 50.0 };
    if icons > 0 {
        // one row of icons 23 px tall (20 px pitch from x 26, a new row when the pitch passes W), then `h - 2`, then the separator's 9 (10)
        h += 23.0;
        let mut x = 26.0;
        for _ in 1..icons {
            x += 20.0;
            if w < x {
                x = 26.0;
                h += 23.0;
            }
        }
        h -= 2.0;
        h += if kind == Kind::Photo { 10.0 } else { 9.0 };
    }
    (w, h)
}

/// Where the status icons start (top-left of the first icon) and the row geometry.
pub fn icon_origin(kind: Kind) -> (f32, f32) {
    // live `i3`: icons from x 309, y 120 (`iStack_30 = 0x3b` / 0x4e below the anchor, +1)
    (PX + 8.0, PY + if kind == Kind::Photo { 0x4e } else { 0x3b } as f32 + 1.0)
}

/// HP / MP digit colour of the packet: white; yellow at or under half (`>> 1`, floor 2), red at or under a quarter (`>> 2`, floor 1) or at 0.
pub fn digit_colour(cur: i32, max: i32) -> Rgba8 {
    let mut half = max >> 1;
    if half < 2 && max > 2 {
        half = 2;
    }
    let mut quarter = max >> 2;
    if quarter == 0 && max > 1 {
        quarter = 1;
    }
    if cur == 0 || cur <= half {
        if cur == 0 || cur <= quarter {
            [0x80, 0x00, 0x00, 0x80]
        } else {
            [0x80, 0x80, 0x00, 0x80]
        }
    } else {
        [0x80, 0x80, 0x80, 0x80]
    }
}

/// Digit texel column of entry 2 for digit `d` (`d * 11 + 0x4d`; 11 is `?`).
pub fn digit_u(d: u32) -> f32 {
    (d * 11 + 0x4d) as f32
}

/// The five digit columns: `Some(d)` per column (`None` = blank).  Enemies of kind 0 show `?` (11) in every column; the others blank the leading zeros
/// (the units digit always shows).
pub fn digit_columns(value: i32, kind: Kind) -> [Option<u32>; 5] {
    let mut out = [None; 5];
    let v = value.max(0);
    let limits = [10000, 1000, 100, 10, 0];
    for (i, o) in out.iter_mut().enumerate() {
        if kind == Kind::Enemy {
            *o = Some(11);
        } else if v >= limits[i] {
            *o = Some(((v / 10i32.pow(4 - i as u32)) % 10) as u32);
        }
    }
    out
}

/// Gauge fill width in px: `value * 63 / max` (0 hides the fill).
pub fn gauge_width(cur: i32, max: i32) -> f32 {
    if max <= 0 {
        return 0.0;
    }
    ((cur as f32 * 63.0) / max as f32).max(0.0)
}

fn spr(tex: Tex, uv: (f32, f32, f32, f32), dst: (f32, f32, f32, f32)) -> Prim {
    Prim::Sprite { tex, uv, dst, rgba: [0x80; 4] }
}

/// `MakePacket`: the primitives in packet order.
pub fn layout(i: &Input) -> Vec<Prim> {
    let (w, h) = size(i.kind, i.name_w, i.icons);
    let (px, py) = (PX, PY);
    let mut out = Vec::with_capacity(64);
    let photo = i.kind == Kind::Photo;

    // fill: a gouraud strip, (0x41,0x41,0x4e) at the top to (0x0a,0x08,0x0a) at the bottom, alpha 0x4c
    let top = [0x41, 0x41, 0x4e, 0x4c];
    let bot = [0x0a, 0x08, 0x0a, 0x4c];
    out.push(Prim::Flat { pos: [(px - 4.0, py - 5.0), (px - 4.0, py + h + 5.0), (px + w + 11.0, py - 5.0), (px + w + 11.0, py + h + 5.0)], col: [top, bot, top, bot] });

    // frame: edges (16 x 7 and 7 x 16 pieces stretched) and the four corner curls of entry 8
    let e = Tex::Btl(T_ORNAMENT);
    out.push(spr(e, (42.0, 33.0, 58.0, 40.0), (px + 16.0, py - 10.0, px + w - 8.0, py - 3.0)));
    out.push(spr(e, (42.0, 33.0, 58.0, 40.0), (px + 15.0, py + h + 3.0, px + w - 8.0, py + h + 10.0)));
    out.push(spr(e, (34.0, 34.0, 41.0, 50.0), (px - 9.0, py + 17.0, px - 2.0, py + h - 33.0)));
    out.push(spr(e, (34.0, 34.0, 41.0, 50.0), (px + w + 9.0, py + 33.0, px + w + 16.0, py + h - 17.0)));
    // top-left curl (texels (34,0)-(65,33) mirrored both ways), bottom-left gem (0,0)-(34,49) mirrored both ways, top-right gem (0,0)-(34,49), bottom-right curl (34,0)-(65,33)
    out.push(spr(e, (65.0, 33.0, 34.0, 0.0), (px - 14.0, py - 14.0, px + 17.0, py + 19.0)));
    out.push(spr(e, (34.0, 49.0, 0.0, 0.0), (px - 17.0, py + h - 35.0, px + 17.0, py + h + 14.0)));
    out.push(spr(e, (0.0, 0.0, 34.0, 49.0), (px + w - 10.0, py - 14.0, px + w + 24.0, py + 35.0)));
    out.push(spr(e, (34.0, 0.0, 65.0, 33.0), (px + w - 10.0, py + h - 19.0, px + w + 21.0, py + h + 14.0)));

    // separator over the status icons: 4 px lavender line, faded at both ends over (W + 13) / 3 (at most 64) px
    if i.icons > 0 {
        let y = py + if photo { 0x47 } else { 0x34 } as f32;
        let x0 = px - 3.0;
        let ramp = (((w + 13.0) / 3.0).floor()).min(64.0);
        let x1 = x0 + w + 10.0;
        let (c0, c1) = ([0x82, 0x7d, 0x97, 0x00], [0x82, 0x7d, 0x97, 0x80]);
        let quad = |xa: f32, xb: f32, ca: Rgba8, cb: Rgba8| Prim::Flat { pos: [(xa, y), (xa, y + 4.0), (xb, y), (xb, y + 4.0)], col: [ca, ca, cb, cb] };
        out.push(quad(x0, x0 + ramp, c0, c1));
        out.push(quad(x0 + ramp, x1 - ramp, c1, c1));
        out.push(quad(x1 - ramp, x1, c1, c0));
    }

    // card: the grey capsule (entry 19, 37 x 50) and the face (36 x 46) one pixel in
    out.push(spr(Tex::Btl(T_CARDS), (0.0, 0.0, 37.0, 50.0), (px, py, px + 37.0, py + 50.0)));
    if i.kind == Kind::Party {
        out.push(spr(Tex::Card(i.model), (0.0, 0.0, 36.0, 46.0), (px + 1.0, py + 1.0, px + 37.0, py + 47.0)));
    } else {
        let (col, row) = ((i.letter / 4) as f32 * 36.0, (i.letter % 4) as f32 * 46.0);
        out.push(spr(Tex::Btl(T_LETTERS), (col, row, col + 36.0, row + 46.0), (px + 1.0, py + 1.0, px + 37.0, py + 47.0)));
    }

    // gauge: the 68 x 8 track (entry 3 rows 8..16, caps of 3 px, middle 45 texels stretched to 62) and the fill (entry 3 row 0..8 from texel 2)
    let gauge = |out: &mut Vec<Prim>, y: f32, u_off: f32, cur: i32, max: i32| {
        let (x0, x1, x2, x3) = (px + 35.0, px + 38.0, px + 100.0, px + 103.0);
        out.push(Prim::Strip { tex: Tex::Btl(T_GAUGE), v: [(x0, y, 0.0, 8.0), (x0, y + 8.0, 0.0, 16.0), (x1, y, 3.0, 8.0), (x1, y + 8.0, 3.0, 16.0), (x2, y, 48.0, 8.0), (x2, y + 8.0, 48.0, 16.0), (x3, y, 51.0, 8.0), (x3, y + 8.0, 51.0, 16.0)], rgba: [0x80; 4] });
        let fw = gauge_width(cur, max);
        if fw != 0.0 {
            let fx = px + 37.0;
            out.push(spr(Tex::Btl(T_GAUGE), (2.0 + u_off, 0.0, fw * 46.0 / 63.0 + 2.0 + 1.0 + u_off, 8.0), (fx, y, fx + fw + 1.0, y + 8.0)));
        }
    };
    // labels + digits
    let label = |out: &mut Vec<Prim>, y: f32, u0: f32| out.push(spr(Tex::Btl(T_DIGITS), (u0, 1.0, u0 + 19.0, 12.0), (px + 37.0, y, px + 56.0, y + 11.0)));
    let digits = |out: &mut Vec<Prim>, y: f32, cur: i32, max: i32, kind: Kind| {
        let col = digit_colour(cur, max);
        for (k, d) in digit_columns(cur, kind).iter().enumerate() {
            if let Some(d) = d {
                let x = px + 58.0 + 8.8 * k as f32;
                let u = digit_u(*d);
                out.push(Prim::Sprite { tex: Tex::Btl(T_DIGITS), uv: (u, 1.0, u + 11.0, 15.0), dst: (x, y, x + 8.8, y + 14.0), rgba: col });  // the `?` glyphs take the HP colour too (the packet colours by the real HP)
            }
        }
    };
    gauge(&mut out, py + 39.0, 0.0, i.hp, i.max_hp);
    label(&mut out, py + 27.0, 1.0);
    digits(&mut out, py + 27.0, i.hp, i.max_hp, if i.hp_visible { if i.kind == Kind::Enemy { Kind::Photo } else { i.kind } } else { Kind::Enemy });
    if photo {
        gauge(&mut out, py + 61.0, 51.0, i.mp, i.max_mp);
        label(&mut out, py + 48.0, 20.0);
        // the MP value never blanks as `?` (kind 2 only)
        digits(&mut out, py + 48.0, i.mp, i.max_mp, Kind::Photo);
        // class ring: two sprites 40 x 42 at (P.x+107, P.y+24), the second (the dashed outline) pulsing 0.5 .. 1.5, the element 22 x 25 pulsing 1 .. 1.5
        let s = i.phase.sin();
        let a_ring = ((s / 2.0 + 1.0) * 128.0) as i32;
        let a_elem = (((s + 1.0) / 4.0 + 1.0) * 128.0) as i32;
        let (rx, ry) = (px + 107.0, py + 24.0);
        out.push(Prim::Sprite { tex: Tex::Btl(T_RING), uv: (0.0, 0.0, 40.0, 44.0), dst: (rx, ry, rx + 40.0, ry + 42.0), rgba: [0x80; 4] });
        out.push(Prim::Sprite { tex: Tex::Btl(T_RING), uv: (40.0, 0.0, 80.0, 44.0), dst: (rx, ry, rx + 40.0, ry + 42.0), rgba: [RING_TINT[0], RING_TINT[1], RING_TINT[2], a_ring.clamp(0, 255) as u8] });
        let u = (i.element.min(6) as f32) * 22.0;
        out.push(Prim::Sprite { tex: Tex::Btl(T_ELEMENT), uv: (u, 0.0, u + 22.0, 25.0), dst: (px + 127.0 - 11.0, py + 46.0 - 12.5, px + 127.0 + 11.0, py + 46.0 + 12.5), rgba: [RING_TINT[0], RING_TINT[1], RING_TINT[2], a_elem.clamp(0, 255) as u8] });
        out.push(spr(Tex::Btl(T_CAMERA), (0.0, 0.0, 27.0, 42.0), (px + 149.0, py + 25.0, px + 176.0, py + 67.0)));
    }

    // status icons: 19 x 23 from the sheet of entry 39, 20 px apart, a new row (23 px) when the pitch passes W
    if i.icons > 0 {
        let (ox, oy) = icon_origin(i.kind);
        let (mut x, mut y) = (ox, oy);
        let mut right = 26.0;
        for n in 0..i.icons {
            if n > 0 {
                right += 20.0;
                x += 20.0;
                if w < right {
                    right = 26.0;
                    x = ox;
                    y += 23.0;
                }
            }
            out.push(Prim::Icon { n, x, y });
        }
    }
    out
}

#[cfg(test)]
mod tests {
    use super::*;

    fn input(kind: Kind) -> Input {
        Input { kind, hp_visible: true, name_w: 52.0, letter: 0, model: 0, hp: 22, max_hp: 38, mp: 0, max_mp: 0, element: 6, icons: 0, phase: 0.0 }
    }

    #[test]
    fn plate_size_follows_the_packet() {
        // a short name: the minimum 96 x 50 (the fill spans 297..408, y 55..115; the live plate is 294..411 x 52..118 with the curls)
        assert_eq!(size(Kind::Party, 52.0, 0), (96.0, 50.0));
        // a long name widens it: the live `Revenant(1)` plate ends 23 px further out
        assert_eq!(size(Kind::Enemy, 75.0, 0).0, 117.0);
        // a photographed enemy: at least 168 x 72
        assert_eq!(size(Kind::Photo, 75.0, 0), (168.0, 72.0));
        // one status icon: +23 - 2 + 9 = 80
        assert_eq!(size(Kind::Enemy, 52.0, 1), (96.0, 80.0));
        // five icons overflow one row of a 96 wide plate (26 + 20 * 3 = 86 ok, the 5th at 106 > 96 wraps once)
        assert_eq!(size(Kind::Enemy, 52.0, 5).1, 50.0 + 23.0 + 23.0 - 2.0 + 9.0);
    }

    #[test]
    fn frame_pieces_hang_off_the_anchor() {
        let prims = layout(&input(Kind::Party));
        let Prim::Flat { pos, col } = prims[0] else { panic!() };
        assert_eq!(pos[0], (297.0, 55.0));
        assert_eq!(pos[3], (301.0 + 96.0 + 11.0, 60.0 + 50.0 + 5.0));
        assert_eq!(col[0], [0x41, 0x41, 0x4e, 0x4c]);
        assert_eq!(col[1], [0x0a, 0x08, 0x0a, 0x4c]);
        let sprites: Vec<_> = prims.iter().filter_map(|p| if let Prim::Sprite { tex: Tex::Btl(8), dst, .. } = p { Some(*dst) } else { None }).collect();
        assert_eq!(sprites.len(), 8);
        // top edge (P.x + 16, P.y - 10) .. (P.x + W - 8, P.y - 3)
        assert_eq!(sprites[0], (317.0, 50.0, 389.0, 57.0));
        // top-left curl (P.x - 14, P.y - 14) 31 x 33, top-right gem 34 x 49 at P.x + W - 10
        assert_eq!(sprites[4], (287.0, 46.0, 318.0, 79.0));
        assert_eq!(sprites[6], (387.0, 46.0, 421.0, 95.0));
    }

    #[test]
    fn card_gauge_and_label_positions() {
        let prims = layout(&input(Kind::Party));
        let caps: Vec<_> = prims.iter().filter_map(|p| if let Prim::Sprite { tex: Tex::Btl(19), dst, .. } = p { Some(*dst) } else { None }).collect();
        assert_eq!(caps, vec![(301.0, 60.0, 338.0, 110.0)]);
        let face = prims.iter().find_map(|p| if let Prim::Sprite { tex: Tex::Card(_), dst, .. } = p { Some(*dst) } else { None }).unwrap();
        assert_eq!(face, (302.0, 61.0, 338.0, 107.0));
        // HP track: x 336 / 339 / 401 / 404, y 99..107
        let Some(Prim::Strip { v, .. }) = prims.iter().find(|p| matches!(p, Prim::Strip { .. })) else { panic!() };
        assert_eq!((v[0].0, v[0].1), (336.0, 99.0));
        assert_eq!((v[7].0, v[7].1), (404.0, 107.0));
        // HP 22 / 38: fill 63 * 22 / 38 = 36.47 wide from x 338
        let fill = prims.iter().find_map(|p| if let Prim::Sprite { tex: Tex::Btl(3), dst, uv, .. } = p { Some((*dst, *uv)) } else { None }).unwrap();
        assert!((fill.0 .2 - (338.0 + 36.473686 + 1.0)).abs() < 1e-3, "{:?}", fill);
        assert_eq!(fill.1 .0, 2.0);
        // `HP` label (338, 87) 19 x 11, digits 359 + 8.8 k, 14 px tall from y 87 with the last digit at x 394.2
        let label = prims.iter().find_map(|p| if let Prim::Sprite { tex: Tex::Btl(2), uv, dst, .. } = p { if uv.0 == 1.0 { Some(*dst) } else { None } } else { None }).unwrap();
        assert_eq!(label, (338.0, 87.0, 357.0, 98.0));
        let digs: Vec<_> = prims.iter().filter_map(|p| if let Prim::Sprite { tex: Tex::Btl(2), uv, dst, .. } = p { if uv.0 > 70.0 { Some((uv.0, dst.0)) } else { None } } else { None }).collect();
        // 22: tens (col 3) and units (col 4)
        assert_eq!(digs.len(), 2);
        assert_eq!(digs[0], (digit_u(2), 359.0 + 8.8 * 3.0));
        assert_eq!(digs[1], (digit_u(2), 359.0 + 8.8 * 4.0));
    }

    #[test]
    fn enemy_hp_is_question_marks_until_photographed() {
        assert_eq!(digit_columns(17, Kind::Enemy), [Some(11); 5]);
        assert_eq!(digit_columns(17, Kind::Photo), [None, None, None, Some(1), Some(7)]);
        assert_eq!(digit_columns(0, Kind::Party), [None, None, None, None, Some(0)]);
        assert_eq!(digit_columns(12345, Kind::Party), [Some(1), Some(2), Some(3), Some(4), Some(5)]);
        assert_eq!(digit_u(0), 77.0);
        assert_eq!(digit_u(11), 198.0);
    }

    #[test]
    fn digit_colours_follow_the_thresholds() {
        let white = [0x80; 4];
        assert_eq!(digit_colour(38, 38), white);
        assert_eq!(digit_colour(20, 38), white);
        assert_eq!(digit_colour(19, 38), [0x80, 0x80, 0, 0x80]); // <= half
        assert_eq!(digit_colour(10, 38), [0x80, 0x80, 0, 0x80]);
        assert_eq!(digit_colour(9, 38), [0x80, 0, 0, 0x80]); // 38 >> 2 = 9
        assert_eq!(digit_colour(0, 38), [0x80, 0, 0, 0x80]);
        // max 3: half 2, quarter 1
        assert_eq!(digit_colour(2, 3), [0x80, 0x80, 0, 0x80]);
        assert_eq!(digit_colour(1, 3), [0x80, 0, 0, 0x80]);
    }

    #[test]
    fn gauge_fill_is_hidden_at_zero() {
        assert_eq!(gauge_width(0, 38), 0.0);
        assert_eq!(gauge_width(38, 38), 63.0);
        let mut i = input(Kind::Party);
        i.hp = 0;
        let prims = layout(&i);
        assert!(!prims.iter().any(|p| matches!(p, Prim::Sprite { tex: Tex::Btl(3), .. })));
    }

    #[test]
    fn photographed_plate_has_mp_row_ring_element_and_camera() {
        let mut i = input(Kind::Photo);
        i.name_w = 75.0;
        i.mp = 0;
        i.max_mp = 10;
        i.element = 5;
        let prims = layout(&i);
        let camera = prims.iter().find_map(|p| if let Prim::Sprite { tex: Tex::Btl(13), dst, .. } = p { Some(*dst) } else { None }).unwrap();
        assert_eq!(camera, (450.0, 85.0, 477.0, 127.0));
        let ring: Vec<_> = prims.iter().filter_map(|p| if let Prim::Sprite { tex: Tex::Btl(12), dst, .. } = p { Some(*dst) } else { None }).collect();
        assert_eq!(ring, vec![(408.0, 84.0, 448.0, 126.0); 2]);
        let elem = prims.iter().find_map(|p| if let Prim::Sprite { tex: Tex::Btl(11), uv, dst, .. } = p { Some((*uv, *dst)) } else { None }).unwrap();
        assert_eq!(elem.0, (110.0, 0.0, 132.0, 25.0));
        assert_eq!(elem.1, (417.0, 93.5, 439.0, 118.5));
        // MP label at y 108, MP gauge track at y 121
        let tracks: Vec<f32> = prims.iter().filter_map(|p| if let Prim::Strip { v, .. } = p { Some(v[0].1) } else { None }).collect();
        assert_eq!(tracks, vec![99.0, 121.0]);
        // MP 0: red digit 0
        let mp_digit = prims.iter().find_map(|p| if let Prim::Sprite { tex: Tex::Btl(2), uv, dst, rgba } = p { if uv.0 > 70.0 && dst.1 == 108.0 { Some(*rgba) } else { None } } else { None }).unwrap();
        assert_eq!(mp_digit, [0x80, 0, 0, 0x80]);
    }

    #[test]
    fn status_icons_get_a_separator_and_wrap() {
        let mut i = input(Kind::Party);
        i.icons = 2;
        let prims = layout(&i);
        let flats = prims.iter().filter(|p| matches!(p, Prim::Flat { .. })).count();
        assert_eq!(flats, 1 + 3, "fill + the three separator pieces");
        let icons: Vec<(f32, f32)> = prims.iter().filter_map(|p| if let Prim::Icon { x, y, .. } = p { Some((*x, *y)) } else { None }).collect();
        assert_eq!(icons, vec![(309.0, 120.0), (329.0, 120.0)]);
        // separator ramps: W 96 -> (96 + 13) / 3 = 36
        let sep = prims.iter().filter_map(|p| if let Prim::Flat { pos, col } = p { Some((pos[0], pos[2], col[0][3], col[2][3])) } else { None }).nth(1).unwrap();
        assert_eq!(sep, ((298.0, 112.0), (334.0, 112.0), 0, 0x80));
        // 5 icons on a 96 wide plate: the fifth wraps to the next row
        i.icons = 5;
        let prims = layout(&i);
        let icons: Vec<(f32, f32)> = prims.iter().filter_map(|p| if let Prim::Icon { x, y, .. } = p { Some((*x, *y)) } else { None }).collect();
        assert_eq!(icons[3], (369.0, 120.0));
        assert_eq!(icons[4], (309.0, 143.0));
    }

    #[test]
    fn pulse_phase_wraps_at_pi() {
        let mut p = 0.0;
        for _ in 0..200 {
            p = poll_phase(p, 1.0 / 60.0);
            assert!((-PI..PI).contains(&p));
        }
        assert!(poll_phase(PI - 0.001, 1.0 / 60.0) < 0.0);
    }
}
