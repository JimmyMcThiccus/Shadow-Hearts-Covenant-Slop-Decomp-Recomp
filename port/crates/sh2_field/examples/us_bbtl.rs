//! Dump the `BBTL` (scripted battle) table of the disc in `SH2_DISC_DIR`: `cargo run -p sh2_field --example us_bbtl`
use sh2_field::host::FieldTables;
use sh2_field::pkb_compat::PkbSet;
fn main() {
    let set = PkbSet::from_env().unwrap();
    let d = sh2_field::plugin::read_field_t(&set).expect("FIELD_T.DAT / FIELD.DAT");
    println!("field tables {} bytes, tag at 0x10: {:?}", d.len(), String::from_utf8_lossy(&d[0x10..0x14]));
    let mut t = FieldTables::default();
    t.from_field_t(&d);
    println!("tres {} bbtl {}", t.tres.len(), t.bbtl.len());
    for (i, r) in t.bbtl.iter().enumerate() {
        println!("bbtl {i}: bg {} bgm {} monset {} boss {}", u16::from_le_bytes([r[0], r[1]]), u16::from_le_bytes([r[2], r[3]]), u16::from_le_bytes([r[4], r[5]]), r[6]);
    }
}
