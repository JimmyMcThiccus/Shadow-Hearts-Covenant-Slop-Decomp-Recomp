# MenuRegister

Base class: `MenuObj`

Draws a numeric register (digits via sprite sheet) -- `SetRegister(index, value, flags)`/`Update`.

## Virtual table (`__vt__MenuRegister`)

| slot | function |
|---|---|
| 0x08 | `__dt__12MenuRegisterFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__7MenuObjFv` |
| 0x14 | `Update__12MenuRegisterFiiUs` |
| 0x18 | `Connect__12MenuRegisterFP4_QWD` |
| 0x1c | `Destroy__12MenuRegisterFv` |
| 0x20 | `Clear__12MenuRegisterFv` |
| 0x2c | `@24@__dt__12MenuRegisterFv` |

## Constructed by

`WinCreate__9BtlResultFi`, `__ct__7KeyWaitFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x0028d000 | 0x70 | `__ct__12MenuRegisterFv` | `MenuRegister::MenuRegister()` |
| 0x0028d070 | 0xac | `__dt__12MenuRegisterFv` | `MenuRegister::~MenuRegister()` |
| 0x0028d120 | 0xc0 | `SetRegister__12MenuRegisterFiUlUl` | `MenuRegister::SetRegister(int, unsigned long, unsigned long)` |
| 0x0028d1e0 | 0x1a0 | `Update__12MenuRegisterFiiUs` | `MenuRegister::Update(int, int, unsigned short)` |
| 0x0028d380 | 0x34 | `Connect__12MenuRegisterFP4_QWD` | `MenuRegister::Connect(_QWD*)` |
| 0x0028d3c0 | 0x2c | `Destroy__12MenuRegisterFv` | `MenuRegister::Destroy()` |
| 0x0028d3f0 | 0x38 | `Clear__12MenuRegisterFv` | `MenuRegister::Clear()` |
| 0x0028d430 | 0x8 | `@24@__dt__12MenuRegisterFv` | `@24@__dt__12MenuRegisterFv` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuRegister.c`
