use sh2_core::fileio::Disc;
use sh2_formats::model::Model;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).unwrap();
    for id in a[2..].iter() {
        let b = d.read(&format!("BTLDATA/BBG/{id}.BBG")).unwrap();
        let n = u32::from_le_bytes(b[0..4].try_into().unwrap()) as usize;
        let mut secs = vec![];
        for i in 0..n {
            let off = u32::from_le_bytes(b[12 + i * 8..16 + i * 8].try_into().unwrap()) as usize;
            secs.push((String::from_utf8_lossy(&b[8 + i * 8..12 + i * 8]).trim_end_matches('\0').to_string(), off));
        }
        println!("{id}: {secs:?}");
        let (_, off) = &secs.iter().find(|s| s.0 == "mdl").unwrap();
        let end = secs.iter().map(|s| s.1).filter(|&o| o > *off).min().unwrap_or(b.len());
        match Model::parse(&b[*off..end]) {
            Ok(m) => {
                let mut lo = [f32::MAX; 3];
                let mut hi = [f32::MIN; 3];
                for at in &m.atomics {
                    for p in &at.geometry.positions {
                        for k in 0..3 {
                            lo[k] = lo[k].min(p[k]);
                            hi[k] = hi[k].max(p[k]);
                        }
                    }
                }
                println!("  atomics {} textures {} warnings {:?} bounds {lo:?} {hi:?}", m.atomics.len(), m.textures.len(), m.warnings.len());
            }
            Err(e) => println!("  parse error {e}"),
        }
    }
}
