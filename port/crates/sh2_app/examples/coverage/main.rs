//! Whole-game coverage harness (round 5 QA): what of the retail US game (SLUS_210.41, `SH2_US_DISC_DIR`) the port cannot do yet.
//!
//! ```text
//! cargo run --release -p sh2_app --example coverage -- all            # every check (resumes; --fresh starts over), then the report
//! cargo run --release -p sh2_app --example coverage -- run field      # one category (field fx battle battleapp party lsd msd story)
//! cargo run --release -p sh2_app --example coverage -- report         # tools/coverage/out/*.tsv -> notes/integration/coverage.md
//! options: --jobs N (worker processes per category; default 6 or SH2_COV_JOBS), --out DIR (default tools/coverage/out), --only NAME, --fresh, --ticks N (start function), --ev-ticks N, --arg1 (field events with argument 1 only; default: 1, 2 and 4)
//! ```
//!
//! Each category runs in a worker process (`worker <cat>`) with a per-item watchdog: an item that hangs is written as `timeout` and the
//! worker is restarted, skipping what is already in `<out>/<cat>.tsv`.

mod battle;
mod battleapp;
mod common;
mod field;
mod fx;
mod lsd;
mod msd;
mod party;
mod report;
mod srcscan;
mod story;

use std::path::PathBuf;

/// default worker processes per category (override: `--jobs N` / `SH2_COV_JOBS=N`)
const MAX_JOBS: usize = 6;

pub const CATS: &[&str] = &["field", "fx", "battle", "battleapp", "party", "lsd", "msd", "story"];

fn main() {
    let a: Vec<String> = std::env::args().collect();
    let get = |k: &str| a.iter().position(|x| x == k).and_then(|i| a.get(i + 1)).cloned();
    let has = |k: &str| a.iter().any(|x| x == k);
    let out = get("--out").map(PathBuf::from).unwrap_or_else(default_out);
    let only = get("--only");
    let fresh = has("--fresh");
    let cmd = a.get(1).cloned().unwrap_or_else(|| "all".into());
    sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    if std::env::var_os("SH2_US_DISC_DIR").is_none() {
        eprintln!("SH2_US_DISC_DIR is not set (the US retail disc folder)");
        std::process::exit(2);
    }
    // every crate reads "the disc" from SH2_DISC_DIR; the retail run points it at the US folder (as sh2_app --us does)
    std::env::set_var("SH2_DISC_DIR", std::env::var_os("SH2_US_DISC_DIR").unwrap());
    std::env::set_var("SH2_CUTSCENE", "off");
    // disc 2 (later cut scenes): attached by sh2_core::fileio::Disc::open when SH2_US_DISC2_DIR names it
    if std::env::var_os("SH2_US_DISC2_DIR").is_none() {
        if let Some(d2) = common::disc2_dir() {
            std::env::set_var("SH2_US_DISC2_DIR", d2);
        }
    }
    match cmd.as_str() {
        "worker" => {
            common::init_logger();
            common::install_panic_hook();
            let cat = a.get(2).cloned().expect("worker <cat>");
            if let Some((k, n)) = get("--shard").and_then(|v| v.split_once('/').map(|(k, n)| (k.parse().unwrap_or(0), n.parse().unwrap_or(1)))) {
                *common::SHARD.lock().unwrap() = (k, n);
            }
            common::start_watchdog(match cat.as_str() {
                "field" | "story" => "FS",
                "fx" => "FX",
                "battle" | "battleapp" => "BE",
                "party" => "BP",
                "lsd" => "CS",
                "msd" => "MN",
                _ => "QA",
            });
            let ticks: u32 = get("--ticks").and_then(|v| v.parse().ok()).unwrap_or(3000);
            let ev_ticks: u32 = get("--ev-ticks").and_then(|v| v.parse().ok()).unwrap_or(3000);
            match cat.as_str() {
                "field" => field::run_all(&out, fresh, only.as_deref(), ticks, ev_ticks, !has("--arg1")),
                "fx" => fx::run_all(&out, fresh, only.as_deref()),
                "battle" => battle::run_all(&out, fresh, only.as_deref()),
                "battleapp" => battleapp::run_all(&out, fresh, only.as_deref()),
                "party" => party::run_all(&out, fresh, only.as_deref()),
                "lsd" => lsd::run_all(&out, fresh, only.as_deref(), has("--decode-movies")),
                "msd" => msd::run_all(&out, fresh, only.as_deref()),
                "story" => story::run_all(&out, fresh, only.as_deref()),
                c => {
                    eprintln!("coverage: unknown category {c}; categories: {}", CATS.join(" "));
                    std::process::exit(2);
                }
            }
        }
        "run" | "all" => {
            let cats: Vec<String> = if cmd == "all" { CATS.iter().map(|s| s.to_string()).collect() } else { a[2..].iter().take_while(|x| !x.starts_with("--")).cloned().collect() };
            // fail fast (before any worker starts or coverage.md is rewritten) on an unknown / missing category
            let bad: Vec<&String> = cats.iter().filter(|c| !CATS.contains(&c.as_str())).collect();
            if cats.is_empty() || !bad.is_empty() {
                eprintln!("coverage: unknown category {bad:?} (or none given); categories: {}", CATS.join(" "));
                std::process::exit(2);
            }
            let mut pass: Vec<String> = a.iter().skip(2).skip_while(|x| !x.starts_with("--")).cloned().collect();
            // --jobs N: parallel shards per category (default by category)
            let jobs_arg: Option<usize> = get("--jobs").and_then(|v| v.parse().ok());
            let env_jobs: Option<usize> = std::env::var("SH2_COV_JOBS").ok().and_then(|v| v.parse().ok());
            if let Some(i) = pass.iter().position(|x| x == "--jobs") {
                pass.drain(i..(i + 2).min(pass.len()));
            }
            pass.retain(|p| p != "--fresh");
            for cat in cats {
                let t0 = std::time::Instant::now();
                if fresh {
                    for f in common::cat_files(&out, &cat) {
                        let _ = std::fs::remove_file(f);
                    }
                }
                // worker processes per category: `--jobs N`, else `SH2_COV_JOBS`, else at most MAX_JOBS (6: the machine is shared by
                // several agents; round 5 ran 20 field workers)
                let jobs = jobs_arg.or(env_jobs).unwrap_or(match cat.as_str() {
                    "field" | "battle" | "party" | "battleapp" | "lsd" => MAX_JOBS,
                    _ => 1,
                }).max(1);
                let exe = std::env::current_exe().unwrap();
                let handles: Vec<_> = (0..jobs)
                    .map(|k| {
                        let (exe, out, cat, pass) = (exe.clone(), out.clone(), cat.clone(), pass.clone());
                        std::thread::spawn(move || {
                            let stem = if jobs > 1 { format!("{cat}.s{k}") } else { cat.clone() };
                            for attempt in 0..400 {
                                let mut c = std::process::Command::new(&exe);
                                c.arg("worker").arg(&cat).arg("--out").arg(&out).arg("--shard").arg(format!("{k}/{jobs}"));
                                c.args(&pass);
                                let st = c.status().expect("spawn worker");
                                match st.code() {
                                    Some(0) => break,
                                    Some(3) => eprintln!("coverage: {stem}: worker restarted after a timeout (attempt {attempt})"),
                                    Some(2) => {
                                        eprintln!("coverage: {stem}: worker usage error; not retrying");
                                        break;
                                    }
                                    other => {
                                        // a crash that is not a panic (stack overflow, abort): note the item that was running and go on
                                        eprintln!("coverage: {stem}: worker died ({other:?}); restarting");
                                        common::note_crash(&out, &stem, other);
                                    }
                                }
                            }
                        })
                    })
                    .collect();
                for h in handles {
                    let _ = h.join();
                }
                eprintln!("coverage: {cat} done in {:.0}s", t0.elapsed().as_secs_f32());
            }
            report::write(&out, &report_for(&out));
        }
        "report" => report::write(&out, &report_for(&out)),
        c => {
            eprintln!("unknown command {c}");
            std::process::exit(2);
        }
    }
}

fn root() -> PathBuf {
    // port/crates/sh2_app -> repository root
    PathBuf::from(env!("CARGO_MANIFEST_DIR")).join("../../..")
}
fn default_out() -> PathBuf {
    root().join("tools/coverage/out")
}
/// notes/integration/coverage.md for the default output folder, `<out>/coverage.md` for any other (test runs)
fn report_for(out: &std::path::Path) -> PathBuf {
    if std::fs::canonicalize(out).ok() == std::fs::canonicalize(default_out()).ok() {
        report_path()
    } else {
        out.join("coverage.md")
    }
}
fn report_path() -> PathBuf {
    root().join("notes/integration/coverage.md")
}
