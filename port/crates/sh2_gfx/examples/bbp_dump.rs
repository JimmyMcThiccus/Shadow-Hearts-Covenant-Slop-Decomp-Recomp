//! Developer tool (E3): `bbp_dump <disc> <effect id> [P index] [--hex]` prints the parsed `P` (`BBPF`) sections of one battle effect.
use sh2_core::fileio::Disc;
use sh2_gfx::effects::bbp::Bbpf;
use sh2_script::efmg::Efmg;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).unwrap();
    let id: i32 = a[2].parse().unwrap();
    let want: Option<u8> = a.get(3).and_then(|s| s.parse().ok());
    let hex = a.iter().any(|s| s == "--hex");
    let bytes = d.read(&format!("EFFECT/{id:03}_00.EFD")).unwrap();
    let e = Efmg::parse(&bytes).unwrap();
    for (idx, sec) in e.iter_kind(b'P') {
        if want.is_some() && want != Some(idx) {
            continue;
        }
        let b = Bbpf::parse(sec).unwrap();
        println!("P[{idx}] {} bytes, {} lines, origin {:?}", sec.len(), b.lines.len(), b.origin);
        for (i, l) in b.lines.iter().enumerate().take(3) {
            println!("  line {i}: A {:?} B {:?} C {:?}", l.a.truncate(), l.b.truncate(), l.c.truncate());
        }
        for k in &b.keys {
            println!("  key t={:.3} rot={:.3} scale={:?} col={:?} flags={:x}", k.time, k.rot, k.scale, k.color, k.flags);
        }
        if hex {
            for (i, ch) in sec.chunks(16).enumerate() {
                println!("{:04x}: {}", i * 16, ch.iter().map(|b| format!("{b:02x}")).collect::<Vec<_>>().join(" "));
            }
        }
    }
}
