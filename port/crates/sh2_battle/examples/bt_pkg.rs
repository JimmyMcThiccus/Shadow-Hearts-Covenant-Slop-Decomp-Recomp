//! Round 6 BT: list the package entries (tag, offset, motion names) of battle CHR files.  `bt_pkg <disc> <chr>...`
use sh2_core::fileio::Disc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).expect("disc");
    for n in &a[2..] {
        let n: u32 = n.parse().unwrap();
        for f in sh2_battle::models::chr_files_for(true, n) {
            let Ok(b) = d.read(&f) else {
                println!("{f}: missing");
                continue;
            };
            println!("{f}: {} bytes", b.len());
            for (tag, off) in sh2_battle::models::package_entries(&b) {
                let mut extra = String::new();
                if let Ok(m) = sh2_formats::motion::Motion::parse(&b[off..]) {
                    extra = format!(" motion {:?} dur {:.2}", m.name, m.duration());
                }
                println!("  {tag:5} @{off:#x}{extra}");
            }
        }
    }
}
