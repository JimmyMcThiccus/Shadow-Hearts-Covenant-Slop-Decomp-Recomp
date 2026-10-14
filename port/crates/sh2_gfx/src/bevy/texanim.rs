//! `TXAH` texture animation for skinned models (characters, battle monsters): the `TXAD` entries decoded by
//! `sh2_formats::model` become [`TexAnimEntry`]s (RGBA rows ready to copy into the texture); `TXA<name>` motion events and the
//! eye-blink machine select the frame ([`crate::model::ModelInstance::texanim_frame`]).  The BG-model version of the same mapping lives in
//! [`super::bgmotion`] (`parse_texanim`, which reads the raw blob instead of the decoded table).

use sh2_formats::model::{Model, TexFormat, TextureDef};

use super::bgmotion::TexAnimEntry;

/// Convert the decoded `TXAD` entries of `model` (same rectangle logic as `TextureAnim::CreateData`/`RefLoadImage`: the transfer is `w`
/// pixels per row from `dstX`, bottom-aligned with the entry's inset).
pub fn texanim_entries(model: &Model) -> Vec<TexAnimEntry> {
    let mut out = Vec::new();
    for def in &model.texanims {
        let Some(t) = model.textures.get(def.texture as usize) else { continue };
        let (w, h) = (def.width as usize, def.height as usize);
        let rrw = w.clamp(1, (t.width as usize).max(1));
        let px = w * h;
        let rows = px.div_ceil(rrw.max(1));
        let bits = if t.format == TexFormat::Psmt4 { 4 } else { 8 };
        let row_bytes = if bits == 4 { rrw.div_ceil(2) } else { rrw };
        let mut frames = Vec::new();
        for k in 0..def.frame_count as usize {
            let Some(src) = def.frame_bytes(k, bits) else { break };
            let mut data = src.to_vec();
            data.resize(rows * row_bytes, 0);
            let mut tmp: TextureDef = t.clone();
            tmp.width = rrw as u16;
            tmp.height = rows as u16;
            tmp.data = data;
            frames.push(tmp.to_rgba8());
        }
        let y0 = (t.height as u32).saturating_sub(def.inset as u32).saturating_sub(h as u32);
        out.push(TexAnimEntry { name: def.name.clone(), texture: def.texture as usize, x0: def.dst_x as u32, y0, rrw: rrw as u32, rows: rows as u32, frames, current: 0 });
    }
    out
}
