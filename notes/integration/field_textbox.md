# Field text boxes / message windows (retail look)

Goal: the field dialogue windows draw like retail from the original assets: ornate frame, face medallion + portrait, name label, white field
serif text, animated page-advance icon, open / close fades, window slots, SE cues.  Reference: live capture of the Ring Soul scene
(`screens/textbox/after/compare_reference_vs_port_ring_soul.png`, top = retail, bottom = port).

## What was decompiled

| class (JP FIELD.BIN / main exe) | what it does | where it is in the port |
|---|---|---|
| `CField::CreateWindow/RecreateWindow/SetWindowPos/SetWindowSize/OpenWindow/CloseWindow/OpenMessage/ClearMessage/KeyWait/KeyWaitStat` (JP 0x004b5040..0x004b5880, `decomp/G/CField.c`) | script ops 0x30-0x38: the record `_WndInfo` (`CField+0x60c + id*0x14`: `FieldMessage*`, +4 kind, +5 flags, +8/+0xa pos... ) is only a record, `OpenWindow` copies size + pos into the live window and starts `MenuWindow::Open(effect, ms)` | `script_ui::FieldWindow` (`x,y,cols,rows` = record, `win` = live `MenuWindow`), `host.rs` ops 0x30-0x3d |
| `CField::CreateName/SetNamePos/OpenName/CloseName` (0x004b5d60..) | name plate = a 16 x 1 window of kind 0 (no art), `SetNamePos` moves the live window at once, `OpenName(text, effect, ms)` = `OpenWindow` + `OpenMessage` | `UiState::create_name`, ops 0x39-0x3d |
| `CField::LoadFace/SetFacePos/SetFaceSize/OpenFace/CloseFace/ReleaseFace`, `FaceImage` (0x004a0440..0x004a0ae0) | `FaceImage::Create(id)` = `FileManeger::GetHandle(sm_pFace, id)` -> `MENU/FACE/FI_%03d.TEX`; a `MenuPolygon` with UV (0,0)-(0x66,0x80) in its own window of priority 0x10; `LoadFace` sets 96 x 96 (retail), `Open/Close` = `MenuWindow::Open/Close` | `script_ui::FaceSlot`, `textbox::draw_face` |
| `FieldMessage` (0x004a0d80..0x004a2a28), `FieldMessageData` (0x380 bytes: `+0x10 MenuWindow`, `+0xc4 FontDraw`, `+0x104 MenuMessage`, `+0x19c KeyWait`, `+0x278 Cursor`) | `CreateWindow(id, kind, font, 2, 0x100)`: `MenuWindow::Create(.., style = kind, 1)`, font item shadow (0, 1), `SetSize(30, 3)`; `Polling` state machine 3 open -> 9 typing -> 0xe key wait / 0xf select -> 1 idle, 4 closing -> 0; typed-line scroll (`Scroll(0, row)`); SE 0 / 2 / 3 in the select state | `FieldWindow::tick`, `state()`, `host::select_poll` |
| `FieldMessage::SetSize(cols, rows)` + `FontItem::GetRealWidth/Height` | window = `cols * REAL_W` x `rows * REAL_H`; `REAL_W = (u8)(22 * 0.8) = 17` (narrow flag), `REAL_H = 22 + shadow y 1 = 23` (US font 1 = `MFIELD.MSD`, cell 22 x 22) | `script_ui::REAL_W/REAL_H` |
| `FieldMessage::OpenMessage` / `SetPosition` for style 3 | a **note** window ignores the script x: `OpenWindow` only stores effect + time, the first `OpenMessage` sets the size from the order extents of the text, centres it (`256 - w/2`) and opens it | `FieldWindow::deferred_open`, `textbox::note_extent` |
| `MenuWindowMessage` (JP 0x00287bc0, US 0x00285730) | style 1: polygon 0 + sprites 0x14..0x17 of `COMMON/CMNMENU.DAT`; `Update`: `W' = W + sprite[0].priority (-6)`, polygon `W' + 33` wide, right cap at `W'`, rails stretched to `W'` | `textbox::message_frame` |
| `MenuWindowFace` (0x002871b0) | style 2: sprite 0x13 (the 112 x 128 round medallion) at the window origin | `textbox::face_frame` |
| `MenuWindowNote` (0x00288390) | style 3: sprites 0..6, `W' = W + sprite[0].priority (-32)` | `textbox::note_frame` |
| `KeyWait` (0x002808a0..0x00281000) | sprite 0x1d at (`W - 15`, `H - 20`) of the window; alpha `0x80 - (|t / 10| & 0xff)`, `t += pass time`, wraps 0x3c0 -> -0x3c0 (period 1.92 s); state machine 10 -> 11 -> 12 (circle press) -> 13 (release) | `textbox::key_alpha/key_icon`, `FieldWindow::key_t` |
| `MenuObj::UpdateTimer` (US 0x00271c60) | `sm_iPassTime = min(GetTimer() - prev, 33)` ms: every `MenuWindow` / `MenuMessage` poll advances by it | `UiState::tick` (16 / 17 ms per 60 Hz tick) |

## Asset formats

* **Frames**: `COMMON/CMNMENU.DAT` is a scene (`Msd`): 43 sprite records (0x20 bytes: id, priority, x, y, w, h, uv...), 5 polygon records, 17 attach
  files.  Attach files used here (all `MenuTexture` blobs, decoded with `sh2_gfx::texture::decode_menu_texture`):

  | attach | size | content |
  |---|---|---|
  | 8 | 88 x 120 | general / note frame pieces (note sprites 0..6 use the corner pieces at y 33..57) |
  | 9 | 40 x 104 | **dialogue frame**: the left curled cap (sprite 0x14 UV 1..39 x 1..95); the right cap is the same texels mirrored (u0 > u1); sprites 0x16 / 0x17 are 1 x 5 rail slices |
  | 10 | 112 x 128 | **round medallion** (face frame, sprite 0x13) |
  | 11 | 16 x 20 | **page-advance icon** (sprite 0x1d) |
  | 2 / 3 | 24 x 20 / 40 x 40 | cursor arrow / flare |

  Sprite / polygon record layout is the one parsed by `sh2_menu::msd`; the text-box relevant records are copied into `textbox::FrameRecs::builtin()`
  (tests run without the disc; `FrameRecs::from_msd` re-reads them and rejects a scene that is not the retail one, e.g. the JP demo, which
  then gets the old flat panel).  Untextured polygons are GS values: the channels are halved for the canvas (live: the fill is a dark slate;
  rgba (64,64,78,76) top, (10,8,10,76) bottom).
* **Portraits**: `MENU/FACE/FI_%03d.TEX`, 104 x 128, numbered by the face id the script gives `LoadFace(slot, id)` (Nicolai 018, Karin 006,
  Ring Soul flame ring 124 ...); the polygon shows texels 0..102 x 0..128.  `COMMON/CMNMENU.DAT` resource 6/7 holds the path pattern
  (`MENU/FACE/` + `FI_%03d.TEX`).  The round medallion is **not** part of the portrait; it is the kind-2 window behind it.
* **Text**: `MENU/DAT/MFIELD.MSD` attach 0 = font 1 (22 x 22 cells), drawn by the existing `FIELD_FONT` path (proportional, narrow x 0.8); the name
  plate uses CLUT row 4 (teal), the body row 0.

## The standard dialogue setup (census `examples/textbox_census.rs`, 379 US maps)

```
CreateWindow(2, kind 2, 0, 2)  SetWindowPos(10, 295)  OpenWindow(0, 50 ms)          the medallion
CreateName(0, 0, 0, 2)  SetNamePos(120, 302)  OpenName(text, 0, 15 ms)              name label (no frame)
LoadFace(0, id)  SetFacePos(12, 278)  SetFaceSize(102, 128)  OpenFace(0, 150 ms)     portrait, priority 0x10
CreateWindow(0, kind 1, 0, 2)  SetWindowPos(133, 338)  SetWindowSize(20, 3)  OpenWindow(0, 15 ms)
OpenMessage(text, id, talker)  ... KeyWait  ClearMessage ...  CloseName/Face(0, 20)  CloseWindow(0, 20 / 10)
```
Kinds in use: 1 (dialogue), 2 (medallion), 3 (narration note, 279 maps), 6 (general, 42 maps); effects are always 0 (fade); times are
`MenuObj::sm_iPassTime` milliseconds (15 / 50 / 150 / 20), not frames.

## What the port draws now

* `textbox::TextboxPlugin` draws into sprite layer `SPRITE_BASE + 6` (14), and the back fader (`SetFader(0, ..)`) into `SPRITE_BASE + 4` (12)
  so it stays behind the windows; `plugin::draw_field_ui` no longer draws windows / names / faces / the back fader (the old flat panels).
* Draw order: windows and name plates in creation order (`FieldWindow::seq`, the `MenuObjTable` priority 0), then the portraits (priority 0x10).
* Message frame / medallion / note strip / general frame (`cmd_common::general_frame`) exactly from the records; frames are drawn as soon as the
  window is open, with or without text (retail shows an open empty frame).
* Text: line by line (`$` / newline), typed with the option speed (`MENU+0x274` bits 4-5: 200 / 100 / 50 ms per glyph, instant), shadow (0, 1),
  lines scrolled out of the window fade by their visible fraction (the GS scissor is not reproduced); typed-line scroll like `Polling` state 9.
* Page icon: shown when typing is done and the script is at `KeyWait`; pulses 128 -> 32 -> 128 alpha in 1.92 s.  Circle **or** cross during
  the typing finishes it (retail `0x6000`), circle advances.
* Selection (`SelectInit/AddItem/Select`): items are the lines of the window, the silver spinning arrow with its flare points at the selected one
  from the left; horizontal lists (mode bit 0) use left / right; SE `CursorMove` / `Decide` / `Cancel` (`MenuSound::PlaySE` 0 / 2 / 3) are queued in
  `UiState::ses` and handed to the menu sound player.
* Dev aid: `SH2_TEXTBOX_DEMO=ring|select|note|all` (+ `SH2_TEXTBOX_DEMO_SPEED=instant`) puts the Ring Soul dialogue of the reference
  capture, a Yes / No list and a narration note on any field after 200 ticks.

## Verification

* Reference (live capture of the Ring Soul scene) vs port demo (same positions 133,338 / 120,302 / 12,278, face 124): frame, caps, rails, medallion,
  portrait, name colour, row pitch (22 px), page icon position and shape match in position and shape at 4x zoom (`screens/textbox/after/`).
* Real script run (`SH2_START_MAP=AP_02_U`, Nicolai / Karin dialogue): before / after in `screens/textbox/before` / `after`.
* Unit tests: `textbox::tests` (frame geometry of both frames, icon position + alpha curve, line split, typed reveal, whole dialogue draw order,
  open / close timing 50 ms = 3 ticks, note window opens with its first message), `script_ui::tests`.  `cargo test -p sh2_field` (disc env set) passes.

## Open / guesses

* Typing speed: the retail interval table (200 / 100 / 50 ms) is in `MenuMessage::SetDefault`; the port now advances windows by real time
  (16.7 ms per 60 Hz tick).  The old port polled with 32 ms per tick (about 1.9x too fast if the retail frame is 16.7 ms).  If the retail field
  runs at 30 fps the 33 ms clamp of `UpdateTimer` gives the same real-time speed; not checked against a live typing capture (the world-map
  state loaded in PCSX2 during this work could not be used; `sm_iPassTime` at gp-0x7d00 read 0 there).
* Name plates type out like any `MenuMessage` (decomp: `OpenName` -> `OpenMessage`, `MenuMessage::Start` honours the speed option).  Previously instant.
* Text clipping: retail clips to the window rectangle; the port fades partly visible lines instead.
* Per-glyph fade-in alpha of the typed characters is not drawn (existing limitation of the text path); the retail `...` of the US scripts is a
  wider glyph than the ASCII dots used in the demo text.
* Select windows: item rectangles (`MenuMessage::GetRect`) are approximated by measured text widths; cancel still returns -2 (retail result is the
  short 0xffff).
* The back fader no longer dims the radar / other sprite layers below layer 12.
* The JP demo disc keeps the flat fallback frame (its CMNMENU scene differs).
* Kinds 4, 5, 7 (`Frame`, `Plain`, `Compact`) are not used by any US script and are not drawn.

## Regression checks run

* `cargo test -p sh2_field` with the disc env set (138 + integration tests, incl. `retail_story` / `retail_route`): all pass.
* `script_corpus --us --map AP_00_U / AP_02_U / AP_03_U / AD_01_U`: no unimplemented ops, 0 stuck jobs (AD_02_U / BO_02_U did not finish within
  120 s in this debug build; the whole-disc sweep was not completed, 25 min without output).
* `sh2_app --us --autoplay --boost 80 --shots`: field, world map, battle command menu and ring frames unchanged.
* Dev tools added: `sh2_menu` examples `face_dump`, `font_cells`; `sh2_field` example `textbox_census` (window / name / face op argument census).
