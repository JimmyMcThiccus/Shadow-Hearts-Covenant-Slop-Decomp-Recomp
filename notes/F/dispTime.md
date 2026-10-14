# dispTime

Base class: `CPolObj`

Play-time display: 10 digit sprites `HHHH:MM:SS`; adds 16 per frame while running; digit 0xb = colon, 0xc = blank (leading zeros suppressed).

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x18 | `primWin *` | win |
| 0x1c | `primTex *` | tex0 |
| 0x20 | `primTex *` | tex1 |
| 0x28 | `f32` | x |
| 0x2c | `f32` | y |
| 0x30 | `s32` | ms |
| 0x34 | `u8` | running |
| 0x35 | `u8` | autostart |
| 0x36 | `u8[10]` | digits |

## Virtual table (`__vt__dispTime`)

| slot | function |
|---|---|
| 0x08 | `__dt__8dispTimeFv` |
| 0x0c | `Polling__8dispTimeFv` |

## Constructed by

`mSetupDispFile__12dispSaveFileFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x003a59b0 | 0x5c | `__ct__8dispTimeFv` | `dispTime::dispTime()` |
| 0x003a5a10 | 0xc4 | `__dt__8dispTimeFv` | `dispTime::~dispTime()` |
| 0x003a5ae0 | 0xbc | `initialize__8dispTimeFP7primTexiiib` | `dispTime::initialize(primTex*, int, int, int, bool)` |
| 0x003a5ba0 | 0x94 | `setPos__8dispTimeFff` | `dispTime::setPos(float, float)` |
| 0x003a5c40 | 0x1c | `getPW__8dispTimeFv` | `dispTime::getPW()` |
| 0x003a5c60 | 0x1b4 | `mSetupTime__8dispTimeFv` | `dispTime::mSetupTime()` |
| 0x003a5e20 | 0x354 | `mCalcTime__8dispTimeFv` | `dispTime::mCalcTime()` |
| 0x003a6180 | 0x68 | `Polling__8dispTimeFv` | `dispTime::Polling()` |

## Open questions

- none recorded

Decompilation: `decomp/F/dispTime.c`
