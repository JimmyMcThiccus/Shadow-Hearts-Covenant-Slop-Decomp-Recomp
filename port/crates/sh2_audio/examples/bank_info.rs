//! `SH2_DISC_DIR=... cargo run -p sh2_audio --example bank_info [path-substring]` – print the structure of every SDH bank found
//! in the disc's sound files (COMMON/FIELD/BTLDATA `*.SSE`/`*.SSQ`).
use sh2_audio::sdh::Bank;
use sh2_core::fileio::Disc;

fn main() {
    let dir = std::env::var("SH2_DISC_DIR").expect("SH2_DISC_DIR");
    let disc = Disc::open(&dir).unwrap();
    let filt = std::env::args().nth(1);
    for (_c, files) in disc.listing() {
        for (path, _loc) in files {
            let up = path.to_uppercase();
            if !(up.ends_with(".SSE") || up.ends_with(".SSQ")) {
                continue;
            }
            if let Some(f) = &filt {
                if !up.contains(&f.to_uppercase()) {
                    continue;
                }
            }
            let d = disc.read(&path).unwrap();
            match Bank::parse(&d) {
                Ok(b) => println!(
                    "{path:<34} id={:#06x} pg={:#x} ft={:#x} vol={} waves={} progs={} sets={} tones={} timbres={} se_map={} fq={} seqs={}",
                    b.bank_id, b.program_set_id, b.timbre_set_id, b.volume_percent, b.waves.len(), b.programs.len(), b.sample_sets.len(), b.tones.len(), b.timbres.len(), b.se_map.len(), b.se_records.len(), b.sequences.len()
                ),
                Err(e) => println!("{path}: {e}"),
            }
        }
    }
}
