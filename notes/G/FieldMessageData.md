# FieldMessageData

* base: `-`; allocation size: 0x380; ctor JP `0x004a0bb0`
* embedded sub-objects: `+0x10 MenuWindow`, `+0xc4 FontDraw`, `+0x104 MenuMessage`, `+0x19c KeyWait`, `+0x278 Cursor`
* vtable stores: `+8 __vt__17DelayDeleteObject`, `+8 __vt__16FieldMessageData`

| JP addr | size | method |
|---|---|---|
| `0x004a0bb0` | 0xa0 | `FieldMessageData::FieldMessageData()` |
| `0x004a0c50` | 0x130 | `FieldMessageData::~FieldMessageData()` |

Decompiled source: `decomp/G/FieldMessageData.c`.
