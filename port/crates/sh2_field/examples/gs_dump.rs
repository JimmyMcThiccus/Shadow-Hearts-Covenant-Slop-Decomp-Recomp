//! Read-only: print the `GS` chunk map names (+0x10 current, +0x20 "saved" map) and the story flags of every SH2 save on a PS2 memory card image.
//! `gs_dump <Mcd.ps2>`
use sh2_menu::memcard::MemCard;
use sh2_menu::save::{FieldSave, SaveFile};
fn main() {
    let p = std::env::args().nth(1).expect("card");
    let mc = MemCard::open(&p).expect("card");
    for d in mc.root() {
        if !d.is_dir() {
            continue;
        }
        let name = d.name.clone();
        for f in mc.list_dir(&name).unwrap_or_default() {
            if !f.is_file() {
                continue;
            }
            let Some(b) = mc.read_file(&name, &f.name) else { continue };
            let Ok(s) = SaveFile::parse(&b) else { continue };
            let gs = s.field.find(FieldSave::TAG_GS).map(|c| c.payload.clone()).unwrap_or_default();
            let cs = |o: usize| gs.get(o - 4..o + 12).map(|x| String::from_utf8_lossy(&x[..x.iter().position(|&c| c == 0).unwrap_or(16)]).to_string()).unwrap_or_default();
            let rg = s.field.find(FieldSave::TAG_RG).map(|c| c.payload.clone()).unwrap_or_default();
            let flags: Vec<String> = (8..0x70u32).filter(|&n| rg.get(0xc + (n as usize >> 3)).map(|b| b & (1 << (n & 7)) != 0).unwrap_or(false)).map(|n| format!("{n:#x}")).collect();
            println!("{name}/{}: cur {:?} saved {:?} flags {}", f.name, cs(0x10), cs(0x20), flags.join(","));
        }
    }
}
