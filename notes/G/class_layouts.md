# FIELD.BIN class layouts recovered from constructors and allocation sites

Generated from the JP overlay (`SH2JP_FIELD.BIN`): base class = first base-constructor call in the ctor, members = embedded sub-object constructors (`__ct__` called with `this+off`), vtables = stores of `__vt__*` into `this`, size = argument of the `operator new` (`__nw__FUi`) call that precedes the ctor call inside this overlay (`?` = allocated from the main exe or on the stack; not scanned). Offsets are bytes from the object start.

| class | base | size | #funcs | embedded members | vtable stores | ctor |
|---|---|---|---|---|---|---|
| `BgeffLight` | PutiObject | 0x200 | 5 |  |  | `0x004ce240` |
| `BgeffLightPrim` | PutiPrim | 0x48 | 4 |  | +0x10 __vt__14BgeffLightPrim | `0x004ce040` |
| `CAnalogStick` | - | ? | 3 |  |  | `0x004a6150` |
| `CBalIcon` | DelayDeleteObject | 0x2c | 9 |  | +8 __vt__8CBalIcon | `0x004cc7c0` |
| `CFModel` | Model | ? | 8 |  | +0x10 __vt__7CFModel | `0x004cc280` |
| `CField` | CScriptEx | ? | 201 | +0x1cd0 FVector, +0x1ce0 FVector, +0x1cf0 FVector, +0x1d00 BufMemory, +0x1d10 FVector, +0x1d20 FVector | +0x14 __vt__6CField | `0x004a2b00` |
| `CFieldBG` | - | ? | 24 |  |  | `0x004da620` |
| `CFieldCamera` | - | ? | 15 | +0x30 FVector, +0x40 FVector, +0x50 FVector, +0x60 FVector, +0x70 FVector, +0x80 FVector, +0x90 FVector, +0xb0 FVector, +0xc0 FVector |  | `0x004be190` |
| `CFieldEvent` | - | ? | 8 |  |  | `0x004befa0` |
| `CFieldModel` | DelayDeleteObject | ? | 111 | +0x10 FVector, +0x20 FVector, +0x30 FVector, +0x40 FVector, +0x50 FVector, +0x60 FVector | +8 __vt__11CFieldModel | `0x004c06b0` |
| `CFloorMan` | - | ? | 9 |  |  | `0x004bc850` |
| `CList` | - | ? | 1 |  |  | `0x004c0810` |
| `CNaviMap` | DelayDeleteObject | 0x120 | 32 | +0x10 _NaviWork, +0xd0 Matrix, +0x110 CImage | +8 __vt__8CNaviMap | `0x004cf1a0` |
| `CXFModel` | ExModel | ? | 8 |  | +0x10 __vt__8CXFModel | `0x004cc530` |
| `CmdAroma` | CmdPrivateScene | 0x520 | 13 | +0x70 CmdAromaBaseOil, +0x3f0 CmdAromaBlend | +8 __vt__8CmdAroma | `0x0045f4e0` |
| `CmdAromaBaseOil` | CmdWindow | ? | 6 | +0xb4 FontDraw, +0xf4 FontDraw, +0x134 SendOnLocal, +0x168 MenuTexture, +0x1a8 SendOnLocal, +0x1d8 MenuText | +8 __vt__15CmdAromaBaseOil | `0x00460580` |
| `CmdAromaBlend` | CmdWindow | ? | 7 | +0xb4 FontDraw, +0xf4 SendOnLocal | +8 __vt__13CmdAromaBlend | `0x00460f50` |
| `CmdBackGround` | MenuScene | 0x1e0 | 4 | +0x5c MenuWindow, +0x110 MenuTexture, +0x150 SendOnLocal, +0x180 MenuSprite | +8 __vt__13CmdBackGround | `0x00438450` |
| `CmdBackGroundCapture` | CmdBackGround | 0x398 | 4 | +0x1e8 MenuTexture, +0x228 SendOnLocal, +0x258 SendOnLocal, +0x348 MenuRegister, +0x370 MenuRegister | +8 __vt__20CmdBackGroundCapture | `0x00437e50` |
| `CmdButtonReport` | MenuScene | ? | 8 | +0x58 MenuWindow, +0x10c SendOnLocal, +0x13c FontDraw | +8 __vt__15CmdButtonReport | `0x0043de70` |
| `CmdClothes` | CmdPrivateScene | 0x78 | 13 |  | +8 __vt__10CmdClothes | `0x00458070` |
| `CmdClothesSlot` | CmdWindow | 0x254 | 6 | +0xb4 FontDraw, +0xf4 SendOnLocal, +0x124 MenuGroup, +0x174 MenuSprite, +0x1d4 MenuText | +8 __vt__14CmdClothesSlot | `0x00458bf0` |
| `CmdComboKey` | CmdPCScene | 0xcc0 | 21 | +0x88 CmdComboKeySlot, +0xad0 CmdSubTitle | +8 __vt__11CmdComboKey | `0x00485ef0` |
| `CmdComboKeyCharacter` | CmdWindow | 0xf8 | 7 | +0xb4 FontDraw | +8 __vt__20CmdComboKeyCharacter | `0x004898b0` |
| `CmdComboKeyCommand` | CmdWindow | 0x374 | 7 | +0xb4 FontDraw | +8 __vt__18CmdComboKeyCommand | `0x00489210` |
| `CmdComboKeyGoods` | CmdWindow | 0x128 | 7 | +0xb4 SendOnLocal, +0xe4 FontDraw | +8 __vt__16CmdComboKeyGoods | `0x00489f90` |
| `CmdComboKeySlot` | CmdWindow | ? | 7 | +0xb4 FontDraw, +0xf4 MenuText, +0x174 SendOnLocal, +0x1a4 SendOnLocal | +8 __vt__15CmdComboKeySlot | `0x00488610` |
| `CmdComboMagic` | MenuScene | 0x188 | 8 | +0x68 FontDraw, +0xa8 MenuWindow | +8 __vt__13CmdComboMagic | `0x0048c130` |
| `CmdCommon` | MenuScene | ? | 4 | +0x58 Cursor, +0x158 MenuTexture | +8 __vt__9CmdCommon | `0x00437740` |
| `CmdCrest` | CmdPCScene | 0x9c0 | 26 | +0x88 MenuScene, +0xe0 MenuScene, +0x1f8 CmdSubMenu, +0x350 CmdCrestPCInfo | +8 __vt__8CmdCrest | `0x00490ca0` |
| `CmdCrestDetail` | CmdWindow | 0x1d68 | 6 | +0xb4 SendOnLocal, +0xe4 SendOnLocal, +0x114 FontDraw, +0x154 FontDraw, +0x194 MenuSprite, +0x1f4 MenuText, +0x274 MenuGroup, +0x4a4 MenuPolygon, +0x528 MenuText, +0x5a8 MenuText | +8 __vt__14CmdCrestDetail | `0x00498170` |
| `CmdCrestDetailData` | MenuGroup | ? | 2 | +0x410 FontDraw, +0x450 MenuText, +0x4d0 MenuText, +0x550 MenuText |  | `0x004983a0` |
| `CmdCrestMagic` | CmdWindow | 0xca0 | 6 | +0xb8 MenuTexture, +0xf8 SendOnLocal, +0x128 SendOnLocal, +0x518 MenuPolygon, +0x59c FontDraw, +0x5dc FontDraw | +8 __vt__13CmdCrestMagic | `0x00497490` |
| `CmdCrestPCInfo` | CmdWindow | ? | 6 | +0xb8 MenuTexture, +0xf8 SendOnLocal, +0x128 SendOnLocal, +0x158 MenuSprite, +0x1b8 MenuBar, +0x220 MenuBar, +0x288 MenuBar, +0x2f0 FontDraw, +0x330 MenuText, +0x3b0 MenuText, +0x430 MenuText, +0x4b0 MenuText | +8 __vt__14CmdCrestPCInfo | `0x004900e0` |
| `CmdElement` | MenuScene | 0x6b0 | 9 | +0x58 MenuWindow, +0x110 MenuTexture, +0x150 MenuTexture, +0x190 SendOnLocal, +0x1c0 SendOnLocal, +0x1f0 MenuElement, +0x588 MenuSprite | +8 __vt__10CmdElement | `0x004462b0` |
| `CmdEquipment` | CmdPCScene | 0xd0 | 21 |  | +8 __vt__12CmdEquipment | `0x0044b820` |
| `CmdEquipmentGoods` | CmdWindow | 0x12c | 7 | +0xb4 SendOnLocal, +0xe4 FontDraw | +8 __vt__17CmdEquipmentGoods | `0x00450170` |
| `CmdEquipmentSlot` | CmdWindow | 0x714 | 7 | +0xb4 FontDraw, +0xf4 SendOnLocal, +0x124 MenuGroup, +0x174 MenuSprite, +0x1d4 MenuText, +0x254 MenuGroup, +0x2a4 MenuSprite, +0x304 MenuText | +8 __vt__16CmdEquipmentSlot | `0x0044f6d0` |
| `CmdEquipmentStatus` | CmdWindow | 0xb34 | 6 | +0xb4 FontDraw, +0xf4 FontDraw | +8 __vt__18CmdEquipmentStatus | `0x0048f350` |
| `CmdExplain` | MenuScene | 0x52c | 14 | +0x6c MenuWindow, +0x120 KeyWait, +0x1fc FontDraw, +0x23c MenuMessage, +0x2d4 FontDraw, +0x314 MenuText, +0x394 MenuText | +8 __vt__10CmdExplain | `0x0043ea00` |
| `CmdFence` | CmdWindow | ? | 6 | +0xb8 MenuTexture, +0xf8 SendOnLocal, +0x128 FontDraw | +8 __vt__8CmdFence | `0x0049af80` |
| `CmdFormation` | MenuScene | ? | 12 | +0x74 Cursor, +0x178 Cmd, +0x728 Cmd | +8 __vt__12CmdFormation | `0x0047dd70` |
| `CmdFormationMember` | CmdWindow | ? | 8 | +0xb4 SendOnLocal, +0xe4 FontDraw, +0x128 MenuTexture, +0x168 SendOnLocal, +0x528 MenuPolygon | +8 __vt__18CmdFormationMember | `0x0047f440` |
| `CmdFormationParameter` | MenuGroup | ? | 2 | +0x50 MenuTexture, +0x90 SendOnLocal, +0xc0 MenuSprite, +0x120 MenuText, +0x960 MenuSprite |  | `0x004802f0` |
| `CmdFormationTeam` | CmdWindow | ? | 15 | +0xb4 FontDraw, +0xf8 MenuTexture, +0x198 MenuGroup, +0x6a4 MenuPolygon | +8 __vt__16CmdFormationTeam | `0x00480ce0` |
| `CmdFormationTeamData` | MenuGroup | ? | 2 | +0x50 MenuText |  | `0x00481b20` |
| `CmdFriendship` | CmdPrivateScene | ? | 7 | +0x5c MenuWindow, +0x110 FontDraw | +8 __vt__13CmdFriendship | `0x004549d0` |
| `CmdFusion` | CmdPrivateScene | ? | 31 |  | +8 __vt__9CmdFusion | `0x0046ee40` |
| `CmdFusionCharge` | CmdWindow | ? | 6 | +0xb8 MenuTexture, +0xfc SendOnLocal, +0x12c SendOnLocal, +0x15c SendOnLocal, +0x18c SendOnLocal, +0x1bc MenuSprite, +0x21c MenuSprite, +0x33c MenuBar | +8 __vt__15CmdFusionCharge | `0x0047d2d0` |
| `CmdFusionLevelup` | CmdWindow | ? | 5 | +0xb8 MenuTexture, +0xf8 SendOnLocal, +0x128 MenuSprite | +8 __vt__16CmdFusionLevelup | `0x0047dae0` |
| `CmdFusionList` | CmdWindow | ? | 8 | +0xb4 FontDraw, +0xf8 Cursor | +8 __vt__13CmdFusionList | `0x004735b0` |
| `CmdFusionParameter` | CmdWindow | ? | 6 | +0xb4 FontDraw, +0xf4 FontDraw, +0x2b4 MenuText, +0x334 MenuText, +0x3b4 MenuText, +0x434 MenuText | +8 __vt__18CmdFusionParameter | `0x0047b980` |
| `CmdFusionSkillList` | CmdWindow | ? | 7 | +0xb4 FontDraw | +8 __vt__18CmdFusionSkillList | `0x0047cb00` |
| `CmdFusionStatus` | CmdWindow | ? | 6 | +0xb4 FontDraw, +0xf4 FontDraw | +8 __vt__15CmdFusionStatus | `0x0047c370` |
| `CmdGoods` | MenuGroup | ? | 2 | +0x50 MenuText, +0xd0 MenuText |  | `0x00454640` |
| `CmdGoodsButton` | MenuSprite | ? | 2 | +0x60 MenuSprite, +0xc0 MenuText |  | `0x0043dfa0` |
| `CmdGoodsComboKey` | MenuGroup | ? | 2 | +0x50 MenuText, +0xd0 MenuText, +0x150 MenuSprite |  | `0x004887a0` |
| `CmdGoodsCrest` | CmdWindow | 0x1c8 | 11 | +0xb4 SendOnLocal, +0xe4 SendOnLocal, +0x114 SendOnLocal, +0x144 SendOnLocal, +0x174 FontDraw | +8 __vt__13CmdGoodsCrest | `0x004950b0` |
| `CmdGoodsCrestData` | MenuGroup | ? | 2 | +0x50 MenuText, +0xd0 MenuText, +0x150 MenuPolygon, +0x1d4 MenuSprite, +0x534 MenuSprite, +0x594 MenuSprite, +0x5f4 MenuBar |  | `0x004958c0` |
| `CmdGoodsFusion` | MenuGroup | ? | 2 | +0x50 MenuText, +0xd0 MenuText, +0x150 MenuText |  | `0x004739f0` |
| `CmdGoodsIcon` | MenuGroup | ? | 2 | +0x50 MenuText, +0xd0 MenuText, +0x150 MenuSprite |  | `0x00450610` |
| `CmdGoodsKeyCustom` | MenuText | ? | 2 | +0x80 MenuText |  | `0x004789b0` |
| `CmdGoodsList` | MenuGroup | ? | 2 | +0x50 MenuText |  | `0x0045b690` |
| `CmdGoodsOption` | MenuSprite | ? | 2 | +0x60 MenuText |  | `0x00446e20` |
| `CmdGoodsPad` | MenuGroup | ? | 2 | +0x50 MenuSprite, +0xb0 MenuSprite |  | `0x0047a010` |
| `CmdGoodsPadMenu` | MenuGroup | ? | 2 | +0x50 MenuSprite, +0xb0 MenuText |  | `0x0047a880` |
| `CmdGoodsScore` | MenuGroup | ? | 2 | +0x50 MenuText, +0xd0 MenuText, +0x150 MenuText |  | `0x004760b0` |
| `CmdGoodsScoreRank` | MenuGroup | ? | 2 | +0x50 MenuText, +0xd0 MenuText |  | `0x00476f30` |
| `CmdGoodsSubTitle` | MenuGroup | ? | 2 | +0x170 MenuText |  | `0x00478510` |
| `CmdGoodsSword` | MenuGroup | ? | 2 | +0x50 MenuText, +0xd0 MenuText, +0x150 MenuText |  | `0x00457dd0` |
| `CmdGoodsTarot` | MenuGroup | ? | 2 | +0x50 MenuSprite, +0xb0 MenuText |  | `0x00456210` |
| `CmdGraveyard` | MenuScene | 0x31c | 8 | +0x6c CmdGraveyardMenu, +0x2e0 Smooth | +8 __vt__12CmdGraveyard | `0x0045e680` |
| `CmdGraveyardMenu` | CmdWindow | ? | 5 | +0xb4 FontDraw, +0xf4 MenuText | +8 __vt__16CmdGraveyardMenu | `0x0045f060` |
| `CmdHelp` | MenuScene | 0x2f0 | 15 | +0x68 MenuTexture, +0xa8 CmdHelpMenu, +0x1d0 CmdHelpClause | +8 __vt__7CmdHelp | `0x004590d0` |
| `CmdHelpClause` | CmdWindow | ? | 7 | +0xb4 FontDraw | +8 __vt__13CmdHelpClause | `0x0045b2e0` |
| `CmdHelpExplain` | CmdWindow | 0x428 | 8 | +0xb8 FontDraw, +0xf8 FontDraw, +0x138 MenuText, +0x1b8 MenuMessage, +0x250 MenuTexture, +0x290 SendOnLocal, +0x2c0 MenuSprite, +0x320 KeyWait | +8 __vt__14CmdHelpExplain | `0x0045bb60` |
| `CmdHelpMenu` | CmdWindow | ? | 8 | +0xb4 FontDraw, +0xf4 SendOnLocal | +8 __vt__11CmdHelpMenu | `0x0045a740` |
| `CmdHelpMenuData` | MenuText | ? | 2 | +0x80 MenuSprite |  | `0x0045ae50` |
| `CmdItem` | MenuScene | 0xa0 | 14 |  | +8 __vt__7CmdItem | `0x004402f0` |
| `CmdItemGoods` | CmdWindow | 0x128 | 8 | +0xb4 FontDraw, +0xf4 SendOnLocal | +8 __vt__12CmdItemGoods | `0x0045d540` |
| `CmdItemMessage` | CmdWindow | 0x268 | 6 | +0xb4 FontDraw, +0xf4 MenuMessage, +0x18c KeyWait | +8 __vt__14CmdItemMessage | `0x0045e1e0` |
| `CmdKeyCustom` | MenuScene | 0x1c10 | 11 | +0x68 Cursor, +0x168 MenuTexture, +0x1a8 MenuTexture, +0x1e8 MenuTexture, +0x228 CmdKeyCustomPad, +0x111c CmdKeyCustomMenu | +8 __vt__12CmdKeyCustom | `0x00478840` |
| `CmdKeyCustomMenu` | CmdWindow | ? | 5 | +0xb4 FontDraw, +0xf4 SendOnLocal | +8 __vt__16CmdKeyCustomMenu | `0x0047a720` |
| `CmdKeyCustomPad` | CmdWindow | ? | 6 | +0xb4 SendOnLocal, +0xe4 SendOnLocal, +0x114 SendOnLocal, +0x144 SendOnLocal, +0x174 FontDraw, +0xa74 MenuSprite | +8 __vt__15CmdKeyCustomPad | `0x00479e50` |
| `CmdLibrary` | MenuScene | 0x208 | 20 | +0x64 CmdSubMenu | +8 __vt__10CmdLibrary | `0x004619c0` |
| `CmdLibraryDetail` | CmdWindow | 0x1424 | 6 | +0xb4 FontDraw, +0xf4 FontDraw, +0x134 SendOnLocal, +0x4e4 MenuText, +0x564 MenuText, +0x5e4 MenuText, +0x664 MenuText, +0x6e4 MenuText, +0x764 MenuText | +8 __vt__16CmdLibraryDetail | `0x004649a0` |
| `CmdLibraryInfo` | CmdWindow | 0x308 | 6 | +0xb8 MenuTexture, +0xf8 SendOnLocal, +0x128 MenuSprite, +0x188 FontDraw, +0x1c8 FontDraw, +0x208 MenuText, +0x288 MenuText | +8 __vt__14CmdLibraryInfo | `0x0047b2e0` |
| `CmdLibraryList` | CmdWindow | 0xf8 | 6 | +0xb4 FontDraw | +8 __vt__14CmdLibraryList | `0x00465c60` |
| `CmdLibraryTitle` | CmdSubTitle | 0x248 | 4 | +0x1c8 MenuText | +8 __vt__15CmdLibraryTitle | `0x0047b7c0` |
| `CmdMagic` | CmdPCScene | 0x368 | 10 | +0x88 CmdMagicGoods, +0x180 CmdSubTitle | +8 __vt__8CmdMagic | `0x0048d2b0` |
| `CmdMagicGoods` | CmdWindow | ? | 7 | +0xb4 FontDraw | +8 __vt__13CmdMagicGoods | `0x0048e9e0` |
| `CmdMenu` | Menu | 0x17f8 | 20 | +0x70 MenuRender, +0xb8 CmdParty, +0x348 CmdCommon, +0x4e0 CmdNote, +0x780 CmdTitleLog, +0xa60 CmdButtonReport, +0x10f0 CmdElement, +0x17a0 MenuScene | +0x14 __vt__7CmdMenu | `0x00435860` |
| `CmdMenuTutorial` | CmdMenu | ? | 7 | +0x180c MenuWindow, +0x18c0 FontDraw, +0x1900 MenuMessage, +0x1998 KeyWait | +0x14 __vt__15CmdMenuTutorial | `0x00473fc0` |
| `CmdNote` | MenuScene | ? | 5 | +0x58 MenuWindow, +0x110 MenuTexture, +0x150 SendOnLocal, +0x180 MenuSprite, +0x1e0 FontDraw, +0x220 MenuText | +8 __vt__7CmdNote | `0x00437970` |
| `CmdNoteMessage` | CmdWindow | 0x2b0 | 7 | +0xb4 FontDraw, +0xf4 MenuText, +0x174 MenuSprite, +0x1d4 KeyWait | +8 __vt__14CmdNoteMessage | `0x00483150` |
| `CmdOption` | MenuScene | 0x2640 | 8 | +0x848 MenuWindow, +0x8fc MenuWindow, +0x9b0 FontDraw, +0x9f0 FontDraw, +0x20b0 MenuBar, +0x24e0 MenuTexture, +0x2520 MenuTexture, +0x2560 MenuTexture, +0x25a0 SendOnLocal, +0x25d0 SendOnLocal, +0x2600 SendOnLocal | +8 __vt__9CmdOption | `0x00446be0` |
| `CmdPC` | - | ? | 21 |  |  | `0x0043ad20` |
| `CmdPCInfo` | MenuScene | 0xaa4 | 5 | +0x58 MenuWindow, +0x10c FontDraw, +0x14c FontDraw, +0x38c MenuText, +0x40c MenuText, +0xa14 SendOnLocal, +0xa44 MenuSprite | +8 __vt__9CmdPCInfo | `0x0048a930` |
| `CmdPCScene` | MenuScene | ? | 8 |  | +8 __vt__10CmdPCScene | `0x0048b540` |
| `CmdParameter` | MenuText | ? | 2 | +0x80 MenuText |  | `0x0044ac40` |
| `CmdParty` | - | ? | 13 |  |  | `0x0043cad0` |
| `CmdPhotograph` | CmdPrivateScene | 0x354 | 5 | +0x5c CmdPhotographGoods | +8 __vt__13CmdPhotograph | `0x00456730` |
| `CmdPhotographGoods` | CmdWindow | ? | 5 | +0xb4 FontDraw | +8 __vt__18CmdPhotographGoods | `0x00456ae0` |
| `CmdPrivate` | CmdPCScene | 0x98 | 17 |  | +8 __vt__10CmdPrivate | `0x00448b40` |
| `CmdPrivateMenu` | CmdWindow | 0x374 | 6 | +0xb4 FontDraw | +8 __vt__14CmdPrivateMenu | `0x0044ed20` |
| `CmdPrivateScene` | MenuScene | ? | 6 |  | +8 __vt__15CmdPrivateScene | `0x0044b700` |
| `CmdProfile` | CmdPrivateScene | 0x58c | 8 | +0x60 CmdExplain | +8 __vt__10CmdProfile | `0x00455310` |
| `CmdPropertyGoods` | CmdWindow | 0x12c | 7 | +0xb4 FontDraw, +0xf4 SendOnLocal | +8 __vt__16CmdPropertyGoods | `0x0049e200` |
| `CmdPropertyList` | MenuScene | 0x16c | 16 | +0x78 MenuScene, +0xd0 MenuScene | +8 __vt__15CmdPropertyList | `0x0049b890` |
| `CmdPropertySlot` | MenuGroup | ? | 2 | +0x50 MenuSprite, +0xb0 MenuText |  | `0x0044f870` |
| `CmdRingCustom` | CmdPCScene | 0x128, 0x220, 0x254 | 33 | +0x8c CmdSubMenu | +8 __vt__13CmdRingCustom | `0x00466e30` |
| `CmdRingCustomAutoRing` | CmdWindow | 0x1f8 | 7 | +0xb4 FontDraw | +8 __vt__21CmdRingCustomAutoRing | `0x0049fc30` |
| `CmdRingCustomCount` | CmdWindow | 0x788 | 8 | +0xb4 FontDraw | +8 __vt__18CmdRingCustomCount | `0x0049f210` |
| `CmdRingCustomFinalGoods` | CmdWindow | ? | 8 | +0xb4 FontDraw, +0xf4 SendOnLocal | +8 __vt__23CmdRingCustomFinalGoods | `0x0046d520` |
| `CmdRingCustomFinalSlot` | CmdWindow | ? | 7 | +0xb4 FontDraw, +0xf4 SendOnLocal, +0x124 MenuGroup, +0x174 MenuSprite, +0x1d4 MenuText | +8 __vt__22CmdRingCustomFinalSlot | `0x0046e090` |
| `CmdRingCustomGoods` | CmdWindow | 0x2f8 | 7 | +0xb4 FontDraw | +8 __vt__18CmdRingCustomGoods | `0x0048faf0` |
| `CmdRingCustomHitArea` | CmdWindow | 0xea0 | 8 | +0xb4 FontDraw, +0xe14 ScrollMark | +8 __vt__20CmdRingCustomHitArea | `0x0046b880` |
| `CmdRingCustomInfo` | CmdWindow | 0xa80 | 6 | +0xb8 MenuTexture, +0xf8 SendOnLocal, +0x128 SendOnLocal, +0x158 FontDraw, +0x198 FontDraw, +0x638 MenuPolygon | +8 __vt__17CmdRingCustomInfo | `0x0046cab0` |
| `CmdRingMessage` | MenuScene | 0x3e4 | 5 | +0x5c Cursor, +0x158 MenuWindow, +0x20c FontDraw, +0x24c MenuMessage | +8 __vt__14CmdRingMessage | `0x0046e710` |
| `CmdSTAllParameter` | MenuGroup | ? | 2 | +0x50 MenuText, +0xd0 MenuText, +0x150 MenuText, +0x1d0 MenuText |  | `0x00443970` |
| `CmdScore` | MenuScene | 0x2dc | 13 | +0xa4 CmdScoreTitle, +0x218 MenuWindow | +8 __vt__8CmdScore | `0x00474c10` |
| `CmdScoreData` | CmdWindow | 0x1414 | 6 | +0xb4 FontDraw | +8 __vt__12CmdScoreData | `0x00475f50` |
| `CmdScoreRank` | CmdWindow | 0xfc, 0x248 | 6 | +0xb4 FontDraw | +8 __vt__12CmdScoreRank | `0x00476880` |
| `CmdScoreRankFrame` | CmdWindow | ? | 5 | +0xb8 MenuTexture, +0xf8 SendOnLocal, +0x128 MenuSprite, +0x188 MenuText, +0x208 FontDraw | +8 __vt__17CmdScoreRankFrame | `0x00477970` |
| `CmdScoreTitle` | CmdWindow | ? | 6 | +0xb4 FontDraw, +0xf4 MenuText | +8 __vt__13CmdScoreTitle | `0x00477d50` |
| `CmdSelectTarget` | MenuScene | 0xaa0 | 6 | +0x74 MenuWindow, +0x1a8 MenuTexture, +0x1e8 SendOnLocal, +0x218 SendOnLocal, +0x248 MenuSprite, +0x2a8 MenuSprite, +0x308 FontDraw, +0x348 MenuText, +0x3c8 MenuText, +0x448 MenuText, +0x4c8 MenuText, +0x548 MenuText, +0x5c8 MenuText, +0x648 MenuText, +0x6c8 MenuText, +0x748 MenuText, +0x7c8 MenuText, +0x850 MenuWindow, +0x904 FontDraw, +0x944 MenuText, +0x9c4 KeyWait | +8 __vt__15CmdSelectTarget | `0x00442bd0` |
| `CmdSort` | MenuScene | 0x160 | 5 | +0x5c MenuWindow, +0x110 FontDraw | +8 __vt__7CmdSort | `0x00466490` |
| `CmdStatus` | CmdPrivateScene | 0xf28 | 7 | +0x5c MenuWindow, +0x110 FontDraw, +0xa50 MenuText, +0xad0 MenuText, +0xb50 MenuText, +0xbd0 MenuText, +0xd58 CmdSubTitle | +8 __vt__9CmdStatus | `0x0044aab0` |
| `CmdSubMenu` | MenuScene | 0x154 | 6 | +0x58 MenuWindow, +0x10c FontDraw | +8 __vt__10CmdSubMenu | `0x0047ad00` |
| `CmdSubTitle` | MenuScene | 0x1c8 | 6 | +0x58 MenuWindow, +0x110 MenuTexture, +0x150 SendOnLocal, +0x180 FontDraw | +8 __vt__11CmdSubTitle | `0x00478050` |
| `CmdSword` | CmdPrivateScene | 0x84 | 8 |  | +8 __vt__8CmdSword | `0x00456f30` |
| `CmdSwordGoods` | CmdWindow | 0xf8 | 6 | +0xb4 FontDraw | +8 __vt__13CmdSwordGoods | `0x00457790` |
| `CmdTarot` | CmdPrivateScene | 0x318 | 8 | +0x5c CmdTarotGoods, +0x188 CmdTarotImage | +8 __vt__8CmdTarot | `0x00455720` |
| `CmdTarotGoods` | CmdWindow | ? | 6 | +0xb4 SendOnLocal, +0xe4 FontDraw | +8 __vt__13CmdTarotGoods | `0x00455ce0` |
| `CmdTarotImage` | CmdWindow | ? | 6 | +0xb8 MenuTexture, +0xf8 SendOnLocal, +0x128 MenuSprite | +8 __vt__13CmdTarotImage | `0x00456390` |
| `CmdTechnique` | CmdPrivateScene | 0x8c | 10 |  | +8 __vt__12CmdTechnique | `0x00453540` |
| `CmdTechniqueGoods` | CmdWindow | 0xf8 | 7 | +0xb4 FontDraw | +8 __vt__17CmdTechniqueGoods | `0x004540d0` |
| `CmdTitleLog` | MenuScene | ? | 6 | +0x58 MenuWindow, +0x190 SendOnLocal, +0x1c0 MenuSprite, +0x220 FontDraw, +0x260 MenuText | +8 __vt__11CmdTitleLog | `0x00442470` |
| `CmdTop` | MenuScene | 0x90 | 15 |  | +8 __vt__6CmdTop | `0x00438790` |
| `CmdTopMenu` | CmdWindow | 0x5f4 | 6 | +0xb4 FontDraw, +0x574 MenuText | +8 __vt__10CmdTopMenu | `0x00450e10` |
| `CmdTopMenuData` | CmdWindow | 0x1f4 | 5 | +0xb4 FontDraw | +8 __vt__14CmdTopMenuData | `0x0048bd70` |
| `CmdTopPC` | CmdWindow | 0x74a0 | 9 | +0xb8 SendOnLocal, +0xe8 FontDraw, +0x72b0 MenuTexture, +0x72f0 SendOnLocal | +8 __vt__8CmdTopPC | `0x00451bc0` |
| `CmdTopPCParameter` | MenuGroup | ? | 2 | +0x50 MenuTexture, +0x90 SendOnLocal, +0xc0 MenuSprite, +0x120 MenuText, +0x1a0 Menu, +0x250 Menu, +0x300 Menu, +0x3b0 Menu, +0x460 Menu, +0x510 Menu, +0x5c0 MenuSprite, +0x620 MenuBar, +0x688 Menu, +0x738 Menu, +0x7e8 MenuSprite, +0x848 MenuBar, +0x8b0 Menu, +0x960 Menu, +0xa10 MenuSprite, +0xa70 MenuBar |  | `0x00451fa0` |
| `CmdTopPlayInfo` | CmdWindow | 0x348 | 6 | +0xb8 MenuTexture, +0xf8 SendOnLocal, +0x128 MenuSprite, +0x188 Menu, +0x238 MenuSprite, +0x298 Menu | +8 __vt__14CmdTopPlayInfo | `0x00451460` |
| `CmdWhiteMagic` | CmdPCScene | 0x360 | 8 | +0x88 CmdTechniqueGoods, +0x180 CmdSubTitle | +8 __vt__13CmdWhiteMagic | `0x00496330` |
| `CmdWindow` | MenuWindow | ? | 7 |  | +8 __vt__9CmdWindow | `0x0044f2d0` |
| `CmdWolfBout` | CmdPrivateScene | 0x90 | 18 |  | +8 __vt__11CmdWolfBout | `0x00483620` |
| `CmdWolfBoutProfile` | CmdWindow | 0x1f4 | 6 | +0xb4 FontDraw, +0xf4 MenuText, +0x174 MenuText | +8 __vt__18CmdWolfBoutProfile | `0x00485b20` |
| `CmdWolfBoutStamp` | CmdWindow | 0x280 | 6 | +0xb8 MenuTexture, +0xf8 SendOnLocal, +0x128 MenuSprite, +0x188 MenuTexture, +0x1c8 SendOnLocal, +0x1fc ScrollMark | +8 __vt__16CmdWolfBoutStamp | `0x00485250` |
| `DelayDeleteObject` | CList | ? | 2 |  | +8 __vt__17DelayDeleteObject | `0x004c07d0` |
| `DelayLight` | AnimLight | 0x60 | 6 | +0x40 FVector, +0x50 FVector | +0x14 __vt__10DelayLight | `0x004326c0` |
| `FVector` | - | ? | 16 |  |  | `0x00430c50` |
| `FaceImage` | CPolObj | 0x1c | 11 |  | +0x14 __vt__9FaceImage | `0x004a0440` |
| `FaceImageData` | - | 0x184 | 2 | +0x18 MenuWindow, +0xcc SendOnLocal, +0xfc MenuPolygon | +8 __vt__17DelayDeleteObject, +8 __vt__13FaceImageData | `0x004a0250` |
| `FieldMessage` | CPolObj | 0x1c | 22 |  | +0x14 __vt__12FieldMessage | `0x004a0d80` |
| `FieldMessageData` | - | 0x380 | 2 | +0x10 MenuWindow, +0xc4 FontDraw, +0x104 MenuMessage, +0x19c KeyWait, +0x278 Cursor | +8 __vt__17DelayDeleteObject, +8 __vt__16FieldMessageData | `0x004a0bb0` |
| `FldSpline` | - | ? | 7 |  |  | `0x004bc040` |
| `IVector` | - | ? | 1 |  |  | `0x004d04d0` |
| `Matrix` | - | ? | 12 |  |  | `0x00432660` |
| `MenuElement` | MenuPlace | ? | 9 | +0x1c0 SendOnLocal, +0x1f0 SendOnLocal, +0x220 SendOnLocal, +0x250 MenuSprite, +0x2b0 MenuPolygon, +0x334 MenuSprite | +8 __vt__11MenuElement | `0x00444f80` |
| `MenuModelAura` | MenuModelManeger | 0x1bc | 9 |  | +0x14 __vt__13MenuModelAura | `0x004999f0` |
| `MenuModelAuraPacket` | VI | ? | 6 |  | +16 __vt__19MenuModelAuraPacket | `0x00499240` |
| `MenuModelAuraRegister` | VI | ? | 3 |  | +16 __vt__21MenuModelAuraRegister | `0x00498fe0` |
| `SavePoint` | CPolObj | 0xc0 | 14 | +0x30 SvpLight, +0xb0 FVector | +0x14 __vt__9SavePoint | `0x00430b80` |
| `SvpLight` | AnimLight | ? | 5 |  |  | `0x00432210` |
| `WarpPoint` | CPolObj | 0xe0 | 18 |  |  | `0x00432a30` |
| `_AutoMoveInfo` | - | ? | 3 | +0x10 FVector |  | `0x004c07a0` |
| `_NaviWork` | FVector | ? | 1 | +0x10 FVector, +0x20 FVector, +0x30 FVector |  | `0x004cf2e0` |
| `_QWD` | FVector | ? | 2 |  |  | `0x004cefb0` |
| `_rgba32` | - | ? | 4 |  |  | `0x0049a360` |
| `bookScrollMark` | CPolObj | 0x30 | 7 |  | +0x14 __vt__14bookScrollMark | `0x004f1240` |
| `dRoll` | CPolObj | 0x5c | 6 |  | +0x20 __vt__17DelayDeleteObject, +0x14 __vt__5dRoll | `0x004f18c0` |
| `floatDemon` | CPolObj | 0x60 | 10 |  | +0x14 __vt__10floatDemon | `0x005005e0` |
| `pageScrollMark` | CPolObj | 0x34 | 7 |  | +0x14 __vt__14pageScrollMark | `0x00500f20` |
| `shop` | CPolObj | 0x134 | 39 | +0x40 Font, +0x44 Font | +0x20 __vt__17DelayDeleteObject, +0x14 __vt__4shop | `0x004dee30` |
| `shopCapture` | VI | 0x280 | 11 |  |  | `0x004e8fc0` |
| `shopCash` | - | 0x18 | 8 |  |  | `0x004e8490` |
| `shopScrollMark` | CPolObj | 0x2c | 6 |  | +0x14 __vt__14shopScrollMark | `0x004e89a0` |
| `solomon` | CPolObj | 0xbd0 | 43 |  |  | `0x004f2180` |
| `solomonArea` | CPolObj | 0x80 | 5 | +0x18 prim | +0x14 __vt__11solomonArea | `0x00503110` |
| `solomonCursor` | CPolObj | 0x5c | 10 |  | +0x14 __vt__13solomonCursor | `0x00501720` |
| `solomonEffect` | CPolObj | 0x58 | 12 |  | +0x20 __vt__17DelayDeleteObject, +0x14 __vt__13solomonEffect | `0x004fea20` |
| `solomonSlot` | CPolObj | 0x6c | 11 |  | +0x14 __vt__11solomonSlot | `0x00502220` |
| `solomonThm` | CPolObj | 0x98 | 22 |  | +0x14 __vt__10solomonThm | `0x00503da0` |
| `solomonTutorial` | CPolObj | 0x48 | 5 |  | +0x14 __vt__15solomonTutorial | `0x004ffa00` |
| `tagPutiVertex4` | _QWD | ? | 1 | +0x10 _QWD, +0x20 _QWD, +0x30 _QWD |  | `0x004cf030` |
| `tailor` | CPolObj | 0x170 | 27 |  |  | `0x004eb090` |
| `worldMap` | CPolObj | 0x34 | 35 | +0x28 Font | +0x20 __vt__17DelayDeleteObject, +0x14 __vt__8worldMap | `0x00506ce0` |
| `worldMapFade` | CPolObj | ? | 7 |  | +0x14 __vt__12worldMapFade | `0x0050b0c0` |
| `worldMapLight` | CPolObj | 0x94 | 9 |  | +0x14 __vt__13worldMapLight | `0x0050be50` |
| `worldMapPoint` | - | 0x80 | 4 |  |  | `0x0050cc90` |
| `worldMapThm` | - | 0x18 | 8 |  |  | `0x0050b810` |

## Cmd* (in-game menu) hierarchy

Roots: `Menu` (section F toolkit) → `CmdMenu` (0x17f8 bytes, the whole in-game menu object, owns every page as an embedded `MenuScene` subclass); pages derive from `MenuScene`; item lists `Cmd*Goods` derive from `CmdGoods`; windows from `CmdWindow` → `MenuWindow`.

* **-** ← CmdPC, CmdParty
* **CmdBackGround** ← CmdBackGroundCapture
* **CmdMenu** ← CmdMenuTutorial
* **CmdPCScene** ← CmdComboKey, CmdCrest, CmdEquipment, CmdMagic, CmdPrivate, CmdRingCustom, CmdWhiteMagic
* **CmdPrivateScene** ← CmdAroma, CmdClothes, CmdFriendship, CmdFusion, CmdPhotograph, CmdProfile, CmdStatus, CmdSword, CmdTarot, CmdTechnique, CmdWolfBout
* **CmdSubTitle** ← CmdLibraryTitle
* **CmdWindow** ← CmdAromaBaseOil, CmdAromaBlend, CmdClothesSlot, CmdComboKeyCharacter, CmdComboKeyCommand, CmdComboKeyGoods, CmdComboKeySlot, CmdCrestDetail, CmdCrestMagic, CmdCrestPCInfo, CmdEquipmentGoods, CmdEquipmentSlot, CmdEquipmentStatus, CmdFence, CmdFormationMember, CmdFormationTeam, CmdFusionCharge, CmdFusionLevelup, CmdFusionList, CmdFusionParameter, CmdFusionSkillList, CmdFusionStatus, CmdGoodsCrest, CmdGraveyardMenu, CmdHelpClause, CmdHelpExplain, CmdHelpMenu, CmdItemGoods, CmdItemMessage, CmdKeyCustomMenu, CmdKeyCustomPad, CmdLibraryDetail, CmdLibraryInfo, CmdLibraryList, CmdMagicGoods, CmdNoteMessage, CmdPhotographGoods, CmdPrivateMenu, CmdPropertyGoods, CmdRingCustomAutoRing, CmdRingCustomCount, CmdRingCustomFinalGoods, CmdRingCustomFinalSlot, CmdRingCustomGoods, CmdRingCustomHitArea, CmdRingCustomInfo, CmdScoreData, CmdScoreRank, CmdScoreRankFrame, CmdScoreTitle, CmdSwordGoods, CmdTarotGoods, CmdTarotImage, CmdTechniqueGoods, CmdTopMenu, CmdTopMenuData, CmdTopPC, CmdTopPlayInfo, CmdWolfBoutProfile, CmdWolfBoutStamp
* **Menu** ← CmdMenu
* **MenuGroup** ← CmdCrestDetailData, CmdFormationParameter, CmdFormationTeamData, CmdGoods, CmdGoodsComboKey, CmdGoodsCrestData, CmdGoodsFusion, CmdGoodsIcon, CmdGoodsList, CmdGoodsPad, CmdGoodsPadMenu, CmdGoodsScore, CmdGoodsScoreRank, CmdGoodsSubTitle, CmdGoodsSword, CmdGoodsTarot, CmdPropertySlot, CmdSTAllParameter, CmdTopPCParameter
* **MenuScene** ← CmdBackGround, CmdButtonReport, CmdComboMagic, CmdCommon, CmdElement, CmdExplain, CmdFormation, CmdGraveyard, CmdHelp, CmdItem, CmdKeyCustom, CmdLibrary, CmdNote, CmdOption, CmdPCInfo, CmdPCScene, CmdPrivateScene, CmdPropertyList, CmdRingMessage, CmdScore, CmdSelectTarget, CmdSort, CmdSubMenu, CmdSubTitle, CmdTitleLog, CmdTop
* **MenuSprite** ← CmdGoodsButton, CmdGoodsOption
* **MenuText** ← CmdGoodsKeyCustom, CmdHelpMenuData, CmdParameter
* **MenuWindow** ← CmdWindow
