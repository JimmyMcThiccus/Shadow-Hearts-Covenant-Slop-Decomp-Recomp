# notes/H - Section H (BATTLE.BIN) index

* `battle_rules.md` - every formula (stats, turn order, damage, SP, rewards, levelling) -> `port/crates/sh2_battle/src/rules.rs`
* `battle_data.md` - PKFINFO/PKB, BTLDATA.PKB, SSHDAT/SSHMES containers, MONSTERParam, equipment, AIS -> `data.rs`, `pkb_compat.rs`
* `battle_flow.md` - BtlSocket -> CBattle phases -> BtlMenu protocol -> support objects -> `flow.rs`
* `CBattle.md` (with `BtlChr` and `CBattle` struct tables), `BtlMenu.md`, `BtlSocket.md`, one `<Class>.md` per remaining class
  (method inventory with JP/US addresses + observed field offsets; regenerate with `tools/H_gen_notes.py`)
* `us_map.txt` - JP->US function map for BATTLE.BIN (553 entries; see header); `us_map_candidates.txt` - unverified extras
* decompilation: `decomp/H/*.c` (+ `types.h`); tools: `tools/H_*.py`, `tools/usmatch.py`, `tools/make_decomp.py`
