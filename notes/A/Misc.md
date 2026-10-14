# Misc section A: boot glue, Dbg, BRN_LinkList, US deltas

Boot chain, `main`, `SSHMain`, `SSHSys::Initialize` order: see port `boot.rs` header.
* `_start` 0x200008 -> InitTLB 0x212f30 -> supplement_crt0 0x213540 (2 semaphores) -> main. US: main 0x21f6c0, CApp ctor 0x21f780, InitMain 0x21f9f0.
* IOP: reboot with "IOPRP271.IMG" (region dir JPN/USA/GBR), modules SIO2MAN MCMAN MCSERV PADMAN, then IOPUTY FIO LIBSD SDRV_IOP (list word semantics in `ssh_sys.rs`).
* `mwInit` = `__initialize_cpp_rts(0x404920,0x404998,0x40a830,0x40a830)`; `mwExit` runs `__global_destructor_chain`. US: mwOverlayInit 0x3c58b0, mwExit 0x3c5930, mwInit 0x3c5940.
* Dbg (`dbwin.cpp`): text console `DBSTREAM`; ported to `dbg.rs`.
* BRN_LinkList (`BRN_calc_linklist.cpp`): 5-link verlet chain; layout in `brn.rs`. In SLUS the whole class had already been named by another section; only `calcNextLinkList` (0x246730) was missing and is now named.
* ClutAdressControl: GsxRaster subclass, ctor calls vtbl+0x10(1, 0x3eef, 0, 0x40, 0x100); `getAdress(i) = (m_base & 0x3fff) + i*4`.

## US (retail) deltas found in section A
* Data files use `.NA` extension; FileIOLib struct is 0x20 smaller and has HDD power-off handling in `ResetSystem`; no `checkPFSFreeSize`.
* `SSHSys` gains request 0x40 (new scene, funcs 0x3ee600/0x3ee620/0x3ee670/0x3eda50 + fade helper using 500 ms), CApp::Run grows to 0x680.
* New OPENING.BIN overlay; CDMYStage::preLoad loads it, `opening(u8)` added; GameOver object is 100 bytes with extra sub-objects.
* GetRegDat has more kinds.
* The shared Ghidra program SLUS_210.41 had `0x239a70` mis-named `__ct__11LevelsModelFv` (fuzzy false positive); it is `cbOverlayLoad` (renamed).
