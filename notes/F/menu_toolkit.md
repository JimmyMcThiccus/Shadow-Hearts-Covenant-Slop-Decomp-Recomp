# Menu toolkit (section F) — widget model, scenes, data

Source: JP demo `SLPM_602.19`, code range 0x00264de0 .. 0x00291b9c (Metrowerks, ~480 functions; `MenuObj.cpp`,
`MenuWindow.cpp`, `MenuScene.cpp`, ... linked contiguously) plus the save/title code at 0x00327ef0..0x0032a700,
0x0037d990..0x00383d38, 0x00391cd0..0x00399d60 and 0x003a4650..0x003ad2c0.
Rust port: `port/crates/sh2_menu` (modules `widget`, `window`, `cursor`, `message`, `msd`, `scene`, `gfx`).
Per-class notes: `notes/F/<Class>.md`; cleaned decompilation: `decomp/F/<Class>.c`.

## 1. Architecture in one picture

```
CApp::Run  ->  CPoller(0x60/0x48/0x54)  ->  Menu::Run / widget::Polling
World OT layer 13  <-  MenuRender (VIF1Prim, sm_menuRender)         [MenuObj statics]
  MenuRender.objs : MenuObjTable (priority ordered)
     MenuWindow*                                  (MenuObj::AddOT)
        frame decoration (MenuWindowGeneral|Message|Face|Note|Frame|Plain|Compact)  @+0x3c
        ScrollData @+0x40, ScrollMark @+0x44, Scissor @+0x4c
        places  : MenuPlace chain @+0x38  (MenuText, MenuMessage, MenuSprite, MenuPolygon, MenuGroup...)
        objs    : MenuObjTable @+0x18     (attached places + free objects, drawn in priority order)
     Cursor*                                       (also an OT member; follows a MenuPlace of a window)
Menu (CPolObj, CPoller prio 0x80)  ->  MenuScene list (one .MSD each, one active)
```

* **Everything is a `MenuObj`** (0x18 bytes): `DelayDeleteObject` links, vptr@8, `next`@0xc for `MenuObjTable`,
  dirty masks@0x10/0x11, flags@0x12 (render, poll, in-table, delay-delete, created), `priority`@0x14, `id`@0x16.
* **`MenuPlace`** adds geometry + cursor grid coordinates; **`MenuItem`** adds packet memory + tint + blink.
  Leaf widgets: `MenuSprite`, `MenuPolygon`, `MenuText`, `MenuMessage`, `MenuFont`, `MenuFontItalic`;
  container: `MenuGroup`.
* **`MenuWindow`** is the unit the game opens/closes: style decoration, scrolling grid, children.
* **Rendering**: each widget keeps *two* GS packet buffers (one per VIF1 frame, selected by `m_Env__8VIF1Prim & 1`) and
  rebuilds only the parts whose dirty bit is set (`Update(x16, y16, alpha)`), then `Connect(prev)` chains them into
  the OT. Coordinates passed down are 12.4 fixed point screen offsets (centre 0x7000/0x7200 of the 512x448 frame);
  alpha is Q15 (0x8000 = 1). The port replaces this with immediate `gfx::DrawCmd`s in the same draw order.
* **Time** is the SysTool timer (`MenuObj::UpdateTimer`, called once per frame by `MenuRender::getPacket`):
  `sm_iPassTime` (ints) and `sm_fPassTime` (float) drive every animation. One frame = 16 ticks on the title code.

## 2. MenuWindow

Style code (`MenuWindow::Create(style,...)`, stored in wflags bits 6-8): 1 Message, 2 Face, 3 Note, 4 Frame, 5 Plain,
6 General, 7 Compact. All decorations are assembled from the **common scene** (`COMMON/CMNMENU.DAT`, 33 sprite and
2 polygon records, 14 attached textures): Note = sprites 0-6; General = sprites 8-0x11 + polygon 1; Message = sprites
0x14-0x17 + polygon 0; Face = sprite 0x13; Compact = sprites 0x18-0x1c. Plain/Frame use a built-in vertical gradient
(0x30,0x30,0x60 -> 0x20,0x20,0x40).

Open/close effects (`Open(effect, frames)` / `Close`): 0 fade, 1/2 slide vertically from above/below (start y =
-(h+100) / 548), 3/4 slide horizontally (start x = -(w+100) / 612), 5 zoom (clip rect grows from the centre).
State byte: 0 closed, 1 open, 5 sliding, 6 zoom, 7 fade. `Close` = open-reversed + render flag cleared by `Finish()`.

Scrolling: `ScrollData` holds the visible grid (cols x rows) and cell size; places carry `(col,row)`;
`AllotPacket()` attaches only places inside the visible grid (+1 line while scrolling). Scroll animation is an
exponential approach (`step = delta * dt * 0.01`), optionally speed-limited per axis. `ScrollMark` shows 4 arrows.

Cursor navigation lives in the window: `GetPlace(dir,col,row)` finds the nearest selectable place in a direction,
`MovePlace` additionally wraps (window flags 0xb1 bit3 = wrap horizontally, bit4 = wrap vertically — record
bytes 0x19 bits 3/4), `GetCornerPlace` returns row/column extremes (note the original compares the *column* with the
row argument for RIGHT — mirrored in the port), `SetCursor(cursor, axis)` snaps to the place nearest the cursor.

## 3. Cursor

Image + optional shadow polygon (type 1) or additive flare trail (type 2). Direction 8/4/2/1 = image to the left /
right / above / below of the pointed rectangle, pointing at it. Target tip = rect edge ± gap (default 1). Smooth
follow `pos += (target-pos)*dt*0.01`; snaps and clears the moving state when both deltas < 1 px. `rotate` spins about X.
`Select(place)` = scroll the window to reveal the place + `place->IsSelected(cursor)` (cancels the previous place,
sets `selected`, sets the target from `place->GetKeyRect()`; groups report their key child's rect). Cursor position is
stored window-local while on a place (`ConvertScreen` adds window pos + scroll offset).

## 4. MenuMessage (typewriter)

See `notes/F/MenuMessage.md`. Speed option (MENU byte 0x274 bits 4-5): 0 slow 200, 1 normal 100, 2 fast 50, 3 instant.
Glyph fade-in `alpha += (0x83126f * dt) >> 24` per frame until 0x80.

## 5. Scenes and data

A **scene** is an `.MSD` file from `MENU.PKB` (`MENU/MSD/*.MSD`, `MENU/DAT/CMDMENU.MSD`, `MENU/DAT/MFIELD.MSD`) or
`COMMON.PKB` (`COMMON/CMNMENU.DAT`). Format and the directory of MENU.PKB: `notes/F/msd_format.md`.
`MenuScene::OrderFile` -> DVD read -> pointer relocation -> `Initialize` (chunk index by type) -> `GetReady()` builds
windows via `SetData(index, widget)`:

| chunk type | record | stride | `SetData` target | notes |
|---|---|---|---|---|
| 0 | resource name | 8 | (strings) | `[ptr][u16][u16]` e.g. `MENU/IMG/GO/GO_%03d.TEX` |
| 1 | text | 0xc | MenuText/Message text source | `[ptr sjis][ptr sjis alt][i32]` |
| 2 | FontDraw canvas | 0x10 | `FontDraw` | psm, flags, width, height, clut |
| 3 | cursor | 0xc | `Cursor` | type, shadow, direction, rotate, back-object |
| 4 | window | 0x1c | `MenuWindow` | x,y,w,h, scroll cols/rows, open/close ticks, effects, style, clip, wrap |
| 5 | group | 0x18 | `MenuGroup` | x,y,col,row,w,h,label,alpha |
| 6 | sprite | 0x20 | `MenuSprite` | x,y,w,h,col,row,label,flags,rgba,u0,u1,v0,v1 |
| 7 | polygon | 0x3c | `MenuPolygon` | 4 vertices, 4 RGBA, 4 UV |
| 8 | text | 0x1c | `MenuText` | x,y,col,row,text id,rgba,font,csa/spacing,shadow,mode |
| 9 | message | 0x20 | `MenuMessage` | as text + max chars |
| 10 | font | 0x1c | `MenuFont` | font index, count |
| 11 | italic font | 0x18 | `MenuFontItalic` | name ptr |
| 12 | attach file | 0xc | `FindAttachFile(id)` | embedded blobs (textures `.TEX`, nested tables) |

Game code (FIELD.BIN `Cmd*` menus, section G; BATTLE.BIN, section H) calls `Scene::SetData(i, new widget)` and
`window->AddPlace(widget)` and sets the cursor; the toolkit has no hard-coded layouts.

## 6. Key facts for the port

* Pad bits (menu code): UP 0x10, RIGHT 0x20, DOWN 0x40, LEFT 0x80, L2/R2 0x100/0x200, L1/R1 0x400/0x800, TRIANGLE
  0x1000, **CIRCLE 0x2000 = OK**, **CROSS 0x4000 = cancel** (JP convention), SQUARE 0x8000, START 0x8.
  `Menu::GetKey`: `keys = (trigger & 0xff0f) | (repeat & 0xf0)`.
* Sound IDs used by menus: 0 move, 2 decide, 3 cancel, 4 buzzer, 0x1000 complete (`primSound::play`).
* Colour/alpha: 0x80 = 1.0. Menu coordinate space 512x448; the title switches the display to 640x448 (movie/title) and
  back (`openingMessage::changeDispMode`).
* `MENU` save section byte 0x274 is the options byte: bits0-1 vibration, bits2-3 sound out, bits4-5 text speed.
