use sh2_audio::Bank;
use sh2_core::fileio::Disc;
fn main() {
    let disc = Disc::from_env().unwrap();
    let path = std::env::args().nth(1).unwrap();
    let prog: usize = std::env::args().nth(2).unwrap().parse().unwrap();
    let b = Bank::parse(&disc.read(&path).unwrap()).unwrap();
    let p = &b.programs[prog];
    println!("program {prog}: vol={} pan={} coarse={} fine={}", p.vol, p.pan, p.coarse, p.fine);
    for s in &p.splits {
        println!("  split {s:?}");
        let set = &b.sample_sets[s.sample_set as usize];
        println!("    set curve={} vel {}..{} tones {:?}", set.curve, set.vel_lo, set.vel_hi, set.tones);
        for &t in &set.tones {
            let tone = &b.tones[t as usize];
            let w = &b.waves[tone.wave() as usize];
            println!("    tone {t}: wave {} rate {} len {} samples loop {:?} looping={} | vol {} pan {} root {} fine {} adsr {:04x}/{:04x} raw {:02x?}", tone.wave(), w.rate, w.pcm.len(), w.loop_start, w.looping, tone.vol(), tone.pan(), tone.root_key(), tone.fine(), tone.adsr1(), tone.adsr2(), tone.raw);
        }
    }
}
