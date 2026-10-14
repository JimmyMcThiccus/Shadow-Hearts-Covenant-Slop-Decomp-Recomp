//! `MenuDataTable` / `.MSD` scene-file format (MENU.PKB: `MENU/MSD/*.MSD`, `MENU/DAT/*.MSD`,
//! `SAVELIST.MDT`).
//!
//! A scene file is a singly linked list of *chunks*. Every chunk is a table of fixed-stride records:
//!
//! ```text
//! +0x00 u16 type        (record kind, see [`ChunkType`])
//! +0x02 u8  ptr_count   (the first `ptr_count` u32 of every record are file-relative pointers)
//! +0x03 u8  -
//! +0x04 u16 -
//! +0x06 u16 stride      (bytes per record)
//! +0x08 u32 count       (records)
//! +0x0c u32 next        (byte distance to the next chunk, 0 = last)
//! +0x10 records[count]
//! ```
//! JP: 0x00283760 `Convert__13MenuDataTableFPUci` relocates the pointers in place (mode 0: relative to the
//! start of the file, mode 1: relative to the chunk — used by `MenuDataTable::Create` for `.MDT`).
//! JP: 0x002839f0 `Find__13MenuDataTableFs` walks the list for a type. `MenuScene::Initialize`
//! (0x00279570) indexes the chunks by type into `MenuScene+0x24 + type*4`.
//!
//! The record layouts below were read off `MenuScene::SetData(...)` (0x00279880..0x0027b070).

use thiserror::Error;

#[derive(Debug, Error)]
pub enum MsdError {
    #[error("truncated MSD data at {0:#x}")]
    Truncated(usize),
    #[error("chunk at {0:#x} has bad stride/count")]
    BadChunk(usize),
}

/// Record kinds (`MenuScene` table slots).
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum ChunkType {
    /// 0: resource name table `[ptr name][u16 arg][u16 flags]` (texture path templates etc.)
    Resource,
    /// 1: text table `[ptr text][ptr text_alt][i32 tag]`
    Text,
    /// 2: `FontDraw` canvas
    FontDraw,
    /// 3: `Cursor`
    Cursor,
    /// 4: `MenuWindow`
    Window,
    /// 5: `MenuGroup`
    Group,
    /// 6: `MenuSprite`
    Sprite,
    /// 7: `MenuPolygon`
    Polygon,
    /// 8: `MenuText`
    MenuText,
    /// 9: `MenuMessage`
    Message,
    /// 10: `MenuFont`
    Font,
    /// 11: `MenuFontItalic`
    FontItalic,
    /// 12: embedded attach files `[ptr data][i32 id][u32 size]`
    Attach,
    Other(u16),
}

impl From<u16> for ChunkType {
    fn from(v: u16) -> Self {
        use ChunkType::*;
        match v {
            0 => Resource, 1 => Text, 2 => FontDraw, 3 => Cursor, 4 => Window, 5 => Group,
            6 => Sprite, 7 => Polygon, 8 => MenuText, 9 => Message, 10 => Font, 11 => FontItalic,
            12 => Attach, o => Other(o),
        }
    }
}

/// Retail `CMDMENU.MSD` data-table chunk numbering: the demo's types 7..=26 (character profiles, weapon / armor / accessory / item
/// descriptions, help pages, library, ring texts ...) are numbered `+ 2` in the US file; types 0..=6 are unchanged.
pub fn us_mdt_type(demo: u16) -> u16 {
    match demo {
        7..=26 => demo + 2,
        // the combo-key tables (`MenuDataTable` keys 0x31 / 0x32 / 0x33) moved down by one
        49..=51 => demo - 1,
        _ => demo,
    }
}

#[derive(Debug, Clone)]
pub struct Chunk {
    pub offset: usize,
    pub kind: ChunkType,
    pub raw_type: u16,
    pub ptr_count: u8,
    pub stride: usize,
    pub count: usize,
    pub next: usize,
}

impl Chunk {
    pub fn record_offset(&self, i: usize) -> usize {
        self.offset + 0x10 + i * self.stride
    }
}

/// A parsed scene file. The raw bytes are kept; records are decoded on demand.
#[derive(Debug, Clone)]
pub struct Msd {
    pub data: Vec<u8>,
    pub chunks: Vec<Chunk>,
    /// `.MDT` chunk-type translation (demo type -> this file's type).  The retail `CMDMENU` data table renumbered its chunks
    /// (`type + 2` for 7..=26, `type - 1` for the combo-key tables 49..=51), so the callers written against the demo numbers keep working: see [`Msd::with_mdt_map`].
    pub mdt_map: Option<fn(u16) -> u16>,
}

fn u16_at(d: &[u8], o: usize) -> u16 {
    u16::from_le_bytes([d[o], d[o + 1]])
}
fn i16_at(d: &[u8], o: usize) -> i16 {
    u16_at(d, o) as i16
}
fn u32_at(d: &[u8], o: usize) -> u32 {
    u32::from_le_bytes([d[o], d[o + 1], d[o + 2], d[o + 3]])
}

impl Msd {
    pub fn parse(data: Vec<u8>) -> Result<Self, MsdError> {
        let mut chunks = Vec::new();
        let mut o = 0usize;
        loop {
            if o + 0x10 > data.len() {
                return Err(MsdError::Truncated(o));
            }
            let raw_type = u16_at(&data, o);
            let stride = u16_at(&data, o + 6) as usize;
            let count = u32_at(&data, o + 8) as usize;
            let next = u32_at(&data, o + 0xc) as usize;
            if o + 0x10 + stride * count > data.len() {
                return Err(MsdError::BadChunk(o));
            }
            chunks.push(Chunk { offset: o, kind: raw_type.into(), raw_type, ptr_count: data[o + 2], stride, count, next });
            if next == 0 {
                break;
            }
            o += next;
        }
        Ok(Msd { data, chunks, mdt_map: None })
    }

    /// JP: 0x002839f0 Find__13MenuDataTableFs
    pub fn find(&self, kind: ChunkType) -> Option<&Chunk> {
        self.chunks.iter().find(|c| c.kind == kind)
    }

    /// NUL terminated string at a file-relative pointer.
    pub fn cstr(&self, ptr: u32) -> &[u8] {
        let s = ptr as usize;
        if s >= self.data.len() {
            return &[];
        }
        let e = self.data[s..].iter().position(|&b| b == 0).map(|p| s + p).unwrap_or(self.data.len());
        &self.data[s..e]
    }

    fn rec(&self, kind: ChunkType, i: usize) -> Option<&[u8]> {
        let c = self.find(kind)?;
        if i >= c.count {
            return None;
        }
        let o = c.record_offset(i);
        Some(&self.data[o..o + c.stride])
    }

    pub fn count(&self, kind: ChunkType) -> usize {
        self.find(kind).map(|c| c.count).unwrap_or(0)
    }

    pub fn resource_name(&self, i: usize) -> Option<String> {
        let r = self.rec(ChunkType::Resource, i)?;
        Some(String::from_utf8_lossy(self.cstr(u32_at(r, 0))).into_owned())
    }

    /// Text table entry (raw Shift-JIS bytes).
    pub fn text(&self, i: usize) -> Option<&[u8]> {
        let r = self.rec(ChunkType::Text, i)?;
        Some(self.cstr(u32_at(r, 0)))
    }

    /// Text table entry as `(primary, alternate, tag)`: raw Shift-JIS bytes of both strings and the `i32` tag record field
    /// (`CmdTop`: the page id selected by the entry; negative = save / load).
    pub fn text_entry(&self, i: usize) -> Option<(&[u8], &[u8], i32)> {
        let r = self.rec(ChunkType::Text, i)?;
        Some((self.cstr(u32_at(r, 0)), self.cstr(u32_at(r, 4)), u32_at(r, 8) as i32))
    }

    /// Raw bytes of resource-table string `i` (the type-0 chunk holds help lines, format strings and file names).
    pub fn resource_bytes(&self, i: usize) -> Option<&[u8]> {
        let r = self.rec(ChunkType::Resource, i)?;
        Some(self.cstr(u32_at(r, 0)))
    }

    /// `[ptr][u16 a][u16 b]` fields of resource record `i`.
    pub fn resource_args(&self, i: usize) -> Option<(u16, u16)> {
        let r = self.rec(ChunkType::Resource, i)?;
        Some((u16_at(r, 4), u16_at(r, 6)))
    }

    /// Embedded attach file `i` (JP `FindAttachFile` by table position), as a slice of the scene data.
    pub fn attach_data(&self, i: usize) -> Option<&[u8]> {
        let a = self.attach_files().into_iter().nth(i)?;
        self.data.get(a.offset as usize..(a.offset + a.size) as usize)
    }

    /// Embedded attach file looked up by its record id (`MenuScene::FindAttachFile(short id)`: compares the low 16 bits).
    pub fn attach_by_id(&self, id: i16) -> Option<&[u8]> {
        let a = self.attach_files().into_iter().find(|a| a.id as i16 == id)?;
        self.data.get(a.offset as usize..(a.offset + a.size) as usize)
    }

    /// Parse attach file `i` as a nested scene.
    pub fn attach_scene(&self, i: usize) -> Option<Msd> {
        Msd::parse(self.attach_data(i)?.to_vec()).ok()
    }

    /// `.MDT` mode (`MenuDataTable::Convert(data, 1)`): chunk of raw type `ty`.
    pub fn find_raw(&self, ty: u16) -> Option<&Chunk> {
        let ty = self.mdt_map.map(|f| f(ty)).unwrap_or(ty);
        self.chunks.iter().find(|c| c.raw_type == ty)
    }

    /// The u16 at +4 of an MDT chunk header: the id of the first record (`CmdLibrary::FindNPC` adds it to the record index to get the
    /// `FieldNpcLibrary` id; people start at 13).
    pub fn mdt_base(&self, ty: u16) -> u16 {
        self.find_raw(ty).map(|c| u16_at(&self.data, c.offset + 4)).unwrap_or(0)
    }

    /// Install a chunk-type translation for the `mdt_*` accessors (retail: [`us_mdt_type`]).
    pub fn with_mdt_map(mut self, f: fn(u16) -> u16) -> Self {
        self.mdt_map = Some(f);
        self
    }

    pub fn mdt_count(&self, ty: u16) -> usize {
        self.find_raw(ty).map(|c| c.count).unwrap_or(0)
    }

    /// Raw bytes of record `i` of an MDT chunk (pointer words included).
    pub fn mdt_rec(&self, ty: u16, i: usize) -> Option<&[u8]> {
        let c = self.find_raw(ty)?;
        if i >= c.count {
            return None;
        }
        let o = c.record_offset(i);
        self.data.get(o..o + c.stride)
    }

    /// String of pointer field `k` of record `i` of MDT chunk `ty` (pointers are chunk relative).
    pub fn mdt_str(&self, ty: u16, i: usize, k: usize) -> &[u8] {
        let (Some(c), Some(r)) = (self.find_raw(ty), self.mdt_rec(ty, i)) else { return &[] };
        if k >= c.ptr_count as usize {
            return &[];
        }
        self.cstr(c.offset as u32 + u32_at(r, k * 4))
    }

    /// `n` bytes at pointer field `k` of record `i` (chunk relative), for pointers to binary arrays (the retail help categories point at
    /// a `u16` list of entry ids).
    pub fn mdt_ptr_bytes(&self, ty: u16, i: usize, k: usize, n: usize) -> &[u8] {
        let (Some(c), Some(r)) = (self.find_raw(ty), self.mdt_rec(ty, i)) else { return &[] };
        if k >= c.ptr_count as usize {
            return &[];
        }
        let o = c.offset + u32_at(r, k * 4) as usize;
        self.data.get(o..(o + n).min(self.data.len())).unwrap_or(&[])
    }

    /// Non-pointer bytes of an MDT record (after the pointer words).
    pub fn mdt_data(&self, ty: u16, i: usize) -> &[u8] {
        let (Some(c), Some(r)) = (self.find_raw(ty), self.mdt_rec(ty, i)) else { return &[] };
        &r[(c.ptr_count as usize * 4).min(r.len())..]
    }

    /// Position of `MenuFont` record `i` (chunk type 10: `+4 x, +6 y`, `+0xc` string index, `+0xe` font number).
    pub fn font_pos(&self, i: usize) -> Option<(f32, f32)> {
        let r = self.rec(ChunkType::Font, i)?;
        Some((i16_at(r, 4) as f32, i16_at(r, 6) as f32))
    }

    /// `(string index, font number)` of `MenuFont` record `i`.
    pub fn font_text(&self, i: usize) -> Option<(u16, u16)> {
        let r = self.rec(ChunkType::Font, i)?;
        Some((u16_at(r, 0xc), u16_at(r, 0xe)))
    }

    /// Position of `MenuFontItalic` record `i` (chunk type 11: `+8 x, +0xa y`).
    pub fn italic_pos(&self, i: usize) -> Option<(f32, f32)> {
        let r = self.rec(ChunkType::FontItalic, i)?;
        Some((i16_at(r, 8) as f32, i16_at(r, 0xa) as f32))
    }

    pub fn attach_files(&self) -> Vec<AttachRec> {
        let Some(c) = self.find(ChunkType::Attach) else { return vec![] };
        // an `.MDT` table whose chunk type collides with the attach id has 8-byte rows: not an attach list (QA round 5: no panic)
        if c.stride < 12 {
            return vec![];
        }
        (0..c.count)
            .map(|i| {
                let r = &self.data[c.record_offset(i)..c.record_offset(i) + c.stride];
                AttachRec { offset: u32_at(r, 0), id: u32_at(r, 4) as i32, size: u32_at(r, 8) }
            })
            .collect()
    }

    pub fn font_draw(&self, i: usize) -> Option<FontDrawRec> {
        let r = self.rec(ChunkType::FontDraw, i)?;
        Some(FontDrawRec { id: u16_at(r, 0), priority: i16_at(r, 2), psm: u16_at(r, 4), flags: u16_at(r, 6), width: u16_at(r, 8), height: u16_at(r, 0xa), clut: u32_at(r, 0xc) })
    }

    pub fn cursor(&self, i: usize) -> Option<CursorRec> {
        let r = self.rec(ChunkType::Cursor, i)?;
        let w8 = r[8];
        let w9 = r[9];
        Some(CursorRec {
            id: u16_at(r, 0),
            priority: i16_at(r, 2),
            width: i16_at(r, 4),
            height: i16_at(r, 6),
            kind: w8 & 7,
            shadow: (w8 >> 3) & 3,
            rotate: (w8 >> 5) & 1 != 0,
            direction: ((u16_at(r, 8) >> 6) & 0xf) as u8,
            skip_mode: (w9 >> 2) & 0xf,
            back_object: (w9 >> 6) & 1 != 0,
        })
    }

    pub fn window(&self, i: usize) -> Option<WindowRec> {
        let r = self.rec(ChunkType::Window, i)?;
        let f = u16_at(r, 0x18);
        let b19 = r[0x19];
        Some(WindowRec {
            id: u16_at(r, 0),
            priority: i16_at(r, 2),
            x: i16_at(r, 4) as f32,
            y: i16_at(r, 6) as f32,
            w: u16_at(r, 8) as f32,
            h: u16_at(r, 0xa) as f32,
            scroll_cols: i16_at(r, 0xc),
            scroll_rows: i16_at(r, 0xe),
            open_time: u32_at(r, 0x10),
            close_time: u32_at(r, 0x14),
            open_effect: (f & 7) as u8,
            close_effect: ((f >> 3) & 7) as u8,
            style: ((f >> 6) & 7) as u8,
            clip_mode: (b19 >> 1) & 3,
            wrap_h: (b19 >> 3) & 1 != 0,
            wrap_v: (b19 >> 4) & 1 != 0,
            scroll_enable: (b19 >> 6) & 1 != 0,
            scroll_mark_mask: r[0x1a],
        })
    }

    pub fn group(&self, i: usize) -> Option<GroupRec> {
        let r = self.rec(ChunkType::Group, i)?;
        Some(GroupRec {
            id: u16_at(r, 0),
            priority: i16_at(r, 2),
            x: i16_at(r, 4) as f32,
            y: i16_at(r, 6) as f32,
            col: i16_at(r, 8),
            row: i16_at(r, 0xa),
            w: i16_at(r, 0xc) as f32,
            h: i16_at(r, 0xe) as f32,
            label: u16_at(r, 0x10),
            alpha: u16_at(r, 0x12),
            selectable: r[0x14] & 1 != 0,
            has_size: r[0x15] != 0,
        })
    }

    pub fn sprite(&self, i: usize) -> Option<SpriteRec> {
        let r = self.rec(ChunkType::Sprite, i)?;
        let fl = r[0x12];
        Some(SpriteRec {
            id: u16_at(r, 0),
            priority: i16_at(r, 2),
            x: i16_at(r, 4) as f32,
            y: i16_at(r, 6) as f32,
            w: u16_at(r, 8) as f32,
            h: u16_at(r, 0xa) as f32,
            col: i16_at(r, 0xc),
            row: i16_at(r, 0xe),
            label: u16_at(r, 0x10),
            has_uv: fl & 1 != 0,
            single_packet: (fl >> 1) & 1 != 0,
            alpha_relative: (fl >> 2) & 1 != 0,
            flag3: (fl >> 3) & 1 != 0,
            rgba: [r[0x14], r[0x15], r[0x16], r[0x17]],
            u0: u16_at(r, 0x18),
            u1: u16_at(r, 0x1a),
            v0: u16_at(r, 0x1c),
            v1: u16_at(r, 0x1e),
        })
    }

    pub fn polygon(&self, i: usize) -> Option<PolygonRec> {
        let r = self.rec(ChunkType::Polygon, i)?;
        let fl = r[0xa];
        let mut p = PolygonRec {
            id: u16_at(r, 0),
            priority: i16_at(r, 2),
            col: i16_at(r, 4),
            row: i16_at(r, 6),
            label: u16_at(r, 8),
            has_uv: fl & 1 != 0,
            single_packet: (fl >> 1) & 1 != 0,
            alpha_relative: (fl >> 2) & 1 != 0,
            flag3: (fl >> 3) & 1 != 0,
            x: [0.0; 4],
            y: [0.0; 4],
            rgba: [[0; 4]; 4],
            u: [0; 4],
            v: [0; 4],
        };
        for k in 0..4 {
            p.x[k] = i16_at(r, 0xc + 2 * k) as f32;
            p.y[k] = i16_at(r, 0x14 + 2 * k) as f32;
            p.rgba[k] = [r[0x1c + k], r[0x20 + k], r[0x24 + k], r[0x28 + k]];
            p.u[k] = u16_at(r, 0x2c + 2 * k);
            p.v[k] = u16_at(r, 0x34 + 2 * k);
        }
        Some(p)
    }

    /// Shared prefix of `MenuText` / `MenuMessage` / `MenuFont` records.
    fn text_common(&self, r: &[u8]) -> TextCommon {
        let csa = i16_at(r, 0x16);
        TextCommon {
            id: u16_at(r, 0),
            priority: i16_at(r, 2),
            x: i16_at(r, 4) as f32,
            y: i16_at(r, 6) as f32,
            col: i16_at(r, 8),
            row: i16_at(r, 0xa),
            text_id: u16_at(r, 0xc),
            rgba: [r[0x10], r[0x11], r[0x12], r[0x13]],
            font_number: (u16_at(r, 0x14) & 0xff) as u8,
            clut_set: ((csa as i32 + if csa < 0 { 15 } else { 0 }) >> 4) as u8,
            spacing: {
                let lo = (csa as u16 & 0xf) as i8;
                if csa < 0 && lo != 0 { lo - 16 } else { lo }
            },
            shadow: [r[0x18], r[0x19]],
            mode: r[0x1a],
            flags: r[0x1b],
        }
    }

    pub fn menu_text(&self, i: usize) -> Option<TextCommon> {
        let r = self.rec(ChunkType::MenuText, i)?;
        Some(self.text_common(r))
    }

    pub fn message(&self, i: usize) -> Option<MessageRec> {
        let r = self.rec(ChunkType::Message, i)?;
        Some(MessageRec { common: self.text_common(r), max_chars: u16_at(r, 0x1c), extra: u16_at(r, 0x1e) })
    }
}

#[derive(Debug, Clone)]
pub struct AttachRec {
    pub offset: u32,
    pub id: i32,
    pub size: u32,
}

#[derive(Debug, Clone)]
pub struct FontDrawRec {
    pub id: u16,
    pub priority: i16,
    /// `GS_PSM` code (0x2c in all samples = PSMT8? CT16S?; see FontDraw notes)
    pub psm: u16,
    pub flags: u16,
    pub width: u16,
    pub height: u16,
    pub clut: u32,
}

#[derive(Debug, Clone)]
pub struct CursorRec {
    pub id: u16,
    pub priority: i16,
    /// size of the cursor image (written to the cursor target size)
    pub width: i16,
    pub height: i16,
    /// `Cursor::SetType` image index
    pub kind: u8,
    /// 0 none, 1 polygon shadow, 2 flare trail (`Cursor::SetShadow`)
    pub shadow: u8,
    pub rotate: bool,
    /// bit mask 1 down, 2 up, 4 left, 8 right (`Cursor::SetDirection`)
    pub direction: u8,
    pub skip_mode: u8,
    pub back_object: bool,
}

#[derive(Debug, Clone)]
pub struct WindowRec {
    pub id: u16,
    pub priority: i16,
    pub x: f32,
    pub y: f32,
    pub w: f32,
    pub h: f32,
    pub scroll_cols: i16,
    pub scroll_rows: i16,
    /// open/close durations in `MenuObj` timer ticks
    pub open_time: u32,
    pub close_time: u32,
    pub open_effect: u8,
    pub close_effect: u8,
    pub style: u8,
    pub clip_mode: u8,
    /// window flags@0xb1 bit3: cursor wraps horizontally at the row ends (`MovePlace`)
    pub wrap_h: bool,
    /// bit4: cursor wraps vertically at the column ends
    pub wrap_v: bool,
    pub scroll_enable: bool,
    pub scroll_mark_mask: u8,
}

#[derive(Debug, Clone)]
pub struct GroupRec {
    pub id: u16,
    pub priority: i16,
    pub x: f32,
    pub y: f32,
    pub col: i16,
    pub row: i16,
    pub w: f32,
    pub h: f32,
    pub label: u16,
    pub alpha: u16,
    pub selectable: bool,
    pub has_size: bool,
}

#[derive(Debug, Clone)]
pub struct SpriteRec {
    pub id: u16,
    pub priority: i16,
    pub x: f32,
    pub y: f32,
    pub w: f32,
    pub h: f32,
    pub col: i16,
    pub row: i16,
    pub label: u16,
    pub has_uv: bool,
    pub single_packet: bool,
    pub alpha_relative: bool,
    pub flag3: bool,
    pub rgba: [u8; 4],
    pub u0: u16,
    pub u1: u16,
    pub v0: u16,
    pub v1: u16,
}

#[derive(Debug, Clone)]
pub struct PolygonRec {
    pub id: u16,
    pub priority: i16,
    pub col: i16,
    pub row: i16,
    pub label: u16,
    pub has_uv: bool,
    pub single_packet: bool,
    pub alpha_relative: bool,
    pub flag3: bool,
    pub x: [f32; 4],
    pub y: [f32; 4],
    pub rgba: [[u8; 4]; 4],
    pub u: [u16; 4],
    pub v: [u16; 4],
}

#[derive(Debug, Clone)]
pub struct TextCommon {
    pub id: u16,
    pub priority: i16,
    pub x: f32,
    pub y: f32,
    pub col: i16,
    pub row: i16,
    /// index into the type-1 text table
    pub text_id: u16,
    pub rgba: [u8; 4],
    pub font_number: u8,
    pub clut_set: u8,
    pub spacing: i8,
    pub shadow: [u8; 2],
    pub mode: u8,
    pub flags: u8,
}

#[derive(Debug, Clone)]
pub struct MessageRec {
    pub common: TextCommon,
    pub max_chars: u16,
    pub extra: u16,
}

/// `PKFINFO.TBL` name codec and entry type: re-exported from the canonical implementation
/// (`sh2_core::fileio`, section A -- `FileIOLib::enCode/deCode`, verified byte-exact on all 11 archives).
pub mod pkf {
    pub use sh2_core::fileio::{decode_name, encode_name, DirEntry as Entry};

    #[cfg(test)]
    mod tests {
        use super::*;
        #[test]
        fn name_roundtrip() {
            for n in ["MENU", "GAMEOVER.MSD", "CMDMENU.MSD", "FI_000.TEX", "BGM803.SSV", "SAVELIST.MDT"] {
                assert_eq!(decode_name(&encode_name(n)), n);
            }
        }
    }
}
