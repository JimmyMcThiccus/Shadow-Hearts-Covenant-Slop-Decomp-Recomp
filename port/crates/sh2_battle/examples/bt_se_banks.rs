//! Round 6 BT: wave-bank id and sound count of every SE bank on the disc (`*.SSE`).  `bt_se_banks <disc> [filter]`
use sh2_core::fileio::Disc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).expect("disc");
    let filter = a.get(2).cloned().unwrap_or_default();
    for dir in ["BTLDATA/SOUND/SE", "BTLDATA/SOUND/SYSTEM", "COMMON"] {
        let Some(files) = d.info().list_dir(dir) else {
            println!("{dir}: no listing");
            continue;
        };
        for e in files.iter().filter(|e| !e.is_dir()) {
            let name = &e.name;
            if !name.to_uppercase().ends_with(".SSE") || !name.contains(&filter) {
                continue;
            }
            let p = format!("{dir}/{name}");
            let Ok(b) = d.read(&p) else { continue };
            match sh2_audio::sdh::Bank::parse_opts(&b, false) {
                Ok(bank) => println!("{p}: bank {:#06x} waves {}", bank.bank_id, bank.waves.len()),
                Err(e) => println!("{p}: {e:?}"),
            }
        }
    }
}
