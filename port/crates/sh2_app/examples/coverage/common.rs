//! Shared plumbing of the coverage harness: result rows, a capturing logger, panic capture and a per-item watchdog.
//!
//! Every check writes one row per item into `<out>/<category>.tsv` (appended + flushed at once, so a crash or a hang loses nothing).
//! A worker process that hangs on an item is killed by its own watchdog after writing a `timeout` row; the driver restarts the
//! worker, which skips every item already in the file (resume).

use std::collections::{BTreeMap, HashSet};
use std::io::Write;
use std::path::{Path, PathBuf};
use std::sync::atomic::{AtomicU64, Ordering};
use std::sync::Mutex;
use std::time::{Duration, Instant};

/// One row of the matrix.
#[derive(Clone, Debug, Default)]
pub struct Row {
    pub id: String,
    /// ok / fails / stub / untested / timeout
    pub status: String,
    /// failing op / panic / short summary
    pub detail: String,
    /// FS / BP / BE / FX / MN / CS / QA / - (data)
    pub owner: String,
    /// machine-readable extras `key=value;key=value` (counts, ops list, edges ...)
    pub extra: String,
}

impl Row {
    pub fn new(id: impl Into<String>) -> Self {
        Row { id: id.into(), status: "ok".into(), ..Default::default() }
    }
    pub fn to_line(&self) -> String {
        format!("{}\t{}\t{}\t{}\t{}\n", esc(&self.id), esc(&self.status), esc(&self.detail), esc(&self.owner), esc(&self.extra))
    }
    pub fn parse(line: &str) -> Option<Row> {
        let f: Vec<&str> = line.trim_end_matches(['\n', '\r']).split('\t').collect();
        if f.len() < 5 {
            return None;
        }
        Some(Row { id: unesc(f[0]), status: unesc(f[1]), detail: unesc(f[2]), owner: unesc(f[3]), extra: unesc(f[4]) })
    }
    pub fn get(&self, key: &str) -> Option<&str> {
        self.extra.split(';').find_map(|kv| kv.strip_prefix(key).and_then(|r| r.strip_prefix('=')))
    }
    /// rank: fails > timeout > stub > untested > ok
    pub fn worse(&mut self, status: &str) {
        let rank = |s: &str| match s {
            "fails" => 4,
            "timeout" => 3,
            "stub" => 2,
            "untested" => 1,
            _ => 0,
        };
        if rank(status) > rank(&self.status) {
            self.status = status.to_string();
        }
    }
    pub fn add_detail(&mut self, s: impl AsRef<str>) {
        let s = s.as_ref();
        if s.is_empty() {
            return;
        }
        if !self.detail.is_empty() {
            self.detail.push_str("; ");
        }
        self.detail.push_str(s);
    }
    pub fn add_owner(&mut self, o: &str) {
        if o.is_empty() || self.owner.split('/').any(|x| x == o) {
            return;
        }
        if !self.owner.is_empty() {
            self.owner.push('/');
        }
        self.owner.push_str(o);
    }
    pub fn kv(&mut self, k: &str, v: impl std::fmt::Display) {
        if !self.extra.is_empty() {
            self.extra.push(';');
        }
        self.extra.push_str(&format!("{k}={v}"));
    }
}

fn esc(s: &str) -> String {
    s.replace('\\', "\\\\").replace('\t', "\\t").replace('\n', "\\n").replace('\r', "")
}
fn unesc(s: &str) -> String {
    let mut o = String::new();
    let mut it = s.chars();
    while let Some(c) = it.next() {
        if c == '\\' {
            match it.next() {
                Some('t') => o.push('\t'),
                Some('n') => o.push('\n'),
                Some(x) => o.push(x),
                None => {}
            }
        } else {
            o.push(c);
        }
    }
    o
}

pub fn read_rows(path: &Path) -> Vec<Row> {
    std::fs::read_to_string(path).map(|s| s.lines().filter_map(Row::parse).collect()).unwrap_or_default()
}

/// Appends rows to `<out>/<cat>.tsv` (one flush per row).
pub struct Sink {
    file: std::fs::File,
    pub done: HashSet<String>,
}

/// `--shard k/n` of this worker (items `i` with `i % n == k`)
pub static SHARD: Mutex<(usize, usize)> = Mutex::new((0, 1));
static ITEM_NO: AtomicU64 = AtomicU64::new(0);

/// True when the next item belongs to this worker's shard (call once per item, in a fixed order).
pub fn mine() -> bool {
    let i = ITEM_NO.fetch_add(1, Ordering::Relaxed) as usize;
    let (k, n) = *SHARD.lock().unwrap();
    i % n == k
}

/// Every row file of a category (`cat.tsv` and the shard files `cat.sK.tsv`).
pub fn cat_files(out: &Path, cat: &str) -> Vec<PathBuf> {
    let mut v = vec![];
    if let Ok(rd) = std::fs::read_dir(out) {
        for e in rd.flatten() {
            let n = e.file_name().to_string_lossy().to_string();
            if n == format!("{cat}.tsv") || (n.starts_with(&format!("{cat}.s")) && n.ends_with(".tsv")) {
                v.push(e.path());
            }
        }
    }
    v.sort();
    v
}

impl Sink {
    pub fn open(out: &Path, cat: &str, fresh: bool) -> Sink {
        std::fs::create_dir_all(out).unwrap();
        let (k, n) = *SHARD.lock().unwrap();
        let path = if n > 1 { out.join(format!("{cat}.s{k}.tsv")) } else { out.join(format!("{cat}.tsv")) };
        if fresh {
            let _ = std::fs::remove_file(&path);
        }
        let done = read_rows(&path).into_iter().map(|r| r.id).collect();
        let file = std::fs::OpenOptions::new().create(true).append(true).open(&path).unwrap();
        *SINK_PATH.lock().unwrap() = Some(path);
        Sink { file, done }
    }
    pub fn put(&mut self, r: &Row) {
        self.file.write_all(r.to_line().as_bytes()).unwrap();
        self.file.flush().unwrap();
        self.done.insert(r.id.clone());
    }
}

// ------------------------------------------------------------------------------------------------------------------------------
// logger: keeps warn / error lines of the current item
// ------------------------------------------------------------------------------------------------------------------------------

static LOG: Mutex<Vec<String>> = Mutex::new(Vec::new());
struct Capture;
impl log::Log for Capture {
    fn enabled(&self, m: &log::Metadata) -> bool {
        m.level() <= log::Level::Warn || (m.level() <= log::Level::Debug && DEBUG_TOO.load(Ordering::Relaxed) != 0)
    }
    fn log(&self, r: &log::Record) {
        if !self.enabled(r.metadata()) {
            return;
        }
        let mut l = LOG.lock().unwrap();
        if l.len() < 4000 {
            l.push(format!("{} {}", r.level(), r.args()));
        }
    }
    fn flush(&self) {}
}
static CAPTURE: Capture = Capture;
pub static DEBUG_TOO: AtomicU64 = AtomicU64::new(0);

pub fn init_logger() {
    let _ = log::set_logger(&CAPTURE);
    log::set_max_level(log::LevelFilter::Debug);
}

/// warn / error lines logged since the last call, collapsed (`line xN`)
pub fn take_log() -> Vec<(String, usize)> {
    let v = std::mem::take(&mut *LOG.lock().unwrap());
    let mut m: BTreeMap<String, usize> = BTreeMap::new();
    for l in v {
        // numbers vary between calls: collapse them so that the same message counts once
        *m.entry(l).or_default() += 1;
    }
    let mut out: Vec<(String, usize)> = m.into_iter().collect();
    out.sort_by(|a, b| b.1.cmp(&a.1));
    out
}

// ------------------------------------------------------------------------------------------------------------------------------
// panics
// ------------------------------------------------------------------------------------------------------------------------------

static PANIC_MSG: Mutex<Option<String>> = Mutex::new(None);

pub fn install_panic_hook() {
    std::panic::set_hook(Box::new(|info| {
        let msg = if let Some(s) = info.payload().downcast_ref::<&str>() {
            s.to_string()
        } else if let Some(s) = info.payload().downcast_ref::<String>() {
            s.clone()
        } else {
            "panic".to_string()
        };
        let loc = info.location().map(|l| format!("{}:{}", l.file().replace('\\', "/"), l.line())).unwrap_or_default();
        let short: String = msg.chars().take(300).collect();
        if std::env::var_os("SH2_QA_BT").is_some() {
            eprintln!("{}", std::backtrace::Backtrace::force_capture());
        }
        *PANIC_MSG.lock().unwrap() = Some(format!("panic at {loc}: {short}"));
    }));
}

/// Runs `f`, turning a panic into `Err("panic at file:line: msg")`.
pub fn guarded<T>(f: impl FnOnce() -> T) -> Result<T, String> {
    *PANIC_MSG.lock().unwrap() = None;
    match std::panic::catch_unwind(std::panic::AssertUnwindSafe(f)) {
        Ok(v) => Ok(v),
        Err(_) => Err(PANIC_MSG.lock().unwrap().take().unwrap_or_else(|| "panic".into())),
    }
}

/// Owner of a panic location (crate path -> agent, file ownership of round5_brief.md).
pub fn owner_of_path(loc: &str) -> &'static str {
    let l = loc.replace('\\', "/");
    let file = l.rsplit('/').next().unwrap_or("");
    let file = file.split(':').next().unwrap_or("");
    if l.contains("sh2_battle/") {
        let bp = ["actions.rs", "flow.rs", "rules.rs", "tarot.rs", "ui.rs", "menu_data.rs", "hud.rs", "hud_hits.rs", "hud_result.rs"];
        if bp.contains(&file) {
            return "BP";
        }
        if file == "effects_bridge.rs" {
            return "FX";
        }
        return "BE";
    }
    if l.contains("sh2_gfx/") || l.contains("sh2_formats/") {
        return "FX";
    }
    if l.contains("sh2_audio/") {
        return "CS";
    }
    if l.contains("sh2_menu/") {
        return if file == "movie.rs" { "CS" } else { "MN" };
    }
    if l.contains("sh2_field/") {
        if file.starts_with("cmd") || file.starts_with("classes_") {
            return "MN";
        }
        let mn = ["menu_overlay.rs", "data_screen.rs", "shop.rs", "solomon.rs", "tailor.rs", "fscreen.rs", "screens_dev.rs", "title_options.rs", "points.rs"];
        if mn.contains(&file) {
            return "MN";
        }
        if file.starts_with("cutscene") {
            return "CS";
        }
        return "FS";
    }
    if l.contains("sh2_script/") {
        return "FS";
    }
    if l.contains("sh2_app/") {
        return "QA";
    }
    "QA"
}

// ------------------------------------------------------------------------------------------------------------------------------
// watchdog
// ------------------------------------------------------------------------------------------------------------------------------

static CUR_ITEM: Mutex<Option<(String, Instant, Duration)>> = Mutex::new(None);
static SINK_PATH: Mutex<Option<PathBuf>> = Mutex::new(None);

/// Starts the watchdog thread: an item that runs longer than its budget gets a `timeout` row and the process exits with code 3.
pub fn start_watchdog(owner: &'static str) {
    std::thread::spawn(move || loop {
        std::thread::sleep(Duration::from_millis(500));
        let cur = CUR_ITEM.lock().unwrap().clone();
        if let Some((id, t0, budget)) = cur {
            if t0.elapsed() > budget {
                let mut r = Row::new(id);
                r.status = "timeout".into();
                r.detail = format!("hang: no result after {}s (infinite loop?)", budget.as_secs());
                r.owner = owner.into();
                if let Some(p) = SINK_PATH.lock().unwrap().clone() {
                    if let Ok(mut f) = std::fs::OpenOptions::new().append(true).open(p) {
                        let _ = f.write_all(r.to_line().as_bytes());
                        let _ = f.flush();
                    }
                }
                eprintln!("watchdog: {} timed out", r.id);
                std::process::exit(3);
            }
        }
    });
}

pub fn begin_item(id: &str, budget_s: u64) {
    *CUR_ITEM.lock().unwrap() = Some((id.to_string(), Instant::now(), Duration::from_secs(budget_s)));
    if let Some(p) = SINK_PATH.lock().unwrap().clone() {
        let _ = std::fs::write(p.with_extension("current"), id);
    }
    let _ = take_log();
}
pub fn end_item() {
    *CUR_ITEM.lock().unwrap() = None;
    if let Some(p) = SINK_PATH.lock().unwrap().clone() {
        let _ = std::fs::remove_file(p.with_extension("current"));
    }
}

/// The worker died without a panic (abort, stack overflow): write a `fails` row for the item it was running.
pub fn note_crash(out: &Path, file_stem: &str, code: Option<i32>) {
    let cat = file_stem;
    let cur = out.join(format!("{cat}.current"));
    let Ok(id) = std::fs::read_to_string(&cur) else { return };
    let mut r = Row::new(id.trim());
    r.status = "fails".into();
    r.detail = format!("process crash (exit {code:?}): abort / stack overflow, no panic message");
    r.owner = "QA".into();
    if let Ok(mut f) = std::fs::OpenOptions::new().create(true).append(true).open(out.join(format!("{cat}.tsv"))) {
        let _ = f.write_all(r.to_line().as_bytes());
    }
    let _ = std::fs::remove_file(cur);
}

/// `name` of a field op (`ex 0xc2 sub`).
pub fn field_op_name(ex: u8, sub: u8) -> String {
    if ex == 0xc2 {
        if let Some((_, n)) = sh2_script::opcodes::FIELD_SUBOPS.iter().find(|(s, _)| *s == sub) {
            return format!("{n}(c2.{sub:02x})");
        }
        return format!("c2.{sub:02x}");
    }
    if ex == 0xc3 {
        return format!("SetFieldData sel {sub:#x}");
    }
    if ex == 0xc0 {
        if let Some((_, n, _)) = sh2_script::opcodes::LSD_SUBOPS.iter().find(|(s, _, _)| *s == sub) {
            return format!("{n}(c0.{sub:02x})");
        }
    }
    format!("{ex:02x}.{sub:02x}")
}

/// Owner of a field script op by what it does.
pub fn field_op_owner(ex: u8, sub: u8) -> &'static str {
    if ex != 0xc2 {
        return "FS";
    }
    match sub {
        0x4d | 0x7f | 0x7e | 0x66 | 0x68 | 0x7d => "MN",
        0x50..=0x5f | 0x62 | 0x69..=0x6e => "CS",
        0x2f | 0x60 | 0x61 => "FX",
        0x72 | 0x73 => "BE",
        _ => "FS",
    }
}

/// Collapses a log line to a pattern (digits -> #) for counting distinct issues.
#[allow(dead_code)]
pub fn pattern(s: &str) -> String {
    let mut o = String::with_capacity(s.len());
    let mut last_digit = false;
    for c in s.chars() {
        if c.is_ascii_digit() {
            if !last_digit {
                o.push('#');
            }
            last_digit = true;
        } else {
            last_digit = false;
            o.push(c);
        }
    }
    o.chars().take(160).collect()
}

pub fn disc_dir() -> PathBuf {
    std::env::var_os("SH2_US_DISC_DIR").map(PathBuf::from).unwrap_or_else(|| PathBuf::from("../SH2US"))
}

/// US disc 2 (`SH2_US_DISC2_DIR`, default `../disk2extracted` next to the disc 1 folder): only `LSD.PKB` / `PKFINFO.TBL` differ.
pub fn disc2_dir() -> Option<PathBuf> {
    let p = std::env::var_os("SH2_US_DISC2_DIR").map(PathBuf::from).unwrap_or_else(|| disc_dir().join("../disk2extracted"));
    p.join("PKFINFO.TBL").exists().then_some(p)
}
