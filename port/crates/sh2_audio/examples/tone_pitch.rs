use sh2_audio::Bank;
use sh2_core::fileio::Disc;
fn main() {
    let disc = Disc::from_env().unwrap();
    let a: Vec<String> = std::env::args().skip(1).collect();
    let bank = Bank::parse(&disc.read(&a[0]).unwrap()).unwrap();
    for (i, t) in bank.tones.iter().enumerate() {
        let Some(w) = bank.waves.get(t.wave() as usize) else { continue };
        let pcm: Vec<f32> = w.pcm.iter().map(|&x| x as f32).collect();
        if pcm.len() < 6000 {
            continue;
        }
        // analyse the loop region if there is one, else the middle
        let start = w.loop_start.unwrap_or(pcm.len() / 3).min(pcm.len() - 5000);
        let n = 2500.min(pcm.len() - start - 2500);
        let seg = &pcm[start..start + n + 2500];
        let r0: f32 = seg[..n].iter().map(|x| x * x).sum();
        if r0 < 1.0 {
            continue;
        }
        let root = 440.0 * 2f32.powf((t.root_key() as f32 - 69.0) / 12.0);
        // lags corresponding to roots 4 octaves down .. 2 up
        let mut best = (0.0f32, 0usize);
        let lo = (w.rate as f32 / (root * 4.0)) as usize;
        let hi = ((w.rate as f32 / (root / 4.0)) as usize).min(2400);
        let mut vals = vec![0.0f32; hi + 2];
        for lag in lo.max(8)..hi {
            let r: f32 = (0..n).map(|k| seg[k] * seg[k + lag]).sum::<f32>() / r0;
            vals[lag] = r;
            if r > best.0 {
                best = (r, lag);
            }
        }
        // first strong peak
        let mut lagp = best.1;
        for lag in lo.max(9)..hi - 1 {
            if vals[lag] > 0.85 * best.0 && vals[lag] >= vals[lag - 1] && vals[lag] >= vals[lag + 1] {
                lagp = lag;
                break;
            }
        }
        let f = w.rate as f32 / lagp as f32;
        println!("tone {i:3} wave {:3} rate {:5} root {:3} ({:6.1} Hz) native f0 {:7.1} Hz ratio {:5.2}  conf {:.2} | b2={:02x} b3={:02x} b5={:02x} b6={:02x} b7={:02x}", t.wave(), w.rate, t.root_key(), root, f, f / root, best.0, t.raw[2], t.raw[3], t.raw[5], t.raw[6], t.raw[7]);
    }
}
