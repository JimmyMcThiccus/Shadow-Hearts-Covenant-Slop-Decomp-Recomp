# SendOnLocal

Base class: `MenuObj`

Texture register block (TEX0/CLAMP/... for a RasterPacket + ClutRaster) sent in front of sprites that sample it; `Create(RasterPacket*, ClutRaster*, ...)`, `UpdatePacket`, `GetTex0`.

## Virtual table (`__vt__SendOnLocal`)

| slot | function |
|---|---|
| 0x08 | `__dt__11SendOnLocalFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__7MenuObjFv` |
| 0x14 | `Update__11SendOnLocalFiiUs` |
| 0x18 | `Connect__11SendOnLocalFP4_QWD` |
| 0x1c | `Destroy__11SendOnLocalFv` |
| 0x20 | `Clear__11SendOnLocalFv` |
| 0x2c | `@24@__dt__11SendOnLocalFv` |

## Constructed by

`Create__11MenuMessageFUsUc`, `Create__8MenuIconFc`, `GetReady__13GameOverSceneFv`, `WinCreate__9BtlResultFi`, `__ct__10ScrollMarkFv`, `__ct__10SoulEnergyFv`, `__ct__14MenuWindowFaceFv`, `__ct__14MenuWindowNoteFv`, `__ct__17MenuWindowCompactFv`, `__ct__17MenuWindowGeneralFv`, `__ct__17MenuWindowMessageFv`, `__ct__6CursorFv`, `__ct__7KeyWaitFv`, `__ct__8MenuFontFv`, `__ct__9MenuFlareFv`, `setWinMenuTex__7primTexFP10MenuWindowP11MenuTexturei`, `setWinTex__7primTexFP10MenuWindowii`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00277820 | 0x70 | `__ct__11SendOnLocalFv` | `SendOnLocal::SendOnLocal()` |
| 0x00277890 | 0xac | `__dt__11SendOnLocalFv` | `SendOnLocal::~SendOnLocal()` |
| 0x00277940 | 0x190 | `Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi` | `SendOnLocal::Create(RasterPacket*, ClutRaster*, bool, int)` |
| 0x00277ad0 | 0x164 | `Create__11SendOnLocalFP4_QWDUl` | `SendOnLocal::Create(_QWD*, unsigned long)` |
| 0x00277c40 | 0x8c | `UpdatePacket__11SendOnLocalFv` | `SendOnLocal::UpdatePacket()` |
| 0x00277cd0 | 0x6c | `SetTextureRegister__11SendOnLocalFUlUl` | `SendOnLocal::SetTextureRegister(unsigned long, unsigned long)` |
| 0x00277d40 | 0x100 | `GetTex0__11SendOnLocalFv` | `SendOnLocal::GetTex0()` |
| 0x00277e40 | 0x2d4 | `Update__11SendOnLocalFiiUs` | `SendOnLocal::Update(int, int, unsigned short)` |
| 0x00278120 | 0x34 | `Connect__11SendOnLocalFP4_QWD` | `SendOnLocal::Connect(_QWD*)` |
| 0x00278160 | 0x2c | `Destroy__11SendOnLocalFv` | `SendOnLocal::Destroy()` |
| 0x00278190 | 0x48 | `Clear__11SendOnLocalFv` | `SendOnLocal::Clear()` |
| 0x002781e0 | 0x8 | `@24@__dt__11SendOnLocalFv` | `@24@__dt__11SendOnLocalFv` |

## Open questions

- none recorded

Decompilation: `decomp/F/SendOnLocal.c`
