# P2Sprite

Copy of a **main-executable** class statically linked into FIELD.BIN (duplicated code of another section's class); documented by the owning section. Listed here for address mapping only.

| JP addr | size | method |
|---|---|---|
| `0x004ccc20` | 0x34 | `P2Sprite::SetHotSpot(float, float)` |
| `0x004ccca0` | 0x48 | `P2Sprite::SetSize(float, float)` |
| `0x004cccf0` | 0x34 | `P2Sprite::SetDirty()` |
| `0x004ccd30` | 0x48 | `P2Sprite::SetTexSize(float, float)` |
| `0x004ccd80` | 0x48 | `P2Sprite::SetTexPos(float, float)` |
| `0x004cce10` | 0x40 | `P2Sprite::SetFilter(int)` |
| `0x004cdbb0` | 0x48 | `P2Sprite::SetScale(float, float)` |

Decompiled source: `decomp/G/_OverlayCopies_P2Sprite.c`.
