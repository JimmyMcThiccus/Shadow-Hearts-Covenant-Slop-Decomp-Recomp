# DelayDeleteObject

Copy of a **main-executable** class statically linked into FIELD.BIN (duplicated code of another section's class); documented by the owning section. Listed here for address mapping only.

* base: `CList`; allocation size: unknown; ctor JP `0x004c07d0`
* vtable stores: `+8 __vt__17DelayDeleteObject`

| JP addr | size | method |
|---|---|---|
| `0x004a02d0` | 0x64 | `DelayDeleteObject::~DelayDeleteObject()` |
| `0x004c07d0` | 0x3c | `DelayDeleteObject::DelayDeleteObject()` |

Decompiled source: `decomp/G/_OverlayCopies_DelayDeleteObject.c`.
