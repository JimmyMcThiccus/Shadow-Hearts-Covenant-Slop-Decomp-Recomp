# openingMessage

Base class: `CPolObj`

Title screen driver (switch on state @0xe0, see title_flow.md). Created by `CDMYStage::Start`; owns the fader window, title sprites (6 `prim2D`), menu window + cursor, music/sound objects, the `dataAccess` and the attract battle.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x28 | `GsxCamera *` | cam |
| 0x54 | `s32` | disp_w |
| 0x58 | `s32` | disp_h |
| 0x5c | `primSound *` | snd |
| 0x60 | `primMusic *` | bgm |
| 0x64 | `primWin *` | fader |
| 0x6c | `primWin *` | title |
| 0x70 | `primWin *` | menu |
| 0x74 | `primCursor *` | cursor |
| 0x78 | `s32` | sel |
| 0x80 | `prim2D *[6]` | title_sprite |
| 0xbc | `s32` | n_title_sprite |
| 0xc4 | `s32` | pulse |
| 0xd0 | `void *` | d0 |
| 0xd4 | `openingBattleDemo *` | demo |
| 0xd8 | `dataAccess *` | data_access |
| 0xdc | `install *` | install |
| 0xe0 | `s32` | state |
| 0xe4 | `s32` | next_state |
| 0xe8 | `s32` | e8 |
| 0xec | `s32` | timer |
| 0xf0 | `s32` | cb_event |

## Virtual table (`__vt__openingMessage`)

| slot | function |
|---|---|
| 0x08 | `__dt__14openingMessageFv` |
| 0x0c | `Polling__14openingMessageFv` |
| 0x18 | `@24@__dt__14openingMessageFv` |
| 0x1c | `DelayDelete__17DelayDeleteObjectFv` |

## Constructed by

`Start__9CDMYStageFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x003a8340 | 0x14 | `LSD_CB__14openingMessageFv` | `openingMessage::LSD_CB()` |
| 0x003a83f0 | 0x110 | `__ct__14openingMessageFv` | `openingMessage::openingMessage()` |
| 0x003a8500 | 0x170 | `__dt__14openingMessageFv` | `openingMessage::~openingMessage()` |
| 0x003a8670 | 0x134 | `initialize__14openingMessageFv` | `openingMessage::initialize()` |
| 0x003a87b0 | 0x2a4 | `changeDispMode__14openingMessageFii` | `openingMessage::changeDispMode(int, int)` |
| 0x003a8a60 | 0x15b8 | `Polling__14openingMessageFv` | `openingMessage::Polling()` |
| 0x003aa020 | 0x24 | `CBEntry__14openingMessageFiPv` | `openingMessage::CBEntry(int, void*)` |
| 0x003aa050 | 0x108 | `mSetupFader__14openingMessageFv` | `openingMessage::mSetupFader()` |
| 0x003aa160 | 0x48 | `mReleaseFader__14openingMessageFv` | `openingMessage::mReleaseFader()` |
| 0x003aa1b0 | 0xccc | `mSetupTitleWin__14openingMessageFv` | `openingMessage::mSetupTitleWin()` |
| 0x003aae80 | 0xbc | `mReleaseTitleWin__14openingMessageFv` | `openingMessage::mReleaseTitleWin()` |
| 0x003aaf40 | 0x70 | `mReleaseMenuWin__14openingMessageFv` | `openingMessage::mReleaseMenuWin()` |
| 0x003aafb0 | 0x10c | `mSetupTrialWin__14openingMessageFv` | `openingMessage::mSetupTrialWin()` |
| 0x003ab0c0 | 0x48 | `mReleaseTrialWin__14openingMessageFv` | `openingMessage::mReleaseTrialWin()` |
| 0x003ab110 | 0x174 | `mSetupTrialMainWin__14openingMessageFv` | `openingMessage::mSetupTrialMainWin()` |
| 0x003ab290 | 0x48 | `mReleaseTrialMainWin__14openingMessageFv` | `openingMessage::mReleaseTrialMainWin()` |
| 0x003ab2e0 | 0x1a8 | `mSetupTrialMovieWin__14openingMessageFv` | `openingMessage::mSetupTrialMovieWin()` |
| 0x003ab490 | 0x48 | `mReleaseTrialMovieWin__14openingMessageFv` | `openingMessage::mReleaseTrialMovieWin()` |
| 0x003ab500 | 0x8 | `@24@__dt__14openingMessageFv` | `@24@__dt__14openingMessageFv` |

## Rust port

`title::OpeningMessage`.

## Open questions

- none recorded

Decompilation: `decomp/F/openingMessage.c`
