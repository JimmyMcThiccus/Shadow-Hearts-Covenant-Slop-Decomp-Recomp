use sh2_core::fileio::Disc;
use sh2_formats::{model::Model, motion::Motion, pkb};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).unwrap();
    let b = d.read(&a[2]).unwrap();
    let pkg = pkb::parse_package(&b, 0).unwrap();
    for (i, e) in pkg.entries.iter().enumerate() {
        let k = e.kind_str();
        let extra = match k.as_str() {
            "mdl" => Model::parse(&b[e.offset..]).map(|m| format!("model frames {} atomics {} tex {} ext {:?}", m.frames.len(), m.atomics.len(), m.textures.len(), m.extensions.iter().map(|x| String::from_utf8_lossy(&x.tag).to_string()).collect::<Vec<_>>())).unwrap_or_else(|e| format!("ERR {e}")),
            "anm" => Motion::parse(&b[e.offset..]).map(|m| format!("{:>12} frames {} main {} loop {} tracks {}", m.name, m.last_frame(), m.is_main(), m.is_loop(), m.tracks.len())).unwrap_or_else(|e| format!("ERR {e}")),
            _ => String::new(),
        };
        println!("{i:3} {k:5} off={:#x} {extra}", e.offset);
    }
}
