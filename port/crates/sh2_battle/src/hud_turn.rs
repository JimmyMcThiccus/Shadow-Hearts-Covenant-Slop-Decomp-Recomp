//! `TurnOrderDisp` (the "Turn Priority" plate, top left): the retail object, function by function.
//!
//! Retail (`SLUS_210.41` + `BATTLE.BIN` overlay, JP demo addresses in brackets):
//! * `TurnOrderDisp::__ct`          0x50ce90 [0x4ea280]  -- hidden (`y = -128`), scale 1, phase 0
//! * `TurnOrderDisp::Polling`       0x50d190 [0x4ea5a0]  -- [`TurnOrderDisp::poll`]
//! * `TurnOrderDisp::MakePacket`    0x50d4f0 [0x4ea940]  -- [`TurnOrderDisp::layout`] (the GIF packet's geometry as [`Prim`]s)
//! * `TurnOrderDisp::TurnOrderOpen` 0x5119d0 [0x4f0af0]  -- [`TurnOrderDisp::open`]
//! * `TurnOrderDisp::TurnOrderClose`0x511a20 [0x4f0b40]  -- [`TurnOrderDisp::close`]
//! * `TurnOrderDisp::SetSelectChr`  0x511a60 [0x4f0b80]  -- [`TurnOrderDisp::set_select_chr`]
//!
//! Object lifetime: `__dt` 0x50d020 [0x4ea430], `Destruct` 0x50d140 [0x4ea550] (`Dispose` from the poller) and `getPacket` 0x57dff0 [0x54b350] (= `MakePacket`)
//! are the owner's `Option` / the per-frame [`TurnOrderDisp::layout`] call here.
//!
//! Object fields (retail offsets): `+0x38` state (0 hidden / 1 opening / 2 open / 3 closing), `+0x58` slide offset `y`, `+0x5c` select mask (two bits per
//! fighter: 1 = ally marker, 2 = enemy marker, 3 = special), `+0x60` target scale, `+0x64` scale, `+0x68` phase.
//! All coordinates are the 512 x 448 virtual screen (the GS packet adds the offsets 1792 / 1824, i.e. screen = packet - centre).  The packet truncates
//! `y + c * s` / `c * s` to integers before building the rectangles; [`fl`] reproduces that.
//!
//! Draw order of the packet: emblem (`BTL_000` entry 20), the glow quad (entry 21 orange / 22 cyan), nine capsules (entry 19 region (0,0)-(37,50)),
//! the actor's big face / letter, nine card faces, nine outlines (entry 19 region (37,0)-(70,46)), then the entry 18 group: title, zigzag, rail
//! (+ tail) and nine rail pips.

/// `BTL_000` entry numbers the packet draws from (retail `CBattle + 0x4484 + 4 * k`).
pub const T_TITLE: u8 = 18;
pub const T_CARDS: u8 = 19;
pub const T_EMBLEM: u8 = 20;
pub const T_ORANGE: u8 = 21;
pub const T_CYAN: u8 = 22;
pub const T_BIGLETTERS: u8 = 23;
pub const T_LETTERS: u8 = 24;

/// Texture sizes of the entries above (the packet reads them from the `JRCTex` header: `+2` width, `+4` height).
pub const EMBLEM_SIZE: (f32, f32) = (92.0, 112.0);
pub const GLOW_SIZE: (f32, f32) = (36.0, 60.0);
pub const TITLE_W: f32 = 100.0;

/// `TurnOrderOpen` starts the plate at `-96 * scale`; it is hidden once `y <= -128 * scale`.
pub const OPEN_FROM: f32 = -96.0;
pub const HIDDEN_AT: f32 = -128.0;
/// Scale while a target is chosen (live captures `04e` .. `04n`: title ink 51 px against 63 at scale 1 -> 0.8; the cards then sit at a pitch of 20).
pub const TARGET_SCALE: f32 = 0.8;
/// Frame time the object's `Polling` is written for (`CBattle + 0x38`, seconds).
pub const DT: f32 = 1.0 / 60.0;

/// `(int)(value)` of the packet (the values are positive once the GS offset is added, so this is a floor).
#[inline]
pub fn fl(v: f32) -> f32 {
    v.floor()
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Slide {
    /// `+0x38 == 0`: nothing moves (hidden, unless `y` was left open by `Default`)
    Idle,
    Opening,
    Open,
    Closing,
}

#[derive(Clone, Copy, Debug)]
pub struct TurnOrderDisp {
    pub state: Slide,
    /// `+0x58`
    pub y: f32,
    /// `+0x64`
    pub scale: f32,
    /// `+0x60`
    pub target_scale: f32,
    /// `+0x68`, in `[-pi, pi)`
    pub phase: f32,
    /// `+0x5c`
    pub select: u32,
}

impl Default for TurnOrderDisp {
    /// An open plate (used where nobody drives the slide: dev demos, tests).
    fn default() -> Self {
        TurnOrderDisp { state: Slide::Open, y: 0.0, scale: 1.0, target_scale: 1.0, phase: 0.0, select: 0 }
    }
}

impl TurnOrderDisp {
    /// `__ct`: hidden above the screen.
    pub fn new() -> Self {
        TurnOrderDisp { state: Slide::Idle, y: HIDDEN_AT, ..Default::default() }
    }

    /// `TurnOrderOpen`
    pub fn open(&mut self) {
        self.state = Slide::Opening;
        self.y = self.scale * OPEN_FROM;
    }

    /// `TurnOrderClose`
    pub fn close(&mut self) {
        self.state = Slide::Closing;
        self.y = 0.0;
    }

    /// `SetSelectChr(chr, mode)`: replaces the two bits of `chr`.
    pub fn set_select_chr(&mut self, chr: usize, mode: u32) {
        let sh = ((chr & 0xf) << 1) as u32;
        self.select = (self.select & !(3 << sh)) | (mode << sh);
    }

    /// the `+100 = 0` stores of `BtlMenu`: forget every marker.
    pub fn clear_select(&mut self) {
        self.select = 0;
    }

    pub fn select_of(&self, chr: usize) -> u32 {
        (self.select >> (((chr & 0xf) << 1) as u32)) & 3
    }

    /// `MakePacket` draws nothing once the plate has slid fully out.
    pub fn hidden(&self) -> bool {
        self.y <= self.scale * HIDDEN_AT
    }

    /// The `CBattle` rule: `TurnOrderOpen` only from state 0 (when it has been closed), `TurnOrderClose` only from state 2.
    pub fn want_open(&mut self, want: bool) {
        match (want, self.state) {
            (true, Slide::Idle) => self.open(),
            (false, Slide::Open) => self.close(),
            _ => {}
        }
    }

    /// `Polling`, one frame of `dt` seconds (the retail frame time is 1/60).
    pub fn poll(&mut self, dt: f32) {
        // phase: 2 turns per second, kept in [-pi, pi)
        self.phase += dt * std::f32::consts::TAU * 2.0;
        if self.phase >= std::f32::consts::PI {
            self.phase -= std::f32::consts::TAU;
        }
        // the scale approaches its target by at most 2 * dt per frame
        if self.scale < self.target_scale {
            let d = (self.target_scale - self.scale).min(dt * 2.0);
            self.scale += d;
        } else if self.target_scale < self.scale {
            let d = (self.target_scale - self.scale).max(-dt * 2.0);
            self.scale += d;
        }
        match self.state {
            Slide::Closing => {
                self.y -= (self.scale * 128.0 / 8.0) * dt * 60.0;
                if self.y <= self.scale * -128.0 {
                    self.state = Slide::Idle;
                    self.y = self.scale * -128.0;
                }
            }
            Slide::Opening => {
                self.y += (self.scale * 128.0 / 8.0) * dt * 60.0;
                if self.y >= 0.0 {
                    self.state = Slide::Open;
                    self.y = 0.0;
                }
            }
            _ => {}
        }
    }

    /// Frame helper for the port: run the retail frames that passed since the last call.
    pub fn poll_frames(&mut self, frames: u32) {
        for _ in 0..frames.min(12) {
            self.poll(DT);
        }
    }

    /// The plate's own scale target for the current page (the target pages shrink it, `04e` .. `04n`).
    pub fn set_target_page(&mut self, target_page: bool) {
        self.target_scale = if target_page { TARGET_SCALE } else { 1.0 };
    }
}

/// A texel rectangle drawn 1:1 into a screen rectangle (sprite) or a four vertex strip (glow).
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Tex {
    /// `BTL_000` entry
    Btl(u8),
    /// the acting party member's portrait (the port draws `FI_<model>`)
    Face(u32),
    /// a party member's card portrait (the port draws `FI_<model>` into the card)
    CardFace(u32),
}

/// Colour as the GS packet stores it (`RGBAQ`, 0x80 = 1.0).
pub type Rgba8 = [u8; 4];

#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Sprite {
    pub tex: Tex,
    /// source rectangle `(u0, v0, u1, v1)` in texels
    pub uv: (f32, f32, f32, f32),
    /// destination `(x0, y0, x1, y1)` in virtual pixels
    pub dst: (f32, f32, f32, f32),
    pub rgba: Rgba8,
}

/// A textured four vertex strip (top-left, bottom-left, top-right, bottom-right).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Strip {
    pub tex: Tex,
    pub uv: [(f32, f32); 4],
    pub pos: [(f32, f32); 4],
    pub rgba: Rgba8,
}

#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Prim {
    Sprite(Sprite),
    Strip(Strip),
}

/// Appearance of a card / of the acting member's face from the fighter's state (`MakePacket` colour rules).
#[derive(Clone, Copy, Debug, PartialEq, Eq, Default)]
pub enum Tint {
    #[default]
    Normal,
    /// a party member whose SP is 0 (berserk): `0x802020a0`
    Berserk,
    /// knocked out / loses its turns: `0x80189696`
    Down,
}

impl Tint {
    /// RGB (0x80 = 1.0) of the packet.
    pub fn rgb(self) -> [u8; 3] {
        match self {
            Tint::Normal => [0x80, 0x80, 0x80],
            Tint::Berserk => [0xa0, 0x20, 0x20],
            Tint::Down => [0x96, 0x96, 0x18],
        }
    }
}

#[derive(Clone, Copy, Debug, Default)]
pub struct Card {
    pub enemy: bool,
    /// enemy letter 0 = A .. 7 = H (`BtlChr + 0x120`)
    pub letter: u8,
    /// portrait model number for a party member
    pub model: u32,
    /// fighter index (select mask / actor test)
    pub chr: usize,
    pub tint: Tint,
}

#[derive(Clone, Copy, Debug, Default)]
pub struct Actor {
    pub enemy: bool,
    pub letter: u8,
    pub model: u32,
    pub chr: usize,
    pub tint: Tint,
}

pub struct Input<'a> {
    pub actor: Actor,
    /// turn table slots 1..9
    pub cards: &'a [Card],
    /// `CBattle + 0x32` (`wTurnPendMask`, the Combo members still to act): bit per fighter
    pub pending: u32,
}

/// Outline colour of a select mask value (`MakePacket`: 3 / 2 / 1).
pub fn outline_rgba(mask: u32) -> Option<Rgba8> {
    match mask {
        3 => Some([0x7d, 0x5a, 0x01, 0x80]),
        2 => Some([0x80, 0x00, 0x00, 0x80]),
        1 => Some([0x01, 0x7d, 0x5a, 0x80]),
        _ => None,
    }
}

/// The slots (1..9) whose card gets a rail pip: pending Combo members other than the actor, each fighter once (`uVar17` of `MakePacket`).
pub fn pip_slots(cards: &[Card], actor_chr: usize, pending: u32) -> u32 {
    let mut slots = 0u32;
    let mut seen = 0u32;
    for (i, c) in cards.iter().take(9).enumerate() {
        let k = i as u32 + 1;
        let bit = 1u32 << (c.chr as u32 & 31);
        if pending & bit != 0 && c.chr != actor_chr && seen & bit == 0 {
            slots |= 1 << k;
            seen |= bit;
        }
    }
    slots
}

/// x of the nine card slots: `x_0 = (int)(84 s)`, `x_{k+1} = (int)(x_k + 26 s)` (the packet truncates every step, so the pitch at 0.8 is 20).
pub fn slot_xs(s: f32) -> [f32; 9] {
    let mut out = [0.0; 9];
    let mut x = fl(84.0 * s);
    for o in out.iter_mut() {
        *o = x;
        x = fl(x + 26.0 * s);
    }
    out
}

impl TurnOrderDisp {
    /// `MakePacket`: everything the plate draws, in packet order.
    pub fn layout(&self, inp: &Input) -> Vec<Prim> {
        let mut out = Vec::with_capacity(48);
        if self.hidden() {
            return out;
        }
        let (s, y) = (self.scale, self.y);
        let white: Rgba8 = [0x80, 0x80, 0x80, 0x80];
        let sprite = |tex: Tex, uv: (f32, f32, f32, f32), dst: (f32, f32, f32, f32), rgba: Rgba8| Prim::Sprite(Sprite { tex, uv, dst, rgba });

        // 1. emblem at (14 s, 11 s)
        let (ex, ey) = (fl(14.0 * s), fl(y + 11.0 * s));
        out.push(sprite(Tex::Btl(T_EMBLEM), (0.0, 0.0, EMBLEM_SIZE.0, EMBLEM_SIZE.1), (ex, ey, ex + EMBLEM_SIZE.0 * s, ey + EMBLEM_SIZE.1 * s), white));

        // 2. glow quad at (31 s, 38 s): orange behind an acting enemy, cyan (rotated 30 degrees, pulsing 1 .. 1.5) when the actor is itself marked
        let (gx, gy) = (fl(31.0 * s), fl(y + 38.0 * s));
        let (gw, gh) = (GLOW_SIZE.0, GLOW_SIZE.1);
        let uv = [(0.0, 0.0), (0.0, gh - 0.5), (gw - 0.5, 0.0), (gw - 0.5, gh - 0.5)];
        if self.select_of(inp.actor.chr) == 0 {
            if inp.actor.enemy {
                let pos = [(gx, gy), (gx, gy + gh * s), (gx + gw * s, gy), (gx + gw * s, gy + gh * s)];
                out.push(Prim::Strip(Strip { tex: Tex::Btl(T_ORANGE), uv, pos, rgba: white }));
            }
        } else {
            let (hw, hh) = (fl(gw * s / 2.0), fl(gh * s / 2.0));
            let k = self.phase.sin() * 0.25 + 1.25;
            let rot = 0.5236_f32;
            let (sn, cs) = rot.sin_cos();
            let corner = |sx: f32, sy: f32| {
                let (px, py) = (sx * hw * k, sy * hh * k);
                (px * cs - py * sn + gx + hw, px * sn + py * cs + gy + hh)
            };
            out.push(Prim::Strip(Strip { tex: Tex::Btl(T_CYAN), uv, pos: [corner(-1.0, -1.0), corner(-1.0, 1.0), corner(1.0, -1.0), corner(1.0, 1.0)], rgba: white }));
        }

        // 3. nine capsules (entry 19, texels (0,0)-(37,50)) from (x - s, y - s) to (x + 36 s, y + 49 s)
        let xs = slot_xs(s);
        let cy = fl(y + 40.0 * s);
        for &x in &xs {
            out.push(sprite(Tex::Btl(T_CARDS), (0.0, 0.0, 37.0, 50.0), (x - s, cy - s, x + 36.0 * s, cy + 49.0 * s), white));
        }

        // 4. the actor: a party member's portrait at (21 s, 28 s), an enemy's big letter (entry 23, 36 x 48 cells, 2 columns) at (33 s, 41 s)
        let tint = inp.actor.tint.rgb();
        let rgba = [tint[0], tint[1], tint[2], 0x80];
        if inp.actor.enemy {
            let (col, row) = ((inp.actor.letter / 4) as f32 * 36.0, (inp.actor.letter % 4) as f32 * 48.0);
            let (lx, ly) = (fl(33.0 * s), fl(y + 41.0 * s));
            out.push(sprite(Tex::Btl(T_BIGLETTERS), (col, row, col + 36.0, row + 48.0), (lx, ly, lx + 36.0 * s, ly + 48.0 * s), rgba));
        } else {
            let (px, py) = (fl(21.0 * s), fl(y + 28.0 * s));
            out.push(sprite(Tex::Face(inp.actor.model), (0.0, 0.0, 52.0, 64.0), (px, py, px + 52.0 * s, py + 64.0 * s), rgba));
        }

        // 5. nine card faces at (x_k, y) (letters 36 x 46 of entry 24, two columns of four rows; a party card is the portrait texture 1:1)
        for (i, &x) in xs.iter().enumerate() {
            let Some(c) = inp.cards.get(i) else { continue };
            let marked = self.select_of(c.chr) != 0 || c.chr == inp.actor.chr;
            let t = c.tint.rgb();
            let rgba = [t[0], t[1], t[2], if marked { 0x80 } else { 0x40 }];
            if c.enemy {
                let (col, row) = ((c.letter / 4) as f32 * 36.0, (c.letter % 4) as f32 * 46.0);
                out.push(sprite(Tex::Btl(T_LETTERS), (col, row, col + 36.0, row + 46.0), (x, cy, x + 36.0 * s, cy + 46.0 * s), rgba));
            } else {
                out.push(sprite(Tex::CardFace(c.model), (0.0, 0.0, 36.0, 46.0), (x, cy, x + 36.0 * s, cy + 46.0 * s), rgba));
            }
        }

        // 6. outlines (entry 19, texels (37,0)-(70,46)) of the marked fighters, 33 x 46 at (x_k, y)
        for (i, &x) in xs.iter().enumerate() {
            let Some(c) = inp.cards.get(i) else { continue };
            if let Some(rgba) = outline_rgba(self.select_of(c.chr)) {
                out.push(sprite(Tex::Btl(T_CARDS), (37.0, 0.0, 70.0, 46.0), (x, cy, x + 33.0 * s, cy + 46.0 * s), rgba));
            }
        }

        // 7. entry 18: title (100 x 18), zigzag (40 x 32), the rail (with partners: 80.5..96 stretched to the last pip + 61.5..76 tail), nine pips
        out.push(sprite(Tex::Btl(T_TITLE), (0.0, 0.0, TITLE_W, 18.0), (fl(79.0 * s), fl(y + 25.0 * s), fl(79.0 * s) + TITLE_W * s, fl(y + 25.0 * s) + 18.0 * s), white));
        let zy = fl(y + 75.0 * s);
        let zx = fl(52.0 * s);
        out.push(sprite(Tex::Btl(T_TITLE), (0.0, 18.0, 40.0, 50.0), (zx, zy, zx + 40.0 * s, zy + 32.0 * s), white));
        let pips = pip_slots(inp.cards, inp.actor.chr, inp.pending);
        let rx = fl(92.0 * s);
        let mut tail_x = rx;
        if pips != 0 {
            let last = (1..=9u32).rev().find(|k| pips & (1 << k) != 0).unwrap_or(1);
            let w = (((last as f32 - 1.0) * 26.0 + 17.0 - 4.0) * s).trunc();
            out.push(sprite(Tex::Btl(T_TITLE), (80.5, 18.0, 96.0, 50.0), (rx, zy, rx + w, zy + 32.0 * s), white));
            tail_x = fl(92.0 * s + w);
        }
        out.push(sprite(Tex::Btl(T_TITLE), (61.5, 18.0, 76.0, 50.0), (tail_x, zy, tail_x + 16.0 * s, zy + 32.0 * s), white));
        let mut px = fl(88.0 * s);
        for k in 1..=9u32 {
            if pips & (1 << k) != 0 {
                out.push(sprite(Tex::Btl(T_TITLE), (42.0, 18.0, 59.0, 50.0), (px, zy, px + 17.0 * s, zy + 32.0 * s), white));
            }
            px = fl(px + 26.0 * s);
        }
        out
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn cards(n: usize) -> Vec<Card> {
        (0..n).map(|i| Card { enemy: i % 2 == 0, letter: (i % 8) as u8, model: 5, chr: i + 1, tint: Tint::Normal }).collect()
    }

    fn actor(chr: usize, enemy: bool) -> Actor {
        Actor { enemy, letter: 0, model: 5, chr, tint: Tint::Normal }
    }

    #[test]
    fn card_slots_truncate_every_step() {
        // scale 1: 84, 110, 136 ...
        let xs = slot_xs(1.0);
        assert_eq!(xs[0], 84.0);
        assert_eq!(xs[1], 110.0);
        assert_eq!(xs[8], 84.0 + 8.0 * 26.0);
        // scale 0.8 (target pages): 67.2 -> 67, 87.8 -> 87, 107.8 -> 107: a pitch of exactly 20
        let xs = slot_xs(0.8);
        assert_eq!(&xs[..3], &[67.0, 87.0, 107.0]);
        assert_eq!(xs[8] - xs[0], 160.0);
    }

    #[test]
    fn opening_takes_six_frames_and_closing_eight() {
        let mut t = TurnOrderDisp::new();
        assert!(t.hidden());
        t.want_open(true);
        assert_eq!(t.y, -96.0);
        let mut n = 0;
        while t.state == Slide::Opening {
            t.poll(DT);
            n += 1;
        }
        assert_eq!((n, t.state, t.y), (6, Slide::Open, 0.0));
        // closing is ignored unless the plate is open; then 16 px per frame up to -128
        t.want_open(false);
        assert_eq!(t.state, Slide::Closing);
        let mut n = 0;
        while t.state == Slide::Closing {
            t.poll(DT);
            n += 1;
        }
        assert_eq!((n, t.y), (8, -128.0));
        assert!(t.hidden());
        assert!(t.layout(&Input { actor: actor(0, false), cards: &cards(9), pending: 0 }).is_empty());
        // asking to open while closing does nothing (CBattle only calls TurnOrderOpen from state 0)
        t.state = Slide::Closing;
        t.want_open(true);
        assert_eq!(t.state, Slide::Closing);
    }

    #[test]
    fn scale_follows_its_target_at_two_dt_per_frame() {
        let mut t = TurnOrderDisp::default();
        t.set_target_page(true);
        let mut n = 0;
        while (t.scale - TARGET_SCALE).abs() > 1e-4 {
            t.poll(DT);
            n += 1;
            assert!(n < 20);
        }
        assert!((6..=7).contains(&n), "{n}");
        t.set_target_page(false);
        t.poll_frames(8);
        assert!((t.scale - 1.0).abs() < 1e-4);
    }

    #[test]
    fn phase_turns_twice_per_second_inside_minus_pi_pi() {
        let mut t = TurnOrderDisp::default();
        for _ in 0..30 {
            t.poll(DT);
            assert!(t.phase >= -std::f32::consts::PI && t.phase < std::f32::consts::PI);
        }
        // 30 frames = 0.5 s = one full turn
        assert!(t.phase.abs() < 1e-3 || (t.phase.abs() - std::f32::consts::TAU).abs() < 1e-3, "{}", t.phase);
    }

    #[test]
    fn select_chr_replaces_two_bits() {
        let mut t = TurnOrderDisp::default();
        t.set_select_chr(3, 2);
        t.set_select_chr(5, 1);
        assert_eq!((t.select_of(3), t.select_of(5), t.select_of(4)), (2, 1, 0));
        t.set_select_chr(3, 1);
        assert_eq!(t.select_of(3), 1);
        t.set_select_chr(3, 0);
        assert_eq!(t.select_of(3), 0);
        t.clear_select();
        assert_eq!(t.select, 0);
    }

    #[test]
    fn capsules_and_cards_follow_the_packet() {
        let t = TurnOrderDisp::default();
        let cs = cards(9);
        let prims = t.layout(&Input { actor: actor(0, false), cards: &cs, pending: 0 });
        // emblem, 9 capsules, actor face, 9 faces, title, zigzag, tail
        assert_eq!(prims.len(), 1 + 9 + 1 + 9 + 3);
        let Prim::Sprite(emblem) = prims[0] else { panic!() };
        assert_eq!(emblem.dst, (14.0, 11.0, 106.0, 123.0));
        let Prim::Sprite(cap0) = prims[1] else { panic!() };
        // (84 - 1, 40 - 1) .. (84 + 36, 40 + 49)
        assert_eq!(cap0.dst, (83.0, 39.0, 120.0, 89.0));
        assert_eq!(cap0.uv, (0.0, 0.0, 37.0, 50.0));
        let Prim::Sprite(face0) = prims[11] else { panic!() };
        assert_eq!(face0.tex, Tex::Btl(T_LETTERS));
        assert_eq!(face0.dst, (84.0, 40.0, 120.0, 86.0));
        // an unmarked card is drawn at half alpha, the actor's other turn at full alpha
        assert_eq!(face0.rgba[3], 0x40);
        let prims = t.layout(&Input { actor: actor(1, false), cards: &cs, pending: 0 });
        let Prim::Sprite(face0) = prims[11] else { panic!() };
        assert_eq!(face0.rgba[3], 0x80, "chr 1 is the actor");
    }

    #[test]
    fn slide_offsets_every_rectangle() {
        let mut t = TurnOrderDisp::default();
        t.y = -48.0;
        let cs = cards(2);
        let prims = t.layout(&Input { actor: actor(0, false), cards: &cs, pending: 0 });
        let Prim::Sprite(emblem) = prims[0] else { panic!() };
        assert_eq!(emblem.dst.1, -48.0 + 11.0);
    }

    #[test]
    fn enemy_actor_gets_the_orange_glow_and_the_big_letter() {
        let t = TurnOrderDisp::default();
        let a = Actor { enemy: true, letter: 5, model: 0, chr: 4, tint: Tint::Normal };
        let prims = t.layout(&Input { actor: a, cards: &cards(3), pending: 0 });
        let Prim::Strip(g) = prims[1] else { panic!("glow strip first") };
        assert_eq!(g.tex, Tex::Btl(T_ORANGE));
        assert_eq!(g.pos[0], (31.0, 38.0));
        assert_eq!(g.pos[3], (67.0, 98.0));
        // actor face after the 9 capsules: letter F = column 1, row 1
        let Prim::Sprite(l) = prims[11] else { panic!() };
        assert_eq!(l.tex, Tex::Btl(T_BIGLETTERS));
        assert_eq!(l.uv, (36.0, 48.0, 72.0, 96.0));
        assert_eq!(l.dst, (33.0, 41.0, 69.0, 89.0));
    }

    #[test]
    fn marked_actor_gets_the_cyan_glow_pulsing_about_its_centre() {
        let mut t = TurnOrderDisp::default();
        t.set_select_chr(0, 1);
        let a = actor(0, false);
        let prims = t.layout(&Input { actor: a, cards: &cards(1), pending: 0 });
        let Prim::Strip(g) = prims[1] else { panic!() };
        assert_eq!(g.tex, Tex::Btl(T_CYAN));
        // centre of the four corners = (31 + 18, 38 + 30)
        let cx = g.pos.iter().map(|p| p.0).sum::<f32>() / 4.0;
        let cy = g.pos.iter().map(|p| p.1).sum::<f32>() / 4.0;
        assert!((cx - 49.0).abs() < 1e-3 && (cy - 68.0).abs() < 1e-3, "{cx} {cy}");
        // phase 0: factor 1.25
        let d = ((g.pos[3].0 - g.pos[0].0).powi(2) + (g.pos[3].1 - g.pos[0].1).powi(2)).sqrt();
        let want = ((36.0f32 * 1.25).powi(2) + (60.0f32 * 1.25).powi(2)).sqrt();
        assert!((d - want).abs() < 0.1, "{d} {want}");
    }

    #[test]
    fn outlines_follow_the_select_mask() {
        let mut t = TurnOrderDisp::default();
        let cs = cards(4);
        t.set_select_chr(2, 2); // card 1 (chr 2): enemy marker
        t.set_select_chr(4, 1); // card 3 (chr 4): ally marker
        let prims = t.layout(&Input { actor: actor(0, false), cards: &cs, pending: 0 });
        let outlines: Vec<Sprite> = prims.iter().filter_map(|p| if let Prim::Sprite(s) = p { Some(*s) } else { None }).filter(|s| s.uv == (37.0, 0.0, 70.0, 46.0)).collect();
        assert_eq!(outlines.len(), 2);
        assert_eq!(outlines[0].rgba, [0x80, 0, 0, 0x80]);
        assert_eq!(outlines[0].dst, (110.0, 40.0, 143.0, 86.0));
        assert_eq!(outlines[1].rgba, [0x01, 0x7d, 0x5a, 0x80]);
        assert_eq!(outline_rgba(3), Some([0x7d, 0x5a, 0x01, 0x80]));
        assert_eq!(outline_rgba(0), None);
        // marked cards are drawn at full alpha
        let faces: Vec<Sprite> = prims.iter().filter_map(|p| if let Prim::Sprite(s) = p { Some(*s) } else { None }).filter(|s| matches!(s.tex, Tex::CardFace(_)) || s.tex == Tex::Btl(T_LETTERS)).collect();
        assert_eq!(faces.iter().map(|f| f.rgba[3]).collect::<Vec<_>>(), vec![0x40, 0x80, 0x40, 0x80]);
    }

    #[test]
    fn combo_partners_extend_the_rail_and_mark_their_slots() {
        let t = TurnOrderDisp::default();
        let cs = cards(9);
        // fighters 3 and 6 (cards 3 and 6) still have to act in the combo; the actor is fighter 0; a repeated fighter only counts once
        let mut cs2 = cs.clone();
        cs2[7].chr = 3;
        let pending = (1 << 3) | (1 << 6);
        assert_eq!(pip_slots(&cs2, 0, pending), (1 << 3) | (1 << 6));
        let prims = t.layout(&Input { actor: actor(0, false), cards: &cs2, pending });
        let rail: Vec<Sprite> = prims.iter().filter_map(|p| if let Prim::Sprite(s) = p { Some(*s) } else { None }).filter(|s| s.tex == Tex::Btl(T_TITLE)).collect();
        // title, zigzag, rail, tail, 2 pips
        assert_eq!(rail.len(), 6);
        let seg = rail[2];
        assert_eq!(seg.uv, (80.5, 18.0, 96.0, 50.0));
        // last pip slot 6: ((6 - 1) * 26 + 17 - 4) = 143 px from x 92
        assert_eq!(seg.dst, (92.0, 75.0, 92.0 + 143.0, 107.0));
        assert_eq!(rail[3].uv, (61.5, 18.0, 76.0, 50.0));
        assert_eq!(rail[3].dst.0, 92.0 + 143.0);
        // pips under slots 3 and 6: x = 88 + 26 (k - 1)
        assert_eq!(rail[4].dst.0, 88.0 + 26.0 * 2.0);
        assert_eq!(rail[5].dst.0, 88.0 + 26.0 * 5.0);
        // nobody pending: only the short tail at x 92
        let prims = t.layout(&Input { actor: actor(0, false), cards: &cs, pending: 0 });
        let tail = prims.iter().filter_map(|p| if let Prim::Sprite(s) = p { Some(*s) } else { None }).filter(|s| s.uv == (61.5, 18.0, 76.0, 50.0)).collect::<Vec<_>>();
        assert_eq!(tail.len(), 1);
        assert_eq!(tail[0].dst.0, 92.0);
    }

    #[test]
    fn tints_follow_the_packet_colours() {
        assert_eq!(Tint::Berserk.rgb(), [0xa0, 0x20, 0x20]);
        assert_eq!(Tint::Down.rgb(), [0x96, 0x96, 0x18]);
        assert_eq!(Tint::Normal.rgb(), [0x80; 3]);
    }
}
