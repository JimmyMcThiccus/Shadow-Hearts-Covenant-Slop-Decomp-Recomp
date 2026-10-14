# deviceChecker

Probes the three devices: `checkDeviceAll` -> `mCheckAll` (opens each, reads the system file), `checkPollMC` / `finishPollMC` poll card hot-plug (`mPollMC`), queries `getActiveDeviceNum`, `getSavedDeviceNum`, `getFreeDeviceNum`, `isOnlyHDD`, `isHDD`, `isChangeStatus`, `closeDevice`.

## Virtual table (`__vt__deviceChecker`)

| slot | function |
|---|---|
| 0x08 | `__dt__13deviceCheckerFv` |
| 0x0c | `Polling__13deviceCheckerFv` |

## Constructed by

`initialize__10dataAccessFQ210dataAccess10ACCESSMODEPFiPv_vPv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x003990f0 | 0x3c | `__ct__13deviceCheckerFv` | `deviceChecker::deviceChecker()` |
| 0x00399130 | 0x84 | `__dt__13deviceCheckerFv` | `deviceChecker::~deviceChecker()` |
| 0x003991c0 | 0x58 | `initialize__13deviceCheckerFv` | `deviceChecker::initialize()` |
| 0x00399220 | 0x38 | `checkDeviceAll__13deviceCheckerFv` | `deviceChecker::checkDeviceAll()` |
| 0x00399260 | 0x38 | `checkPollMC__13deviceCheckerFv` | `deviceChecker::checkPollMC()` |
| 0x003992a0 | 0x34 | `finishPollMC__13deviceCheckerFv` | `deviceChecker::finishPollMC()` |
| 0x003992e0 | 0x74 | `Polling__13deviceCheckerFv` | `deviceChecker::Polling()` |
| 0x00399360 | 0x304 | `mPollMC__13deviceCheckerFv` | `deviceChecker::mPollMC()` |
| 0x00399670 | 0x434 | `mCheckAll__13deviceCheckerFv` | `deviceChecker::mCheckAll()` |
| 0x00399ab0 | 0x60 | `closeDevice__13deviceCheckerFv` | `deviceChecker::closeDevice()` |
| 0x00399b10 | 0x34 | `isChangeStatus__13deviceCheckerFv` | `deviceChecker::isChangeStatus()` |
| 0x00399b50 | 0x6c | `getActiveDeviceNum__13deviceCheckerFv` | `deviceChecker::getActiveDeviceNum()` |
| 0x00399bc0 | 0x84 | `getSavedDeviceNum__13deviceCheckerFv` | `deviceChecker::getSavedDeviceNum()` |
| 0x00399c50 | 0xa4 | `getFreeDeviceNum__13deviceCheckerFv` | `deviceChecker::getFreeDeviceNum()` |
| 0x00399d00 | 0x5c | `isOnlyHDD__13deviceCheckerFv` | `deviceChecker::isOnlyHDD()` |
| 0x00399d60 | 0x3c | `isHDD__13deviceCheckerFv` | `deviceChecker::isHDD()` |

## Rust port

`dataaccess::check_all`.

## Open questions

- none recorded

Decompilation: `decomp/F/deviceChecker.c`
