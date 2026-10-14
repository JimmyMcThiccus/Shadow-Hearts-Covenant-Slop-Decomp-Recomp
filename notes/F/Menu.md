# Menu

Base class: `CPolObj (+DelayDeleteObject @0x20)`

Scene manager polled by `CPoller` (priority 0x80). Holds the scene list (+0x38, linked through the scene's `next`), the active scene (+0x34) and the key word (+0x48 = `(trigger & 0xff0f) | (repeat & 0xf0)`). `Run()` calls the active scene's virtual `Run` (+0x1c) and, if the scene is 'created' (+0x23 bit4), `GetReady`. `Active(id)`, `Ready()`, `Shutdown()/Restore()` put all other scenes to sleep. `DestroyList()` deletes every scene.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x20 | `void **` | vptr_dd |
| 0x28 | `MenuDataTable` | table |
| 0x34 | `MenuScene *` | active |
| 0x38 | `MenuScene *` | scenes |
| 0x3c | `u8` | m3c |
| 0x3e | `u16` | m3e |
| 0x48 | `u16` | keys |

## Virtual table (`__vt__Menu`)

| slot | function |
|---|---|
| 0x08 | `__dt__4MenuFv` |
| 0x0c | `Polling__4MenuFv` |
| 0x18 | `@24@__dt__4MenuFv` |
| 0x1c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x20 | `Create__4MenuFP9BufMemory` |
| 0x24 | `Active__4MenuFs` |
| 0x28 | `Ready__4MenuFsss` |
| 0x2c | `GetKey__4MenuFv` |

## Constructed by

`__ct__8GameOverFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00264de0 | 0x100 | `__ct__4MenuFv` | `Menu::Menu()` |
| 0x00264ee0 | 0xbc | `__dt__4MenuFv` | `Menu::~Menu()` |
| 0x00264fa0 | 0x7c | `Run__4MenuFv` | `Menu::Run()` |
| 0x00265020 | 0x78 | `Shutdown__4MenuFv` | `Menu::Shutdown()` |
| 0x002650a0 | 0x78 | `Restore__4MenuFv` | `Menu::Restore()` |
| 0x00265120 | 0x98 | `DestroyList__4MenuFv` | `Menu::DestroyList()` |
| 0x002651c0 | 0x88 | `AddScene__4MenuFP9MenuScene` | `Menu::AddScene(MenuScene*)` |
| 0x00265250 | 0x10c | `RemoveScene__4MenuFP9MenuScene` | `Menu::RemoveScene(MenuScene*)` |
| 0x00265360 | 0x90 | `GetScene__4MenuFs` | `Menu::GetScene(short)` |
| 0x002653f0 | 0x8c | `DestroyScene__4MenuFP9MenuSceneb` | `Menu::DestroyScene(MenuScene*, bool)` |
| 0x00265480 | 0x14 | `Create__4MenuFP9BufMemory` | `Menu::Create(BufMemory*)` |
| 0x002654a0 | 0x14 | `Polling__4MenuFv` | `Menu::Polling()` |
| 0x002654c0 | 0x50 | `Active__4MenuFs` | `Menu::Active(short)` |
| 0x00265510 | 0x14 | `Ready__4MenuFsss` | `Menu::Ready(short, short, short)` |
| 0x00265530 | 0xf0 | `GetKey__4MenuFv` | `Menu::GetKey()` |
| 0x00265620 | 0x8 | `@24@__dt__4MenuFv` | `@24@__dt__4MenuFv` |

## Rust port

`scene::Menu`.

## Open questions

- none recorded

Decompilation: `decomp/F/Menu.c`
