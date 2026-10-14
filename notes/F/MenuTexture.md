# MenuTexture

Base class: `BufMemory-backed texture`

Texture upload wrapper (`Create(buf, psm, w?, h?)`, `OrderFile`) used by the common scene and GameOver; owns a `RasterPacket`.

## Virtual table (`__vt__MenuTexture`)

| slot | function |
|---|---|
| 0x08 | `__dt__11MenuTextureFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |

## Constructed by

`GetReady__13GameOverSceneFv`, `__ct__10FileHandleFv`, `__ct__10MenuCommonFv`, `__ct__13CmdSoulEnergyFv`, `__ct__6prim2DFi`, `__ct__Q29primLayer5LayerFv`, `__sinit_CMenuFont.cpp`, `__sinit_CMenuFontItalic.cpp`, `setWinTex__7primTexFP10MenuWindowii`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x002676b0 | 0xe4 | `__ct__11MenuTextureFv` | `MenuTexture::MenuTexture()` |
| 0x002677a0 | 0xa4 | `__dt__11MenuTextureFv` | `MenuTexture::~MenuTexture()` |
| 0x00267850 | 0xf4 | `ReadBuffer__11MenuTextureFP9BufMemoryi` | `MenuTexture::ReadBuffer(BufMemory*, int)` |
| 0x00267950 | 0xc4 | `Create__11MenuTextureFP9BufMemory6GS_PSMUiiUc` | `MenuTexture::Create(BufMemory*, GS_PSM, unsigned int, int, unsigned char)` |
| 0x00267a20 | 0x1ec | `Create__11MenuTextureFPUc6GS_PSMUii` | `MenuTexture::Create(unsigned char*, GS_PSM, unsigned int, int)` |
| 0x00267c10 | 0x64 | `Release__11MenuTextureFv` | `MenuTexture::Release()` |
| 0x00267c80 | 0xb4 | `ReleaseBuffer__11MenuTextureFv` | `MenuTexture::ReleaseBuffer()` |
| 0x00267d40 | 0xc0 | `OrderFile__11MenuTextureFPCc6GS_PSMUii` | `MenuTexture::OrderFile(const char*, GS_PSM, unsigned int, int)` |
| 0x00267e00 | 0x38 | `ReadFileFunc__11MenuTextureFiP9BufMemoryiPcPv` | `MenuTexture::ReadFileFunc(int, BufMemory*, int, char*, void*)` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuTexture.c`
