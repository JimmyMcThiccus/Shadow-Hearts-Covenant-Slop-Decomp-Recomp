//! dev tool: which texture columns / rows of an attach texture have any opaque pixel (`col_profile <disc> <path> <attach path>`)
use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::msd::Msd;
use sh2_gfx::texture::decode_menu_texture;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(&a[1]).unwrap();
    let mut data = d.read(&a[2]).expect("file");
    for idx in a[3].split('/').filter(|s| !s.is_empty()) {
        let m = Msd::parse(data.clone()).unwrap();
        let at = &m.attach_files()[idx.parse::<usize>().unwrap()];
        data = data[at.offset as usize..(at.offset + at.size) as usize].to_vec();
    }
    let img = decode_menu_texture(&data, 0).unwrap();
    println!("{}x{}", img.width, img.height);
    for (name, n, m, f) in [("cols", img.width, img.height, true), ("rows", img.height, img.width, false)] {
        let mut runs = Vec::new(); let mut start: Option<u32> = None;
        for i in 0..=n {
            let any = i < n && (0..m).any(|j| { let (x, y) = if f { (i, j) } else { (j, i) }; img.px(x, y)[3] > 0 });
            match (any, start) { (true, None) => start = Some(i), (false, Some(s)) => { runs.push((s, i - 1)); start = None; } _ => {} }
        }
        println!("{name}: {:?}", runs);
    }
}
