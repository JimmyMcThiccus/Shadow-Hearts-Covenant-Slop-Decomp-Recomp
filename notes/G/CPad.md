# CPad

Copy of a **main-executable** class statically linked into FIELD.BIN (duplicated code of another section's class); documented by the owning section. Listed here for address mapping only.

| JP addr | size | method |
|---|---|---|
| `0x004a3360` | 0x28 | `CPad::SetPriority(const CPad::Priority&)` |
| `0x004a5950` | 0x34 | `CPad::GetReal` |
| `0x004a61e0` | 0x34 | `CPad::GetAnalogStickL` |
| `0x004a6220` | 0x34 | `CPad::GetPress` |

Decompiled source: `decomp/G/_OverlayCopies_CPad.c`.
