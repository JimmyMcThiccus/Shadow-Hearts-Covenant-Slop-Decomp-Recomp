fn main() {
    let dir = std::env::var("SH2_DISC_DIR").unwrap();
    let d = sh2_menu::disc::DiscDir::open(dir).unwrap();
    let bank = sh2_menu::gamefont::FontBank::load(&d);
    let f = bank.get(0).unwrap();
    for ch in ['ア', 'テ'] {
        let raw = f.debug_raw(ch);
        println!("{ch} {} bytes {:02x?}", raw.len(), &raw[..]);
        for stride in [17usize, 18, 19, 20, 21, 22] {
            println!("stride {stride}");
            for y in 0..(400 / stride).min(22) {
                let row: String = (0..stride).map(|x| { let i = y * stride + x; let b = raw.get(i / 4).copied().unwrap_or(0); let l = (b >> ((i & 3) * 2)) & 3; if l == 0 { '.' } else { '#' } }).collect();
                println!("{row}");
            }
        }
    }
}
