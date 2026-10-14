//! List the contents of the PKB archives of a Shadow Hearts: Covenant disc folder.
//!
//! `SH2_DISC_DIR=".../Shadow Hearts II (Japan) (Furokuban)" cargo run -p sh2_core --example pkb_list [path-prefix]`
//! With an argument it only prints entries whose path contains it, and also resolves it with `Disc::read` to prove
//! the byte offsets (prints the first bytes of each match).
use sh2_core::fileio::Disc;

fn main() {
    let dir = std::env::var("SH2_DISC_DIR").expect("set SH2_DISC_DIR to the disc folder");
    let disc = Disc::open(&dir).expect("PKFINFO.TBL");
    let filter = std::env::args().nth(1);
    let listing = disc.listing();
    let mut total = 0usize;
    for (container, files) in &listing {
        let kind = if files.first().map(|f| f.1.in_archive).unwrap_or(false) { "PKB" } else { "file" };
        println!("== {container} ({kind}, {} entries)", files.len());
        for (path, loc) in files {
            total += 1;
            if let Some(f) = &filter {
                if !path.to_uppercase().contains(&f.to_uppercase()) {
                    continue;
                }
                let head = disc.read(path).map(|b| b[..b.len().min(8)].to_vec()).unwrap_or_default();
                println!("  {path:<40} off={:#010x} size={:>9} head={:02x?}", loc.byte_offset, loc.size, head);
            } else if files.len() <= 20 {
                println!("  {path:<40} off={:#010x} size={:>9}", loc.byte_offset, loc.size);
            }
        }
    }
    println!("{total} files total");
}
