//! Round 5 BE: headless matrix of every retail monster set (`sh2_battle::headless::run_set`).
//! `cargo run --release -p sh2_battle --example be_every_battle [-- FIRST LAST]`  (tab separated rows + a summary)
use std::collections::BTreeMap;
use std::sync::Arc;

use sh2_battle::{actions::ActionTables, data::BattleData, headless, pkb_compat::PkbDisc};

fn main() {
    let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR")).unwrap();
    let data = BattleData::load_us(&d).unwrap();
    let tables = Arc::new(ActionTables::load(&data));
    let s = headless::sturdy_session(&data);
    let a: Vec<usize> = std::env::args().skip(1).filter_map(|x| x.parse().ok()).collect();
    let n = headless::monset_count(&data);
    let (lo, hi) = (a.first().copied().unwrap_or(0), a.get(1).copied().unwrap_or(n - 1).min(n - 1));
    let mut by_outcome: BTreeMap<String, usize> = BTreeMap::new();
    let mut decisions: BTreeMap<String, u32> = BTreeMap::new();
    let (mut scripted, mut fallback) = (0u32, 0u32);
    println!("set\toutcome\tturns\tflags\tscripted/monsters\tai_scripted\tai_fallback\texp\tcash\tmissing_models\tmissing_ais\tenemies\tdecisions\tskills\tmissing_effects\tmotion_problems");
    for set in lo..=hi {
        let r = headless::run_set(&data, &tables, &d, &s, set, 7 + set as u32, 400);
        *by_outcome.entry(format!("{:?}", r.outcome)).or_default() += 1;
        for (k, v) in &r.decisions {
            *decisions.entry(k.clone()).or_default() += v;
        }
        scripted += r.ai_scripted;
        fallback += r.ai_fallback;
        let en: Vec<String> = r.enemies.iter().map(|(i, n)| format!("{i}:{n}")).collect();
        println!(
            "{set}\t{:?}\t{}\t{:#x}\t{}/{}\t{}\t{}\t{}\t{}\t{:?}\t{:?}\t{}\t{:?}\t{:?}\t{:?}\t{:?}",
            r.outcome,
            r.turns,
            r.flags,
            r.scripted,
            r.enemies.len(),
            r.ai_scripted,
            r.ai_fallback,
            r.exp,
            r.cash,
            r.missing_models,
            r.missing_ais,
            en.join(", "),
            r.decisions,
            r.skills,
            r.missing_effects,
            r.motion_problems
        );
    }
    eprintln!("outcomes {by_outcome:?}");
    eprintln!("AI turns scripted {scripted} fallback {fallback}; decisions {decisions:?}");
}
