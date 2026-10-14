//! Dump the DYNH chains of a character model: `dyn_dump FIELD/MODEL/005.SET`
use sh2_formats::dynamics::parse_dynamics;
use sh2_formats::model::Model;
use sh2_formats::pkb;
use sh2_gfx::bevy::Sh2Disc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let disc = Sh2Disc::from_env(a.iter().any(|x| x == "--us")).unwrap();
    let b = disc.read(&a[1]).unwrap();
    let pkg = pkb::parse_package(&b, 0).unwrap();
    for e in pkg.entries.iter().filter(|e| e.kind_str() == "mdl") {
        let m = Model::parse(&b[e.offset..]).unwrap();
        println!("model @{:#x} frames {}", e.offset, m.frames.len());
        for ext in m.extensions.iter().filter(|x| &x.tag == b"DYNH") {
            println!(" DYNH count {} data {}", ext.count, ext.data.len());
            for c in parse_dynamics(ext).unwrap() {
                println!("  chain {} flags {:#x} grav {} air {}", c.name, c.flags, c.gravity_raw, c.air_resistance_raw);
                for n in &c.nodes {
                    let fi = m.find_frame(&n.frame_name);
                    let f = fi.map(|i| &m.frames[i]);
                    println!("   node {:12} c={} p10={} rest={:?} frame={:?} bind_t={:?} parent={:?} child={:?}", n.frame_name, n.param_c, n.param_10, n.rest_pos, fi, f.map(|f| f.translation), f.map(|f| f.parent), f.map(|f| f.child));
                }
            }
        }
    }
}
