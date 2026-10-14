# MenuDataTable

Loader for a standalone table file (`.MDT`, e.g. `MENU/DAT/SAVELIST.MDT` used by `SaveMenuSection`'s place-name table): `Order(path)` -> `ReadDataFunc` -> `Create(data, buf)` which relocates with mode 1 (pointers relative to their chunk). `Find(type)` walks the chunk list. `Convert(data, mode)` is the relocation pass shared with scenes.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x0 | `u8 *` | data |
| 0x4 | `BufMemory *` | heap |
| 0x8 | `u8` | loading |
| 0x9 | `u8` | release_pending |

## Constructed by

`__ct__15SaveMenuSectionFv`, `__ct__4MenuFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00283760 | 0x11c | `Convert__13MenuDataTableFPUci` | `MenuDataTable::Convert(unsigned char*, int)` |
| 0x00283880 | 0x38 | `__ct__13MenuDataTableFv` | `MenuDataTable::MenuDataTable()` |
| 0x002838c0 | 0x5c | `__dt__13MenuDataTableFv` | `MenuDataTable::~MenuDataTable()` |
| 0x00283920 | 0x78 | `Order__13MenuDataTableFPCc` | `MenuDataTable::Order(const char*)` |
| 0x002839a0 | 0x44 | `ReadDataFunc__13MenuDataTableFiP9BufMemoryiPcPv` | `MenuDataTable::ReadDataFunc(int, BufMemory*, int, char*, void*)` |
| 0x002839f0 | 0x80 | `Find__13MenuDataTableFs` | `MenuDataTable::Find(short)` |
| 0x00283a70 | 0x80 | `Create__13MenuDataTableFPUcP9BufMemory` | `MenuDataTable::Create(unsigned char*, BufMemory*)` |
| 0x00283af0 | 0x78 | `Release__13MenuDataTableFv` | `MenuDataTable::Release()` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuDataTable.c`
