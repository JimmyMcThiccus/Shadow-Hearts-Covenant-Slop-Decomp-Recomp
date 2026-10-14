# Battle UI finishing pass -- D1: command menu *contents* (2026-10-10)

Files: `port/crates/sh2_battle/src/menu_data.rs` (new: the per-character availability rules + save readers), `ui.rs` (`build_lists`,
`MenuBuild`, `BtlText::{labels_raw, notes_raw, fusion_help}`, root order), `actions.rs` (`SKIL` name / description columns, sort columns,
`FUSM` names + SP), `bridge.rs` (`ensure_pc`), `devdrive.rs` (party / level / save overrides), one call site in `plugin.rs::build_menu`
(U2's file: six lines replaced, nothing else touched), `lib.rs` (module line).  Example `examples/us_menu_dump.rs` dumps everything the
builder sees (PC ids, `SKIL` groups with both name columns, `MC_P`, `ITEM` sort columns, `FUSM`, level rows, scene rows; `SH2_MENU_DUMP_JP=1`
for the demo disc).

## Root cause (why the first-fight lists were wrong)

The retail US build was fed the demo-era *assumptions* of `ui::build_lists`, none of which the retail code shares:

1. **Skill names came from the wrong column.**  `ActionTables::load` took the `SKIL` record's `+0x3e` as the name index; retail (and the JP
   demo, `BtlMenu.c` `SetSkill1Menu`) read the name with `GetRegDat(9, rec + 2)`.  `+0x3e` is the index of the entry's *description*
   (`sshmes` kind 0x1f).  With the US tables Karin's group 5 therefore printed `Blessed Light / Divine Light / Iron Clow / Unknown` (the
   names at 34..37) instead of `Heuervelk / Bullenfogel / ...` (24..27), and Nicolai's group 11 printed `Hail / Rage / Blaze` (51..53)
   instead of `Cure / Blessed Light / Divine Light` (33..35).
2. **No learned mask.**  `pc_skills(pc)` listed every battle-usable record of the character's `SKIL` group.  `SetSkill1Menu`
   (`SH2US_BATTLE.BIN` 0x604290) masks the group per character from the save (below): Karin's mask is 0 on a new game (no Sword Art
   memorised -> `SetMainMenu` hides the entry, live `01j`), Nicolai's is `BTL0` record `+0x6c` = 3 (`PC_I[0x18..]`, verified on the real
   card save: `03 00 00 00`) = Cure + Blessed Light.
3. **Item order.**  The port always sorted the bag by the `ITEM+0x2c` column.  `SetItemMenu` (0x603210) sorts by `MENU+0x28c`: 0 = id order
   (the default of a new game and of the real card save), 1 = `+0x2c`, 2 = `+0x2e`.  In id order the first-fight bag is Thera Leaf (0) /
   Mana Leaf (4) / Pure Leaf (8) / Talisman of Luck (15) -- live `04b`; by `+0x2c` the Talisman (column 7) came first.
4. **Labels / root order.**  The special entry's label went through a lossy demo->retail index map (`us_of`, 25 -> 23) and was hard-coded
   for two PCs; `BtlMenu::new` ordered the roots Attack / Crest Magic / special / Fusion / ...  Retail `SetMainMenu` (0x5f20c0, the JP one
   has the same order) builds Attack, Fusion, the character's special entry, Crest Magic, Items, Defend, Combo, Run Away (live `14b`:
   Joachim = Attack / Muscle Arts / Crest Magic / Items; `08a`: Yuri = Attack / Fusion / Items / Defend).
5. **Fusion page.**  The port listed the first 24 `FUSM` rows for PC 0 regardless of the save; `SetFusionMenu` (0x603cb0) lists the bits of
   `BTL0+0xec4` (Yuri bits 0..0x14, Kurando 0x15 / 0x16) with the SP upkeep `(DecSPp(FUSM+5) + 99) / 100` in the right column (`08c`:
   Vastitas 3 / Sorm 4 / Gaudion 5) and the kind 0x18 description as the help line.
6. **Skill help.**  `BtlText::skill_help` was kind 0x22 (monster skill info) indexed by the record index; the real page shows kind 0x1f
   indexed by the record's `+0x3e` (`04a`: Cure -> row 51 `Restores small amount of HP to one ally.`; `08k`: Shield -> 55).

## Tables and save fields now used (`menu_data::MenuSource`)

| what | where the game reads it | port |
|---|---|---|
| PC id | `BtlChr+0x120` | `Fighter::char_id` (`SSHMES` section 3: 0 Yuri, 1 Blanca, 2 Gepetto, 3 Lucia, 4 Anastasia, 5 Karin, 6 Joachim, 7 Kurando, 8 Ouka, 9 Hien, 10 Raiden, 11 Nicolai, 12 Rene, 13 Veronica) |
| skill list | `GetRegDat(0x3c, pc)` = `SKIL` group `pc`, 0x40 B rows: `+2` name (kind 9), `+4` flags (`(f & 0x1f) >> 3` in {1, 2} = usable), `+0x1e` MP, `+0x3e` description (kind 0x1f) | `ActionTables::groups` (`name_idx`, `help_idx`) |
| skill mask | Blanca `BTL0+0xfd7` wolf bouts -> tiers (`wolf_bout_mask`); Gepetto `MENU+0x2fc` u32; Anastasia `BTL0+0xfc3..` one bit per record; Karin bag `+0x43 / +0x44` (`0xabc + bag * 0x200`; obtained-bit set bytes 0x13 / 0x14) -> three families of three tiers, only the highest memorised tier listed, Sonnestark when all three are complete (`sword_arts_mask`); Joachim `BTL0+0xfcb` (signed); Nicolai / Rene / Veronica record `+0x6c` u32; everyone else all records | `MenuSource::skill_mask` |
| special entry | `SetMainMenu` per PC: 13 Manifestations (mask != 0), 14 Marionette (`MENU+0x2fc` != 0), 18 Album (a photo exists), 19 Sword Arts (mask != 0), 20 Muscle Arts (`+0xfcb` != 0), 22 Support Fire (8..10), 23 White Magic, 24 Clow, 25 Panish; Lucia's Tarot Card (15) / Aromatherapy (16) and Kurando's Demon Morph (21, his fusion list) are not `SKIL` lists | `MenuSource::special_label`, `BtlText::label_raw` / `note_raw` (retail table 42 / 43 verbatim) |
| crest magic | record `+0x32..0x3a` crest slots (`BtlSave + 0x6e + pc * 0xc0`), `MC_P` flags bit k -> needs the learned bit `bag + 0x16a` bit c, sort `MENU+0x28e` (0 by id, 1..3 by `MAGI+0x3e / +0x40 / +0x42`) | `crest_magic` + `ActionTables::magic_sort` |
| items | `bag + id` count, usable flags, sort `MENU+0x28c` | `item_order` / `item_order2` / id order |
| fusion | `BTL0+0xec4` bits, `FUSM+5` SP, names kind 1, help kind 0x18 | `fusion_bits`, `ActionTables::{fusion_names, fusion_sp}`, `BtlText::fusion_help` |

The MP column is the table's `+0x1e` (the `DecMPp` percent modifiers of accessories are not applied -- same as before); rows whose cost
exceeds the actor's MP are greyed (`12c`: Karin's four arts greyed at 15 MP).

## What each character's menu shows now (retail), and the evidence

| PC | root entries (`SetMainMenu` order) | list | live capture |
|---|---|---|---|
| Karin (5), new game | Attack / Items / Defend / Combo / Run Away | no Sword Arts (mask 0) | `01j` (no entry), `04b` items -> `d1_items_list_karin.png` |
| Karin with the obtained bits set | Attack / Sword Arts / Items / ... | `Heuervelk 64 / Bullenfogel 64 / Geuschbenst 72 / Sonnestark 88` (mask 0x324) | `12a`, `12c` -> `d1_sword_arts_karin.png` (port: `SH2_BATTLE_SAVE=cff:f8,d00:1f`) |
| Nicolai (11) | Attack / White Magic / Items / Defend / Combo / Run Away | `Cure 6 / Blessed Light 10`, help per entry | `01_c`, `04a` -> `d1_command_menu_nicolai.png`, `d1_white_magic_list.png` |
| Yuri (0) with fusions 0..2 | Attack / Fusion / [Crest Magic] / Items / Defend / ... | `Vastitas 3 / Sorm 4 / Gaudion 5`, help `Earth spirit born from a long-suffering soul.` | `08a`, `08b`, `08c` (unit test `yuri_fusion_and_sort_modes`; port shot: see "Blockers") |
| Joachim (6) | Attack / Muscle Arts / Crest Magic / Items | group 6 masked by `+0xfcb`: `Drain Touch 20 / Grand Slam 36 / Deathtron Hammer 72 / Artem Buster 88` (names from the `+2` column, the first two affordable at 50 MP) | `14b` (order verified: special before Crest Magic), `14d` (list + greying) |
| Lucia (3) | Attack / Tarot Card / Aromatherapy / Crest Magic / Items ... | Crest Magic list `Rage 12 / Shield 12 / Gale 12 / Heat Edge 8` in id order (sort mode 0) | `10a`, `10q`; the Tarot / Aroma pages are separate menus (open) |
| Anastasia (4) | Attack / Snap Shot <films> / Album / Crest Magic ... | Album = group 4 records with a photographed bit (`11d`: Aqua Raise 36 / Direct Press 28 / Cash Steal 38 / Remove 50 = records 0..3 by the `+2` column and `+0x1e`, record order) | `11b`, `11d`; the Snap Shot direct entry is open |
| Blanca (1) | Attack / Manifestations / ... | group 1: records 0..10 are the `Soul Comet` tiers (one listed, chosen by the wolf-bout count `BTL0+0xfd7`; record 11 `Red Comet` from 15 bouts), 12..14 `Full Moon / Comeback / Aurora` unlock at 5 / 8 / 12 bouts (`wolf_bout_mask`) | no list capture yet (`15a` is her turn's slide-in) |
| Blanca (1), Gepetto (2), Kurando (7), Ouka / Hien / Raiden, Rene, Veronica | per the table above | | no capture yet -- derived from the decompile only |

Fusion monsters (`08h` .. `08n`: Vastitas's `Special Skills` = `Shield 12 / Crag 16`) are the `BtlChr+0xb1` bit 1 path of
`SetSkill1Menu` (`FUSM+8..` skill ids gated by the fusion level `BTL0+0xf24`, group `0xe + fusion / 3`): the port does not model the fused
state (fusion is a timed boost), so that page cannot appear yet; the rule is documented in `menu_data.rs` for whoever adds it.

## Dev drive additions (`devdrive.rs`)

`SH2_BATTLE_PARTY=0,5,3,4` (PC ids; members the new game does not create are built from `PC_I` by `bridge::ensure_pc`), `SH2_BATTLE_LEVEL=<n>`,
`SH2_BATTLE_SAVE=<hex off>:<hex bytes>,...` (retail `BTL0` offsets of save_retail.md, e.g. `ec4:07` fusions, `fd7:03` wolf bouts,
`cff:f8,d00:1f` all of Karin's arts (bag 1: `0xabc + 0x200 + 0x43`)), `SH2_BATTLE_MENU=28c:01` (item sort mode).  These reproduce C1's memory recipes without the
emulator.

## Evidence (`screens/battle_ui/d1_*.png`, real capture left, port right)

`d1_command_menu_nicolai.png` (`01_c`), `d1_white_magic_list.png` (`04a`), `d1_items_list_karin.png` (`04b`), `d1_command_menu_karin_arts.png` (`12a`) and `d1_sword_arts_karin.png` (`12c`,
port with all arts memorised, Karin alone), `d1_command_menu_yuri.png` (`08a`, party Yuri / Karin / Lucia / Anastasia Lv 12),
`d1_fusion_list_yuri.png` (`08c`).  The stats in the party panel differ from C1's shots (they were poked in memory); the lists are what this
pass is about.

`sh2_gfx::bevy::character::parse_character` panicked on Yuri's `BTLDATA/CHR` bundle (three `wse` / `mse` / `cse` directory entries point
past the end of the package); it now skips such entries with a warning -- the only change outside the battle crate.

## Tests

`menu_data::tests`: `sword_art_tiers`, `wolf_bouts` (pure), `first_fight_nicolai`, `first_fight_karin`, `yuri_fusion_and_sort_modes`
(retail new-game session from the US disc: names, MP, order, hidden entry, learned tier, fusion rows + SP, sort mode 1);
`ui::tests::root_order_is_fusion_special_magic`; `ui::tests::real_us_battle_text` extended (kind 0x1f rows 51 / 55, raw labels, fusion help).
`cargo test -p sh2_battle`: 121 passed; `cargo test --workspace` (2026-10-10, end of the pass): every crate green, no failures.
After the follow-up (party variants, aroma / tarot / snap pages, fused state, effect rings): `cargo test -p sh2_battle` 131 passed;
`cargo test --workspace` green (exit 0) after every code change but the last one-line flow tweak (the immediate fused menu), which the
crate re-test covers.

## Still open

* Lucia's Tarot Card / Aromatherapy pages (`10c`..`10o`: a two-level oil list with a sub-header) and Anastasia's `Snap Shot <films>` direct
  entry (label `GetRegDat(0xf, has_film)`, MP from kind 0x45 `+0x1c`): separate menus, not `SKIL` lists; not built.
* Rene's `Clow` / Veronica's `Panish` are direct single-skill entries in the real menu (greyed when the MP is short); the port shows them as a
  one-row list.
* Joachim's entry is greyed by a kind 0x48 row of the current state (`socket+0x750`), Gepetto's mask source (`MENU+0x2fc`) and Blanca's
  counter are read but no capture exists for them yet.
* `DecMPp` / `DecSPp` modifiers (accessories halving MP, the fusion SP upkeep after the soul-system bonus) are not applied; offensive items are
  not greyed by record `+0x5c >> 6 == 1` / `+0x5d & 1`; Yuri's Fusion entry does not check story flag 0x2ac.
* The skill help's `/%i<n>` tail is dropped; the real line ends with a ring-hit icon (`12c`, `08m`) -- HUD work.
* The demo (`--jp`) build keeps its generic `Special Skills` label (26) but now applies the JP `SetSkill1Menu` masks (pc 1 fixed bit 12, pc 2
  `MENU+0x2fc`, pc 5 record `+0x3a`, pc 6 `BtlSave+0xe37`) and the corrected name column; not re-photographed.

## Follow-up (C1's 96 party captures `08_`..`19_`, same day)

Every gate of the retail `SetMainMenu` / `SetSkill1Menu` / `SetMagicMenu` / `SetItemMenu` / `SetFusionMenu` / `SetBaseAromaMenu` (0x605450) /
`SetAddAromaMenu` (0x6056c0) was re-read in `SH2US_BATTLE.BIN` and matches C1's decoded table (INDEX.md "Memory recipe" step 3); the port now
models them all in `menu_data.rs` / `ui.rs` and reproduces C1's setups without the emulator (`SH2_BATTLE_RECIPE=<name>`, below).

| character | root menu (port = live) | list (port = live) | capture | side-by-side |
|---|---|---|---|---|
| Yuri (0) | Attack / Fusion / Items / Defend / Combo / Run Away (fusion bits `BTL0+0xec4`; story flag `RG` 0x2ac is not checked: no field state in battle) | Fusion: `Vastitas 3 / Sorm 4 / Gaudion 5`, help kind 0x18 | `08a`, `08c` | `d1_command_menu_yuri`, `d1_fusion_list_yuri` |
| Vastitas (Yuri fused, fusion level 2) | Attack / Fusion / Special Skills / Items / ... (`Special Skills` = label 26 for Yuri's fusions, 27 otherwise); the Fusion page starts with `Cancel` (label 47) | `Shield 12 / Crag 16` = `FUSM+8..` skill slots whose level `+0x16..` <= `BTL0+0xf24+id`, from `SKIL` group `14 + id / 3` | `08h`, `08k` | `d1_vastitas_menu`, `d1_vastitas_special_skills` |
| Blanca (1) | Attack / Manifestations / Items / Defend | 15 wolf bouts (`BTL0+0xfd7`) -> `Red Comet 20 / Full Moon 18 / Comeback 36 / Aurora 54` (records 11..14 of group 1) | `15b`, `15d` | `d1_blanca_*` |
| Gepetto (2) | Attack / Marionette / Items / Defend | dress mask `MENU+0x2fc` = 3 -> `Earth Cast 20 / Aqua Cast 20` (all-enemy AoE: `flags 0x4308`, class from the record) | `16a`, `16e` | `d1_gepetto_*` |
| Lucia (3) | Attack / Tarot Card / Aromatherapy / Crest Magic / Items / ... (tarot bits `0xf3f..0xf41`, oil bits `0xf42`, record crest slots) | Crest Magic `Rage 12 / Shield 12 / Gale 12 / Heat Edge 8` (id order); Aromatherapy page 1 = owned oils without costs (`Select Aroma Oil.`), page 2 under the `Ocean Oil` sub-header = `Misty Oil 20 / Grass Oil 25 / Night Oil 30 / Moon Oil 30` (`GetRegDat(0x43)` rows `(first, second, MP)`), help `????`; confirm = `MenuEvent::Aroma { id: combo row }` -> name window `Ocean Oil × Misty Oil`; Tarot Card reports `MenuEvent::Tarot` with no target page | `10a`, `10n0`, `10n`, `10o`, `10q` | `d1_lucia_*` |
| Anastasia (4) | Attack / Snap Shot `1` / Album / Crest Magic (`Snap Shot` = `GetRegDat(0xf, 0)`, MP 1 in the cost column; Album needs a photo bit `0xfc3..0xfc5`) | Album `Aqua Raise 36 / Direct Press 28 / Cash Steal 38 / Remove 50`; Snap Shot -> enemy target page (`Pending::Snap`, blue marker is U3's) -> `MenuEvent::Snap { target }` | `11b`, `11d`, `11f` | `d1_anastasia_*` |
| Karin (5) | Attack / Sword Arts / Items / Defend | `Heuervelk 64 / Bullenfogel 64 / Geuschbenst 72 / Sonnestark 88`, greyed at 15 MP | `12a`, `12c` | `d1_command_menu_karin_arts`, `d1_sword_arts_karin` |
| Joachim (6) | Attack / Muscle Arts / Crest Magic / Items | `Drain Touch 20 / Grand Slam 36 / Deathtron Hammer 72 / Artem Buster 88` (two affordable at 50 MP) | `14b`, `14d` | `d1_joachim_*` |
| Kurando (7) | Attack / Demon Morph / Items / Defend (bits 21 / 22 of `0xec4` + `0xec0` bit 3) | `Tsukiyomi 5 / Jutendouji 7` (help `Moon goddess that empowers those of noble spirit.`); fused Tsukiyomi: Attack / Demon Morph / Special Skills / Items (the party row says `Young Swordsman`: the `PC_I` name of PC 7 before the story reveals it, C1 wrote `Kurando` into the record) | `17b`, `17d`, `17k` | `d1_kurando_command_menu`, `d1_kurando_demon_morph_list`, `d1_tsukiyomi_menu` |
| Nicolai (11) | as before | | `01_c`, `04a` | |

New data shapes for the HUD (U3 renders; the fields are documented in the code): `hud::HudList::subtitle` (second header strip, `10n`),
`ui::Page::{Aroma, Aroma2 { first }}` (plain lists), `ui::Pending::Snap` (enemy target page with the blue marker, `11f`), `ui::Root::{Tarot,
Aroma, Snap}` (root rows; `Snap Shot` carries its MP in the cost column like a list row), `flow::Fused` / `Battle::fused` (the fused
name replaces the fighter's name; `Fused::model` = `FUSM+2` is the fusion's portrait / model number -- `plugin.rs` already shows it through
`rt.fused`, which is kept in step: `Cancel` clears it).

Fused state (`flow.rs`, minimal): `MenuEvent::Fusion { id }` -> phase 9 sets `Battle::fused[actor]` (name, model, SP upkeep from
`FUSM+5`) through the new `Host::fusion_info` and goes straight back to `Phase::Command` for the same actor (live `08h` / `17k`: the
transformation costs no turn; `d1_tsukiyomi_menu.png`); every later `TurnBefore` pays the upkeep from the SP left and reverts at SP 0; the Fusion page while fused
lists `Cancel` (id -1) first, which reverts without an effect.  Fusion-monster skills are `MenuEvent::Special { enemy_like: false }` (the
effect path of the PC skills; the fusion group's record is found through `ActionTables::fusion_group`).

Dev-drive recipes (`SH2_BATTLE_RECIPE=yuri|vastitas|lucia|anastasia|karin|blanca|gepetto|joachim|kurando|tsukiyomi|nicolai`, explicit
`SH2_BATTLE_PARTY` / `_LEVEL` / `_SAVE` / `_MENU` override the recipe) and commands `tarot`, `aroma`, `snap` (plus `fusion` then `skill` for the
fused pages); shots `aroma_menu`, `aroma2_menu`, `snap_target`, `fused_menu`.  Single-member parties (`SH2_BATTLE_PARTY=<pc>`) were used for
the list shots so the scripted command lands on the right character.

Side-by-sides written for the follow-up: `d1_yuri_command_menu_4party`, `d1_vastitas_menu`, `d1_vastitas_special_skills`, `d1_blanca_command_menu`,
`d1_blanca_manifestations_list`, `d1_gepetto_command_menu`, `d1_gepetto_marionette_list`, `d1_gepetto_marionette_target`, `d1_lucia_command_menu`,
`d1_lucia_aroma_list`, `d1_lucia_aroma2_list`, `d1_lucia_crest_magic_list`, `d1_anastasia_command_menu`, `d1_anastasia_snap_target`,
`d1_anastasia_album_list`, `d1_joachim_command_menu`, `d1_joachim_muscle_arts_list`, `d1_kurando_command_menu`, `d1_kurando_demon_morph_list`,
`d1_tsukiyomi_menu` (when the fused Kurando shot landed), `d1_cure_ring`, `d1_cure_ring_intro`.

Tests (`menu_data::tests`): `blanca_manifestations`, `gepetto_marionette`, `joachim_muscle_arts_and_crest_order`, `lucia_tarot_aroma_crest`,
`anastasia_snap_and_album`, `kurando_demon_morph`, `fused_vastitas_special_skills` -- each builds C1's recipe on a retail new-game session
(`bridge::ensure_pc` + the `BTL0` pokes) and checks the root rows, the list names / costs / greying and the events.

Still open after the follow-up: the Tarot draw presentation (card row, flip, result message, `10d`..`10l`) and the Snap Shot camera sequence /
photo bit (`11g`..`11j`; `MenuEvent::Snap` ends with no effect), the aroma combination's description once known (`????` is shown always), the
`Combo Magic` (labels 5 / 6) and the status-sealed Combo greying, Rene / Veronica direct entries, the kind-0x48 arena rule for Joachim, DecMPp /
DecSPp modifiers, Yuri's field flag 0x2ac.

## Rings of the non-weapon actions (U1's finding, same day)

`CBattle::EffectFunc` (JP CBattle.c, the `AddStepArea` / `AddModulateArea` / `AddStrikeArea` calls at 0x4a6ee0.. ; retail `EffectFunc`
0x484650 reads the same columns) builds a Judgement Ring for every party action from the action record itself -- there is no separate
ring table:

| record | zones | columns |
|---|---|---|
| `SKIL` (0x40 B) and `MAGI` (0x44 B) | up to five `AddStepArea(start, width)` (green), the list stops at the first width <= 0; then one `AddModulateArea(start, width, min_pct, strike)` when its width > 0 (white band with the blue full-score part, red tail) | steps `+0x20/+0x22`, `+0x24/+0x26`, `+0x28/+0x2a`, `+0x2c/+0x2e`, `+0x30/+0x32`; modulate `+0x34..+0x3b` |
| `ITEM` (0x30 B) | one `AddStrikeArea(start, width, strike)` (weapon colours) -- items ring too | `+0x1c / +0x1e / +0x20` |

`SetMode(5, 1, 1, 4, 3)`, period 1.6 (`SetJRingStatus` only applies the status modifiers).  US data: Cure = modulate (60, 60, 100, 15) and
nothing else (= C1's `01l` "one area (60, 60, 15)"), Blessed Light = step (160, 50) + modulate (220, 110, 60, 11), Crag = (145, 50) +
(220, 100, 60, 10), Heuervelk III = three steps + (240, 90, 60, 10), Shield = (145, 50) + (220, 110, 100, 11), Thera Leaf = strike (45, 120, 15).

Port: `ActionRec::{ring_steps, ring_mod, ring_strike}` (`actions.rs`), `RingRun::start_effect` (`plugin.rs`, next to U1's `start_special`:
step zones first, then the modulate / strike zone, exactly as registered), started by `run_battle` before `effect_gate` for `Phase::Effect` /
`Phase::Aroma` of a party member (`effect_ring`: items / crest magic / PC skills / fusion skills from their records, aroma combinations with
the Cure-like blue zone of live `10o` until the `0x43` row's own ring columns are decoded); the grade multiplies every hit / heal of the effect
in `flow.rs` (`scale_by_ring`: 0 = `Miss!!` cancels the effect, 1.2 = strike), as `EffectDamageSet` does with `GetJRingAreaResult`.
Items ring as well (the JP code's `AddStrikeArea` branch; the dev drive's Thera Leaf logged `ring result x1.00 (1 hits of 1)`), so no
item-specific exception was added.  Dev drive: shot `effect_ring` (30 ticks into a non-attack ring; `judgement_ring_run` 45 ticks later).
Evidence: `d1_cure_ring.png` (`01l` left: the live frozen Cure ring; right: the port's Cure ring under way), `d1_cure_ring_intro.png`.
Tests: `menu_data::tests::effect_ring_zones` (Cure / Blessed Light / Shield / Crag / Thera Leaf columns on the US data),
`flow::tests::effect_hits_follow_the_ring_grade`.
