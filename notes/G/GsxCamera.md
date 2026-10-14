# GsxCamera

Copy of a **main-executable** class statically linked into FIELD.BIN (duplicated code of another section's class); documented by the owning section. Listed here for address mapping only.

| JP addr | size | method |
|---|---|---|
| `0x004a80c0` | 0x1c | `GsxCamera::GetFrame()` |
| `0x004a80e0` | 0xc | `GsxCamera::GetActiveCamera()` |
| `0x004c6a40` | 0x1c | `GsxCamera::GetMatrix()` |
| `0x004dbfd0` | 0x70 | `GsxCamera::SetFogColor(const _rgba32&)` |
| `0x004dc040` | 0x94 | `GsxCamera::SetFogParam(float, float)` |
| `0x004dc0e0` | 0x34 | `GsxCamera::SetBgColor(const _rgba32&)` |

Decompiled source: `decomp/G/_OverlayCopies_GsxCamera.c`.
