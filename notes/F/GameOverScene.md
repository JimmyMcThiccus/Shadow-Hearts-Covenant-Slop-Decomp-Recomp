# GameOverScene

Base class: `MenuScene`

State machine (pointer-to-member at +0x58): GetReady, ReadData, Realize, ExitRealize, SelectLoad, ExitSelectLoad. Image index from MENU `0x29c` (random among `0x29e` mask bits if negative).

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x58 | `ptmf` | state_fn |
| 0x64 | `GameOverRealize *` | realize |
| 0x68 | `GameOverSelect *` | select |
| 0x6c | `dataAccess *` | data_access |

## Virtual table (`__vt__GameOverScene`)

| slot | function |
|---|---|
| 0x08 | `__dt__13GameOverSceneFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `GetRealHeap__9MenuSceneFP9BufMemoryi` |
| 0x14 | `GetReady__13GameOverSceneFv` |
| 0x18 | `Release__13GameOverSceneFv` |
| 0x1c | `Run__13GameOverSceneFv` |
| 0x20 | `Shutdown__9MenuSceneFv` |
| 0x24 | `Restore__9MenuSceneFv` |

## Constructed by

`__ct__8GameOverFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x003ac270 | 0x44 | `__ct__13GameOverSceneFv` | `GameOverScene::GameOverScene()` |
| 0x003ac2c0 | 0x74 | `__dt__13GameOverSceneFv` | `GameOverScene::~GameOverScene()` |
| 0x003ac340 | 0x278 | `GetReady__13GameOverSceneFv` | `GameOverScene::GetReady()` |
| 0x003ac5c0 | 0x5c | `Run__13GameOverSceneFv` | `GameOverScene::Run()` |
| 0x003ac620 | 0x20 | `ShiftTitle__13GameOverSceneFv` | `GameOverScene::ShiftTitle()` |
| 0x003ac640 | 0x174 | `ReadData__13GameOverSceneFv` | `GameOverScene::ReadData()` |
| 0x003ac7c0 | 0x168 | `Realize__13GameOverSceneFv` | `GameOverScene::Realize()` |
| 0x003ac930 | 0x3d0 | `ExitRealize__13GameOverSceneFv` | `GameOverScene::ExitRealize()` |
| 0x003acd00 | 0x260 | `SelectLoad__13GameOverSceneFv` | `GameOverScene::SelectLoad()` |
| 0x003acf60 | 0x188 | `ExitSelectLoad__13GameOverSceneFv` | `GameOverScene::ExitSelectLoad()` |
| 0x003ad2b0 | 0x10 | `Release__13GameOverSceneFv` | `GameOverScene::Release()` |

## Rust port

`gameover::GameOverScene`.

## Open questions

- none recorded

Decompilation: `decomp/F/GameOverScene.c`
