use sh2_audio::Bank;
use sh2_core::fileio::Disc;
fn main() {
    let disc = Disc::from_env().unwrap();
    for path in std::env::args().skip(1) {
        let b = Bank::parse(&disc.read(&path).unwrap()).unwrap();
        println!("{path}: tags {:?} id {:#x}", b.tags.iter().map(|t| String::from_utf8_lossy(t).into_owned()).collect::<Vec<_>>(), b.bank_id);
        for (i, w) in b.waves.iter().enumerate() {
            let peak = w.pcm.iter().map(|s| s.unsigned_abs()).max().unwrap_or(0);
            println!("  wave {i}: off {:#x} flags {} rate {} samples {} ({:.2}s) peak {} loop {:?}", w.offset, w.flags, w.rate, w.pcm.len(), w.duration_secs(), peak, w.loop_start);
        }
        for (i, t) in b.timbres.iter().enumerate() {
            for g in &t.groups {
                println!("  timbre {i}: notes {}..{} tones {:?}", g.note_lo, g.note_hi, g.tones.iter().map(|t| (t.wave(), t.vol())).collect::<Vec<_>>());
            }
        }
        for (id, v) in &b.se_map {
            println!("  se {id:#x} -> {v:#x} {:?}", b.se_target(*id));
        }
        for (i, r) in b.se_records.iter().enumerate() {
            if let Some(r) = r {
                println!("  fq {i}: vol {} pan {} timbre {:#x} streams {:?}", r.vol, r.pan, r.timbre_id, r.streams.iter().map(|s| s.events.to_vec()).collect::<Vec<_>>());
            }
        }
    }
}
