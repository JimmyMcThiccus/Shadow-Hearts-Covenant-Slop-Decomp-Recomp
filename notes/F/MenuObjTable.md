# MenuObjTable

Priority-sorted singly linked list of `MenuObj`s (head @+4). Used as the render layer's window list and as every window's child-draw table. `AddPriority` inserts before the first element with a strictly larger priority (stable for equal priorities), sets flags `in-table`, marks both dirty masks 0x3f. `Trace*` helpers walk the list: `TracePolling` (objects with the poll flag), `TraceUpdate(x,y,alpha[,dirty])` (render flag + dirty for the current buffer), `TraceConnect(packet)` chains the GS packets, `TraceSetRendering`, `TraceAddUpdate`.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x0 | `void **` | vptr |
| 0x4 | `MenuObj *` | head |

## Virtual table (`__vt__MenuObjTable`)

| slot | function |
|---|---|
| 0x08 | `__dt__12MenuObjTableFv` |

## Constructed by

`__ct__10MenuRenderFv`, `__ct__10MenuWindowFv`, `__ct__8MenuIconFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00275140 | 0x30 | `__ct__12MenuObjTableFv` | `MenuObjTable::MenuObjTable()` |
| 0x00275170 | 0x64 | `__dt__12MenuObjTableFv` | `MenuObjTable::~MenuObjTable()` |
| 0x002751e0 | 0x160 | `AddPriority__12MenuObjTableFP7MenuObj` | `MenuObjTable::AddPriority(MenuObj*)` |
| 0x00275340 | 0xf4 | `RemoveObj__12MenuObjTableFP7MenuObj` | `MenuObjTable::RemoveObj(MenuObj*)` |
| 0x00275440 | 0x7c | `FindObj__12MenuObjTableFs` | `MenuObjTable::FindObj(short)` |
| 0x002754c0 | 0x80 | `ClearTable__12MenuObjTableFv` | `MenuObjTable::ClearTable()` |
| 0x00275540 | 0x6c | `TraceSetRendering__12MenuObjTableFUc` | `MenuObjTable::TraceSetRendering(unsigned char)` |
| 0x002755b0 | 0x78 | `TracePolling__12MenuObjTableFv` | `MenuObjTable::TracePolling()` |
| 0x00275630 | 0xb4 | `TraceUpdate__12MenuObjTableFiiUs` | `MenuObjTable::TraceUpdate(int, int, unsigned short)` |
| 0x002756f0 | 0xd4 | `TraceUpdate__12MenuObjTableFiiUsUc` | `MenuObjTable::TraceUpdate(int, int, unsigned short, unsigned char)` |
| 0x002757d0 | 0x6c | `TraceAddUpdate__12MenuObjTableFUc` | `MenuObjTable::TraceAddUpdate(unsigned char)` |
| 0x00275840 | 0x84 | `TraceConnect__12MenuObjTableFP4_QWD` | `MenuObjTable::TraceConnect(_QWD*)` |

## Rust port

`Window::draw` sorts `objs + attached places` by priority; `MenuRoot::draw` sorts windows.

## Open questions

- none recorded

Decompilation: `decomp/F/MenuObjTable.c`
