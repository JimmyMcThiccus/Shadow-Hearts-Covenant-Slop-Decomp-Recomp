# Coverage after pass N5 (end of section I naming work)

Programs: `SLUS_210.41` (main), `SH2US_FIELD.BIN`, `SH2US_BATTLE.BIN`, `SH2US_OPENING.BIN`.  "Named" = the Ghidra function has a non-`FUN_` name.  Names applied: notes/I/us_map_N5.txt (2058 rows).

## Per program
| program | functions at start of N5 | unnamed at start | functions now | named now | unnamed now | named by N5 |
|---|---|---|---|---|---|---|
| SLUS_210.41 | 5,038 | 1,033 | 5,167 (+129 this-adjust/vtable thunks created) | 4,904 | **263** | 770 (+129 new functions) |
| SH2US_FIELD.BIN | 2,203 | 1,166 | 2,353 (+150 thunks created) | 2,017 | **336** | 830 (+150 new) |
| SH2US_BATTLE.BIN | 721 | 168 | 826 (+105 thunks created) | 758 | **68** | 100 (+105 new) |
| SH2US_OPENING.BIN | 104 | 0 | 104 | 104 | 0 | -- (already complete) |
| **total** | 8,066 | 2,367 | 8,450 | 7,783 | **667** | 1,700 named (+384 created+named thunks) |

The task brief expected "~100 small helpers" unnamed in FIELD; the real number at the start was 1,166 (the Cmd menu classes had only been matched where 3-gram similarity was high).  The 384 new functions are the 8-byte `@N@` this-adjust thunks of the multiple-inheritance vtables (JP has them as symbols, Ghidra had not made them functions in the US images): 129 in the main image, 150 in FIELD, 105 in BATTLE (e.g. `@24@__dt__<Class>`, `@36@__dt__`, `@20@getPacket`, `@20@DelayDelete`); each was created only where the matched JP vtable slot holds a thunk of the same class and the US bytes are `j target; addiu a0,a0,-N`.

## How the names were obtained (rows of us_map_N5.txt by tier)
* `C1`: 414
* `THUNK`: 367
* `FPSPEC`: 215
* `S1`: 159
* `CLSBLOCK`: 158
* `VT`: 98
* `C3`: 68
* `S2`: 63
* `C2`: 61
* `G`: 52
* `VTO`: 46
* `SDRV`: 44
* `MENU`: 44
* `S3`: 43
* `S4`: 35
* `FP2`: 19
* `SHOP`: 16
* `L1`: 14
* `BTL`: 14
* `BTLFX`: 14
* `DA`: 13
* `MOVIE`: 12
* `FLAG`: 11
* `PRIM`: 9
* `L2`: 8
* `SDK`: 8
* `MS`: 7
* `FP3`: 6
* `S5`: 5
* `CSE`: 4
* `BGEFF`: 4
* `GAMESEC`: 4
* `FM`: 3
* `SMS`: 3
* `STATS`: 3
* `BtlFader`: 1
* `CMUS`: 1
* `kputs`: 1
* `CreateAmbient`: 1
* `ResetLink__15DynamicsControlFv`: 1
* `Retail_ClutHolderDt`: 1
* `__ct__19FpObjectRetailLenz6FiPv`: 1
* `StopDmaCallBack`: 1
* `GetRealPAtk`: 1
* `0028f310`: 1
* `DelayDelete__9MenuSceneFv`: 1
* `__sinit_LSDRetailFilter.cpp`: 1
* `UpdateCount`: 1
* `SetBtlMotion`: 1

Hold-out precision (tools/I_N5/README.md): the gap DP pairs for hidden anchors were correct in 613/613 (main), 405/408 (FIELD, 50 % of anchors hidden), the sandwich rule 85/89, the lowered DP floor (0.3 + callee rule) 430/433, the relaxed equal-count rule 183/183 (main) and 0 errors in 167 FIELD gaps; vtable-derived names have no hold-out (they are exact slot identity).  A callee-name audit of every previously named function (tools/I_N5/audit_names.py) found and fixed 14 earlier wrong names (end of us_map_N5.txt): twin-function shifts (BtlSaveSec GetReal*, LightControl Create*, CmdRingCustom Update*, BtlModel SetBtlMotion, Enable/DisableAlpha) and three swapped `__sinit_*` stubs.

## SLUS_210.41 by class group
| group | functions | named | unnamed now | unnamed at start |
|---|---|---|---|---|
| SDK / libc / libkernl / crt0 (0x200000-0x240000) | 1060 | 1031 | 29 | 73 |
| Model / Atomic / Frame / Dynamics / CBBox / ClutRaster (0x240000-0x262000) | 374 | 362 | 12 | 36 |
| Menu toolkit: Menu*/Font*/Cursor/Window* (0x262000-0x290000) | 666 | 624 | 42 | 103 |
| Menu retail-new scenes + MenuEffectModel/MenuModelPrim (0x290000-0x294000) | 64 | 64 | 0 | 46 |
| CScript / CScriptEx (0x294000-0x298b60) | 42 | 41 | 1 | 2 |
| Fp*/Puti* JP-named classes (0x298b60-0x2c84e0) | 315 | 292 | 23 | 71 |
| Fp*/Puti* retail-new classes (0x2c84e0-0x2f3550) | 234 | 234 | 0 | 215 |
| JRing family (0x2f3550-0x331df0) | 132 | 131 | 1 | 3 |
| Effect / EffectCore / VEC handlers / BgEffect (0x331df0-0x35f000) | 711 | 693 | 18 | 37 |
| SaveData / SaveDevice / CPath / BtlSocket / HNMSnd (0x35f000-0x38a000) | 141 | 109 | 32 | 58 |
| BtlBonus / BtlResult / BtlFader (0x38a000-0x3b2090) | 73 | 66 | 7 | 29 |
| Sdrv / SdrvEE / SifCmd (0x3b2090-0x3b9000) | 141 | 140 | 1 | 73 |
| BtlSaveSec / AnimServer / LSDPlayer handlers (0x3b9000-0x3d5800) | 225 | 206 | 19 | 56 |
| dataAccess / prim* / disp* / deviceChecker (0x3d5800-0x3e5000) | 207 | 182 | 25 | 99 |
| BtlIn / BtlInBoss / CFieldSocket / CSe / CMusic / BgEffectMan (0x3e5000-0x3fee60) | 387 | 367 | 20 | 67 |
| Field-side helpers: CPauser/CLSDPauser/CScrCapture/GenericData/EventHandler/LSDScrEx/StreamBGM (0x3fee60-0x4075a0) | 151 | 131 | 20 | 36 |
| CBBPolygon / CBGBat / M524 / sinit / kernel-patch tail (0x4075a0-0x440000) | 244 | 231 | 13 | 29 |

## What remains, and why
Cause classification of the 667 (list with addresses: notes/I/us_unnamed_N5.txt; clusters: bottom of this file):
| program | retail-new, no JP candidate in the anchor bracket | retail-new extras (JP candidates exist, score below the floor) | rewritten (JP candidates, no confident pair) | tiny stub / inline accessor (<=0x40) | SDK |
|---|---|---|---|---|---|
| SLUS_210.41 | 99 | 59 | 29 | 47 | 29 |
| SH2US_FIELD.BIN | 156 | 67 | 43 | 70 | -- |
| SH2US_BATTLE.BIN | 39 | 12 | 13 | 4 | -- |

* **SDK (29)**: the US build links a different libvu0/libmpeg/libcdvd/libkernl revision (smaller `sceMpeg*`, merged tail functions, `syscall` stubs with identical bodies at several addresses: `RFU091`/`RFU116_SetSyscall`/`InitTLB`/`AddDmacHandler`/`kCopy` appear several times in the main list and cannot be told apart by content).  Five libkernl names that the rename tool rejects (`VSync`, `Exit`, `SetTLBHandler`, `InitTLBFunctions`, `InitTLB32MB`) are recorded as labels only.
* **retail-new without JP candidate**: the in-game menu additions of the FIELD overlay beyond the 158 recovered functions (worldMap panels 0x553ad0-0x557280, shop/tailor/solomon extras, `CField` sound queue 0x51c3f0-0x51d930, `CField::StartEffect` helpers), the 12 BATTLE camera/boss-effect modes (`UpdateRetailCamera*`, the ten 0x484630-0x49cdd0 boss effect functions, `AIInit` family 0x6abaf0-0x6cf020 = a 110 KB rewritten battle AI/sequence engine), the retail `dataAccess` save/load screen (rewritten on top of the Menu toolkit: `primWin`/`primCursor` calls became `MenuWindow`/`Cursor` calls, 89 US vs 38 JP functions; 13 names recovered by sequence alignment, the rest need per-function reading), SaveData/SaveDevice helpers 0x35fc10-0x362120 (checksum, thumbnail, icon order), BtlSaveSec 0x3bba80-0x3c4e40 (stat tables), `BtlSocket` helpers, 29 Fp helper functions of existing classes.
* **rewritten**: Menu toolkit Font accessors (0x271220-0x271360), MenuModelManeger, SaveMenuSection party helpers, FpObjectTaki/Thunder members, `BtlBonus::MakePacket`-adjacent helpers.
* **tiny stubs**: PAD/Cursor/FontDraw accessor copies emitted out of line in the FIELD overlay (0x4ed400-0x4f0640 FieldMessage/FaceImage block: 23+14 functions of 0x10-0x90 bytes), save-block bit tests, vtable stubs.

## Clusters of unnamed functions (>=1 within 0x1000 of each other)

### SLUS_210.41
| range | unnamed | neighbouring classes |
|---|---|---|
| 0x203ee8-0x203ee8 | 1 | _getRef0 x1 |
| 0x20aec8-0x20aed8 | 2 | open x2 |
| 0x20c910-0x20cc10 | 2 | scePrintf x1, sceSifExitCmd x1 |
| 0x212d80-0x213968 | 3 | SetTLBHandler x1, supplement_crt0 x1, InitExecPS2 x1 |
| 0x215eb0-0x216990 | 2 | sceCdSyncS x1, sceCdRead x1 |
| 0x21fa50-0x21fa60 | 2 | InitMain__Fv x2 |
| 0x222d30-0x222f10 | 4 | Matrix x3, FVector x1 |
| 0x225a00-0x225cf0 | 2 | LightData x2 |
| 0x22b580-0x22b580 | 1 | OrderPacket x1 |
| 0x233ed8-0x233ed8 | 1 | strlen x1 |
| 0x239770-0x239cf0 | 2 | converttobcd x1, Overlay x1 |
| 0x23bce0-0x23d000 | 6 | Model x6 |
| 0x23f6a0-0x23f6a0 | 1 | Atomic x1 |
| 0x2425c0-0x2425c0 | 1 | SequenceControl x1 |
| 0x245380-0x245380 | 1 | Texture x1 |
| 0x248500-0x248f00 | 2 | BRN_LinkList x1, BlendShape x1 |
| 0x24f2b0-0x24f690 | 4 | checkBoundingArea2__FR x4 |
| 0x2520b0-0x2520b0 | 1 | BoundingCircle x1 |
| 0x25fc70-0x25fc70 | 1 | ExModel x1 |
| 0x261540-0x261a70 | 2 | BBAtomic x1, Scissor x1 |
| 0x264420-0x264a10 | 2 | ClutRaster x1, MenuTexture x1 |
| 0x26fb90-0x26fe90 | 2 | Cursor x1, Font x1 |
| 0x271220-0x2737d0 | 10 | Font x5, MenuObj x2, Retail_ClutHolderDt x1 |
| 0x277300-0x277420 | 2 | MenuScene x2 |
| 0x27ebb0-0x27eee0 | 3 | MenuModel x3 |
| 0x280180-0x281210 | 6 | MenuModelManeger x6 |
| 0x286eb0-0x288830 | 13 | SaveMenuSection x13 |
| 0x28c120-0x28c120 | 1 | MenuCommon x1 |
| 0x28ee50-0x28fe90 | 3 | MenuModelPack x3 |
| 0x295ae0-0x295ae0 | 1 | CScript x1 |
| 0x29a8d0-0x29af60 | 2 | CScript x2 |
| 0x2a3330-0x2a3330 | 1 | SetWhiteTex__FP12tagPT x1 |
| 0x2a6fa0-0x2a6fa0 | 1 | SetFlareGlow__FfP7FpFl x1 |
| 0x2add50-0x2addf0 | 2 | FpSmoke x2 |
| 0x2af1e0-0x2af1e0 | 1 | FpSun x1 |
| 0x2b2c60-0x2b2c60 | 1 | FpObjectLenzFlare x1 |
| 0x2b8ae0-0x2b8ef0 | 2 | FpObjectThunder x2 |
| 0x2bc420-0x2be4d0 | 7 | FpBlackHole x4, FpRetailBolt x3 |
| 0x2c0700-0x2c0d20 | 2 | FpObjectBlackHole x1, FpObjectTnderBH2 x1 |
| 0x2c1dd0-0x2c1ef0 | 2 | FpObjectTnderBH2 x1, FpObjectTnderBH x1 |
| 0x2c54a0-0x2c5d70 | 2 | FpObjectTaki x2 |
| 0x2fc9d0-0x2fc9d0 | 1 | JRing x1 |
| 0x3351c0-0x336df0 | 9 | Effect x5, tagEffSeCtrl x2, EffectCore x2 |
| 0x3385c0-0x3385c0 | 1 | EffectCore x1 |
| 0x33b110-0x33b110 | 1 | EffectCore x1 |
| 0x33dec0-0x33ee60 | 2 | BBPLineModel x1, EffectCamera x1 |
| 0x344940-0x344940 | 1 | mdlRetail929__FiiPPcPv x1 |
| 0x3535b0-0x3535b0 | 1 | cbReleaseSDH__FPvPUiUi x1 |
| 0x35df30-0x35e460 | 3 | fefRetail3010__FiiPPcP x2, fefRetail3008__FiiPPcP x1 |
| 0x35fc10-0x360440 | 12 | SaveData x9, SaveDataSection x3 |
| 0x361b20-0x362c60 | 9 | SaveDevice x6, SaveDeviceMC x2, CPath x1 |
| 0x3649c0-0x3649c0 | 1 | CPathControl x1 |
| 0x3686b0-0x369330 | 8 | BtlSocket x6, HNMApi x2 |
| 0x386130-0x386390 | 2 | BtlSaveSec x2 |
| 0x38a900-0x38af50 | 2 | HNMSnd x2 |
| 0x38d020-0x38d840 | 4 | HNMSnd x4 |
| 0x3aeb30-0x3aeb30 | 1 | BtlResult x1 |
| 0x3b2360-0x3b2360 | 1 | BtlFader x1 |
| 0x3bba80-0x3bc710 | 6 | BtlSaveSec x6 |
| 0x3be860-0x3c02f0 | 8 | BtlSaveSec x8 |
| 0x3c4e40-0x3c4e40 | 1 | BtlSaveSec x1 |
| 0x3c6050-0x3c6050 | 1 | AnimServerHandler x1 |
| 0x3c82c0-0x3c82c0 | 1 | LSDPlayer x1 |
| 0x3c93d0-0x3c93d0 | 1 | LSDPlayer x1 |
| 0x3ccda0-0x3ccda0 | 1 | MovieServerHandler x1 |
| 0x3d6d90-0x3d7460 | 5 | dataAccess x5 |
| 0x3d8fb0-0x3dc630 | 11 | prim2D x7, dataAccess x3, primPacket x1 |
| 0x3de640-0x3de640 | 1 | primSprite x1 |
| 0x3e22a0-0x3e3b20 | 8 | dispCash x2, primModel x2, MsgTable x2 |
| 0x3eab90-0x3eab90 | 1 | GetRleLength__FPv x1 |
| 0x3ebda0-0x3ed220 | 9 | BtlInBoss x8, GetRleLength__FPv x1 |
| 0x3f3ce0-0x3f5dc0 | 6 | Retail_CountBits__FPUc x2, InitFieldSocketCB__FPF x2, RestoreTreasureFlag__F x1 |
| 0x3f6fd0-0x3f8380 | 4 | CFieldSocket x2, Retail_CFieldSocket_Se x1, FieldChkEncountItem__F x1 |
| 0x3fef60-0x3fef60 | 1 | ReplaceLF__FPc x1 |
| 0x4000c0-0x401d60 | 6 | CScrCapture x2, LSDScrEx x2, StreamBGM x2 |
| 0x4044b0-0x4044b0 | 1 | FldTimer x1 |
| 0x405850-0x4075a0 | 13 | SetFullSprite2__FP5P2P x9, P2Filter x3, CGhostEfx x1 |
| 0x40d700-0x40d700 | 1 | CBRingSoul x1 |
| 0x411b70-0x411b70 | 1 | FrameChange x1 |
| 0x414410-0x414ec0 | 6 | CBGBat x6 |
| 0x4373b0-0x437e10 | 4 | __sinit_dvdorder.cpp x1, __sinit_PutiEffect.cpp x1, __sinit_ModelServer.cp x1 |

### SH2US_FIELD.BIN
| range | unnamed | neighbouring classes |
|---|---|---|
| 0x45efc0-0x45efc0 | 1 | SavePoint x1 |
| 0x460380-0x4613b0 | 3 | SavePoint x1, DelayLight x1, WarpPoint x1 |
| 0x463770-0x464190 | 7 | CmdMenu x6, WarpPoint x1 |
| 0x467bb0-0x468570 | 2 | solomonCursor x1, CmdTop x1 |
| 0x469880-0x469880 | 1 | CmdTop x1 |
| 0x46ad60-0x46ad60 | 1 | CmdTop x1 |
| 0x46c0c0-0x46e050 | 14 | CmdPC x8, CmdParty x6 |
| 0x46fbf0-0x46fe30 | 2 | CmdExplain x2 |
| 0x4734b0-0x473b60 | 2 | CmdItem x1, CmdTitleLog x1 |
| 0x4765a0-0x479ea0 | 15 | MenuElement x8, CmdElement x5, DelayDeleteObject x1 |
| 0x47b270-0x47b320 | 3 | CmdPrivate x3 |
| 0x47d360-0x47d6b0 | 2 | CmdStatus x2 |
| 0x47f420-0x47fea0 | 4 | CmdEquipment x3, CmdRingCustom x1 |
| 0x484700-0x484700 | 1 | CmdTopMenu x1 |
| 0x4868b0-0x48cdf0 | 22 | CmdTarot x8, CmdTechnique x2, CmdProfile x2 |
| 0x491340-0x491340 | 1 | CmdHelpExplain x1 |
| 0x493770-0x495810 | 7 | CmdAroma x4, CmdGraveyard x2, CmdGraveyardMenu x1 |
| 0x498e20-0x498e20 | 1 | CmdLibrary x1 |
| 0x49b1d0-0x49c2d0 | 4 | CmdLibraryDetail x4 |
| 0x49fb30-0x4a01e0 | 2 | CmdRingCustom x2 |
| 0x4a39d0-0x4a3a50 | 2 | CmdRingCustomHitArea x2 |
| 0x4a5800-0x4a7d20 | 10 | CmdFusion x9, CmdRingCustomFinalSlot x1 |
| 0x4ad5b0-0x4aea90 | 5 | CmdScore x5 |
| 0x4b0ea0-0x4b1a00 | 3 | CmdKeyCustom x2, CmdScoreTitle x1 |
| 0x4b3860-0x4b49c0 | 3 | CmdKeyCustomMenu x1, CmdSubMenu x1, CmdLibraryInfo x1 |
| 0x4b6a80-0x4b78e0 | 5 | CmdFormation x3, CmdFusionLevelup x2 |
| 0x4b8c30-0x4b9090 | 3 | CmdFormation x3 |
| 0x4bb990-0x4be0b0 | 12 | CmdFormationTeam x7, CmdWolfBout x4, CmdNoteMessage x1 |
| 0x4c4970-0x4c55b0 | 2 | CmdComboKeyGoods x1, CmdPCInfo x1 |
| 0x4c7cf0-0x4c7cf0 | 1 | CmdComboMagic x1 |
| 0x4c9800-0x4c9880 | 2 | CmdMagic x2 |
| 0x4cd2c0-0x4cd2c0 | 1 | CmdCrest x1 |
| 0x4d64d0-0x4d65b0 | 2 | MenuModelAura x2 |
| 0x4d81a0-0x4d8220 | 2 | CmdPropertyList x2 |
| 0x4d9eb0-0x4dabb0 | 2 | CmdPropertyList x2 |
| 0x4dc800-0x4dc800 | 1 | CmdRingCustomAutoRing x1 |
| 0x4ed400-0x4f2360 | 57 | FieldMessage x23, FaceImage x14, FldTeamChange x6 |
| 0x4fcba0-0x4fcba0 | 1 | CField x1 |
| 0x500a90-0x500a90 | 1 | CField x1 |
| 0x504d90-0x504d90 | 1 | FldSpline x1 |
| 0x5061c0-0x5097f0 | 8 | CFieldModel x3, CFieldEvent x2, mdlReadMotionCB__FiP9B x2 |
| 0x50aed0-0x50aed0 | 1 | CFieldModel x1 |
| 0x50d440-0x50e0a0 | 2 | CFieldModel x2 |
| 0x5126e0-0x5126e0 | 1 | CXFModel x1 |
| 0x514300-0x514300 | 1 | BgeffLight x1 |
| 0x519430-0x519430 | 1 | GetObjSeSize__FPQ23SDB x1 |
| 0x51bd00-0x521610 | 40 | CField x25, CFieldBG x10, FldTeamChange x4 |
| 0x526be0-0x526be0 | 1 | shop x1 |
| 0x529290-0x529290 | 1 | shop x1 |
| 0x530730-0x530d80 | 3 | shop x3 |
| 0x53a4b0-0x53a4b0 | 1 | tailor x1 |
| 0x546860-0x546860 | 1 | solomon x1 |
| 0x547c00-0x548d30 | 4 | solomon x4 |
| 0x549ea0-0x54bd00 | 6 | solomon x5, solomonEffect x1 |
| 0x54e670-0x550250 | 9 | floatDemon x6, solomonCursor x2, solomonSlot x1 |
| 0x551b40-0x553ef0 | 12 | solomonThm x6, worldMap x5, solomonEffect x1 |
| 0x5553c0-0x5576c0 | 17 | worldMap x10, pageScrollMark x7 |
| 0x559510-0x55ae10 | 6 | worldMap x6 |
| 0x55e290-0x55e290 | 1 | worldMapThm x1 |
| 0x55f590-0x55ff60 | 9 | worldMapPoint x9 |

### SH2US_BATTLE.BIN
| range | unnamed | neighbouring classes |
|---|---|---|
| 0x48c0d0-0x48c0d0 | 1 | CBattle x1 |
| 0x48fe30-0x48fe30 | 1 | CBattle x1 |
| 0x493450-0x4958d0 | 5 | CBattle x5 |
| 0x499b40-0x499b40 | 1 | CBattle x1 |
| 0x49ccd0-0x49ccd0 | 1 | CBattle x1 |
| 0x4a1280-0x4a1280 | 1 | CBattle x1 |
| 0x4a2b50-0x4a2b50 | 1 | CBattle x1 |
| 0x4e0d70-0x4e0d70 | 1 | CBattle x1 |
| 0x51cfa0-0x51da80 | 2 | TotalHitInfo x2 |
| 0x5718b0-0x572850 | 4 | BreakBBox x4 |
| 0x576820-0x576820 | 1 | BreakBBox x1 |
| 0x57a510-0x57af20 | 4 | BreakBBox x4 |
| 0x57d9f0-0x57db20 | 2 | BreakBBox x1, BBoxAddAttribute1 x1 |
| 0x587900-0x587900 | 1 | BtlModel x1 |
| 0x58f340-0x58f340 | 1 | BtlModel x1 |
| 0x5cec30-0x5cf210 | 3 | CBtlPAfter2 x3 |
| 0x5ed6e0-0x5ed6e0 | 1 | BtlMenu x1 |
| 0x6202f0-0x6202f0 | 1 | BMesWin x1 |
| 0x624570-0x624f70 | 2 | Get3DAngle2__F7FVector x1, GetPointToLineLength__ x1 |
| 0x627830-0x627830 | 1 | StatusRecovery__Fii x1 |
| 0x62fc80-0x62fc80 | 1 | CharactorShow__Fib x1 |
| 0x6330d0-0x6330d0 | 1 | SetForceDeath__Fi x1 |
| 0x659ea0-0x659ea0 | 1 | CBattle x1 |
| 0x65d370-0x65d370 | 1 | CBattle x1 |
| 0x672080-0x672080 | 1 | CBattle x1 |
| 0x675c90-0x675e30 | 2 | CBattle x2 |
| 0x678be0-0x678d30 | 2 | CBattle x2 |
| 0x67b220-0x67b220 | 1 | CBattle x1 |
| 0x688330-0x688330 | 1 | CBattle x1 |
| 0x68a1b0-0x68a1b0 | 1 | CBattle x1 |
| 0x69e160-0x69e160 | 1 | CBattle x1 |
| 0x6a0c30-0x6a0c30 | 1 | CBattle x1 |
| 0x6a62f0-0x6a6f70 | 3 | CBattle x3 |
| 0x6a8220-0x6a8eb0 | 2 | CBattle x2 |
| 0x6c6730-0x6c6730 | 1 | CBattle x1 |
| 0x6ce010-0x6cf020 | 6 | CBattle x6 |
| 0x6d9450-0x6d9450 | 1 | CBattle x1 |
| 0x6defb0-0x6e0320 | 5 | CBattle x5 |
| 0x6e26e0-0x6e26e0 | 1 | CBattle x1 |

---

# Coverage after pass N6 (final: 0 unnamed functions)

Pass N6 named the 667 functions left by N5 (`us_unnamed_N5.txt`), recorded name by name in `us_map_N6.txt` (name read back from Ghidra at the end of the pass), and created 58 functions that were hidden inside the preceding function's body or were vtable-slot targets Ghidra had not made functions.  All four programs are saved.

## Per program (final)
| program | functions | unnamed | named by N6 | functions created in N6 |
|---|---|---|---|---|
| SLUS_210.41 | 5,224 | **0** | 263 | 57 (48 mid-entry points called from the overlays, plus the SDK ones: `ioctl` 0x20aed0, `_set_sreg` 0x20c8e0, `_change_addr` 0x20c900, `sceSifSetSysCmdBuffer` 0x20cc28, `_sceCdSC` 0x216020, `kCopy` 0x212d90/0x2135d8/0x213978, `kFindAddress` 0x213610) |
| SH2US_FIELD.BIN | 2,353 | **0** | 336 | 0 |
| SH2US_BATTLE.BIN | 827 | **0** | 68 | 1 (`MakePacket__14BtlTarotEffect` 0x57b2d0) |
| SH2US_OPENING.BIN | 104 | **0** | 0 | 0 |
| **total** | 8,508 | **0** | 667 | 58 |

## Names applied per cause group (N5 cause -> kind of name)
K = JP-style `Method__Class` name (JP name carried over where the role is identical, or a behaviour name in JP style); R = `Retail_<Class>_<Method>` (retail-new behaviour, no JP twin); S = `Sub<addr>__Class` / `stub_<caller>_<n>` (no behaviour recoverable).

| cause group | rows | K | R | S |
|---|---|---|---|---|
| SDK leftovers | 29 | 23 | 4 | 2 |
| retail-new, no JP candidate in bracket | 294 | 90 | 203 | 1 |
| retail-new extras (JP candidates below floor) | 138 | 61 | 75 | 2 |
| rewritten (JP candidates, no confident pair) | 85 | 63 | 22 | 0 |
| tiny stub / inline accessor | 121 | 29 | 89 | 3 |
| **total** | 667 | 266 | 393 | 8 |

By program: main 263 (123 K / 132 R / 8 S), FIELD 336 (109 / 227 / 0), BATTLE 68 (34 / 34 / 0).

## Caveats (why "0 unnamed" is not "all names are right")
* The 393 `Retail_*` names are behaviour-derived; the 8 `S` names are placeholders by caller.  Prefer the class/method names in `us_retail_classes.md` where they differ.
* The "retail-new extras" group: where a JP name below the similarity floor was usable (same class, same bracket position, same callee/size shape) it was taken; otherwise the function was named by behaviour.
* A mid-pass audit (sandwiched class outliers, duplicate names, positional ct/dt triples) corrected about 60 names from earlier passes and from the first half of N6 (examples: the OrderPacket/List cluster, `convert{to,from}bcd`, `_sceCd_ncmd_prechk`, `TarotEffectFunc`, the EndSet stub run, the Cmd* ct/dt names).  The audit was partial.  Known remaining duplicates (Ghidra allows them): `Retail_CField_cbCmdScene` x2, `AddDmacHandler`, `GetBekijo__FUi`, `ResetLink__15DynamicsControl`, `olLoadCB`, `setD4_CHCR`.
* SDK: the libkernl revision tag is `libkernl2710` in both JP and US (identical SDK revision for the kernel stubs); libvu0/libmpeg leftovers were labelled by matching the sce string/version tags and instruction shape.
* The per-name evidence notes for the early N6 batches (CField/shop/solomon/worldMap and the first main/BATTLE batches) were lost with the working directory mid-pass; their effect exists in Ghidra and in `us_map_N6.txt`, and the later batches are in `tools/I_N6/names/*.txt` with `applied_log.txt`.

## Deliverables of N6
* `us_map_N6.txt` (667 rows), `us_rewritten.md` (85 rewritten functions vs JP), `us_retail_classes.md` (N6 additions), cleaned C in `decomp/I/us_battle_phases.c`, `us_battle_tarot.c`, `us_battle_aiinit.c`, tooling in `tools/I_N6/`.
