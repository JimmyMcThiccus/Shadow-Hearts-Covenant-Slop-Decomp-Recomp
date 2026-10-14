# MenuFlare

Base class: `MenuObj`

Additive light-trail attached to the cursor (shadow type 2): ring of fading sprites following the cursor path (`SetOffset`, `ClearAfter`, `Polling`).

## Virtual table (`__vt__MenuFlare`)

| slot | function |
|---|---|
| 0x08 | `__dt__9MenuFlareFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__9MenuFlareFv` |
| 0x14 | `Update__9MenuFlareFiiUs` |
| 0x18 | `Connect__9MenuFlareFP4_QWD` |
| 0x1c | `Destroy__9MenuFlareFv` |
| 0x20 | `Clear__9MenuFlareFv` |

## Constructed by

`SetShadow__6CursorFUc`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00286570 | 0x88 | `__ct__9MenuFlareFv` | `MenuFlare::MenuFlare()` |
| 0x00286600 | 0xbc | `__dt__9MenuFlareFv` | `MenuFlare::~MenuFlare()` |
| 0x002866c0 | 0x35c | `Create__9MenuFlareFv` | `MenuFlare::Create()` |
| 0x00286a20 | 0x160 | `SetOffset__9MenuFlareFffff` | `MenuFlare::SetOffset(float, float, float, float)` |
| 0x00286b80 | 0x6c | `ClearAfter__9MenuFlareFv` | `MenuFlare::ClearAfter()` |
| 0x00286bf0 | 0x80 | `Polling__9MenuFlareFv` | `MenuFlare::Polling()` |
| 0x00286c70 | 0x370 | `Update__9MenuFlareFiiUs` | `MenuFlare::Update(int, int, unsigned short)` |
| 0x00286fe0 | 0xb0 | `Connect__9MenuFlareFP4_QWD` | `MenuFlare::Connect(_QWD*)` |
| 0x00287090 | 0x7c | `Destroy__9MenuFlareFv` | `MenuFlare::Destroy()` |
| 0x00287110 | 0xa0 | `Clear__9MenuFlareFv` | `MenuFlare::Clear()` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuFlare.c`
