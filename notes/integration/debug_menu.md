# US retail built-in debug menu (live map, 2026-10-14)

Source: the user's PCSX2 save on the built-in debug map (orange "DUMMY" floor, one save point, Karin controlled).  Screenshots in
`screens/debug_menu/`.  Same save-block addresses as slot 8: `BTL0` 0x100130, `MENU` 0x102d2c.

**Driving:** Karin facing north, **X (key K) with a short 0.05 s press** opens the menu (a 0.1 s press also confirms the remembered
row).  Circle closes the menu from level 1 but steps back one level on deeper pages.  `tools/live/dbgmenu.py OUT.png i j ...` follows a
row path and backs out again; `tools/live/dbgstep.py OUT.png KEY ...` presses keys and prints the BTL0 / MENU bytes that changed.
Several entries change the save immediately (counts, flags, party), so diff before and after and restore anything changed.

Translations are mine; `?` = not opened / not understood yet.

## External reference

The Shadow Hearts fandom wiki documents the same menus from play: https://shadowhearts.fandom.com/wiki/Debug_Menu (with sub-pages for
the Fly! area list, the Boss / Event battle lists and the Pit Fight list).  Points it adds that we had not seen or that differ:

* Its "Menu 2" is our Circle + R2 movie menu, "Menu 3" Square + R2, "Menu 4" Circle + Square.
* **Mini-games**: the wiki says Mini Game 1 (2P / CPU) runs (Yuri vs Kurando throwing Blancas / Eleanors, first to 7 hits loses) and
  that the Director's Cut replaces Debug Island 2 / Help with **Mini Game 2** (Yuri dodging Nicolai heads, a whack-a-mole).  Our
  reading of the US script found no call behind the Mini Game 1 rows and our one live try closed the menu: **re-check** (the game may
  start it from another path, or our scripted press missed).
* Version date: US / PAL "2004/07/16 15:00" (matches), Director's Cut "2004/04/05 15:30".
* Other > **Fly!** (飛びたい！) = manual warp by ID letters (the menu cousin of our Circle + R3 Experiment warp).
* World map: the Debug Island point exists but the world map re-locks it on load; a second Paris point goes straight to Gepetto's
  apartment; a Gallery of the Dead point exists unused.
* Party Leader can be any NPC (numeric input); Character Name is the only way to fix Lenny / Kurando names early in the US build.
* Other > Menu settings presets (Opening, Ardennes, Anastasia solo / back, later opening, Blanca solo / back, Mutant Apes) and the
  individual menu-entry control (these write the `MENU+0x300` entry-flag bytes the port's `cmd_top` reads).
* Menu 4 > Systems: change disc, save icon / title, save point, "You cleared it, right?" (New Game+), localization code.

## Button shortcuts on the debug map (10_button_combos.png)

Found by the user (Circle + R2) and probed 2026-10-14.  The DB_00_U script has no `get_pad` checks, so these come from the field
engine calling the map's events directly.  Hold the shoulder / Select button, then press the face button.

| combo | opens |
|---|---|
| X | main debug menu (below) |
| Circle + R1 | main debug menu |
| Circle + R2 | Movie player (row 6 directly) |
| Circle + Select | Battle player (Boss battle / Event battle / Pit fight) |
| Square + R2 | **second debug menu**: バージョン表示 version display, 自由ウィンドウ作成 free window creation, ミニゲーム１ (2P) / (CPU) mini-game 1 vs player / CPU, デバ島２へ go to Debug Island 2, ヘルプ help |
| Circle + R3 | **party menu**: パーティ編集 party edit, 物語上でのパーティ the story's party, セットパーティ実行 apply the set party, 実験 experiment |
| **Circle + Square** | **asset / sound test menu** (found by the user; 12_circle_square_menu.png), below |
| Circle + L1, Circle + L2 | a "Team A" strip with the members' faces (the normal L1 / L2 team display) |
| Triangle (+ R2) | the normal command menu |
| Circle + L3, Select + R2 | nothing |

### Square + R2 menu, decoded (DB_00_U script 0xfa45; explored live 2026-10-14)

* **Version display**: a message window "―デバッグ島情報― 更新日 ２００４／０７／１６" (debug island info, updated 2004/07/16).
* **Free window creation**: calls script function 0xf90b (not opened).
* **Mini-game 1 (2P) / (CPU)**: **empty in the US build**: their handler branches fall straight through (no call), so choosing them
  just closes the menu.  The mini-game was cut; only the menu rows remain.  Help is empty the same way.
* **Debug Island 2**: `MapJump("DB_01_U")`, but **DB_01_U is not on the US disc** (FIELD.PKB has only DB_00_U): the game goes to a
  black screen and stays there (CPU running, nothing loads).  Reload a state.

### Per-area debug maps (`*_DB`): skit testers (11_ap00db_skit.png)

Map jump 2 sends you to per-area debug maps.  Each is the DUMMY floor with a menu that launches the area's story skits (キャラ劇) in
the real map with the right party: AP_00_DB > "The two moving forward" plays Nicolai's "I should warn you. It's completely different
here inside the tower..." inside Apoina Tower.  Menus (from the scripts' strings; blank = no matching rows, not opened):

| map | rows |
|---|---|
| AP_00_DB Apoina Tower | map first half / second half; skits 進む二人 The two moving forward, リングの魂 Ring Soul, 扉の前で Before the door, 希望という名の憎悪 Hatred called hope, 天秤ギミック scales puzzle |
| AD_00_DB | 秘密の花園 The secret garden, なんで怪物が？ Why a monster?, 血液型の部屋 blood-type room, 星座パネルの部屋 constellation-panel room, アンドレ戦直前 just before the André fight, 助けてくれて、ありがとう thanks for saving me |
| FI_00_DB Firenze | 身体で払うわ, カルラのお礼 Carla's thanks, ルチアの旅立ち Lucia sets out, カルラの館で作戦会議 1/2 strategy meetings at Carla's mansion, ロレンスからの伝言 Lorenz's message, オーロラオイル入手 Aurora oil, 歩数計イベント pedometer event |
| GT_00_DB | トーマスの正体 Thomas's true identity, 楽園に暮らす人々 people of paradise, 試練の準備 preparing for the trial, 主教が目覚めたよ！ the bishop woke up, ソロモン帰り back from Solomon, ピットファイト pit fight |
| MS_00_DB Mirror castle | map first / second half; 鏡の城, 鏡イベント mirror event, 鏡の中へ into the mirror, 後半最初に入ったとき first visit in the second half, 破壊の力 power of destruction, 人間に戻るアンリ Henri becomes human |
| MU_00_DB Muhyoan | 帝都浅草・無響庵, 行ってきます I'm off, 福引イベント lottery event, みんなを探して find everyone |
| TD_00_DB Todo lab | 桜花ボス戦前 before the Ouka boss, 潜入！藤堂技研 infiltrate, 鉄奇兵・鹿組頭, 脱出！藤堂技研 escape |
| SO_00_DB Solomon | meet King Solomon, battle end |
| PA_00_DB, RU_00_DB | ボス部屋 boss room |
| IK_DB_U | イベントバトル無し (no event battle) |
| AR_15_DB, BO_02_DB, DH_00_DB, FI_01_DB, GB_DB_U, IN_00_DB, KT_00_DB, QG_DB_U, SK_DB_U, SU_22_DB, ZI_00_DB | script present, other wording (not surveyed) |

Maps with only an `.MPS` (no script) on the US disc: CA_00_DB, DO_00_DB, HE_00_DB, IF_00_DB, MI_DB_U, SH_00_DB, SM_00_DB, YO_00_DB --
Map jump 2 rows such as DO00DB / HE00DB / IF00DB / SM00DB / YO00DB lead there (expect an empty floor or a hang; not tried).
Tools: `cargo run -p sh2_field --example msc_dump -- --us MAP DIR` + `tools/live/msc_list.py`.

### Circle + R3 party menu, decoded (DB_00_U script 0xe6c0; explored live 2026-10-14)

* **パーティ編集 party edit**: パーティＡ–Ｅ, then the five teams by name (Ａ（Team A） ...).
* **物語上でのパーティ the story's party**: one-press story parties (sets members / joins as the story would):
  New Game setup, Yuri's party, add Karin, add Joachim, Joachim vs Cerberus, revert, before / after Joachim joins, add Lucia,
  Undersea temple (+ revert), Blanca alone (+ revert), Anastasia alone, Anastasia joins & battle, Anastasia joins locked / unlocked,
  Yuri & Karin, revert; **second half**: second-half opening, Blanca alone, Kurando alone, Kurando & Blanca, back to Yuri's group,
  Blanca's group joins, the Three Monkeys, add Hien, add Raiden, revert, remove / rejoin Kurando, Joachim & Anastasia for Nihonbashi,
  add Yuri & Karin, everyone, Three Monkeys (Nihonbashi), revert, Yuri & Karin, add Kurando & Blanca, Joachim & Anastasia, add Lucia &
  Gepetto, everyone, Karin absent (+ revert), Mikasa special team (+ revert); **other**: Wolfbout, Gama battle, Nemeton depths
  (each with a revert).
* **セットパーティ実行 apply set party**: a 0–9 number entry (script 0xb9a9) then function 0x3908.
* **実験 Experiment** (function 0xf7d8): **numeric map warp.**  It reads script register word **0x64** (byte 0x190 of the register
  file) as `v = L1*1,000,000 + L2*10,000 + D1*1000 + D2*100 + S` and jumps to `"%c%c_%d%d_%c"` (letters 0 = A, suffix S = 0/1/2 ->
  U / N / ?) or `"%c%c_%d%d_DB"` for S >= 3, via the same helper as Debug Island 2 (0x645, arg 0x190).  The register is 0 on a plain
  save, so it tries **AA_00_U** (not on the disc: black screen).  Verified live: v = 150200 -> AP_02_U loads with its story scene.
  Examples: AP_02_U 150200, AP_00_DB 150003, DB_00_U 3010000, PA_00_DB 15000003.  `_S` maps cannot be expressed.  The flag editor's
  **Warp** tab sets it (`flagnames.encode_map`).

### Square + R2 > Free window creation

A message-window tester: ウィンドウ作成 create window (asks for X, Y, width, height, mode), メッセージ追加 add message, メッセージ削除
delete message, 改行 newline, ウィンドウ閉じ close window.

### Circle + Square > asset / sound test menu (DB_00_U script ~0xd400)

Rows (colour-coded by group in the game): SE load / delete / play / loop play / stop; BGM play / stop; stream play / stop; LSD
(cutscene) play; SET (model) load, motion load, SET delete, motion delete, motion play, change facing, **mini motion viewer**; help,
shop, NPC library, treasure-chest contents survey, Wolf stamp (ブランカ・スタンプ); **ring editor**; system; **NPC viewer** (NPC
number entry); ウル (Yuri).

* **Mini motion viewer** ("ADM設定" ADM settings): key assignment, look around, move, load / delete model, load / delete motion, set
  facing, switch motion set, motion list, hit check, with a `<n>` model-slot selector at the top.  It takes over the pad and moves the
  controlled character; Circle does not leave it and the shortcut combos are ignored while it runs (exit not found yet: reload a
  state).
* **Ring editor** (opened live): rows タイプ type (Normal / Key 鍵 / Roto ロト ring), スピード speed (default **1800 msec** per lap),
  ステータス status (0), エリア指定 area setting; エリア表示 area display and リング開始 ring start appear once areas exist.  Area
  setting: セット set / ひとつクリア clear one / ぜんぶクリア clear all / ひとつクリアを戻す undo clear / OK; Set > 追加 add asks
  色 colour, 開始角度 start angle, 終了角度 end angle on a 0–9 digit pad (the pad cursor returns to 0 after every digit; 入力終了 =
  10 Downs) and lists areas as "セット%D（Ｃ%DＳ%DＥ%D）" (set n: colour, start, end) with 次へ / 戻る paging.  The script also holds
  Ring Tower presets: 1 / 2 / 3 people, Kurando (93F), Gepetto (94F), Lucia (95F), Karin (96F), ...  Driving the pad by script is
  fiddly (a mistimed press left the editor on an empty list page that ignores Left); easier by hand.

## Live story-flag editor

`tools/live/flag_editor.py` (tkinter): one tab per flag page with named checkboxes (tick = set in the running game), Set all / Clear
all, the Ring Soul / secret-art counters, and a Raw tab (any flag number, list of everything set).  It finds the register file every
second through `[0x43fd28]` -> CScript (vtable 0x4392b0) -> +0x1c ScriptWork -> +0x44 registers (checked on DB_00_U and AP_02_U), so
it follows map changes and refuses to write when no field script runs (battle, world map, title).  Names live in
`tools/live/flagnames.py`; `scriptflags.py` prints the set flags from the command line.  The port has the same option at new game:
`SH2_STORY_FLAGS` (`sh2_menu::story_flags`, e.g. `first:5,wolf:3,0x54`).

## Main menu (00_main.png)

| # | Japanese | Meaning |
|---|---|---|
| 0 | ワールドマップポイント設定 | World map point settings |
| 1 | パーティ設定 | Party settings |
| 2 | アイテム、パラメータ設定 | Items / parameter settings |
| 3 | マップジャンプ | Map jump |
| 4 | フラグ管理 | Flag management |
| 5 | その他 | Other |
| 6 | ムービープレイヤー | Movie player |
| 7 | マップジャンプ２ | Map jump 2 |
| 8 | バトルプレイヤー | Battle player |
| 9 | バグ直し用 | For bug fixing |

## 0 World map point settings

* ポイント設定 (point settings): the world-map destination list as checkable rows: グレイヴヤード (Graveyard, "cannot be selected now"),
  Apoina Tower, Domremy, Ardennes Forest, ○Paris (magenta = region header), Shabby apartment, Montmartre, Champs-Élysées, Notre-Dame,
  Louvre, Wine cellar, Southampton, Ronda mine, Wales, 次へ (next page).  Lit rows = point available.
* 移動許可設定 (movement permission): which world-map regions can be travelled: Europe only, Paris streets → Europe, Yokohama streets →
  Japan, Imperial capital → Japan, Yokohama → Japan → capital, Europe ↔ Japan, combinations ... → Paris.  These are the retail
  world-map unlock stages (worth wiring to the port's world map flags).

## 1 Party settings (06_party_settings.png)

| row | Japanese | Meaning / effect |
|---|---|---|
| 0 | 操作キャラ指定 | Controlled character (field model) |
| 1 | パーティ編集 | Party edit: character -> team A–E -> Add / Remove.  Adding creates the save record exactly like the game's `PCInit` (byte-identical to `us_pc_records`), sets the joined bit (`MENU+0x82`) and appends to the team (`MENU+0x84 + team*0x20`) |
| 2 | バトルチーム編集 | Battle team edit |
| 3 | レベル変更 | Level change: list of all characters with their level, e.g. Yuri 04, Blanca 03, Gepetto 03, Lucia 09, Anastasia 18, Karin 02, Joachim 05, Kurando 00, Ouka 50, Hien 50, Raiden 00, Nicolai 02 (00 = no record) |
| 4 | カレント変更 | Current team (A–E) |
| 5 | チーム名編集 | Team name edit |
| 6 | キャラ名変更 | Character name change |
| 7 | 装備変更 | Equipment change: character -> 裸にする (strip all) / 装備変更 (equipment) / 紋章変更 (crest change: 8 slots + "remove all" -> Equip / Remove -> crest list Astaroth, Asmodeus, Amon, Orobas, Gaap, Baal, Samigina, Glasyalabolas, Bifrons, Bune ...; writes record `+0x32 + slot`, e.g. Samigina = 6) |

The character lists have 13 entries: the 12 party ids plus **レニ (Leni)** at the end (no record in the US data; worth checking).

## 2 Items / parameters (05_items_page.png)

* お金 (money), アイテム (items), 歩数計距離 (pedometer distance), ソウルエナジー (soul energy).
* アイテム -> category: 1 items, 2 weapons, 3 armour, 4 accessories, 5 crests (魔方陣), 6 custom items, 7 Corelia, 8 aroma items,
  9 tarot cards, 10 key items -> entry list -> 追加 / 削除 (add / remove) -> quantity prompt (値 01) or an info box
  (カテゴリ 9 / 番号 0 / 所持数 0).  Confirming writes the count into the active bag immediately (the user's save holds 99 of every
  consumable).  The tarot category lists The Fool, The Magician, High Priestess ... (Lucia's cards).

## 3 Map jump, 7 Map jump 2

Map jump: ワールドマップへ戻る (back to the world map, red), then areas with their map ids: Apoina Tower AP00U, Domremy DO04U, Ardennes
Forest AR15U, Paris: Shabby apartment BO01U, Montmartre PA01U, Champs-Élysées PA03U, Notre-Dame PA02U, Louvre RU03U, Wine cellar I12U,
Southampton SA01U, Ronda mine RO00U, Wales E00U, 次へ (next).  The digits are editable (cyan).  **The list wraps: 15 x Down lands on
row 0 "back to the world map", and confirming it leaves the debug map at once** (happened 2026-10-14; navigate to 次へ with Up instead).

Map jump 2 (08_mapjump2_movies.png) lists debug maps by prefix with an editable number: 前半 (first half) GY00DB, AP00DB, DO00DB,
AR00DB, HE00DB, KS00DB; 後半 (second half) YO00DB; ダンジョン＆隠し (dungeons & hidden) ND00DB, IF00DB, SH00DB, SM00DB.  The `*DB` maps
are the per-area debug maps (the user's save is one of them).

## 4 Flag management (09_flag_pages.png)

Rows: 0 set all flags to 0 (acts at once, not opened); 1 first-half clear flags; 2 second-half clear flags; 3 hidden clear flags;
4 Wolfbout clear flags; 5 hidden-appearance flags; 6 change registers; 7 save registers (not opened); 8 Ring Soul flags; 9 Grave
flags; 10 secret-art book (奥義書) flags.  Opening each page wrote nothing (BTL0 and MENU diffed around every visit); × = flag clear,
everything is clear on the user's save.  The pages list the scenario as the game tracks it:

* **1 First half:** Opening, Apoina part A, Domremy, Ardennes Forest, Paris, Louvre 1, Wine cellar, Louvre 2, Southampton, Ronda
  mine, Wales 1, Firenze 1, Manmaria Island, Firenze 2, 次へ (more).
* **2 Second half:** second-half opening, red-brick warehouse, Yokohama 1, battleship Mikasa 1, Todo lab 1, Mikasa 2, Yokohama 2,
  foreign cemetery 1, the other world (異界), Muhyoan 1, Nihonbashi 1, Todo lab 2, Muhyoan 2, Nihonbashi 2, 次へ.
* **3 Hidden dungeons:** Sesshoseki (killing stone), Doll house, Schwarzwald, わくらば (marked ボツ = cut), Nemeton deepest level,
  Ring Tower.
* **4 Wolfbout opponents:** Tetsu, Terry, Jerome, Henri, Philip, R3, Necross, 3連星 (triple star), Kibolin, Eleonore, Matsunaga,
  Robo, Henri (2nd), Robo (2nd), Phantom Wolf (怪人ウルフ).
* **5 Hidden appearances** (side characters, mostly in ス / エ pairs, probably start / end): Professor 1, Sailor Serge, Soldier,
  Crybaby Katsuta, Mandran, Professor 2 (x2), Doris, Hero and the dancer (x2), 我は狗が身 ..., more below.
* **6 Registers:** 1Bit, #B, #C, #W, #S, #R, #F (script register banks; `CScript` register types).
* **8 Ring Soul:** reset, visit 1 ... 14+ (Ring Soul counter).
* **9 Grave (Graveyard) events,** in pairs: the lost girl, "what are you looking for?", Yuri, Karin and Jeanne, release of power,
  the truth of the curse, the vanished Jeanne, memories, もうじき ("soon") ...
* **10 Secret-art books:** reset, 1st ... 10th.

### Where the flags live (decoded 2026-10-14, user's throwaway state slot 1)

The debug menu is the event script of map **DB_00_U** (`grep_msc_sjis --us 前半クリアフラグを変更`; Flag management = event 5,
function 0x7fba; listing with `tools/live/msc_list.py`).  Every page row is a plain **script flag** (`setFlag` / `clrFlag` /
`chkFlag`, VM builtins 0xa4–0xa6): flag n = bit `n & 31` of u32 register word `n >> 5` of the `CScript` register file (the `RG` save
chunk, `CFieldSocket::SaveScriptRegister`).  On the debug map that file is at **0x75dcc0** (heap).  Confirming a row **toggles it
immediately** (no prompt; the やめる / クリア！ prompt belongs to row 0 "set all flags to 0").  The cursor of some pages does not start
on row 0 (Wolfbout starts on the next uncleared opponent), so position by reading the screen.

| page | flag number | verified live |
|---|---|---|
| 1 first half (3 screens of 14) | `8 + screen*14 + row` (Opening 8 ... Graveyard 0x29) | rows 0, 1, 2 |
| 2 second half (screens of 14) | `0x3c + screen*14 + row` | rows 0, 3 |
| 3 hidden clear | `0x64 + row` | row 1 |
| 4 Wolfbout | `0xa0 + row` | bits 3 / 13 = the two ○ rows, toggle of row 5 |
| 5 hidden appearance | rows 0–18 = `0x29d0 + row`; row 19 "last dungeon appears" = **0x54**; row 20 "trade sequence failed" = 0x29fe | rows 0, 19 |
| 6 registers | register editor (1Bit, #B, #C, #W, #S, #R, #F = bit / byte / ... / float views) | – |
| 8 Ring Soul | count byte in typed register 0x1539 (reset, 1st ... ); the page then offers the Ring Soul maps AD_01_U, AP_04_A, FU_06_U, GT_05_U, MI_00_U, SK_03_U, ND_09_U, RO_08_U, WE_00_U, RU_04_U, RU_04_N | from code |
| 9 Graveyard events | `0x29e8 + row` (18 rows, pairs per event) | rows 0, 5 |
| 10 secret-art books | count byte in 8-bit register 0x18 (reset, 1st ... 10th) | from code |

First-half rows beyond the first screen: SG Italy branch, Firenze 3, Nemeton ruins, Firenze 4, Cannes, Sainte-Marguerite, Cannes 2,
Wales 2, Hermitage 1, Petrograd 1, Hermitage 2, Petrograd 2, Goreme Valley, Mirror castle / Goreme Valley 2, Corridor of the dead,
Hermitage 3, Idar Flamme, Apoina Tower 2, Graveyard.  Hidden-appearance rows 15–18: Blue-eyed Tatsutahime, Quiz 1 Mikasa, Quiz 2
Yokohama, Quiz 3 clear.  Graveyard pairs end with こたえ (the answer).  `tools/live/scriptflags.py` prints the set flags with these
names (slot 1 of the user's debug save: 0x0, 0x2, 0x80, 0x88, 0x90, 0x1248).

For the port: these are the same flag numbers the story scripts use with `chkFlag`, so a dev option that sets e.g. "first half
cleared up to Paris" (flags 8..12) or a Wolfbout rank (0xa0 + n) is a one-line `setFlag` loop on the session's register file.

## 5 Other

Motion speed change; heal everyone; per-character special!; change Yoahism; "I want to get stronger"; "I want lots of things"; "I want
to fly!"; HP / MP / SP max!; battle model change; menu settings; strongest (provisional); allow soul energy gain; "far away"
(彼方へ); character mode settings; special info settings.  (None executed yet; several of these change the save.)

## 6 Movie player

M.C.E.S. (N), CG movies (MOVIE_), picture-story movies (M), side story? (G), test (TEST).  Each opens a file-name entry pad (digits 0–9, アルファベット = letters, 入力終了 = done): the movie is picked by typing its name
(prefix N / MOVIE_ / M / G / TEST + number).

## 8 Battle player (02_battle_player.png)

* ボスバトル (boss battle) -> numeric id entry 0–9 + 入力終了 (done).
* イベントバトル (event battle): map number (-1), BGM number (-1), team number (-1), monster set number (0), monster set count (1),
  reset (red), start battle (yellow).
* ピットファイト (pit fight): pit fight index (0), get pit fight info, start pit fight; "pit fight data count (18)"; info for index 0:
  "Choose any 1 person and win 5 battles in a row!".

A quick way to reach any battle for live comparisons (event battle with a monster set id = the port's `SH2_BATTLE_DEMO` monsets).

## 9 For bug fixing

×力の解放イベント (power release event), ×堕天使アスタロト (fallen angel Astaroth) -- greyed (×).

## Findings used by the port (2026-10-14)

* **White Magic** is Nicolai-only: `CmdTopPC::SetTarget` case 0 checks the record class byte (+2) == 11 (user confirmed).  Healing
  crests do not add anyone.
* **Crest Magic** needs a crest-capable class (`CmdPC+0x50 != -1`: Blanca, Gepetto, Lucia, Anastasia, Joachim) and at least one crest
  spell; Karin / Yuri / Ouka / Hien / Nicolai are refused even with a crest (`sh2_field::cmd_top::RETAIL_CREST_USERS`).
* Opening the in-game menu rewrites `BTL0+0x10bc..0x133c` (the 12 x 0x10 ability / combo-key slots) between two encodings
  (`{kind, idx, 0xffff}` x4 and a byte-packed form); the field and the menu disagree on the layout, so don't diff that range.

## Japanese demos (checked 2026-10-14)

* **Furokuban** (`SH2JP`, SLPM_602.19): FIELD/MPS lists only the ~45 demo-route maps; no `DB_*` / `*_DB` maps at all.
* **Taikenban** (SLPM_602.14, Aug 2003; SBD archives with hashed names, so maps cannot be listed from the disc):
  * no debug-menu text anywhere on the disc or in RAM (デバ島, ミニゲーム, キャラ劇, the flag-page titles, ワールドマップポイント設定,
    バトルプレイヤー: 0 hits, checked on the title, the attract battle and in the field at Apoina Tower);
  * its 7,000-symbol executable has no mini-game or debug-island functions (only the generic `Dbg` print class);
  * the button shortcuts (Circle + R2, Square + R2, Circle + R1, Circle + R3, Circle + Select) do nothing on a real map (on retail they
    call the debug map's own events, so this was expected even if the engine hook exists);
  * leftovers it does have: 「デバッグまつり開催中！」 ("Debug festival in progress!") in `dataAccess::mSetupProgressSaveLoad` (the
    save/load progress screen; the demo cannot save) next to "Save Slot=%d" / "Slot%d= %d" / "mapName" debug prints, and in the map
    scripts the chest debug prompt 「フラグを無効にしますか？」 (disable the flag?) / 「デバッグメッセージ」 with `1BitFlag(%d) = %d`,
    the same hook the retail AP_00_DB test map carries.
  * The demo starts on a scenario picker: アポイナの塔 Apoina Tower (story intro + battle tutorial), 迷いの森の亡霊 Ghost of the lost
    forest, 華の都のかたすみで In a corner of the flower capital, 捕らわれの仲間 The captured companion.
* **Warp test (live):** the scenario picker's destination table holds the start maps (AP_01_U, AR_00_S, PA_00_S, SM_07_U; static copy
  0x3c51d0 in SLPM_602.14, runtime copy ~0x66a336).  Overwriting the first entry while the picker is open redirects "Apoina Tower":
  `AP_02_U` loads straight into that map (skipping the AP_01_U intro), `DB_00_U` makes the engine request `/MPS/DB_00_U.MSC` and hang
  on a black screen (reset needed).  So the debug map file is genuinely absent from the Taikenban, not just unreachable.  The same
  patch is a handy way to start the demo on any map it ships.
* Verdict: the debug island, Debug Island 2 and the mini-game are not in either demo; the mini-game exists only as the two empty rows
  of the retail Square + R2 menu.
