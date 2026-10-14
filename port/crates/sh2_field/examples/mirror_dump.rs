use sh2_field::mps::{tags, Mps};
use sh2_gfx::bevy::Sh2Disc;
fn main() {
    let name = std::env::args().nth(1).unwrap();
    let disc = Sh2Disc::from_env(true).unwrap();
    let mps = Mps::parse(disc.read(&format!("FIELD/MPS/{name}.MPS")).unwrap()).unwrap();
    let c = mps.find(tags::MIRROR).unwrap();
    println!("count {} data_off {:#x} hdr {:#x} relocated {}", c.count, c.data_off, c.hdr, c.relocated);
    println!("hdr bytes {:02x?}", &mps.data[c.hdr..c.hdr + 0x20]);
    let s = c.data_start();
    for i in 0..(c.count as usize * 3) {
        let o = s + i * 0x10;
        let f: Vec<f32> = (0..4).map(|k| f32::from_le_bytes(mps.data[o + k * 4..o + k * 4 + 4].try_into().unwrap())).collect();
        println!("  +{:#x}: {:?}", i * 0x10, f);
    }
}
