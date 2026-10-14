# MenuMessage

Base class: `PluralFontItem`

Typewriter message box. Per-glyph 0x30-byte packet entries (alpha @+0x17, width @+0xc, fade rate @+0x24) and macro entries (kind @+0x14, trigger glyph @+0x16, argument @+0x24). `Start()` is skipped if the text-speed option (MENU byte 0x274 bits 4-5) is 3 (instant). `Polling` reveals one glyph per `char_interval` ticks (slow 200 / normal 100 / fast 50, `SetDefault`), fades new glyphs in with `alpha += (rate*dt)>>24` (rate 0x83126f => 0x80 in ~16 ticks), and handles macros: 6 default, 5 set speed, 1/3/4 wait (state 10). `Return()` is the newline: cursor_x=0, cursor_y += line height + gap, line_no++. A `SendOnLocal` key icon (kind 4 only) is appended at the end ('more' marker).

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x20 | `u8` | state |
| 0x68 | `MenuObjTable` | icons |
| 0x74 | `u16` | stride |
| 0x76 | `u16` | n_chars |
| 0x78 | `u16` | n_visible |
| 0x7a | `u16` | cur_char |
| 0x7c | `u16` | n_rects |
| 0x7e | `u16` | n_lines |
| 0x80 | `u16` | fade_from |
| 0x82 | `u16` | cursor_x |
| 0x84 | `u16` | cursor_y |
| 0x86 | `u16` | line_no |
| 0x88 | `u16` | n_macro |
| 0x8a | `u16` | cur_macro |
| 0x8c | `s16` | char_interval |
| 0x8e | `s16` | char_timer |
| 0x90 | `u32` | fade_rate |
| 0x94 | `SendOnLocal *` | kbd_icon |

## Virtual table (`__vt__MenuMessage`)

| slot | function |
|---|---|
| 0x08 | `__dt__11MenuMessageFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__11MenuMessageFv` |
| 0x14 | `Update__11MenuMessageFiiUs` |
| 0x18 | `Connect__11MenuMessageFP4_QWD` |
| 0x1c | `Destroy__11MenuMessageFv` |
| 0x20 | `Clear__11MenuMessageFv` |
| 0x24 | `SetPosition__9MenuPlaceFff` |
| 0x28 | `SetSize__9MenuPlaceFff` |
| 0x2c | `SetAlpha__8MenuItemFUc` |
| 0x30 | `SetColor__8MenuItemFUcUcUc` |
| 0x34 | `SetBright__14PluralFontItemFf` |
| 0x38 | `SetOwner__8FontItemFP10MenuWindow` |
| 0x3c | `GetKeyPlace__9MenuPlaceFv` |
| 0x40 | `GetKeyRect__9MenuPlaceFP8DrawRect` |
| 0x44 | `AllotPacket__14PluralFontItemFP4_QWDP4_QWD` |
| 0x48 | `GetAllotCount__14PluralFontItemFv` |
| 0x4c | `Attach__9MenuPlaceFP10MenuWindow` |
| 0x50 | `Detach__9MenuPlaceFv` |
| 0x5c | `@60@__dt__11MenuMessageFv` |
| 0x60 | `Create__11MenuMessageFUsUc` |
| 0x64 | `GetFontEnv__14PluralFontItemFv` |

## Constructed by

`Read__17LSDCaptionHandlerFP10_LSDHANDLEP10RingBuffer`, `__ct__14LSDCaptionDataFv`, `addMessage__7primWinFiiPcib`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x0027d490 | 0x60 | `__ct__11MenuMessageFv` | `MenuMessage::MenuMessage()` |
| 0x0027d4f0 | 0x94 | `__dt__11MenuMessageFv` | `MenuMessage::~MenuMessage()` |
| 0x0027d590 | 0xe8 | `Create__11MenuMessageFUsUc` | `MenuMessage::Create(unsigned short, unsigned char)` |
| 0x0027d680 | 0xac | `ClearMessage__11MenuMessageFv` | `MenuMessage::ClearMessage()` |
| 0x0027d730 | 0x78 | `Return__11MenuMessageFv` | `MenuMessage::Return()` |
| 0x0027d7b0 | 0x184 | `Start__11MenuMessageFv` | `MenuMessage::Start()` |
| 0x0027d940 | 0x228 | `Finish__11MenuMessageFv` | `MenuMessage::Finish()` |
| 0x0027db70 | 0x1b4 | `SetOrderData__11MenuMessageFUssssUs` | `MenuMessage::SetOrderData(unsigned short, short, short, short, unsigned short)` |
| 0x0027dd30 | 0x258 | `SetMessageData__11MenuMessageFPcP8DrawRect` | `MenuMessage::SetMessageData(char*, DrawRect*)` |
| 0x0027df90 | 0x160 | `SetMacro__11MenuMessageFUs` | `MenuMessage::SetMacro(unsigned short)` |
| 0x0027e0f0 | 0x108 | `GetRect__11MenuMessageFUsP8DrawRect` | `MenuMessage::GetRect(unsigned short, DrawRect*)` |
| 0x0027e200 | 0xa0 | `SetDefault__11MenuMessageFv` | `MenuMessage::SetDefault()` |
| 0x0027e2a0 | 0x58c | `Polling__11MenuMessageFv` | `MenuMessage::Polling()` |
| 0x0027e830 | 0x9cc | `Update__11MenuMessageFiiUs` | `MenuMessage::Update(int, int, unsigned short)` |
| 0x0027f200 | 0xbc | `Connect__11MenuMessageFP4_QWD` | `MenuMessage::Connect(_QWD*)` |
| 0x0027f2c0 | 0x74 | `Destroy__11MenuMessageFv` | `MenuMessage::Destroy()` |
| 0x0027f340 | 0x8c | `Clear__11MenuMessageFv` | `MenuMessage::Clear()` |
| 0x0027f3d0 | 0x110 | `GetLastPosition__11MenuMessageFPsPs` | `MenuMessage::GetLastPosition(short*, short*)` |
| 0x0027f4e0 | 0x8 | `@60@__dt__11MenuMessageFv` | `@60@__dt__11MenuMessageFv` |

## Rust port

`message::Message` (+ tests).

## Open questions

- macro/escape byte encoding in the Shift-JIS stream is decoded by `FontDraw::Order(MenuMessage*, char*)` (section B)

Decompilation: `decomp/F/MenuMessage.c`
