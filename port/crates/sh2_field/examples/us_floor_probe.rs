//! PINE helper: ASCII map of the walkable floor of a (US) map around a point, and floor queries.
//! usage: us_floor_probe [--us] MAP ENTRY cx cz half step      (prints '#'=circle_chk(4) ok, '.'=floor only, ' '=void)
//!        us_floor_probe [--us] MAP ENTRY q x y z [x y z ...]   (floor y / circle_chk per point)
use sh2_field::sim::FieldSim;
use sh2_gfx::bevy::Sh2Disc;

fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let v: Vec<&String> = a.iter().skip(1).filter(|x| !x.starts_with("--")).collect();
    let disc = Sh2Disc::from_env(us).unwrap();
    let map = v[0].as_str();
    let entry: i32 = v[1].parse().unwrap();
    let bytes = disc.read(&format!("FIELD/MPS/{map}.MPS")).unwrap();
    let mut sim = FieldSim::new(map, bytes, entry).unwrap();
    println!("start pos {:?} yaw {:.4} enc rate {}", sim.player.pos, sim.player.yaw, sim.enc.rate);
    let fl = sim.field.floor.as_mut().unwrap();
    println!("world {:?} tris {}", fl.data.world, fl.data.triangles.len());
    if v[2] == "q" {
        for c in v[3..].chunks(3) {
            let p: Vec<f32> = c.iter().map(|s| s.parse().unwrap()).collect();
            let pos = [p[0], p[1], p[2]];
            let t = fl.on_floor_chk(pos);
            let y = t.map(|t| fl.on_floor_point(pos, t));
            println!("{:?}: tri {:?} floor_y {:?} circle4 {}", pos, t, y, fl.circle_chk(pos, 4.0).is_some());
        }
        return;
    }
    let cx: f32 = v[2].parse().unwrap();
    let cz: f32 = v[3].parse().unwrap();
    let half: f32 = v[4].parse().unwrap();
    let step: f32 = v[5].parse().unwrap();
    let mut z = cz + half;
    while z >= cz - half {
        let mut row = String::new();
        let mut x = cx - half;
        while x <= cx + half {
            let p = [x, std::env::var("PROBE_Y").ok().and_then(|s| s.parse().ok()).unwrap_or(0.0), z];
            // find the floor y from the slice query at a guessed height: on_floor_chk ignores y?
            let ch = if fl.circle_chk(p, 4.0).is_some() { '#' } else if fl.on_floor_chk(p).is_some() { '.' } else { ' ' };
            row.push(ch);
            x += step;
        }
        println!("{:8.1} {}", z, row);
        z -= step;
    }
}
