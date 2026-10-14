# CmdScoreRankFrame

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x00477970`
* embedded sub-objects: `+0xb8 MenuTexture`, `+0xf8 SendOnLocal`, `+0x128 MenuSprite`, `+0x188 MenuText`, `+0x208 FontDraw`
* vtable stores: `+8 __vt__17CmdScoreRankFrame`

| JP addr | size | method |
|---|---|---|
| `0x00477970` | 0xac | `CmdScoreRankFrame::CmdScoreRankFrame()` |
| `0x00477a20` | 0xf4 | `CmdScoreRankFrame::~CmdScoreRankFrame()` |
| `0x00477b20` | 0x20c | `CmdScoreRankFrame::CreateScene(CmdScore*)` |
| `0x00477d30` | 0x8 | `CmdScoreRankFrame::~CmdScoreRankFrame()` |
| `0x00477d40` | 0x8 | `CmdScoreRankFrame::~CmdScoreRankFrame()` |

Decompiled source: `decomp/G/CmdScoreRankFrame.c`.
