//! Dump the TXAH tables of the models in a package: `txa_dump FIELD/MODEL/005.SET`
use sh2_formats::model::Model;
use sh2_formats::pkb;
use sh2_gfx::bevy::Sh2Disc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let disc = Sh2Disc::from_env(a.iter().any(|x| x == "--us")).unwrap();
    for f in a.iter().skip(1).filter(|x| !x.starts_with("--")) {
        let b = disc.read(f).unwrap();
        let pkg = pkb::parse_package(&b, 0).unwrap();
        for e in pkg.entries.iter().filter(|e| e.kind_str() == "mdl") {
            let m = Model::parse(&b[e.offset..]).unwrap();
            println!("{f} model @{:#x}: {} textures {:?}", e.offset, m.textures.len(), m.textures.iter().map(|t| (t.width, t.height, t.format)).collect::<Vec<_>>());
            for t in &m.texanims {
                println!("   TXAD {:12} tex {} frames {} {}x{} stride {} dst_x {} inset {} data {}", t.name, t.texture, t.frame_count, t.width, t.height, t.stride, t.dst_x, t.inset, t.data.len());
            }
        }
    }
}
