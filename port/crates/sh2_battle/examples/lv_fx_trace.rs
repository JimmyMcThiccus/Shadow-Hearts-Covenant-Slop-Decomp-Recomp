//! Round 5b LV: raw syscall trace of an EFFECT program with `chrGetGTCount` answering N (default 4), no log cap.
//! `lv_fx_trace <name e.g. 080_00> [n] [frames]`
use sh2_core::fileio::Disc;
use sh2_gfx::effects::efmg::{kind, Efmg, Heco};
use sh2_script::opcodes::VEC_FUNC_TABLE;
use sh2_script::vsm::{Machine, SysCalls, Vec3};
struct H {
    frame: u32,
    n: i32,
}
impl SysCalls for H {
    fn syscall(&mut self, vm: &mut Vec3<'_>, id: i32, args: &[u32]) {
        let name = VEC_FUNC_TABLE.iter().find(|f| f.id == id).map(|f| f.name).unwrap_or("?");
        match id {
            200 => vm.wait_frame(),
            1401 => {
                if let Some(&o) = args.last() {
                    vm.write_u32(o, self.n as u32)
                }
            }
            2006 => vm.write_u32(args[1], 1),
            1304 | 1310 | 1306 => {
                if args.len() > 1 {
                    vm.write_u32(args[1], 1)
                }
            }
            1132 => vm.write_u32(args[0], 1),
            _ => {}
        }
        if id != 200 && id != 1500 && id != 1501 {
            let a: Vec<String> = args.iter().map(|&o| format!("{:#x}/{:.3}", vm.read_i32(o), vm.read_f32(o))).collect();
            println!("f{:3} {id} {name}({})", self.frame, a.join(", "));
        }
    }
    fn frame_begin(&mut self) {
        self.frame += 1;
    }
    fn print(&mut self, s: &str) {
        println!("PRINT {s}");
    }
}
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(std::env::var("SH2_US_DISC_DIR").unwrap()).unwrap();
    let b = d.read(&format!("EFFECT/{}.EFD", a[1])).unwrap();
    let efmg = Efmg::parse(&b).unwrap();
    let (_, sec) = efmg.iter_kind(kind::CODE).next().unwrap();
    let heco = Heco::parse(sec).unwrap();
    let mut m = Machine::new(&heco);
    let mut h = H { frame: 0, n: a.get(2).and_then(|s| s.parse().ok()).unwrap_or(4) };
    let max: u32 = a.get(3).and_then(|s| s.parse().ok()).unwrap_or(400);
    let mut frames = 0;
    while m.frame(&mut h) && frames < max {
        frames += 1;
    }
    println!("frames {frames}");
}
