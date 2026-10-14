use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::sjis;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(std::env::var("SH2_DISC_DIR").unwrap()).unwrap();
    let raw = d.read(&a[1]).expect("file");
    let count = u32::from_le_bytes(raw[0..4].try_into().unwrap()) as usize;
    let total = u32::from_le_bytes(raw[4..8].try_into().unwrap()) as usize;
    println!("count {count} total {total} len {}", raw.len());
    let offs: Vec<(String, usize)> = (0..count).map(|i| (String::from_utf8_lossy(&raw[8+i*8..8+i*8+4]).to_string(), u32::from_le_bytes(raw[8+i*8+4..8+i*8+8].try_into().unwrap()) as usize)).collect();
    for i in 0..count {
        let end = offs.get(i+1).map(|x| x.1).unwrap_or(total);
        let len = end - offs[i].1;
        println!("sec {i} tag {:?} off {:#x} len {:#x}", offs[i].0, offs[i].1, len);
    }
    if a.len() > 3 {
        let sec: usize = a[2].parse().unwrap(); let stride: usize = a[3].parse().unwrap();
        let n: usize = a.get(4).and_then(|s| s.parse().ok()).unwrap_or(10);
        let end = offs.get(sec+1).map(|x| x.1).unwrap_or(total);
        let s = &raw[offs[sec].1..end];
        for i in 0..(s.len()/stride).min(n) {
            let r = &s[i*stride..(i+1)*stride];
            let e = r.iter().position(|&c| c==0).unwrap_or(r.len());
            println!("[{i}] {}", sjis::decode(&r[..e]));
        }
    }
}
