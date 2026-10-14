# KeyWait

Base class: `MenuObj`

Blinking 'press button' marker (down arrow icon) shown by `primWin::addKeyWait`.

## Virtual table (`__vt__KeyWait`)

| slot | function |
|---|---|
| 0x08 | `__dt__7KeyWaitFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__7KeyWaitFv` |
| 0x14 | `Update__7KeyWaitFiiUs` |
| 0x18 | `Connect__7KeyWaitFP4_QWD` |
| 0x1c | `Destroy__7KeyWaitFv` |
| 0x20 | `Clear__7KeyWaitFv` |

## Constructed by

`addKeyWait__7primWinFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x002808a0 | 0x80 | `__ct__7KeyWaitFv` | `KeyWait::KeyWait()` |
| 0x00280920 | 0xc4 | `__dt__7KeyWaitFv` | `KeyWait::~KeyWait()` |
| 0x002809f0 | 0xfc | `Create__7KeyWaitFv` | `KeyWait::Create()` |
| 0x00280af0 | 0xf8 | `SetPosition__7KeyWaitFi` | `KeyWait::SetPosition(int)` |
| 0x00280bf0 | 0x1c0 | `Polling__7KeyWaitFv` | `KeyWait::Polling()` |
| 0x00280db0 | 0x17c | `Update__7KeyWaitFiiUs` | `KeyWait::Update(int, int, unsigned short)` |
| 0x00280f30 | 0x54 | `Connect__7KeyWaitFP4_QWD` | `KeyWait::Connect(_QWD*)` |
| 0x00280f90 | 0x64 | `Destroy__7KeyWaitFv` | `KeyWait::Destroy()` |
| 0x00281000 | 0xe4 | `Clear__7KeyWaitFv` | `KeyWait::Clear()` |

## Open questions

- none recorded

Decompilation: `decomp/F/KeyWait.c`
