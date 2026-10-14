use sh2_field::mps::{ModelKind, Mps};
use sh2_formats::model::{Model, TexFormat};
use sh2_gfx::bevy::Sh2Disc;
fn main() {
    let name = std::env::args().nth(1).unwrap();
    let us = std::env::args().any(|a| a == "--us");
    let disc = Sh2Disc::from_env(us).unwrap();
    let mps = Mps::parse(disc.read(&format!("FIELD/MPS/{name}.MPS")).unwrap()).unwrap();
    for (mi, rec) in mps.models().unwrap().iter().enumerate() {
        if matches!(rec.kind, ModelKind::Motion) { continue; }
        let blob = mps.model_blob(rec);
        let Ok(m) = Model::parse(blob) else { continue };
        for (ti, t) in m.textures.iter().enumerate() {
            if t.format == TexFormat::Ipu {
                println!("model {mi} {} tex {ti} {}x{} raw_format {:#x} clut {} data {} bytes file_offset {:#x}", rec.name, t.width, t.height, t.raw_format, t.palette.len(), t.data.len(), t.file_offset);
                println!("head {:02x?}", &t.data[..t.data.len().min(96)]);
                std::fs::write(std::env::var("TEX_OUT").unwrap() + &format!("/{name}_ipu{ti}.bin"), &t.data).unwrap();
                match sh2_gfx::ipu::decode_ipum(&t.data) {
                    Ok(mv) => {
                        println!("decoded {} frames {}x{}", mv.frames.len(), mv.width, mv.height);
                        for k in [0usize, 1, 30, 60, 119] {
                            if let Some(f) = mv.frames.get(k) {
                                let mut o = (mv.width as u32).to_le_bytes().to_vec();
                                o.extend((mv.height as u32).to_le_bytes());
                                o.extend(f);
                                std::fs::write(std::env::var("TEX_OUT").unwrap() + &format!("/{name}_f{k:03}.raw"), o).unwrap();
                            }
                        }
                    }
                    Err(e) => println!("decode error: {e}"),
                }
                let o = t.file_offset;
                println!("tihd {:02x?}", &blob[o..o + 0x20]);
            }
        }
    }
}
