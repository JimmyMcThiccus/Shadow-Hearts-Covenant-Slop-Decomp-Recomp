//! `btl_box_probe <disc> <chr numbers...>`: the `bbx` box and radius of battle models.
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    for n in &a[2..] {
        let n: u32 = n.parse().unwrap();
        let b = d.read(&format!("BTLDATA/CHR/{n:03}.BCM")).unwrap();
        let secs = sh2_battle::stage::sections(&b);
        let bx = secs.iter().find(|s| s.0 == "bbx").and_then(|s| sh2_battle::formation::ChrBox::parse(s.1));
        println!("{n}: {bx:?} radius {:?}", bx.map(|b| b.radius()));
        if std::env::var_os("BBX_DUMP").is_some() {
            if let Some(s) = secs.iter().find(|s| s.0 == "bbx") {
                let d = s.1;
                println!("  bbx {} bytes: {:02x?}", d.len(), &d[..d.len().min(0x100)]);
                println!("  text: {:?}", String::from_utf8_lossy(&d[..d.len().min(0x100)]));
            }
        }
    }
}
