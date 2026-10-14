//! Debug: dump per-atomic stats of a map (renderer fidelity work).
use sh2_field::mps::Mps;
use sh2_formats::model::Model;
use sh2_gfx::bevy::Sh2Disc;

fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let name = a.iter().skip(1).find(|x| !x.starts_with("--")).unwrap();
    let disc = Sh2Disc::from_env(us).unwrap();
    let mps = Mps::parse(disc.read(&format!("FIELD/MPS/{name}.MPS")).unwrap()).unwrap();
    println!("FIELD hdr {:?}", mps.field_header());
    for l in mps.lights().unwrap() {
        println!("LIGHT kind {} flags {:x} int {} col {:?} pos {:?}", l.kind, l.flags, l.intensity, l.color, l.pos);
        println!("   raw {:02x?}", &l.raw[..]);
    }
    println!("FOG {:?}  BG {:?}  mirrors {:?}", mps.fog().unwrap(), mps.bg_color(), mps.mirrors().unwrap());
    for (i, rec) in mps.models().unwrap().iter().enumerate() {
        println!("MODEL {i} {} kind {:?} flags {:x} pos {:?} rot {:?} target {}", rec.name, rec.kind, rec.flags, rec.pos, rec.rot, rec.target_model);
        if matches!(rec.kind, sh2_field::mps::ModelKind::Motion) {
            match sh2_formats::motion::Motion::parse(mps.model_blob(rec)) {
                Ok(mo) => {
                    for e in &mo.events {
                        let n = (e.key_count as usize).min(12);
                        let keys: Vec<(u16, i16)> = (0..n).map(|i| { let o = i * 4; (u16::from_le_bytes([e.raw[o], e.raw[o + 1]]), i16::from_le_bytes([e.raw[o + 2], e.raw[o + 3]])) }).collect();
                        println!("   EVENT {} kind {:x} bone {} keys {:?}", e.name, e.kind, e.bone, keys);
                    }
                    println!("  MOTION `{}` frames {} fps {} flags {:x} tracks {:?} events {:?}", mo.name, mo.frame_count, mo.fps, mo.flags, mo.tracks.iter().map(|t| (t.name.clone(), t.rot_keys.len(), t.pos_keys.len())).collect::<Vec<_>>(), mo.events.iter().map(|e| (e.name.clone(), e.key_count, e.bone, e.kind)).collect::<Vec<_>>());
                }
                Err(e) => println!("  MOTION parse error {e}"),
            }
            continue;
        }
        let Ok(m) = Model::parse(mps.model_blob(rec)) else { continue };
        if let Some(raw) = &m.texanim_raw {
            println!("  TXAH {} bytes: {:02x?}", raw.len(), &raw[..raw.len().min(0x60)]);
            let blob = mps.model_blob(&rec);
            let to = m.header.texanim_off as usize;
            let n = u16::from_le_bytes([blob[to + 4], blob[to + 5]]) as usize;
            let mut p = to + 0x10;
            for _ in 0..n {
                let e = &blob[p..p + 0x30];
                let name = String::from_utf8_lossy(&e[4..16]).trim_end_matches('\0').to_string();
                let r16 = |o: usize| u16::from_le_bytes([e[o], e[o + 1]]);
                println!("   TXAD `{}` tex {} frames {} w {} h {} stride {} dstx {} inset {} size16 {} hdr {:02x?}", name, e[0x10], e[0x11], r16(0x12), r16(0x14), r16(0x18), r16(0x1a), r16(0x1c), r16(0x20), &e[0x10..0x30]);
                p += 0x30 + r16(0x20) as usize * 16;
            }
        }
        for (fi, f) in m.frames.iter().enumerate() { println!("  FRAME {fi} {} parent {:?}", f.name, f.parent); }
        println!("  hdr flags {:x} texanim {} textures {}", m.header.flags, m.texanim_raw.as_ref().map(|v| v.len()).unwrap_or(0), m.textures.len());
        for (ti, t) in m.textures.iter().enumerate() {
            let rgba = t.to_rgba8();
            if let Ok(dir) = std::env::var("TEX_OUT") {
                let mut f = (t.width as u32).to_le_bytes().to_vec();
                f.extend((t.height as u32).to_le_bytes());
                f.extend(&rgba);
                std::fs::write(format!("{dir}/{name}_m{i}_t{ti}.raw"), f).unwrap();
            }
            let mut hist = std::collections::BTreeMap::new();
            for px in rgba.chunks(4) { *hist.entry(px[3]).or_insert(0usize) += 1; }
            let h: Vec<String> = hist.iter().take(12).map(|(a, n)| format!("{a}:{n}")).collect();
            println!("  TEX {ti} alphahist(used px) {} ({} distinct)", h.join(","), hist.len());
            println!("  TEX {ti} {}x{} {:?} fmt {:x} alpha {:04x} aref {} flags {:02x}", t.width, t.height, t.format, t.raw_format, t.alpha_bits, t.alpha_ref, t.flags);
        }
        let mut groups: std::collections::BTreeMap<(u8, u16, u8, u8, u8, u8, String), (usize, u32)> = Default::default();
        for at in m.atomics.iter() {
            let e = groups.entry((at.texture, at.flags, at.b14, at.b15, at.b16, at.b17, format!("{:?}/t2={}/sh={}/e{}", at.kind, at.texture2, at.shared_ref, at.extra20))).or_default();
            e.0 += 1;
            e.1 += at.vertex_count;
        }
        for (k, v) in groups {
            println!("  GRP tex {} fl {:04x} b14 {:02x} b15 {:02x} b16 {:02x} b17 {:02x} {} -> {} atomics {} verts", k.0, k.1, k.2, k.3, k.4, k.5, k.6, v.0, v.1);
        }
    }
}
