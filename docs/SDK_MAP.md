# SDK / library map of the JP binary (section I)

Source: `symbols/SLPM_602.19.syms` (JP Furokuban main executable, 5,163 functions in `main`) and
`symbols/SLPM_602.19_module_map.txt`. Counts below are **functions in the main executable only**
(`FIELD.BIN`/`BATTLE.BIN` contain no SDK or libc code, only game code and `__sinit_*` stubs). The totals were
produced by classifying the address ranges of the module map and dropping C++-mangled game symbols
(`name__NclassF...`, `@NN@` thunks, `__sinit_*`) from the ranges; they are the *library* functions
(~925 of the 5,163 main functions, the OUTLINE's "~1,400" counted some neighbouring game helpers too).

Library versions, from the `__ps2_libinfo__` strings in `.rodata` ("PsIIlib…"): **libgraph 2700, libdma 2700,
libipu 2700, libscf 2700, libkernl 2710, libpad 2710, libcdvd 2710, libmc 2710** -> Sony PS2 SDK 2.7.x
(IOP image `IOPRP271.IMG`, i.e. IOP kernel 2.71). Compiler runtime is **Metrowerks CodeWarrior** (MW MIPS C 2.4.1.01),
not GCC: C++ EH is the MW `__throw`/`__frame_state_for` implementation; libc/libm are the **newlib + fdlibm** that ship with the SDK.

Everything here is *replaced*, not ported: the Rust code never calls a `sce*` function. The Rust column names the
replacement and, where it already exists, the module that models the same state.

## 1. Main executable (EE)

| Family | Address range | Funcs | What the game uses it for | Rust / Bevy replacement |
|---|---|---:|---|---|
| **crt0 / soft-double helpers** (`_dpflt`, `_dpfle`) | `002001e0-00200224` | 2 | compiler support (double compare/convert); `_root` entry at `002001d0` | none (Rust `f64`) |
| **libgraph** (`sceGsResetGraph`, `sceGsSetDefDispEnv/DrawEnv/DrawEnv2/Clear`, `sceGsPutDispEnv`, `sceGsSyncV`, `sceGsSyncPath`, `sceGsSyncVCallback`, `sceGsSetDefStoreImage`, `sceGsExecStoreImage`, `sceGsSetHalfOffset`, `sceGszbufaddr`, `_GetGsDxDyOffset`) | `00200228-00201b58` | 16 | GS reset and 512x448 display/draw environment (`Gsx`, `GsxCamera::Flip`), vblank callback `cbVSync`, frame read-back for screen capture / render-to-texture (`GsxFrameBuf::StoreImage`, `CScrCapture`) | `sh2_gfx::gs` (`GsInterpreter`) + `sh2_gfx::renderer::GfxBackend` implemented on Bevy render targets; vblank = Bevy `Update` tick, store-image = render-to-texture / `Screenshot`; half-offset jitter dropped (notes/B/pipeline.md §7) |
| **libdma** (`sceDmaGetChan/Reset/PutEnv/GetEnv/PutStallAddr/Send/SendN/SendI/Recv*/Sync/Watch/Pause/Restart`, `WaitDma`, `WatchDma`, `CheckAddress`, `memclr`) | `00201b58-0020239c` | 19 | kicking GIF/VIF1 DMA chains built by `World`/`CVif1Packet`/`P2Pkt`, SPR/IPU transfers, `WaitDma` after each flip | `sh2_gfx::dma` models the tag chain; at runtime a "send" becomes `GsInterpreter::run(chain)` -> draw calls; sync/watch become no-ops |
| **libvif** (`sceVif1PkTerminate`) | `002023a0-002023f8` | 1 | closes a VIF1 packet in `CVif1Packet`/`Texture` | `sh2_gfx::packet` |
| **libvu0** (`sceVu0ApplyMatrix`, `MulMatrix`, `InversMatrix`, `TransposeMatrix`, `RotMatrixX/Y/Z`, `RotMatrix`, `CameraMatrix`, `ViewScreenMatrix`, `NormalLightMatrix`, `LightColorMatrix`, `DropShadowMatrix`, `RotTransPers`, `ClipAll`, `Normalize`, `OuterProduct`, ... ) | `002023f8-002030dc` | 41 | back-end of `FVector`/`Matrix`/`Quaternion` (section C), camera/projection (`GsxCamera`), light matrices (`LightControl`), shadow projection (`ShadowControl`), VEC `mat*`/`vec*` system calls | **`glam`** behind `sh2_formats::math::{FVector, Matrix}` (column-major, `v' = M*v`, same layout as `Mat4`); `sceVu0RotMatrix` = `Rx*Ry*Rz` (Z applied first), `sceVu0RotMatrixX/Y/Z` = `Mat4::from_rotation_*` |
| **libvpu** (`sceVpu0Reset`) | `002030e0-0020313c` | 1 | VU0 reset at boot | none |
| **libipu + libmpeg** (IPU software/hardware MPEG-2 decoder: `_motionComp0`, `_ipuVdec`, `_decMB0`, `_sequenceHeader`, `_pictureHeader`..., `sceMpegInit/Create/Delete/AddBs/GetPicture*/Reset/AddCallback`, `sceIpuInit/Sync/StopDMA/RestartDMA`) | `00203140-0020a378` | 134 | movie tracks (`MovieServerHandler`/`MovServer`, `MOVS` chunk of an LSD, opening/ending FMVs) and `IPUTexture` (IPU used as a bit-stream / colour-space converter for textures) | no decoder in Rust: either (a) pre-convert the `.PSS/.MPG` streams to a modern container and play with a video decoder crate (`ffmpeg-next`, `bevy_video`, `openh264`-via-transcode), or (b) a pure-Rust MPEG-2 decoder crate; `MovieServerHandler` becomes a trait (`MovieBackend::{start,poll_frame,end}`). `IPUTexture` is replaced by decoding the `.TEX` payload on the CPU (`sh2_gfx::texture`) |
| **libkernl syscall stubs** (`CreateThread`, `StartThread`, `SleepThread`, `WakeupThread`, `CreateSema`/`SignalSema`/`WaitSema`, `AddIntcHandler`/`AddDmacHandler`, `EnableCache`/`FlushCache`/`SyncDCache`, `SetAlarm`, `GsGetIMR`, `SetVSyncFlag`, `RFU0xx`, `ExecPS2`/`LoadExecPS2`, `VSync`, ...) | `0020a380-0020ad64` | 141 | `CThread` (main thread + `CApp` thread, `SleepThread` forever), semaphores in `FileIOLib`/`Sdrv`/`SifCmd`, VSync wait in `CApp::Run`, `Reboot()` -> `LoadExecPS2` | `sh2_core::thread` (`CThread` state model), `sh2_core::app`/`poller`: a Bevy schedule (`Update` = pollers) replaces the threads; semaphores -> `std::sync`/channels; VSync = frame pacing (`bevy_winit`); `LoadExecPS2` (soft reboot) -> `AppExit`/state reset; cache ops -> no-ops |
| **newlib syscall glue** (`write`, `read`, `open`, `close`, `lseek`, `sbrk`, `isatty`, `fstat`, `stat`, `unlink`, `getpid`, `kill`, `_sceSDC`/`_sceIDC` = `SyncDCache`/`InvalidDCache`, `EnableIntc`/`DisableIntc`, `iWakeupThread`...) | `0020ad68-0020b800` | 33 | libc <-> kernel/`sceFs` bridge (stdout via DECI2 TTY, `sbrk` for `malloc`) | Rust `std`; stdout -> `log`/`println!` |
| **libdeci2 / TTY / kprintf** (`sceDeci2*`, `sceTty*`, `kputs`, `_printf`, `kprintf`, `scePrintf`, `printfloat`) | `0020b800-0020c8a0` | 25 | debug console (`dbwin`, `Dbg`) and `printf` of the "Effect Script: ..." diagnostics | `log` crate (`sh2_core::dbg`) |
| **libsif cmd + rpc** (`sceSifInitCmd`, `sceSifAddCmdHandler`, `sceSifSendCmd`, `sceSifInitRpc`, `sceSifBindRpc`, `sceSifCallRpc`, `sceSifCheckStatRpc`, `sceSifSetDma`, ...) | `0020c8a0-0020e018` | 39 | the only EE<->IOP transport: `FIO.IRX` file I/O (`FileIOLib`, sif-cmd id "FIOIRX"), `SDRV_IOP.IRX` sound (`SdrvEE`, id "sdrv_iop"), pad/mc RPC servers | removed: `FileIOLib` = `sh2_core::fileio::Disc` (host file read); `SdrvEE` = `SoundBackend` trait (see libsd below); SIF command ids and packet layouts are documented in notes/A/FileIOLib.md and notes/E/audio.md |
| **libfs / sceIo client** (`sceFsInit`, `sceOpen`, `sceRead`, `sceWrite`, `sceLseek`, `sceIoctl`, `sceDopen`, `sceDread`, `sceMount`, `sceMkdir`, ...) | `0020e018-002116f8` | 40 | host/`cdrom0:`/`mc0:`/`hdd0:` file I/O used by the libc glue, the memory-card and HDD save devices (`SaveDeviceMC`, `SaveDeviceHDD`) | `std::fs`; save slots through `sh2_menu::storage` (a `SaveDevice` trait implemented on a save directory) |
| **libsif loadfile + IOP heap** (`sceSifLoadModule`, `sceSifLoadStartModule`, `sceSifRebootIop`, `sceSifSyncIop`, `sceSifAllocIopHeap`, `sceSifLoadElf`) | `002116f8-00212c58` | 33 | `SSHMain` boot: `sceSifRebootIop("IOPRP271.IMG")` then loads SIO2MAN, MCMAN, MCSERV, PADMAN, IOPUTY, FIO, LIBSD, SDRV_IOP (`sh2_core::ssh_sys::IOP_MODULES_PASS1/2`) | none (IOP does not exist); the module list is kept only as documentation |
| **crt0 / TLB / ExecPS2 / alarm** (`SetTLBHandler`, `InitTLB32MB`, `_kTLBException`, `InitExecPS2`, `ExecPS2`, `InitAlarm`, `_send_to_iop`, `supplement_crt0`) | `00212c58-00213e1c` | 54 | boot-time TLB set-up for the 32 MB map, `FullAllocAndFree`/heap layout, system-call-table patching of the kernel (`PatchIsNeeded`) | none (virtual memory is the OS's); `BufMemory` (`sh2_core::bufmem`) models the game's own heap |
| **libpad** (`scePadInit/Init2`, `scePadPortOpen`, `scePadRead`, `scePadGetState`, `scePadSetMainMode`, `scePadSetActDirect`, `scePadSetActAlign`, `scePadInfoAct/Comb/Mode/PressMode`, `scePadEnterPressMode`) | `00213e20-00215188` | 29 | `CPadMan`'s controller state machine (detect DualShock2, enable analog + pressure-sensitive mode, vibration through actuators), `CVibe` | **`bevy_input` / `gilrs`** gamepad events feed `sh2_core::pad` (`CPad`: active-low button bytes, 0x80-centred sticks, 8-bit pressure); vibration -> gilrs force-feedback via `sh2_core::vibe` |
| **libcdvd** (`sceCdInit`, `sceCdRead`, `sceCdSync`, `sceCdSearchFile`, `sceCdLayerSearchFile`, `sceCdDiskReady`, `sceCdStatus`, `sceCdMmode`, `sceCdPowerOff`, `sceCdCallback`) | `00215188-00216b90` | 27 | `FileIOLib::InitPkb` (locates `\PKFINFO.TBL;1` and every `*.PKB` LBA, sector-aligned PKB reads), disc-swap check, `DvdromOrder` | `sh2_core::fileio::Disc` over the unpacked disc folder (`SH2_DISC_DIR`); LBA bookkeeping is kept as `FileLoc` metadata, not used for reads |
| **libmc** (`sceMcInit`, `sceMcOpen`, `sceMcRead`, `sceMcWrite`, `sceMcSync`, `sceMcGetDir`, `sceMcGetInfo`, `sceMcFormat`, `sceMcDelete`, ...) | `00216b90-00218380` | 28 | `SaveDeviceMC` state machine (memory-card slots, icon + save file, `CSaveData`) | `sh2_menu::storage` / `sh2_menu::save` serialisation to files under the user's data dir (`dirs`/Bevy `UserData`); the card ops machine is kept as async-ish `Sync()` states |
| **newlib libm + fdlibm** (`__ieee754_*f`, `__kernel_*`, `sin/cos/floor/scalbn`, `sinf/cosf/tanf/acosf/asinf/atanf/atan2f/powf`) | `00218380-0021cb7c` | 34 | float trig everywhere (cameras, particles, rings, `calSin`/`calCos` VEC calls) | Rust `f32::sin_cos` etc. **Not bit-identical** to fdlibm (differences ~1 ulp); if replay-exact results are ever needed, port fdlibm `sinf/cosf` (`libm` crate is fdlibm-derived) |
| **libgcc int64 / soft-fp** (`__muldi3`, `__divdi3`, `__moddi3`, `__udivdi3`, `__umoddi3`, `__floatdidf`, `__fixdfdi`, ...) | `0021cb80-0021e768` | 9 | 64-bit integer arithmetic on the 32-bit-ABI code (timers, sizes) | Rust `u64/i64` |
| **Metrowerks EH runtime + soft-double** (`__throw`, `__rethrow`, `__sjthrow`, `__register_frame_info`, `__frame_state_for`, `find_fde`, `execute_cfa_insn`, `eh_context*`, `__eh_alloc`, `dpadd/dpsub/dpmul/dpdiv/dpcmp`, `__pack_d/__unpack_d`) | `0021e768-00221e18` | 67 | C++ exceptions (gcc-2.95-style DWARF CFI unwinding, `__terminate`, `__unexpected`) and software double-precision (the EE FPU has no f64) | none: the game does not rely on exceptions for control flow; Rust `Result`/`panic`; `f64` is native |
| **newlib libc** (`malloc`/`free`/`_malloc_r`, `memcpy/memset/memmove/memcmp/memchr`, `str*`, `strtod/strtol/atoi`, `printf/sprintf/sscanf/vfprintf`, `fread`, `fflush`, `ungetc`, `rand/srand`, `setlocale`, `signal/raise`, `abort`) | `00231b20-0023bba8` | 114 | `sprintf` for resource names (`MENU/IMG/GO/GO_%03d.TEX`), `rand()` for all gameplay randomness (`sh2_gfx::effects::compat::Rand`, battle `Rng`), `malloc` under `new`, `strtod` in the scripts | Rust `std` (`format!`, `str::parse`); **`rand()` must be the newlib LCG** (`srand`/`rand` at `00236208/00236220`) when reproducing recorded battles: implemented as the `Rng` traits in `sh2_gfx::effects::jring` / `sh2_battle::rules` |
| **libscf + RTC time helpers** (`sceScfGetLanguage`, `sceScfGetAspect`, `sceScfGetSpdif`, `sceScfGetTimeZone`, `sceScfGetLocalTimefromRTC`, `GetRomName`, `IsT10K`, `tobcd`/`frombcd`, `adddate`) | `0023ca60-0023d150` | 21 | `GetLanguage`, the aspect/SPDIF/time-zone settings of the console (`SSHSys::Language`), play-time clock on the save screen | `sh2_core::boot::get_language` (locale / config); aspect fixed to 4:3 with letter-box; time via `std::time` / `chrono` |
| **Metrowerks C++ runtime** (`__initialize_cpp_rts`, `__register_global_object`, `__destroy_global_chain`, `__construct_array`, `__destroy_arr`, `__construct_new_array`, `__destroy_new_array`, `__ptmf_scall`, `__ptmf_test`, `__throw_catch_compare`, `__end__catch`, `__unexpected`, `std::bad_exception`, `mwInit`, `mwExit`, `mwOverlayInit`) | `00383d40-00384d14` | 18 | static constructors (`__sinit_*.cpp`: BGMServer ... app, dbwin), array new/delete, pointer-to-member-function calls, overlay init (zero bss + run overlay ctors in `Overlay::Load`) | `sh2_core::overlay` models `mwOverlayInit`; static ctors -> `Default`/`Plugin::build`; PTMF -> trait objects / fn pointers |

Subtotal of the above: **~925 functions, ~180 KB of code**. The remaining main-executable functions are game code (see
`symbols/classes_by_section.txt`).

### Data-side SDK/runtime objects (not functions)
`__ps2_libinfo__` (one per library, the version strings above), `__clz_tab`, `__malloc_av_`/`__malloc_lock_owner`
(newlib allocator state), `_sceCd_c_cb_sem` and other `_sce*` semaphores/state, `__vt__Q23std13bad_exception` and the
MW RTS exception tables; none need a port.

## 2. IOP modules (from `MODULES/`, loaded by `SSHMain` via `sceSifLoadModule`)

The IOP side is *not* in `SLPM_602.19`; the EE reaches it only through libsif (above). There is **no `libsd`/`sceSd*`
function in the EE binary**: sound is driven by the game's own IOP module, so "libsdr" is an IOP-side family.

| Module | Role | Used by | Rust / Bevy replacement |
|---|---|---|---|
| `IOPRP271.IMG` | IOP kernel image (2.71) loaded by `sceSifRebootIop` | boot | none |
| `SIO2MAN.IRX`, `PADMAN.IRX` | pad/multitap server for libpad | `CPadMan` | `bevy_input`/`gilrs` |
| `MCMAN.IRX`, `MCSERV.IRX` | memory-card server for libmc | `SaveDeviceMC` | file-backed saves |
| `IOPUTY.IRX` | IOP utility (printf over the SIF) | `Dbg` | `log` |
| `FIO.IRX` ("FIOIRX", 42 KB, game-specific) | EE-driven file I/O + CD reads for `*.PKB` (sif-cmd id "FIOIRX") | `FileIOLib`/`DvdromOrder` | `sh2_core::fileio::Disc` |
| `LIBSD.IRX` (Sony **libsd**, SPU2 driver) | SPU2 voice/reverb/DMA primitives | `SDRV_IOP.IRX` only | a `SoundBackend` mixer (below) |
| `SDRV_IOP.IRX` ("SDRV Sound Driver System (C)Nautilus", 89 KB, symbols intact) | the game's sound engine: SE sequencer (`sem*`), BGM sequencer (`sqm*`), voice/stream manager (`vsd*`, `vcm*`, `lfom*`), `.SDH`/wave banks, EE streaming | `Sdrv`/`SdrvEE`, `HNMSnd`, `CSe`, `CMusic`, `StreamBGM`, `primSound/primMusic` | **`SoundBackend` trait** (`sh2_script::audio`) implemented on **rodio** or **kira**: SPU2 ADPCM decode (VAG) -> PCM, sequencer + reverb + LFO re-implemented in Rust (protocol in notes/E/audio.md) |
| `SDRDRV.IRX` | Sony SDR sound driver, on the disc but not in `SSHMain`'s module lists | - | - |
| `DEV9.IRX`, `ATAD.IRX`, `HDD.IRX`, `PTS.IRX` | PS2 HDD stack | `SaveDeviceHDD` (optional HDD save) | not needed |
| `SMAP.IRX`, `INET.IRX`, `INETCTL.IRX`, `NETCNF.IRX`, `ETHNET.IRX`, `USBD.IRX`, `USBKB.IRX` | network/USB stacks on the disc | not referenced by `SSHMain`'s module lists | not needed |

## 3. Replacement summary

| PS2 facility | Replacement crate / module |
|---|---|
| sceVu0*, `FVector`/`Matrix`/`Quaternion` | `glam` via `sh2_formats::math` |
| sceGs*/sceDma*/VIF1/GIF packets | `sh2_gfx::{gs,dma,packet,world}` interpreted into Bevy meshes/materials; `renderer::GfxBackend` |
| scePad* | `bevy_input` + `gilrs` -> `sh2_core::pad` |
| sceCd* + FIO.IRX + libfs | `sh2_core::fileio` (`SH2_DISC_DIR`) |
| sceMc* / HDD | `sh2_menu::storage` file-backed save device |
| libsd + SDRV_IOP | `SoundBackend` on `rodio` -- done: `sh2_audio` (software SPU2 + sequencer, notes/integration/audio.md) |
| libipu / libmpeg | video decoder crate or pre-converted assets (`MovieBackend` trait) |
| libkernl threads/semaphores/alarms | Bevy schedule + `std::sync` |
| libscf | `sh2_core::boot::get_language`, locale/config |
| newlib libc/libm | Rust `std` (+ `libm` crate when bit-exact fdlibm is needed); keep the newlib `rand()` LCG |
| MW C++ RTS / EH | `Default`/`Plugin::build`, `Result` |
| crt0 / TLB | none |
