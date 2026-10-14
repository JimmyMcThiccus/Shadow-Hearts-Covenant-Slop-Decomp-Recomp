//! `mpeg2_check <stream.m2v> [ref.yuv] [max_frames]` : decode an MPEG-2 elementary stream with `sh2_gfx::ipu::mpeg2` and
//! (optionally) compare every frame with a raw yuv420p dump made by `ffmpeg -i x.m2v -f rawvideo -pix_fmt yuv420p ref.yuv`.
use sh2_gfx::ipu::mpeg2::Mpeg2Decoder;
use std::io::Read;

fn main() {
    let a: Vec<String> = std::env::args().collect();
    let data = std::fs::read(&a[1]).unwrap();
    let mut reff = a.get(2).filter(|s| *s != "-").map(|p| std::fs::File::open(p).unwrap());
    let max: usize = a.get(3).and_then(|s| s.parse().ok()).unwrap_or(usize::MAX);
    let mut dec = Mpeg2Decoder::new(&data);
    let t0 = std::time::Instant::now();
    let mut n = 0usize;
    let mut worst = 100.0f64;
    let mut types = [0usize; 4];
    while n < max {
        match dec.next_frame() {
            Ok(Some(f)) => {
                types[f.picture_type as usize] += 1;
                if let Some(rf) = reff.as_mut() {
                    let (w, h) = (f.width, f.height);
                    let mut buf = vec![0u8; w * h * 3 / 2];
                    if rf.read_exact(&mut buf).is_err() {
                        println!("reference ended at frame {n}");
                        break;
                    }
                    let mut se = 0f64;
                    for y in 0..h {
                        for x in 0..w {
                            let d = f.y[y * f.stride + x] as f64 - buf[y * w + x] as f64;
                            se += d * d;
                        }
                    }
                    for (plane, off) in [(&f.cb, w * h), (&f.cr, w * h + w * h / 4)] {
                        for y in 0..h / 2 {
                            for x in 0..w / 2 {
                                let d = plane[y * (f.stride / 2) + x] as f64 - buf[off + y * (w / 2) + x] as f64;
                                se += d * d;
                            }
                        }
                    }
                    let mse = se / (w * h * 3 / 2) as f64;
                    let psnr = if mse == 0.0 { 99.0 } else { 10.0 * (255.0f64 * 255.0 / mse).log10() };
                    if psnr < 98.0 {
                        let mut bad = vec![];
                        for my in 0..h / 16 {
                            for mx in 0..w / 16 {
                                let mut diff = 0;
                                for y in 0..16 {
                                    for x in 0..16 {
                                        if f.y[(my * 16 + y) * f.stride + mx * 16 + x] != buf[(my * 16 + y) * w + mx * 16 + x] {
                                            diff += 1;
                                        }
                                    }
                                }
                                if diff > 0 {
                                    bad.push((mx, my, diff));
                                }
                            }
                        }
                        println!("  {} bad MBs (luma): first {:?}", bad.len(), &bad[..bad.len().min(12)]);
                    }
                    if psnr < worst {
                        worst = psnr;
                    }
                    if n < 2 || psnr < 98.0 {
                        println!("frame {n} type {} tr {} psnr {psnr:.2}", f.picture_type, f.temporal_reference);
                    }
                }
                n += 1;
            }
            Ok(None) => break,
            Err(e) => {
                println!("error after {n} frames: {e} ({})", dec.debug_state());
                break;
            }
        }
    }
    println!("{n} frames in {:.2}s ({:.1} fps), I/P/B = {}/{}/{}, worst psnr {worst:.2}, format {:?}", t0.elapsed().as_secs_f32(), n as f32 / t0.elapsed().as_secs_f32(), types[1], types[2], types[3], dec.format());
}
