/* Raw Ghidra decompilation (SH2US_BATTLE.BIN): FUN_005ad3b0 = BtlCamera attack camera (Polling case 0x13). */

void FUN_005ad3b0(undefined8 param_1)

{
  undefined1 auVar1 [12];
  undefined1 auVar2 [12];
  undefined1 auVar3 [16];
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  byte *pbVar8;
  long lVar9;
  undefined8 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined1 (*pauVar13) [16];
  int iVar14;
  int iVar15;
  int iVar16;
  float fVar17;
  float fVar18;
  undefined1 in_vf0 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auStack_1590 [16];
  undefined1 auStack_1580 [8];
  undefined4 uStack_1578;
  undefined4 uStack_1574;
  undefined1 auStack_1570 [16];
  undefined1 auStack_1560 [8];
  undefined4 uStack_1558;
  undefined4 uStack_1554;
  undefined1 auStack_1550 [16];
  undefined1 auStack_1540 [8];
  undefined4 uStack_1538;
  undefined4 uStack_1534;
  undefined1 auStack_1530 [16];
  undefined1 auStack_1520 [8];
  undefined4 uStack_1518;
  undefined4 uStack_1514;
  undefined1 auStack_1510 [16];
  undefined1 auStack_1500 [16];
  undefined1 auStack_14f0 [16];
  undefined1 auStack_14e0 [8];
  undefined4 uStack_14d8;
  undefined4 uStack_14d4;
  undefined1 auStack_14d0 [16];
  undefined1 auStack_14c0 [16];
  undefined1 auStack_14b0 [16];
  undefined1 auStack_14a0 [8];
  undefined4 uStack_1498;
  undefined4 uStack_1494;
  undefined1 auStack_1490 [16];
  undefined1 auStack_1480 [16];
  undefined1 auStack_1470 [16];
  undefined1 auStack_1460 [16];
  undefined1 auStack_1450 [16];
  undefined1 auStack_1440 [16];
  undefined1 auStack_1430 [16];
  undefined1 auStack_1420 [16];
  undefined1 auStack_1410 [16];
  undefined1 auStack_1400 [8];
  float fStack_13f8;
  undefined4 uStack_13f4;
  undefined1 auStack_13f0 [16];
  undefined1 auStack_13e0 [8];
  undefined4 uStack_13d8;
  undefined4 uStack_13d4;
  undefined1 auStack_13d0 [16];
  undefined1 auStack_13c0 [8];
  undefined4 uStack_13b8;
  undefined4 uStack_13b4;
  undefined1 auStack_13b0 [16];
  undefined1 auStack_13a0 [8];
  undefined4 uStack_1398;
  undefined4 uStack_1394;
  undefined1 auStack_1390 [16];
  undefined1 auStack_1380 [12];
  undefined4 uStack_1374;
  undefined1 auStack_1370 [16];
  undefined1 auStack_1360 [8];
  undefined4 uStack_1358;
  undefined4 uStack_1354;
  undefined1 auStack_1350 [16];
  undefined1 auStack_1340 [12];
  undefined4 uStack_1334;
  undefined1 auStack_1330 [16];
  undefined1 auStack_1320 [8];
  undefined4 uStack_1318;
  undefined4 uStack_1314;
  undefined1 auStack_1310 [16];
  undefined8 uStack_1300;
  undefined4 uStack_12f4;
  undefined1 auStack_12f0 [16];
  ulong uStack_12e0;
  undefined4 uStack_12d8;
  undefined4 uStack_12d4;
  undefined1 auStack_12d0 [16];
  undefined8 uStack_12c0;
  undefined4 uStack_12b4;
  undefined1 auStack_12b0 [16];
  undefined1 auStack_12a0 [16];
  undefined1 auStack_1290 [8];
  undefined4 uStack_1288;
  undefined4 uStack_1284;
  undefined1 auStack_1280 [16];
  undefined8 uStack_1270;
  undefined4 uStack_1268;
  undefined4 uStack_1264;
  undefined1 auStack_1260 [16];
  undefined8 uStack_1250;
  undefined4 uStack_1248;
  undefined4 uStack_1244;
  undefined1 auStack_1240 [16];
  undefined1 auStack_1230 [16];
  undefined1 auStack_1220 [16];
  undefined8 uStack_1210;
  undefined4 uStack_1208;
  undefined4 uStack_1204;
  undefined8 uStack_1200;
  undefined4 uStack_11f8;
  undefined4 uStack_11f4;
  undefined1 auStack_11f0 [16];
  undefined1 auStack_11e0 [16];
  undefined1 auStack_11d0 [16];
  undefined8 uStack_11c0;
  undefined4 uStack_11b8;
  undefined4 uStack_11b4;
  undefined1 auStack_11b0 [16];
  undefined1 auStack_11a0 [16];
  undefined1 auStack_1190 [16];
  undefined1 auStack_1180 [16];
  undefined1 auStack_1170 [16];
  undefined1 auStack_1160 [8];
  float fStack_1158;
  undefined4 uStack_1154;
  undefined1 auStack_1150 [16];
  undefined1 auStack_1140 [8];
  float fStack_1138;
  undefined4 uStack_1134;
  undefined1 auStack_1130 [16];
  undefined1 auStack_1120 [4];
  float fStack_111c;
  undefined1 auStack_1110 [16];
  undefined1 auStack_1100 [16];
  undefined8 uStack_10f0;
  undefined4 uStack_10e8;
  undefined4 uStack_10e4;
  undefined1 auStack_10e0 [16];
  undefined1 auStack_10d0 [8];
  undefined4 uStack_10c8;
  undefined4 uStack_10c4;
  undefined1 auStack_10c0 [16];
  undefined1 auStack_10b0 [8];
  undefined4 uStack_10a8;
  undefined4 uStack_10a4;
  undefined1 auStack_10a0 [16];
  undefined1 auStack_1090 [8];
  undefined4 uStack_1088;
  undefined4 uStack_1084;
  undefined1 auStack_1080 [16];
  undefined1 auStack_1070 [8];
  undefined4 uStack_1068;
  undefined4 uStack_1064;
  undefined1 auStack_1060 [16];
  undefined1 auStack_1050 [16];
  undefined1 auStack_1040 [16];
  undefined1 auStack_1030 [8];
  undefined4 uStack_1028;
  undefined4 uStack_1024;
  undefined1 auStack_1020 [16];
  undefined1 auStack_1010 [16];
  undefined1 auStack_1000 [16];
  undefined1 auStack_ff0 [8];
  undefined4 uStack_fe8;
  undefined4 uStack_fe4;
  undefined1 auStack_fe0 [16];
  undefined1 auStack_fd0 [16];
  undefined1 auStack_fc0 [16];
  undefined1 auStack_fb0 [16];
  undefined1 auStack_fa0 [16];
  undefined1 auStack_f90 [16];
  undefined1 auStack_f80 [16];
  undefined1 auStack_f70 [16];
  undefined1 auStack_f60 [16];
  undefined1 auStack_f50 [16];
  undefined1 auStack_f40 [16];
  undefined1 auStack_f30 [8];
  undefined4 uStack_f28;
  undefined4 uStack_f24;
  undefined1 auStack_f20 [16];
  undefined1 auStack_f10 [16];
  undefined1 auStack_f00 [16];
  undefined8 uStack_ef0;
  undefined4 uStack_ee8;
  undefined4 uStack_ee4;
  undefined1 auStack_ee0 [16];
  undefined1 auStack_ed0 [16];
  undefined8 uStack_ec0;
  undefined4 uStack_eb8;
  undefined4 uStack_eb4;
  undefined1 auStack_eb0 [16];
  undefined1 auStack_ea0 [16];
  undefined1 auStack_e90 [16];
  undefined1 auStack_e80 [8];
  undefined4 uStack_e78;
  undefined4 uStack_e74;
  undefined1 auStack_e70 [16];
  undefined1 auStack_e60 [8];
  float fStack_e58;
  undefined4 uStack_e54;
  undefined1 auStack_e50 [16];
  undefined1 auStack_e40 [16];
  undefined1 auStack_e30 [16];
  undefined1 auStack_e20 [8];
  undefined4 uStack_e18;
  undefined4 uStack_e14;
  undefined1 auStack_e10 [16];
  undefined1 auStack_e00 [16];
  undefined1 auStack_df0 [16];
  undefined1 auStack_de0 [8];
  undefined4 uStack_dd8;
  undefined4 uStack_dd4;
  undefined1 auStack_dd0 [16];
  undefined1 auStack_dc0 [16];
  undefined1 auStack_db0 [16];
  undefined1 auStack_da0 [8];
  undefined4 uStack_d98;
  undefined4 uStack_d94;
  undefined1 auStack_d90 [16];
  undefined1 auStack_d80 [16];
  undefined1 auStack_d70 [16];
  undefined1 auStack_d60 [8];
  undefined4 uStack_d58;
  undefined4 uStack_d54;
  undefined1 auStack_d50 [16];
  undefined1 auStack_d40 [16];
  undefined1 auStack_d30 [16];
  undefined1 auStack_d20 [8];
  undefined4 uStack_d18;
  undefined4 uStack_d14;
  undefined1 auStack_d10 [16];
  undefined1 auStack_d00 [16];
  undefined1 auStack_cf0 [16];
  undefined1 auStack_ce0 [8];
  undefined4 uStack_cd8;
  undefined4 uStack_cd4;
  undefined1 auStack_cd0 [16];
  undefined1 auStack_cc0 [16];
  undefined1 auStack_cb0 [16];
  undefined1 auStack_ca0 [16];
  undefined1 auStack_c90 [16];
  undefined1 auStack_c80 [16];
  undefined1 auStack_c70 [16];
  undefined1 auStack_c60 [16];
  undefined1 auStack_c50 [8];
  float fStack_c48;
  float fStack_c44;
  undefined1 auStack_c40 [16];
  undefined8 uStack_c30;
  undefined4 uStack_c28;
  undefined4 uStack_c24;
  undefined8 uStack_c20;
  undefined4 uStack_c18;
  undefined4 uStack_c14;
  undefined1 auStack_c10 [16];
  undefined1 auStack_c00 [16];
  undefined1 auStack_bf0 [16];
  undefined1 auStack_be0 [16];
  undefined8 uStack_bd0;
  undefined4 uStack_bc8;
  undefined4 uStack_bc4;
  undefined1 auStack_bc0 [16];
  undefined8 uStack_bb0;
  undefined4 uStack_ba8;
  undefined4 uStack_ba4;
  undefined1 auStack_ba0 [16];
  undefined1 auStack_b90 [16];
  undefined1 auStack_b80 [16];
  undefined8 uStack_b70;
  undefined4 uStack_b68;
  undefined4 uStack_b64;
  undefined1 auStack_b60 [16];
  undefined1 auStack_b50 [8];
  undefined4 uStack_b48;
  undefined4 uStack_b44;
  undefined1 auStack_b40 [16];
  undefined8 uStack_b30;
  undefined4 uStack_b28;
  undefined4 uStack_b24;
  undefined1 auStack_b20 [16];
  undefined1 auStack_b10 [16];
  undefined1 auStack_b00 [16];
  undefined8 uStack_af0;
  undefined4 uStack_ae8;
  undefined4 uStack_ae4;
  undefined1 auStack_ae0 [16];
  undefined1 auStack_ad0 [16];
  undefined8 uStack_ac0;
  undefined4 uStack_ab8;
  undefined4 uStack_ab4;
  undefined1 auStack_ab0 [16];
  undefined1 auStack_aa0 [16];
  undefined1 auStack_a90 [16];
  undefined1 auStack_a80 [8];
  undefined4 uStack_a78;
  undefined4 uStack_a74;
  undefined8 uStack_a70;
  undefined4 uStack_a68;
  undefined4 uStack_a64;
  undefined1 auStack_a60 [8];
  undefined4 uStack_a58;
  undefined4 uStack_a54;
  undefined1 auStack_a50 [8];
  undefined4 uStack_a48;
  undefined4 uStack_a44;
  undefined1 auStack_a40 [8];
  float fStack_a38;
  undefined4 uStack_a34;
  undefined1 auStack_a30 [8];
  float fStack_a28;
  undefined4 uStack_a24;
  undefined1 auStack_a20 [8];
  float fStack_a18;
  undefined4 uStack_a14;
  undefined8 uStack_a10;
  undefined4 uStack_a08;
  undefined4 uStack_a04;
  undefined8 uStack_a00;
  undefined4 uStack_9f8;
  undefined4 uStack_9f4;
  undefined1 auStack_9f0 [8];
  undefined4 uStack_9e8;
  undefined4 uStack_9e4;
  undefined1 auStack_9e0 [8];
  float fStack_9d8;
  undefined4 uStack_9d4;
  undefined1 auStack_9d0 [8];
  float fStack_9c8;
  undefined4 uStack_9c4;
  undefined1 auStack_9c0 [16];
  undefined1 auStack_9b0 [16];
  undefined1 auStack_9a0 [16];
  undefined1 auStack_990 [8];
  undefined4 uStack_988;
  undefined4 uStack_984;
  undefined1 auStack_980 [16];
  undefined1 auStack_970 [8];
  undefined4 uStack_968;
  undefined4 uStack_964;
  undefined1 auStack_960 [16];
  undefined1 auStack_950 [16];
  undefined1 auStack_940 [8];
  undefined4 uStack_938;
  undefined4 uStack_934;
  undefined1 auStack_930 [16];
  undefined1 auStack_920 [16];
  undefined1 auStack_910 [8];
  undefined4 uStack_908;
  undefined4 uStack_904;
  undefined1 auStack_900 [16];
  undefined1 auStack_8f0 [16];
  undefined1 auStack_8e0 [8];
  undefined4 uStack_8d8;
  undefined4 uStack_8d4;
  undefined1 auStack_8d0 [16];
  undefined1 auStack_8c0 [16];
  undefined1 auStack_8b0 [8];
  undefined4 uStack_8a8;
  undefined4 uStack_8a4;
  undefined1 auStack_8a0 [16];
  undefined1 auStack_890 [16];
  undefined1 auStack_880 [8];
  undefined4 uStack_878;
  undefined4 uStack_874;
  undefined1 auStack_870 [16];
  undefined1 auStack_860 [16];
  undefined1 auStack_850 [8];
  undefined4 uStack_848;
  undefined4 uStack_844;
  undefined1 auStack_840 [16];
  undefined1 auStack_830 [16];
  undefined1 auStack_820 [16];
  undefined1 auStack_810 [16];
  undefined1 auStack_800 [16];
  undefined1 auStack_7f0 [16];
  undefined1 auStack_7e0 [8];
  undefined4 uStack_7d8;
  undefined4 uStack_7d4;
  undefined1 auStack_7d0 [8];
  undefined4 uStack_7c8;
  undefined4 uStack_7c4;
  undefined1 auStack_7c0 [16];
  undefined1 auStack_7b0 [8];
  float fStack_7a8;
  undefined4 uStack_7a4;
  undefined1 auStack_7a0 [16];
  undefined1 auStack_790 [16];
  undefined1 auStack_780 [16];
  undefined1 auStack_770 [8];
  undefined4 uStack_768;
  undefined4 uStack_764;
  undefined1 auStack_760 [16];
  undefined1 auStack_750 [16];
  undefined1 auStack_740 [16];
  undefined1 auStack_730 [8];
  undefined4 uStack_728;
  undefined4 uStack_724;
  undefined1 auStack_720 [16];
  undefined1 auStack_710 [16];
  undefined1 auStack_700 [16];
  undefined1 auStack_6f0 [8];
  undefined4 uStack_6e8;
  undefined4 uStack_6e4;
  undefined1 auStack_6e0 [16];
  undefined1 auStack_6d0 [16];
  undefined1 auStack_6c0 [16];
  undefined1 auStack_6b0 [8];
  undefined4 uStack_6a8;
  undefined4 uStack_6a4;
  undefined1 auStack_6a0 [16];
  undefined1 auStack_690 [16];
  undefined1 auStack_680 [16];
  undefined1 auStack_670 [8];
  undefined4 uStack_668;
  undefined4 uStack_664;
  undefined1 auStack_660 [16];
  undefined1 auStack_650 [16];
  undefined1 auStack_640 [16];
  undefined1 auStack_630 [8];
  undefined4 uStack_628;
  undefined4 uStack_624;
  undefined1 auStack_620 [16];
  undefined1 auStack_610 [16];
  undefined1 auStack_600 [16];
  undefined1 auStack_5f0 [16];
  undefined1 auStack_5e0 [16];
  undefined1 auStack_5d0 [16];
  undefined1 auStack_5c0 [16];
  undefined1 auStack_5b0 [16];
  undefined1 auStack_5a0 [8];
  float fStack_598;
  float fStack_594;
  undefined1 auStack_590 [16];
  undefined8 uStack_580;
  undefined4 uStack_578;
  undefined4 uStack_574;
  undefined1 auStack_570 [16];
  undefined1 auStack_560 [16];
  undefined8 uStack_550;
  undefined4 uStack_548;
  undefined4 uStack_544;
  undefined1 auStack_540 [16];
  undefined1 auStack_530 [16];
  float afStack_520 [2];
  undefined4 uStack_518;
  undefined4 uStack_514;
  undefined1 auStack_510 [4];
  float fStack_50c;
  float fStack_508;
  undefined4 uStack_504;
  undefined1 auStack_500 [16];
  undefined8 uStack_4f0;
  undefined4 uStack_4e8;
  undefined4 uStack_4e4;
  undefined1 auStack_4e0 [4];
  undefined4 uStack_4dc;
  undefined4 uStack_4d8;
  undefined4 uStack_4d4;
  undefined1 auStack_4d0 [16];
  undefined8 uStack_4c0;
  undefined4 uStack_4b8;
  undefined4 uStack_4b4;
  undefined1 auStack_4b0 [16];
  undefined8 uStack_4a0;
  undefined4 uStack_498;
  undefined4 uStack_494;
  undefined1 auStack_490 [4];
  undefined4 uStack_48c;
  undefined4 uStack_488;
  undefined4 uStack_484;
  undefined1 auStack_480 [16];
  undefined8 uStack_470;
  undefined4 uStack_468;
  undefined4 uStack_464;
  undefined1 auStack_460 [4];
  undefined4 uStack_45c;
  undefined4 uStack_458;
  undefined4 uStack_454;
  undefined1 auStack_450 [16];
  undefined1 auStack_440 [8];
  undefined4 uStack_438;
  undefined4 uStack_434;
  undefined1 auStack_430 [16];
  undefined8 uStack_420;
  undefined4 uStack_418;
  undefined4 uStack_414;
  undefined1 auStack_410 [16];
  undefined1 auStack_400 [16];
  undefined1 auStack_3f0 [16];
  undefined8 uStack_3e0;
  undefined4 uStack_3d8;
  undefined4 uStack_3d4;
  undefined1 auStack_3d0 [16];
  undefined1 auStack_3c0 [16];
  undefined8 uStack_3b0;
  undefined4 uStack_3a8;
  undefined4 uStack_3a4;
  undefined1 auStack_3a0 [16];
  undefined1 auStack_390 [16];
  undefined8 uStack_380;
  undefined4 uStack_378;
  undefined4 uStack_374;
  undefined1 auStack_370 [16];
  undefined8 uStack_360;
  undefined4 uStack_358;
  undefined4 uStack_354;
  undefined1 auStack_350 [16];
  undefined1 auStack_340 [8];
  float fStack_338;
  undefined4 uStack_334;
  undefined1 auStack_330 [8];
  float fStack_328;
  undefined4 uStack_324;
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [4];
  undefined4 uStack_30c;
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [16];
  undefined1 auStack_2e0 [16];
  undefined8 uStack_2d0;
  undefined4 uStack_2c8;
  undefined4 uStack_2c4;
  undefined1 auStack_2c0 [16];
  undefined1 auStack_2b0 [16];
  undefined8 uStack_2a0;
  undefined4 uStack_298;
  undefined4 uStack_294;
  undefined1 auStack_290 [16];
  undefined8 uStack_280;
  undefined4 uStack_278;
  undefined4 uStack_274;
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined8 uStack_230;
  undefined4 uStack_228;
  undefined4 uStack_224;
  undefined1 auStack_220 [8];
  undefined4 uStack_218;
  undefined4 uStack_214;
  undefined1 auStack_210 [4];
  undefined4 uStack_20c;
  undefined4 uStack_208;
  undefined4 uStack_204;
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [16];
  undefined1 auStack_1d0 [16];
  float fStack_1c0;
  float fStack_1bc;
  float fStack_1b8;
  undefined4 uStack_1b4;
  float fStack_1b0;
  float fStack_1ac;
  float fStack_1a8;
  undefined4 uStack_1a4;
  undefined1 auStack_1a0 [8];
  float fStack_198;
  undefined4 uStack_194;
  float fStack_190;
  float fStack_18c;
  float fStack_188;
  float fStack_184;
  float fStack_180;
  float fStack_17c;
  float fStack_178;
  undefined4 uStack_174;
  float fStack_170;
  float fStack_16c;
  float fStack_168;
  undefined4 uStack_164;
  float fStack_160;
  float fStack_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  undefined1 auStack_120 [4];
  undefined1 auStack_11c [4];
  undefined8 uStack_118;
  undefined1 auStack_110 [4];
  undefined1 auStack_10c [4];
  undefined8 uStack_108;
  float fStack_100;
  float fStack_fc;
  float fStack_f8;
  undefined4 uStack_f4;
  float fStack_f0;
  float fStack_ec;
  float fStack_e8;
  undefined4 uStack_e4;
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  undefined4 uStack_d4;
  float afStack_d0 [12];
  float afStack_a0 [32];
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  
  auStack_1a0._4_4_ = in_zero_hi;
  auStack_1a0._0_4_ = in_zero_lo;
  fStack_198 = in_zero_udw;
  uStack_194 = in_register_0000000c;
  fStack_1c0 = in_zero_lo;
  fStack_1bc = in_zero_hi;
  fStack_1b8 = in_zero_udw;
  uStack_1b4 = in_register_0000000c;
  fStack_1b0 = in_zero_lo;
  fStack_1ac = in_zero_hi;
  fStack_1a8 = in_zero_udw;
  uStack_1a4 = in_register_0000000c;
  fStack_190 = in_zero_lo;
  fStack_18c = in_zero_hi;
  fStack_188 = in_zero_udw;
  fStack_184 = (float)in_register_0000000c;
  fStack_180 = in_zero_lo;
  fStack_17c = in_zero_hi;
  fStack_178 = in_zero_udw;
  uStack_174 = in_register_0000000c;
  fStack_170 = in_zero_lo;
  fStack_16c = in_zero_hi;
  fStack_168 = in_zero_udw;
  uStack_164 = in_register_0000000c;
  fStack_100 = in_zero_lo;
  fStack_fc = in_zero_hi;
  fStack_f8 = in_zero_udw;
  uStack_f4 = in_register_0000000c;
  fStack_f0 = in_zero_lo;
  fStack_ec = in_zero_hi;
  fStack_e8 = in_zero_udw;
  uStack_e4 = in_register_0000000c;
  fStack_e0 = in_zero_lo;
  fStack_dc = in_zero_hi;
  fStack_d8 = in_zero_udw;
  uStack_d4 = in_register_0000000c;
  FUN_00472e10(auStack_200);
  iVar15 = (int)param_1;
  iVar4 = iGpffff8610 + *(int *)(iVar15 + 0xd0) * 0x510;
  *(undefined4 *)(iVar15 + 0xd4) = *(undefined4 *)(iVar4 + 0xbc);
  if (((*(char *)(iGpffff8610 + 0x4850) != '\0') &&
      ((long)*(char *)(iGpffff8610 + 0x4852) == (long)*(int *)(iVar15 + 0xd4))) &&
     (*(char *)(iGpffff8610 + 0x4851) < '\n')) {
    *(int *)(iVar15 + 0xd4) = (int)*(char *)(iGpffff8610 + 0x4853);
  }
  if (((*(char *)(iGpffff8610 + 0x4858) != '\0') &&
      ((long)*(char *)(iGpffff8610 + 0x485a) == (long)*(int *)(iVar15 + 0xd4))) &&
     (*(char *)(iGpffff8610 + 0x4859) < '\n')) {
    *(int *)(iVar15 + 0xd4) = (int)*(char *)(iGpffff8610 + 0x485b);
  }
  iVar5 = iGpffff8610 + *(int *)(iVar15 + 0xd4) * 0x510;
  if (((*(char *)(iVar4 + 0xb8) == '\x0e') || (*(char *)(iVar4 + 0xb8) == '\x0f')) &&
     (*(char *)(iVar4 + 0xb9) < '\x04')) {
    uVar10 = *(undefined8 *)(iVar4 + 0x160);
    uVar11 = *(undefined4 *)(iVar4 + 0x168);
    uVar12 = *(undefined4 *)(iVar4 + 0x16c);
    *(int *)(iVar15 + 0x100) = (int)uVar10;
    *(int *)(iVar15 + 0x104) = (int)((ulong)uVar10 >> 0x20);
    *(undefined4 *)(iVar15 + 0x108) = uVar11;
    *(undefined4 *)(iVar15 + 0x10c) = uVar12;
  }
  _auStack_120 = *(undefined1 (*) [16])(iVar4 + 0x360);
  auVar19 = _vmr32(in_vf0);
  auVar20 = _vmr32(auVar19);
  auVar21 = _vmr32(auVar20);
  auStack_1d0 = _sqc2(in_vf0);
  auStack_1e0 = _sqc2(auVar19);
  auStack_1f0 = _sqc2(auVar20);
  auStack_200 = _sqc2(auVar21);
  uVar11 = func_0x00222e40(-*(float *)(iVar4 + 0x184));
  func_0x00202938(uVar11,auStack_200,auStack_200);
  func_0x00222df0(auStack_210,auStack_200,auStack_120);
  auVar1._4_8_ = uStack_118;
  auVar1._0_4_ = uStack_20c;
  _auStack_120 = auVar1._0_8_ << 0x20;
  uStack_118._0_4_ = (float)uStack_208;
  uStack_118._4_4_ = uStack_204;
  auVar19._12_4_ = 0;
  auVar19._0_12_ = _auStack_11c;
  _auStack_120 = auVar19 << 0x20;
  auVar19 = _vmr32(in_vf0);
  auVar20 = _vmr32(auVar19);
  auVar21 = _vmr32(auVar20);
  auStack_1d0 = _sqc2(in_vf0);
  auStack_1e0 = _sqc2(auVar19);
  auStack_1f0 = _sqc2(auVar20);
  auStack_200 = _sqc2(auVar21);
  uVar11 = func_0x00222e40(*(undefined4 *)(iVar4 + 0x184));
  func_0x00202938(uVar11,auStack_200,auStack_200);
  func_0x00222df0(auStack_220,auStack_200,auStack_120);
  *(int *)(iVar15 + 0x110) = auStack_220._0_4_;
  *(int *)(iVar15 + 0x114) = auStack_220._4_4_;
  *(undefined4 *)(iVar15 + 0x118) = uStack_218;
  *(undefined4 *)(iVar15 + 0x11c) = uStack_214;
  if (*(int *)(iVar15 + 0xd8) != 0) {
    if (((*(short *)(iVar15 + 0x1e) == 1) || (*(short *)(iVar15 + 0x1e) == 4)) ||
       (*(short *)(iVar15 + 0x1e) == 5)) {
      if (((*(byte *)(iVar4 + 0xb4) & 1) == 0) &&
         (((lVar9 = func_0x00233b40(*(int *)(iVar4 + 0x14c) + 0x514,0x6e5bc8), lVar9 == 0 ||
           (lVar9 = func_0x00233b40(*(int *)(iVar4 + 0x14c) + 0x514,0x6e5bd0), lVar9 == 0)) ||
          ((lVar9 = func_0x00233b40(*(int *)(iVar4 + 0x14c) + 0x514,0x6e5bd8), lVar9 == 0 ||
           (lVar9 = func_0x00233b40(*(int *)(iVar4 + 0x14c) + 0x514,0x6e5be0), lVar9 == 0)))))) {
        *(undefined2 *)(iVar15 + 0x1e) = 2;
        *(undefined4 *)(iVar15 + 0x84) = 0x44000000;
        if ((long)((ulong)*(byte *)(iVar4 + 0xb1) << 0x3e) < 0) {
          switch(*(undefined2 *)(iVar4 + 0xba)) {
          default:
            *(undefined4 *)(iVar15 + 0xf0) = 0x41333333;
            break;
          case 1:
          case 2:
            *(undefined4 *)(iVar15 + 0xf0) = 0x41a00000;
            break;
          case 4:
          case 5:
            *(undefined4 *)(iVar15 + 0xf0) = 0x41a00000;
            break;
          case 7:
          case 8:
            *(undefined4 *)(iVar15 + 0xf0) = 0x41800000;
            break;
          case 10:
          case 0xb:
            *(undefined4 *)(iVar15 + 0xf0) = 0x41800000;
            break;
          case 0xd:
          case 0xe:
            *(undefined4 *)(iVar15 + 0xf0) = 0x41800000;
            break;
          case 0x10:
          case 0x11:
            *(undefined4 *)(iVar15 + 0xf0) = 0x414ccccd;
            break;
          case 0x12:
          case 0x13:
            *(undefined4 *)(iVar15 + 0xf0) = 0x41966666;
            break;
          case 0x14:
            *(undefined4 *)(iVar15 + 0xf0) = 0x414ccccd;
            break;
          case 0x15:
            *(undefined4 *)(iVar15 + 0xf0) = 0x41666666;
            break;
          case 0x16:
            *(undefined4 *)(iVar15 + 0xf0) = 0x41333333;
          }
        }
        else {
          switch(*(undefined2 *)(iVar4 + 0x120)) {
          case 0:
            *(undefined4 *)(iVar15 + 0xf0) = 0x41333333;
            break;
          case 1:
            *(undefined4 *)(iVar15 + 0xf0) = 0x4139999a;
            break;
          case 2:
            *(undefined4 *)(iVar15 + 0xf0) = 0x412ccccd;
            break;
          case 3:
            *(undefined4 *)(iVar15 + 0xf0) = 0x412ccccd;
            break;
          case 4:
            *(undefined4 *)(iVar15 + 0xf0) = 0x412ccccd;
            break;
          case 5:
            *(undefined4 *)(iVar15 + 0xf0) = 0x412ccccd;
            break;
          case 6:
            *(undefined4 *)(iVar15 + 0xf0) = 0x4139999a;
            break;
          case 7:
            *(undefined4 *)(iVar15 + 0xf0) = 0x412ccccd;
            break;
          case 8:
            *(undefined4 *)(iVar15 + 0xf0) = 0x412ccccd;
            break;
          case 9:
            *(undefined4 *)(iVar15 + 0xf0) = 0x4139999a;
            break;
          case 10:
            *(undefined4 *)(iVar15 + 0xf0) = 0x41600000;
            break;
          case 0xb:
            *(undefined4 *)(iVar15 + 0xf0) = 0x4139999a;
            break;
          case 0xc:
            *(undefined4 *)(iVar15 + 0xf0) = 0x4139999a;
            break;
          case 0xd:
            *(undefined4 *)(iVar15 + 0xf0) = 0x4139999a;
          }
        }
        *(undefined4 *)(iVar15 + 0xf4) = 0;
        *(int *)(iVar15 + 0x140) = 3 << ((*(uint *)(iVar15 + 0xd0) & 0xf) << 1);
        *(byte *)(iVar15 + 0x18) = *(byte *)(iVar15 + 0x18) & 0x7f | 0x80;
        AllEffMdlDispOff__7CBattleFv(iGpffff8610);
        FUN_0058f340(*(undefined4 *)(iVar4 + 0x14c));
        fStack_20 = *(float *)(iVar4 + 0x184) + 20.0;
        auVar19 = _vmr32(in_vf0);
        auVar20 = _vmr32(auVar19);
        auVar21 = _vmr32(auVar20);
        auStack_1d0 = _sqc2(in_vf0);
        auStack_1e0 = _sqc2(auVar19);
        auStack_1f0 = _sqc2(auVar20);
        auStack_200 = _sqc2(auVar21);
        uVar11 = func_0x00222e40(0xbf800000);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(fStack_20);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        fVar17 = (float)func_0x00222fd0(iVar4 + 0x3b0);
        fStack_20 = *(float *)(iVar4 + 0x354) + fVar17 + 50.0;
        uVar10 = FUN_004baab0(0,0,-fStack_20,0x3f800000,auStack_240);
        func_0x00222df0(&uStack_230,auStack_200,uVar10);
        uStack_118._0_4_ = (float)uStack_228;
        _auStack_120 = uStack_230;
        uStack_118._4_4_ = uStack_224;
        __pl__7FVectorCFRC7FVector(auStack_250,iVar4 + 0x160,iVar4 + 0x3a0);
        auVar20 = _lqc2(auStack_250);
        auVar19 = _lqc2(_auStack_120);
        auVar19 = _vadd(auVar19,auVar20);
        _auStack_120 = _sqc2(auVar19);
        puVar6 = (undefined4 *)FUN_00472df0(auStack_270);
        *puVar6 = 0x3f000000;
        puVar6 = (undefined4 *)vy__7FVectorFv(auStack_270);
        *puVar6 = 0x3f000000;
        puVar6 = (undefined4 *)vz__7FVectorFv(auStack_270);
        *puVar6 = 0x3f000000;
        puVar6 = (undefined4 *)vw__7FVectorFv(auStack_270);
        *puVar6 = 0x3f800000;
        uVar10 = func_0x00222f00(auStack_260,auStack_120);
        uVar11 = func_0x002261a0(uVar10,auStack_270);
        *(undefined4 *)(iVar15 + 0x210) = uVar11;
        func_0x002280f0(0x41000000,*(undefined4 *)(iVar15 + 0x210));
        func_0x00228140(*(undefined4 *)(iVar15 + 0x210),0);
      }
    }
    else if (((*(short *)(iVar15 + 0x1e) == 2) &&
             (lVar9 = func_0x00233b40(*(int *)(iVar4 + 0x14c) + 0x514,0x6e5bc8), lVar9 != 0)) &&
            ((lVar9 = func_0x00233b40(*(int *)(iVar4 + 0x14c) + 0x514,0x6e5bd0), lVar9 != 0 &&
             ((lVar9 = func_0x00233b40(*(int *)(iVar4 + 0x14c) + 0x514,0x6e5bd8), lVar9 != 0 &&
              (lVar9 = func_0x00233b40(*(int *)(iVar4 + 0x14c) + 0x514,0x6e5be0), lVar9 != 0)))))) {
      *(undefined2 *)(iVar15 + 0x1e) = 1;
      *(undefined4 *)(iVar15 + 0xdc) = 0;
      *(undefined4 *)(iVar15 + 0x84) = 0x44000000;
      *(uint *)(iVar15 + 0x140) =
           *(uint *)(iVar15 + 0x140) | 3 << ((*(uint *)(iVar15 + 0xd4) & 0xf) << 1);
      *(byte *)(iVar15 + 0x18) = *(byte *)(iVar15 + 0x18) & 0x7f | 0x80;
      AllEffMdlDispOn__7CBattleFv(iGpffff8610);
      if (*(int *)(iVar15 + 0x210) != -1) {
        func_0x002282f0(*(undefined4 *)(iVar15 + 0x210));
        *(undefined4 *)(iVar15 + 0x210) = 0xffffffff;
      }
      iVar7 = func_0x003b9540(0x40,*(undefined4 *)(iVar4 + 0x568),0xffffffffffffffff);
      if ((*(byte *)(iVar7 + 2) & 7) != 0) {
        __pl__7FVectorCFRC7FVector(&uStack_280,iVar5 + 0x160,iVar5 + 0x3a0);
        uStack_118._0_4_ = (float)uStack_278;
        _auStack_120 = uStack_280;
        uStack_118._4_4_ = uStack_274;
        __pl__7FVectorCFRC7FVector(auStack_290,iVar4 + 0x160,iVar4 + 0x3a0);
        auVar20 = _lqc2(auStack_290);
        auVar19 = _lqc2(_auStack_120);
        auVar19 = _vsub(auVar19,auVar20);
        _auStack_120 = _sqc2(auVar19);
        fStack_20 = (float)func_0x00222fd0(auStack_120);
        fStack_1c = -((*(float *)(iVar5 + 0x164) + *(float *)(iVar5 + 0x3a4)) -
                     *(float *)(iVar5 + 0x3b4)) * 2.0 * 10.0;
        if (fStack_1c + *(float *)(iVar4 + 0x354) + *(float *)(iVar5 + 0x354) <= fStack_20) {
          *(undefined2 *)(iVar15 + 0x1e) = 4;
        }
        else {
          *(undefined2 *)(iVar15 + 0x1e) = 5;
        }
      }
    }
  }
  switch(*(undefined2 *)(iVar15 + 0x1e)) {
  case 0:
    *(undefined4 *)(iVar15 + 0xdc) = 0;
    fVar17 = (float)func_0x00222fd0(iVar4 + 0x3b0);
    fVar18 = (float)func_0x00222fd0(iVar5 + 0x3b0);
    *(float *)(iVar15 + 0xe0) = fVar17 + fVar18;
    *(undefined4 *)(iVar15 + 0xf0) = 0x41200000;
    __pl__7FVectorCFRC7FVector(auStack_2b0,iVar5 + 0x360,iVar5 + 0x160);
    __pl__7FVectorCFRC7FVector(auStack_2c0,iVar4 + 0x360,iVar15 + 0x100);
    __mi__7FVectorCFRC7FVector(&uStack_2a0,auStack_2b0,auStack_2c0);
    uStack_118._0_4_ = (float)uStack_298;
    _auStack_120 = uStack_2a0;
    uStack_118._4_4_ = uStack_294;
    auStack_11c = (undefined1  [4])((float)((ulong)uStack_2a0 >> 0x20) / 2.0);
    auStack_120 = (undefined1  [4])(int)uStack_2a0;
    fVar17 = (float)func_0x00222fd0(auStack_120);
    *(float *)(iVar15 + 0x80) =
         (*(float *)(iVar15 + 0x84) * (*(float *)(iVar15 + 0xe0) + fVar17)) / 512.0;
    __pl__7FVectorCFRC7FVector(&uStack_2d0,iVar5 + 0x3a0,iVar5 + 0x160);
    uStack_118._0_4_ = (float)uStack_2c8;
    _auStack_120 = uStack_2d0;
    uStack_118._4_4_ = uStack_2c4;
    if ((((*(char *)(iVar4 + 0xb8) == '\x0e') || (*(char *)(iVar4 + 0xb8) == '\x0f')) &&
        (*(char *)(iVar4 + 0xb9) == '\x01')) && (*(int *)(iVar4 + 0xc0) != 0)) {
      uVar10 = FUN_004baab0(*(undefined4 *)(iVar4 + 0xdc),0,*(undefined4 *)(iVar4 + 0xe0),0x3f800000
                            ,auStack_2f0);
      __pl__7FVectorCFRC7FVector(auStack_2e0,iVar4 + 0x3a0,uVar10);
      auVar20 = _lqc2(auStack_2e0);
      auVar19 = _lqc2(_auStack_120);
      auVar19 = _vsub(auVar19,auVar20);
      _auStack_120 = _sqc2(auVar19);
    }
    else {
      __pl__7FVectorCFRC7FVector(auStack_300,iVar4 + 0x3a0,iVar15 + 0x100);
      auVar20 = _lqc2(auStack_300);
      auVar19 = _lqc2(_auStack_120);
      auVar19 = _vsub(auVar19,auVar20);
      _auStack_120 = _sqc2(auVar19);
    }
    uVar10 = func_0x00222f00(auStack_320,auStack_120);
    Get3DAngle__F7FVector(auStack_310,uVar10);
    *(undefined4 *)(iVar15 + 0xe4) = uStack_30c;
    *(undefined4 *)(iVar15 + 0xe8) = 0xc1200000;
    fStack_20 = *(float *)(iVar4 + 0x3a4) - *(float *)(iVar4 + 0x3b4);
    fStack_1c = *(float *)(iVar5 + 0x3a4) - *(float *)(iVar5 + 0x3b4);
    __pl__7FVectorCFRC7FVector(auStack_330,iVar5 + 0x160,iVar5 + 0x3a0);
    fStack_f0 = auStack_330._0_4_;
    fStack_ec = auStack_330._4_4_;
    fStack_e8 = fStack_328;
    uStack_e4 = uStack_324;
    uVar10 = func_0x00222f00(auStack_350,&fStack_f0);
    Get3DAngle__F7FVector(auStack_340,uVar10);
    fStack_100 = auStack_340._0_4_;
    fStack_fc = auStack_340._4_4_;
    fStack_f8 = fStack_338;
    uStack_f4 = uStack_334;
    iVar7 = 0;
    for (fStack_18 = -180.0; fStack_18 < 180.0; fStack_18 = fStack_18 + 11.25) {
      if (((fStack_20 * 1.2 <= fStack_1c) || ((-135.0 <= fStack_18 && (fStack_18 <= 135.0)))) &&
         ((fStack_1c * 1.2 <= fStack_20 || ((fStack_18 <= -45.0 || (45.0 <= fStack_18)))))) {
        for (fStack_14 = *(float *)(iVar15 + 0xe4) + fStack_18; fStack_14 < -180.0;
            fStack_14 = fStack_14 + 360.0) {
        }
        for (; 180.0 <= fStack_14; fStack_14 = fStack_14 - 360.0) {
        }
        if ((((-*(float *)(iGpffff8610 + 0x40b4) / 4.0 <= fStack_f0) ||
             ((10.0 <= fStack_14 && (fStack_14 <= 170.0)))) &&
            (((fStack_f0 <= *(float *)(iGpffff8610 + 0x40b4) / 4.0 ||
              ((fStack_14 <= -10.0 && (-170.0 <= fStack_14)))) &&
             ((fStack_e8 <= *(float *)(iGpffff8610 + 0x40bc) / 4.0 ||
              ((-80.0 <= fStack_14 && (fStack_14 <= 80.0)))))))) &&
           ((-*(float *)(iGpffff8610 + 0x40bc) / 4.0 <= fStack_e8 ||
            ((fStack_14 <= -100.0 || (100.0 <= fStack_14)))))) {
          afStack_a0[iVar7] = fStack_18;
          iVar7 = iVar7 + 1;
        }
      }
    }
    if (iVar7 == 0) {
      for (fStack_18 = -180.0; fStack_18 < 180.0; fStack_18 = fStack_18 + 11.25) {
        for (fStack_14 = *(float *)(iVar15 + 0xe4) + fStack_18; fStack_14 < -180.0;
            fStack_14 = fStack_14 + 360.0) {
        }
        for (; 180.0 <= fStack_14; fStack_14 = fStack_14 - 360.0) {
        }
        if (((((-*(float *)(iGpffff8610 + 0x40b4) / 4.0 <= fStack_f0) ||
              ((10.0 <= fStack_14 && (fStack_14 <= 170.0)))) &&
             ((fStack_f0 <= *(float *)(iGpffff8610 + 0x40b4) / 4.0 ||
              ((fStack_14 <= -10.0 && (-170.0 <= fStack_14)))))) &&
            ((fStack_e8 <= *(float *)(iGpffff8610 + 0x40bc) / 4.0 ||
             ((-80.0 <= fStack_14 && (fStack_14 <= 80.0)))))) &&
           ((-*(float *)(iGpffff8610 + 0x40bc) / 4.0 <= fStack_e8 ||
            ((fStack_14 <= -100.0 || (100.0 <= fStack_14)))))) {
          afStack_a0[iVar7] = fStack_18;
          iVar7 = iVar7 + 1;
        }
      }
    }
    iVar14 = func_0x00232cc8();
    fStack_20 = (float)iVar14 / 2.1474836e+09;
    for (iVar16 = 0; iVar16 < iVar7; iVar16 = iVar16 + 1) {
      fStack_1c = (float)(iVar16 + 1) / (float)iVar7;
      if ((((afStack_a0[iVar16] <= 11.25) || (-168.75 <= afStack_a0[iVar16])) ||
          ((78.75 <= afStack_a0[iVar16] && (afStack_a0[iVar16] <= 101.25)))) ||
         ((-101.25 <= afStack_a0[iVar16] && (afStack_a0[iVar16] <= -78.75)))) {
        fStack_1c = (fStack_1c - (float)iVar16 / (float)iVar7) / 4.0 + (float)iVar16 / (float)iVar7;
      }
      if ((float)iVar14 / 2.1474836e+09 <= fStack_1c) {
        *(float *)(iVar15 + 0xec) = afStack_a0[iVar16];
        break;
      }
    }
    if ((((30.0 < *(float *)(iVar15 + 0xec)) && (*(float *)(iVar15 + 0xec) < 60.0)) ||
        ((120.0 < *(float *)(iVar15 + 0xec) && (*(float *)(iVar15 + 0xec) < 150.0)))) ||
       (((-30.0 < *(float *)(iVar15 + 0xec) && (*(float *)(iVar15 + 0xec) < -60.0)) ||
        ((-120.0 < *(float *)(iVar15 + 0xec) && (*(float *)(iVar15 + 0xec) < -150.0)))))) {
      *(undefined4 *)(iVar15 + 0xe8) = 0xc1700000;
      iVar7 = func_0x00232cc8();
      if ((float)iVar7 / 2.1474836e+09 < 0.5) {
        *(undefined4 *)(iVar15 + 0xe8) = 0x41200000;
        *(undefined4 *)(iVar15 + 0xf0) = 0;
      }
    }
    else if ((((11.25 < *(float *)(iVar15 + 0xec)) && (*(float *)(iVar15 + 0xec) < 78.75)) ||
             ((101.25 < *(float *)(iVar15 + 0xec) && (*(float *)(iVar15 + 0xec) < 168.75)))) ||
            (((-11.25 < *(float *)(iVar15 + 0xec) && (*(float *)(iVar15 + 0xec) < -78.75)) ||
             ((-101.25 < *(float *)(iVar15 + 0xec) && (*(float *)(iVar15 + 0xec) < -168.75)))))) {
      *(undefined4 *)(iVar15 + 0xe8) = 0xc1a00000;
    }
    else if ((((*(float *)(iVar15 + 0xec) <= 11.25) && (-11.25 <= *(float *)(iVar15 + 0xec))) ||
             (168.75 <= *(float *)(iVar15 + 0xec))) || (*(float *)(iVar15 + 0xec) <= -168.75)) {
      *(undefined4 *)(iVar15 + 0xe8) = 0xc1f00000;
    }
    else {
      *(undefined4 *)(iVar15 + 0xf0) = 0x40a00000;
    }
    *(byte *)(iVar15 + 0x18) = *(byte *)(iVar15 + 0x18) & 0x7f | 0x80;
    *(undefined2 *)(iVar15 + 0x1e) = 1;
    iVar7 = func_0x003b9540(0x40,*(undefined4 *)(iVar4 + 0x568),0xffffffffffffffff);
    if ((*(byte *)(iVar7 + 2) & 7) != 0) {
      __pl__7FVectorCFRC7FVector(&uStack_360,iVar5 + 0x160,iVar5 + 0x3a0);
      uStack_118._0_4_ = (float)uStack_358;
      _auStack_120 = uStack_360;
      uStack_118._4_4_ = uStack_354;
      __pl__7FVectorCFRC7FVector(auStack_370,iVar4 + 0x160,iVar4 + 0x3a0);
      auVar20 = _lqc2(auStack_370);
      auVar19 = _lqc2(_auStack_120);
      auVar19 = _vsub(auVar19,auVar20);
      _auStack_120 = _sqc2(auVar19);
      fVar17 = (float)func_0x00222fd0(auStack_120);
      if (fVar17 < -((*(float *)(iVar5 + 0x164) + *(float *)(iVar5 + 0x3a4)) -
                    *(float *)(iVar5 + 0x3b4)) * 2.0 * 10.0 +
                   *(float *)(iVar4 + 0x354) + *(float *)(iVar5 + 0x354)) {
        *(undefined2 *)(iVar15 + 0x1e) = 5;
        return;
      }
      *(undefined2 *)(iVar15 + 0x1e) = 4;
      return;
    }
  case 1:
    if ((*(char *)(iVar4 + 0xb8) == '\x0f') &&
       (((*(short *)(*(int *)(iVar4 + 0x14c) + 0x510) == 0x1f ||
         (*(short *)(*(int *)(iVar4 + 0x14c) + 0x510) == 0x20)) ||
        (*(short *)(*(int *)(iVar4 + 0x14c) + 0x510) == 0x21)))) {
      __pl__7FVectorCFRC7FVector(auStack_390,iVar5 + 0x360,iVar5 + 0x160);
      __pl__7FVectorCFRC7FVector(auStack_3a0,iVar15 + 0x110,iVar15 + 0x100);
      __mi__7FVectorCFRC7FVector(&uStack_380,auStack_390,auStack_3a0);
      uStack_118._0_4_ = (float)uStack_378;
      _auStack_120 = uStack_380;
      uStack_118._4_4_ = uStack_374;
    }
    else {
      __pl__7FVectorCFRC7FVector(auStack_3c0,iVar5 + 0x360,iVar5 + 0x160);
      __pl__7FVectorCFRC7FVector(auStack_3d0,iVar4 + 0x360,iVar15 + 0x100);
      __mi__7FVectorCFRC7FVector(&uStack_3b0,auStack_3c0,auStack_3d0);
      uStack_118._0_4_ = (float)uStack_3a8;
      _auStack_120 = uStack_3b0;
      uStack_118._4_4_ = uStack_3a4;
    }
    auStack_11c = (undefined1  [4])((float)auStack_11c / 2.0);
    fStack_20 = *(float *)(iVar15 + 0xe0);
    fStack_1c = (float)func_0x00222fd0(auStack_120);
    if (fStack_1c < 10.0) {
      fStack_1c = 10.0;
    }
    fStack_20 = fStack_20 + fStack_1c;
    if (fStack_20 < 30.0) {
      fStack_20 = 30.0;
    }
    fStack_20 = fStack_20 + *(float *)(iVar15 + 0xf0);
    if (*(int *)(iVar15 + 0xdc) == 0) {
      *(float *)(iVar15 + 0x80) = (fStack_20 * *(float *)(iVar15 + 0x84)) / 512.0;
    }
    else {
      fStack_1c = (fStack_20 * *(float *)(iVar15 + 0x84)) / 512.0 - *(float *)(iVar15 + 0x80);
      *(float *)(iVar15 + 0x80) =
           *(float *)(iVar15 + 0x80) + fStack_1c * 3.75 * *(float *)(iVar15 + 0x24);
    }
    __pl__7FVectorCFRC7FVector(&uStack_3e0,iVar5 + 0x3a0,iVar5 + 0x160);
    uStack_118._0_4_ = (float)uStack_3d8;
    _auStack_120 = uStack_3e0;
    uStack_118._4_4_ = uStack_3d4;
    if (((*(char *)(iVar4 + 0xb8) == '\x0e') || (*(char *)(iVar4 + 0xb8) == '\x0f')) &&
       ((*(char *)(iVar4 + 0xb9) == '\x01' && (*(int *)(iVar4 + 0xc0) != 0)))) {
      uVar10 = FUN_004baab0(*(undefined4 *)(iVar4 + 0xdc),0,*(undefined4 *)(iVar4 + 0xe0),0x3f800000
                            ,auStack_400);
      __pl__7FVectorCFRC7FVector(auStack_3f0,iVar4 + 0x3a0,uVar10);
      auVar20 = _lqc2(auStack_3f0);
      auVar19 = _lqc2(_auStack_120);
      auVar19 = _vsub(auVar19,auVar20);
      _auStack_120 = _sqc2(auVar19);
    }
    else {
      __pl__7FVectorCFRC7FVector(auStack_410,iVar4 + 0x3a0,iVar15 + 0x100);
      auVar20 = _lqc2(auStack_410);
      auVar19 = _lqc2(_auStack_120);
      auVar19 = _vsub(auVar19,auVar20);
      _auStack_120 = _sqc2(auVar19);
    }
    uVar10 = func_0x00222f00(auStack_430,auStack_120);
    Get3DAngle__F7FVector(&uStack_420,uVar10);
    uStack_108._0_4_ = (float)uStack_418;
    _auStack_110 = uStack_420;
    uStack_108._4_4_ = uStack_414;
    fStack_20 = (float)((ulong)uStack_420 >> 0x20) + *(float *)(iVar15 + 0xec);
    if (*(int *)(iVar15 + 0xdc) == 0) {
      *(float *)(iVar15 + 0xe4) = fStack_20;
    }
    else {
      for (fStack_20 = fStack_20 - *(float *)(iVar15 + 0xe4); fStack_20 < -180.0;
          fStack_20 = fStack_20 + 360.0) {
      }
      for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
      }
      if (0.0 <= fStack_20) {
        if (*(float *)(iVar15 + 0x24) * 30.0 < fStack_20) {
          fStack_20 = *(float *)(iVar15 + 0x24) * 30.0;
        }
      }
      else if (fStack_20 < *(float *)(iVar15 + 0x24) * -30.0) {
        fStack_20 = *(float *)(iVar15 + 0x24) * -30.0;
      }
      *(float *)(iVar15 + 0xe4) = *(float *)(iVar15 + 0xe4) + fStack_20;
    }
    if (*(float *)(iVar15 + 0xe4) < -180.0) {
      *(float *)(iVar15 + 0xe4) = *(float *)(iVar15 + 0xe4) + 360.0;
    }
    if (180.0 < *(float *)(iVar15 + 0xe4)) {
      *(float *)(iVar15 + 0xe4) = *(float *)(iVar15 + 0xe4) - 360.0;
    }
    if ((((long)((ulong)*(byte *)(iVar4 + 0x3c1) << 0x3e) < 0) && (*(int *)(iVar4 + 0x500) != 0)) &&
       (*(char *)(*(int *)(iVar4 + 0x500) + 3) == '\x03')) {
      fStack_20 = 30.0 - *(float *)(iVar15 + 0xe8);
      *(undefined4 *)(iVar15 + 0xf0) = 0x41a00000;
    }
    else if ((((long)((ulong)*(byte *)(iVar4 + 0x3c1) << 0x3e) < 0) &&
             (*(int *)(iVar4 + 0x500) != 0)) && (*(char *)(*(int *)(iVar4 + 0x500) + 3) == '\x05'))
    {
      fStack_1c = -30.0 - *(float *)(iVar15 + 0xe8);
      *(undefined4 *)(iVar15 + 0xf0) = 0x41a00000;
    }
    else {
      fStack_20 = 0.0;
    }
    for (; fStack_20 < -180.0; fStack_20 = fStack_20 + 360.0) {
    }
    for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
    }
    if (0.0 <= fStack_20) {
      if (*(float *)(iVar15 + 0x24) * 30.0 < fStack_20) {
        fStack_20 = *(float *)(iVar15 + 0x24) * 30.0;
      }
    }
    else if (fStack_20 < *(float *)(iVar15 + 0x24) * -30.0) {
      fStack_20 = *(float *)(iVar15 + 0x24) * -30.0;
    }
    *(float *)(iVar15 + 0xe8) = *(float *)(iVar15 + 0xe8) + fStack_20;
    if (*(float *)(iVar15 + 0xe8) < -180.0) {
      *(float *)(iVar15 + 0xe8) = *(float *)(iVar15 + 0xe8) + 360.0;
    }
    if (180.0 < *(float *)(iVar15 + 0xe8)) {
      *(float *)(iVar15 + 0xe8) = *(float *)(iVar15 + 0xe8) - 360.0;
    }
    auVar19 = _vmr32(in_vf0);
    auVar20 = _vmr32(auVar19);
    auVar21 = _vmr32(auVar20);
    auStack_1d0 = _sqc2(in_vf0);
    auStack_1e0 = _sqc2(auVar19);
    auStack_1f0 = _sqc2(auVar20);
    auStack_200 = _sqc2(auVar21);
    uVar11 = func_0x00222e40(*(undefined4 *)(iVar15 + 0xe8));
    func_0x00202890(uVar11,auStack_200,auStack_200);
    uVar11 = func_0x00222e40(-*(float *)(iVar15 + 0xe4));
    func_0x00202938(uVar11,auStack_200,auStack_200);
    if (*(int *)(iVar15 + 0xdc) == 0) {
      uVar10 = FUN_004baab0(0,0,-*(float *)(iVar15 + 0x80),0x3f800000,auStack_450);
      func_0x00222df0(auStack_440,auStack_200,uVar10);
      *(int *)(iVar15 + 0x50) = auStack_440._0_4_;
      *(int *)(iVar15 + 0x54) = auStack_440._4_4_;
      *(undefined4 *)(iVar15 + 0x58) = uStack_438;
      *(undefined4 *)(iVar15 + 0x5c) = uStack_434;
      auVar19 = _vmr32(in_vf0);
      auVar20 = _vmr32(auVar19);
      auVar21 = _vmr32(auVar20);
      auStack_1d0 = _sqc2(in_vf0);
      auStack_1e0 = _sqc2(auVar19);
      auStack_1f0 = _sqc2(auVar20);
      auStack_200 = _sqc2(auVar21);
      uVar11 = func_0x00222e40(-*(float *)(iVar5 + 0x184));
      func_0x00202938(uVar11,auStack_200,auStack_200);
      func_0x00222df0(auStack_460,auStack_200,iVar5 + 0x360);
      auVar2._4_8_ = uStack_108;
      auVar2._0_4_ = uStack_45c;
      _auStack_110 = auVar2._0_8_ << 0x20;
      uStack_108._0_4_ = (float)uStack_458;
      uStack_108._4_4_ = uStack_454;
      auVar3._12_4_ = 0;
      auVar3._0_12_ = _auStack_10c;
      _auStack_110 = auVar3 << 0x20;
      auVar19 = _vmr32(in_vf0);
      auVar20 = _vmr32(auVar19);
      auVar21 = _vmr32(auVar20);
      auStack_1d0 = _sqc2(in_vf0);
      auStack_1e0 = _sqc2(auVar19);
      auStack_1f0 = _sqc2(auVar20);
      auStack_200 = _sqc2(auVar21);
      uVar11 = func_0x00222e40(*(undefined4 *)(iVar5 + 0x184));
      func_0x00202938(uVar11,auStack_200,auStack_200);
      func_0x00222df0(auStack_480,auStack_200,auStack_110);
      __pl__7FVectorCFRC7FVector(&uStack_470,iVar5 + 0x160,auStack_480);
      uStack_118._0_4_ = (float)uStack_468;
      _auStack_120 = uStack_470;
      uStack_118._4_4_ = uStack_464;
      auStack_11c = (undefined1  [4])*(undefined4 *)(iVar5 + 0x3a4);
      auStack_120 = (undefined1  [4])(int)uStack_470;
      auVar19 = _vmr32(in_vf0);
      auVar20 = _vmr32(auVar19);
      auVar21 = _vmr32(auVar20);
      auStack_1d0 = _sqc2(in_vf0);
      auStack_1e0 = _sqc2(auVar19);
      auStack_1f0 = _sqc2(auVar20);
      auStack_200 = _sqc2(auVar21);
      uVar11 = func_0x00222e40(-*(float *)(iVar4 + 0x184));
      func_0x00202938(uVar11,auStack_200,auStack_200);
      func_0x00222df0(auStack_490,auStack_200,iVar4 + 0x360);
      fStack_fc = (float)uStack_48c;
      fStack_f8 = (float)uStack_488;
      uStack_f4 = uStack_484;
      fStack_100 = 0.0;
      auVar19 = _vmr32(in_vf0);
      auVar20 = _vmr32(auVar19);
      auVar21 = _vmr32(auVar20);
      auStack_1d0 = _sqc2(in_vf0);
      auStack_1e0 = _sqc2(auVar19);
      auStack_1f0 = _sqc2(auVar20);
      auStack_200 = _sqc2(auVar21);
      uVar11 = func_0x00222e40(*(undefined4 *)(iVar4 + 0x184));
      func_0x00202938(uVar11,auStack_200,auStack_200);
      func_0x00222df0(auStack_4b0,auStack_200,&fStack_100);
      __pl__7FVectorCFRC7FVector(&uStack_4a0,iVar4 + 0x160,auStack_4b0);
      uStack_108._0_4_ = (float)uStack_498;
      _auStack_110 = uStack_4a0;
      uStack_108._4_4_ = uStack_494;
      auStack_10c = (undefined1  [4])*(undefined4 *)(iVar4 + 0x3a4);
      auStack_110 = (undefined1  [4])(int)uStack_4a0;
      auVar20 = _lqc2(_auStack_110);
      auVar19 = _lqc2(_auStack_120);
      auVar19 = _vadd(auVar19,auVar20);
      _auStack_120 = _sqc2(auVar19);
      func_0x00223030(0x40000000,auStack_120);
      auVar20 = _lqc2(_auStack_120);
      auVar19 = _lqc2(*(undefined1 (*) [16])(iVar15 + 0x50));
      auVar19 = _vadd(auVar19,auVar20);
      auVar19 = _sqc2(auVar19);
      *(undefined1 (*) [16])(iVar15 + 0x50) = auVar19;
    }
    else {
      uVar10 = FUN_004baab0(0,0,-*(float *)(iVar15 + 0x80),0x3f800000,auStack_4d0);
      func_0x00222df0(&uStack_4c0,auStack_200,uVar10);
      uStack_118._0_4_ = (float)uStack_4b8;
      _auStack_120 = uStack_4c0;
      uStack_118._4_4_ = uStack_4b4;
      auVar19 = _vmr32(in_vf0);
      auVar20 = _vmr32(auVar19);
      auVar21 = _vmr32(auVar20);
      auStack_1d0 = _sqc2(in_vf0);
      auStack_1e0 = _sqc2(auVar19);
      auStack_1f0 = _sqc2(auVar20);
      auStack_200 = _sqc2(auVar21);
      uVar11 = func_0x00222e40(-*(float *)(iVar5 + 0x184));
      func_0x00202938(uVar11,auStack_200,auStack_200);
      func_0x00222df0(auStack_4e0,auStack_200,iVar5 + 0x360);
      fStack_fc = (float)uStack_4dc;
      fStack_f8 = (float)uStack_4d8;
      uStack_f4 = uStack_4d4;
      fStack_100 = 0.0;
      auVar19 = _vmr32(in_vf0);
      auVar20 = _vmr32(auVar19);
      auVar21 = _vmr32(auVar20);
      auStack_1d0 = _sqc2(in_vf0);
      auStack_1e0 = _sqc2(auVar19);
      auStack_1f0 = _sqc2(auVar20);
      auStack_200 = _sqc2(auVar21);
      uVar11 = func_0x00222e40(*(undefined4 *)(iVar5 + 0x184));
      func_0x00202938(uVar11,auStack_200,auStack_200);
      func_0x00222df0(auStack_500,auStack_200,&fStack_100);
      __pl__7FVectorCFRC7FVector(&uStack_4f0,iVar5 + 0x160,auStack_500);
      uStack_108._0_4_ = (float)uStack_4e8;
      _auStack_110 = uStack_4f0;
      uStack_108._4_4_ = uStack_4e4;
      auStack_10c = (undefined1  [4])*(undefined4 *)(iVar5 + 0x3a4);
      auStack_110 = (undefined1  [4])(int)uStack_4f0;
      auVar19 = _vmr32(in_vf0);
      auVar20 = _vmr32(auVar19);
      auVar21 = _vmr32(auVar20);
      auStack_1d0 = _sqc2(in_vf0);
      auStack_1e0 = _sqc2(auVar19);
      auStack_1f0 = _sqc2(auVar20);
      auStack_200 = _sqc2(auVar21);
      uVar11 = func_0x00222e40(-*(float *)(iVar4 + 0x184));
      func_0x00202938(uVar11,auStack_200,auStack_200);
      func_0x00222df0(auStack_510,auStack_200,iVar4 + 0x360);
      fStack_ec = fStack_50c;
      fStack_e8 = fStack_508;
      uStack_e4 = uStack_504;
      fStack_f0 = 0.0;
      auVar19 = _vmr32(in_vf0);
      auVar20 = _vmr32(auVar19);
      auVar21 = _vmr32(auVar20);
      auStack_1d0 = _sqc2(in_vf0);
      auStack_1e0 = _sqc2(auVar19);
      auStack_1f0 = _sqc2(auVar20);
      auStack_200 = _sqc2(auVar21);
      uVar11 = func_0x00222e40(*(undefined4 *)(iVar4 + 0x184));
      func_0x00202938(uVar11,auStack_200,auStack_200);
      func_0x00222df0(auStack_530,auStack_200,&fStack_f0);
      __pl__7FVectorCFRC7FVector(afStack_520,iVar4 + 0x160,auStack_530);
      fStack_100 = afStack_520[0];
      fStack_f8 = (float)uStack_518;
      uStack_f4 = uStack_514;
      fStack_fc = *(float *)(iVar4 + 0x3a4);
      auVar21._4_4_ = fStack_fc;
      auVar21._0_4_ = afStack_520[0];
      auVar21._8_4_ = uStack_518;
      auVar21._12_4_ = uStack_514;
      auVar20 = _lqc2(auVar21);
      auVar19 = _lqc2(_auStack_110);
      auVar19 = _vadd(auVar19,auVar20);
      _auStack_110 = _sqc2(auVar19);
      func_0x00223030(0x40000000,auStack_110);
      auVar20 = _lqc2(_auStack_110);
      auVar19 = _lqc2(_auStack_120);
      auVar19 = _vadd(auVar19,auVar20);
      auVar19 = _sqc2(auVar19);
      auVar20 = _lqc2(*(undefined1 (*) [16])(iVar15 + 0x50));
      auVar19 = _lqc2(auVar19);
      auVar19 = _vsub(auVar19,auVar20);
      _auStack_120 = _sqc2(auVar19);
      __ml__7FVectorCFf(*(float *)(iVar15 + 0x24) * 10.0,auStack_540,auStack_120);
      auVar20 = _lqc2(auStack_540);
      auVar19 = _lqc2(*(undefined1 (*) [16])(iVar15 + 0x50));
      auVar19 = _vadd(auVar19,auVar20);
      auVar19 = _sqc2(auVar19);
      *(undefined1 (*) [16])(iVar15 + 0x50) = auVar19;
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    if (*(float *)(iVar15 + 0x50) < (-*(float *)(iGpffff8610 + 0x40b4) - 10.0) / 2.0 + 1.0) {
      *(float *)(iVar15 + 0x50) = (-*(float *)(iGpffff8610 + 0x40b4) - 10.0) / 2.0 + 1.0;
    }
    if ((*(float *)(iGpffff8610 + 0x40b4) + 10.0) / 2.0 - 1.0 < *(float *)(iVar15 + 0x50)) {
      *(float *)(iVar15 + 0x50) = (*(float *)(iGpffff8610 + 0x40b4) + 10.0) / 2.0 - 1.0;
    }
    if (*(float *)(iVar15 + 0x58) < (-*(float *)(iGpffff8610 + 0x40bc) - 10.0) / 2.0 + 1.0) {
      *(float *)(iVar15 + 0x58) = (-*(float *)(iGpffff8610 + 0x40bc) - 10.0) / 2.0 + 1.0;
    }
    if ((*(float *)(iGpffff8610 + 0x40bc) + 10.0) / 2.0 - 1.0 < *(float *)(iVar15 + 0x58)) {
      *(float *)(iVar15 + 0x58) = (*(float *)(iGpffff8610 + 0x40bc) + 10.0) / 2.0 - 1.0;
    }
    __pl__7FVectorCFRC7FVector(&uStack_550,iVar5 + 0x160,iVar5 + 0x360);
    uStack_118._0_4_ = (float)uStack_548;
    _auStack_120 = uStack_550;
    uStack_118._4_4_ = uStack_544;
    if ((*(char *)(iVar4 + 0xb8) == '\x0f') &&
       (((*(short *)(*(int *)(iVar4 + 0x14c) + 0x510) == 0x1f ||
         (*(short *)(*(int *)(iVar4 + 0x14c) + 0x510) == 0x20)) ||
        (*(short *)(*(int *)(iVar4 + 0x14c) + 0x510) == 0x21)))) {
      __pl__7FVectorCFRC7FVector(auStack_560,iVar15 + 0x110,iVar15 + 0x100);
      auVar20 = _lqc2(auStack_560);
      auVar19 = _lqc2(_auStack_120);
      auVar19 = _vadd(auVar19,auVar20);
      _auStack_120 = _sqc2(auVar19);
    }
    else {
      __pl__7FVectorCFRC7FVector(auStack_570,iVar4 + 0x360,iVar15 + 0x100);
      auVar20 = _lqc2(auStack_570);
      auVar19 = _lqc2(_auStack_120);
      auVar19 = _vadd(auVar19,auVar20);
      _auStack_120 = _sqc2(auVar19);
    }
    func_0x00223030(0x40000000,auStack_120);
    auVar20 = _lqc2(*(undefined1 (*) [16])(iVar15 + 0x50));
    auVar19 = _lqc2(_auStack_120);
    auVar19 = _vsub(auVar19,auVar20);
    _auStack_120 = _sqc2(auVar19);
    uVar10 = func_0x00222f00(auStack_590,auStack_120);
    Get3DAngle__F7FVector(&uStack_580,uVar10);
    fStack_198 = (float)uStack_578;
    auStack_1a0 = (undefined1  [8])uStack_580;
    uStack_194 = uStack_574;
    while ((float)auStack_1a0._0_4_ < -180.0) {
      auStack_1a0._0_4_ = (float)auStack_1a0._0_4_ + 360.0;
    }
    while (180.0 < (float)auStack_1a0._0_4_) {
      auStack_1a0._0_4_ = (float)auStack_1a0._0_4_ - 360.0;
    }
    while ((float)auStack_1a0._4_4_ < -180.0) {
      auStack_1a0._4_4_ = (float)auStack_1a0._4_4_ + 360.0;
    }
    while (180.0 < (float)auStack_1a0._4_4_) {
      auStack_1a0._4_4_ = (float)auStack_1a0._4_4_ - 360.0;
    }
    FUN_004baab0(0x43b40000,0xc3b40000,0x43b40000,0xc3b40000,auStack_5a0);
    fStack_190 = auStack_5a0._0_4_;
    fStack_18c = auStack_5a0._4_4_;
    fStack_188 = fStack_598;
    fStack_184 = fStack_594;
    __pl__7FVectorCFRC7FVector(auStack_5d0,iVar5 + 0x160,iVar5 + 0x360);
    uVar10 = FUN_004baab0(-*(float *)(iVar5 + 0x3b0),-*(float *)(iVar5 + 0x3b4),
                          -*(float *)(iVar5 + 0x3b8),0x3f800000,auStack_5e0);
    __pl__7FVectorCFRC7FVector(auStack_5c0,auStack_5d0,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_5b0,auStack_5c0,iVar15 + 0x50);
    __pl__7FVectorCFRC7FVector(auStack_610,iVar5 + 0x160,iVar5 + 0x360);
    uVar10 = FUN_004baab0(*(undefined4 *)(iVar5 + 0x3b0),-*(float *)(iVar5 + 0x3b4),
                          -*(float *)(iVar5 + 0x3b8),0x3f800000,auStack_620);
    __pl__7FVectorCFRC7FVector(auStack_600,auStack_610,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_5f0,auStack_600,iVar15 + 0x50);
    __pl__7FVectorCFRC7FVector(auStack_650,iVar5 + 0x160,iVar5 + 0x360);
    uVar10 = FUN_004baab0(-*(float *)(iVar5 + 0x3b0),*(undefined4 *)(iVar5 + 0x3b4),
                          -*(float *)(iVar5 + 0x3b8),0x3f800000,auStack_660);
    __pl__7FVectorCFRC7FVector(auStack_640,auStack_650,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_630,auStack_640,iVar15 + 0x50);
    fStack_100 = auStack_630._0_4_;
    fStack_fc = auStack_630._4_4_;
    fStack_f8 = (float)uStack_628;
    uStack_f4 = uStack_624;
    __pl__7FVectorCFRC7FVector(auStack_690,iVar5 + 0x160,iVar5 + 0x360);
    uVar10 = FUN_004baab0(*(undefined4 *)(iVar5 + 0x3b0),*(undefined4 *)(iVar5 + 0x3b4),
                          -*(float *)(iVar5 + 0x3b8),0x3f800000,auStack_6a0);
    __pl__7FVectorCFRC7FVector(auStack_680,auStack_690,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_670,auStack_680,iVar15 + 0x50);
    fStack_f0 = auStack_670._0_4_;
    fStack_ec = auStack_670._4_4_;
    fStack_e8 = (float)uStack_668;
    uStack_e4 = uStack_664;
    __pl__7FVectorCFRC7FVector(auStack_6d0,iVar5 + 0x160,iVar5 + 0x360);
    uVar10 = FUN_004baab0(-*(float *)(iVar5 + 0x3b0),-*(float *)(iVar5 + 0x3b4),
                          *(undefined4 *)(iVar5 + 0x3b8),0x3f800000,auStack_6e0);
    __pl__7FVectorCFRC7FVector(auStack_6c0,auStack_6d0,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_6b0,auStack_6c0,iVar15 + 0x50);
    fStack_e0 = auStack_6b0._0_4_;
    fStack_dc = auStack_6b0._4_4_;
    fStack_d8 = (float)uStack_6a8;
    uStack_d4 = uStack_6a4;
    __pl__7FVectorCFRC7FVector(auStack_710,iVar5 + 0x160,iVar5 + 0x360);
    uVar10 = FUN_004baab0(*(undefined4 *)(iVar5 + 0x3b0),-*(float *)(iVar5 + 0x3b4),
                          *(undefined4 *)(iVar5 + 0x3b8),0x3f800000,auStack_720);
    __pl__7FVectorCFRC7FVector(auStack_700,auStack_710,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_6f0,auStack_700,iVar15 + 0x50);
    afStack_d0[0] = auStack_6f0._0_4_;
    afStack_d0[1] = auStack_6f0._4_4_;
    afStack_d0[2] = (float)uStack_6e8;
    afStack_d0[3] = (float)uStack_6e4;
    __pl__7FVectorCFRC7FVector(auStack_750,iVar5 + 0x160,iVar5 + 0x360);
    uVar10 = FUN_004baab0(-*(float *)(iVar5 + 0x3b0),*(undefined4 *)(iVar5 + 0x3b4),
                          *(undefined4 *)(iVar5 + 0x3b8),0x3f800000,auStack_760);
    __pl__7FVectorCFRC7FVector(auStack_740,auStack_750,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_730,auStack_740,iVar15 + 0x50);
    afStack_d0[4] = auStack_730._0_4_;
    afStack_d0[5] = auStack_730._4_4_;
    afStack_d0[6] = (float)uStack_728;
    afStack_d0[7] = (float)uStack_724;
    __pl__7FVectorCFRC7FVector(auStack_790,iVar5 + 0x160,iVar5 + 0x360);
    uVar10 = FUN_004baab0(*(undefined4 *)(iVar5 + 0x3b0),*(undefined4 *)(iVar5 + 0x3b4),
                          *(undefined4 *)(iVar5 + 0x3b8),0x3f800000,auStack_7a0);
    __pl__7FVectorCFRC7FVector(auStack_780,auStack_790,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_770,auStack_780,iVar15 + 0x50);
    afStack_d0[8] = auStack_770._0_4_;
    afStack_d0[9] = auStack_770._4_4_;
    afStack_d0[10] = (float)uStack_768;
    afStack_d0[0xb] = (float)uStack_764;
    for (iVar5 = 0; iVar5 < 8; iVar5 = iVar5 + 1) {
      uVar10 = func_0x00222f00(auStack_7c0,auStack_120 + iVar5 * 0x10);
      Get3DAngle__F7FVector(auStack_7b0,uVar10);
      fStack_180 = auStack_7b0._0_4_;
      fStack_17c = auStack_7b0._4_4_;
      fStack_178 = fStack_7a8;
      uStack_174 = uStack_7a4;
      for (fStack_20 = fStack_180 - (float)auStack_1a0._0_4_; fStack_20 < -180.0;
          fStack_20 = fStack_20 + 360.0) {
      }
      for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
      }
      if (fStack_20 < fStack_190) {
        fStack_190 = fStack_20;
      }
      if (fStack_18c < fStack_20) {
        fStack_18c = fStack_20;
      }
      for (fStack_20 = fStack_17c - (float)auStack_1a0._4_4_; fStack_20 < -180.0;
          fStack_20 = fStack_20 + 360.0) {
      }
      for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
      }
      if (fStack_20 < fStack_188) {
        fStack_188 = fStack_20;
      }
      if (fStack_184 < fStack_20) {
        fStack_184 = fStack_20;
      }
    }
    if ((*(char *)(iVar4 + 0xb8) == '\x0f') &&
       (((*(short *)(*(int *)(iVar4 + 0x14c) + 0x510) == 0x1f ||
         (*(short *)(*(int *)(iVar4 + 0x14c) + 0x510) == 0x20)) ||
        (*(short *)(*(int *)(iVar4 + 0x14c) + 0x510) == 0x21)))) {
      __pl__7FVectorCFRC7FVector(auStack_7d0,iVar15 + 0x110,iVar15 + 0x100);
      fStack_180 = auStack_7d0._0_4_;
      fStack_17c = auStack_7d0._4_4_;
      fStack_178 = (float)uStack_7c8;
      uStack_174 = uStack_7c4;
    }
    else {
      __pl__7FVectorCFRC7FVector(auStack_7e0,iVar4 + 0x360,iVar15 + 0x100);
      fStack_180 = auStack_7e0._0_4_;
      fStack_17c = auStack_7e0._4_4_;
      fStack_178 = (float)uStack_7d8;
      uStack_174 = uStack_7d4;
    }
    uVar10 = FUN_004baab0(-*(float *)(iVar4 + 0x3b0),-*(float *)(iVar4 + 0x3b4),
                          -*(float *)(iVar4 + 0x3b8),0x3f800000,auStack_810);
    __pl__7FVectorCFRC7FVector(auStack_800,&fStack_180,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_7f0,auStack_800,iVar15 + 0x50);
    uVar10 = FUN_004baab0(*(undefined4 *)(iVar4 + 0x3b0),-*(float *)(iVar4 + 0x3b4),
                          -*(float *)(iVar4 + 0x3b8),0x3f800000,auStack_840);
    __pl__7FVectorCFRC7FVector(auStack_830,&fStack_180,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_820,auStack_830,iVar15 + 0x50);
    uVar10 = FUN_004baab0(-*(float *)(iVar4 + 0x3b0),*(undefined4 *)(iVar4 + 0x3b4),
                          -*(float *)(iVar4 + 0x3b8),0x3f800000,auStack_870);
    __pl__7FVectorCFRC7FVector(auStack_860,&fStack_180,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_850,auStack_860,iVar15 + 0x50);
    fStack_100 = auStack_850._0_4_;
    fStack_fc = auStack_850._4_4_;
    fStack_f8 = (float)uStack_848;
    uStack_f4 = uStack_844;
    uVar10 = FUN_004baab0(*(undefined4 *)(iVar4 + 0x3b0),*(undefined4 *)(iVar4 + 0x3b4),
                          -*(float *)(iVar4 + 0x3b8),0x3f800000,auStack_8a0);
    __pl__7FVectorCFRC7FVector(auStack_890,&fStack_180,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_880,auStack_890,iVar15 + 0x50);
    fStack_f0 = auStack_880._0_4_;
    fStack_ec = auStack_880._4_4_;
    fStack_e8 = (float)uStack_878;
    uStack_e4 = uStack_874;
    uVar10 = FUN_004baab0(-*(float *)(iVar4 + 0x3b0),-*(float *)(iVar4 + 0x3b4),
                          *(undefined4 *)(iVar4 + 0x3b8),0x3f800000,auStack_8d0);
    __pl__7FVectorCFRC7FVector(auStack_8c0,&fStack_180,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_8b0,auStack_8c0,iVar15 + 0x50);
    fStack_e0 = auStack_8b0._0_4_;
    fStack_dc = auStack_8b0._4_4_;
    fStack_d8 = (float)uStack_8a8;
    uStack_d4 = uStack_8a4;
    uVar10 = FUN_004baab0(*(undefined4 *)(iVar4 + 0x3b0),-*(float *)(iVar4 + 0x3b4),
                          *(undefined4 *)(iVar4 + 0x3b8),0x3f800000,auStack_900);
    __pl__7FVectorCFRC7FVector(auStack_8f0,&fStack_180,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_8e0,auStack_8f0,iVar15 + 0x50);
    afStack_d0[0] = auStack_8e0._0_4_;
    afStack_d0[1] = auStack_8e0._4_4_;
    afStack_d0[2] = (float)uStack_8d8;
    afStack_d0[3] = (float)uStack_8d4;
    uVar10 = FUN_004baab0(-*(float *)(iVar4 + 0x3b0),*(undefined4 *)(iVar4 + 0x3b4),
                          *(undefined4 *)(iVar4 + 0x3b8),0x3f800000,auStack_930);
    __pl__7FVectorCFRC7FVector(auStack_920,&fStack_180,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_910,auStack_920,iVar15 + 0x50);
    afStack_d0[4] = auStack_910._0_4_;
    afStack_d0[5] = auStack_910._4_4_;
    afStack_d0[6] = (float)uStack_908;
    afStack_d0[7] = (float)uStack_904;
    uVar10 = FUN_004baab0(*(undefined4 *)(iVar4 + 0x3b0),*(undefined4 *)(iVar4 + 0x3b4),
                          *(undefined4 *)(iVar4 + 0x3b8),0x3f800000,auStack_960);
    __pl__7FVectorCFRC7FVector(auStack_950,&fStack_180,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_940,auStack_950,iVar15 + 0x50);
    afStack_d0[8] = auStack_940._0_4_;
    afStack_d0[9] = auStack_940._4_4_;
    afStack_d0[10] = (float)uStack_938;
    afStack_d0[0xb] = (float)uStack_934;
    for (iVar4 = 0; iVar4 < 8; iVar4 = iVar4 + 1) {
      uVar10 = func_0x00222f00(auStack_980,auStack_120 + iVar4 * 0x10);
      Get3DAngle__F7FVector(auStack_970,uVar10);
      fStack_180 = auStack_970._0_4_;
      fStack_17c = auStack_970._4_4_;
      fStack_178 = (float)uStack_968;
      uStack_174 = uStack_964;
      for (fStack_20 = fStack_180 - (float)auStack_1a0._0_4_; fStack_20 < -180.0;
          fStack_20 = fStack_20 + 360.0) {
      }
      for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
      }
      if (fStack_20 < fStack_190) {
        fStack_190 = fStack_20;
      }
      if (fStack_18c < fStack_20) {
        fStack_18c = fStack_20;
      }
      for (fStack_20 = fStack_17c - (float)auStack_1a0._4_4_; fStack_20 < -180.0;
          fStack_20 = fStack_20 + 360.0) {
      }
      for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
      }
      if (fStack_20 < fStack_188) {
        fStack_188 = fStack_20;
      }
      if (fStack_184 < fStack_20) {
        fStack_184 = fStack_20;
      }
    }
    uVar10 = FUN_004baab0(fStack_190,fStack_188,0,0x3f800000,auStack_9a0);
    __pl__7FVectorCFRC7FVector(auStack_990,auStack_1a0,uVar10);
    fStack_160 = auStack_990._0_4_;
    fStack_15c = auStack_990._4_4_;
    uStack_158 = uStack_988;
    uStack_154 = uStack_984;
    uVar10 = FUN_004baab0(fStack_18c,fStack_184,0,0x3f800000,auStack_9c0);
    __pl__7FVectorCFRC7FVector(auStack_9b0,auStack_1a0,uVar10);
    for (fStack_20 = (float)auStack_9b0._0_8_ - fStack_160; fStack_20 < -180.0;
        fStack_20 = fStack_20 + 360.0) {
    }
    for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
    }
    if (*(int *)(iVar15 + 0xdc) == 0) {
      *(float *)(iVar15 + 0x60) = -(fStack_160 + fStack_20 / 2.0);
    }
    else {
      for (fStack_20 = -(fStack_160 + fStack_20 / 2.0) - *(float *)(iVar15 + 0x60);
          fStack_20 < -180.0; fStack_20 = fStack_20 + 360.0) {
      }
      for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
      }
      *(float *)(iVar15 + 0x60) =
           *(float *)(iVar15 + 0x60) + fStack_20 * 4.0 * *(float *)(iVar15 + 0x24);
    }
    while (*(float *)(iVar15 + 0x60) < -180.0) {
      *(float *)(iVar15 + 0x60) = *(float *)(iVar15 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar15 + 0x60)) {
      *(float *)(iVar15 + 0x60) = *(float *)(iVar15 + 0x60) - 360.0;
    }
    for (fStack_20 = SUB84(auStack_9b0._0_8_,4) - fStack_15c; fStack_20 < -180.0;
        fStack_20 = fStack_20 + 360.0) {
    }
    for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
    }
    if (*(int *)(iVar15 + 0xdc) == 0) {
      *(float *)(iVar15 + 100) = -(fStack_15c + fStack_20 / 2.0);
    }
    else {
      for (fStack_20 = -(fStack_15c + fStack_20 / 2.0) - *(float *)(iVar15 + 100);
          fStack_20 < -180.0; fStack_20 = fStack_20 + 360.0) {
      }
      for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
      }
      *(float *)(iVar15 + 100) =
           *(float *)(iVar15 + 100) + fStack_20 * 4.0 * *(float *)(iVar15 + 0x24);
    }
    while (*(float *)(iVar15 + 100) < -180.0) {
      *(float *)(iVar15 + 100) = *(float *)(iVar15 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar15 + 100)) {
      *(float *)(iVar15 + 100) = *(float *)(iVar15 + 100) - 360.0;
    }
    *(undefined4 *)(iVar15 + 0x68) = 0;
    *(undefined4 *)(iVar15 + 0xdc) = 1;
    break;
  case 2:
    *(float *)(iVar15 + 0xf4) = *(float *)(iVar15 + 0xf4) + *(float *)(iVar15 + 0x24);
    *(float *)(iVar15 + 0x84) = *(float *)(iVar15 + 0x84) - *(float *)(iVar15 + 0x24) * 10.0 * 30.0;
    if ((long)((ulong)*(byte *)(iVar4 + 0xb1) << 0x3e) < 0) {
      switch(*(undefined2 *)(iVar4 + 0xba)) {
      default:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 5.6;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 5.6;
        break;
      case 1:
      case 2:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 10.0;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 10.0;
        break;
      case 4:
      case 5:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 10.0;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 10.0;
        break;
      case 7:
      case 8:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 8.0;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 8.0;
        break;
      case 10:
      case 0xb:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 8.0;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 8.0;
        break;
      case 0xd:
      case 0xe:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 8.0;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 8.0;
        break;
      case 0x10:
      case 0x11:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 6.4;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 6.4;
        break;
      case 0x12:
      case 0x13:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 9.4;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 9.4;
        break;
      case 0x14:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 6.4;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 6.4;
        break;
      case 0x15:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 7.2;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 7.2;
        break;
      case 0x16:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 5.6;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 5.6;
      }
    }
    else {
      switch(*(undefined2 *)(iVar4 + 0x120)) {
      case 0:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 5.6;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 5.6;
        break;
      case 1:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 5.8;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 5.8;
        break;
      case 2:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 5.4;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 5.4;
        break;
      case 3:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 5.4;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 5.4;
        break;
      case 4:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 5.4;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 5.4;
        break;
      case 5:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 5.4;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 5.4;
        break;
      case 6:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 5.8;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 5.8;
        break;
      case 7:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 5.4;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 5.4;
        break;
      case 8:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 5.4;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 5.4;
        break;
      case 9:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 5.8;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 5.8;
        break;
      case 10:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 7.0;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 7.0;
        break;
      case 0xb:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 5.8;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 5.8;
        break;
      case 0xc:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 5.8;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 5.8;
        break;
      case 0xd:
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) - 5.8;
        *(float *)(iVar15 + 0xf0) =
             *(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x24) * 0.9 * 30.0;
        *(float *)(iVar15 + 0xf0) = *(float *)(iVar15 + 0xf0) + 5.8;
      }
    }
    if (((*(byte *)(iVar4 + 0xb4) & 1) == 0) && (*(short *)(iVar4 + 0x120) == 2)) {
      pauVar13 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iVar4 + 0x14c) + 0x544) + 0x30) +
                  (uint)*(byte *)(*(int *)(*(int *)(*(int *)(iVar4 + 0x14c) + 0x544) + 0xe4) +
                                 *(short *)(iGpffff8610 + 0x4660) * 0x110) * 0x1f0 +
                 (bGpffff8240 & 1) * 0x40);
      auStack_200 = *pauVar13;
      auStack_1f0 = pauVar13[1];
      auStack_1e0 = pauVar13[2];
      auStack_1d0 = pauVar13[3];
      FUN_00624f70(*(int *)(*(int *)(*(int *)(iVar4 + 0x14c) + 0x544) + 0xe4) +
                   *(short *)(iGpffff8610 + 0x4660) * 0x110 + 0x10,auStack_200,&fStack_1b0,
                   &fStack_1c0,1,8);
      __pl__7FVectorCFRC7FVector(auStack_a60,&fStack_1b0,&fStack_1c0);
      *(int *)(iVar15 + 0x70) = auStack_a60._0_4_;
      *(int *)(iVar15 + 0x74) = auStack_a60._4_4_;
      *(undefined4 *)(iVar15 + 0x78) = uStack_a58;
      *(undefined4 *)(iVar15 + 0x7c) = uStack_a54;
      func_0x00223030(0x40000000,iVar15 + 0x70);
      __mi__7FVectorCFRC7FVector(&uStack_a70,&fStack_1c0,&fStack_1b0);
      uStack_118._0_4_ = (float)uStack_a68;
      _auStack_120 = uStack_a70;
      uStack_118._4_4_ = uStack_a64;
      func_0x00223030(0x40000000,auStack_120);
      *(float *)(iVar15 + 0x80) = (*(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x84)) / 512.0;
    }
    else {
      FUN_004baab0(0x477fff00,0x477fff00,0x477fff00,0x3f800000,auStack_9d0);
      fStack_1b0 = auStack_9d0._0_4_;
      fStack_1ac = auStack_9d0._4_4_;
      fStack_1a8 = fStack_9c8;
      uStack_1a4 = uStack_9c4;
      FUN_004baab0(0xc77fff00,0xc77fff00,0xc77fff00,0x3f800000,auStack_9e0);
      fStack_1c0 = auStack_9e0._0_4_;
      fStack_1bc = auStack_9e0._4_4_;
      fStack_1b8 = fStack_9d8;
      uStack_1b4 = uStack_9d4;
      for (iVar5 = 0; iVar5 < *(int *)(*(int *)(iVar4 + 0x540) + 8); iVar5 = iVar5 + 1) {
        pauVar13 = (undefined1 (*) [16])
                   (*(int *)(*(int *)(iVar4 + 0x14c) + 0x30) +
                    (uint)*(byte *)(*(int *)(*(int *)(iVar4 + 0x14c) + 0xe4) +
                                   *(short *)(iVar4 + 0xb0 + iVar5 * 2 + 0x498) * 0x110) * 0x1f0 +
                   (bGpffff8240 & 1) * 0x40);
        auStack_200 = *pauVar13;
        auStack_1f0 = pauVar13[1];
        auStack_1e0 = pauVar13[2];
        auStack_1d0 = pauVar13[3];
        FUN_00624f70(*(int *)(*(int *)(iVar4 + 0x14c) + 0xe4) +
                     *(short *)(iVar4 + 0xb0 + iVar5 * 2 + 0x498) * 0x110 + 0x10,auStack_200,
                     &fStack_1b0,&fStack_1c0,0,8);
      }
      if (((long)((ulong)*(byte *)(iVar4 + 0xb1) << 0x3e) < 0) &&
         ((*(short *)(iVar4 + 0xba) == 4 || (*(short *)(iVar4 + 0xba) == 5)))) {
        __pl__7FVectorCFRC7FVector(&uStack_a10,&fStack_1b0,&fStack_1c0);
        fStack_198 = (float)uStack_a08;
        auStack_1a0 = (undefined1  [8])uStack_a10;
        uStack_194 = uStack_a04;
        func_0x00223030(0x40000000,auStack_1a0);
        __mi__7FVectorCFRC7FVector(auStack_a20,&fStack_1c0,&fStack_1b0);
        fStack_190 = auStack_a20._0_4_;
        fStack_18c = auStack_a20._4_4_;
        fStack_188 = fStack_a18;
        fStack_184 = (float)uStack_a14;
        func_0x00223030(0x40000000,&fStack_190);
        pbVar8 = (byte *)FUN_00587900(*(undefined4 *)(iVar4 + 0x14c),0x6e5be8,0);
        pauVar13 = (undefined1 (*) [16])
                   (*(int *)(*(int *)(iVar4 + 0x14c) + 0x30) + (uint)*pbVar8 * 0x1f0 +
                   (bGpffff8240 & 1) * 0x40);
        auStack_200 = *pauVar13;
        auStack_1f0 = pauVar13[1];
        auStack_1e0 = pauVar13[2];
        auStack_1d0 = pauVar13[3];
        FUN_00624f70(pbVar8 + 0x10,auStack_200,&fStack_1b0,&fStack_1c0,1,8);
        __pl__7FVectorCFRC7FVector(auStack_a30,&fStack_1b0,&fStack_1c0);
        fStack_180 = auStack_a30._0_4_;
        fStack_17c = auStack_a30._4_4_;
        fStack_178 = fStack_a28;
        uStack_174 = uStack_a24;
        func_0x00223030(0x40000000,&fStack_180);
        __mi__7FVectorCFRC7FVector(auStack_a40,&fStack_1c0,&fStack_1b0);
        fStack_170 = auStack_a40._0_4_;
        fStack_16c = auStack_a40._4_4_;
        fStack_168 = fStack_a38;
        uStack_164 = uStack_a34;
        func_0x00223030(0x40000000,&fStack_170);
        auVar20._4_4_ = fStack_17c;
        auVar20._0_4_ = fStack_180;
        auVar20._8_4_ = fStack_178;
        auVar20._12_4_ = uStack_174;
        auVar20 = _lqc2(auVar20);
        auVar19 = _lqc2(_auStack_1a0);
        auVar19 = _vsub(auVar19,auVar20);
        _auStack_1a0 = _sqc2(auVar19);
        func_0x00223030(0x40800000,auStack_1a0);
        __pl__7FVectorCFRC7FVector(auStack_a50,auStack_1a0,&fStack_180);
        *(int *)(iVar15 + 0x70) = auStack_a50._0_4_;
        *(int *)(iVar15 + 0x74) = auStack_a50._4_4_;
        *(undefined4 *)(iVar15 + 0x78) = uStack_a48;
        *(undefined4 *)(iVar15 + 0x7c) = uStack_a44;
      }
      else {
        __pl__7FVectorCFRC7FVector(auStack_9f0,&fStack_1b0,&fStack_1c0);
        *(int *)(iVar15 + 0x70) = auStack_9f0._0_4_;
        *(int *)(iVar15 + 0x74) = auStack_9f0._4_4_;
        *(undefined4 *)(iVar15 + 0x78) = uStack_9e8;
        *(undefined4 *)(iVar15 + 0x7c) = uStack_9e4;
        func_0x00223030(0x40000000,iVar15 + 0x70);
        __mi__7FVectorCFRC7FVector(&uStack_a00,&fStack_1c0,&fStack_1b0);
        uStack_118._0_4_ = (float)uStack_9f8;
        _auStack_120 = uStack_a00;
        uStack_118._4_4_ = uStack_9f4;
        func_0x00223030(0x40000000,auStack_120);
      }
      *(float *)(iVar15 + 0x80) = (*(float *)(iVar15 + 0xf0) * *(float *)(iVar15 + 0x84)) / 512.0;
    }
    auVar19 = _vmr32(in_vf0);
    auVar20 = _vmr32(auVar19);
    auVar21 = _vmr32(auVar20);
    auStack_1d0 = _sqc2(in_vf0);
    auStack_1e0 = _sqc2(auVar19);
    auStack_1f0 = _sqc2(auVar20);
    auStack_200 = _sqc2(auVar21);
    if ((long)((ulong)*(byte *)(iVar4 + 0xb1) << 0x3e) < 0) {
      switch(*(undefined2 *)(iVar4 + 0xba)) {
      default:
        uVar11 = func_0x00222e40(0x41ae6666);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 8.4);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 1:
      case 2:
        uVar11 = func_0x00222e40(0x41accccd);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) - 46.9);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 4:
      case 5:
        uVar11 = func_0x00222e40(0x42120000);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) - 25.3);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 7:
      case 8:
        uVar11 = func_0x00222e40(0x41b9999a);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 66.0);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 10:
      case 0xb:
        uVar11 = func_0x00222e40(0xc0400000);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) - 58.1);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 0xd:
      case 0xe:
        uVar11 = func_0x00222e40(0x41bf3333);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) - 22.7);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 0x10:
      case 0x11:
        uVar11 = func_0x00222e40(0xc0d66666);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 3.9);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 0x12:
      case 0x13:
        uVar11 = func_0x00222e40(0x4206cccd);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 26.4);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 0x14:
        uVar11 = func_0x00222e40(0x41ad999a);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) - 50.0);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 0x15:
        uVar11 = func_0x00222e40(0x41e8cccd);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 34.7);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 0x16:
        uVar11 = func_0x00222e40(0x41d9999a);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) - 23.4);
        func_0x00202938(uVar11,auStack_200,auStack_200);
      }
    }
    else {
      switch(*(undefined2 *)(iVar4 + 0x120)) {
      case 0:
        uVar11 = func_0x00222e40(0x41ae6666);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 8.4);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 1:
        uVar11 = func_0x00222e40(0xc0b00000);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 43.3);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 2:
        uVar11 = func_0x00222e40(0x41500000);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 18.0);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 3:
        uVar11 = func_0x00222e40(0x41a80000);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 27.5);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 4:
        uVar11 = func_0x00222e40(0x41680000);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 28.2);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 5:
        uVar11 = func_0x00222e40(0x41dc0000);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 29.0);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 6:
        uVar11 = func_0x00222e40(0xc194cccd);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 4.2);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 7:
        uVar11 = func_0x00222e40(0x40b00000);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 38.0);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 8:
        uVar11 = func_0x00222e40(0xc0066666);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) - 19.6);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 9:
        uVar11 = func_0x00222e40(0x4227999a);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 10.2);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 10:
        uVar11 = func_0x00222e40(0x40b00000);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 34.0);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 0xb:
        uVar11 = func_0x00222e40(0x40800000);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) - 1.7);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 0xc:
        uVar11 = func_0x00222e40(0x422a6666);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 30.7);
        func_0x00202938(uVar11,auStack_200,auStack_200);
        break;
      case 0xd:
        uVar11 = func_0x00222e40(0x4225999a);
        func_0x00202890(uVar11,auStack_200,auStack_200);
        uVar11 = func_0x00222e40(*(float *)(iVar4 + 0x184) + 60.7);
        func_0x00202938(uVar11,auStack_200,auStack_200);
      }
    }
    uVar10 = FUN_004baab0(0,0,-*(float *)(iVar15 + 0x80),0x3f800000,auStack_a90);
    func_0x00222df0(auStack_a80,auStack_200,uVar10);
    *(int *)(iVar15 + 0x50) = auStack_a80._0_4_;
    *(int *)(iVar15 + 0x54) = auStack_a80._4_4_;
    *(undefined4 *)(iVar15 + 0x58) = uStack_a78;
    *(undefined4 *)(iVar15 + 0x5c) = uStack_a74;
    auVar20 = _lqc2(*(undefined1 (*) [16])(iVar15 + 0x70));
    auVar19 = _lqc2(*(undefined1 (*) [16])(iVar15 + 0x50));
    auVar19 = _vadd(auVar19,auVar20);
    auVar19 = _sqc2(auVar19);
    *(undefined1 (*) [16])(iVar15 + 0x50) = auVar19;
    CameraYPosCheck__9BtlCameraFv(param_1);
    if (*(float *)(iVar15 + 0x50) < (-*(float *)(iGpffff8610 + 0x40b4) - 10.0) / 2.0 + 1.0) {
      *(float *)(iVar15 + 0x50) = (-*(float *)(iGpffff8610 + 0x40b4) - 10.0) / 2.0 + 1.0;
    }
    if ((*(float *)(iGpffff8610 + 0x40b4) + 10.0) / 2.0 - 1.0 < *(float *)(iVar15 + 0x50)) {
      *(float *)(iVar15 + 0x50) = (*(float *)(iGpffff8610 + 0x40b4) + 10.0) / 2.0 - 1.0;
    }
    if (*(float *)(iVar15 + 0x58) < (-*(float *)(iGpffff8610 + 0x40bc) - 10.0) / 2.0 + 1.0) {
      *(float *)(iVar15 + 0x58) = (-*(float *)(iGpffff8610 + 0x40bc) - 10.0) / 2.0 + 1.0;
    }
    if ((*(float *)(iGpffff8610 + 0x40bc) + 10.0) / 2.0 - 1.0 < *(float *)(iVar15 + 0x58)) {
      *(float *)(iVar15 + 0x58) = (*(float *)(iGpffff8610 + 0x40bc) + 10.0) / 2.0 - 1.0;
    }
    auVar20 = _lqc2(*(undefined1 (*) [16])(iVar15 + 0x50));
    auVar19 = _lqc2(*(undefined1 (*) [16])(iVar15 + 0x70));
    auVar19 = _vsub(auVar19,auVar20);
    _auStack_120 = _sqc2(auVar19);
    uVar10 = func_0x00222f00(auStack_ab0,auStack_120);
    Get3DAngle__F7FVector(auStack_aa0,uVar10);
    *(float *)(iVar15 + 0x60) = -(float)auStack_aa0._0_8_;
    while (*(float *)(iVar15 + 0x60) < -180.0) {
      *(float *)(iVar15 + 0x60) = *(float *)(iVar15 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar15 + 0x60)) {
      *(float *)(iVar15 + 0x60) = *(float *)(iVar15 + 0x60) - 360.0;
    }
    *(float *)(iVar15 + 100) = -SUB84(auStack_aa0._0_8_,4);
    while (*(float *)(iVar15 + 100) < -180.0) {
      *(float *)(iVar15 + 100) = *(float *)(iVar15 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar15 + 100)) {
      *(float *)(iVar15 + 100) = *(float *)(iVar15 + 100) - 360.0;
    }
    *(undefined4 *)(iVar15 + 0x68) = 0;
    break;
  case 3:
    __pl__7FVectorCFRC7FVector(auStack_ad0,iVar5 + 0x360,iVar5 + 0x160);
    __pl__7FVectorCFRC7FVector(auStack_ae0,iVar4 + 0x360,iVar15 + 0x100);
    __mi__7FVectorCFRC7FVector(&uStack_ac0,auStack_ad0,auStack_ae0);
    uStack_118._0_4_ = (float)uStack_ab8;
    _auStack_120 = uStack_ac0;
    uStack_118._4_4_ = uStack_ab4;
    auStack_11c = (undefined1  [4])((float)((ulong)uStack_ac0 >> 0x20) / 2.0);
    auStack_120 = (undefined1  [4])(int)uStack_ac0;
    fStack_20 = *(float *)(iVar15 + 0xe0);
    fStack_1c = (float)func_0x00222fd0(auStack_120);
    if (fStack_1c < 10.0) {
      fStack_1c = 10.0;
    }
    fStack_20 = fStack_20 + fStack_1c;
    if (fStack_20 < 30.0) {
      fStack_20 = 30.0;
    }
    if (*(int *)(iVar15 + 0xdc) == 0) {
      *(float *)(iVar15 + 0x80) = (fStack_20 * *(float *)(iVar15 + 0x84)) / 512.0;
    }
    else {
      fStack_1c = (fStack_20 * *(float *)(iVar15 + 0x84)) / 512.0 - *(float *)(iVar15 + 0x80);
      *(float *)(iVar15 + 0x80) =
           *(float *)(iVar15 + 0x80) + fStack_1c * 3.75 * *(float *)(iVar15 + 0x24);
    }
    __pl__7FVectorCFRC7FVector(&uStack_af0,iVar5 + 0x3a0,iVar5 + 0x160);
    uStack_118._0_4_ = (float)uStack_ae8;
    _auStack_120 = uStack_af0;
    uStack_118._4_4_ = uStack_ae4;
    if ((((*(char *)(iVar4 + 0xb8) == '\x0e') || (*(char *)(iVar4 + 0xb8) == '\x0f')) &&
        (*(char *)(iVar4 + 0xb9) == '\x01')) && (*(int *)(iVar4 + 0xc0) != 0)) {
      uVar10 = FUN_004baab0(*(undefined4 *)(iVar4 + 0xdc),0,*(undefined4 *)(iVar4 + 0xe0),0x3f800000
                            ,auStack_b10);
      __pl__7FVectorCFRC7FVector(auStack_b00,iVar4 + 0x3a0,uVar10);
      auVar20 = _lqc2(auStack_b00);
      auVar19 = _lqc2(_auStack_120);
      auVar19 = _vsub(auVar19,auVar20);
      _auStack_120 = _sqc2(auVar19);
    }
    else {
      __pl__7FVectorCFRC7FVector(auStack_b20,iVar4 + 0x3a0,iVar15 + 0x100);
      auVar20 = _lqc2(auStack_b20);
      auVar19 = _lqc2(_auStack_120);
      auVar19 = _vsub(auVar19,auVar20);
      _auStack_120 = _sqc2(auVar19);
    }
    uVar10 = func_0x00222f00(auStack_b40,auStack_120);
    Get3DAngle__F7FVector(&uStack_b30,uVar10);
    uStack_108._0_4_ = (float)uStack_b28;
    _auStack_110 = uStack_b30;
    uStack_108._4_4_ = uStack_b24;
    fStack_20 = (float)((ulong)uStack_b30 >> 0x20) + *(float *)(iVar15 + 0xec);
    if (*(int *)(iVar15 + 0xdc) == 0) {
      *(float *)(iVar15 + 0xe4) = fStack_20;
    }
    else {
      for (fStack_20 = fStack_20 - *(float *)(iVar15 + 0xe4); fStack_20 < -180.0;
          fStack_20 = fStack_20 + 360.0) {
      }
      for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
      }
      if (0.0 <= fStack_20) {
        if (*(float *)(iVar15 + 0x24) * 30.0 < fStack_20) {
          fStack_20 = *(float *)(iVar15 + 0x24) * 30.0;
        }
      }
      else if (fStack_20 < *(float *)(iVar15 + 0x24) * -30.0) {
        fStack_20 = *(float *)(iVar15 + 0x24) * -30.0;
      }
      *(float *)(iVar15 + 0xe4) = *(float *)(iVar15 + 0xe4) + fStack_20;
    }
    if (*(float *)(iVar15 + 0xe4) < -180.0) {
      *(float *)(iVar15 + 0xe4) = *(float *)(iVar15 + 0xe4) + 360.0;
    }
    if (180.0 < *(float *)(iVar15 + 0xe4)) {
      *(float *)(iVar15 + 0xe4) = *(float *)(iVar15 + 0xe4) - 360.0;
    }
    if ((*(short *)(*(int *)(iVar4 + 0x14c) + 0x510) == 0x1a) ||
       ((*(short *)(*(int *)(iVar4 + 0x14c) + 0x510) == 0xb &&
        (*(short *)(*(int *)(iVar4 + 0x14c) + 0x512) == 1)))) {
      fStack_20 = 30.0 - *(float *)(iVar15 + 0xe8);
    }
    else if ((*(short *)(*(int *)(iVar4 + 0x14c) + 0x510) == 0x1b) ||
            ((*(short *)(*(int *)(iVar4 + 0x14c) + 0x510) == 0xc &&
             (*(short *)(*(int *)(iVar4 + 0x14c) + 0x512) == 1)))) {
      fStack_20 = -30.0 - *(float *)(iVar15 + 0xe8);
    }
    else {
      fStack_20 = 0.0;
    }
    for (; fStack_20 < -180.0; fStack_20 = fStack_20 + 360.0) {
    }
    for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
    }
    if (0.0 <= fStack_20) {
      if (*(float *)(iVar15 + 0x24) * 45.0 < fStack_20) {
        fStack_20 = *(float *)(iVar15 + 0x24) * 45.0;
      }
    }
    else if (fStack_20 < *(float *)(iVar15 + 0x24) * -45.0) {
      fStack_20 = *(float *)(iVar15 + 0x24) * -45.0;
    }
    *(float *)(iVar15 + 0xe8) = *(float *)(iVar15 + 0xe8) + fStack_20;
    if (*(float *)(iVar15 + 0xe8) < -180.0) {
      *(float *)(iVar15 + 0xe8) = *(float *)(iVar15 + 0xe8) + 360.0;
    }
    if (180.0 < *(float *)(iVar15 + 0xe8)) {
      *(float *)(iVar15 + 0xe8) = *(float *)(iVar15 + 0xe8) - 360.0;
    }
    auVar19 = _vmr32(in_vf0);
    auVar20 = _vmr32(auVar19);
    auVar21 = _vmr32(auVar20);
    auStack_1d0 = _sqc2(in_vf0);
    auStack_1e0 = _sqc2(auVar19);
    auStack_1f0 = _sqc2(auVar20);
    auStack_200 = _sqc2(auVar21);
    uVar11 = func_0x00222e40(*(undefined4 *)(iVar15 + 0xe8));
    func_0x00202890(uVar11,auStack_200,auStack_200);
    uVar11 = func_0x00222e40(-*(float *)(iVar15 + 0xe4));
    func_0x00202938(uVar11,auStack_200,auStack_200);
    if (*(int *)(iVar15 + 0xdc) == 0) {
      uVar10 = FUN_004baab0(0,0,-*(float *)(iVar15 + 0x80),0x3f800000,auStack_b60);
      func_0x00222df0(auStack_b50,auStack_200,uVar10);
      *(int *)(iVar15 + 0x50) = auStack_b50._0_4_;
      *(int *)(iVar15 + 0x54) = auStack_b50._4_4_;
      *(undefined4 *)(iVar15 + 0x58) = uStack_b48;
      *(undefined4 *)(iVar15 + 0x5c) = uStack_b44;
      __pl__7FVectorCFRC7FVector(&uStack_b70,iVar5 + 0x360,iVar5 + 0x160);
      uStack_118._0_4_ = (float)uStack_b68;
      _auStack_120 = uStack_b70;
      uStack_118._4_4_ = uStack_b64;
      __pl__7FVectorCFRC7FVector(auStack_b80,iVar4 + 0x360,iVar15 + 0x100);
      auVar20 = _lqc2(auStack_b80);
      auVar19 = _lqc2(_auStack_120);
      auVar19 = _vsub(auVar19,auVar20);
      _auStack_120 = _sqc2(auVar19);
      func_0x00223030(0x40000000,auStack_120);
      auStack_11c = (undefined1  [4])0x0;
      uVar10 = FUN_004baab0(*(undefined4 *)(iVar15 + 0x100),0,*(undefined4 *)(iVar15 + 0x108),
                            0x3f800000,auStack_ba0);
      __pl__7FVectorCFRC7FVector(auStack_b90,iVar4 + 0x360,uVar10);
      auVar20 = _lqc2(auStack_b90);
      auVar19 = _lqc2(_auStack_120);
      auVar19 = _vadd(auVar19,auVar20);
      _auStack_120 = _sqc2(auVar19);
      auVar20 = _lqc2(_auStack_120);
      auVar19 = _lqc2(*(undefined1 (*) [16])(iVar15 + 0x50));
      auVar19 = _vadd(auVar19,auVar20);
      auVar19 = _sqc2(auVar19);
      *(undefined1 (*) [16])(iVar15 + 0x50) = auVar19;
    }
    else {
      uVar10 = FUN_004baab0(0,0,-*(float *)(iVar15 + 0x80),0x3f800000,auStack_bc0);
      func_0x00222df0(&uStack_bb0,auStack_200,uVar10);
      uStack_118._0_4_ = (float)uStack_ba8;
      _auStack_120 = uStack_bb0;
      uStack_118._4_4_ = uStack_ba4;
      __pl__7FVectorCFRC7FVector(&uStack_bd0,iVar5 + 0x360,iVar5 + 0x160);
      uStack_108._0_4_ = (float)uStack_bc8;
      _auStack_110 = uStack_bd0;
      uStack_108._4_4_ = uStack_bc4;
      __pl__7FVectorCFRC7FVector(auStack_be0,iVar4 + 0x360,iVar15 + 0x100);
      auVar20 = _lqc2(auStack_be0);
      auVar19 = _lqc2(_auStack_110);
      auVar19 = _vsub(auVar19,auVar20);
      _auStack_110 = _sqc2(auVar19);
      func_0x00223030(0x40000000,auStack_110);
      auStack_10c = (undefined1  [4])0x0;
      uVar10 = FUN_004baab0(*(undefined4 *)(iVar15 + 0x100),0,*(undefined4 *)(iVar15 + 0x108),
                            0x3f800000,auStack_c00);
      __pl__7FVectorCFRC7FVector(auStack_bf0,iVar4 + 0x360,uVar10);
      auVar20 = _lqc2(auStack_bf0);
      auVar19 = _lqc2(_auStack_110);
      auVar19 = _vadd(auVar19,auVar20);
      _auStack_110 = _sqc2(auVar19);
      auVar20 = _lqc2(_auStack_110);
      auVar19 = _lqc2(_auStack_120);
      auVar19 = _vadd(auVar19,auVar20);
      auVar19 = _sqc2(auVar19);
      auVar20 = _lqc2(*(undefined1 (*) [16])(iVar15 + 0x50));
      auVar19 = _lqc2(auVar19);
      auVar19 = _vsub(auVar19,auVar20);
      _auStack_120 = _sqc2(auVar19);
      __ml__7FVectorCFf(*(float *)(iVar15 + 0x24) * 12.0,auStack_c10,auStack_120);
      auVar20 = _lqc2(auStack_c10);
      auVar19 = _lqc2(*(undefined1 (*) [16])(iVar15 + 0x50));
      auVar19 = _vadd(auVar19,auVar20);
      auVar19 = _sqc2(auVar19);
      *(undefined1 (*) [16])(iVar15 + 0x50) = auVar19;
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    if (*(float *)(iVar15 + 0x50) < (-*(float *)(iGpffff8610 + 0x40b4) - 10.0) / 2.0 + 1.0) {
      *(float *)(iVar15 + 0x50) = (-*(float *)(iGpffff8610 + 0x40b4) - 10.0) / 2.0 + 1.0;
    }
    if ((*(float *)(iGpffff8610 + 0x40b4) + 10.0) / 2.0 - 1.0 < *(float *)(iVar15 + 0x50)) {
      *(float *)(iVar15 + 0x50) = (*(float *)(iGpffff8610 + 0x40b4) + 10.0) / 2.0 - 1.0;
    }
    if (*(float *)(iVar15 + 0x58) < (-*(float *)(iGpffff8610 + 0x40bc) - 10.0) / 2.0 + 1.0) {
      *(float *)(iVar15 + 0x58) = (-*(float *)(iGpffff8610 + 0x40bc) - 10.0) / 2.0 + 1.0;
    }
    if ((*(float *)(iGpffff8610 + 0x40bc) + 10.0) / 2.0 - 1.0 < *(float *)(iVar15 + 0x58)) {
      *(float *)(iVar15 + 0x58) = (*(float *)(iGpffff8610 + 0x40bc) + 10.0) / 2.0 - 1.0;
    }
    __pl__7FVectorCFRC7FVector(&uStack_c20,iVar5 + 0x160,iVar5 + 0x360);
    uStack_118._0_4_ = (float)uStack_c18;
    _auStack_120 = uStack_c20;
    uStack_118._4_4_ = uStack_c14;
    func_0x00223030(0x40000000,auStack_120);
    auVar20 = _lqc2(*(undefined1 (*) [16])(iVar15 + 0x50));
    auVar19 = _lqc2(_auStack_120);
    auVar19 = _vsub(auVar19,auVar20);
    _auStack_120 = _sqc2(auVar19);
    uVar10 = func_0x00222f00(auStack_c40,auStack_120);
    Get3DAngle__F7FVector(&uStack_c30,uVar10);
    fStack_198 = (float)uStack_c28;
    auStack_1a0 = (undefined1  [8])uStack_c30;
    uStack_194 = uStack_c24;
    while ((float)auStack_1a0._0_4_ < -180.0) {
      auStack_1a0._0_4_ = (float)auStack_1a0._0_4_ + 360.0;
    }
    while (180.0 < (float)auStack_1a0._0_4_) {
      auStack_1a0._0_4_ = (float)auStack_1a0._0_4_ - 360.0;
    }
    while ((float)auStack_1a0._4_4_ < -180.0) {
      auStack_1a0._4_4_ = (float)auStack_1a0._4_4_ + 360.0;
    }
    while (180.0 < (float)auStack_1a0._4_4_) {
      auStack_1a0._4_4_ = (float)auStack_1a0._4_4_ - 360.0;
    }
    FUN_004baab0(0x43b40000,0xc3b40000,0x43b40000,0xc3b40000,auStack_c50);
    fStack_190 = auStack_c50._0_4_;
    fStack_18c = auStack_c50._4_4_;
    fStack_188 = fStack_c48;
    fStack_184 = fStack_c44;
    __pl__7FVectorCFRC7FVector(auStack_c80,iVar5 + 0x160,iVar5 + 0x360);
    uVar10 = FUN_004baab0(-*(float *)(iVar5 + 0x3b0),-*(float *)(iVar5 + 0x3b4),
                          -*(float *)(iVar5 + 0x3b8),0x3f800000,auStack_c90);
    __pl__7FVectorCFRC7FVector(auStack_c70,auStack_c80,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_c60,auStack_c70,iVar15 + 0x50);
    __pl__7FVectorCFRC7FVector(auStack_cc0,iVar5 + 0x160,iVar5 + 0x360);
    uVar10 = FUN_004baab0(*(undefined4 *)(iVar5 + 0x3b0),-*(float *)(iVar5 + 0x3b4),
                          -*(float *)(iVar5 + 0x3b8),0x3f800000,auStack_cd0);
    __pl__7FVectorCFRC7FVector(auStack_cb0,auStack_cc0,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_ca0,auStack_cb0,iVar15 + 0x50);
    __pl__7FVectorCFRC7FVector(auStack_d00,iVar5 + 0x160,iVar5 + 0x360);
    uVar10 = FUN_004baab0(-*(float *)(iVar5 + 0x3b0),*(undefined4 *)(iVar5 + 0x3b4),
                          -*(float *)(iVar5 + 0x3b8),0x3f800000,auStack_d10);
    __pl__7FVectorCFRC7FVector(auStack_cf0,auStack_d00,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_ce0,auStack_cf0,iVar15 + 0x50);
    fStack_100 = auStack_ce0._0_4_;
    fStack_fc = auStack_ce0._4_4_;
    fStack_f8 = (float)uStack_cd8;
    uStack_f4 = uStack_cd4;
    __pl__7FVectorCFRC7FVector(auStack_d40,iVar5 + 0x160,iVar5 + 0x360);
    uVar10 = FUN_004baab0(*(undefined4 *)(iVar5 + 0x3b0),*(undefined4 *)(iVar5 + 0x3b4),
                          -*(float *)(iVar5 + 0x3b8),0x3f800000,auStack_d50);
    __pl__7FVectorCFRC7FVector(auStack_d30,auStack_d40,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_d20,auStack_d30,iVar15 + 0x50);
    fStack_f0 = auStack_d20._0_4_;
    fStack_ec = auStack_d20._4_4_;
    fStack_e8 = (float)uStack_d18;
    uStack_e4 = uStack_d14;
    __pl__7FVectorCFRC7FVector(auStack_d80,iVar5 + 0x160,iVar5 + 0x360);
    uVar10 = FUN_004baab0(-*(float *)(iVar5 + 0x3b0),-*(float *)(iVar5 + 0x3b4),
                          *(undefined4 *)(iVar5 + 0x3b8),0x3f800000,auStack_d90);
    __pl__7FVectorCFRC7FVector(auStack_d70,auStack_d80,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_d60,auStack_d70,iVar15 + 0x50);
    fStack_e0 = auStack_d60._0_4_;
    fStack_dc = auStack_d60._4_4_;
    fStack_d8 = (float)uStack_d58;
    uStack_d4 = uStack_d54;
    __pl__7FVectorCFRC7FVector(auStack_dc0,iVar5 + 0x160,iVar5 + 0x360);
    uVar10 = FUN_004baab0(*(undefined4 *)(iVar5 + 0x3b0),-*(float *)(iVar5 + 0x3b4),
                          *(undefined4 *)(iVar5 + 0x3b8),0x3f800000,auStack_dd0);
    __pl__7FVectorCFRC7FVector(auStack_db0,auStack_dc0,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_da0,auStack_db0,iVar15 + 0x50);
    afStack_d0[0] = auStack_da0._0_4_;
    afStack_d0[1] = auStack_da0._4_4_;
    afStack_d0[2] = (float)uStack_d98;
    afStack_d0[3] = (float)uStack_d94;
    __pl__7FVectorCFRC7FVector(auStack_e00,iVar5 + 0x160,iVar5 + 0x360);
    uVar10 = FUN_004baab0(-*(float *)(iVar5 + 0x3b0),*(undefined4 *)(iVar5 + 0x3b4),
                          *(undefined4 *)(iVar5 + 0x3b8),0x3f800000,auStack_e10);
    __pl__7FVectorCFRC7FVector(auStack_df0,auStack_e00,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_de0,auStack_df0,iVar15 + 0x50);
    afStack_d0[4] = auStack_de0._0_4_;
    afStack_d0[5] = auStack_de0._4_4_;
    afStack_d0[6] = (float)uStack_dd8;
    afStack_d0[7] = (float)uStack_dd4;
    __pl__7FVectorCFRC7FVector(auStack_e40,iVar5 + 0x160,iVar5 + 0x360);
    uVar10 = FUN_004baab0(*(undefined4 *)(iVar5 + 0x3b0),*(undefined4 *)(iVar5 + 0x3b4),
                          *(undefined4 *)(iVar5 + 0x3b8),0x3f800000,auStack_e50);
    __pl__7FVectorCFRC7FVector(auStack_e30,auStack_e40,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_e20,auStack_e30,iVar15 + 0x50);
    afStack_d0[8] = auStack_e20._0_4_;
    afStack_d0[9] = auStack_e20._4_4_;
    afStack_d0[10] = (float)uStack_e18;
    afStack_d0[0xb] = (float)uStack_e14;
    for (iVar4 = 0; iVar4 < 8; iVar4 = iVar4 + 1) {
      uVar10 = func_0x00222f00(auStack_e70,auStack_120 + iVar4 * 0x10);
      Get3DAngle__F7FVector(auStack_e60,uVar10);
      fStack_180 = auStack_e60._0_4_;
      fStack_17c = auStack_e60._4_4_;
      fStack_178 = fStack_e58;
      uStack_174 = uStack_e54;
      for (fStack_20 = fStack_180 - (float)auStack_1a0._0_4_; fStack_20 < -180.0;
          fStack_20 = fStack_20 + 360.0) {
      }
      for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
      }
      if (fStack_20 < fStack_190) {
        fStack_190 = fStack_20;
      }
      if (fStack_18c < fStack_20) {
        fStack_18c = fStack_20;
      }
      for (fStack_20 = fStack_17c - (float)auStack_1a0._4_4_; fStack_20 < -180.0;
          fStack_20 = fStack_20 + 360.0) {
      }
      for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
      }
      if (fStack_20 < fStack_188) {
        fStack_188 = fStack_20;
      }
      if (fStack_184 < fStack_20) {
        fStack_184 = fStack_20;
      }
    }
    uVar10 = FUN_004baab0(fStack_190,fStack_188,0,0x3f800000,auStack_e90);
    __pl__7FVectorCFRC7FVector(auStack_e80,auStack_1a0,uVar10);
    fStack_160 = auStack_e80._0_4_;
    fStack_15c = auStack_e80._4_4_;
    uStack_158 = uStack_e78;
    uStack_154 = uStack_e74;
    uVar10 = FUN_004baab0(fStack_18c,fStack_184,0,0x3f800000,auStack_eb0);
    __pl__7FVectorCFRC7FVector(auStack_ea0,auStack_1a0,uVar10);
    for (fStack_20 = (float)auStack_ea0._0_8_ - fStack_160; fStack_20 < -180.0;
        fStack_20 = fStack_20 + 360.0) {
    }
    for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
    }
    if (*(int *)(iVar15 + 0xdc) == 0) {
      *(float *)(iVar15 + 0x60) = -(fStack_160 + fStack_20 / 2.0);
    }
    else {
      for (fStack_20 = -(fStack_160 + fStack_20 / 2.0) - *(float *)(iVar15 + 0x60);
          fStack_20 < -180.0; fStack_20 = fStack_20 + 360.0) {
      }
      for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
      }
      *(float *)(iVar15 + 0x60) =
           *(float *)(iVar15 + 0x60) + fStack_20 * 4.0 * *(float *)(iVar15 + 0x24);
    }
    while (*(float *)(iVar15 + 0x60) < -180.0) {
      *(float *)(iVar15 + 0x60) = *(float *)(iVar15 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar15 + 0x60)) {
      *(float *)(iVar15 + 0x60) = *(float *)(iVar15 + 0x60) - 360.0;
    }
    for (fStack_20 = SUB84(auStack_ea0._0_8_,4) - fStack_15c; fStack_20 < -180.0;
        fStack_20 = fStack_20 + 360.0) {
    }
    for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
    }
    if (*(int *)(iVar15 + 0xdc) == 0) {
      *(float *)(iVar15 + 100) = -(fStack_15c + fStack_20 / 2.0);
    }
    else {
      for (fStack_20 = -(fStack_15c + fStack_20 / 2.0) - *(float *)(iVar15 + 100);
          fStack_20 < -180.0; fStack_20 = fStack_20 + 360.0) {
      }
      for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
      }
      *(float *)(iVar15 + 100) =
           *(float *)(iVar15 + 100) + fStack_20 * 5.0 * *(float *)(iVar15 + 0x24);
    }
    while (*(float *)(iVar15 + 100) < -180.0) {
      *(float *)(iVar15 + 100) = *(float *)(iVar15 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar15 + 100)) {
      *(float *)(iVar15 + 100) = *(float *)(iVar15 + 100) - 360.0;
    }
    *(undefined4 *)(iVar15 + 0x68) = 0;
    *(undefined4 *)(iVar15 + 0xdc) = 1;
    break;
  case 4:
    __pl__7FVectorCFRC7FVector(&uStack_ec0,iVar5 + 0x160,iVar5 + 0x3a0);
    uStack_118._0_4_ = (float)uStack_eb8;
    _auStack_120 = uStack_ec0;
    uStack_118._4_4_ = uStack_eb4;
    __pl__7FVectorCFRC7FVector(auStack_ed0,iVar4 + 0x160,iVar4 + 0x3a0);
    auVar20 = _lqc2(auStack_ed0);
    auVar19 = _lqc2(_auStack_120);
    auVar19 = _vsub(auVar19,auVar20);
    _auStack_120 = _sqc2(auVar19);
    FUN_004baab0(*(undefined4 *)(iGpffff8610 + 0x40b4),0,*(undefined4 *)(iGpffff8610 + 0x40bc),
                 0x3f800000,auStack_ee0);
    fVar17 = (float)func_0x00222fd0(auStack_120);
    fVar18 = (float)func_0x00222fd0(auStack_110);
    *(float *)(iVar15 + 0x84) = (fVar17 / (fVar18 * 0.75) + 1.2) * 512.0;
    uVar10 = func_0x00222f00(auStack_f00,auStack_120);
    Get3DAngle__F7FVector(&uStack_ef0,uVar10);
    uStack_108._0_4_ = (float)uStack_ee8;
    _auStack_110 = uStack_ef0;
    uStack_108._4_4_ = uStack_ee4;
    fStack_20 = *(float *)(iVar4 + 0x3b4) * 0.75;
    if (fStack_20 < 4.0) {
      fStack_20 = 4.0;
    }
    fVar17 = (float)func_0x00222fd0(iVar4 + 0x3b0);
    fStack_1c = (*(float *)(iVar15 + 0x84) * (*(float *)(iVar4 + 0x354) + fVar17 + 20.0)) / 512.0;
    fStack_18 = -(float)auStack_110;
    if ((fStack_18 <= 40.0) && (fStack_18 = fStack_18 * 1.25 - 10.0, fStack_18 < -10.0)) {
      fStack_18 = -10.0;
    }
    auVar19 = _vmr32(in_vf0);
    auVar20 = _vmr32(auVar19);
    auVar21 = _vmr32(auVar20);
    auStack_1d0 = _sqc2(in_vf0);
    auStack_1e0 = _sqc2(auVar19);
    auStack_1f0 = _sqc2(auVar20);
    auStack_200 = _sqc2(auVar21);
    uVar11 = func_0x00222e40(fStack_18);
    func_0x00202890(uVar11,auStack_200,auStack_200);
    uVar11 = func_0x00222e40(-(float)auStack_10c);
    func_0x00202938(uVar11,auStack_200,auStack_200);
    uVar10 = FUN_004baab0(0,0,-fStack_1c,0x3f800000,auStack_f20);
    func_0x00222df0(auStack_f10,auStack_200,uVar10);
    __pl__7FVectorCFRC7FVector(auStack_f50,auStack_120,iVar4 + 0x160);
    __pl__7FVectorCFRC7FVector(auStack_f40,auStack_f50,iVar4 + 0x3a0);
    uVar10 = FUN_004baab0(0,-*(float *)(iVar4 + 0x3b4) - fStack_20,0,0x3f800000,auStack_f60);
    __pl__7FVectorCFRC7FVector(auStack_f30,auStack_f40,uVar10);
    *(int *)(iVar15 + 0x50) = auStack_f30._0_4_;
    *(int *)(iVar15 + 0x54) = auStack_f30._4_4_;
    *(undefined4 *)(iVar15 + 0x58) = uStack_f28;
    *(undefined4 *)(iVar15 + 0x5c) = uStack_f24;
    if (-10.0 < *(float *)(iVar15 + 0x54)) {
      *(undefined4 *)(iVar15 + 0x54) = 0xc1200000;
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    if (*(float *)(iVar15 + 0x50) < (-*(float *)(iGpffff8610 + 0x40b4) - 10.0) / 2.0 + 1.0) {
      *(float *)(iVar15 + 0x50) = (-*(float *)(iGpffff8610 + 0x40b4) - 10.0) / 2.0 + 1.0;
    }
    if ((*(float *)(iGpffff8610 + 0x40b4) + 10.0) / 2.0 - 1.0 < *(float *)(iVar15 + 0x50)) {
      *(float *)(iVar15 + 0x50) = (*(float *)(iGpffff8610 + 0x40b4) + 10.0) / 2.0 - 1.0;
    }
    if (*(float *)(iVar15 + 0x58) < (-*(float *)(iGpffff8610 + 0x40bc) - 10.0) / 2.0 + 1.0) {
      *(float *)(iVar15 + 0x58) = (-*(float *)(iGpffff8610 + 0x40bc) - 10.0) / 2.0 + 1.0;
    }
    if ((*(float *)(iGpffff8610 + 0x40bc) + 10.0) / 2.0 - 1.0 < *(float *)(iVar15 + 0x58)) {
      *(float *)(iVar15 + 0x58) = (*(float *)(iGpffff8610 + 0x40bc) + 10.0) / 2.0 - 1.0;
    }
    __pl__7FVectorCFRC7FVector(auStack_f90,iVar5 + 0x160,iVar5 + 0x3a0);
    uVar10 = FUN_004baab0(0,-*(float *)(iVar5 + 0x3b4),0,0x3f800000,auStack_fa0);
    __pl__7FVectorCFRC7FVector(auStack_f80,auStack_f90,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_f70,auStack_f80,iVar15 + 0x50);
    __pl__7FVectorCFRC7FVector(auStack_fd0,iVar5 + 0x160,iVar5 + 0x3a0);
    uVar10 = FUN_004baab0(0,*(undefined4 *)(iVar5 + 0x3b4),0,0x3f800000,auStack_fe0);
    __pl__7FVectorCFRC7FVector(auStack_fc0,auStack_fd0,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_fb0,auStack_fc0,iVar15 + 0x50);
    __pl__7FVectorCFRC7FVector(auStack_1010,iVar4 + 0x160,iVar4 + 0x3a0);
    uVar10 = FUN_004baab0(0,-*(float *)(iVar4 + 0x3b4),0,0x3f800000,auStack_1020);
    __pl__7FVectorCFRC7FVector(auStack_1000,auStack_1010,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_ff0,auStack_1000,iVar15 + 0x50);
    fStack_100 = auStack_ff0._0_4_;
    fStack_fc = auStack_ff0._4_4_;
    fStack_f8 = (float)uStack_fe8;
    uStack_f4 = uStack_fe4;
    __pl__7FVectorCFRC7FVector(auStack_1050,iVar4 + 0x160,iVar4 + 0x3a0);
    uVar10 = FUN_004baab0(0,*(float *)(iVar4 + 0x3b4) * 0.5,0,0x3f800000,auStack_1060);
    __pl__7FVectorCFRC7FVector(auStack_1040,auStack_1050,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_1030,auStack_1040,iVar15 + 0x50);
    fStack_f0 = auStack_1030._0_4_;
    fStack_ec = auStack_1030._4_4_;
    fStack_e8 = (float)uStack_1028;
    uStack_e4 = uStack_1024;
    uVar10 = func_0x00222f00(auStack_1080,auStack_120);
    Get3DAngle__F7FVector(auStack_1070,uVar10);
    fStack_e0 = auStack_1070._0_4_;
    fStack_dc = auStack_1070._4_4_;
    fStack_d8 = (float)uStack_1068;
    uStack_d4 = uStack_1064;
    uVar10 = func_0x00222f00(auStack_10a0,auStack_110);
    Get3DAngle__F7FVector(auStack_1090,uVar10);
    afStack_d0[0] = auStack_1090._0_4_;
    afStack_d0[1] = auStack_1090._4_4_;
    afStack_d0[2] = (float)uStack_1088;
    afStack_d0[3] = (float)uStack_1084;
    uVar10 = func_0x00222f00(auStack_10c0,&fStack_100);
    Get3DAngle__F7FVector(auStack_10b0,uVar10);
    afStack_d0[4] = auStack_10b0._0_4_;
    afStack_d0[5] = auStack_10b0._4_4_;
    afStack_d0[6] = (float)uStack_10a8;
    afStack_d0[7] = (float)uStack_10a4;
    uVar10 = func_0x00222f00(auStack_10e0,&fStack_f0);
    Get3DAngle__F7FVector(auStack_10d0,uVar10);
    afStack_d0[8] = (float)auStack_10d0._0_4_;
    afStack_d0[9] = (float)auStack_10d0._4_4_;
    afStack_d0[10] = (float)uStack_10c8;
    afStack_d0[0xb] = (float)uStack_10c4;
    for (; fStack_e0 < -180.0; fStack_e0 = fStack_e0 + 360.0) {
    }
    for (; 180.0 < fStack_e0; fStack_e0 = fStack_e0 - 360.0) {
    }
    fStack_20 = fStack_e0;
    fStack_1c = fStack_e0;
    for (iVar4 = 5; iVar4 < 8; iVar4 = iVar4 + 1) {
      while (*(float *)(auStack_120 + iVar4 * 0x10) < -180.0) {
        *(float *)(auStack_120 + iVar4 * 0x10) = *(float *)(auStack_120 + iVar4 * 0x10) + 360.0;
      }
      while (180.0 < *(float *)(auStack_120 + iVar4 * 0x10)) {
        *(float *)(auStack_120 + iVar4 * 0x10) = *(float *)(auStack_120 + iVar4 * 0x10) - 360.0;
      }
      if (*(float *)(auStack_120 + iVar4 * 0x10) < fStack_20) {
        fStack_20 = *(float *)(auStack_120 + iVar4 * 0x10);
      }
      if (fStack_1c < *(float *)(auStack_120 + iVar4 * 0x10)) {
        fStack_1c = *(float *)(auStack_120 + iVar4 * 0x10);
      }
    }
    for (fStack_1c = fStack_1c - fStack_20; fStack_1c < -180.0; fStack_1c = fStack_1c + 360.0) {
    }
    for (; 180.0 < fStack_1c; fStack_1c = fStack_1c - 360.0) {
    }
    *(float *)(iVar15 + 0x60) = -(fStack_20 + fStack_1c / 2.0);
    while (*(float *)(iVar15 + 0x60) < -180.0) {
      *(float *)(iVar15 + 0x60) = *(float *)(iVar15 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar15 + 0x60)) {
      *(float *)(iVar15 + 0x60) = *(float *)(iVar15 + 0x60) - 360.0;
    }
    for (fStack_20 = fStack_dc - afStack_d0[5]; fStack_20 < -180.0; fStack_20 = fStack_20 + 360.0) {
    }
    for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
    }
    *(float *)(iVar15 + 100) = -(afStack_d0[5] + fStack_20 / 2.0);
    while (*(float *)(iVar15 + 100) < -180.0) {
      *(float *)(iVar15 + 100) = *(float *)(iVar15 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar15 + 100)) {
      *(float *)(iVar15 + 100) = *(float *)(iVar15 + 100) - 360.0;
    }
    *(undefined4 *)(iVar15 + 0x68) = 0;
    break;
  case 5:
    __pl__7FVectorCFRC7FVector(&uStack_10f0,iVar5 + 0x160,iVar5 + 0x3a0);
    uStack_118._0_4_ = (float)uStack_10e8;
    _auStack_120 = uStack_10f0;
    uStack_118._4_4_ = uStack_10e4;
    __pl__7FVectorCFRC7FVector(auStack_1100,iVar4 + 0x160,iVar4 + 0x3a0);
    auVar20 = _lqc2(auStack_1100);
    auVar19 = _lqc2(_auStack_120);
    auVar19 = _vsub(auVar19,auVar20);
    _auStack_120 = _sqc2(auVar19);
    FUN_004baab0(*(undefined4 *)(iGpffff8610 + 0x40b4),0,*(undefined4 *)(iGpffff8610 + 0x40bc),
                 0x3f800000,auStack_1110);
    fVar17 = (float)func_0x00222fd0(auStack_120);
    fVar18 = (float)func_0x00222fd0(auStack_110);
    *(float *)(iVar15 + 0x84) = (fVar17 / (fVar18 * 0.75) + 1.2) * 512.0;
    uVar10 = func_0x00222f00(auStack_1130,auStack_120);
    Get3DAngle__F7FVector(auStack_1120,uVar10);
    auVar19 = _vmr32(in_vf0);
    auVar20 = _vmr32(auVar19);
    auVar21 = _vmr32(auVar20);
    auStack_1d0 = _sqc2(in_vf0);
    auStack_1e0 = _sqc2(auVar19);
    auStack_1f0 = _sqc2(auVar20);
    auStack_200 = _sqc2(auVar21);
    uVar11 = func_0x00222e40(-fStack_111c);
    func_0x00202938(uVar11,auStack_200,auStack_200);
    uVar10 = FUN_004baab0(*(float *)(iVar4 + 0x354) * 3.0,0,0,0x3f800000,auStack_1150);
    func_0x00222df0(auStack_1140,auStack_200,uVar10);
    fStack_100 = auStack_1140._0_4_;
    fStack_fc = auStack_1140._4_4_;
    fStack_f8 = fStack_1138;
    uStack_f4 = uStack_1134;
    uVar10 = FUN_004baab0(-*(float *)(iVar4 + 0x354) * 3.0,0,0,0x3f800000,auStack_1170);
    func_0x00222df0(auStack_1160,auStack_200,uVar10);
    fStack_f0 = auStack_1160._0_4_;
    fStack_ec = auStack_1160._4_4_;
    fStack_e8 = fStack_1158;
    uStack_e4 = uStack_1154;
    __pl__7FVectorCFRC7FVector(auStack_1190,iVar4 + 0x160,iVar4 + 0x3a0);
    __pl__7FVectorCFRC7FVector(auStack_1180,auStack_1190,&fStack_100);
    __pl__7FVectorCFRC7FVector(auStack_11b0,iVar5 + 0x160,iVar5 + 0x3a0);
    __mi__7FVectorCFRC7FVector(auStack_11a0,auStack_11b0,auStack_120);
    uVar10 = func_0x00222f00(auStack_11d0,auStack_110);
    Get3DAngle__F7FVector(&uStack_11c0,uVar10);
    uStack_108._0_4_ = (float)uStack_11b8;
    _auStack_110 = uStack_11c0;
    uStack_108._4_4_ = uStack_11b4;
    fStack_20 = -(float)uStack_11c0;
    if ((fStack_20 <= 40.0) && (fStack_20 = fStack_20 * 1.25 - 10.0, fStack_20 < -10.0)) {
      fStack_20 = -10.0;
    }
    fVar17 = (float)func_0x00222fd0(iVar4 + 0x3b0);
    fStack_1c = (*(float *)(iVar15 + 0x84) * (*(float *)(iVar4 + 0x354) + fVar17 + 20.0)) / 512.0;
    auVar19 = _vmr32(in_vf0);
    auVar20 = _vmr32(auVar19);
    auVar21 = _vmr32(auVar20);
    auStack_1d0 = _sqc2(in_vf0);
    auStack_1e0 = _sqc2(auVar19);
    auStack_1f0 = _sqc2(auVar20);
    auStack_200 = _sqc2(auVar21);
    uVar11 = func_0x00222e40(fStack_20);
    func_0x00202890(uVar11,auStack_200,auStack_200);
    uVar11 = func_0x00222e40(-(float)auStack_10c);
    func_0x00202938(uVar11,auStack_200,auStack_200);
    uVar10 = FUN_004baab0(0,0,-fStack_1c,0x3f800000,auStack_11f0);
    func_0x00222df0(auStack_11e0,auStack_200,uVar10);
    __pl__7FVectorCFRC7FVector(&uStack_1200,auStack_120,auStack_110);
    fStack_198 = (float)uStack_11f8;
    auStack_1a0 = (undefined1  [8])uStack_1200;
    uStack_194 = uStack_11f4;
    __pl__7FVectorCFRC7FVector(auStack_1220,iVar4 + 0x160,iVar4 + 0x3a0);
    __pl__7FVectorCFRC7FVector(&uStack_1210,auStack_1220,&fStack_f0);
    uStack_118._0_4_ = (float)uStack_1208;
    _auStack_120 = uStack_1210;
    uStack_118._4_4_ = uStack_1204;
    __pl__7FVectorCFRC7FVector(auStack_1240,iVar5 + 0x160,iVar5 + 0x3a0);
    __mi__7FVectorCFRC7FVector(auStack_1230,auStack_1240,auStack_120);
    uVar10 = func_0x00222f00(auStack_1260,auStack_110);
    Get3DAngle__F7FVector(&uStack_1250,uVar10);
    uStack_108._0_4_ = (float)uStack_1248;
    _auStack_110 = uStack_1250;
    uStack_108._4_4_ = uStack_1244;
    fStack_20 = -(float)uStack_1250;
    if ((fStack_20 <= 40.0) && (fStack_20 = fStack_20 * 1.25 - 10.0, fStack_20 < -10.0)) {
      fStack_20 = -10.0;
    }
    fVar17 = (float)func_0x00222fd0(iVar4 + 0x3b0);
    fStack_1c = (*(float *)(iVar15 + 0x84) * (*(float *)(iVar4 + 0x354) + fVar17 + 20.0)) / 512.0;
    auVar19 = _vmr32(in_vf0);
    auVar20 = _vmr32(auVar19);
    auVar21 = _vmr32(auVar20);
    auStack_1d0 = _sqc2(in_vf0);
    auStack_1e0 = _sqc2(auVar19);
    auStack_1f0 = _sqc2(auVar20);
    auStack_200 = _sqc2(auVar21);
    uVar11 = func_0x00222e40(fStack_20);
    func_0x00202890(uVar11,auStack_200,auStack_200);
    uVar11 = func_0x00222e40(-(float)auStack_10c);
    func_0x00202938(uVar11,auStack_200,auStack_200);
    uVar10 = FUN_004baab0(0,0,-fStack_1c,0x3f800000,auStack_1280);
    func_0x00222df0(&uStack_1270,auStack_200,uVar10);
    uStack_108._0_4_ = (float)uStack_1268;
    _auStack_110 = uStack_1270;
    uStack_108._4_4_ = uStack_1264;
    __pl__7FVectorCFRC7FVector(auStack_1290,auStack_120,auStack_110);
    fStack_190 = auStack_1290._0_4_;
    fStack_18c = auStack_1290._4_4_;
    fStack_188 = (float)uStack_1288;
    fStack_184 = (float)uStack_1284;
    iVar7 = *(int *)(iVar15 + 0xdc);
    if (iVar7 == 2) {
      *(float *)(iVar15 + 0x50) = fStack_190;
      *(float *)(iVar15 + 0x54) = fStack_18c;
      *(undefined4 *)(iVar15 + 0x58) = uStack_1288;
      *(undefined4 *)(iVar15 + 0x5c) = uStack_1284;
    }
    else if (iVar7 == 1) {
      *(int *)(iVar15 + 0x50) = auStack_1a0._0_4_;
      *(int *)(iVar15 + 0x54) = auStack_1a0._4_4_;
      *(float *)(iVar15 + 0x58) = fStack_198;
      *(undefined4 *)(iVar15 + 0x5c) = uStack_194;
    }
    else if (iVar7 == 0) {
      __pl__7FVectorCFRC7FVector(auStack_12b0,iVar4 + 0x160,iVar4 + 0x3a0);
      __mi__7FVectorCFRC7FVector(auStack_12a0,auStack_12b0,auStack_1a0);
      fStack_20 = (float)func_0x00222fd0(auStack_120);
      uVar10 = func_0x00222f00(auStack_12d0,auStack_120);
      Get3DAngle__F7FVector(&uStack_12c0,uVar10);
      uStack_118._0_4_ = fStack_20;
      _auStack_120 = uStack_12c0;
      uStack_118._4_4_ = uStack_12b4;
      __pl__7FVectorCFRC7FVector(auStack_12f0,iVar5 + 0x160,iVar5 + 0x3a0);
      __mi__7FVectorCFRC7FVector(&uStack_12e0,auStack_12f0,auStack_1a0);
      uStack_108._0_4_ = (float)uStack_12d8;
      _auStack_110 = uStack_12e0;
      uStack_108._4_4_ = uStack_12d4;
      _auStack_110 = uStack_12e0 & 0xffffffff;
      fStack_20 = (float)func_0x00222fd0(auStack_110);
      uVar10 = func_0x00222f00(auStack_1310,auStack_110);
      Get3DAngle__F7FVector(&uStack_1300,uVar10);
      uStack_108._0_4_ = fStack_20;
      _auStack_110 = uStack_1300;
      uStack_108._4_4_ = uStack_12f4;
      __pl__7FVectorCFRC7FVector(auStack_1330,iVar4 + 0x160,iVar4 + 0x3a0);
      __mi__7FVectorCFRC7FVector(auStack_1320,auStack_1330,&fStack_190);
      fStack_f8 = (float)uStack_1318;
      uStack_f4 = uStack_1314;
      fStack_fc = 0.0;
      fStack_20 = (float)func_0x00222fd0(&fStack_100);
      uVar10 = func_0x00222f00(auStack_1350,&fStack_100);
      Get3DAngle__F7FVector(auStack_1340,uVar10);
      fStack_100 = (float)auStack_1340._0_8_;
      fStack_fc = SUB84(auStack_1340._0_8_,4);
      uStack_f4 = uStack_1334;
      fStack_f8 = fStack_20;
      __pl__7FVectorCFRC7FVector(auStack_1370,iVar5 + 0x160,iVar5 + 0x3a0);
      __mi__7FVectorCFRC7FVector(auStack_1360,auStack_1370,&fStack_190);
      fStack_e8 = (float)uStack_1358;
      uStack_e4 = uStack_1354;
      fStack_ec = 0.0;
      fStack_20 = (float)func_0x00222fd0(&fStack_f0);
      uVar10 = func_0x00222f00(auStack_1390,&fStack_f0);
      Get3DAngle__F7FVector(auStack_1380,uVar10);
      fStack_f0 = (float)auStack_1380._0_8_;
      fStack_ec = SUB84(auStack_1380._0_8_,4);
      uStack_e4 = uStack_1374;
      fStack_e8 = fStack_20;
      iVar7 = 0;
      iVar16 = 0;
      for (iVar14 = 0; iVar14 < 0xc; iVar14 = iVar14 + 1) {
        if (((((*(byte *)(iGpffff8610 + iVar14 * 0x510 + 0xb0) & 1) != 0) &&
             ((long)((ulong)*(byte *)(iGpffff8610 + iVar14 * 0x510 + 0xb0) << 0x3e) < 0)) &&
            (-1 < (long)((ulong)*(byte *)(iGpffff8610 + iVar14 * 0x510 + 0xb2) << 0x3c))) &&
           ((iVar14 != *(int *)(iVar15 + 0xd0) && (iVar14 != *(int *)(iVar15 + 0xd4))))) {
          __pl__7FVectorCFRC7FVector
                    (auStack_13b0,iGpffff8610 + iVar14 * 0x510 + 0x160,
                     iGpffff8610 + iVar14 * 0x510 + 0x3a0);
          __mi__7FVectorCFRC7FVector(auStack_13a0,auStack_13b0,auStack_1a0);
          fStack_e0 = auStack_13a0._0_4_;
          fStack_dc = auStack_13a0._4_4_;
          fStack_d8 = (float)uStack_1398;
          uStack_d4 = uStack_1394;
          fStack_20 = (float)func_0x00222fd0(&fStack_e0);
          uVar10 = func_0x00222f00(auStack_13d0,&fStack_e0);
          Get3DAngle__F7FVector(auStack_13c0,uVar10);
          fStack_e0 = auStack_13c0._0_4_;
          fStack_dc = auStack_13c0._4_4_;
          fStack_d8 = (float)uStack_13b8;
          uStack_d4 = uStack_13b4;
          if (fStack_20 < (float)uStack_118 + *(float *)(iVar4 + 0x354) + 10.0) {
            for (fStack_1c = fStack_dc - (float)auStack_11c; fStack_1c < -180.0;
                fStack_1c = fStack_1c + 360.0) {
            }
            for (; 180.0 < fStack_1c; fStack_1c = fStack_1c - 360.0) {
            }
            if ((-60.0 <= fStack_1c) && (fStack_1c <= 60.0)) {
              iVar7 = iVar7 + 1;
            }
          }
          if (fStack_20 < (float)uStack_108 + *(float *)(iVar5 + 0x354) + 10.0) {
            for (fStack_1c = fStack_dc - (float)auStack_10c; fStack_1c < -180.0;
                fStack_1c = fStack_1c + 360.0) {
            }
            for (; 180.0 < fStack_1c; fStack_1c = fStack_1c - 360.0) {
            }
            if ((-60.0 <= fStack_1c) && (fStack_1c <= 60.0)) {
              iVar7 = iVar7 + 1;
            }
          }
          __pl__7FVectorCFRC7FVector
                    (auStack_13f0,iGpffff8610 + iVar14 * 0x510 + 0x160,
                     iGpffff8610 + iVar14 * 0x510 + 0x3a0);
          __mi__7FVectorCFRC7FVector(auStack_13e0,auStack_13f0,&fStack_190);
          fStack_e0 = auStack_13e0._0_4_;
          fStack_dc = auStack_13e0._4_4_;
          fStack_d8 = (float)uStack_13d8;
          uStack_d4 = uStack_13d4;
          fStack_20 = (float)func_0x00222fd0(&fStack_e0);
          uVar10 = func_0x00222f00(auStack_1410,&fStack_e0);
          Get3DAngle__F7FVector(auStack_1400,uVar10);
          fStack_e0 = auStack_1400._0_4_;
          fStack_dc = auStack_1400._4_4_;
          fStack_d8 = fStack_13f8;
          uStack_d4 = uStack_13f4;
          if (fStack_20 < fStack_f8 + *(float *)(iVar4 + 0x354) + 10.0) {
            for (fStack_1c = fStack_dc - fStack_fc; fStack_1c < -180.0;
                fStack_1c = fStack_1c + 360.0) {
            }
            for (; 180.0 < fStack_1c; fStack_1c = fStack_1c - 360.0) {
            }
            if ((-60.0 <= fStack_1c) && (fStack_1c <= 60.0)) {
              iVar16 = iVar16 + 1;
            }
          }
          if (fStack_20 < fStack_e8 + *(float *)(iVar5 + 0x354) + 10.0) {
            for (fStack_1c = fStack_dc - fStack_ec; fStack_1c < -180.0;
                fStack_1c = fStack_1c + 360.0) {
            }
            for (; 180.0 < fStack_1c; fStack_1c = fStack_1c - 360.0) {
            }
            if ((-60.0 <= fStack_1c) && (fStack_1c <= 60.0)) {
              iVar16 = iVar16 + 1;
            }
          }
        }
      }
      if (iVar7 < iVar16) {
        *(int *)(iVar15 + 0x50) = auStack_1a0._0_4_;
        *(int *)(iVar15 + 0x54) = auStack_1a0._4_4_;
        *(float *)(iVar15 + 0x58) = fStack_198;
        *(undefined4 *)(iVar15 + 0x5c) = uStack_194;
        *(undefined4 *)(iVar15 + 0xdc) = 1;
      }
      else if (iVar16 < iVar7) {
        *(float *)(iVar15 + 0x50) = fStack_190;
        *(float *)(iVar15 + 0x54) = fStack_18c;
        *(float *)(iVar15 + 0x58) = fStack_188;
        *(float *)(iVar15 + 0x5c) = fStack_184;
        *(undefined4 *)(iVar15 + 0xdc) = 2;
      }
      else {
        fStack_20 = (float)func_0x00222fd0(auStack_1a0);
        fStack_1c = (float)func_0x00222fd0(&fStack_190);
        if (fStack_20 < fStack_18) {
          *(int *)(iVar15 + 0x50) = auStack_1a0._0_4_;
          *(int *)(iVar15 + 0x54) = auStack_1a0._4_4_;
          *(float *)(iVar15 + 0x58) = fStack_198;
          *(undefined4 *)(iVar15 + 0x5c) = uStack_194;
          *(undefined4 *)(iVar15 + 0xdc) = 1;
        }
        else {
          *(float *)(iVar15 + 0x50) = fStack_190;
          *(float *)(iVar15 + 0x54) = fStack_18c;
          *(float *)(iVar15 + 0x58) = fStack_188;
          *(float *)(iVar15 + 0x5c) = fStack_184;
          *(undefined4 *)(iVar15 + 0xdc) = 2;
        }
      }
    }
    if (-5.0 < *(float *)(iVar15 + 0x54)) {
      *(undefined4 *)(iVar15 + 0x54) = 0xc0a00000;
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    if (*(float *)(iVar15 + 0x50) < (-*(float *)(iGpffff8610 + 0x40b4) - 10.0) / 2.0 + 1.0) {
      *(float *)(iVar15 + 0x50) = (-*(float *)(iGpffff8610 + 0x40b4) - 10.0) / 2.0 + 1.0;
    }
    if ((*(float *)(iGpffff8610 + 0x40b4) + 10.0) / 2.0 - 1.0 < *(float *)(iVar15 + 0x50)) {
      *(float *)(iVar15 + 0x50) = (*(float *)(iGpffff8610 + 0x40b4) + 10.0) / 2.0 - 1.0;
    }
    if (*(float *)(iVar15 + 0x58) < (-*(float *)(iGpffff8610 + 0x40bc) - 10.0) / 2.0 + 1.0) {
      *(float *)(iVar15 + 0x58) = (-*(float *)(iGpffff8610 + 0x40bc) - 10.0) / 2.0 + 1.0;
    }
    if ((*(float *)(iGpffff8610 + 0x40bc) + 10.0) / 2.0 - 1.0 < *(float *)(iVar15 + 0x58)) {
      *(float *)(iVar15 + 0x58) = (*(float *)(iGpffff8610 + 0x40bc) + 10.0) / 2.0 - 1.0;
    }
    __pl__7FVectorCFRC7FVector(auStack_1440,iVar5 + 0x160,iVar5 + 0x3a0);
    uVar10 = FUN_004baab0(0,-*(float *)(iVar5 + 0x3b4),0,0x3f800000,auStack_1450);
    __pl__7FVectorCFRC7FVector(auStack_1430,auStack_1440,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_1420,auStack_1430,iVar15 + 0x50);
    __pl__7FVectorCFRC7FVector(auStack_1480,iVar5 + 0x160,iVar5 + 0x3a0);
    uVar10 = FUN_004baab0(0,*(undefined4 *)(iVar5 + 0x3b4),0,0x3f800000,auStack_1490);
    __pl__7FVectorCFRC7FVector(auStack_1470,auStack_1480,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_1460,auStack_1470,iVar15 + 0x50);
    __pl__7FVectorCFRC7FVector(auStack_14c0,iVar4 + 0x160,iVar4 + 0x3a0);
    uVar10 = FUN_004baab0(0,-*(float *)(iVar4 + 0x3b4),0,0x3f800000,auStack_14d0);
    __pl__7FVectorCFRC7FVector(auStack_14b0,auStack_14c0,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_14a0,auStack_14b0,iVar15 + 0x50);
    fStack_100 = auStack_14a0._0_4_;
    fStack_fc = auStack_14a0._4_4_;
    fStack_f8 = (float)uStack_1498;
    uStack_f4 = uStack_1494;
    __pl__7FVectorCFRC7FVector(auStack_1500,iVar4 + 0x160,iVar4 + 0x3a0);
    uVar10 = FUN_004baab0(0,*(float *)(iVar4 + 0x3b4) * 0.5,0,0x3f800000,auStack_1510);
    __pl__7FVectorCFRC7FVector(auStack_14f0,auStack_1500,uVar10);
    __mi__7FVectorCFRC7FVector(auStack_14e0,auStack_14f0,iVar15 + 0x50);
    fStack_f0 = auStack_14e0._0_4_;
    fStack_ec = auStack_14e0._4_4_;
    fStack_e8 = (float)uStack_14d8;
    uStack_e4 = uStack_14d4;
    uVar10 = func_0x00222f00(auStack_1530,auStack_120);
    Get3DAngle__F7FVector(auStack_1520,uVar10);
    fStack_e0 = auStack_1520._0_4_;
    fStack_dc = auStack_1520._4_4_;
    fStack_d8 = (float)uStack_1518;
    uStack_d4 = uStack_1514;
    uVar10 = func_0x00222f00(auStack_1550,auStack_110);
    Get3DAngle__F7FVector(auStack_1540,uVar10);
    afStack_d0[0] = auStack_1540._0_4_;
    afStack_d0[1] = auStack_1540._4_4_;
    afStack_d0[2] = (float)uStack_1538;
    afStack_d0[3] = (float)uStack_1534;
    uVar10 = func_0x00222f00(auStack_1570,&fStack_100);
    Get3DAngle__F7FVector(auStack_1560,uVar10);
    afStack_d0[4] = auStack_1560._0_4_;
    afStack_d0[5] = auStack_1560._4_4_;
    afStack_d0[6] = (float)uStack_1558;
    afStack_d0[7] = (float)uStack_1554;
    uVar10 = func_0x00222f00(auStack_1590,&fStack_f0);
    Get3DAngle__F7FVector(auStack_1580,uVar10);
    afStack_d0[8] = (float)auStack_1580._0_4_;
    afStack_d0[9] = (float)auStack_1580._4_4_;
    afStack_d0[10] = (float)uStack_1578;
    afStack_d0[0xb] = (float)uStack_1574;
    for (; fStack_e0 < -180.0; fStack_e0 = fStack_e0 + 360.0) {
    }
    for (; 180.0 < fStack_e0; fStack_e0 = fStack_e0 - 360.0) {
    }
    fStack_20 = fStack_e0;
    fStack_1c = fStack_e0;
    for (iVar4 = 5; iVar4 < 8; iVar4 = iVar4 + 1) {
      while (*(float *)(auStack_120 + iVar4 * 0x10) < -180.0) {
        *(float *)(auStack_120 + iVar4 * 0x10) = *(float *)(auStack_120 + iVar4 * 0x10) + 360.0;
      }
      while (180.0 < *(float *)(auStack_120 + iVar4 * 0x10)) {
        *(float *)(auStack_120 + iVar4 * 0x10) = *(float *)(auStack_120 + iVar4 * 0x10) - 360.0;
      }
      if (*(float *)(auStack_120 + iVar4 * 0x10) < fStack_20) {
        fStack_20 = *(float *)(auStack_120 + iVar4 * 0x10);
      }
      if (fStack_1c < *(float *)(auStack_120 + iVar4 * 0x10)) {
        fStack_1c = *(float *)(auStack_120 + iVar4 * 0x10);
      }
    }
    for (fStack_1c = fStack_1c - fStack_20; fStack_1c < -180.0; fStack_1c = fStack_1c + 360.0) {
    }
    for (; 180.0 < fStack_1c; fStack_1c = fStack_1c - 360.0) {
    }
    *(float *)(iVar15 + 0x60) = -(fStack_20 + fStack_1c / 2.0);
    while (*(float *)(iVar15 + 0x60) < -180.0) {
      *(float *)(iVar15 + 0x60) = *(float *)(iVar15 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar15 + 0x60)) {
      *(float *)(iVar15 + 0x60) = *(float *)(iVar15 + 0x60) - 360.0;
    }
    for (fStack_20 = fStack_dc - afStack_d0[5]; fStack_20 < -180.0; fStack_20 = fStack_20 + 360.0) {
    }
    for (; 180.0 < fStack_20; fStack_20 = fStack_20 - 360.0) {
    }
    *(float *)(iVar15 + 100) = -(afStack_d0[5] + fStack_20 / 2.0);
    while (*(float *)(iVar15 + 100) < -180.0) {
      *(float *)(iVar15 + 100) = *(float *)(iVar15 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar15 + 100)) {
      *(float *)(iVar15 + 100) = *(float *)(iVar15 + 100) - 360.0;
    }
    *(undefined4 *)(iVar15 + 0x68) = 0;
  }
  return;
}


/* FUN_005c3520 = fusion camera */

void FUN_005c3520(undefined8 param_1)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  float fVar4;
  undefined4 uVar5;
  float fVar6;
  undefined1 in_vf0 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [8];
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  float fStack_d8;
  undefined4 uStack_d4;
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [8];
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [8];
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined1 auStack_70 [8];
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  iVar3 = (int)param_1;
  iVar1 = iGpffff8610 + *(int *)(iVar3 + 0xd0) * 0x510;
  if (*(short *)(iVar3 + 0x1e) == 0) {
    *(undefined4 *)(iVar3 + 0xe0) = 0;
    *(undefined4 *)(iVar3 + 0xe4) = 0xc1c80000;
    *(undefined4 *)(iVar3 + 0xe8) = 0xc2200000;
    *(undefined4 *)(iVar3 + 0xec) = 0x41dc0000;
    *(undefined2 *)(iVar3 + 0x1e) = 1;
  }
  fVar6 = *(float *)(iVar1 + 0x184) + *(float *)(iVar3 + 0xe4);
  if (fVar6 < -180.0) {
    fVar6 = fVar6 + 360.0;
  }
  if (180.0 < fVar6) {
    fVar6 = fVar6 - 360.0;
  }
  auVar7 = _lqc2(*(undefined1 (*) [16])(iVar1 + 0x160));
  auVar8 = _lqc2(*(undefined1 (*) [16])(iVar1 + 0x360));
  auVar7 = _vadd(auVar7,auVar8);
  auStack_130 = _sqc2(auVar7);
  func_0x00222f00(auStack_70,auStack_130);
  *(int *)(iVar3 + 0x70) = auStack_70._0_4_;
  *(int *)(iVar3 + 0x74) = auStack_70._4_4_;
  *(undefined4 *)(iVar3 + 0x78) = uStack_68;
  *(undefined4 *)(iVar3 + 0x7c) = uStack_64;
  fVar4 = (float)func_0x00222fd0(iVar1 + 0x370);
  *(float *)(iVar3 + 0x80) =
       (*(float *)(iVar3 + 0x84) * (*(float *)(iVar3 + 0xec) + *(float *)(iVar1 + 0x354) + fVar4)) /
       512.0;
  auVar7 = _vmr32(in_vf0);
  auVar8 = _vmr32(auVar7);
  auVar9 = _vmr32(auVar8);
  _sqc2(in_vf0);
  _sqc2(auVar7);
  _sqc2(auVar8);
  _sqc2(auVar9);
  auVar7 = _vmr32(in_vf0);
  auVar8 = _vmr32(auVar7);
  auVar9 = _vmr32(auVar8);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar7);
  auStack_30 = _sqc2(auVar8);
  auStack_40 = _sqc2(auVar9);
  uStack_60 = in_zero_lo;
  uStack_5c = in_zero_hi;
  uStack_58 = in_zero_udw;
  uStack_54 = in_register_0000000c;
  uVar5 = func_0x00222e40(*(undefined4 *)(iVar3 + 0xe8));
  func_0x00202890(uVar5,auStack_40,auStack_40);
  uVar5 = func_0x00222e40(fVar6);
  func_0x00202938(uVar5,auStack_40,auStack_40);
  if (*(int *)(iVar3 + 0xdc) == 0) {
    fStack_98 = -*(float *)(iVar3 + 0x80);
    uStack_a0 = 0;
    uStack_9c = 0;
    uStack_94 = 0x3f800000;
    func_0x00222df0(auStack_90,auStack_40,&uStack_a0);
    auVar7 = _lqc2(auStack_90);
    auVar8 = _lqc2(*(undefined1 (*) [16])(iVar3 + 0x70));
    auVar7 = _vadd(auVar7,auVar8);
    auStack_140 = _sqc2(auVar7);
    func_0x00222f00(auStack_80,auStack_140);
    *(int *)(iVar3 + 0x50) = auStack_80._0_4_;
    *(int *)(iVar3 + 0x54) = auStack_80._4_4_;
    *(undefined4 *)(iVar3 + 0x58) = uStack_78;
    *(undefined4 *)(iVar3 + 0x5c) = uStack_74;
  }
  else {
    fStack_d8 = -*(float *)(iVar3 + 0x80);
    uStack_e0 = 0;
    uStack_dc = 0;
    uStack_d4 = 0x3f800000;
    func_0x00222df0(auStack_d0,auStack_40,&uStack_e0);
    auVar7 = _lqc2(auStack_d0);
    auVar8 = _lqc2(*(undefined1 (*) [16])(iVar3 + 0x70));
    auVar7 = _vadd(auVar7,auVar8);
    auStack_170 = _sqc2(auVar7);
    func_0x00222f00(auStack_c0,auStack_170);
    auVar7 = _lqc2(auStack_c0);
    auVar8 = _lqc2(*(undefined1 (*) [16])(iVar3 + 0x50));
    auVar7 = _vsub(auVar7,auVar8);
    auStack_150 = _sqc2(auVar7);
    func_0x00222f00(auStack_b0,auStack_150);
    uStack_60 = auStack_b0._0_4_;
    uStack_5c = auStack_b0._4_4_;
    uStack_58 = uStack_a8;
    uStack_54 = uStack_a4;
    func_0x00223010((*(float *)(iVar3 + 0x24) * 30.0) / 4.0,&uStack_60);
    auVar7._4_4_ = uStack_5c;
    auVar7._0_4_ = uStack_60;
    auVar7._8_4_ = uStack_58;
    auVar7._12_4_ = uStack_54;
    auVar8 = _lqc2(auVar7);
    auVar7 = _lqc2(*(undefined1 (*) [16])(iVar3 + 0x50));
    auVar7 = _vadd(auVar7,auVar8);
    auVar7 = _sqc2(auVar7);
    *(undefined1 (*) [16])(iVar3 + 0x50) = auVar7;
  }
  CameraYPosCheck__9BtlCameraFv(param_1);
  auVar7 = _lqc2(*(undefined1 (*) [16])(iVar1 + 0x160));
  auVar8 = _lqc2(*(undefined1 (*) [16])(iVar1 + 0x360));
  auVar7 = _vadd(auVar7,auVar8);
  auStack_180 = _sqc2(auVar7);
  func_0x00222f00(auStack_100,auStack_180);
  auVar7 = _lqc2(auStack_100);
  auVar8 = _lqc2(*(undefined1 (*) [16])(iVar3 + 0x50));
  auVar7 = _vsub(auVar7,auVar8);
  auStack_160 = _sqc2(auVar7);
  func_0x00222f00(auStack_f0,auStack_160);
  uStack_60 = auStack_f0._0_4_;
  uStack_5c = auStack_f0._4_4_;
  uStack_58 = uStack_e8;
  uStack_54 = uStack_e4;
  uVar2 = func_0x00222f00(auStack_120,&uStack_60);
  Get3DAngle__F7FVector(auStack_110,uVar2);
  if (*(int *)(iVar3 + 0xdc) == 0) {
    *(float *)(iVar3 + 0x60) = -(float)auStack_110._0_8_;
    *(float *)(iVar3 + 100) = -SUB84(auStack_110._0_8_,4);
  }
  else {
    for (fVar6 = -(float)auStack_110._0_8_ - *(float *)(iVar3 + 0x60); fVar6 < -180.0;
        fVar6 = fVar6 + 360.0) {
    }
    for (; 180.0 <= fVar6; fVar6 = fVar6 - 360.0) {
    }
    *(float *)(iVar3 + 0x60) =
         *(float *)(iVar3 + 0x60) + fVar6 * ((*(float *)(iVar3 + 0x24) * 30.0) / 4.0);
    for (fVar6 = -SUB84(auStack_110._0_8_,4) - *(float *)(iVar3 + 100); fVar6 < -180.0;
        fVar6 = fVar6 + 360.0) {
    }
    for (; 180.0 <= fVar6; fVar6 = fVar6 - 360.0) {
    }
    *(float *)(iVar3 + 100) =
         *(float *)(iVar3 + 100) + fVar6 * ((*(float *)(iVar3 + 0x24) * 30.0) / 4.0);
  }
  while (*(float *)(iVar3 + 0x60) < -180.0) {
    *(float *)(iVar3 + 0x60) = *(float *)(iVar3 + 0x60) + 360.0;
  }
  while (180.0 < *(float *)(iVar3 + 0x60)) {
    *(float *)(iVar3 + 0x60) = *(float *)(iVar3 + 0x60) - 360.0;
  }
  while (*(float *)(iVar3 + 100) < -180.0) {
    *(float *)(iVar3 + 100) = *(float *)(iVar3 + 100) + 360.0;
  }
  while (180.0 < *(float *)(iVar3 + 100)) {
    *(float *)(iVar3 + 100) = *(float *)(iVar3 + 100) - 360.0;
  }
  *(undefined4 *)(iVar3 + 0x68) = 0;
  *(undefined4 *)(iVar3 + 0xdc) = 1;
  return;
}

