//! Debug: per-map feature census for the renderer (which maps use mirrors / fog / billboards / water / TXAH / IPU ...).
use sh2_field::mps::Mps;
use sh2_formats::model::{AtomicKind, Model, TexFormat};
use sh2_gfx::bevy::Sh2Disc;

fn main() {
    let us = std::env::args().any(|x| x == "--us");
    let disc = Sh2Disc::from_env(us).unwrap();
    let list = disc.0.info().list_dir("FIELD/MPS").unwrap_or_default();
    let mut names: Vec<String> = list.iter().map(|e| e.name.clone()).filter(|n| n.ends_with(".MPS")).map(|n| n.trim_end_matches(".MPS").to_owned()).collect();
    names.sort();
    for name in names {
        let Ok(data) = disc.read(&format!("FIELD/MPS/{name}.MPS")) else { continue };
        let Ok(mps) = Mps::parse(data) else { continue };
        let mut s = String::new();
        let mir = mps.mirrors().map(|m| m.len()).unwrap_or(0);
        let fog = mps.fog().ok().flatten();
        let (mut bill, mut water, mut txah, mut ipu, mut shared, mut models, mut motions, mut skin, mut lowalpha) = (0, 0, 0, 0, 0, 0, 0, 0, 0);
        let mut abe_off = 0;
        for rec in mps.models().unwrap_or_default() {
            if matches!(rec.kind, sh2_field::mps::ModelKind::Motion) { motions += 1; continue; }
            let Ok(m) = Model::parse(mps.model_blob(&rec)) else { continue };
            models += 1;
            if m.texanim_raw.is_some() { txah += 1; }
            for t in &m.textures { if matches!(t.format, TexFormat::Ipu) { ipu += 1; } }
            for a in &m.atomics {
                match a.kind { AtomicKind::Billboard => bill += 1, AtomicKind::Water => water += 1, AtomicKind::Skin | AtomicKind::SkinNL => skin += 1, _ => {} }
                if a.shared_ref != -1 { shared += 1; }
                if a.flags & 0x40 == 0 { abe_off += 1; }
                let _ = &mut lowalpha;
            }
        }
        s += &format!("{name:10} models {models} motions {motions} mir {mir} fog {} bg {:?} bill {bill} water {water} txah {txah} ipu {ipu} shared {shared} skin {skin} abe_off {abe_off}", fog.is_some(), mps.bg_color());
        println!("{s}");
    }
}
