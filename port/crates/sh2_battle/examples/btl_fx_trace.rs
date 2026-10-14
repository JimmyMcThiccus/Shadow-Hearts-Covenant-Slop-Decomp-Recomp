//! Developer tool: run an EFFECT/*.EFD program with a logging host and print every system call (+args).
use sh2_core::fileio::Disc;
use sh2_gfx::effects::efmg::{kind, Efmg, Heco};
use sh2_script::opcodes::VEC_FUNC_TABLE;
use sh2_script::vsm::{Machine, SysCalls, Vec3};
struct H {
    frame: u32,
    log: Vec<String>,
    counts: std::collections::BTreeMap<&'static str, u32>,
}
impl SysCalls for H {
    fn syscall(&mut self, vm: &mut Vec3<'_>, id: i32, args: &[u32]) {
        let name = VEC_FUNC_TABLE.iter().find(|f| f.id == id).map(|f| f.name).unwrap_or("?");
        *self.counts.entry(name).or_default() += 1;
        let a: Vec<String> = args.iter().map(|&o| format!("{:#x}/{:.2}", vm.read_i32(o), vm.read_f32(o))).collect();
        if self.log.len() < 400 {
            self.log.push(format!("f{:3} {id} {name}({})", self.frame, a.join(", ")));
        }
        match id {
            200 => vm.wait_frame(),
            2006 => vm.write_u32(args[1], 1),
            1304 | 1310 | 1306 => {
                if args.len() > 1 {
                    vm.write_u32(args[1], 1)
                }
            }
            1132 => vm.write_u32(args[0], 1),
            _ => {}
        }
    }
    fn frame_begin(&mut self) {
        self.frame += 1;
    }
    fn print(&mut self, s: &str) {
        self.log.push(format!("PRINT {s}"));
    }
}
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).unwrap();
    let name = &a[2];
    let b = d.read(&format!("EFFECT/{name}.EFD")).unwrap();
    let efmg = Efmg::parse(&b).unwrap();
    let (_, sec) = efmg.iter_kind(kind::CODE).next().unwrap();
    let heco = Heco::parse(sec).unwrap();
    let mut m = Machine::new(&heco);
    let mut h = H { frame: 0, log: vec![], counts: Default::default() };
    let max: u32 = a.get(3).and_then(|s| s.parse().ok()).unwrap_or(600);
    let mut frames = 0;
    while m.frame(&mut h) && frames < max {
        frames += 1;
    }
    for l in &h.log {
        println!("{l}");
    }
    println!("frames {frames} finished {} threads {}", m.finished, m.threads.len());
    for (k, v) in &h.counts {
        println!("  {k}: {v}");
    }
}
