# MenuModelManeger

Loader/cache for menu models (`Create(path)`, `OrderFile`, `ReadFile`, `Polling`, `Access`, `Reset`); files `MENU/DAT/*.MMD` (model), `*.MTD`, `*.MED` (effect/motion data).

## Virtual table (`__vt__MenuModelManeger`)

| slot | function |
|---|---|
| 0x08 | `__dt__16MenuModelManegerFv` |
| 0x0c | `Polling__16MenuModelManegerFv` |
| 0x10 | `Event__16MenuModelManegerFP9MenuModelPCcPCc` |

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00282590 | 0x38 | `ReadComplete__16MenuModelManegerFiP9BufMemoryiPcPv` | `MenuModelManeger::ReadComplete(int, BufMemory*, int, char*, void*)` |
| 0x002825d0 | 0x80 | `__ct__16MenuModelManegerFv` | `MenuModelManeger::MenuModelManeger()` |
| 0x00282650 | 0x7c | `__dt__16MenuModelManegerFv` | `MenuModelManeger::~MenuModelManeger()` |
| 0x002826d0 | 0x40 | `Create__16MenuModelManegerFPCc` | `MenuModelManeger::Create(const char*)` |
| 0x00282710 | 0x154 | `Destroy__16MenuModelManegerFUc` | `MenuModelManeger::Destroy(unsigned char)` |
| 0x00282870 | 0xfc | `Access__16MenuModelManegerFv` | `MenuModelManeger::Access()` |
| 0x00282970 | 0x138 | `Reset__16MenuModelManegerFv` | `MenuModelManeger::Reset()` |
| 0x00282ab0 | 0x170 | `OrderFile__16MenuModelManegerFv` | `MenuModelManeger::OrderFile()` |
| 0x00282c20 | 0x27c | `ReadFile__16MenuModelManegerFiP9BufMemory` | `MenuModelManeger::ReadFile(int, BufMemory*)` |
| 0x00282ea0 | 0x8a4 | `Polling__16MenuModelManegerFv` | `MenuModelManeger::Polling()` |
| 0x00283750 | 0x10 | `Event__16MenuModelManegerFP9MenuModelPCcPCc` | `MenuModelManeger::Event(MenuModel*, const char*, const char*)` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuModelManeger.c`
