# CNaviMap

* base: `DelayDeleteObject`; allocation size: 0x120; ctor JP `0x004cf1a0`
* embedded sub-objects: `+0x10 _NaviWork`, `+0xd0 Matrix`, `+0x110 CImage`
* vtable stores: `+8 __vt__8CNaviMap`

| JP addr | size | method |
|---|---|---|
| `0x004b0660` | 0x44 | `CNaviMap::AttachFrame(int, Frame*)` |
| `0x004cf1a0` | 0x140 | `CNaviMap::CNaviMap()` |
| `0x004cf340` | 0xbc | `CNaviMap::Release()` |
| `0x004cf400` | 0x40 | `CNaviMap::Delete()` |
| `0x004cf440` | 0x2e4 | `CNaviMap::SetData(_NaviMapDataHdr*)` |
| `0x004cf730` | 0xf0 | `CNaviMap::DspMesh(int, int)` |
| `0x004cf820` | 0x4c | `CNaviMap::isDsp()` |
| `0x004cf870` | 0xbc | `CNaviMap::DspClr(int)` |
| `0x004cf930` | 0x48 | `CNaviMap::Dsp(int)` |
| `0x004cf980` | 0xcc | `CNaviMap::Clr(int)` |
| `0x004cfa50` | 0x984 | `CNaviMap::Update(float, FVector*, float)` |
| `0x004d0530` | 0x28 | `CNaviMap::MakePacketS(void*)` |
| `0x004d06b0` | 0x360 | `CNaviMap::GetPolyColor(FVector*)` |
| `0x004d0a10` | 0xb44 | `CNaviMap::MakePacket()` |
| `0x004d1670` | 0x8b4 | `CNaviMap::MakeMapPacket()` |
| `0x004d1f30` | 0xa80 | `CNaviMap::MakeMaskPacket()` |
| `0x004d29b0` | 0x2fc | `CNaviMap::Set4Sprite(_QWD&*, int, int, int, int, int, int, int)` |
| `0x004d2cb0` | 0x594 | `CNaviMap::SetCursor()` |
| `0x004d3250` | 0x164 | `CNaviMap::GetNavVector(FVector*, _NavVertex*)` |
| `0x004d33c0` | 0x2e8 | `CNaviMap::CnvVertex(_QWD*, FVector*, Matrix*)` |
| `0x004d36f0` | 0xa3c | `CNaviMap::MakeItemPacket()` |
| `0x004d41c0` | 0xa0 | `CNaviMap::GetCenterPos(FVector&)` |
| `0x004d4260` | 0x330 | `CNaviMap::GetRectVertex(_DWD*, FVector*, int, float, float)` |
| `0x004d4590` | 0x2c8 | `CNaviMap::GetArrowVertex(_DWD*, FVector*, int)` |
| `0x004d4860` | 0x3e0 | `CNaviMap::GetSprVertex(_DWD*, FVector*, int, float, int, int)` |
| `0x004d4c40` | 0x3f0 | `CNaviMap::GetFT4Vertex(_DWD*, FVector*, int, float, int, int)` |
| `0x004d5030` | 0x184 | `CNaviMap::AddItem(int, FVector&, int, int, bool, unsigned int)` |
| `0x004d51c0` | 0x1c4 | `CNaviMap::SetItem(int, int, FVector&, int, int, bool, unsigned int)` |
| `0x004d5390` | 0xbc | `CNaviMap::RemoveItem(int)` |
| `0x004d5450` | 0x90 | `CNaviMap::DspItem(int, bool)` |
| `0x004d54e0` | 0x74 | `CNaviMap::GetItem(int)` |
| `0x004d5560` | 0x94 | `CNaviMap::~CNaviMap()` |

Decompiled source: `decomp/G/CNaviMap.c`.
