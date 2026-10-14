# dataAccess — Save / Load / device-check screen

`dataAccess` (0x00391cd0..0x00399d60, 38 functions) is a `CPolObj` registered with `CPoller(0x48)` prio 0x80. It
drives `SaveData` (global 0x00421e70; `DAT_00421e90` = open device, `DAT_00421e94` = io state: 0 none/error, 1 busy,
2 done, 3 failed) and uses `primWin`/`primCursor`/`primSound` (section B) for the UI. Rust: `sh2_menu::dataaccess`.

* `initialize(mode, cb, arg)`: modes **0 = save**, **1 = load**, **2 = initial device check**. Modes 0/1 start in state 1 and
  order `SAVELOAD/SAVELOAD.DAT` (153 KB texture bundle, delivered to `DVD_CBFunc` -> `primTex`); mode 2 creates a `deviceChecker`
  and runs `mInitialDeviceCheck` (its own state, +0x150) until it needs UI.
* `start(STARTMODE, x, y)` (0x00392210): sets the 'go' flag (+0x173) and the cursor start position; STARTMODE 0 = interactive screen,
  1 = go straight to load from the title, 3/4 = other.
* Callback `cb(event, arg)` (+0x24/+0x28): events **0** background ready, **1** screen shown, **2** no usable device,
  **3** save found / saved (also "quit"), **4** finished (object may be freed), **5** slot loaded, **6** initial check wants the UI.
  Event 4 is always last; after 5 the game jumps to the loaded map (`FieldMapJump(GetSavedMpsName(0), -2)`).

## Save/Load state machine (`Polling`, state @+0x160)

| state | meaning | next |
|---|---|---|
| 0 | (mode 2 only) `mInitialDeviceCheck` | -> 0x1d when it returns 1 (or 0x1c) |
| 1 | wait for texture (`m_TexRead`) + go flag, `mSetupBG`, cb(0) | 2 |
| 2 | fade finished, cb(1) | 5 |
| 3 / 4 | rebuild device selection after a cancel/fade | 5 |
| 5 | **device select** (Memory Card 1 / 2 / HDD): O -> `mOpenDevice(sel)` + progress bar -> 6; X -> fade -> 0x19 | |
| 6 | opening: poll `SaveData` io state. Fail (3) -> warning (device or system file) -> 7 (next 0x19). Not formatted (`SaveDevice+0xc==0`): retry up to 3 times via 8, then warning -> 7 (next 9 for cards / 0x19 for HDD). OK: build slot flags (`SystemFile` slot byte0 == 0xff => empty). Load with no used slot: warning "no save data" -> 7 (0x19). Otherwise -> 0xe | |
| 7 | warning popup, `mCheckWarning` (O/X) -> `next_state` (+0x164) | |
| 8 | re-open device (state 6) | 6 |
| 9 / 10 | **format query** (card only): O on "format" -> `Format()`, progress 4/frame -> 0xb | |
| 0xb | format progress; ok -> 0xd (message "formatted", then 0xe in save mode); fail -> warning, 7->8 | |
| 0xe | `mSetupSelectFile`: file list (15 slots, 3 visible, `dispSaveFile` panels) | 0xf |
| 0xf | **file select**: up/down scroll (0x10 / 0x11, 12 frames), X -> 0x19, O: load & slot empty -> buzzer (SE 4); save & `free < 0x63 KB` -> warning "not enough space" -> 0x16 (next 0x19); else -> 0x12 | |
| 0x12 | build the Yes/No query (Save: overwrite? Load: load?) | 0x13 |
| 0x13 | answer: O on Yes -> 0x14 (disable reset: `CPause::DisableReset`), else back to 0xf | |
| 0x14 | fade query, `GetSaveDataSlot(&info)` for save (fills the slot summary from live data) | 0x15 |
| 0x15 | **execute**: `SaveData::Save(slot)` / `Load(slot)`; progress +1/frame; ok (2) -> complete SE 0x1000, "done" window, disp panels refreshed -> 0x18; fail -> warning -> 0x17 (next 0x19) | |
| 0x16 / 0x17 | warning acknowledged -> `next_state` | |
| 0x18 | done window: O -> `Close()`, cb(3 save / 5 load), fade -> 0x1c | |
| 0x19 | quit: fade windows | 0x1a |
| 0x1a | `SaveData::Close`, `mSetupQuit` ("quit?" Yes/No) | 0x1b |
| 0x1b | answer: O on Yes -> cb(3) (mode 1) fade -> 0x1c; X or No -> 3 | |
| 0x1c | wait fade; (event 5 only: restore brightness `SetBright(v*0.03+0.7)`, `FieldMapJump`) release BG | 0x1d |
| 0x1d | (once) cb(4); call `Run` virtual (self delete) | |

Resets are disabled around device writes (`CPause::DisableReset/EnableReset`).

## Initial device check (`mInitialDeviceCheck`, state @+0x150)

0: `checkDeviceAll`; 2: poll results (`deviceChecker+0x24` done flag): no active device -> result 0 -> 5; a device with saved data -> 3
(cb(3) if its system slot table has data, else cb(2)) -> 4 (return 1); no free device -> result 1 (cards but unusable) or 2 (only HDD) -> 5; free card
available -> result 3 -> 5. 5: order the SAVELOAD texture (cb(6) = needs UI, switches the display mode in `openingMessage`), `mSetupBG`,
start `checkPollMC` (hot-plug polling unless result 3) -> 6. 6: device status screen; O/X -> 8 (release, `finishPollMC`, fade) -> 1
(close device, check again) or 9 (result 3: leave -> cb(2) -> 7). 0xb..0x16: create the system file (`SaveData::CreateSystem`, progress,
success message) and format flow, same widgets as the main screen.

Messages (`dataMess_*_J`, `initialMess_*_J`, indexed by device kind 0/1/2): deviceWarning, systemWarning, deviceUnformat,
deviceNoSaveData, saveQueryOverWrite/SaveNote/SaveProgress*, saveWarning, deviceExistSaveData.

## deviceChecker

`initialize` allocates per-device status; `checkDeviceAll` -> `Polling` -> `mCheckAll` (opens MC1, MC2 then HDD one by one with
`SaveData::Open`, reads the system file, records `{status, has_save, free_kb}`), sets the done flag @+0x24. `checkPollMC`/`mPollMC`
re-probes the cards each frame (`sceMcGetInfo`) so a swapped card is detected (`isChangeStatus`). `getActiveDeviceNum`,
`getSavedDeviceNum`, `getFreeDeviceNum`, `isOnlyHDD`, `isHDD` summarise.
