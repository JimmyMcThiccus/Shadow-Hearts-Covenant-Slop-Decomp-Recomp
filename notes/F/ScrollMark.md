# ScrollMark

Base class: `MenuObj`

Four blinking arrows at the window edges telling which directions have more content (`SetMark(mask)`: 1 up, 2 down, 4 left, 8 right; `SetArea`).

## Virtual table (`__vt__ScrollMark`)

| slot | function |
|---|---|
| 0x08 | `__dt__10ScrollMarkFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__10ScrollMarkFv` |
| 0x14 | `Update__10ScrollMarkFiiUs` |
| 0x18 | `Connect__10ScrollMarkFP4_QWD` |
| 0x1c | `Destroy__10ScrollMarkFv` |
| 0x20 | `Clear__10ScrollMarkFv` |

## Constructed by

`CreateScrollMark__10MenuWindowFUc`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x0027b330 | 0x70 | `__ct__10ScrollMarkFv` | `ScrollMark::ScrollMark()` |
| 0x0027b3a0 | 0xac | `__dt__10ScrollMarkFv` | `ScrollMark::~ScrollMark()` |
| 0x0027b450 | 0x3a0 | `Create__10ScrollMarkFUcP10MenuWindowUc` | `ScrollMark::Create(unsigned char, MenuWindow*, unsigned char)` |
| 0x0027b7f0 | 0x104 | `SetMark__10ScrollMarkFUc` | `ScrollMark::SetMark(unsigned char)` |
| 0x0027b900 | 0x254 | `SetArea__10ScrollMarkFUcffff` | `ScrollMark::SetArea(unsigned char, float, float, float, float)` |
| 0x0027bb60 | 0x5c | `Polling__10ScrollMarkFv` | `ScrollMark::Polling()` |
| 0x0027bbc0 | 0x254 | `Update__10ScrollMarkFiiUs` | `ScrollMark::Update(int, int, unsigned short)` |
| 0x0027be20 | 0xcc | `Connect__10ScrollMarkFP4_QWD` | `ScrollMark::Connect(_QWD*)` |
| 0x0027bef0 | 0x68 | `Destroy__10ScrollMarkFv` | `ScrollMark::Destroy()` |
| 0x0027bf60 | 0x6c | `Clear__10ScrollMarkFv` | `ScrollMark::Clear()` |

## Open questions

- none recorded

Decompilation: `decomp/F/ScrollMark.c`
