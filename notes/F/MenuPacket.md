# MenuPacket

Double-buffered GS packet memory (quadwords): `CreatePacket(n)` allocates 2n qwords, `SetPacket(n, a, b)` borrows memory, `ConnectPacket(prev)` writes the DMA tag chaining this packet after `prev` and returns the new tail. Not needed in the port (replaced by immediate draw commands).

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x0 | `void **` | vptr |
| 0x4 | `void *` | pkt0 |
| 0x8 | `void *` | pkt1 |
| 0xc | `u16` | qwc |
| 0xe | `u8` | pflags |

## Virtual table (`__vt__MenuPacket`)

| slot | function |
|---|---|
| 0x08 | `__dt__10MenuPacketFv` |

## Constructed by

`__ct__10MenuWindowFv`, `__ct__10SoulEnergyFv`, `__ct__11SendOnLocalFv`, `__ct__12MenuRegisterFv`, `__ct__7ScissorFv`, `__ct__8FontDrawFv`, `__ct__8MenuItemFv`, `__ct__9MenuFrameFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00265630 | 0x3c | `__ct__10MenuPacketFv` | `MenuPacket::MenuPacket()` |
| 0x00265670 | 0x6c | `__dt__10MenuPacketFv` | `MenuPacket::~MenuPacket()` |
| 0x002656e0 | 0x7c | `ConnectPacket__10MenuPacketFP4_QWD` | `MenuPacket::ConnectPacket(_QWD*)` |
| 0x00265760 | 0x100 | `CreatePacket__10MenuPacketFUs` | `MenuPacket::CreatePacket(unsigned short)` |
| 0x00265860 | 0x110 | `CreateSinglePacket__10MenuPacketFUs` | `MenuPacket::CreateSinglePacket(unsigned short)` |
| 0x00265970 | 0x84 | `SetPacket__10MenuPacketFUsP4_QWDP4_QWD` | `MenuPacket::SetPacket(unsigned short, _QWD*, _QWD*)` |
| 0x00265a00 | 0x74 | `DestroyPacket__10MenuPacketFv` | `MenuPacket::DestroyPacket()` |
| 0x00265a80 | 0x34 | `ClearPacket__10MenuPacketFv` | `MenuPacket::ClearPacket()` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuPacket.c`
