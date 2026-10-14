use sh2_field::mps::{ModelKind, Mps};
use sh2_formats::model::Model;
use sh2_gfx::bevy::bgmotion::parse_texanim;
use sh2_gfx::bevy::Sh2Disc;
fn main() {
    let name = std::env::args().nth(1).unwrap();
    let out = std::env::var("TEX_OUT").unwrap();
    let disc = Sh2Disc::from_env(true).unwrap();
    let mps = Mps::parse(disc.read(&format!("FIELD/MPS/{name}.MPS")).unwrap()).unwrap();
    for (mi, rec) in mps.models().unwrap().iter().enumerate() {
        if matches!(rec.kind, ModelKind::Motion) { continue; }
        let blob = mps.model_blob(rec);
        let Ok(m) = Model::parse(blob) else { continue };
        for e in parse_texanim(blob, &m) {
            let t = &m.textures[e.texture];
            println!("model {mi} {} entry {} tex {} ({}x{}) x0 {} y0 {} rrw {} rows {} frames {}", rec.name, e.name, e.texture, t.width, t.height, e.x0, e.y0, e.rrw, e.rows, e.frames.len());
            let w = |nm: String, wd: usize, ht: usize, d: &[u8]| {
                let mut f = (wd as u32).to_le_bytes().to_vec();
                f.extend((ht as u32).to_le_bytes());
                f.extend(d);
                std::fs::write(format!("{out}/{nm}.raw"), f).unwrap();
            };
            w(format!("m{mi}_{}_base", e.name), t.width as usize, t.height as usize, &t.to_rgba8());
            for (k, f) in e.frames.iter().enumerate() { w(format!("m{mi}_{}_f{k}", e.name), e.rrw as usize, e.rows as usize, f); }
        }
    }
}
