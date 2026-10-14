//! Developer tool: scan every BBG of a disc (`bbg_scan <disc dir>`): texture formats / sizes, parse warnings, DAT, FOG, BGCOLOR.
use sh2_core::fileio::Disc;
use sh2_formats::model::TexFormat;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).unwrap();
    // `bbg_scan <disc> --dump <id> <dir>`: write every texture of one BBG as NN_WxH.rgba
    if a.len() > 4 && a[2] == "--dump" {
        let id: u32 = a[3].parse().unwrap();
        let b = d.read(&format!("BTLDATA/BBG/{id:03}.BBG")).unwrap();
        let secs = sh2_battle::stage::sections(&b);
        let m = sh2_formats::model::Model::parse(secs.iter().find(|s| s.0 == "mdl").unwrap().1).unwrap();
        std::fs::create_dir_all(&a[4]).unwrap();
        for (i, t) in m.textures.iter().enumerate() {
            std::fs::write(format!("{}/{i:02}_{}x{}.rgba", a[4], t.width, t.height), t.to_rgba8()).unwrap();
        }
        return;
    }
    // `bbg_scan <disc> --atoms <id>`: list the atomics (name, texture, vertices, bounds, mean colour)
    if a.len() > 3 && a[2] == "--atoms" {
        let id: u32 = a[3].parse().unwrap();
        let b = d.read(&format!("BTLDATA/BBG/{id:03}.BBG")).unwrap();
        let secs = sh2_battle::stage::sections(&b);
        let m = sh2_formats::model::Model::parse(secs.iter().find(|s| s.0 == "mdl").unwrap().1).unwrap();
        for (i, t) in m.textures.iter().enumerate() {
            println!("TEX {i} {}x{} fmt {:#x} alpha_bits {:#06x} ref {} flags {:#x}", t.width, t.height, t.raw_format, t.alpha_bits, t.alpha_ref, t.flags);
        }
        for (i, at) in m.atomics.iter().enumerate() {
            let p = &at.geometry.positions;
            if p.is_empty() { continue; }
            let mut lo = [f32::MAX; 3]; let mut hi = [f32::MIN; 3];
            for v in p { for k in 0..3 { lo[k] = lo[k].min(v[k]); hi[k] = hi[k].max(v[k]); } }
            let c = &at.geometry.colors;
            let mean: Vec<u32> = (0..4).map(|k| if c.is_empty() { 0 } else { c.iter().map(|x| x[k] as u32).sum::<u32>() / c.len() as u32 }).collect();
            println!("{i:3} {:12} {:?} tex {:3}/{:3} v{} fl {:#x} ext20 {} lo {:.0?} hi {:.0?} col {mean:?}", at.name, at.kind, at.texture, at.texture2, at.vertex_count, at.flags, at.extra20, lo, hi);
        }
        return;
    }
    for id in 0..200u32 {
        let Ok(b) = d.read(&format!("BTLDATA/BBG/{id:03}.BBG")) else { continue };
        let secs = sh2_battle::stage::sections(&b);
        let tags: Vec<String> = secs.iter().map(|s| format!("{}:{}", s.0, s.1.len())).collect();
        let Some(m) = secs.iter().find(|s| s.0 == "mdl") else { println!("{id:03} no mdl {tags:?}"); continue };
        match sh2_formats::model::Model::parse(m.1) {
            Ok(m) => {
                let ipu = m.textures.iter().filter(|t| t.format == TexFormat::Ipu).count();
                let fm: Vec<String> = m.textures.iter().map(|t| format!("{}x{}/{:x}{}", t.width, t.height, t.raw_format, if t.format == TexFormat::Ipu { "IPU" } else { "" })).collect();
                println!("{id:03} atomics {} tex {} ipu {} warn {} {fm:?}", m.atomics.len(), m.textures.len(), ipu, m.warnings.len());
            }
            Err(e) => println!("{id:03} parse error {e}"),
        }
    }
}
