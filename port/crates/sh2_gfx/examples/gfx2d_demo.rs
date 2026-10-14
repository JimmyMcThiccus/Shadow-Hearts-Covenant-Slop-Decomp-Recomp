//! Draws a synthetic 2D `GfxFrame` (frame border, a textured sprite from an uploaded CT32 image, an additive and an alpha-blended quad) through the
//! 512 x 448 virtual frame buffer: `cargo run -p sh2_gfx --example gfx2d_demo -- --shot out.png [--size WxH]`; `SH2_SCREEN=native|letterbox` changes the presentation.
use bevy::prelude::*;
use bevy::window::WindowResolution;
use sh2_gfx::bevy::capture::{ScreenshotJob, ScreenshotPlugin};
use sh2_gfx::bevy::gfx2d::Gfx2dPlugin;
use sh2_gfx::gs::{Alpha, BitBltBuf, BlendKind, ImageUpload, Test, TrxPos, Vertex};
use sh2_gfx::renderer::{GfxFrame, RenderBatch, Sh2GfxPlugin, TexKey};

fn v(x: f32, y: f32, u: f32, w: f32, rgba: [u8; 4]) -> Vertex {
    Vertex { x, y, z: 0, rgba, u, v: w, q: 1.0, fog: 0 }
}

fn quad(x0: f32, y0: f32, x1: f32, y1: f32, uv: (f32, f32), rgba: [u8; 4]) -> [[Vertex; 3]; 2] {
    let (a, b, c, d) = (v(x0, y0, 0.0, 0.0, rgba), v(x1, y0, uv.0, 0.0, rgba), v(x0, y1, 0.0, uv.1, rgba), v(x1, y1, uv.0, uv.1, rgba));
    [[a, c, b], [b, c, d]]
}

fn setup(mut frame: ResMut<GfxFrame>, mut commands: Commands) {
    // the replay camera does not clear (it draws over the 3D scene): something must clear the target every frame
    commands.spawn((Camera3d::default(), Camera { order: -10, ..default() }));
    // 16 x 16 checker texture, CT32, GS alpha 0x80 = opaque
    let mut data = Vec::new();
    for y in 0..16 {
        for x in 0..16 {
            let on = (x / 4 + y / 4) % 2 == 0;
            data.extend_from_slice(&if on { [255u8, 200, 40, 0x80] } else { [40, 60, 200, 0x80] });
        }
    }
    frame.uploads.push(ImageUpload {
        bitbltbuf: BitBltBuf { sbp: 0, sbw: 0, spsm: 0, dbp: 0x2000, dbw: 1, dpsm: 0 },
        pos: TrxPos { ssax: 0, ssay: 0, dsax: 0, dsay: 0, dir: 0 },
        rrw: 16,
        rrh: 16,
        data,
    });
    let white = [0x80, 0x80, 0x80, 0x80];
    let mut batches = Vec::new();
    // frame border: 4 px bars on the 512 x 448 edge (opaque)
    let mut border = Vec::new();
    for (x0, y0, x1, y1) in [(0.0, 0.0, 512.0, 4.0), (0.0, 444.0, 512.0, 448.0), (0.0, 0.0, 4.0, 448.0), (508.0, 0.0, 512.0, 448.0)] {
        border.extend(quad(x0, y0, x1, y1, (0.0, 0.0), [0x80, 0x10, 0x10, 0x80]));
    }
    let base = |tex: Option<TexKey>, blend: BlendKind, fst: bool, tris| RenderBatch { texture: tex, blend, alpha: Alpha::default(), test: Test::from_bits(0), target_block: 0, fst, gouraud: true, tris };
    batches.push(base(None, BlendKind::Other, true, border));
    // textured sprite, 3x magnified, at (64, 64)
    let key = TexKey { tbp0: 0x2000, tbw: 1, psm: 0, tw: 4, th: 4, cbp: 0, cpsm: 0, csa: 0 };
    batches.push(base(Some(key), BlendKind::Other, true, quad(64.0, 64.0, 112.0, 112.0, (16.0, 16.0), white).to_vec()));
    // alpha-blended translucent green square overlapping it
    batches.push(base(None, BlendKind::AlphaBlend, true, quad(90.0, 90.0, 170.0, 150.0, (0.0, 0.0), [0x10, 0x80, 0x20, 0x40]).to_vec()));
    // additive quad
    batches.push(base(None, BlendKind::Additive, true, quad(120.0, 70.0, 200.0, 120.0, (0.0, 0.0), [0x60, 0x20, 0x10, 0x60]).to_vec()));
    // blend ramp: white quads with GS alpha 0x10..0x80 over black (alpha blend), second row additive, along y = 300 / 360
    for k in 0..8u8 {
        let a = 0x10 * (k + 1);
        let x0 = 20.0 + k as f32 * 50.0;
        batches.push(base(None, BlendKind::AlphaBlend, true, quad(x0, 300.0, x0 + 40.0, 340.0, (0.0, 0.0), [0x80, 0x80, 0x80, a]).to_vec()));
        batches.push(base(None, BlendKind::Additive, true, quad(x0, 360.0, x0 + 40.0, 400.0, (0.0, 0.0), [0x40, 0x40, 0x40, a]).to_vec()));
    }
    if std::env::var_os("RAMP_ONLY").is_some() {
        batches.drain(..4);
    }
    frame.batches = batches;
    frame.frame_index = 1;
}

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let mut shot = None;
    let mut size = (1024u32, 768u32);
    let mut i = 0;
    while i < a.len() {
        match a[i].as_str() {
            "--shot" => {
                shot = a.get(i + 1).cloned();
                i += 1;
            }
            "--size" => {
                if let Some((w, h)) = a.get(i + 1).and_then(|s| s.split_once('x')) {
                    size = (w.parse().unwrap_or(1024), h.parse().unwrap_or(768));
                }
                i += 1;
            }
            _ => {}
        }
        i += 1;
    }
    let mut app = App::new();
    app.add_plugins(DefaultPlugins.set(WindowPlugin { primary_window: Some(Window { title: "gfx2d demo".into(), resolution: WindowResolution::new(size.0, size.1), ..default() }), ..default() }))
        .add_plugins((Sh2GfxPlugin, Gfx2dPlugin))
        .insert_resource(ClearColor(Color::BLACK))
        .add_systems(Startup, setup);
    if let Some(p) = shot {
        app.add_plugins(ScreenshotPlugin).insert_resource(ScreenshotJob { path: p.into(), after_frames: 20, exit_when_done: true });
    }
    app.run();
}
