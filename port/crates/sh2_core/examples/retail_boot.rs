//! Verify that the US retail disc boots through the same code path as the JP demo: data names (`.NA`), the title overlay
//! `OPENING.BIN` (MWo3 group 3) and the OPENING.PKB contents resolve through `PKFINFO.TBL`.
//!
//! `SH2_US_DISC_DIR="<US disc folder>" cargo run -p sh2_core --example retail_boot`
use sh2_core::boot::Region;
use sh2_core::fileio::Disc;
use sh2_core::overlay::OverlayHeader;

fn main() {
    let dir = std::env::var("SH2_US_DISC_DIR").expect("set SH2_US_DISC_DIR to the US disc folder");
    let disc = Disc::open(&dir).expect("PKFINFO.TBL");
    let region = Region::Us;
    println!("{} files in PKFINFO.TBL", disc.listing().values().map(|v| v.len()).sum::<usize>());
    for name in [region.sshmes(), region.sshdat(), "opening/opening.dat", "opening/theater.dat", "opening/install.dat", "opening/demo.lsd", "OPENING/BGM803.SSV", "saveLoad/saveLoad.dat", "OPENING.BIN", "FIELD.BIN", "BATTLE.BIN"] {
        match disc.info().search_file(name) {
            Some(l) => println!("  {name:<28} {:<10} off={:#010x} size={:>9}", l.container, l.byte_offset, l.size),
            None => println!("  {name:<28} NOT FOUND"),
        }
    }
    for f in ["OPENING.BIN", "FIELD.BIN", "BATTLE.BIN"] {
        let img = disc.read(f).expect(f);
        let h = OverlayHeader::parse(&img).expect("MWo3");
        println!("{f}: group {} load {:#x} text {:#x} data {:#x} bss {:#x} ctors {:#x}..{:#x} name {:?}", h.id, h.load_addr, h.text_size, h.data_size, h.bss_size, h.ctor_begin, h.ctor_end, h.name);
    }
    let mes = disc.read(region.sshmes()).unwrap();
    let dat = disc.read(region.sshdat()).unwrap();
    println!("sshmes.na: {} tables, {} bytes; sshdat.na: {} tables, {} bytes", u32::from_le_bytes(mes[..4].try_into().unwrap()), mes.len(), u32::from_le_bytes(dat[..4].try_into().unwrap()), dat.len());
}
