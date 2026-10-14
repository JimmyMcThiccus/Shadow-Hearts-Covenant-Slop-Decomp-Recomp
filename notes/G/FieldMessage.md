# FieldMessage

* base: `CPolObj`; allocation size: 0x1c; ctor JP `0x004a0d80`
* vtable stores: `+0x14 __vt__12FieldMessage`

| JP addr | size | method |
|---|---|---|
| `0x004a0d80` | 0x44 | `FieldMessage::FieldMessage()` |
| `0x004a0dd0` | 0x7c | `FieldMessage::~FieldMessage()` |
| `0x004a0e50` | 0x338 | `FieldMessage::CreateWindow(short, unsigned char, unsigned char, unsigned char, short)` |
| `0x004a1190` | 0xbc | `FieldMessage::DestroyWindow()` |
| `0x004a1250` | 0x140 | `FieldMessage::ChengeLayer(int)` |
| `0x004a1390` | 0x12c | `FieldMessage::OpenWindow(unsigned char, int)` |
| `0x004a14c0` | 0xb4 | `FieldMessage::CloseWindow(unsigned char, int)` |
| `0x004a1580` | 0x1bc | `FieldMessage::OpenMessage(char*)` |
| `0x004a1740` | 0x178 | `FieldMessage::ClearMessage()` |
| `0x004a18c0` | 0x94 | `FieldMessage::EnableKeyWait(short)` |
| `0x004a1960` | 0xac | `FieldMessage::SetSelectMessage(char*)` |
| `0x004a1a10` | 0x174 | `FieldMessage::StartSelect(short)` |
| `0x004a1b90` | 0xa8 | `FieldMessage::SetPosition(float, float)` |
| `0x004a1c40` | 0x130 | `FieldMessage::SetSize(short, short)` |
| `0x004a1d70` | 0x8c | `FieldMessage::StartKeyWait()` |
| `0x004a1e00` | 0xc4 | `FieldMessage::SetCursor(short)` |
| `0x004a1ed0` | 0xb58 | `FieldMessage::Polling()` |
| `0x004b5220` | 0x38 | `FieldMessage::SetVariable(unsigned char)` |
| `0x004b55e0` | 0x20 | `FieldMessage::GetState` |
| `0x004b6170` | 0x38 | `FieldMessage::SetCancel(unsigned char)` |
| `0x004b61f0` | 0x40 | `FieldMessage::SetSelectMode(unsigned char)` |
| `0x004b64a0` | 0x20 | `FieldMessage::GetResult` |

Decompiled source: `decomp/G/FieldMessage.c`.
