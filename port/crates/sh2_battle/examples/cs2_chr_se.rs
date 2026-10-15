//! Round 6 CS2: the SE banks inside the battle character packages (`BTLDATA/CHR/NNN.BCM` entries `ase` / `dse` / `wse` / `mse` / `cse`,
//! CBattle chr load: `ase` -> `BtlChr+0x4b0`, `dse` -> `+0x4b8`, both `HNMSnd::IOPEntry`).  `cs2_chr_se <disc> [first] [last] [--wav DIR]`
//! (`--wav`: every SE of the listed characters' `ase` / `dse` banks rendered to `DIR/chrNNN_<kind>_<id>.wav`, 3 s, played through `FindSE`)
use sh2_core::fileio::Disc;
use sh2_formats::pkb;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).expect("disc");
    let first: u32 = a.get(2).and_then(|s| s.parse().ok()).unwrap_or(0);
    let last: u32 = a.get(3).and_then(|s| s.parse().ok()).unwrap_or(999);
    let wav: Option<String> = a.iter().position(|s| s == "--wav").and_then(|i| a.get(i + 1)).cloned();
    for n in first..=last {
        for ext in ["BCM", "WPN"] {
            let p = format!("BTLDATA/CHR/{n:03}.{ext}");
            let Ok(b) = d.read(&p) else { continue };
            let Some(pkg) = pkb::parse_package(&b, 0) else { continue };
            let mut out = Vec::new();
            for e in &pkg.entries {
                let k = e.kind_str();
                if !k.ends_with("se") {
                    continue;
                }
                if let Some(dir) = wav.as_ref().filter(|_| k == "ase" || k == "dse") {
                    if let Ok(bank) = sh2_audio::sdh::Bank::parse(&b[e.offset..]) {
                        let set = bank.se_set_id.unwrap_or(bank.bank_id);
                        let ids: Vec<u16> = bank.se_map.iter().map(|x| x.0).collect();
                        for id in ids {
                            let mut synth = sh2_audio::Synth::new();
                            synth.add_bank(bank.clone());
                            let Some(h) = synth.find_se_bank(set, id) else { continue };
                            synth.play_se(h, id, &sh2_script::audio::SeParam::default());
                            let pcm = sh2_audio::synth::render_seconds(&mut synth, 3.0);
                            let _ = std::fs::create_dir_all(dir);
                            let f = std::path::Path::new(dir).join(format!("chr{n:03}_{k}_{:04x}{id:04x}.wav", set));
                            sh2_audio::write_wav(&f, &pcm, 2, sh2_audio::OUT_RATE).unwrap();
                        }
                    }
                }
                match sh2_audio::sdh::Bank::parse_opts(&b[e.offset..], false) {
                    Ok(bank) => out.push(format!("{k} wave bank {:#06x} FE set {:x?} waves {} se {} ids {:x?}", bank.bank_id, bank.se_set_id, bank.waves.len(), bank.se_map.len(), bank.se_map.iter().map(|x| x.0).collect::<Vec<_>>())),
                    Err(er) => out.push(format!("{k} ERR {er:?}")),
                }
            }
            if !out.is_empty() {
                println!("{p}: {}", out.join(" | "));
            }
        }
    }
    // the SE files: wave bank vs FE set id
    for dir in ["BTLDATA/SOUND/SE", "BTLDATA/SOUND/SYSTEM", "COMMON", "FIELD/SOUND/SE"] {
        let Some(files) = d.info().list_dir(dir) else { continue };
        for e in files.iter().filter(|e| !e.is_dir() && e.name.to_uppercase().ends_with(".SSE")) {
            let p = format!("{dir}/{}", e.name);
            let Ok(b) = d.read(&p) else { continue };
            if let Ok(bank) = sh2_audio::sdh::Bank::parse_opts(&b, false) {
                println!("{p}: wave bank {:#06x} FE set {:x?} se {} ids {:x?}", bank.bank_id, bank.se_set_id, bank.se_map.len(), bank.se_map.iter().map(|x| x.0).collect::<Vec<_>>());
            }
        }
    }
}
