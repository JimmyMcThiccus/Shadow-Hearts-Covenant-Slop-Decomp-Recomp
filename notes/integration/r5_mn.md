# Round 5 MN: menus and meta systems (running notes, 2026-10-14)

Agent MN owns `sh2_menu/**` (except `movie.rs`) and the sh2_field menu / shop / meta files (`round5_brief.md`).
Live captures of this round: `scratchpad/live/*.png` of the MN session (not kept in the tree; the ones that matter are referenced below by name and
the comparisons are under `notes/integration/screens/menu5/`).

## Live-driving lessons (also in `tools/live/README.md`)

* **Forcing `MENU+0x300` entries 5 (Ring Custom), 8 (Graveyard) or 14 (Combo Magic) to 2 on a save that has not unlocked them hangs the retail
  game** when the command menu opens (EE spins in a list search at 0x265c38: the page's object list lookup never finds its node).  Three hangs, each
  needed a state load by the user.  Entries 2 / 3 / 7 (Crest Magic / Crest Change / Party Members) are safe to force.  The port must **not** copy
  this: its `cmd_top` builds every page from the scene data and opens a forced entry normally (checked with `SH2_MENU_ENTRIES=all`).
* `MENU` = 0x102d2c, `BTL0` = 0x100130 on the slot-5 state too; crest ownership = bag 1 `BTL0 + 0x200 + 0xc1c` bit set (retail `SKILL1`).
* Physical K = confirm, L = cancel, E = R1 (root menu page 2), Q = L1.

## Retail menu: what each page looks like live vs the port (gap list)

Root menu (12 rows per block, 2 blocks): Items, White Magic, Crest Magic, Crest Change, Equipment, Ring Custom., Personal, Party Members, Graveyard,
Data / Solomon's Key, Combo Setup, Combo Magic, Help, Score, Library, Inventory, Options (text table of the `CmdTop` scene, tags = page ids; page
factory `CmdMenu::Ready` US 0x465310 has 24 cases: 0..17 as the demo, 18 `NENTRY.MSD` (team / name entry, `CmdRetailPage02`), 19 `SECHAR.MSD`
(character select, `CmdRetailPage06`), 0x17 Solomon).

| page | live (retail) | port before round 5 | round 5 |
|---|---|---|---|
| Items | streak backdrop, root list, Name / Held, ring emblem, report | retail (round 4) | unchanged |
| White Magic | portrait card, Magic List, Name / MP, ring + element stone | retail (round 4) | greyed rows now really half-bright (gamma text alpha) |
| Crest Magic | same design as White Magic + `square : Sort` (Restore / Attack / Support / By Alphabet) | demo design (field visible, JP hint bar) | **retail** (see below) |
| Crest Change | card with DCP gauge, `Equip Crests / Recommended / Remove All`, 4 slots `LV`, crest list `LVnn` (red = over DCP), `Crest Magic / MP Use` fence, triangle Info, square Sort (By Region / By Crest Lvl / By Alphabet), L2 R2 Scroll | demo design | **retail** (`cmd_crest_retail.rs`) |
| Equipment | retail (round 4) | retail | unchanged |
| Personal | retail (round 4) | retail | unchanged |
| Party Members | backdrop 1 (top-lit), team box `Contingent 2` with 3 battle faces, member rows, report `cross : Edit Team / circle : Quit / triangle : Reset` | demo design | **retail** (`cmd_form_retail.rs`) + square Team Name |
| Combo Setup | Assign Combo / Combo Switch submenu -> member -> card, `Command` fence, `Character State` + `Command` banners, L1 R1 L2 R2 rows | demo design | **retail** (`cmd_misc.rs` `draw_retail`) |
| Help | categories with `New` marks, unread entries orange, page view `1/3`, `L2 R2 : Scroll` | demo design | **retail** (`cmd_help_retail.rs`) |
| Score | `< Grand Total >` categories, Current Score / Current Rating, Rank + monster title (99 Revenant, next 98 Statue) | demo design | **retail** (`cmd_score_retail.rs`, `score.rs` `rank()` = GetRank) |
| Library | Monsters / Characters, 3D model (rotate R, square action), element stone, typed text, `No. n`, `< name >`, report `Start : List / square : Action / R : Rotate L/R` | demo design | backdrop + report only; 3D model / element stone / list open |
| Inventory | Crests (Name / LV) / Items / Key Items / Weapons / Armor / Accessories, crest Details (triangle), item Explanation | demo design | **retail** (`cmd_plist_retail.rs`) |
| Options | boxed choices, brightness bar | demo-ish | **retail** (`cmd_option.rs` `draw_retail`) |
| Button Customization | pad diagram with the four assignment plates | demo-ish | backdrop 1 only (layout open) |
| Ring Custom / Graveyard / Combo Magic | not capturable (see the hang above) | demo design | backdrops + empty reports; `RINGCTM` / `GRAVE` / `CBMAGIC` layouts open |

## Implemented

### Crest Magic (retail `CmdMagic` / `CmdMagicGoods`, US 0x4c7f20 / 0x4c9b60)

* `MAGIC.MSD`: attach 1 card, 2 `Magic List` banner, 3 target card, 4 `CmdSort`, 5 `Name / MP` fence (White Magic's `SKILL.MSD` has the fence at 4).
* Rows follow the magic order table (menu data table retail key 14 = demo 12: per record `+0xc + sort * 2` = magic id), sort = `MENU+0x28e`
  (`CmdMagic::ExecSort` stores the `CmdSort` row 0 Restore / 1 Attack / 2 Support / 3 By Alphabet).
* Availability = `CmdPC::CreateMagic` (0x46c200): per equipped crest (record `+0x32..+0x3a`) each `MC_P` spell (flag bit k = needs the crest's
  learned bit, `SKILL2`) adds 1 to a per-spell count.
* Cost = `Retail_CmdPC_CalcMagicCost` (0x46d0c0): `MAGI+0x1e` (effect 0x4a: (max MP + 5) / 10, at least 1), then `ApplyCostModifiers`
  (0x46d2f0) = `cost * 100 / count` (two crests granting the same spell halve it), plus each accessory's MP percentage, rounded up.
* Greyed (half alpha, not selectable) when `(flags & 0x1f) >> 3 == 1` (battle only) or over the current MP; Notes = magic help (kind 0x21).
* Verified side by side with live `cm_page_a` (Lucia: Rage / Shield / Gale greyed, 12 MP, ring + `None` stone, `square : Sort`).

### Text alpha in gamma space (`sh2_menu::bevy_ui::gamma_alpha`)

The GS blends in gamma space; Bevy blends in linear light, so half-alpha text came out ~1.5x too bright (greyed `Shield`: live 113 / 226 of white,
port 182 / 244).  Glyph quads now use `a' = a^2.2` (exact over black).  Affects every sprite-layer text with alpha < 0x80 (greyed rows, fades).
The same mismatch is the likely cause of the title swirl fudge (`SWIRL_ALPHA = 0.5` instead of the decompiled 0x19 / 128, menu_m1.md section 1)
and of any other semi-transparent quad; a general fix belongs in the renderer (requests.md, Round 5 MN).

## Other retail pages done this round (details in the module docs)

* **Crest Change** `cmd_crest_retail.rs`: modes Menu / RemoveWho / Confirm / Slots / Goods / Sort / Detail.  Crest level = SSHDAT sec 20 `+4`,
  cap = record `+0x2c`, a crest fits when level <= slot level + cap - used.  Owners are the other members.  Recommended is greedy by MDT 25
  column 3.  Sort = `MENU+0x28d`.  The DCP fill texture is not in the scene data, so it is generated (`cmd_retail::dcp_gradient`, measured
  live).  The report is shifted 40 px (`ButtonReport::Shift` 0x293ad0).
* **Party Members** `cmd_form_retail.rs`: backdrop 1, rows from the FORM records, the team box (polys 8..11 / 20 / 21, cyan name, 4 slanted
  slots), Edit Team swap logic, Reset.  Square opens the name entry (mode 0) and writes the party set name.  The live report on the captured
  save has no `Team Name` line; the square binding comes from resource 10 of the common report.
* **Inventory** `cmd_plist_retail.rs`.  **Help** `cmd_help_retail.rs`: MDT 18 categories with `u16` id lists, MDT 19 entries, unlocked bits
  `MENU+0x180`, read bits `MENU+0x1d0`, page text typed out with `%p` / `%i` codes.  **Score** `cmd_score_retail.rs`: comment tables 29..44,
  rank titles 45, `GetRank` 0x4afb50 transliterated and tested against the live capture (rank 99, comment value 52).  **Options**, and
  **Combo Setup** (retail layout; the default style names per member are still open, see below).
* `%iN` inline icons (`cmd_help_retail::draw_inline_icon`): 0..15 are the cells of CMNMENU attach 6.  16..19 are the logical Menu / Confirm /
  Cancel / Other buttons, drawn as the physical triangle / cross / circle / square (cells 12 / 14 / 13 / 15).

## QA9: the five menu scenes no port code loaded

| file | what it is (retail) | port |
|---|---|---|
| `SCHARGE.MSD` | Graveyard soul charge: op 0x4d `InvokeCmdScene(a, b)` -> `CmdRetailSel01` / `CmdRetailPage01` | **done** `soul_charge.rs` (`ScreenReq::SoulCharge`) |
| `NENTRY.MSD` | name entry, `CmdMenu` page 18 = `CmdRetailPage02`: `SpecialMenu(0x400)` (SM_20_U, default "Roger") and the team name | **done** `name_entry.rs` (`ScreenReq::NameEntry`, Party Members square) |
| `WSTAMP.MSD` | Wolf Bout stamp card: `SpecialMenu(0x600, bout)` -> `CmdRetailSel02` / `CmdRetailPage03` | **done** `wolf_stamp.rs` (`ScreenReq::WolfStamp`) |
| `SECHAR.MSD` | character select, `CmdMenu` page 19 = `CmdRetailPage06` ("Equip Weapons, Armor and Accessories.", the member pick of the shop's Equip) | open (the shop's Equip opens the Equipment page directly) |
| `MENU/DAT/MFIELD.MSD` | container of the SCHARGE / WSTAMP scenes for the field overlay | not needed: the port loads `SCHARGE.MSD` / `WSTAMP.MSD` directly |

`Msd::attach_files` no longer reads past a chunk whose rows are shorter than 12 bytes (QA9 robustness).  Coverage rerun with
`tools/coverage/run_all.sh run msd --fresh` (the category is `msd`; `run menus` is not a category, its workers panic with "unknown
category" and only the report is rewritten): NENTRY / SCHARGE / WSTAMP are now `ok`, SECHAR / MFIELD `untested`.

### Soul charge (`CmdRetailPage01`: US 0x4ddd80 GetReady, 0x4def40 charge, 0x4df450 grade-up, 0x4ded70 exit, 0x4df950 message)

* The stone is `SCHARGE.MSD` attach 1, MDT 54 row `a`: `{name; u8 element; u8 grades = 3; i16 need[3] = 40 / 60 / 80}`.  Its state is
  `MENU+0x380+a*0x10`: `[0]` grade, `[2]` i16 cumulative charge.  The pool is the **u16 at `BTL0+0`** (`*ourBtlSaveDat`, gp-0x7c4c).  BE
  confirms that battles add to it, capped at 9999 (`BtlResult::Polling` SLUS 0x398190).
* Holding confirm moves `need[grade] / 90` per frame from the pool into the stone, never more than the pool holds.  Reaching base + need clips
  the charge there, plays SE 0x3004 and the grade-up sequence, then exits with the grade one higher.  Cancel exits and writes the charge back.
  An empty pool in the idle state shows "No more Soul Energy.".  The charge SE is 0x3001.
* With `b != 0` the charge starts from 0 and the game holds confirm itself (`+0x64` ors 0x2000 into the pad).  Nothing is written back when the
  stone already had a grade.
* Not drawn: the 3D Yuri (`SCCHAR.DAT`, motions `chs_*` / `chb_*` / `fac8..a`) and the 3D stone (`SCSTONE.DAT`, `SCLV_%03d.DAT`).  The
  grade-up flare is a white flash plus a `GRADE n` window.  Dev run: `SH2_SCREEN_DEV=soul:<stone>:GY_08_U` (150 energy in the pool).

### Wolf Bout stamps (`CmdRetailSel02` 0x4e39d0, `CmdRetailPage03` 0x4e3c00 / 0x4e3eb0)

`BTL0[0xfd8 + count] = bout`, then `BTL0[0xfd7]` + 1.  Blanca's wolf skills read the count (0x46b088, 0x4bd77c).  Below 13 stamps the card is
the open box (attach 1, stamps on attach 3); from 13 on it is the closed box (attach 2, stamps 13..15 on attach 4).  The new stamp fades in
(+4 per frame, SE 0x3003), then the message window shows MDT 53 row count - 1 (SE 0x1003).  Dev run: `SH2_SCREEN_DEV=wolf:<stamps>:<map>`.

### Name entry (`CmdRetailPage02`, windows Win14 / Win12)

The prompt per mode is text entry 0 / 1; its alt text is the blank field, whose length is the maximum (12 for a team, 16 for a name).  Defaults
come from MDT 56, the character table from MDT 55 (7 x 15, rows separated by `$`), the background from `MENU/IMG/EX/NE_000.TEX`.  The result
goes to `FieldScreens::name_result`.  Retail copies it into `CField + 0x2170`, an array of 0x180-byte message-variable buffers
(`Sub4e0c40` strcpy): **FS request** to feed it to the message variables.  Controls follow the on-screen guide: confirm types, cancel erases,
triangle clears, square restores the default, start asks for confirmation.  Not compared live.

## Script entry points of retail-only screens (`mn_menu_ops` survey of every US map script)

* `InvokeCmdScene(a, b)` (op 0x4d) appears only in `GY_08_U..GY_13_U` (a = 0..5, b = 0 / 1).  It is the soul charge above; the port used to
  open the plain command menu.
* `SpecialMenu` kinds:
  * 0: 0x80 special; 2 = help bits `MENU+0x180`; 3 = entry flags `MENU+0x300`; 4 and up = `CommandMenu`.
  * 1: shop (25 shops).
  * 2: `CommandMenu(6)` (Formation with an argument).
  * 3: tailor.
  * **4: name entry (SM_20_U).**
  * 5: game over (`CField+0x178 = 1`).
  * **6: Wolf Bout stamp (16 maps).**
  * 7: `CField+0x178 = 2` (ED_00_U, YO_00..02_U: the ending hand-over; still open).
  * The port now handles kinds 0..6.
* `CommandMenu` (main exe 0x3f69d0): 4 main, 5 tutorial (0x1d60), 6 page 8, 7 page 18, 0x10 save.

## US text kinds (`data.us().text(kind, id, -1)`)

| kind | text | kind | text |
|---|---|---|---|
| 0 | PC names | 0x1c | item help |
| 2 | monsters | 0x1d | key-item help (garbage) |
| 3 | weapons | 0x1e | clothes help |
| 4 | armour | 0x1f | skill help |
| 5 | accessories | 0x20 | crest help |
| 6 | items | 0x21 | magic help |
| 8 | key items | 0x23 | aroma help |
| 9 | fusions | 0x25 | tarot help |
| 0xa | crests | 0x26 | ring items |
| 0xb | magic | 0x2d | Papillon challenges |
| 0xd | aroma oils | 0x2e | bout challenges |
| 0xe | tarot cards | 0x19 / 0x1a / 0x1b | weapon / armour / accessory help |
| 0x18 | fusion help | | |

## Open (MN, priority order)

1. Library: 3D models, element stone, data mode, list.  Ring Custom (`RINGCTM.MSD`).  Graveyard (`GRAVE.MSD`, six soul grades; the stone
   grades now live at `MENU+0x380`, so it can show them).  Combo Magic (`CBMAGIC.MSD`).  Button Customization layout.  Personal 3D models.
2. SECHAR (page 19) for the shop's Equip.  `SpecialMenu` 7 (the ending hand-over).
3. Combo Setup: the default slot names come from MDT 49 by slot index.  For Karin rows 0 and 3 are empty and show "1" / "4"; the retail
   per-member style list (`ConvertComboKeyDefault`) is not ported.
4. No live side-by-side yet for the new screens (soul charge, wolf stamp, name entry): no save reaches them, and agents cannot load states.
5. Not re-verified live this round (the round 4 state stands): shops, Solomon, tailor, save / warp points, title, Game Over.  Not ported:
   the tarot, aroma and Papillon House screens.
