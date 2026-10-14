# dispCash

Base class: `CPolObj`

Cash display: up to 9 digits with thousands separators (digit 10) and blank padding (12).

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x0 | `primWin *` | win |
| 0x18 | `s32` | cash |
| 0x1c | `u8[10]` | digits |

## Constructed by

`mSetupDispFile__12dispSaveFileFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x003a61f0 | 0x38 | `__ct__8dispCashFv` | `dispCash::dispCash()` |
| 0x003a6230 | 0x7c | `__dt__8dispCashFv` | `dispCash::~dispCash()` |
| 0x003a62b0 | 0x68 | `initialize__8dispCashFP7primTexiii` | `dispCash::initialize(primTex*, int, int, int)` |
| 0x003a6320 | 0x94 | `setPos__8dispCashFff` | `dispCash::setPos(float, float)` |
| 0x003a63c0 | 0x1c | `getPW__8dispCashFv` | `dispCash::getPW()` |
| 0x003a63e0 | 0x1b0 | `mSetupCash__8dispCashFv` | `dispCash::mSetupCash()` |
| 0x003a6590 | 0x1fc | `mCalcCash__8dispCashFv` | `dispCash::mCalcCash()` |

## Open questions

- none recorded

Decompilation: `decomp/F/dispCash.c`
