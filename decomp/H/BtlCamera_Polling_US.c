/* Raw Ghidra decompilation (SH2US_BATTLE.BIN, retail) of BtlCamera::Polling (US 0x00592390, 0x1dd90 bytes; the JP function cannot be decompiled).
 * Mode numbers are the retail ones for the jump-table cases (the retail build inserted two cases: JP 0x18/0x19/0x1a -> US 0x1b/0x1c/0x1d, fusion = FUN_005c3520).
 * Separate functions: case 0x13 = FUN_005ad3b0 (attack camera, f_005ad3b0.c), 0x14 = FUN_005b6fa0, 0x15 = FUN_005bd330.  Used by port/crates/sh2_battle/src/camera.rs. */

/* WARNING: Removing unreachable block (ram,0x005a2ae0) */
/* WARNING: Removing unreachable block (ram,0x00598da4) */
/* WARNING: Removing unreachable block (ram,0x00598df8) */
/* WARNING: Removing unreachable block (ram,0x0059b86c) */
/* WARNING: Removing unreachable block (ram,0x0059b818) */
/* WARNING: Removing unreachable block (ram,0x0059f0b0) */
/* WARNING: Removing unreachable block (ram,0x0059f104) */
/* WARNING: Removing unreachable block (ram,0x005a1e90) */
/* WARNING: Removing unreachable block (ram,0x005a0464) */
/* WARNING: Removing unreachable block (ram,0x005a0410) */
/* WARNING: Removing unreachable block (ram,0x0059c9a0) */
/* WARNING: Removing unreachable block (ram,0x0059c9f4) */
/* WARNING: Removing unreachable block (ram,0x00598f64) */
/* WARNING: Removing unreachable block (ram,0x00598f10) */
/* WARNING: Removing unreachable block (ram,0x005979d0) */
/* WARNING: Removing unreachable block (ram,0x00597a24) */
/* WARNING: Removing unreachable block (ram,0x005a2b34) */
/* WARNING: Removing unreachable block (ram,0x005a1ee4) */
/* WARNING: Switch with 1 destination removed at 0x00596a54 : 23 cases all go to same destination */
/* WARNING: Switch with 1 destination removed at 0x0059743c : 23 cases all go to same destination */

undefined4 Polling__9BtlCameraFv(undefined8 param_1)

{
  short sVar1;
  ushort uVar2;
  byte bVar3;
  bool bVar4;
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  int iVar5;
  undefined1 *puVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  undefined4 uVar9;
  float *pfVar10;
  undefined1 (*pauVar11) [16];
  int iVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  long lVar16;
  int iVar17;
  int iVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  undefined4 uVar24;
  float unaff_f20;
  undefined1 in_vf0 [16];
  undefined1 auVar25 [16];
  undefined1 auVar26 [16];
  undefined1 auVar27 [16];
  undefined1 auStack_3730 [8];
  undefined4 uStack_3728;
  undefined4 uStack_3724;
  undefined1 auStack_3720 [16];
  undefined1 auStack_3710 [8];
  undefined4 uStack_3708;
  undefined4 uStack_3704;
  undefined1 auStack_3700 [16];
  undefined8 uStack_36f0;
  undefined4 uStack_36e8;
  undefined4 uStack_36e4;
  undefined8 uStack_36e0;
  undefined4 uStack_36d8;
  undefined4 uStack_36d4;
  undefined1 auStack_36d0 [16];
  undefined1 auStack_36c0 [16];
  undefined8 uStack_36b0;
  undefined4 uStack_36a8;
  undefined4 uStack_36a4;
  undefined1 auStack_36a0 [8];
  undefined4 uStack_3698;
  undefined4 uStack_3694;
  undefined1 auStack_3690 [8];
  undefined4 uStack_3688;
  undefined4 uStack_3684;
  undefined1 auStack_3680 [8];
  undefined4 uStack_3678;
  undefined4 uStack_3674;
  undefined1 auStack_3670 [16];
  undefined1 auStack_3660 [8];
  undefined4 uStack_3658;
  undefined4 uStack_3654;
  undefined1 auStack_3650 [8];
  undefined4 uStack_3648;
  undefined4 uStack_3644;
  undefined1 auStack_3640 [16];
  undefined1 auStack_3630 [8];
  undefined4 uStack_3628;
  undefined4 uStack_3624;
  undefined1 auStack_3620 [16];
  ulong uStack_3610;
  undefined4 uStack_3608;
  undefined4 uStack_3604;
  undefined8 uStack_3600;
  undefined4 uStack_35f8;
  undefined4 uStack_35f4;
  undefined1 auStack_35f0 [8];
  undefined4 uStack_35e8;
  undefined4 uStack_35e4;
  undefined1 auStack_35e0 [16];
  undefined8 uStack_35d0;
  undefined4 uStack_35c8;
  undefined4 uStack_35c4;
  undefined1 auStack_35c0 [16];
  undefined1 auStack_35b0 [8];
  undefined4 uStack_35a8;
  undefined4 uStack_35a4;
  undefined1 auStack_35a0 [16];
  undefined1 auStack_3590 [8];
  undefined4 uStack_3588;
  undefined4 uStack_3584;
  undefined1 auStack_3580 [16];
  undefined1 auStack_3570 [8];
  undefined4 uStack_3568;
  undefined4 uStack_3564;
  undefined1 auStack_3560 [16];
  undefined1 auStack_3550 [8];
  undefined4 uStack_3548;
  undefined4 uStack_3544;
  undefined1 auStack_3540 [16];
  undefined1 auStack_3530 [16];
  undefined1 auStack_3520 [8];
  float fStack_3518;
  undefined4 uStack_3514;
  undefined1 auStack_3510 [16];
  undefined1 auStack_3500 [16];
  undefined1 auStack_34f0 [8];
  float fStack_34e8;
  undefined4 uStack_34e4;
  undefined1 auStack_34e0 [16];
  undefined1 auStack_34d0 [16];
  undefined1 auStack_34c0 [16];
  undefined8 uStack_34b0;
  undefined4 uStack_34a8;
  undefined4 uStack_34a4;
  undefined1 auStack_34a0 [16];
  undefined1 auStack_3490 [16];
  undefined1 auStack_3480 [16];
  undefined8 uStack_3470;
  undefined4 uStack_3468;
  undefined4 uStack_3464;
  undefined1 auStack_3460 [16];
  undefined1 auStack_3450 [8];
  float fStack_3448;
  undefined4 uStack_3444;
  undefined1 auStack_3440 [16];
  undefined1 auStack_3430 [16];
  undefined1 auStack_3420 [16];
  undefined8 uStack_3410;
  undefined4 uStack_3408;
  undefined4 uStack_3404;
  undefined1 auStack_3400 [16];
  undefined8 uStack_33f0;
  undefined4 uStack_33e8;
  undefined4 uStack_33e4;
  undefined1 auStack_33e0 [16];
  undefined8 uStack_33d0;
  undefined4 uStack_33c8;
  undefined4 uStack_33c4;
  undefined1 auStack_33c0 [8];
  float fStack_33b8;
  float fStack_33b4;
  undefined1 auStack_33b0 [8];
  undefined4 uStack_33a8;
  float fStack_33a4;
  undefined1 auStack_33a0 [8];
  undefined4 uStack_3398;
  undefined4 uStack_3394;
  undefined1 auStack_3390 [16];
  undefined8 uStack_3380;
  undefined4 uStack_3378;
  undefined4 uStack_3374;
  undefined8 uStack_3370;
  undefined4 uStack_3368;
  undefined4 uStack_3364;
  undefined1 auStack_3360 [16];
  undefined1 auStack_3350 [16];
  undefined8 uStack_3340;
  undefined4 uStack_3338;
  undefined4 uStack_3334;
  undefined1 auStack_3330 [16];
  undefined1 auStack_3320 [16];
  undefined1 auStack_3310 [8];
  undefined4 uStack_3308;
  undefined4 uStack_3304;
  undefined1 auStack_3300 [8];
  float fStack_32f8;
  float fStack_32f4;
  undefined1 auStack_32f0 [8];
  undefined4 uStack_32e8;
  float fStack_32e4;
  undefined1 auStack_32e0 [8];
  undefined4 uStack_32d8;
  undefined4 uStack_32d4;
  undefined1 auStack_32d0 [16];
  undefined1 auStack_32c0 [8];
  float fStack_32b8;
  undefined4 uStack_32b4;
  undefined1 auStack_32b0 [16];
  undefined1 auStack_32a0 [8];
  float fStack_3298;
  undefined4 uStack_3294;
  undefined1 auStack_3290 [16];
  undefined8 uStack_3280;
  undefined4 uStack_3278;
  undefined4 uStack_3274;
  undefined8 uStack_3270;
  undefined4 uStack_3268;
  undefined4 uStack_3264;
  undefined1 auStack_3260 [16];
  undefined1 auStack_3250 [8];
  undefined4 uStack_3248;
  undefined4 uStack_3244;
  undefined1 auStack_3240 [16];
  undefined1 auStack_3230 [8];
  float fStack_3228;
  float fStack_3224;
  undefined1 auStack_3220 [16];
  ulong uStack_3210;
  undefined4 uStack_3208;
  undefined4 uStack_3204;
  undefined1 auStack_3200 [16];
  undefined1 auStack_31f0 [8];
  float fStack_31e8;
  undefined4 uStack_31e4;
  undefined1 auStack_31e0 [16];
  undefined1 auStack_31d0 [8];
  float fStack_31c8;
  undefined4 uStack_31c4;
  undefined1 auStack_31c0 [16];
  undefined1 auStack_31b0 [16];
  undefined1 auStack_31a0 [16];
  undefined1 auStack_3190 [16];
  undefined1 auStack_3180 [8];
  undefined4 uStack_3178;
  undefined4 uStack_3174;
  undefined1 auStack_3170 [16];
  undefined1 auStack_3160 [8];
  float fStack_3158;
  float fStack_3154;
  undefined1 auStack_3150 [16];
  ulong uStack_3140;
  undefined4 uStack_3138;
  undefined4 uStack_3134;
  undefined1 auStack_3130 [16];
  undefined1 auStack_3120 [8];
  float fStack_3118;
  undefined4 uStack_3114;
  undefined1 auStack_3110 [16];
  undefined1 auStack_3100 [8];
  float fStack_30f8;
  undefined4 uStack_30f4;
  undefined1 auStack_30f0 [16];
  undefined8 uStack_30e0;
  undefined4 uStack_30d8;
  undefined4 uStack_30d4;
  undefined1 auStack_30d0 [16];
  undefined8 uStack_30c0;
  undefined4 uStack_30b8;
  undefined4 uStack_30b4;
  undefined1 auStack_30b0 [16];
  undefined1 auStack_30a0 [16];
  undefined1 auStack_3090 [16];
  undefined1 auStack_3080 [16];
  undefined8 uStack_3070;
  undefined4 uStack_3068;
  undefined4 uStack_3064;
  undefined1 auStack_3060 [16];
  undefined8 uStack_3050;
  undefined4 uStack_3048;
  undefined4 uStack_3044;
  undefined1 auStack_3040 [16];
  undefined1 auStack_3030 [16];
  undefined1 auStack_3020 [16];
  undefined8 uStack_3010;
  undefined4 uStack_3008;
  undefined4 uStack_3004;
  undefined1 auStack_3000 [16];
  undefined1 auStack_2ff0 [8];
  undefined4 uStack_2fe8;
  undefined4 uStack_2fe4;
  undefined1 auStack_2fe0 [16];
  undefined8 uStack_2fd0;
  undefined4 uStack_2fc8;
  undefined4 uStack_2fc4;
  undefined1 auStack_2fc0 [16];
  undefined8 uStack_2fb0;
  undefined4 uStack_2fa8;
  undefined4 uStack_2fa4;
  undefined1 auStack_2fa0 [16];
  undefined8 uStack_2f90;
  undefined4 uStack_2f88;
  undefined4 uStack_2f84;
  undefined1 auStack_2f80 [16];
  undefined8 uStack_2f70;
  undefined4 uStack_2f68;
  undefined4 uStack_2f64;
  undefined1 auStack_2f60 [16];
  undefined8 uStack_2f50;
  undefined4 uStack_2f48;
  undefined4 uStack_2f44;
  undefined1 auStack_2f40 [16];
  undefined1 auStack_2f30 [8];
  undefined4 uStack_2f28;
  undefined4 uStack_2f24;
  undefined1 auStack_2f20 [16];
  undefined1 auStack_2f10 [8];
  undefined4 uStack_2f08;
  undefined4 uStack_2f04;
  undefined1 auStack_2f00 [16];
  undefined1 auStack_2ef0 [8];
  undefined4 uStack_2ee8;
  undefined4 uStack_2ee4;
  undefined1 auStack_2ee0 [16];
  undefined1 auStack_2ed0 [8];
  undefined4 uStack_2ec8;
  undefined4 uStack_2ec4;
  undefined1 auStack_2ec0 [16];
  undefined1 auStack_2eb0 [16];
  undefined1 auStack_2ea0 [16];
  undefined1 auStack_2e90 [8];
  float fStack_2e88;
  undefined4 uStack_2e84;
  undefined1 auStack_2e80 [16];
  undefined1 auStack_2e70 [16];
  undefined1 auStack_2e60 [16];
  undefined1 auStack_2e50 [8];
  float fStack_2e48;
  undefined4 uStack_2e44;
  undefined1 auStack_2e40 [16];
  undefined1 auStack_2e30 [16];
  undefined1 auStack_2e20 [16];
  undefined8 uStack_2e10;
  undefined4 uStack_2e08;
  undefined4 uStack_2e04;
  undefined1 auStack_2e00 [16];
  undefined1 auStack_2df0 [16];
  undefined1 auStack_2de0 [16];
  undefined8 uStack_2dd0;
  undefined4 uStack_2dc8;
  undefined4 uStack_2dc4;
  undefined1 auStack_2dc0 [16];
  undefined1 auStack_2db0 [8];
  undefined4 uStack_2da8;
  undefined4 uStack_2da4;
  undefined1 auStack_2da0 [16];
  undefined1 auStack_2d90 [8];
  undefined4 uStack_2d88;
  undefined4 uStack_2d84;
  undefined1 auStack_2d80 [16];
  undefined1 auStack_2d70 [8];
  undefined4 uStack_2d68;
  undefined4 uStack_2d64;
  undefined1 auStack_2d60 [16];
  undefined1 auStack_2d50 [8];
  undefined4 uStack_2d48;
  undefined4 uStack_2d44;
  undefined1 auStack_2d40 [16];
  undefined1 auStack_2d30 [12];
  undefined4 uStack_2d24;
  undefined1 auStack_2d20 [16];
  undefined1 auStack_2d10 [8];
  undefined4 uStack_2d08;
  undefined4 uStack_2d04;
  undefined1 auStack_2d00 [16];
  undefined1 auStack_2cf0 [12];
  undefined4 uStack_2ce4;
  undefined1 auStack_2ce0 [16];
  undefined1 auStack_2cd0 [8];
  undefined4 uStack_2cc8;
  undefined4 uStack_2cc4;
  undefined1 auStack_2cc0 [16];
  undefined8 uStack_2cb0;
  undefined4 uStack_2ca4;
  undefined1 auStack_2ca0 [16];
  ulong uStack_2c90;
  undefined4 uStack_2c88;
  undefined4 uStack_2c84;
  undefined1 auStack_2c80 [16];
  undefined8 uStack_2c70;
  undefined4 uStack_2c64;
  undefined1 auStack_2c60 [16];
  undefined1 auStack_2c50 [16];
  undefined8 uStack_2c40;
  undefined4 uStack_2c38;
  undefined4 uStack_2c34;
  undefined1 auStack_2c30 [16];
  undefined1 auStack_2c20 [16];
  undefined1 auStack_2c10 [16];
  undefined8 uStack_2c00;
  undefined4 uStack_2bf8;
  undefined4 uStack_2bf4;
  undefined1 auStack_2bf0 [16];
  undefined1 auStack_2be0 [16];
  undefined1 auStack_2bd0 [16];
  undefined1 auStack_2bc0 [16];
  undefined8 uStack_2bb0;
  undefined4 uStack_2ba8;
  undefined4 uStack_2ba4;
  undefined1 auStack_2ba0 [16];
  undefined1 auStack_2b90 [16];
  undefined1 auStack_2b80 [16];
  undefined8 uStack_2b70;
  undefined4 uStack_2b68;
  undefined4 uStack_2b64;
  undefined1 auStack_2b60 [16];
  undefined1 auStack_2b50 [16];
  undefined1 auStack_2b40 [16];
  undefined1 auStack_2b30 [16];
  undefined1 auStack_2b20 [16];
  undefined1 auStack_2b10 [8];
  undefined4 uStack_2b08;
  undefined4 uStack_2b04;
  undefined1 auStack_2b00 [16];
  undefined1 auStack_2af0 [8];
  undefined4 uStack_2ae8;
  undefined4 uStack_2ae4;
  undefined1 auStack_2ae0 [16];
  undefined1 auStack_2ad0 [4];
  float fStack_2acc;
  undefined1 auStack_2ac0 [16];
  undefined8 uStack_2ab0;
  undefined4 uStack_2aa8;
  undefined4 uStack_2aa4;
  undefined1 auStack_2aa0 [16];
  undefined1 auStack_2a90 [16];
  undefined1 auStack_2a80 [16];
  undefined1 auStack_2a70 [8];
  undefined4 uStack_2a68;
  undefined4 uStack_2a64;
  undefined1 auStack_2a60 [16];
  undefined8 uStack_2a50;
  undefined4 uStack_2a48;
  undefined4 uStack_2a44;
  undefined1 auStack_2a40 [16];
  undefined8 uStack_2a30;
  undefined4 uStack_2a28;
  undefined4 uStack_2a24;
  undefined8 uStack_2a20;
  undefined4 uStack_2a18;
  undefined4 uStack_2a14;
  undefined1 auStack_2a10 [16];
  undefined8 uStack_2a00;
  undefined4 uStack_29f8;
  undefined4 uStack_29f4;
  undefined1 auStack_29f0 [16];
  undefined8 uStack_29e0;
  undefined4 uStack_29d8;
  undefined4 uStack_29d4;
  undefined1 auStack_29d0 [16];
  undefined8 uStack_29c0;
  undefined4 uStack_29b8;
  undefined4 uStack_29b4;
  undefined8 uStack_29b0;
  undefined4 uStack_29a8;
  undefined4 uStack_29a4;
  undefined1 auStack_29a0 [16];
  undefined1 auStack_2990 [16];
  undefined8 uStack_2980;
  float fStack_2978;
  undefined4 uStack_2974;
  undefined1 auStack_2970 [8];
  undefined4 uStack_2968;
  undefined4 uStack_2964;
  undefined1 auStack_2960 [16];
  undefined1 auStack_2950 [8];
  undefined4 uStack_2948;
  undefined4 uStack_2944;
  undefined1 auStack_2940 [16];
  undefined1 auStack_2930 [8];
  undefined4 uStack_2928;
  undefined4 uStack_2924;
  undefined1 auStack_2920 [16];
  undefined1 auStack_2910 [8];
  undefined4 uStack_2908;
  undefined4 uStack_2904;
  undefined1 auStack_2900 [8];
  undefined4 uStack_28f8;
  undefined4 uStack_28f4;
  undefined1 auStack_28f0 [8];
  undefined4 uStack_28e8;
  undefined4 uStack_28e4;
  undefined1 auStack_28e0 [16];
  undefined1 auStack_28d0 [8];
  undefined4 uStack_28c8;
  undefined4 uStack_28c4;
  undefined1 auStack_28c0 [16];
  undefined1 auStack_28b0 [8];
  undefined4 uStack_28a8;
  undefined4 uStack_28a4;
  undefined1 auStack_28a0 [16];
  undefined1 auStack_2890 [8];
  undefined4 uStack_2888;
  undefined4 uStack_2884;
  undefined1 auStack_2880 [16];
  undefined1 auStack_2870 [8];
  undefined4 uStack_2868;
  undefined4 uStack_2864;
  undefined1 auStack_2860 [16];
  undefined1 auStack_2850 [16];
  undefined1 auStack_2840 [8];
  float fStack_2838;
  undefined4 uStack_2834;
  undefined1 auStack_2830 [16];
  undefined1 auStack_2820 [16];
  undefined1 auStack_2810 [8];
  float fStack_2808;
  undefined4 uStack_2804;
  undefined1 auStack_2800 [16];
  undefined1 auStack_27f0 [16];
  undefined1 auStack_27e0 [8];
  float fStack_27d8;
  undefined4 uStack_27d4;
  undefined1 auStack_27d0 [16];
  undefined1 auStack_27c0 [16];
  undefined8 uStack_27b0;
  undefined4 uStack_27a8;
  undefined4 uStack_27a4;
  undefined1 auStack_27a0 [16];
  undefined1 auStack_2790 [16];
  undefined8 uStack_2780;
  undefined4 uStack_2778;
  undefined4 uStack_2774;
  undefined1 auStack_2770 [16];
  undefined1 auStack_2760 [8];
  undefined4 uStack_2758;
  undefined4 uStack_2754;
  undefined1 auStack_2750 [16];
  undefined1 auStack_2740 [8];
  undefined4 uStack_2738;
  undefined4 uStack_2734;
  undefined1 auStack_2730 [16];
  undefined1 auStack_2720 [8];
  undefined4 uStack_2718;
  undefined4 uStack_2714;
  undefined1 auStack_2710 [16];
  undefined8 uStack_2700;
  undefined4 uStack_26f8;
  undefined4 uStack_26f4;
  undefined8 uStack_26f0;
  undefined4 uStack_26e8;
  undefined4 uStack_26e4;
  undefined1 auStack_26e0 [8];
  undefined4 uStack_26d8;
  undefined4 uStack_26d4;
  undefined1 auStack_26d0 [8];
  undefined4 uStack_26c8;
  undefined4 uStack_26c4;
  undefined1 auStack_26c0 [16];
  undefined8 uStack_26b0;
  undefined4 uStack_26a8;
  undefined4 uStack_26a4;
  undefined1 auStack_26a0 [16];
  undefined8 uStack_2690;
  undefined4 uStack_2688;
  undefined4 uStack_2684;
  undefined1 auStack_2680 [16];
  undefined8 uStack_2670;
  undefined4 uStack_2668;
  undefined4 uStack_2664;
  undefined1 auStack_2660 [8];
  undefined4 uStack_2658;
  undefined4 uStack_2654;
  undefined1 auStack_2650 [16];
  undefined8 uStack_2640;
  undefined4 uStack_2638;
  undefined4 uStack_2634;
  undefined1 auStack_2630 [16];
  undefined8 uStack_2620;
  undefined4 uStack_2618;
  undefined4 uStack_2614;
  undefined1 auStack_2610 [16];
  undefined8 uStack_2600;
  undefined4 uStack_25f8;
  undefined4 uStack_25f4;
  undefined1 auStack_25f0 [16];
  undefined1 auStack_25e0 [8];
  undefined4 uStack_25d8;
  undefined4 uStack_25d4;
  undefined1 auStack_25d0 [16];
  undefined1 auStack_25c0 [8];
  undefined4 uStack_25b8;
  undefined4 uStack_25b4;
  undefined1 auStack_25b0 [16];
  undefined1 auStack_25a0 [8];
  undefined4 uStack_2598;
  undefined4 uStack_2594;
  undefined1 auStack_2590 [16];
  undefined1 auStack_2580 [8];
  undefined4 uStack_2578;
  undefined4 uStack_2574;
  undefined1 auStack_2570 [16];
  undefined1 auStack_2560 [12];
  undefined4 uStack_2554;
  undefined1 auStack_2550 [8];
  undefined4 uStack_2548;
  undefined4 uStack_2544;
  undefined1 auStack_2540 [16];
  undefined1 auStack_2530 [12];
  undefined4 uStack_2524;
  undefined1 auStack_2520 [8];
  undefined4 uStack_2518;
  undefined4 uStack_2514;
  undefined1 auStack_2510 [16];
  undefined8 uStack_2500;
  undefined4 uStack_24f4;
  ulong uStack_24f0;
  undefined4 uStack_24e8;
  undefined4 uStack_24e4;
  undefined1 auStack_24e0 [16];
  undefined8 uStack_24d0;
  undefined4 uStack_24c4;
  undefined1 auStack_24c0 [16];
  undefined1 auStack_24b0 [8];
  undefined4 uStack_24a8;
  undefined4 uStack_24a4;
  undefined1 auStack_24a0 [16];
  undefined1 auStack_2490 [16];
  undefined1 auStack_2480 [16];
  undefined8 uStack_2470;
  undefined4 uStack_2468;
  undefined4 uStack_2464;
  undefined1 auStack_2460 [16];
  undefined1 auStack_2450 [16];
  undefined1 auStack_2440 [8];
  undefined4 uStack_2438;
  undefined4 uStack_2434;
  undefined1 auStack_2430 [16];
  undefined1 auStack_2420 [16];
  undefined1 auStack_2410 [16];
  undefined8 uStack_2400;
  undefined4 uStack_23f8;
  undefined4 uStack_23f4;
  undefined1 auStack_23f0 [16];
  undefined1 auStack_23e0 [16];
  undefined1 auStack_23d0 [16];
  undefined1 auStack_23c0 [8];
  float fStack_23b8;
  undefined4 uStack_23b4;
  undefined1 auStack_23b0 [16];
  undefined1 auStack_23a0 [8];
  float fStack_2398;
  undefined4 uStack_2394;
  undefined1 auStack_2390 [16];
  undefined8 uStack_2380;
  undefined4 uStack_2378;
  undefined4 uStack_2374;
  undefined8 uStack_2370;
  undefined4 uStack_2368;
  undefined4 uStack_2364;
  undefined1 auStack_2360 [16];
  undefined1 auStack_2350 [16];
  undefined1 auStack_2340 [16];
  undefined1 auStack_2330 [8];
  undefined4 uStack_2328;
  undefined4 uStack_2324;
  undefined1 auStack_2320 [16];
  undefined1 auStack_2310 [8];
  undefined4 uStack_2308;
  undefined4 uStack_2304;
  undefined1 auStack_2300 [16];
  undefined1 auStack_22f0 [8];
  undefined4 uStack_22e8;
  undefined4 uStack_22e4;
  undefined1 auStack_22e0 [16];
  undefined8 uStack_22d0;
  undefined4 uStack_22c8;
  undefined4 uStack_22c4;
  ulong uStack_22c0;
  undefined4 uStack_22b8;
  undefined4 uStack_22b4;
  ulong uStack_22b0;
  undefined4 uStack_22a8;
  undefined4 uStack_22a4;
  ulong uStack_22a0;
  undefined4 uStack_2298;
  undefined4 uStack_2294;
  undefined1 auStack_2290 [8];
  undefined4 uStack_2288;
  undefined4 uStack_2284;
  undefined1 auStack_2280 [8];
  undefined4 uStack_2278;
  undefined4 uStack_2274;
  undefined1 auStack_2270 [16];
  undefined1 auStack_2260 [8];
  undefined4 uStack_2258;
  undefined4 uStack_2254;
  undefined1 auStack_2250 [16];
  undefined1 auStack_2240 [8];
  undefined4 uStack_2238;
  undefined4 uStack_2234;
  undefined1 auStack_2230 [16];
  undefined1 auStack_2220 [8];
  undefined4 uStack_2218;
  undefined4 uStack_2214;
  undefined1 auStack_2210 [16];
  undefined1 auStack_2200 [8];
  undefined4 uStack_21f8;
  undefined4 uStack_21f4;
  undefined1 auStack_21f0 [16];
  undefined1 auStack_21e0 [16];
  undefined1 auStack_21d0 [8];
  float fStack_21c8;
  undefined4 uStack_21c4;
  undefined1 auStack_21c0 [16];
  undefined1 auStack_21b0 [16];
  undefined1 auStack_21a0 [8];
  float fStack_2198;
  undefined4 uStack_2194;
  undefined1 auStack_2190 [16];
  undefined1 auStack_2180 [16];
  undefined1 auStack_2170 [8];
  float fStack_2168;
  undefined4 uStack_2164;
  undefined1 auStack_2160 [16];
  undefined1 auStack_2150 [16];
  undefined8 uStack_2140;
  undefined4 uStack_2138;
  undefined4 uStack_2134;
  undefined1 auStack_2130 [16];
  undefined1 auStack_2120 [16];
  undefined8 uStack_2110;
  undefined4 uStack_2108;
  undefined4 uStack_2104;
  undefined1 auStack_2100 [16];
  undefined1 auStack_20f0 [8];
  undefined4 uStack_20e8;
  undefined4 uStack_20e4;
  undefined1 auStack_20e0 [16];
  undefined1 auStack_20d0 [8];
  undefined4 uStack_20c8;
  undefined4 uStack_20c4;
  undefined1 auStack_20c0 [16];
  undefined1 auStack_20b0 [8];
  undefined4 uStack_20a8;
  undefined4 uStack_20a4;
  undefined1 auStack_20a0 [16];
  undefined8 uStack_2090;
  undefined4 uStack_2088;
  undefined4 uStack_2084;
  undefined8 uStack_2080;
  undefined4 uStack_2078;
  undefined4 uStack_2074;
  undefined1 auStack_2070 [8];
  undefined4 uStack_2068;
  undefined4 uStack_2064;
  undefined1 auStack_2060 [16];
  undefined1 auStack_2050 [8];
  float fStack_2048;
  undefined4 uStack_2044;
  undefined1 auStack_2040 [16];
  undefined8 uStack_2030;
  undefined4 uStack_2028;
  undefined4 uStack_2024;
  undefined8 uStack_2020;
  undefined4 uStack_2018;
  undefined4 uStack_2014;
  undefined1 auStack_2010 [16];
  undefined8 uStack_2000;
  undefined4 uStack_1ff8;
  undefined4 uStack_1ff4;
  undefined1 auStack_1ff0 [16];
  undefined8 uStack_1fe0;
  undefined4 uStack_1fd8;
  undefined4 uStack_1fd4;
  undefined1 auStack_1fd0 [16];
  undefined8 uStack_1fc0;
  undefined4 uStack_1fb8;
  undefined4 uStack_1fb4;
  undefined8 uStack_1fb0;
  undefined4 uStack_1fa8;
  undefined4 uStack_1fa4;
  undefined1 auStack_1fa0 [16];
  undefined8 uStack_1f90;
  undefined4 uStack_1f88;
  undefined4 uStack_1f84;
  undefined1 auStack_1f80 [16];
  undefined8 uStack_1f70;
  undefined4 uStack_1f68;
  undefined4 uStack_1f64;
  undefined1 auStack_1f60 [16];
  undefined8 uStack_1f50;
  undefined4 uStack_1f48;
  undefined4 uStack_1f44;
  undefined1 auStack_1f40 [16];
  undefined1 auStack_1f30 [8];
  undefined4 uStack_1f28;
  undefined4 uStack_1f24;
  undefined1 auStack_1f20 [16];
  undefined1 auStack_1f10 [8];
  undefined4 uStack_1f08;
  undefined4 uStack_1f04;
  undefined1 auStack_1f00 [16];
  undefined1 auStack_1ef0 [8];
  undefined4 uStack_1ee8;
  undefined4 uStack_1ee4;
  undefined1 auStack_1ee0 [16];
  undefined1 auStack_1ed0 [8];
  undefined4 uStack_1ec8;
  undefined4 uStack_1ec4;
  undefined1 auStack_1ec0 [16];
  undefined1 auStack_1eb0 [12];
  undefined4 uStack_1ea4;
  undefined1 auStack_1ea0 [8];
  undefined4 uStack_1e98;
  undefined4 uStack_1e94;
  undefined1 auStack_1e90 [16];
  undefined1 auStack_1e80 [12];
  undefined4 uStack_1e74;
  undefined1 auStack_1e70 [8];
  undefined4 uStack_1e68;
  undefined4 uStack_1e64;
  undefined1 auStack_1e60 [16];
  undefined8 uStack_1e50;
  undefined4 uStack_1e44;
  ulong uStack_1e40;
  undefined4 uStack_1e38;
  undefined4 uStack_1e34;
  undefined1 auStack_1e30 [16];
  undefined8 uStack_1e20;
  undefined4 uStack_1e14;
  undefined1 auStack_1e10 [16];
  undefined8 uStack_1e00;
  undefined4 uStack_1df8;
  undefined4 uStack_1df4;
  undefined1 auStack_1df0 [16];
  undefined1 auStack_1de0 [16];
  undefined1 auStack_1dd0 [16];
  undefined8 uStack_1dc0;
  undefined4 uStack_1db8;
  undefined4 uStack_1db4;
  undefined1 auStack_1db0 [16];
  undefined1 auStack_1da0 [16];
  undefined8 uStack_1d90;
  undefined4 uStack_1d88;
  undefined4 uStack_1d84;
  undefined1 auStack_1d80 [16];
  undefined1 auStack_1d70 [16];
  undefined1 auStack_1d60 [16];
  undefined8 uStack_1d50;
  undefined4 uStack_1d48;
  undefined4 uStack_1d44;
  undefined1 auStack_1d40 [16];
  undefined1 auStack_1d30 [16];
  undefined1 auStack_1d20 [16];
  undefined1 auStack_1d10 [8];
  float fStack_1d08;
  undefined4 uStack_1d04;
  undefined1 auStack_1d00 [16];
  undefined1 auStack_1cf0 [8];
  float fStack_1ce8;
  undefined4 uStack_1ce4;
  undefined1 auStack_1ce0 [16];
  undefined8 uStack_1cd0;
  undefined4 uStack_1cc8;
  undefined4 uStack_1cc4;
  undefined8 uStack_1cc0;
  undefined4 uStack_1cb8;
  undefined4 uStack_1cb4;
  undefined1 auStack_1cb0 [16];
  undefined1 auStack_1ca0 [16];
  undefined1 auStack_1c90 [8];
  undefined4 uStack_1c88;
  undefined4 uStack_1c84;
  ulong uStack_1c80;
  undefined4 uStack_1c78;
  undefined4 uStack_1c74;
  undefined1 auStack_1c70 [8];
  undefined4 uStack_1c68;
  undefined4 uStack_1c64;
  undefined1 auStack_1c60 [8];
  undefined4 uStack_1c58;
  undefined4 uStack_1c54;
  undefined1 auStack_1c50 [16];
  undefined1 auStack_1c40 [8];
  float fStack_1c38;
  undefined4 uStack_1c34;
  undefined1 auStack_1c30 [16];
  undefined1 auStack_1c20 [8];
  float fStack_1c18;
  undefined4 uStack_1c14;
  undefined8 uStack_1c10;
  undefined4 uStack_1c08;
  undefined4 uStack_1c04;
  undefined1 auStack_1c00 [16];
  undefined1 auStack_1bf0 [16];
  undefined1 auStack_1be0 [16];
  undefined8 uStack_1bd0;
  undefined4 uStack_1bc8;
  undefined4 uStack_1bc4;
  undefined1 auStack_1bc0 [16];
  undefined1 auStack_1bb0 [8];
  undefined4 uStack_1ba8;
  undefined4 uStack_1ba4;
  undefined1 auStack_1ba0 [8];
  undefined4 uStack_1b98;
  undefined4 uStack_1b94;
  undefined1 auStack_1b90 [16];
  undefined1 auStack_1b80 [8];
  undefined4 uStack_1b78;
  undefined4 uStack_1b74;
  undefined1 auStack_1b70 [8];
  undefined4 uStack_1b68;
  undefined4 uStack_1b64;
  undefined1 auStack_1b60 [8];
  undefined4 uStack_1b58;
  undefined4 uStack_1b54;
  undefined1 auStack_1b50 [16];
  undefined8 uStack_1b40;
  undefined4 uStack_1b38;
  undefined4 uStack_1b34;
  undefined1 auStack_1b30 [16];
  undefined1 auStack_1b20 [16];
  undefined8 uStack_1b10;
  undefined4 uStack_1b08;
  undefined4 uStack_1b04;
  undefined1 auStack_1b00 [16];
  undefined1 auStack_1af0 [16];
  undefined1 auStack_1ae0 [8];
  undefined4 uStack_1ad8;
  undefined4 uStack_1ad4;
  undefined1 auStack_1ad0 [16];
  undefined1 auStack_1ac0 [8];
  undefined4 uStack_1ab8;
  undefined4 uStack_1ab4;
  undefined1 auStack_1ab0 [16];
  undefined1 auStack_1aa0 [8];
  undefined4 uStack_1a98;
  undefined4 uStack_1a94;
  undefined1 auStack_1a90 [16];
  undefined1 auStack_1a80 [8];
  undefined4 uStack_1a78;
  undefined4 uStack_1a74;
  undefined1 auStack_1a70 [16];
  undefined1 auStack_1a60 [16];
  undefined1 auStack_1a50 [16];
  undefined1 auStack_1a40 [8];
  float fStack_1a38;
  undefined4 uStack_1a34;
  undefined1 auStack_1a30 [16];
  undefined1 auStack_1a20 [16];
  undefined1 auStack_1a10 [16];
  undefined1 auStack_1a00 [8];
  float fStack_19f8;
  undefined4 uStack_19f4;
  undefined1 auStack_19f0 [16];
  undefined1 auStack_19e0 [16];
  undefined1 auStack_19d0 [16];
  undefined1 auStack_19c0 [8];
  float fStack_19b8;
  undefined4 uStack_19b4;
  undefined1 auStack_19b0 [16];
  undefined1 auStack_19a0 [16];
  undefined1 auStack_1990 [16];
  undefined8 uStack_1980;
  undefined4 uStack_1978;
  undefined4 uStack_1974;
  undefined1 auStack_1970 [16];
  undefined1 auStack_1960 [16];
  undefined1 auStack_1950 [16];
  undefined8 uStack_1940;
  undefined4 uStack_1938;
  undefined4 uStack_1934;
  undefined1 auStack_1930 [16];
  undefined1 auStack_1920 [8];
  undefined4 uStack_1918;
  undefined4 uStack_1914;
  undefined1 auStack_1910 [16];
  undefined1 auStack_1900 [8];
  undefined4 uStack_18f8;
  undefined4 uStack_18f4;
  undefined1 auStack_18f0 [16];
  undefined1 auStack_18e0 [8];
  undefined4 uStack_18d8;
  undefined4 uStack_18d4;
  undefined1 auStack_18d0 [16];
  undefined8 uStack_18c0;
  undefined4 uStack_18b8;
  undefined4 uStack_18b4;
  undefined8 uStack_18b0;
  undefined4 uStack_18a8;
  undefined4 uStack_18a4;
  undefined8 uStack_18a0;
  undefined4 uStack_1898;
  undefined4 uStack_1894;
  undefined1 auStack_1890 [8];
  undefined4 uStack_1888;
  undefined4 uStack_1884;
  undefined1 auStack_1880 [16];
  undefined1 auStack_1870 [16];
  undefined1 auStack_1860 [8];
  float fStack_1858;
  undefined4 uStack_1854;
  undefined1 auStack_1850 [16];
  undefined1 auStack_1840 [16];
  undefined1 auStack_1830 [16];
  undefined8 uStack_1820;
  undefined4 uStack_1818;
  undefined4 uStack_1814;
  undefined1 auStack_1810 [16];
  undefined8 uStack_1800;
  undefined4 uStack_17f8;
  undefined4 uStack_17f4;
  undefined1 auStack_17f0 [16];
  undefined8 uStack_17e0;
  undefined4 uStack_17d8;
  undefined4 uStack_17d4;
  undefined1 auStack_17d0 [16];
  undefined1 auStack_17c0 [16];
  undefined1 auStack_17b0 [16];
  undefined8 uStack_17a0;
  undefined4 uStack_1798;
  undefined4 uStack_1794;
  undefined8 uStack_1790;
  undefined4 uStack_1788;
  undefined4 uStack_1784;
  undefined1 auStack_1780 [16];
  undefined8 uStack_1770;
  undefined4 uStack_1768;
  undefined4 uStack_1764;
  undefined1 auStack_1760 [16];
  undefined8 uStack_1750;
  undefined4 uStack_1748;
  undefined4 uStack_1744;
  undefined1 auStack_1740 [16];
  undefined1 auStack_1730 [16];
  undefined1 auStack_1720 [16];
  undefined8 uStack_1710;
  undefined4 uStack_1708;
  undefined4 uStack_1704;
  undefined1 auStack_1700 [16];
  undefined1 auStack_16f0 [8];
  undefined4 uStack_16e8;
  undefined4 uStack_16e4;
  undefined1 auStack_16e0 [16];
  undefined1 auStack_16d0 [8];
  undefined4 uStack_16c8;
  undefined4 uStack_16c4;
  undefined1 auStack_16c0 [16];
  undefined1 auStack_16b0 [8];
  undefined4 uStack_16a8;
  undefined4 uStack_16a4;
  undefined1 auStack_16a0 [16];
  undefined1 auStack_1690 [8];
  undefined4 uStack_1688;
  undefined4 uStack_1684;
  undefined1 auStack_1680 [16];
  undefined1 auStack_1670 [12];
  undefined4 uStack_1664;
  undefined1 auStack_1660 [16];
  undefined1 auStack_1650 [8];
  undefined4 uStack_1648;
  undefined4 uStack_1644;
  undefined1 auStack_1640 [16];
  undefined1 auStack_1630 [12];
  undefined4 uStack_1624;
  undefined1 auStack_1620 [16];
  undefined1 auStack_1610 [8];
  undefined4 uStack_1608;
  undefined4 uStack_1604;
  undefined1 auStack_1600 [16];
  undefined8 uStack_15f0;
  undefined4 uStack_15e4;
  undefined1 auStack_15e0 [16];
  ulong uStack_15d0;
  undefined4 uStack_15c8;
  undefined4 uStack_15c4;
  undefined1 auStack_15c0 [16];
  undefined8 uStack_15b0;
  undefined4 uStack_15a4;
  undefined1 auStack_15a0 [16];
  undefined1 auStack_1590 [16];
  undefined8 uStack_1580;
  undefined4 uStack_1578;
  undefined4 uStack_1574;
  undefined1 auStack_1570 [16];
  undefined1 auStack_1560 [16];
  undefined1 auStack_1550 [16];
  undefined8 uStack_1540;
  undefined4 uStack_1538;
  undefined4 uStack_1534;
  undefined1 auStack_1530 [16];
  undefined1 auStack_1520 [16];
  undefined1 auStack_1510 [16];
  undefined1 auStack_1500 [16];
  undefined8 uStack_14f0;
  undefined4 uStack_14e8;
  undefined4 uStack_14e4;
  undefined1 auStack_14e0 [16];
  undefined1 auStack_14d0 [16];
  undefined1 auStack_14c0 [16];
  undefined8 uStack_14b0;
  undefined4 uStack_14a8;
  undefined4 uStack_14a4;
  undefined1 auStack_14a0 [16];
  undefined1 auStack_1490 [16];
  undefined1 auStack_1480 [16];
  undefined1 auStack_1470 [16];
  undefined1 auStack_1460 [16];
  undefined1 auStack_1450 [8];
  float fStack_1448;
  undefined4 uStack_1444;
  undefined1 auStack_1440 [16];
  undefined1 auStack_1430 [8];
  float fStack_1428;
  undefined4 uStack_1424;
  undefined1 auStack_1420 [16];
  undefined8 uStack_1410;
  undefined4 uStack_1408;
  undefined4 uStack_1404;
  undefined1 auStack_1400 [16];
  undefined8 uStack_13f0;
  undefined4 uStack_13e8;
  undefined4 uStack_13e4;
  undefined1 auStack_13e0 [16];
  undefined1 auStack_13d0 [16];
  undefined1 auStack_13c0 [16];
  undefined1 auStack_13b0 [8];
  undefined4 uStack_13a8;
  undefined4 uStack_13a4;
  undefined1 auStack_13a0 [16];
  undefined8 uStack_1390;
  undefined4 uStack_1388;
  undefined4 uStack_1384;
  undefined1 auStack_1380 [16];
  undefined8 uStack_1370;
  undefined4 uStack_1368;
  undefined4 uStack_1364;
  undefined1 auStack_1360 [16];
  undefined1 auStack_1350 [16];
  undefined8 uStack_1340;
  undefined4 uStack_1338;
  undefined4 uStack_1334;
  undefined1 auStack_1330 [16];
  undefined8 uStack_1320;
  undefined4 uStack_1318;
  undefined4 uStack_1314;
  undefined1 auStack_1310 [16];
  undefined1 auStack_1300 [8];
  float fStack_12f8;
  undefined4 uStack_12f4;
  undefined1 auStack_12f0 [16];
  undefined1 auStack_12e0 [8];
  float fStack_12d8;
  undefined4 uStack_12d4;
  undefined8 uStack_12d0;
  undefined4 uStack_12c8;
  undefined4 uStack_12c4;
  undefined1 auStack_12c0 [16];
  undefined1 auStack_12b0 [16];
  undefined1 auStack_12a0 [16];
  undefined8 uStack_1290;
  undefined4 uStack_1288;
  undefined4 uStack_1284;
  undefined1 auStack_1280 [16];
  undefined1 auStack_1270 [8];
  undefined4 uStack_1268;
  undefined4 uStack_1264;
  undefined1 auStack_1260 [8];
  undefined4 uStack_1258;
  undefined4 uStack_1254;
  undefined1 auStack_1250 [16];
  undefined1 auStack_1240 [8];
  undefined4 uStack_1238;
  undefined4 uStack_1234;
  undefined1 auStack_1230 [8];
  undefined4 uStack_1228;
  undefined4 uStack_1224;
  undefined1 auStack_1220 [8];
  undefined4 uStack_1218;
  undefined4 uStack_1214;
  undefined1 auStack_1210 [16];
  undefined8 uStack_1200;
  undefined4 uStack_11f8;
  undefined4 uStack_11f4;
  undefined1 auStack_11f0 [16];
  undefined1 auStack_11e0 [16];
  undefined8 uStack_11d0;
  undefined4 uStack_11c8;
  undefined4 uStack_11c4;
  undefined1 auStack_11c0 [16];
  undefined1 auStack_11b0 [16];
  undefined1 auStack_11a0 [8];
  undefined4 uStack_1198;
  undefined4 uStack_1194;
  undefined1 auStack_1190 [16];
  undefined1 auStack_1180 [16];
  undefined1 auStack_1170 [8];
  undefined4 uStack_1168;
  undefined4 uStack_1164;
  undefined1 auStack_1160 [8];
  undefined4 uStack_1158;
  undefined4 uStack_1154;
  undefined1 auStack_1150 [16];
  undefined1 auStack_1140 [8];
  undefined4 uStack_1138;
  undefined4 uStack_1134;
  undefined1 auStack_1130 [8];
  undefined4 uStack_1128;
  undefined4 uStack_1124;
  undefined1 auStack_1120 [8];
  undefined4 uStack_1118;
  undefined4 uStack_1114;
  undefined1 auStack_1110 [8];
  undefined4 uStack_1108;
  undefined4 uStack_1104;
  undefined1 auStack_1100 [8];
  undefined4 uStack_10f8;
  undefined4 uStack_10f4;
  undefined1 auStack_10f0 [16];
  undefined1 auStack_10e0 [8];
  undefined4 uStack_10d8;
  undefined4 uStack_10d4;
  undefined1 auStack_10d0 [8];
  undefined4 uStack_10c8;
  undefined4 uStack_10c4;
  undefined1 auStack_10c0 [16];
  undefined1 auStack_10b0 [8];
  undefined4 uStack_10a8;
  undefined4 uStack_10a4;
  undefined1 auStack_10a0 [8];
  undefined4 uStack_1098;
  undefined4 uStack_1094;
  undefined1 auStack_1090 [16];
  undefined8 uStack_1080;
  undefined4 uStack_1078;
  undefined4 uStack_1074;
  undefined1 auStack_1070 [8];
  undefined4 uStack_1068;
  undefined4 uStack_1064;
  undefined1 auStack_1060 [8];
  undefined4 uStack_1058;
  undefined4 uStack_1054;
  undefined1 auStack_1050 [8];
  undefined4 uStack_1048;
  undefined4 uStack_1044;
  undefined8 uStack_1040;
  undefined4 uStack_1038;
  undefined4 uStack_1034;
  undefined1 auStack_1030 [8];
  undefined4 uStack_1028;
  undefined4 uStack_1024;
  undefined1 auStack_1020 [8];
  undefined4 uStack_1018;
  undefined4 uStack_1014;
  undefined1 auStack_1010 [8];
  undefined4 uStack_1008;
  undefined4 uStack_1004;
  undefined1 auStack_1000 [8];
  undefined4 uStack_ff8;
  undefined4 uStack_ff4;
  undefined8 uStack_ff0;
  undefined4 uStack_fe8;
  undefined4 uStack_fe4;
  undefined8 uStack_fe0;
  undefined4 uStack_fd8;
  undefined4 uStack_fd4;
  undefined1 auStack_fd0 [8];
  undefined4 uStack_fc8;
  undefined4 uStack_fc4;
  undefined8 uStack_fc0;
  undefined4 uStack_fb8;
  undefined4 uStack_fb4;
  undefined8 uStack_fb0;
  undefined4 uStack_fa8;
  undefined4 uStack_fa4;
  undefined1 auStack_fa0 [8];
  undefined4 uStack_f98;
  undefined4 uStack_f94;
  undefined1 auStack_f90 [8];
  undefined4 uStack_f88;
  undefined4 uStack_f84;
  undefined1 auStack_f80 [16];
  undefined1 auStack_f70 [16];
  undefined1 auStack_f60 [16];
  undefined1 auStack_f50 [16];
  undefined8 uStack_f40;
  undefined4 uStack_f38;
  undefined4 uStack_f34;
  undefined1 auStack_f30 [16];
  undefined8 uStack_f20;
  undefined4 uStack_f18;
  undefined4 uStack_f14;
  undefined8 uStack_f10;
  undefined4 uStack_f08;
  undefined4 uStack_f04;
  undefined1 auStack_f00 [16];
  undefined1 auStack_ef0 [16];
  undefined8 uStack_ee0;
  undefined4 uStack_ed8;
  undefined4 uStack_ed4;
  undefined1 auStack_ed0 [8];
  undefined4 uStack_ec8;
  undefined4 uStack_ec4;
  undefined1 auStack_ec0 [8];
  undefined4 uStack_eb8;
  undefined4 uStack_eb4;
  undefined1 auStack_eb0 [16];
  undefined8 uStack_ea0;
  undefined4 uStack_e98;
  undefined4 uStack_e94;
  undefined8 uStack_e90;
  undefined4 uStack_e88;
  undefined4 uStack_e84;
  undefined1 auStack_e80 [16];
  undefined1 auStack_e70 [16];
  undefined8 uStack_e60;
  undefined4 uStack_e58;
  undefined4 uStack_e54;
  undefined1 auStack_e50 [16];
  undefined1 auStack_e40 [16];
  undefined1 auStack_e30 [8];
  undefined4 uStack_e28;
  undefined4 uStack_e24;
  undefined1 auStack_e20 [8];
  float fStack_e18;
  float fStack_e14;
  undefined1 auStack_e10 [8];
  undefined4 uStack_e08;
  float fStack_e04;
  undefined1 auStack_e00 [8];
  undefined4 uStack_df8;
  undefined4 uStack_df4;
  undefined1 auStack_df0 [16];
  undefined1 auStack_de0 [8];
  undefined4 uStack_dd8;
  undefined4 uStack_dd4;
  undefined1 auStack_dd0 [16];
  undefined1 auStack_dc0 [8];
  undefined4 uStack_db8;
  undefined4 uStack_db4;
  undefined1 auStack_db0 [16];
  undefined1 auStack_da0 [8];
  undefined4 uStack_d98;
  undefined4 uStack_d94;
  undefined1 auStack_d90 [16];
  undefined1 auStack_d80 [8];
  undefined4 uStack_d78;
  undefined4 uStack_d74;
  undefined1 auStack_d70 [16];
  undefined1 auStack_d60 [16];
  undefined1 auStack_d50 [8];
  float fStack_d48;
  undefined4 uStack_d44;
  undefined1 auStack_d40 [16];
  undefined1 auStack_d30 [16];
  undefined1 auStack_d20 [8];
  float fStack_d18;
  undefined4 uStack_d14;
  undefined1 auStack_d10 [16];
  undefined1 auStack_d00 [16];
  undefined1 auStack_cf0 [16];
  undefined8 uStack_ce0;
  undefined4 uStack_cd8;
  undefined4 uStack_cd4;
  undefined1 auStack_cd0 [16];
  undefined1 auStack_cc0 [16];
  undefined1 auStack_cb0 [16];
  undefined8 uStack_ca0;
  undefined4 uStack_c98;
  undefined4 uStack_c94;
  undefined1 auStack_c90 [16];
  undefined1 auStack_c80 [8];
  float fStack_c78;
  undefined4 uStack_c74;
  undefined1 auStack_c70 [16];
  undefined1 auStack_c60 [16];
  undefined1 auStack_c50 [16];
  undefined8 uStack_c40;
  undefined4 uStack_c38;
  undefined4 uStack_c34;
  undefined1 auStack_c30 [16];
  undefined8 uStack_c20;
  undefined4 uStack_c18;
  undefined4 uStack_c14;
  undefined1 auStack_c10 [16];
  undefined8 uStack_c00;
  undefined4 uStack_bf8;
  undefined4 uStack_bf4;
  undefined1 auStack_bf0 [8];
  float fStack_be8;
  float fStack_be4;
  undefined1 auStack_be0 [8];
  undefined4 uStack_bd8;
  float fStack_bd4;
  undefined1 auStack_bd0 [8];
  undefined4 uStack_bc8;
  undefined4 uStack_bc4;
  undefined1 auStack_bc0 [16];
  undefined1 auStack_bb0 [8];
  float fStack_ba8;
  float fStack_ba4;
  undefined8 uStack_ba0;
  undefined4 uStack_b98;
  undefined4 uStack_b94;
  undefined8 uStack_b90;
  undefined4 uStack_b88;
  undefined4 uStack_b84;
  undefined1 auStack_b80 [16];
  undefined1 auStack_b70 [8];
  float fStack_b68;
  float fStack_b64;
  undefined8 uStack_b60;
  undefined4 uStack_b58;
  undefined4 uStack_b54;
  undefined1 auStack_b50 [16];
  undefined1 auStack_b40 [16];
  undefined1 auStack_b30 [8];
  undefined4 uStack_b28;
  undefined4 uStack_b24;
  undefined1 auStack_b20 [16];
  undefined1 auStack_b10 [16];
  undefined1 auStack_b00 [8];
  undefined4 uStack_af8;
  undefined4 uStack_af4;
  undefined1 auStack_af0 [16];
  undefined1 auStack_ae0 [16];
  undefined1 auStack_ad0 [8];
  undefined4 uStack_ac8;
  undefined4 uStack_ac4;
  undefined1 auStack_ac0 [16];
  undefined1 auStack_ab0 [16];
  undefined1 auStack_aa0 [8];
  undefined4 uStack_a98;
  undefined4 uStack_a94;
  undefined1 auStack_a90 [16];
  undefined1 auStack_a80 [16];
  undefined1 auStack_a70 [8];
  float fStack_a68;
  undefined4 uStack_a64;
  undefined1 auStack_a60 [16];
  undefined1 auStack_a50 [16];
  undefined1 auStack_a40 [8];
  float fStack_a38;
  undefined4 uStack_a34;
  undefined1 auStack_a30 [16];
  undefined1 auStack_a20 [16];
  undefined8 uStack_a10;
  undefined4 uStack_a08;
  undefined4 uStack_a04;
  undefined1 auStack_a00 [16];
  undefined1 auStack_9f0 [16];
  undefined8 uStack_9e0;
  undefined4 uStack_9d8;
  undefined4 uStack_9d4;
  undefined1 auStack_9d0 [16];
  undefined1 auStack_9c0 [16];
  undefined1 auStack_9b0 [8];
  undefined4 uStack_9a8;
  undefined4 uStack_9a4;
  undefined1 auStack_9a0 [16];
  undefined1 auStack_990 [16];
  undefined1 auStack_980 [8];
  undefined4 uStack_978;
  undefined4 uStack_974;
  undefined1 auStack_970 [16];
  undefined1 auStack_960 [16];
  undefined1 auStack_950 [8];
  undefined4 uStack_948;
  undefined4 uStack_944;
  undefined1 auStack_940 [16];
  undefined1 auStack_930 [16];
  undefined1 auStack_920 [8];
  undefined4 uStack_918;
  undefined4 uStack_914;
  undefined1 auStack_910 [16];
  undefined1 auStack_900 [16];
  undefined1 auStack_8f0 [8];
  float fStack_8e8;
  undefined4 uStack_8e4;
  undefined1 auStack_8e0 [16];
  undefined1 auStack_8d0 [16];
  undefined1 auStack_8c0 [8];
  float fStack_8b8;
  undefined4 uStack_8b4;
  undefined1 auStack_8b0 [16];
  undefined1 auStack_8a0 [16];
  undefined8 uStack_890;
  undefined4 uStack_888;
  undefined4 uStack_884;
  undefined1 auStack_880 [16];
  undefined1 auStack_870 [16];
  undefined8 uStack_860;
  undefined4 uStack_858;
  undefined4 uStack_854;
  undefined1 auStack_850 [8];
  float fStack_848;
  float fStack_844;
  undefined1 auStack_840 [8];
  float fStack_838;
  float fStack_834;
  undefined1 auStack_830 [16];
  undefined1 auStack_820 [16];
  undefined1 auStack_810 [8];
  undefined4 uStack_808;
  undefined4 uStack_804;
  undefined8 uStack_800;
  undefined4 uStack_7f8;
  undefined4 uStack_7f4;
  undefined8 uStack_7f0;
  undefined4 uStack_7e8;
  undefined4 uStack_7e4;
  undefined8 uStack_7e0;
  undefined4 uStack_7d8;
  undefined4 uStack_7d4;
  undefined8 uStack_7d0;
  undefined4 uStack_7c8;
  undefined4 uStack_7c4;
  undefined1 auStack_7c0 [16];
  undefined1 auStack_7b0 [16];
  undefined1 auStack_7a0 [8];
  undefined4 uStack_798;
  undefined4 uStack_794;
  undefined1 auStack_790 [16];
  undefined1 auStack_780 [16];
  undefined1 auStack_770 [8];
  undefined4 uStack_768;
  undefined4 uStack_764;
  undefined1 auStack_760 [16];
  undefined1 auStack_750 [16];
  undefined1 auStack_740 [8];
  undefined4 uStack_738;
  undefined4 uStack_734;
  undefined1 auStack_730 [16];
  undefined1 auStack_720 [16];
  undefined1 auStack_710 [8];
  undefined4 uStack_708;
  undefined4 uStack_704;
  undefined1 auStack_700 [16];
  undefined1 auStack_6f0 [16];
  undefined1 auStack_6e0 [8];
  float fStack_6d8;
  undefined4 uStack_6d4;
  undefined1 auStack_6d0 [16];
  undefined1 auStack_6c0 [16];
  undefined1 auStack_6b0 [8];
  float fStack_6a8;
  undefined4 uStack_6a4;
  undefined1 auStack_6a0 [16];
  undefined1 auStack_690 [16];
  undefined1 auStack_680 [16];
  undefined1 auStack_670 [16];
  undefined1 auStack_660 [16];
  undefined1 auStack_650 [16];
  undefined1 auStack_640 [16];
  undefined1 auStack_630 [16];
  undefined1 auStack_620 [8];
  undefined4 uStack_618;
  undefined4 uStack_614;
  undefined1 auStack_610 [16];
  undefined1 auStack_600 [16];
  undefined1 auStack_5f0 [8];
  undefined4 uStack_5e8;
  undefined4 uStack_5e4;
  undefined1 auStack_5e0 [16];
  undefined1 auStack_5d0 [16];
  undefined1 auStack_5c0 [8];
  undefined4 uStack_5b8;
  undefined4 uStack_5b4;
  undefined1 auStack_5b0 [16];
  undefined1 auStack_5a0 [16];
  undefined1 auStack_590 [8];
  undefined4 uStack_588;
  undefined4 uStack_584;
  undefined1 auStack_580 [16];
  undefined1 auStack_570 [16];
  undefined1 auStack_560 [8];
  float fStack_558;
  undefined4 uStack_554;
  undefined1 auStack_550 [16];
  undefined1 auStack_540 [16];
  undefined1 auStack_530 [8];
  float fStack_528;
  undefined4 uStack_524;
  undefined1 auStack_520 [16];
  undefined1 auStack_510 [16];
  undefined1 auStack_500 [16];
  undefined1 auStack_4f0 [16];
  undefined1 auStack_4e0 [16];
  undefined1 auStack_4d0 [16];
  undefined1 auStack_4c0 [8];
  float fStack_4b8;
  float fStack_4b4;
  undefined1 auStack_4b0 [8];
  float fStack_4a8;
  float fStack_4a4;
  undefined1 auStack_4a0 [8];
  float fStack_498;
  float fStack_494;
  undefined1 auStack_490 [8];
  float fStack_488;
  float fStack_484;
  undefined1 auStack_480 [16];
  undefined1 auStack_470 [8];
  undefined4 uStack_468;
  undefined4 uStack_464;
  undefined1 auStack_460 [8];
  undefined4 uStack_458;
  undefined4 uStack_454;
  undefined1 uStack_450;
  undefined1 uStack_44f;
  byte bStack_44e;
  byte bStack_44d;
  undefined4 uStack_44c;
  undefined4 uStack_448;
  undefined4 uStack_444;
  undefined1 uStack_440;
  undefined1 uStack_43f;
  undefined1 uStack_43e;
  undefined1 uStack_43d;
  undefined4 uStack_43c;
  undefined4 uStack_438;
  undefined4 uStack_434;
  undefined1 auStack_430 [16];
  undefined1 auStack_420 [16];
  undefined1 auStack_410 [16];
  undefined1 auStack_400 [16];
  float fStack_3f0;
  float fStack_3ec;
  float fStack_3e8;
  float fStack_3e4;
  float fStack_3e0;
  float fStack_3dc;
  float fStack_3d8;
  float fStack_3d4;
  float fStack_3d0;
  float fStack_3cc;
  float fStack_3c8;
  float fStack_3c4;
  float fStack_3c0;
  float fStack_3bc;
  float fStack_3b8;
  float fStack_3b4;
  float fStack_3b0;
  float fStack_3ac;
  float fStack_3a8;
  float fStack_3a4;
  float fStack_3a0;
  float fStack_39c;
  float fStack_398;
  float fStack_394;
  float fStack_390;
  float fStack_38c;
  float fStack_388;
  float fStack_384;
  undefined1 auStack_380 [8];
  float fStack_378;
  float fStack_374;
  float fStack_370;
  float fStack_36c;
  float fStack_368;
  float fStack_364;
  float fStack_350;
  float fStack_34c;
  float fStack_348;
  float fStack_344;
  float fStack_340;
  float fStack_33c;
  float fStack_338;
  float fStack_334;
  float fStack_330;
  float fStack_32c;
  float fStack_328;
  float fStack_324;
  float fStack_320;
  float fStack_31c;
  float fStack_318;
  float fStack_314;
  undefined1 auStack_310 [4];
  float afStack_30c [3];
  undefined1 auStack_300 [16];
  undefined4 uStack_2f0;
  undefined4 uStack_2ec;
  undefined4 uStack_2e8;
  undefined4 uStack_2e4;
  undefined4 uStack_2e0;
  undefined4 uStack_2dc;
  undefined4 uStack_2d8;
  undefined4 uStack_2d4;
  undefined1 auStack_210 [4];
  float fStack_20c;
  undefined8 uStack_208;
  undefined1 auStack_200 [8];
  float fStack_1f8;
  undefined4 uStack_1f4;
  float fStack_1f0;
  float fStack_1ec;
  float fStack_1e8;
  undefined4 uStack_1e4;
  float fStack_1e0;
  float fStack_1dc;
  float fStack_1d8;
  undefined4 uStack_1d4;
  float fStack_1d0;
  float fStack_1cc;
  undefined4 uStack_1c8;
  undefined4 uStack_1c4;
  float afStack_1c0 [44];
  float fStack_110;
  float fStack_10c;
  float fStack_108;
  float fStack_104;
  int aiStack_100 [64];
  
  pfVar10 = (float *)auStack_210;
  fStack_110 = in_zero_lo;
  fStack_10c = in_zero_hi;
  fStack_108 = in_zero_udw;
  do {
    *pfVar10 = in_zero_lo;
    pfVar10[1] = in_zero_hi;
    pfVar10[2] = in_zero_udw;
    pfVar10[3] = in_register_0000000c;
    pfVar10 = pfVar10 + 4;
  } while (pfVar10 != &fStack_110);
  pfVar10 = (float *)auStack_310;
  do {
    *pfVar10 = in_zero_lo;
    pfVar10[1] = in_zero_hi;
    pfVar10[2] = in_zero_udw;
    pfVar10[3] = in_register_0000000c;
    pfVar10 = pfVar10 + 4;
  } while (pfVar10 != (float *)auStack_210);
  auStack_380._4_4_ = in_zero_hi;
  auStack_380._0_4_ = in_zero_lo;
  fStack_378 = in_zero_udw;
  fStack_374 = in_register_0000000c;
  fStack_3f0 = in_zero_lo;
  fStack_3ec = in_zero_hi;
  fStack_3e8 = in_zero_udw;
  fStack_3e4 = in_register_0000000c;
  fStack_3e0 = in_zero_lo;
  fStack_3dc = in_zero_hi;
  fStack_3d8 = in_zero_udw;
  fStack_3d4 = in_register_0000000c;
  fStack_3d0 = in_zero_lo;
  fStack_3cc = in_zero_hi;
  fStack_3c8 = in_zero_udw;
  fStack_3c4 = in_register_0000000c;
  fStack_3c0 = in_zero_lo;
  fStack_3bc = in_zero_hi;
  fStack_3b8 = in_zero_udw;
  fStack_3b4 = in_register_0000000c;
  fStack_3b0 = in_zero_lo;
  fStack_3ac = in_zero_hi;
  fStack_3a8 = in_zero_udw;
  fStack_3a4 = in_register_0000000c;
  fStack_3a0 = in_zero_lo;
  fStack_39c = in_zero_hi;
  fStack_398 = in_zero_udw;
  fStack_394 = in_register_0000000c;
  fStack_390 = in_zero_lo;
  fStack_38c = in_zero_hi;
  fStack_388 = in_zero_udw;
  fStack_384 = in_register_0000000c;
  fStack_370 = in_zero_lo;
  fStack_36c = in_zero_hi;
  fStack_368 = in_zero_udw;
  fStack_364 = in_register_0000000c;
  fStack_350 = in_zero_lo;
  fStack_34c = in_zero_hi;
  fStack_348 = in_zero_udw;
  fStack_344 = in_register_0000000c;
  fStack_340 = in_zero_lo;
  fStack_33c = in_zero_hi;
  fStack_338 = in_zero_udw;
  fStack_334 = in_register_0000000c;
  fStack_330 = in_zero_lo;
  fStack_32c = in_zero_hi;
  fStack_328 = in_zero_udw;
  fStack_324 = in_register_0000000c;
  fStack_320 = in_zero_lo;
  fStack_31c = in_zero_hi;
  fStack_318 = in_zero_udw;
  fStack_314 = in_register_0000000c;
  fStack_104 = in_register_0000000c;
  FUN_00472e10(auStack_430);
  iVar5 = func_0x00238ff0();
  iVar17 = (int)param_1;
  *(float *)(iVar17 + 0x24) = (float)(uint)(iVar5 - *(int *)(iVar17 + 0x20)) * 0.001;
  *(int *)(iVar17 + 0x20) = iVar5;
  uVar2 = *(ushort *)(*(int *)(*(int *)(iGpffff861c + 4) * 4 + 0x43fca8) + 0x6c);
  puVar6 = (undefined1 *)GetAnalogStickL__4CPadCFv(iGpffff861c);
  uStack_440 = *puVar6;
  uStack_43f = puVar6[1];
  uStack_43e = puVar6[2];
  uStack_43d = puVar6[3];
  uStack_43c = *(undefined4 *)(puVar6 + 4);
  uStack_438 = *(undefined4 *)(puVar6 + 8);
  uStack_434 = *(undefined4 *)(puVar6 + 0xc);
  puVar6 = (undefined1 *)GetAnalogStickR__4CPadCFv(iGpffff861c);
  uStack_450 = *puVar6;
  uStack_44f = puVar6[1];
  bStack_44e = puVar6[2];
  bStack_44d = puVar6[3];
  uStack_44c = *(undefined4 *)(puVar6 + 4);
  uStack_448 = *(undefined4 *)(puVar6 + 8);
  uStack_444 = *(undefined4 *)(puVar6 + 0xc);
  *(byte *)(iVar17 + 0x1a) = *(byte *)(iVar17 + 0x1a) & 0xfe | 1;
  if ((((iGpffff8610 != 0) && (*(int *)(iGpffff8610 + 0x4624) != 0)) &&
      (*(char *)(iGpffff8610 + 0x4866) == '\0')) &&
     (-1 < (long)((ulong)*(byte *)(iGpffff8610 + 0x24) << 0x3a))) {
    *(byte *)(iVar17 + 0x1a) = *(byte *)(iVar17 + 0x1a) & 0xfe;
  }
  *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0xf7;
  if ((long)((ulong)*(byte *)(iVar17 + 0x18) << 0x39) < 0) {
    func_0x0022e230(&uStack_450,0xffffffffffffffff);
    func_0x0022e230(&uStack_440,0xffffffffffffffff);
    return 1;
  }
  if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3e) < 0) {
    func_0x0022e230(&uStack_450,0xffffffffffffffff);
    func_0x0022e230(&uStack_440,0xffffffffffffffff);
    return 0;
  }
  if ((*(byte *)(iGpffff8610 + 0x24) & 1) != 0) {
    func_0x0022e230(&uStack_450,0xffffffffffffffff);
    func_0x0022e230(&uStack_440,0xffffffffffffffff);
    return 0;
  }
  switch(*(undefined2 *)(iVar17 + 0x1c)) {
  case 1:
    *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + *(float *)(iVar17 + 0x24) * 6.0;
    if (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    if (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    FUN_004baab0(0,0,0,0x3f800000,auStack_460);
    *(int *)(iVar17 + 0x70) = auStack_460._0_4_;
    *(int *)(iVar17 + 0x74) = auStack_460._4_4_;
    *(undefined4 *)(iVar17 + 0x78) = uStack_458;
    *(undefined4 *)(iVar17 + 0x7c) = uStack_454;
    *(float *)(iVar17 + 0x80) =
         (*(float *)(iVar17 + 0x84) *
         (((*(float *)(iGpffff8610 + 0x40b4) + *(float *)(iGpffff8610 + 0x40bc) + 10.0 + 10.0) / 2.0
          ) / 1.75)) / 512.0;
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x60));
    func_0x00202890(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 100));
    func_0x00202938(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x68));
    func_0x002027e8(uVar24,auStack_430,auStack_430);
    uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_480);
    func_0x00222df0(auStack_470,auStack_430,uVar8);
    *(int *)(iVar17 + 0x50) = auStack_470._0_4_;
    *(int *)(iVar17 + 0x54) = auStack_470._4_4_;
    *(undefined4 *)(iVar17 + 0x58) = uStack_468;
    *(undefined4 *)(iVar17 + 0x5c) = uStack_464;
    auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
    auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
    auVar25 = _vadd(auVar25,auVar26);
    auVar25 = _sqc2(auVar25);
    *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    break;
  case 2:
    if (*(short *)(iVar17 + 0x1e) == 0) {
      *(int *)(iVar17 + 0x100) = (int)*(undefined8 *)(iVar17 + 0x60);
      *(int *)(iVar17 + 0x104) = (int)((ulong)*(undefined8 *)(iVar17 + 0x60) >> 0x20);
      *(undefined4 *)(iVar17 + 0x108) = *(undefined4 *)(iVar17 + 0x68);
      *(undefined4 *)(iVar17 + 0x10c) = *(undefined4 *)(iVar17 + 0x6c);
    }
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    uVar24 = func_0x00222e40(-*(float *)(iVar17 + 0x108));
    func_0x002027e8(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(-*(float *)(iVar17 + 0x104));
    func_0x00202938(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(-*(float *)(iVar17 + 0x100));
    func_0x00202890(uVar24,auStack_430,auStack_430);
    FUN_004baab0(0x45800000,0x45800000,0x45800000,0,auStack_490);
    fStack_320 = auStack_490._0_4_;
    fStack_31c = auStack_490._4_4_;
    fStack_318 = fStack_488;
    fStack_314 = fStack_484;
    FUN_004baab0(0xc5800000,0xc5800000,0xc5800000,0,auStack_4a0);
    fStack_330 = auStack_4a0._0_4_;
    fStack_32c = auStack_4a0._4_4_;
    fStack_328 = fStack_498;
    fStack_324 = fStack_494;
    FUN_004baab0(0x45800000,0x45800000,0x45800000,0,auStack_4b0);
    fStack_340 = auStack_4b0._0_4_;
    fStack_33c = auStack_4b0._4_4_;
    fStack_338 = fStack_4a8;
    fStack_334 = fStack_4a4;
    FUN_004baab0(0xc5800000,0xc5800000,0xc5800000,0,auStack_4c0);
    fStack_350 = auStack_4c0._0_4_;
    fStack_34c = auStack_4c0._4_4_;
    fStack_348 = fStack_4b8;
    fStack_344 = fStack_4b4;
    for (iVar5 = 0; iVar5 < *(int *)(iVar17 + 0x1e8); iVar5 = iVar5 + 1) {
      if (*(int *)(iVar17 + iVar5 * 4 + 0x1a8) < 0x80) {
        iVar15 = iGpffff8610 + *(int *)(iVar17 + iVar5 * 4 + 0x1a8) * 0x510;
        if ((long)((ulong)*(byte *)(iVar15 + 0xb4) << 0x39) < 0) {
          __pl__7FVectorCFRC7FVector(auStack_660,iVar15 + 0x170,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(-*(float *)(iVar15 + 0x3b0),-*(float *)(iVar15 + 0x3b4),0,0x3f800000,
                               auStack_670);
          __pl__7FVectorCFRC7FVector(auStack_650,auStack_660,uVar8);
          __pl__7FVectorCFRC7FVector(auStack_690,iVar15 + 0x170,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(*(undefined4 *)(iVar15 + 0x3b0),-*(float *)(iVar15 + 0x3b4),0,
                               0x3f800000,auStack_6a0);
          __pl__7FVectorCFRC7FVector(auStack_680,auStack_690,uVar8);
          __pl__7FVectorCFRC7FVector(auStack_6c0,iVar15 + 0x170,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(0,-*(float *)(iVar15 + 0x3b4),-*(float *)(iVar15 + 0x3b8),0x3f800000,
                               auStack_6d0);
          __pl__7FVectorCFRC7FVector(auStack_6b0,auStack_6c0,uVar8);
          fStack_1f0 = auStack_6b0._0_4_;
          fStack_1ec = auStack_6b0._4_4_;
          fStack_1e8 = fStack_6a8;
          uStack_1e4 = uStack_6a4;
          __pl__7FVectorCFRC7FVector(auStack_6f0,iVar15 + 0x170,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(0,-*(float *)(iVar15 + 0x3b4),*(undefined4 *)(iVar15 + 0x3b8),
                               0x3f800000,auStack_700);
          __pl__7FVectorCFRC7FVector(auStack_6e0,auStack_6f0,uVar8);
          fStack_1e0 = auStack_6e0._0_4_;
          fStack_1dc = auStack_6e0._4_4_;
          fStack_1d8 = fStack_6d8;
          uStack_1d4 = uStack_6d4;
          __pl__7FVectorCFRC7FVector(auStack_720,iVar15 + 0x170,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(-*(float *)(iVar15 + 0x3b0),*(undefined4 *)(iVar15 + 0x3b4),0,
                               0x3f800000,auStack_730);
          __pl__7FVectorCFRC7FVector(auStack_710,auStack_720,uVar8);
          fStack_1d0 = auStack_710._0_4_;
          fStack_1cc = auStack_710._4_4_;
          uStack_1c8 = uStack_708;
          uStack_1c4 = uStack_704;
          __pl__7FVectorCFRC7FVector(auStack_750,iVar15 + 0x170,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(*(undefined4 *)(iVar15 + 0x3b0),*(undefined4 *)(iVar15 + 0x3b4),0,
                               0x3f800000,auStack_760);
          __pl__7FVectorCFRC7FVector(auStack_740,auStack_750,uVar8);
          afStack_1c0[0] = auStack_740._0_4_;
          afStack_1c0[1] = auStack_740._4_4_;
          afStack_1c0[2] = (float)uStack_738;
          afStack_1c0[3] = (float)uStack_734;
          __pl__7FVectorCFRC7FVector(auStack_780,iVar15 + 0x170,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar15 + 0x3b4),-*(float *)(iVar15 + 0x3b8),
                               0x3f800000,auStack_790);
          __pl__7FVectorCFRC7FVector(auStack_770,auStack_780,uVar8);
          afStack_1c0[4] = auStack_770._0_4_;
          afStack_1c0[5] = auStack_770._4_4_;
          afStack_1c0[6] = (float)uStack_768;
          afStack_1c0[7] = (float)uStack_764;
          __pl__7FVectorCFRC7FVector(auStack_7b0,iVar15 + 0x170,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar15 + 0x3b4),*(undefined4 *)(iVar15 + 0x3b8),
                               0x3f800000,auStack_7c0);
          __pl__7FVectorCFRC7FVector(auStack_7a0,auStack_7b0,uVar8);
          afStack_1c0[8] = auStack_7a0._0_4_;
          afStack_1c0[9] = auStack_7a0._4_4_;
          afStack_1c0[10] = (float)uStack_798;
          afStack_1c0[0xb] = (float)uStack_794;
        }
        else {
          __pl__7FVectorCFRC7FVector(auStack_4e0,iVar15 + 0x160,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(-*(float *)(iVar15 + 0x3b0),-*(float *)(iVar15 + 0x3b4),0,0x3f800000,
                               auStack_4f0);
          __pl__7FVectorCFRC7FVector(auStack_4d0,auStack_4e0,uVar8);
          __pl__7FVectorCFRC7FVector(auStack_510,iVar15 + 0x160,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(*(undefined4 *)(iVar15 + 0x3b0),-*(float *)(iVar15 + 0x3b4),0,
                               0x3f800000,auStack_520);
          __pl__7FVectorCFRC7FVector(auStack_500,auStack_510,uVar8);
          __pl__7FVectorCFRC7FVector(auStack_540,iVar15 + 0x160,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(0,-*(float *)(iVar15 + 0x3b4),-*(float *)(iVar15 + 0x3b8),0x3f800000,
                               auStack_550);
          __pl__7FVectorCFRC7FVector(auStack_530,auStack_540,uVar8);
          fStack_1f0 = auStack_530._0_4_;
          fStack_1ec = auStack_530._4_4_;
          fStack_1e8 = fStack_528;
          uStack_1e4 = uStack_524;
          __pl__7FVectorCFRC7FVector(auStack_570,iVar15 + 0x160,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(0,-*(float *)(iVar15 + 0x3b4),*(undefined4 *)(iVar15 + 0x3b8),
                               0x3f800000,auStack_580);
          __pl__7FVectorCFRC7FVector(auStack_560,auStack_570,uVar8);
          fStack_1e0 = auStack_560._0_4_;
          fStack_1dc = auStack_560._4_4_;
          fStack_1d8 = fStack_558;
          uStack_1d4 = uStack_554;
          __pl__7FVectorCFRC7FVector(auStack_5a0,iVar15 + 0x160,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(-*(float *)(iVar15 + 0x3b0),*(undefined4 *)(iVar15 + 0x3b4),0,
                               0x3f800000,auStack_5b0);
          __pl__7FVectorCFRC7FVector(auStack_590,auStack_5a0,uVar8);
          fStack_1d0 = auStack_590._0_4_;
          fStack_1cc = auStack_590._4_4_;
          uStack_1c8 = uStack_588;
          uStack_1c4 = uStack_584;
          __pl__7FVectorCFRC7FVector(auStack_5d0,iVar15 + 0x160,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(*(undefined4 *)(iVar15 + 0x3b0),*(undefined4 *)(iVar15 + 0x3b4),0,
                               0x3f800000,auStack_5e0);
          __pl__7FVectorCFRC7FVector(auStack_5c0,auStack_5d0,uVar8);
          afStack_1c0[0] = auStack_5c0._0_4_;
          afStack_1c0[1] = auStack_5c0._4_4_;
          afStack_1c0[2] = (float)uStack_5b8;
          afStack_1c0[3] = (float)uStack_5b4;
          __pl__7FVectorCFRC7FVector(auStack_600,iVar15 + 0x160,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar15 + 0x3b4),-*(float *)(iVar15 + 0x3b8),
                               0x3f800000,auStack_610);
          __pl__7FVectorCFRC7FVector(auStack_5f0,auStack_600,uVar8);
          afStack_1c0[4] = auStack_5f0._0_4_;
          afStack_1c0[5] = auStack_5f0._4_4_;
          afStack_1c0[6] = (float)uStack_5e8;
          afStack_1c0[7] = (float)uStack_5e4;
          __pl__7FVectorCFRC7FVector(auStack_630,iVar15 + 0x160,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar15 + 0x3b4),*(undefined4 *)(iVar15 + 0x3b8),
                               0x3f800000,auStack_640);
          __pl__7FVectorCFRC7FVector(auStack_620,auStack_630,uVar8);
          afStack_1c0[8] = auStack_620._0_4_;
          afStack_1c0[9] = auStack_620._4_4_;
          afStack_1c0[10] = (float)uStack_618;
          afStack_1c0[0xb] = (float)uStack_614;
        }
        func_0x00316c10(auStack_310,auStack_210,auStack_430,8);
        for (iVar15 = 0; iVar15 < 8; iVar15 = iVar15 + 1) {
          if (*(float *)(auStack_210 + iVar15 * 0x10) < fStack_340) {
            fStack_340 = *(float *)(auStack_210 + iVar15 * 0x10);
          }
          if (*(float *)(auStack_210 + iVar15 * 0x10 + 4) < fStack_33c) {
            fStack_33c = *(float *)(auStack_210 + iVar15 * 0x10 + 4);
          }
          if (*(float *)(auStack_210 + iVar15 * 0x10 + 8) < fStack_338) {
            fStack_338 = *(float *)(auStack_210 + iVar15 * 0x10 + 8);
          }
          if (fStack_350 < *(float *)(auStack_210 + iVar15 * 0x10)) {
            fStack_350 = *(float *)(auStack_210 + iVar15 * 0x10);
          }
          if (fStack_34c < *(float *)(auStack_210 + iVar15 * 0x10 + 4)) {
            fStack_34c = *(float *)(auStack_210 + iVar15 * 0x10 + 4);
          }
          if (fStack_348 < *(float *)(auStack_210 + iVar15 * 0x10 + 8)) {
            fStack_348 = *(float *)(auStack_210 + iVar15 * 0x10 + 8);
          }
          if (*(float *)(auStack_310 + iVar15 * 0x10) < fStack_320) {
            fStack_320 = *(float *)(auStack_310 + iVar15 * 0x10);
          }
          if (*(float *)(auStack_310 + iVar15 * 0x10 + 4) < fStack_31c) {
            fStack_31c = *(float *)(auStack_310 + iVar15 * 0x10 + 4);
          }
          if (*(float *)(auStack_310 + iVar15 * 0x10 + 8) < fStack_318) {
            fStack_318 = *(float *)(auStack_310 + iVar15 * 0x10 + 8);
          }
          if (fStack_330 < *(float *)(auStack_310 + iVar15 * 0x10)) {
            fStack_330 = *(float *)(auStack_310 + iVar15 * 0x10);
          }
          if (fStack_32c < *(float *)(auStack_310 + iVar15 * 0x10 + 4)) {
            fStack_32c = *(float *)(auStack_310 + iVar15 * 0x10 + 4);
          }
          if (fStack_328 < *(float *)(auStack_310 + iVar15 * 0x10 + 8)) {
            fStack_328 = *(float *)(auStack_310 + iVar15 * 0x10 + 8);
          }
        }
      }
      else {
        FUN_004baab0(*(undefined4 *)
                      (iGpffff8610 + (*(int *)(iVar17 + iVar5 * 4 + 0x1a8) + -0x80) * 8 + 0x403c),0,
                     *(undefined4 *)
                      (iGpffff8610 + (*(int *)(iVar17 + iVar5 * 4 + 0x1a8) + -0x80) * 8 + 0x4040),
                     0x3f800000,&uStack_7d0);
        uStack_208._0_4_ = (float)uStack_7c8;
        _auStack_210 = uStack_7d0;
        uStack_208._4_4_ = (float)uStack_7c4;
        func_0x00316c10(auStack_310,auStack_210,auStack_430,1);
        if ((float)auStack_210 < fStack_340) {
          fStack_340 = (float)auStack_210;
        }
        if (fStack_20c < fStack_33c) {
          fStack_33c = fStack_20c;
        }
        if ((float)uStack_208 < fStack_338) {
          fStack_338 = (float)uStack_208;
        }
        if (fStack_350 < (float)auStack_210) {
          fStack_350 = (float)auStack_210;
        }
        if (fStack_34c < fStack_20c) {
          fStack_34c = fStack_20c;
        }
        if (fStack_348 < (float)uStack_208) {
          fStack_348 = (float)uStack_208;
        }
        if ((float)auStack_310 < fStack_320) {
          fStack_320 = (float)auStack_310;
        }
        if (afStack_30c[0] < fStack_31c) {
          fStack_31c = afStack_30c[0];
        }
        if (afStack_30c[1] < fStack_318) {
          fStack_318 = afStack_30c[1];
        }
        if (fStack_330 < (float)auStack_310) {
          fStack_330 = (float)auStack_310;
        }
        if (fStack_32c < afStack_30c[0]) {
          fStack_32c = afStack_30c[0];
        }
        if (fStack_328 < afStack_30c[1]) {
          fStack_328 = afStack_30c[1];
        }
      }
    }
    FUN_004baab0((fStack_350 + fStack_340) / 2.0,(fStack_34c + fStack_33c) / 2.0,
                 (fStack_348 + fStack_338) / 2.0,0x3f800000,&uStack_7e0);
    uStack_208._0_4_ = (float)uStack_7d8;
    _auStack_210 = uStack_7e0;
    uStack_208._4_4_ = (float)uStack_7d4;
    auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
    auVar25 = _lqc2(_auStack_210);
    auVar25 = _vsub(auVar25,auVar26);
    _auStack_210 = _sqc2(auVar25);
    if (*(short *)(iVar17 + 0x1e) != 0) {
      func_0x00223030(0x40c00000,auStack_210);
    }
    auVar26 = _lqc2(_auStack_210);
    auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
    auVar25 = _vadd(auVar25,auVar26);
    auVar25 = _sqc2(auVar25);
    *(undefined1 (*) [16])(iVar17 + 0x70) = auVar25;
    FUN_004baab0(fStack_330 - fStack_320,fStack_32c - fStack_31c,0,0x3f800000,&uStack_7f0);
    uStack_208._0_4_ = (float)uStack_7e8;
    _auStack_210 = uStack_7f0;
    uStack_208._4_4_ = (float)uStack_7e4;
    FUN_004baab0(fStack_330 - fStack_320,0,(fStack_328 - fStack_318) / 2.0,0x3f800000,&uStack_800);
    fStack_1f8 = (float)uStack_7f8;
    auStack_200 = (undefined1  [8])uStack_800;
    uStack_1f4 = uStack_7f4;
    fVar22 = (float)func_0x00222fd0(auStack_210);
    fVar23 = (float)func_0x00222fd0(auStack_200);
    fVar23 = fVar23 + 20.0;
    if (fVar23 <= fVar22) {
      fVar23 = fVar22;
    }
    fVar23 = (fVar23 + 40.0) * (*(float *)(iVar17 + 0x84) / 512.0) - *(float *)(iVar17 + 0x80);
    if (*(short *)(iVar17 + 0x1e) != 0) {
      fVar23 = fVar23 / 6.0;
    }
    *(float *)(iVar17 + 0x80) = *(float *)(iVar17 + 0x80) + fVar23;
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x100));
    func_0x00202890(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x104));
    func_0x00202938(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x108));
    func_0x002027e8(uVar24,auStack_430,auStack_430);
    uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_830);
    func_0x00222df0(auStack_820,auStack_430,uVar8);
    __pl__7FVectorCFRC7FVector(auStack_810,auStack_820,iVar17 + 0x70);
    *(int *)(iVar17 + 0x50) = auStack_810._0_4_;
    *(int *)(iVar17 + 0x54) = auStack_810._4_4_;
    *(undefined4 *)(iVar17 + 0x58) = uStack_808;
    *(undefined4 *)(iVar17 + 0x5c) = uStack_804;
    CameraYPosCheck__9BtlCameraFv(param_1);
    FUN_004baab0(0x43b40000,0x43b40000,0x43b40000,0x3f800000,auStack_840);
    fStack_3a0 = auStack_840._0_4_;
    fStack_39c = auStack_840._4_4_;
    fStack_398 = fStack_838;
    fStack_394 = fStack_834;
    FUN_004baab0(0xc3b40000,0xc3b40000,0xc3b40000,0x3f800000,auStack_850);
    fStack_3b0 = auStack_850._0_4_;
    fStack_3ac = auStack_850._4_4_;
    fStack_3a8 = fStack_848;
    fStack_3a4 = fStack_844;
    for (iVar5 = 0; iVar5 < *(int *)(iVar17 + 0x1e8); iVar5 = iVar5 + 1) {
      if (*(int *)(iVar17 + iVar5 * 4 + 0x1a8) < 0x80) {
        iVar15 = iGpffff8610 + *(int *)(iVar17 + iVar5 * 4 + 0x1a8) * 0x510;
        if ((long)((ulong)*(byte *)(iVar15 + 0xb4) << 0x39) < 0) {
          __pl__7FVectorCFRC7FVector(auStack_9f0,iVar15 + 0x170,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(-*(float *)(iVar15 + 0x3b0),-*(float *)(iVar15 + 0x3b4),0,0x3f800000,
                               auStack_a00);
          __pl__7FVectorCFRC7FVector(&uStack_9e0,auStack_9f0,uVar8);
          uStack_208._0_4_ = (float)uStack_9d8;
          _auStack_210 = uStack_9e0;
          uStack_208._4_4_ = (float)uStack_9d4;
          __pl__7FVectorCFRC7FVector(auStack_a20,iVar15 + 0x170,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(*(undefined4 *)(iVar15 + 0x3b0),-*(float *)(iVar15 + 0x3b4),0,
                               0x3f800000,auStack_a30);
          __pl__7FVectorCFRC7FVector(&uStack_a10,auStack_a20,uVar8);
          fStack_1f8 = (float)uStack_a08;
          auStack_200 = (undefined1  [8])uStack_a10;
          uStack_1f4 = uStack_a04;
          __pl__7FVectorCFRC7FVector(auStack_a50,iVar15 + 0x170,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(0,-*(float *)(iVar15 + 0x3b4),-*(float *)(iVar15 + 0x3b8),0x3f800000,
                               auStack_a60);
          __pl__7FVectorCFRC7FVector(auStack_a40,auStack_a50,uVar8);
          fStack_1f0 = auStack_a40._0_4_;
          fStack_1ec = auStack_a40._4_4_;
          fStack_1e8 = fStack_a38;
          uStack_1e4 = uStack_a34;
          __pl__7FVectorCFRC7FVector(auStack_a80,iVar15 + 0x170,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(0,-*(float *)(iVar15 + 0x3b4),*(undefined4 *)(iVar15 + 0x3b8),
                               0x3f800000,auStack_a90);
          __pl__7FVectorCFRC7FVector(auStack_a70,auStack_a80,uVar8);
          fStack_1e0 = auStack_a70._0_4_;
          fStack_1dc = auStack_a70._4_4_;
          fStack_1d8 = fStack_a68;
          uStack_1d4 = uStack_a64;
          __pl__7FVectorCFRC7FVector(auStack_ab0,iVar15 + 0x170,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(-*(float *)(iVar15 + 0x3b0),*(undefined4 *)(iVar15 + 0x3b4),0,
                               0x3f800000,auStack_ac0);
          __pl__7FVectorCFRC7FVector(auStack_aa0,auStack_ab0,uVar8);
          fStack_1d0 = auStack_aa0._0_4_;
          fStack_1cc = auStack_aa0._4_4_;
          uStack_1c8 = uStack_a98;
          uStack_1c4 = uStack_a94;
          __pl__7FVectorCFRC7FVector(auStack_ae0,iVar15 + 0x170,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(*(undefined4 *)(iVar15 + 0x3b0),*(undefined4 *)(iVar15 + 0x3b4),0,
                               0x3f800000,auStack_af0);
          __pl__7FVectorCFRC7FVector(auStack_ad0,auStack_ae0,uVar8);
          afStack_1c0[0] = auStack_ad0._0_4_;
          afStack_1c0[1] = auStack_ad0._4_4_;
          afStack_1c0[2] = (float)uStack_ac8;
          afStack_1c0[3] = (float)uStack_ac4;
          __pl__7FVectorCFRC7FVector(auStack_b10,iVar15 + 0x170,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar15 + 0x3b4),-*(float *)(iVar15 + 0x3b8),
                               0x3f800000,auStack_b20);
          __pl__7FVectorCFRC7FVector(auStack_b00,auStack_b10,uVar8);
          afStack_1c0[4] = auStack_b00._0_4_;
          afStack_1c0[5] = auStack_b00._4_4_;
          afStack_1c0[6] = (float)uStack_af8;
          afStack_1c0[7] = (float)uStack_af4;
          __pl__7FVectorCFRC7FVector(auStack_b40,iVar15 + 0x170,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar15 + 0x3b4),*(undefined4 *)(iVar15 + 0x3b8),
                               0x3f800000,auStack_b50);
          __pl__7FVectorCFRC7FVector(auStack_b30,auStack_b40,uVar8);
          afStack_1c0[8] = auStack_b30._0_4_;
          afStack_1c0[9] = auStack_b30._4_4_;
          afStack_1c0[10] = (float)uStack_b28;
          afStack_1c0[0xb] = (float)uStack_b24;
        }
        else {
          __pl__7FVectorCFRC7FVector(auStack_870,iVar15 + 0x160,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(-*(float *)(iVar15 + 0x3b0),-*(float *)(iVar15 + 0x3b4),0,0x3f800000,
                               auStack_880);
          __pl__7FVectorCFRC7FVector(&uStack_860,auStack_870,uVar8);
          uStack_208._0_4_ = (float)uStack_858;
          _auStack_210 = uStack_860;
          uStack_208._4_4_ = (float)uStack_854;
          __pl__7FVectorCFRC7FVector(auStack_8a0,iVar15 + 0x160,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(*(undefined4 *)(iVar15 + 0x3b0),-*(float *)(iVar15 + 0x3b4),0,
                               0x3f800000,auStack_8b0);
          __pl__7FVectorCFRC7FVector(&uStack_890,auStack_8a0,uVar8);
          fStack_1f8 = (float)uStack_888;
          auStack_200 = (undefined1  [8])uStack_890;
          uStack_1f4 = uStack_884;
          __pl__7FVectorCFRC7FVector(auStack_8d0,iVar15 + 0x160,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(0,-*(float *)(iVar15 + 0x3b4),-*(float *)(iVar15 + 0x3b8),0x3f800000,
                               auStack_8e0);
          __pl__7FVectorCFRC7FVector(auStack_8c0,auStack_8d0,uVar8);
          fStack_1f0 = auStack_8c0._0_4_;
          fStack_1ec = auStack_8c0._4_4_;
          fStack_1e8 = fStack_8b8;
          uStack_1e4 = uStack_8b4;
          __pl__7FVectorCFRC7FVector(auStack_900,iVar15 + 0x160,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(0,-*(float *)(iVar15 + 0x3b4),*(undefined4 *)(iVar15 + 0x3b8),
                               0x3f800000,auStack_910);
          __pl__7FVectorCFRC7FVector(auStack_8f0,auStack_900,uVar8);
          fStack_1e0 = auStack_8f0._0_4_;
          fStack_1dc = auStack_8f0._4_4_;
          fStack_1d8 = fStack_8e8;
          uStack_1d4 = uStack_8e4;
          __pl__7FVectorCFRC7FVector(auStack_930,iVar15 + 0x160,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(-*(float *)(iVar15 + 0x3b0),*(undefined4 *)(iVar15 + 0x3b4),0,
                               0x3f800000,auStack_940);
          __pl__7FVectorCFRC7FVector(auStack_920,auStack_930,uVar8);
          fStack_1d0 = auStack_920._0_4_;
          fStack_1cc = auStack_920._4_4_;
          uStack_1c8 = uStack_918;
          uStack_1c4 = uStack_914;
          __pl__7FVectorCFRC7FVector(auStack_960,iVar15 + 0x160,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(*(undefined4 *)(iVar15 + 0x3b0),*(undefined4 *)(iVar15 + 0x3b4),0,
                               0x3f800000,auStack_970);
          __pl__7FVectorCFRC7FVector(auStack_950,auStack_960,uVar8);
          afStack_1c0[0] = auStack_950._0_4_;
          afStack_1c0[1] = auStack_950._4_4_;
          afStack_1c0[2] = (float)uStack_948;
          afStack_1c0[3] = (float)uStack_944;
          __pl__7FVectorCFRC7FVector(auStack_990,iVar15 + 0x160,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar15 + 0x3b4),-*(float *)(iVar15 + 0x3b8),
                               0x3f800000,auStack_9a0);
          __pl__7FVectorCFRC7FVector(auStack_980,auStack_990,uVar8);
          afStack_1c0[4] = auStack_980._0_4_;
          afStack_1c0[5] = auStack_980._4_4_;
          afStack_1c0[6] = (float)uStack_978;
          afStack_1c0[7] = (float)uStack_974;
          __pl__7FVectorCFRC7FVector(auStack_9c0,iVar15 + 0x160,iVar15 + 0x3a0);
          uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar15 + 0x3b4),*(undefined4 *)(iVar15 + 0x3b8),
                               0x3f800000,auStack_9d0);
          __pl__7FVectorCFRC7FVector(auStack_9b0,auStack_9c0,uVar8);
          afStack_1c0[8] = auStack_9b0._0_4_;
          afStack_1c0[9] = auStack_9b0._4_4_;
          afStack_1c0[10] = (float)uStack_9a8;
          afStack_1c0[0xb] = (float)uStack_9a4;
        }
        for (iVar15 = 0; iVar15 < 8; iVar15 = iVar15 + 1) {
          __mi__7FVectorCFRC7FVector(&uStack_b60,iVar17 + 0x50,auStack_210 + iVar15 * 0x10);
          afStack_30c[1] = (float)uStack_b58;
          _auStack_310 = uStack_b60;
          afStack_30c[2] = (float)uStack_b54;
          uVar8 = func_0x00222f00(auStack_b80,auStack_310);
          Get3DAngle__F7FVector(auStack_b70,uVar8);
          fStack_368 = fStack_b68;
          fStack_364 = fStack_b64;
          fStack_36c = auStack_b70._4_4_ - (180.0 - *(float *)(iVar17 + 0x104));
          for (fStack_370 = auStack_b70._0_4_ - *(float *)(iVar17 + 0x100); fStack_370 < -180.0;
              fStack_370 = fStack_370 + 360.0) {
          }
          for (; 180.0 < fStack_370; fStack_370 = fStack_370 - 360.0) {
          }
          for (; fStack_36c < -180.0; fStack_36c = fStack_36c + 360.0) {
          }
          for (; 180.0 < fStack_36c; fStack_36c = fStack_36c - 360.0) {
          }
          if (fStack_370 < fStack_3a0) {
            fStack_3a0 = fStack_370;
            iVar12 = iVar15 * 0x10;
            fStack_3b8 = *(float *)(auStack_210 + iVar12 + 8);
            fStack_3b4 = *(float *)(auStack_210 + iVar12 + 0xc);
            fStack_3c0 = (float)*(undefined8 *)(auStack_210 + iVar12);
            fStack_3bc = (float)((ulong)*(undefined8 *)(auStack_210 + iVar12) >> 0x20);
          }
          if (fStack_36c < fStack_39c) {
            fStack_39c = fStack_36c;
            iVar12 = iVar15 * 0x10;
            fStack_3c8 = *(float *)(auStack_210 + iVar12 + 8);
            fStack_3c4 = *(float *)(auStack_210 + iVar12 + 0xc);
            fStack_3d0 = (float)*(undefined8 *)(auStack_210 + iVar12);
            fStack_3cc = (float)((ulong)*(undefined8 *)(auStack_210 + iVar12) >> 0x20);
          }
          if (fStack_3b0 < fStack_370) {
            fStack_3b0 = fStack_370;
            iVar12 = iVar15 * 0x10;
            fStack_3d8 = *(float *)(auStack_210 + iVar12 + 8);
            fStack_3d4 = *(float *)(auStack_210 + iVar12 + 0xc);
            fStack_3e0 = (float)*(undefined8 *)(auStack_210 + iVar12);
            fStack_3dc = (float)((ulong)*(undefined8 *)(auStack_210 + iVar12) >> 0x20);
          }
          if (fStack_3ac < fStack_36c) {
            fStack_3ac = fStack_36c;
            iVar12 = iVar15 * 0x10;
            fStack_3e8 = *(float *)(auStack_210 + iVar12 + 8);
            fStack_3e4 = *(float *)(auStack_210 + iVar12 + 0xc);
            fStack_3f0 = (float)*(undefined8 *)(auStack_210 + iVar12);
            fStack_3ec = (float)((ulong)*(undefined8 *)(auStack_210 + iVar12) >> 0x20);
          }
        }
      }
      else {
        FUN_004baab0(*(undefined4 *)
                      (iGpffff8610 + (*(int *)(iVar17 + iVar5 * 4 + 0x1a8) + -0x80) * 8 + 0x403c),0,
                     *(undefined4 *)
                      (iGpffff8610 + (*(int *)(iVar17 + iVar5 * 4 + 0x1a8) + -0x80) * 8 + 0x4040),
                     0x3f800000,&uStack_b90);
        uStack_208._0_4_ = (float)uStack_b88;
        _auStack_210 = uStack_b90;
        uStack_208._4_4_ = (float)uStack_b84;
        __mi__7FVectorCFRC7FVector(&uStack_ba0,iVar17 + 0x50,auStack_210);
        afStack_30c[1] = (float)uStack_b98;
        _auStack_310 = uStack_ba0;
        afStack_30c[2] = (float)uStack_b94;
        uVar8 = func_0x00222f00(auStack_bc0,auStack_310);
        Get3DAngle__F7FVector(auStack_bb0,uVar8);
        fStack_368 = fStack_ba8;
        fStack_364 = fStack_ba4;
        fStack_36c = auStack_bb0._4_4_ - (180.0 - *(float *)(iVar17 + 0x104));
        for (fStack_370 = auStack_bb0._0_4_ - *(float *)(iVar17 + 0x100); fStack_370 < -180.0;
            fStack_370 = fStack_370 + 360.0) {
        }
        for (; 180.0 < fStack_370; fStack_370 = fStack_370 - 360.0) {
        }
        for (; fStack_36c < -180.0; fStack_36c = fStack_36c + 360.0) {
        }
        for (; 180.0 < fStack_36c; fStack_36c = fStack_36c - 360.0) {
        }
        fVar23 = auStack_210;
        fVar22 = auStack_210._4_4_;
        if (fStack_370 < fStack_3a0) {
          fStack_3a0 = fStack_370;
          fStack_3b8 = (float)uStack_208;
          fStack_3b4 = uStack_208._4_4_;
          fStack_3c0 = fVar23;
          fStack_3bc = fVar22;
        }
        if (fStack_36c < fStack_39c) {
          fStack_39c = fStack_36c;
          fStack_3c8 = (float)uStack_208;
          fStack_3c4 = uStack_208._4_4_;
          fStack_3d0 = fVar23;
          fStack_3cc = fVar22;
        }
        if (fStack_3b0 < fStack_370) {
          fStack_3b0 = fStack_370;
          fStack_3d8 = (float)uStack_208;
          fStack_3d4 = uStack_208._4_4_;
          fStack_3e0 = fVar23;
          fStack_3dc = fVar22;
        }
        if (fStack_3ac < fStack_36c) {
          fStack_3ac = fStack_36c;
          fStack_3e8 = (float)uStack_208;
          fStack_3e4 = uStack_208._4_4_;
          fStack_3f0 = fVar23;
          fStack_3ec = fVar22;
        }
      }
    }
    for (fVar23 = (*(float *)(iVar17 + 0x100) + (fStack_3b0 + fStack_3a0) / 2.0) -
                  *(float *)(iVar17 + 0x60); fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
    }
    if (*(short *)(iVar17 + 0x1e) != 0) {
      fVar23 = fVar23 / 6.0;
    }
    *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + fVar23;
    if (*(float *)(iVar17 + 0x60) < -180.0) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
    }
    if (180.0 < *(float *)(iVar17 + 0x60)) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
    }
    for (fVar23 = (*(float *)(iVar17 + 0x104) - (fStack_3ac + fStack_39c) / 2.0) -
                  *(float *)(iVar17 + 100); fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
    }
    if (*(short *)(iVar17 + 0x1e) != 0) {
      fVar23 = fVar23 / 6.0;
    }
    *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + fVar23;
    if (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    if (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    *(undefined2 *)(iVar17 + 0x1e) = 1;
    break;
  case 4:
    iVar5 = 0;
    for (uVar14 = 0; (int)uVar14 < 0xc; uVar14 = uVar14 + 1) {
      if ((*(uint *)(iVar17 + 0xd4) & 1 << (uVar14 & 0x1f)) != 0) {
        __pl__7FVectorCFRC7FVector
                  (auStack_bd0,iGpffff8610 + uVar14 * 0x510 + 0x160,
                   iGpffff8610 + uVar14 * 0x510 + 0x3a0);
        iVar15 = iVar5 * 0x10;
        *(int *)(auStack_210 + iVar15) = auStack_bd0._0_4_;
        *(int *)(auStack_210 + iVar15 + 4) = auStack_bd0._4_4_;
        *(undefined4 *)(auStack_210 + iVar15 + 8) = uStack_bc8;
        *(undefined4 *)(auStack_210 + iVar15 + 0xc) = uStack_bc4;
        *(undefined4 *)(auStack_310 + iVar5 * 0x10) =
             *(undefined4 *)(iGpffff8610 + uVar14 * 0x510 + 0x354);
        *(undefined4 *)(auStack_310 + iVar5 * 0x10 + 4) =
             *(undefined4 *)(iGpffff8610 + uVar14 * 0x510 + 0x3b4);
        iVar5 = iVar5 + 1;
      }
    }
    _auStack_380 = _auStack_210;
    for (iVar15 = 1; iVar15 < iVar5; iVar15 = iVar15 + 1) {
      auVar26 = _lqc2(*(undefined1 (*) [16])(auStack_210 + iVar15 * 0x10));
      auVar25 = _lqc2(_auStack_380);
      auVar25 = _vadd(auVar25,auVar26);
      _auStack_380 = _sqc2(auVar25);
    }
    func_0x00223030((float)iVar5,auStack_380);
    FUN_004baab0(0,0,0,0x3f800000,auStack_be0);
    fStack_390 = auStack_be0._0_4_;
    fStack_38c = auStack_be0._4_4_;
    fStack_388 = (float)uStack_bd8;
    fStack_384 = fStack_bd4;
    for (iVar15 = 0; iVar15 < iVar5; iVar15 = iVar15 + 1) {
      __mi__7FVectorCFRC7FVector(auStack_bf0,auStack_210 + iVar15 * 0x10,auStack_380);
      fStack_110 = auStack_bf0._0_4_;
      fStack_108 = fStack_be8;
      fStack_104 = fStack_be4;
      fStack_10c = 0.0;
      fVar22 = (float)func_0x00222fd0(&fStack_110);
      fVar23 = *(float *)(auStack_310 + iVar15 * 0x10) + fVar22;
      if (*(float *)(auStack_310 + iVar15 * 0x10) + fVar22 <= fStack_390) {
        fVar23 = fStack_390;
      }
      fStack_390 = fVar23;
      fStack_110 = *(float *)(auStack_210 + iVar15 * 0x10 + 4) -
                   *(float *)(auStack_310 + iVar15 * 0x10 + 4);
      fStack_110 = (*(float *)(auStack_210 + iVar15 * 0x10 + 4) -
                   *(float *)(auStack_310 + iVar15 * 0x10 + 4)) - (float)auStack_380._4_4_;
      fStack_10c = (*(float *)(auStack_210 + iVar15 * 0x10 + 4) +
                   *(float *)(auStack_310 + iVar15 * 0x10 + 4)) - (float)auStack_380._4_4_;
      if (fStack_110 < 0.0) {
        fStack_110 = fStack_110 * -1.0;
      }
      if (fStack_10c < 0.0) {
        fStack_10c = fStack_10c * -1.0;
      }
      if (fStack_38c < fStack_110) {
        fStack_38c = fStack_110;
      }
      if (fStack_38c < fStack_10c) {
        fStack_38c = fStack_10c;
      }
    }
    fStack_388 = fStack_390;
    iVar5 = iGpffff8610 + *(int *)(iVar17 + 0xd8) * 0x510;
    __pl__7FVectorCFRC7FVector(&uStack_c00,iVar5 + 0x160,iVar5 + 0x3a0);
    uStack_208._0_4_ = (float)uStack_bf8;
    _auStack_210 = uStack_c00;
    uStack_208._4_4_ = (float)uStack_bf4;
    auVar26 = _lqc2(_auStack_380);
    auVar25 = _lqc2(_auStack_210);
    auVar25 = _vsub(auVar25,auVar26);
    _auStack_210 = _sqc2(auVar25);
    FUN_004baab0(*(undefined4 *)(iGpffff8610 + 0x40b4),0,*(undefined4 *)(iGpffff8610 + 0x40bc),
                 0x3f800000,auStack_c10);
    if (*(int *)(iVar17 + 0xdc) == 0) {
      fVar23 = (float)func_0x00222fd0(auStack_210);
      fVar22 = (float)func_0x00222fd0(auStack_200);
      *(float *)(iVar17 + 0x84) = (fVar23 / (fVar22 * 0.75) + 1.2) * 512.0;
    }
    else {
      fVar23 = (float)func_0x00222fd0(auStack_210);
      fVar22 = (float)func_0x00222fd0(auStack_200);
      *(float *)(iVar17 + 0x84) =
           *(float *)(iVar17 + 0x84) +
           ((fVar23 / (fVar22 * 0.75) + 1.2) * 512.0 - *(float *)(iVar17 + 0x84)) * 3.75 *
           *(float *)(iVar17 + 0x24);
    }
    uVar8 = func_0x00222f00(auStack_c30,auStack_210);
    Get3DAngle__F7FVector(&uStack_c20,uVar8);
    fStack_1f8 = (float)uStack_c18;
    auStack_200 = (undefined1  [8])uStack_c20;
    uStack_1f4 = uStack_c14;
    fVar23 = fStack_38c;
    if (fStack_38c < 4.0) {
      fVar23 = 4.0;
    }
    fVar20 = (float)func_0x00222fd0(&fStack_390);
    fVar20 = fStack_390 + fVar20;
    fVar21 = *(float *)(iVar17 + 0x84);
    fVar22 = -(float)auStack_200._0_4_;
    if ((fVar22 <= 40.0) && (fVar22 = fVar22 * 1.25 - 10.0, fVar22 < -10.0)) {
      fVar22 = -10.0;
    }
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    uVar24 = func_0x00222e40(fVar22);
    func_0x00202890(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
    func_0x00202938(uVar24,auStack_430,auStack_430);
    uVar8 = FUN_004baab0(0,0,-((fVar21 * (fVar20 + 30.0)) / 512.0),0x3f800000,auStack_c50);
    func_0x00222df0(&uStack_c40,auStack_430,uVar8);
    uStack_208._0_4_ = (float)uStack_c38;
    _auStack_210 = uStack_c40;
    uStack_208._4_4_ = (float)uStack_c34;
    uVar8 = FUN_004baab0(0,-fStack_38c - fVar23,0,0x3f800000,auStack_c70);
    __pl__7FVectorCFRC7FVector(auStack_c60,auStack_380,uVar8);
    auVar26 = _lqc2(auStack_c60);
    auVar25 = _lqc2(_auStack_210);
    auVar25 = _vadd(auVar25,auVar26);
    _auStack_210 = _sqc2(auVar25);
    if (-10.0 < fStack_20c) {
      fStack_20c = -10.0;
    }
    if (*(int *)(iVar17 + 0xdc) == 0) {
      *(int *)(iVar17 + 0x50) = auStack_210;
      *(int *)(iVar17 + 0x54) = auStack_210._4_4_;
      *(float *)(iVar17 + 0x58) = (float)uStack_208;
      *(float *)(iVar17 + 0x5c) = uStack_208._4_4_;
    }
    else {
      __mi__7FVectorCFRC7FVector(auStack_c80,auStack_210,iVar17 + 0x50);
      fStack_1f0 = auStack_c80._0_4_;
      fStack_1ec = auStack_c80._4_4_;
      fStack_1e8 = fStack_c78;
      uStack_1e4 = uStack_c74;
      __ml__7FVectorCFf(*(float *)(iVar17 + 0x24) * 7.5,auStack_c90,&fStack_1f0);
      auVar26 = _lqc2(auStack_c90);
      auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _vadd(auVar25,auVar26);
      auVar25 = _sqc2(auVar25);
      *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    __pl__7FVectorCFRC7FVector(auStack_cc0,iVar5 + 0x160,iVar5 + 0x3a0);
    uVar8 = FUN_004baab0(0,-*(float *)(iVar5 + 0x3b4),0,0x3f800000,auStack_cd0);
    __pl__7FVectorCFRC7FVector(auStack_cb0,auStack_cc0,uVar8);
    __mi__7FVectorCFRC7FVector(&uStack_ca0,auStack_cb0,iVar17 + 0x50);
    uStack_208._0_4_ = (float)uStack_c98;
    _auStack_210 = uStack_ca0;
    uStack_208._4_4_ = (float)uStack_c94;
    __pl__7FVectorCFRC7FVector(auStack_d00,iVar5 + 0x160,iVar5 + 0x3a0);
    uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar5 + 0x3b4),0,0x3f800000,auStack_d10);
    __pl__7FVectorCFRC7FVector(auStack_cf0,auStack_d00,uVar8);
    __mi__7FVectorCFRC7FVector(&uStack_ce0,auStack_cf0,iVar17 + 0x50);
    fStack_1f8 = (float)uStack_cd8;
    auStack_200 = (undefined1  [8])uStack_ce0;
    uStack_1f4 = uStack_cd4;
    uVar8 = FUN_004baab0(0,-fStack_38c,0,0x3f800000,auStack_d40);
    __pl__7FVectorCFRC7FVector(auStack_d30,auStack_380,uVar8);
    __mi__7FVectorCFRC7FVector(auStack_d20,auStack_d30,iVar17 + 0x50);
    fStack_1f0 = auStack_d20._0_4_;
    fStack_1ec = auStack_d20._4_4_;
    fStack_1e8 = fStack_d18;
    uStack_1e4 = uStack_d14;
    uVar8 = FUN_004baab0(0,fStack_38c * 0.5,0,0x3f800000,auStack_d70);
    __pl__7FVectorCFRC7FVector(auStack_d60,auStack_380,uVar8);
    __mi__7FVectorCFRC7FVector(auStack_d50,auStack_d60,iVar17 + 0x50);
    fStack_1e0 = auStack_d50._0_4_;
    fStack_1dc = auStack_d50._4_4_;
    fStack_1d8 = fStack_d48;
    uStack_1d4 = uStack_d44;
    uVar8 = func_0x00222f00(auStack_d90,auStack_210);
    Get3DAngle__F7FVector(auStack_d80,uVar8);
    fStack_1d0 = auStack_d80._0_4_;
    fStack_1cc = auStack_d80._4_4_;
    uStack_1c8 = uStack_d78;
    uStack_1c4 = uStack_d74;
    uVar8 = func_0x00222f00(auStack_db0,auStack_200);
    Get3DAngle__F7FVector(auStack_da0,uVar8);
    afStack_1c0[0] = auStack_da0._0_4_;
    afStack_1c0[1] = auStack_da0._4_4_;
    afStack_1c0[2] = (float)uStack_d98;
    afStack_1c0[3] = (float)uStack_d94;
    uVar8 = func_0x00222f00(auStack_dd0,&fStack_1f0);
    Get3DAngle__F7FVector(auStack_dc0,uVar8);
    afStack_1c0[4] = auStack_dc0._0_4_;
    afStack_1c0[5] = auStack_dc0._4_4_;
    afStack_1c0[6] = (float)uStack_db8;
    afStack_1c0[7] = (float)uStack_db4;
    uVar8 = func_0x00222f00(auStack_df0,&fStack_1e0);
    Get3DAngle__F7FVector(auStack_de0,uVar8);
    afStack_1c0[8] = (float)auStack_de0._0_4_;
    afStack_1c0[9] = (float)auStack_de0._4_4_;
    afStack_1c0[10] = (float)uStack_dd8;
    afStack_1c0[0xb] = (float)uStack_dd4;
    for (; fStack_1d0 < -180.0; fStack_1d0 = fStack_1d0 + 360.0) {
    }
    for (; 180.0 < fStack_1d0; fStack_1d0 = fStack_1d0 - 360.0) {
    }
    fVar23 = fStack_1d0;
    fVar22 = fStack_1d0;
    for (iVar5 = 5; iVar5 < 8; iVar5 = iVar5 + 1) {
      while (*(float *)(auStack_210 + iVar5 * 0x10) < -180.0) {
        *(float *)(auStack_210 + iVar5 * 0x10) = *(float *)(auStack_210 + iVar5 * 0x10) + 360.0;
      }
      while (180.0 < *(float *)(auStack_210 + iVar5 * 0x10)) {
        *(float *)(auStack_210 + iVar5 * 0x10) = *(float *)(auStack_210 + iVar5 * 0x10) - 360.0;
      }
      if (*(float *)(auStack_210 + iVar5 * 0x10) < fVar23) {
        fVar23 = *(float *)(auStack_210 + iVar5 * 0x10);
      }
      if (fVar22 < *(float *)(auStack_210 + iVar5 * 0x10)) {
        fVar22 = *(float *)(auStack_210 + iVar5 * 0x10);
      }
    }
    for (fVar22 = fVar22 - fVar23; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
    }
    for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
    }
    if (*(int *)(iVar17 + 0xdc) == 0) {
      *(float *)(iVar17 + 0x60) = -(fVar23 + fVar22 / 2.0);
    }
    else {
      for (fVar23 = -(fVar23 + fVar22 / 2.0) - *(float *)(iVar17 + 0x60); fVar23 < -180.0;
          fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 0x60) =
           *(float *)(iVar17 + 0x60) + fVar23 * 5.0 * *(float *)(iVar17 + 0x24);
    }
    while (*(float *)(iVar17 + 0x60) < -180.0) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 0x60)) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
    }
    for (fVar23 = fStack_1cc - afStack_1c0[5]; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
    }
    if (*(int *)(iVar17 + 0xdc) == 0) {
      *(float *)(iVar17 + 100) = -(afStack_1c0[5] + fVar23 / 2.0);
    }
    else {
      for (fVar23 = -(afStack_1c0[5] + fVar23 / 2.0) - *(float *)(iVar17 + 100); fVar23 < -180.0;
          fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + fVar23 * 7.5 * *(float *)(iVar17 + 0x24)
      ;
    }
    while (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    *(undefined4 *)(iVar17 + 0x68) = 0;
    *(undefined4 *)(iVar17 + 0xdc) = 1;
    break;
  case 5:
    iVar5 = 0;
    for (uVar14 = 0; (int)uVar14 < 0xc; uVar14 = uVar14 + 1) {
      if ((*(uint *)(iVar17 + 0xd4) & 1 << (uVar14 & 0x1f)) != 0) {
        __pl__7FVectorCFRC7FVector
                  (auStack_e00,iGpffff8610 + uVar14 * 0x510 + 0x160,
                   iGpffff8610 + uVar14 * 0x510 + 0x3a0);
        iVar15 = iVar5 * 0x10;
        *(int *)(auStack_210 + iVar15) = auStack_e00._0_4_;
        *(int *)(auStack_210 + iVar15 + 4) = auStack_e00._4_4_;
        *(undefined4 *)(auStack_210 + iVar15 + 8) = uStack_df8;
        *(undefined4 *)(auStack_210 + iVar15 + 0xc) = uStack_df4;
        *(undefined4 *)(auStack_310 + iVar5 * 0x10) =
             *(undefined4 *)(iGpffff8610 + uVar14 * 0x510 + 0x354);
        *(undefined4 *)(auStack_310 + iVar5 * 0x10 + 4) =
             *(undefined4 *)(iGpffff8610 + uVar14 * 0x510 + 0x3b4);
        iVar5 = iVar5 + 1;
      }
    }
    _auStack_380 = _auStack_210;
    for (iVar15 = 1; iVar15 < iVar5; iVar15 = iVar15 + 1) {
      auVar26 = _lqc2(*(undefined1 (*) [16])(auStack_210 + iVar15 * 0x10));
      auVar25 = _lqc2(_auStack_380);
      auVar25 = _vadd(auVar25,auVar26);
      _auStack_380 = _sqc2(auVar25);
    }
    func_0x00223030((float)iVar5,auStack_380);
    FUN_004baab0(0,0,0,0x3f800000,auStack_e10);
    fStack_390 = auStack_e10._0_4_;
    fStack_38c = auStack_e10._4_4_;
    fStack_388 = (float)uStack_e08;
    fStack_384 = fStack_e04;
    for (iVar15 = 0; iVar15 < iVar5; iVar15 = iVar15 + 1) {
      __mi__7FVectorCFRC7FVector(auStack_e20,auStack_210 + iVar15 * 0x10,auStack_380);
      fStack_110 = auStack_e20._0_4_;
      fStack_108 = fStack_e18;
      fStack_104 = fStack_e14;
      fStack_10c = 0.0;
      fVar22 = (float)func_0x00222fd0(&fStack_110);
      fVar23 = *(float *)(auStack_310 + iVar15 * 0x10) + fVar22;
      if (*(float *)(auStack_310 + iVar15 * 0x10) + fVar22 <= fStack_390) {
        fVar23 = fStack_390;
      }
      fStack_390 = fVar23;
      fStack_110 = *(float *)(auStack_210 + iVar15 * 0x10 + 4) -
                   *(float *)(auStack_310 + iVar15 * 0x10 + 4);
      fStack_110 = (*(float *)(auStack_210 + iVar15 * 0x10 + 4) -
                   *(float *)(auStack_310 + iVar15 * 0x10 + 4)) - (float)auStack_380._4_4_;
      fStack_10c = (*(float *)(auStack_210 + iVar15 * 0x10 + 4) +
                   *(float *)(auStack_310 + iVar15 * 0x10 + 4)) - (float)auStack_380._4_4_;
      if (fStack_110 < 0.0) {
        fStack_110 = fStack_110 * -1.0;
      }
      if (fStack_10c < 0.0) {
        fStack_10c = fStack_10c * -1.0;
      }
      if (fStack_38c < fStack_110) {
        fStack_38c = fStack_110;
      }
      if (fStack_38c < fStack_10c) {
        fStack_38c = fStack_10c;
      }
    }
    fStack_388 = fStack_390;
    *(int *)(iVar17 + 0x70) = auStack_380._0_4_;
    *(int *)(iVar17 + 0x74) = auStack_380._4_4_;
    *(float *)(iVar17 + 0x78) = fStack_378;
    *(float *)(iVar17 + 0x7c) = fStack_374;
    fVar23 = (float)func_0x00222fd0(&fStack_390);
    *(float *)(iVar17 + 0x80) = (*(float *)(iVar17 + 0x84) * (fStack_390 + fVar23 + 35.0)) / 512.0;
    if (*(int *)(iVar17 + 0xdc) == 0) {
      iVar5 = 0;
      for (fVar23 = -3.1415927; fVar23 <= 2.3561945; fVar23 = fVar23 + 0.7853982) {
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x100));
        func_0x00202890(uVar24,auStack_430,auStack_430);
        func_0x00202938(fVar23,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_e50);
        func_0x00222df0(auStack_e40,auStack_430,uVar8);
        __pl__7FVectorCFRC7FVector(auStack_e30,auStack_e40,iVar17 + 0x70);
        iVar15 = iVar5 * 0x10;
        *(int *)(auStack_210 + iVar15) = auStack_e30._0_4_;
        *(int *)(auStack_210 + iVar15 + 4) = auStack_e30._4_4_;
        *(undefined4 *)(auStack_210 + iVar15 + 8) = uStack_e28;
        *(undefined4 *)(auStack_210 + iVar15 + 0xc) = uStack_e24;
        fVar20 = *(float *)(iGpffff8610 + 0x40b4) / 2.0 + *(float *)(auStack_210 + iVar5 * 0x10);
        fVar22 = *(float *)(iGpffff8610 + 0x40b4) / 2.0 - *(float *)(auStack_210 + iVar5 * 0x10);
        if (fVar20 <= fVar22) {
          fVar22 = fVar20;
        }
        *(float *)(auStack_310 + iVar5 * 0x10) = fVar22;
        fVar20 = *(float *)(iGpffff8610 + 0x40bc) / 2.0 + *(float *)(auStack_210 + iVar5 * 0x10 + 8)
        ;
        fVar22 = *(float *)(iGpffff8610 + 0x40bc) / 2.0 - *(float *)(auStack_210 + iVar5 * 0x10 + 8)
        ;
        if (fVar20 <= fVar22) {
          fVar22 = fVar20;
        }
        *(float *)(auStack_310 + iVar5 * 0x10 + 8) = fVar22;
        *(float *)(auStack_310 + iVar5 * 0x10 + 4) = fVar23;
        if ((10.0 < *(float *)(auStack_310 + iVar5 * 0x10)) &&
           (10.0 < *(float *)(auStack_310 + iVar5 * 0x10 + 8))) {
          iVar5 = iVar5 + 1;
        }
      }
      iVar15 = func_0x00232cc8();
      iVar15 = (int)((float)iVar5 * ((float)iVar15 / 2.1474836e+09));
      iVar5 = iVar15 * 0x10;
      uVar8 = *(undefined8 *)(auStack_210 + iVar5);
      uVar24 = *(undefined4 *)(auStack_210 + iVar5 + 8);
      uVar9 = *(undefined4 *)(auStack_210 + iVar5 + 0xc);
      *(int *)(iVar17 + 0x50) = (int)uVar8;
      *(int *)(iVar17 + 0x54) = (int)((ulong)uVar8 >> 0x20);
      *(undefined4 *)(iVar17 + 0x58) = uVar24;
      *(undefined4 *)(iVar17 + 0x5c) = uVar9;
      *(undefined4 *)(iVar17 + 0x104) = *(undefined4 *)(auStack_310 + iVar15 * 0x10 + 4);
    }
    else {
      auVar25 = _vmr32(in_vf0);
      auVar26 = _vmr32(auVar25);
      auVar27 = _vmr32(auVar26);
      auStack_400 = _sqc2(in_vf0);
      auStack_410 = _sqc2(auVar25);
      auStack_420 = _sqc2(auVar26);
      auStack_430 = _sqc2(auVar27);
      uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x100));
      func_0x00202890(uVar24,auStack_430,auStack_430);
      func_0x00202938(*(undefined4 *)(iVar17 + 0x104),auStack_430,auStack_430);
      uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_e80);
      func_0x00222df0(auStack_e70,auStack_430,uVar8);
      __pl__7FVectorCFRC7FVector(&uStack_e60,auStack_e70,iVar17 + 0x70);
      uStack_208._0_4_ = (float)uStack_e58;
      _auStack_210 = uStack_e60;
      uStack_208._4_4_ = (float)uStack_e54;
      auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _lqc2(_auStack_210);
      auVar25 = _vsub(auVar25,auVar26);
      _auStack_210 = _sqc2(auVar25);
      func_0x00223030(0x40800000,auStack_210);
      auVar26 = _lqc2(_auStack_210);
      auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _vadd(auVar25,auVar26);
      auVar25 = _sqc2(auVar25);
      *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    __mi__7FVectorCFRC7FVector(&uStack_e90,iVar17 + 0x70,iVar17 + 0x50);
    uStack_208._0_4_ = (float)uStack_e88;
    _auStack_210 = uStack_e90;
    uStack_208._4_4_ = (float)uStack_e84;
    uVar8 = func_0x00222f00(auStack_eb0,auStack_210);
    Get3DAngle__F7FVector(&uStack_ea0,uVar8);
    fStack_1f8 = (float)uStack_e98;
    auStack_200 = (undefined1  [8])uStack_ea0;
    uStack_1f4 = uStack_e94;
    auVar25 = _auStack_200;
    auStack_200._0_4_ = (undefined4)uStack_ea0;
    auStack_200._4_4_ = (undefined4)((ulong)uStack_ea0 >> 0x20);
    if (*(int *)(iVar17 + 0xdc) == 0) {
      *(float *)(iVar17 + 0x60) = -(float)auStack_200._0_4_;
      *(float *)(iVar17 + 100) = -(float)auStack_200._4_4_;
    }
    else {
      for (fVar23 = -(float)auStack_200._0_4_ - *(float *)(iVar17 + 0x60); fVar23 < -180.0;
          fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 0x60) =
           *(float *)(iVar17 + 0x60) + fVar23 * 7.5 * *(float *)(iVar17 + 0x24);
      for (fVar23 = -(float)auStack_200._4_4_ - *(float *)(iVar17 + 100); fVar23 < -180.0;
          fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + fVar23 * 7.5 * *(float *)(iVar17 + 0x24)
      ;
    }
    while (*(float *)(iVar17 + 0x60) < -180.0) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 0x60)) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
    }
    while (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    *(undefined4 *)(iVar17 + 0x68) = 0;
    *(undefined4 *)(iVar17 + 0xdc) = 1;
    _auStack_200 = auVar25;
    break;
  case 6:
    iVar5 = iGpffff8610 + *(int *)(iVar17 + 0xd0) * 0x510;
    if ((((long)((ulong)*(byte *)(iVar5 + 0xb4) << 0x39) < 0) ||
        ((long)((ulong)*(byte *)(iVar5 + 0xb5) << 0x3c) < 0)) ||
       ((long)((ulong)*(byte *)(iVar5 + 0xb1) << 0x3a) < 0)) {
      __pl__7FVectorCFRC7FVector(auStack_ed0,iVar5 + 0x170,iVar5 + 0x3a0);
      *(int *)(iVar17 + 0x70) = auStack_ed0._0_4_;
      *(int *)(iVar17 + 0x74) = auStack_ed0._4_4_;
      *(undefined4 *)(iVar17 + 0x78) = uStack_ec8;
      *(undefined4 *)(iVar17 + 0x7c) = uStack_ec4;
    }
    else {
      __pl__7FVectorCFRC7FVector(auStack_ec0,iVar5 + 0x160,iVar5 + 0x3a0);
      *(int *)(iVar17 + 0x70) = auStack_ec0._0_4_;
      *(int *)(iVar17 + 0x74) = auStack_ec0._4_4_;
      *(undefined4 *)(iVar17 + 0x78) = uStack_eb8;
      *(undefined4 *)(iVar17 + 0x7c) = uStack_eb4;
    }
    if ((*(int *)(iVar17 + 0xdc) != 0) &&
       (*(float *)(iVar17 + 0xe0) = *(float *)(iVar17 + 0xe0) + *(float *)(iVar17 + 0x24) * 40.0,
       60.0 < *(float *)(iVar17 + 0xe0))) {
      *(undefined4 *)(iVar17 + 0xe0) = 0x42700000;
    }
    fVar23 = (float)func_0x00222fd0(iVar5 + 0x3b0);
    *(float *)(iVar17 + 0x80) =
         (*(float *)(iVar17 + 0x84) *
         (*(float *)(iVar17 + 0xe0) + *(float *)(iVar5 + 0x354) + fVar23)) / 512.0;
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    func_0x00202890(0xbeb2b8c3,auStack_430,auStack_430);
    uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_f00);
    func_0x00222df0(auStack_ef0,auStack_430,uVar8);
    __pl__7FVectorCFRC7FVector(&uStack_ee0,auStack_ef0,iVar17 + 0x70);
    uStack_208._0_4_ = (float)uStack_ed8;
    _auStack_210 = uStack_ee0;
    uStack_208._4_4_ = (float)uStack_ed4;
    if (*(int *)(iVar17 + 0xdc) == 0) {
      *(int *)(iVar17 + 0x50) = (int)uStack_ee0;
      *(int *)(iVar17 + 0x54) = (int)((ulong)uStack_ee0 >> 0x20);
      *(undefined4 *)(iVar17 + 0x58) = uStack_ed8;
      *(undefined4 *)(iVar17 + 0x5c) = uStack_ed4;
    }
    else {
      auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _lqc2(_auStack_210);
      auVar25 = _vsub(auVar25,auVar26);
      _auStack_210 = _sqc2(auVar25);
      func_0x00223030(0x40800000,auStack_210);
      auVar26 = _lqc2(_auStack_210);
      auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _vadd(auVar25,auVar26);
      auVar25 = _sqc2(auVar25);
      *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    __mi__7FVectorCFRC7FVector(&uStack_f10,iVar17 + 0x70,iVar17 + 0x50);
    uStack_208._0_4_ = (float)uStack_f08;
    _auStack_210 = uStack_f10;
    uStack_208._4_4_ = (float)uStack_f04;
    uVar8 = func_0x00222f00(auStack_f30,auStack_210);
    Get3DAngle__F7FVector(&uStack_f20,uVar8);
    fStack_1f8 = (float)uStack_f18;
    auStack_200 = (undefined1  [8])uStack_f20;
    uStack_1f4 = uStack_f14;
    auVar25 = _auStack_200;
    auStack_200._0_4_ = (undefined4)uStack_f20;
    auStack_200._4_4_ = (undefined4)((ulong)uStack_f20 >> 0x20);
    if (*(int *)(iVar17 + 0xdc) == 0) {
      *(float *)(iVar17 + 0x60) = -(float)auStack_200._0_4_;
      *(float *)(iVar17 + 100) = -(float)auStack_200._4_4_;
    }
    else {
      for (fVar23 = -(float)auStack_200._0_4_ - *(float *)(iVar17 + 0x60); fVar23 < -180.0;
          fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 0x60) =
           *(float *)(iVar17 + 0x60) + fVar23 * 7.5 * *(float *)(iVar17 + 0x24);
      for (fVar23 = -(float)auStack_200._4_4_ - *(float *)(iVar17 + 100); fVar23 < -180.0;
          fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + fVar23 * 7.5 * *(float *)(iVar17 + 0x24)
      ;
    }
    while (*(float *)(iVar17 + 0x60) < -180.0) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 0x60)) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
    }
    while (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    *(undefined4 *)(iVar17 + 0x68) = 0;
    *(undefined4 *)(iVar17 + 0xdc) = 1;
    _auStack_200 = auVar25;
    break;
  case 7:
    *(byte *)(iVar17 + 0x1a) = *(byte *)(iVar17 + 0x1a) & 0xfd;
    iVar5 = iGpffff8610 + *(int *)(iVar17 + 0xd0) * 0x510;
    if ((((*(byte *)(iVar17 + 0x1a) & 1) == 0) && (*(float *)(iVar17 + 0x24) != 0.0)) &&
       ((uVar2 & 0x8000) != 0)) {
      if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3b) < 0) {
        *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0xef;
        *(undefined4 *)(iVar17 + 0x84) = 0x44000000;
        *(undefined2 *)(iVar17 + 0x1e) = 1;
      }
      else {
        *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0xef | 0x10;
        *(undefined2 *)(iVar17 + 0x1e) = 0x14;
      }
      *(byte *)(iVar17 + 0x1a) = *(byte *)(iVar17 + 0x1a) & 0xfd | 2;
    }
    sVar1 = *(short *)(iVar17 + 0x1e);
    if (sVar1 == 0x15) {
LAB_005977c0:
      __pl__7FVectorCFRC7FVector(auStack_1060,iVar5 + 0x160,iVar5 + 0x3a0);
      *(int *)(iVar17 + 0x100) = auStack_1060._0_4_;
      *(int *)(iVar17 + 0x104) = auStack_1060._4_4_;
      *(undefined4 *)(iVar17 + 0x108) = uStack_1058;
      *(undefined4 *)(iVar17 + 0x10c) = uStack_1054;
      FUN_004baab0(0,0,0,0x3f800000,auStack_1070);
      *(int *)(iVar17 + 0x110) = auStack_1070._0_4_;
      *(int *)(iVar17 + 0x114) = auStack_1070._4_4_;
      *(undefined4 *)(iVar17 + 0x118) = uStack_1068;
      *(undefined4 *)(iVar17 + 0x11c) = uStack_1064;
      *(undefined4 *)(iVar17 + 0xe8) = 0xc1c80000;
      *(undefined4 *)(iVar17 + 0xec) = 0x42960000;
      if ((long)((ulong)*(byte *)(iVar17 + 0x1a) << 0x3e) < 0) {
        uVar8 = func_0x00222f00(auStack_1090,iVar17 + 0x100);
        Get3DAngle__F7FVector(&uStack_1080,uVar8);
        uStack_208._0_4_ = (float)uStack_1078;
        _auStack_210 = uStack_1080;
        uStack_208._4_4_ = (float)uStack_1074;
        while (fStack_20c < -180.0) {
          auStack_210 = (undefined1  [4])((float)auStack_210 + 360.0);
        }
        while (180.0 < fStack_20c) {
          auStack_210 = (undefined1  [4])((float)auStack_210 - 360.0);
        }
        *(float *)(iVar17 + 0xe4) = -fStack_20c - *(float *)(iVar5 + 0x184);
        while (*(float *)(iVar17 + 0xe4) < -180.0) {
          *(float *)(iVar17 + 0xe4) = *(float *)(iVar17 + 0xe4) + 360.0;
        }
        while (180.0 < *(float *)(iVar17 + 0xe4)) {
          *(float *)(iVar17 + 0xe4) = *(float *)(iVar17 + 0xe4) - 360.0;
        }
      }
      else {
        fVar23 = 0.0;
        if ((*(byte *)(iVar17 + 0x1a) & 1) == 0) {
          fVar23 = ((float)bStack_44e / 60.0 - (float)bStack_44d / 60.0) *
                   *(float *)(iVar17 + 0x24) * 30.0;
        }
        for (fVar23 = fVar23 + *(float *)(iVar17 + 0xe4); fVar23 < -180.0; fVar23 = fVar23 + 360.0)
        {
        }
        for (; 180.0 <= fVar23; fVar23 = fVar23 - 360.0) {
        }
        fVar22 = *(float *)(iVar5 + 0x184) + fVar23;
        if (fVar22 < -180.0) {
          fVar22 = fVar22 + 360.0;
        }
        if (180.0 < fVar22) {
          fVar22 = fVar22 - 360.0;
        }
        FUN_004baab0(*(undefined4 *)(iVar17 + 0xe8),fVar22,0,0x3f800000,auStack_10a0);
        *(int *)(iVar17 + 0x60) = auStack_10a0._0_4_;
        *(int *)(iVar17 + 100) = auStack_10a0._4_4_;
        *(undefined4 *)(iVar17 + 0x68) = uStack_1098;
        *(undefined4 *)(iVar17 + 0x6c) = uStack_1094;
        *(int *)(iVar17 + 0x70) = (int)*(undefined8 *)(iVar17 + 0x100);
        *(int *)(iVar17 + 0x74) = (int)((ulong)*(undefined8 *)(iVar17 + 0x100) >> 0x20);
        *(undefined4 *)(iVar17 + 0x78) = *(undefined4 *)(iVar17 + 0x108);
        *(undefined4 *)(iVar17 + 0x7c) = *(undefined4 *)(iVar17 + 0x10c);
        fVar22 = (float)func_0x00222fd0(iVar5 + 0x3b0);
        *(float *)(iVar17 + 0x80) =
             (*(float *)(iVar17 + 0x84) *
             (*(float *)(iVar17 + 0xec) + *(float *)(iVar5 + 0x354) + fVar22)) / 512.0;
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x60));
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 100));
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x68));
        func_0x002027e8(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_10c0);
        func_0x00222df0(auStack_10b0,auStack_430,uVar8);
        *(int *)(iVar17 + 0x50) = auStack_10b0._0_4_;
        *(int *)(iVar17 + 0x54) = auStack_10b0._4_4_;
        *(undefined4 *)(iVar17 + 0x58) = uStack_10a8;
        *(undefined4 *)(iVar17 + 0x5c) = uStack_10a4;
        auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
        auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
        auVar25 = _vadd(auVar25,auVar26);
        auVar25 = _sqc2(auVar25);
        *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
        bVar4 = false;
        for (fVar22 = *(float *)(iVar5 + 0x184) + *(float *)(iVar17 + 0xe4); fVar22 < -180.0;
            fVar22 = fVar22 + 360.0) {
        }
        for (; 180.0 <= fVar22; fVar22 = fVar22 - 360.0) {
        }
        if (*(float *)(iVar17 + 0x50) < -*(float *)(iGpffff8610 + 0x40b4) / 2.0 + 5.0) {
          if ((*(float *)(iVar17 + 100) < 50.0) || (130.0 < *(float *)(iVar17 + 100))) {
            bVar4 = true;
          }
          if ((fVar22 < 50.0) || (130.0 < fVar22)) {
            bVar4 = true;
          }
        }
        if (*(float *)(iGpffff8610 + 0x40b4) / 2.0 - 5.0 < *(float *)(iVar17 + 0x50)) {
          if ((-50.0 < *(float *)(iVar17 + 100)) || (*(float *)(iVar17 + 100) < -130.0)) {
            bVar4 = true;
          }
          if ((-50.0 < fVar22) || (fVar22 < -130.0)) {
            bVar4 = true;
          }
        }
        if (*(float *)(iVar17 + 0x58) < -*(float *)(iGpffff8610 + 0x40bc) / 2.0 + 5.0) {
          if ((*(float *)(iVar17 + 100) < -40.0) || (40.0 < *(float *)(iVar17 + 100))) {
            bVar4 = true;
          }
          if ((fVar22 < -40.0) || (40.0 < fVar22)) {
            bVar4 = true;
          }
        }
        if (*(float *)(iGpffff8610 + 0x40bc) / 2.0 - 5.0 < *(float *)(iVar17 + 0x58)) {
          if ((-140.0 < *(float *)(iVar17 + 100)) && (*(float *)(iVar17 + 100) < 140.0)) {
            bVar4 = true;
          }
          if ((-140.0 < fVar22) && (fVar22 < 140.0)) {
            bVar4 = true;
          }
        }
        if (!bVar4) {
          *(float *)(iVar17 + 0xe4) = fVar23;
        }
      }
    }
    else {
      if (sVar1 == 0x14) {
        *(undefined4 *)(iVar17 + 0xe4) = 0x42340000;
        *(undefined4 *)(iVar17 + 0x84) = 0x44000000;
        *(byte *)(iVar17 + 0x18) = *(byte *)(iVar17 + 0x18) & 0x7f | 0x80;
        *(undefined2 *)(iVar17 + 0x1e) = 0x15;
        goto LAB_005977c0;
      }
      if (sVar1 == 8) {
LAB_00597640:
        *(undefined4 *)(iVar17 + 0xe4) = 0x43340000;
        *(undefined4 *)(iVar17 + 0xe8) = 0;
        *(undefined4 *)(iVar17 + 0xec) = 0x40a00000;
        *(float *)(iVar17 + 0xe0) = *(float *)(iVar17 + 0xe0) + *(float *)(iVar17 + 0x24);
        FUN_004baab0((*(float *)(iVar17 + 0xe0) - 2.0) * -*(float *)(iVar5 + 0x354),0,0,0x3f800000,
                     &uStack_1040);
        uStack_208._0_4_ = (float)uStack_1038;
        _auStack_210 = uStack_1040;
        uStack_208._4_4_ = (float)uStack_1034;
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(*(undefined4 *)(iVar5 + 0x180));
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(*(undefined4 *)(iVar5 + 0x184));
        func_0x00202938(uVar24,auStack_430,auStack_430);
        func_0x00222df0(auStack_1050,auStack_430,auStack_210);
        *(int *)(iVar17 + 0x110) = auStack_1050._0_4_;
        *(int *)(iVar17 + 0x114) = auStack_1050._4_4_;
        *(undefined4 *)(iVar17 + 0x118) = uStack_1048;
        *(undefined4 *)(iVar17 + 0x11c) = uStack_1044;
        if (4.0 <= *(float *)(iVar17 + 0xe0)) {
          *(undefined2 *)(iVar17 + 0x1e) = 1;
        }
      }
      else {
        if (sVar1 == 7) {
          __pl__7FVectorCFRC7FVector(auStack_1030,iVar5 + 0x160,iVar5 + 0x3a0);
          *(int *)(iVar17 + 0x100) = auStack_1030._0_4_;
          *(int *)(iVar17 + 0x104) = auStack_1030._4_4_;
          *(undefined4 *)(iVar17 + 0x108) = uStack_1028;
          *(undefined4 *)(iVar17 + 0x10c) = uStack_1024;
          if (((*(byte *)(iVar5 + 0xb4) & 1) == 0) && (*(short *)(iVar5 + 0x120) == 1)) {
            *(float *)(iVar17 + 0x104) =
                 *(float *)(iVar17 + 0x104) - (*(float *)(iVar5 + 0x3b4) + 3.0);
          }
          else if (((long)((ulong)*(byte *)(iVar5 + 0xb1) << 0x3e) < 0) &&
                  (*(short *)(iVar5 + 0xba) == 0x16)) {
            *(float *)(iVar17 + 0x104) = *(float *)(iVar17 + 0x104) - *(float *)(iVar5 + 0x3b4);
          }
          else {
            *(float *)(iVar17 + 0x104) =
                 *(float *)(iVar17 + 0x104) + *(float *)(iVar5 + 0x3b4) / 2.0;
          }
          *(undefined4 *)(iVar17 + 0xe0) = 0;
          *(undefined4 *)(iVar17 + 0x84) = 0x44400000;
          *(byte *)(iVar17 + 0x18) = *(byte *)(iVar17 + 0x18) & 0x7f | 0x80;
          *(undefined2 *)(iVar17 + 0x1e) = 8;
          goto LAB_00597640;
        }
        if (sVar1 == 6) {
LAB_00597298:
          __pl__7FVectorCFRC7FVector(auStack_1010,iVar5 + 0x160,iVar5 + 0x3a0);
          *(int *)(iVar17 + 0x100) = auStack_1010._0_4_;
          *(int *)(iVar17 + 0x104) = auStack_1010._4_4_;
          *(undefined4 *)(iVar17 + 0x108) = uStack_1008;
          *(undefined4 *)(iVar17 + 0x10c) = uStack_1004;
          *(float *)(iVar17 + 0x104) =
               *(float *)(iVar17 + 0x104) - *(float *)(iVar5 + 0x3b4) * 0.2857143;
          FUN_004baab0(0,0,0,0x3f800000,auStack_1020);
          *(int *)(iVar17 + 0x110) = auStack_1020._0_4_;
          *(int *)(iVar17 + 0x114) = auStack_1020._4_4_;
          *(undefined4 *)(iVar17 + 0x118) = uStack_1018;
          *(undefined4 *)(iVar17 + 0x11c) = uStack_1014;
          if ((*(byte *)(iVar5 + 0xb4) & 1) == 0) {
            if ((long)((ulong)*(byte *)(iVar5 + 0xb1) << 0x3e) < 0) {
              *(undefined4 *)(iVar17 + 0xe4) = 0x420c0000;
              *(undefined4 *)(iVar17 + 0xe8) = 0xc1a00000;
              *(undefined4 *)(iVar17 + 0xec) = 0x41700000;
            }
            else {
              switch(*(undefined2 *)(iVar5 + 0x120)) {
              case 0:
              case 0xb:
              case 0xd:
                *(undefined4 *)(iVar17 + 0xe4) = 0xc20c0000;
                *(undefined4 *)(iVar17 + 0xe8) = 0xc1a00000;
                *(undefined4 *)(iVar17 + 0xec) = 0x41700000;
                break;
              case 1:
              case 3:
              case 4:
              case 5:
              case 6:
              case 7:
              case 8:
              case 9:
              case 10:
              case 0xc:
                *(undefined4 *)(iVar17 + 0xe4) = 0x420c0000;
                *(undefined4 *)(iVar17 + 0xe8) = 0xc1a00000;
                *(undefined4 *)(iVar17 + 0xec) = 0x41700000;
                break;
              case 2:
                *(undefined4 *)(iVar17 + 0xe4) = 0x420c0000;
                *(undefined4 *)(iVar17 + 0xe8) = 0xc1200000;
                *(undefined4 *)(iVar17 + 0xec) = 0x41700000;
              }
            }
          }
          else {
            if (*(int *)(iVar17 + 0xd4) == 0) {
              *(undefined4 *)(iVar17 + 0xe4) = 0xc20c0000;
            }
            else {
              *(undefined4 *)(iVar17 + 0xe4) = 0x420c0000;
            }
            *(undefined4 *)(iVar17 + 0xe8) = 0xc1a00000;
            *(undefined4 *)(iVar17 + 0xec) = 0x41700000;
          }
          *(float *)(iVar17 + 0xe0) = *(float *)(iVar17 + 0xe0) + *(float *)(iVar17 + 0x24);
          if (8.0 <= *(float *)(iVar17 + 0xe0)) {
            *(undefined2 *)(iVar17 + 0x1e) = 7;
          }
        }
        else {
          if (sVar1 == 5) {
            *(undefined4 *)(iVar17 + 0xe0) = 0;
            *(undefined4 *)(iVar17 + 0x84) = 0x44000000;
            *(byte *)(iVar17 + 0x18) = *(byte *)(iVar17 + 0x18) & 0x7f | 0x80;
            *(undefined2 *)(iVar17 + 0x1e) = 6;
            goto LAB_00597298;
          }
          if (sVar1 == 4) {
LAB_00596ee0:
            if ((*(byte *)(iVar5 + 0xb4) & 1) == 0) {
              if ((long)((ulong)*(byte *)(iVar5 + 0xb1) << 0x3e) < 0) {
                switch(*(undefined2 *)(iVar5 + 0xba)) {
                default:
                  *(undefined4 *)(iVar17 + 0xe4) = 0xc2700000;
                  *(undefined4 *)(iVar17 + 0xe8) = 0;
                  break;
                case 7:
                case 8:
                case 0x15:
                case 0x16:
                  *(undefined4 *)(iVar17 + 0xe4) = 0x42700000;
                  *(undefined4 *)(iVar17 + 0xe8) = 0;
                }
              }
              else {
                switch(*(undefined2 *)(iVar5 + 0x120)) {
                case 0:
                case 1:
                case 0xb:
                case 0xc:
                case 0xd:
                  *(undefined4 *)(iVar17 + 0xe4) = 0x42700000;
                  *(undefined4 *)(iVar17 + 0xe8) = 0;
                  break;
                case 2:
                  *(undefined4 *)(iVar17 + 0xe4) = 0x42700000;
                  *(undefined4 *)(iVar17 + 0xe8) = 0x40f00000;
                  break;
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                  *(undefined4 *)(iVar17 + 0xe4) = 0xc2700000;
                  *(undefined4 *)(iVar17 + 0xe8) = 0;
                }
              }
            }
            else {
              if (*(int *)(iVar17 + 0xd4) == 0) {
                *(undefined4 *)(iVar17 + 0xe4) = 0x42700000;
              }
              else {
                *(undefined4 *)(iVar17 + 0xe4) = 0xc2700000;
              }
              *(undefined4 *)(iVar17 + 0xe8) = 0;
            }
            fVar23 = (float)func_0x00222fd0(iVar5 + 0x3b0);
            *(float *)(iVar17 + 0xec) =
                 (*(float *)(iVar17 + 0xf0) + 8.5) - (*(float *)(iVar5 + 0x354) + fVar23);
            *(float *)(iVar17 + 0xe0) = *(float *)(iVar17 + 0xe0) + *(float *)(iVar17 + 0x24);
            if (((*(byte *)(iVar5 + 0xb4) & 1) == 0) && (*(short *)(iVar5 + 0x120) == 1)) {
              FUN_004baab0(0,0,(*(float *)(iVar17 + 0xe0) - 2.8) * -1.25,0x3f800000,&uStack_fe0);
              uStack_208._0_4_ = (float)uStack_fd8;
              _auStack_210 = uStack_fe0;
              uStack_208._4_4_ = (float)uStack_fd4;
            }
            else {
              FUN_004baab0(0,0,(*(float *)(iVar17 + 0xe0) - 2.3) * -1.25,0x3f800000,&uStack_ff0);
              uStack_208._0_4_ = (float)uStack_fe8;
              _auStack_210 = uStack_ff0;
              uStack_208._4_4_ = (float)uStack_fe4;
            }
            auVar25 = _vmr32(in_vf0);
            auVar26 = _vmr32(auVar25);
            auVar27 = _vmr32(auVar26);
            auStack_400 = _sqc2(in_vf0);
            auStack_410 = _sqc2(auVar25);
            auStack_420 = _sqc2(auVar26);
            auStack_430 = _sqc2(auVar27);
            uVar24 = func_0x00222e40(*(undefined4 *)(iVar5 + 0x180));
            func_0x00202890(uVar24,auStack_430,auStack_430);
            uVar24 = func_0x00222e40(*(undefined4 *)(iVar5 + 0x184));
            func_0x00202938(uVar24,auStack_430,auStack_430);
            func_0x00222df0(auStack_1000,auStack_430,auStack_210);
            *(int *)(iVar17 + 0x110) = auStack_1000._0_4_;
            *(int *)(iVar17 + 0x114) = auStack_1000._4_4_;
            *(undefined4 *)(iVar17 + 0x118) = uStack_ff8;
            *(undefined4 *)(iVar17 + 0x11c) = uStack_ff4;
            if (4.0 <= *(float *)(iVar17 + 0xe0)) {
              *(undefined2 *)(iVar17 + 0x1e) = 5;
            }
          }
          else {
            if (sVar1 == 3) {
              FUN_004baab0(0x45800000,0x45800000,0x45800000,0,&uStack_fb0);
              uStack_208._0_4_ = (float)uStack_fa8;
              _auStack_210 = uStack_fb0;
              uStack_208._4_4_ = (float)uStack_fa4;
              FUN_004baab0(0xc5800000,0xc5800000,0xc5800000,0,&uStack_fc0);
              fStack_1f8 = (float)uStack_fb8;
              auStack_200 = (undefined1  [8])uStack_fc0;
              uStack_1f4 = uStack_fb4;
              for (iVar15 = 0; iVar15 < *(int *)(*(int *)(iVar5 + 0x540) + 8); iVar15 = iVar15 + 1)
              {
                pauVar11 = (undefined1 (*) [16])
                           (*(int *)(*(int *)(iVar5 + 0x14c) + 0x30) +
                            (uint)*(byte *)(*(int *)(*(int *)(iVar5 + 0x14c) + 0xe4) +
                                           *(short *)(iVar5 + 0xb0 + iVar15 * 2 + 0x498) * 0x110) *
                            0x1f0 + (bGpffff8240 & 1) * 0x40);
                auStack_430 = *pauVar11;
                auStack_420 = pauVar11[1];
                auStack_410 = pauVar11[2];
                auStack_400 = pauVar11[3];
                func_0x00316c10(auStack_310,
                                *(int *)(*(int *)(iVar5 + 0x14c) + 0xe4) +
                                *(short *)(iVar5 + 0xb0 + iVar15 * 2 + 0x498) * 0x110 + 0x10,
                                auStack_430,8);
                for (iVar12 = 0; iVar12 < 8; iVar12 = iVar12 + 1) {
                  if (*(float *)(auStack_310 + iVar12 * 0x10) < (float)auStack_210) {
                    auStack_210 = (undefined1  [4])*(undefined4 *)(auStack_310 + iVar12 * 0x10);
                  }
                  if (*(float *)(auStack_310 + iVar12 * 0x10 + 4) < fStack_20c) {
                    fStack_20c = (float)*(undefined4 *)(auStack_310 + iVar12 * 0x10 + 4);
                  }
                  if (*(float *)(auStack_310 + iVar12 * 0x10 + 8) < (float)uStack_208) {
                    uStack_208._0_4_ = (float)*(undefined4 *)(auStack_310 + iVar12 * 0x10 + 8);
                  }
                  if ((float)auStack_200._0_4_ < *(float *)(auStack_310 + iVar12 * 0x10)) {
                    auStack_200._0_4_ = *(undefined4 *)(auStack_310 + iVar12 * 0x10);
                  }
                  if ((float)auStack_200._4_4_ < *(float *)(auStack_310 + iVar12 * 0x10 + 4)) {
                    auStack_200._4_4_ = *(undefined4 *)(auStack_310 + iVar12 * 0x10 + 4);
                  }
                  if (fStack_1f8 < *(float *)(auStack_310 + iVar12 * 0x10 + 8)) {
                    fStack_1f8 = (float)*(undefined4 *)(auStack_310 + iVar12 * 0x10 + 8);
                  }
                }
              }
              __pl__7FVectorCFRC7FVector(auStack_fd0,auStack_210,auStack_200);
              *(int *)(iVar17 + 0x100) = auStack_fd0._0_4_;
              *(int *)(iVar17 + 0x104) = auStack_fd0._4_4_;
              *(undefined4 *)(iVar17 + 0x108) = uStack_fc8;
              *(undefined4 *)(iVar17 + 0x10c) = uStack_fc4;
              func_0x00223030(0x40000000,iVar17 + 0x100);
              *(float *)(iVar17 + 0x104) =
                   (float)auStack_200._4_4_ + (fStack_20c - (float)auStack_200._4_4_) / 3.0;
              *(undefined4 *)(iVar17 + 0xe0) = 0;
              *(float *)(iVar17 + 0xf0) =
                   ((fStack_1f8 - (float)uStack_208) / 2.0 +
                   ((float)auStack_200._0_4_ - (float)auStack_210) / 2.0 +
                   ((float)auStack_200._4_4_ - fStack_20c) / 2.0) / 3.0;
              *(undefined4 *)(iVar17 + 0x84) = 0x44400000;
              *(byte *)(iVar17 + 0x18) = *(byte *)(iVar17 + 0x18) & 0x7f | 0x80;
              *(undefined2 *)(iVar17 + 0x1e) = 4;
              goto LAB_00596ee0;
            }
            if (sVar1 == 2) {
LAB_005968b0:
              __pl__7FVectorCFRC7FVector(auStack_f90,iVar5 + 0x160,iVar5 + 0x3a0);
              *(int *)(iVar17 + 0x100) = auStack_f90._0_4_;
              *(int *)(iVar17 + 0x104) = auStack_f90._4_4_;
              *(undefined4 *)(iVar17 + 0x108) = uStack_f88;
              *(undefined4 *)(iVar17 + 0x10c) = uStack_f84;
              *(float *)(iVar17 + 0x104) =
                   *(float *)(iVar17 + 0x104) - *(float *)(iVar5 + 0x3b4) * 0.2857143;
              FUN_004baab0(0,0,0,0x3f800000,auStack_fa0);
              *(int *)(iVar17 + 0x110) = auStack_fa0._0_4_;
              *(int *)(iVar17 + 0x114) = auStack_fa0._4_4_;
              *(undefined4 *)(iVar17 + 0x118) = uStack_f98;
              *(undefined4 *)(iVar17 + 0x11c) = uStack_f94;
              if ((*(byte *)(iVar5 + 0xb4) & 1) == 0) {
                if ((long)((ulong)*(byte *)(iVar5 + 0xb1) << 0x3e) < 0) {
                  *(undefined4 *)(iVar17 + 0xe4) = 0xc1f00000;
                  *(undefined4 *)(iVar17 + 0xe8) = 0x41000000;
                  *(undefined4 *)(iVar17 + 0xec) = 0x41700000;
                }
                else {
                  switch(*(undefined2 *)(iVar5 + 0x120)) {
                  case 0:
                  case 0xb:
                  case 0xd:
                    *(undefined4 *)(iVar17 + 0xe4) = 0x41f00000;
                    *(undefined4 *)(iVar17 + 0xe8) = 0x41000000;
                    *(undefined4 *)(iVar17 + 0xec) = 0x41700000;
                    break;
                  case 1:
                  case 3:
                  case 4:
                  case 5:
                  case 6:
                  case 7:
                  case 8:
                  case 9:
                  case 10:
                  case 0xc:
                    *(undefined4 *)(iVar17 + 0xe4) = 0xc1f00000;
                    *(undefined4 *)(iVar17 + 0xe8) = 0x41000000;
                    *(undefined4 *)(iVar17 + 0xec) = 0x41700000;
                    break;
                  case 2:
                    *(undefined4 *)(iVar17 + 0xe4) = 0xc1f00000;
                    *(undefined4 *)(iVar17 + 0xe8) = 0x40a00000;
                    *(undefined4 *)(iVar17 + 0xec) = 0x41700000;
                  }
                }
              }
              else {
                if (*(int *)(iVar17 + 0xd4) == 0) {
                  *(undefined4 *)(iVar17 + 0xe4) = 0x41f00000;
                }
                else {
                  *(undefined4 *)(iVar17 + 0xe4) = 0xc1f00000;
                }
                *(undefined4 *)(iVar17 + 0xe8) = 0x41000000;
                *(undefined4 *)(iVar17 + 0xec) = 0x41700000;
              }
              *(float *)(iVar17 + 0xe0) = *(float *)(iVar17 + 0xe0) + *(float *)(iVar17 + 0x24);
              if (8.0 <= *(float *)(iVar17 + 0xe0)) {
                *(undefined2 *)(iVar17 + 0x1e) = 3;
              }
            }
            else {
              if (sVar1 == 1) {
LAB_00596858:
                *(undefined4 *)(iVar17 + 0xe0) = 0;
                uVar14 = func_0x00232cc8();
                *(uint *)(iVar17 + 0xd4) = uVar14 & 0x40;
                *(undefined4 *)(iVar17 + 0x84) = 0x44000000;
                *(byte *)(iVar17 + 0x18) = *(byte *)(iVar17 + 0x18) & 0x7f | 0x80;
                *(undefined2 *)(iVar17 + 0x1e) = 2;
                goto LAB_005968b0;
              }
              if (sVar1 == 0) {
                fVar23 = *(float *)(iVar5 + 0x184);
                auVar25 = _vmr32(in_vf0);
                auVar26 = _vmr32(auVar25);
                auVar27 = _vmr32(auVar26);
                auStack_400 = _sqc2(in_vf0);
                auStack_410 = _sqc2(auVar25);
                auStack_420 = _sqc2(auVar26);
                auStack_430 = _sqc2(auVar27);
                uVar24 = func_0x00222e40(0xbf800000);
                func_0x00202890(uVar24,auStack_430,auStack_430);
                uVar24 = func_0x00222e40(fVar23 + 20.0);
                func_0x00202938(uVar24,auStack_430,auStack_430);
                fVar23 = (float)func_0x00222fd0(iVar5 + 0x3b0);
                uVar8 = FUN_004baab0(0,0,-(*(float *)(iVar5 + 0x354) + fVar23 + 50.0),0x3f800000,
                                     auStack_f50);
                func_0x00222df0(&uStack_f40,auStack_430,uVar8);
                uStack_208._0_4_ = (float)uStack_f38;
                _auStack_210 = uStack_f40;
                uStack_208._4_4_ = (float)uStack_f34;
                __pl__7FVectorCFRC7FVector(auStack_f60,iVar5 + 0x160,iVar5 + 0x3a0);
                auVar26 = _lqc2(auStack_f60);
                auVar25 = _lqc2(_auStack_210);
                auVar25 = _vadd(auVar25,auVar26);
                _auStack_210 = _sqc2(auVar25);
                puVar7 = (undefined4 *)FUN_00472df0(auStack_f80);
                *puVar7 = 0x3f000000;
                puVar7 = (undefined4 *)vy__7FVectorFv(auStack_f80);
                *puVar7 = 0x3f000000;
                puVar7 = (undefined4 *)vz__7FVectorFv(auStack_f80);
                *puVar7 = 0x3f000000;
                puVar7 = (undefined4 *)vw__7FVectorFv(auStack_f80);
                *puVar7 = 0x3f800000;
                uVar8 = func_0x00222f00(auStack_f70,auStack_210);
                uVar24 = func_0x002261a0(uVar8,auStack_f80);
                *(undefined4 *)(iVar17 + 0x210) = uVar24;
                func_0x002280f0(0x41000000,*(undefined4 *)(iVar17 + 0x210));
                func_0x00228140(*(undefined4 *)(iVar17 + 0x210),0);
                *(undefined2 *)(iVar17 + 0x1e) = 1;
                goto LAB_00596858;
              }
            }
          }
        }
      }
    }
    fVar23 = *(float *)(iVar5 + 0x184) + *(float *)(iVar17 + 0xe4);
    if (fVar23 < -180.0) {
      fVar23 = fVar23 + 360.0;
    }
    if (180.0 < fVar23) {
      fVar23 = fVar23 - 360.0;
    }
    FUN_004baab0(*(undefined4 *)(iVar17 + 0xe8),fVar23,0,0x3f800000,auStack_10d0);
    *(int *)(iVar17 + 0x60) = auStack_10d0._0_4_;
    *(int *)(iVar17 + 100) = auStack_10d0._4_4_;
    *(undefined4 *)(iVar17 + 0x68) = uStack_10c8;
    *(undefined4 *)(iVar17 + 0x6c) = uStack_10c4;
    *(int *)(iVar17 + 0x70) = (int)*(undefined8 *)(iVar17 + 0x100);
    *(int *)(iVar17 + 0x74) = (int)((ulong)*(undefined8 *)(iVar17 + 0x100) >> 0x20);
    *(undefined4 *)(iVar17 + 0x78) = *(undefined4 *)(iVar17 + 0x108);
    *(undefined4 *)(iVar17 + 0x7c) = *(undefined4 *)(iVar17 + 0x10c);
    fVar23 = (float)func_0x00222fd0(iVar5 + 0x3b0);
    *(float *)(iVar17 + 0x80) =
         (*(float *)(iVar17 + 0x84) *
         (*(float *)(iVar17 + 0xec) + *(float *)(iVar5 + 0x354) + fVar23)) / 512.0;
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x60));
    func_0x00202890(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 100));
    func_0x00202938(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x68));
    func_0x002027e8(uVar24,auStack_430,auStack_430);
    uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_10f0);
    func_0x00222df0(auStack_10e0,auStack_430,uVar8);
    *(int *)(iVar17 + 0x50) = auStack_10e0._0_4_;
    *(int *)(iVar17 + 0x54) = auStack_10e0._4_4_;
    *(undefined4 *)(iVar17 + 0x58) = uStack_10d8;
    *(undefined4 *)(iVar17 + 0x5c) = uStack_10d4;
    auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
    auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
    auVar25 = _vadd(auVar25,auVar26);
    auVar25 = _sqc2(auVar25);
    *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x110));
    auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
    auVar25 = _vadd(auVar25,auVar26);
    auVar25 = _sqc2(auVar25);
    *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    break;
  case 8:
    lVar16 = (long)*(int *)(iVar17 + 0xd0);
    if (((*(char *)(iGpffff8610 + 0x4850) != '\0') && (*(char *)(iGpffff8610 + 0x4851) < '\n')) &&
       (*(char *)(iGpffff8610 + 0x4852) == lVar16)) {
      lVar16 = (long)*(char *)(iGpffff8610 + 0x4853);
      *(uint *)(iVar17 + 0x140) =
           *(uint *)(iVar17 + 0x140) | 3 << (((int)*(char *)(iGpffff8610 + 0x4853) & 0xfU) << 1);
    }
    if (((*(char *)(iGpffff8610 + 0x4858) != '\0') && (*(char *)(iGpffff8610 + 0x4859) < '\n')) &&
       (*(char *)(iGpffff8610 + 0x485a) == lVar16)) {
      lVar16 = (long)*(char *)(iGpffff8610 + 0x485b);
      *(uint *)(iVar17 + 0x140) =
           *(uint *)(iVar17 + 0x140) | 3 << (((int)*(char *)(iGpffff8610 + 0x485b) & 0xfU) << 1);
    }
    iVar5 = iGpffff8610 + (int)lVar16 * 0x510;
    sVar1 = *(short *)(iVar17 + 0x1e);
    if (sVar1 == 2) {
      *(undefined4 *)(iVar17 + 0xe0) = 0;
      *(undefined4 *)(iVar17 + 0xe4) = 0xc1c80000;
      *(undefined4 *)(iVar17 + 0xe8) = 0xc1c80000;
      *(undefined4 *)(iVar17 + 0xec) = 0x41dc0000;
      __pl__7FVectorCFRC7FVector(auStack_1120,iVar5 + 0x160,iVar5 + 0x3a0);
      *(int *)(iVar17 + 0x70) = auStack_1120._0_4_;
      *(int *)(iVar17 + 0x74) = auStack_1120._4_4_;
      *(undefined4 *)(iVar17 + 0x78) = uStack_1118;
      *(undefined4 *)(iVar17 + 0x7c) = uStack_1114;
      *(float *)(iVar17 + 0x74) = *(float *)(iVar17 + 0x74) + *(float *)(iVar5 + 0x3b4) / 2.0;
    }
    else if (sVar1 == 1) {
      *(undefined4 *)(iVar17 + 0xe0) = 0;
      *(undefined4 *)(iVar17 + 0xe4) = 0xc1c80000;
      *(undefined4 *)(iVar17 + 0xe8) = 0xc1700000;
      *(undefined4 *)(iVar17 + 0xec) = 0x41c80000;
      __pl__7FVectorCFRC7FVector(auStack_1110,iVar5 + 0x160,iVar5 + 0x3a0);
      *(int *)(iVar17 + 0x70) = auStack_1110._0_4_;
      *(int *)(iVar17 + 0x74) = auStack_1110._4_4_;
      *(undefined4 *)(iVar17 + 0x78) = uStack_1108;
      *(undefined4 *)(iVar17 + 0x7c) = uStack_1104;
    }
    else if (sVar1 == 0) {
      *(undefined4 *)(iVar17 + 0xe0) = 0;
      *(undefined4 *)(iVar17 + 0xe4) = 0xc1c80000;
      *(undefined4 *)(iVar17 + 0xe8) = 0xc1700000;
      *(undefined4 *)(iVar17 + 0xec) = 0x41dc0000;
      __pl__7FVectorCFRC7FVector(auStack_1100,iVar5 + 0x160,iVar5 + 0x3a0);
      *(int *)(iVar17 + 0x70) = auStack_1100._0_4_;
      *(int *)(iVar17 + 0x74) = auStack_1100._4_4_;
      *(undefined4 *)(iVar17 + 0x78) = uStack_10f8;
      *(undefined4 *)(iVar17 + 0x7c) = uStack_10f4;
      *(float *)(iVar17 + 0x74) = *(float *)(iVar17 + 0x74) - *(float *)(iVar5 + 0x3b4) / 2.0;
    }
    fVar23 = *(float *)(iVar5 + 0x184) + *(float *)(iVar17 + 0xe4);
    if (fVar23 < -180.0) {
      fVar23 = fVar23 + 360.0;
    }
    if (180.0 < fVar23) {
      fVar23 = fVar23 - 360.0;
    }
    FUN_004baab0(*(undefined4 *)(iVar17 + 0xe8),fVar23,0,0x3f800000,auStack_1130);
    *(int *)(iVar17 + 0x60) = auStack_1130._0_4_;
    *(int *)(iVar17 + 100) = auStack_1130._4_4_;
    *(undefined4 *)(iVar17 + 0x68) = uStack_1128;
    *(undefined4 *)(iVar17 + 0x6c) = uStack_1124;
    fVar23 = (float)func_0x00222fd0(iVar5 + 0x3b0);
    *(float *)(iVar17 + 0x80) =
         (*(float *)(iVar17 + 0x84) *
         (*(float *)(iVar17 + 0xec) + *(float *)(iVar5 + 0x354) + fVar23)) / 512.0;
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x60));
    func_0x00202890(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 100));
    func_0x00202938(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x68));
    func_0x002027e8(uVar24,auStack_430,auStack_430);
    uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_1150);
    func_0x00222df0(auStack_1140,auStack_430,uVar8);
    *(int *)(iVar17 + 0x50) = auStack_1140._0_4_;
    *(int *)(iVar17 + 0x54) = auStack_1140._4_4_;
    *(undefined4 *)(iVar17 + 0x58) = uStack_1138;
    *(undefined4 *)(iVar17 + 0x5c) = uStack_1134;
    auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
    auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
    auVar25 = _vadd(auVar25,auVar26);
    auVar25 = _sqc2(auVar25);
    *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    break;
  case 9:
    iVar5 = iGpffff8610 + *(int *)(iVar17 + 0xd0) * 0x510;
    if (*(short *)(iVar17 + 0x1e) == 1) {
LAB_00598690:
      *(undefined4 *)(iVar17 + 0xe0) = 0;
      *(undefined4 *)(iVar17 + 0xe4) = 0xc1f00000;
      *(undefined4 *)(iVar17 + 0xe8) = 0x40a00000;
      *(undefined4 *)(iVar17 + 0xec) = 0x41a00000;
    }
    else if (*(short *)(iVar17 + 0x1e) == 0) {
      *(undefined4 *)(iVar17 + 0xe0) = 0;
      *(undefined4 *)(iVar17 + 0xe4) = 0xc1f00000;
      *(undefined4 *)(iVar17 + 0xe8) = 0x40a00000;
      *(undefined4 *)(iVar17 + 0xec) = 0x41a00000;
      *(undefined2 *)(iVar17 + 0x1e) = 1;
      goto LAB_00598690;
    }
    fVar23 = *(float *)(iVar5 + 0x184) + *(float *)(iVar17 + 0xe4);
    if (fVar23 < -180.0) {
      fVar23 = fVar23 + 360.0;
    }
    if (180.0 < fVar23) {
      fVar23 = fVar23 - 360.0;
    }
    FUN_004baab0(*(undefined4 *)(iVar17 + 0xe8),fVar23,0,0x3f800000,auStack_1160);
    *(int *)(iVar17 + 0x60) = auStack_1160._0_4_;
    *(int *)(iVar17 + 100) = auStack_1160._4_4_;
    *(undefined4 *)(iVar17 + 0x68) = uStack_1158;
    *(undefined4 *)(iVar17 + 0x6c) = uStack_1154;
    __pl__7FVectorCFRC7FVector(auStack_1180,iVar5 + 0x160,iVar5 + 0x3a0);
    uVar8 = FUN_004baab0(0,-*(float *)(iVar5 + 0x3b4) / 2.0,0,0x3f800000,auStack_1190);
    __pl__7FVectorCFRC7FVector(auStack_1170,auStack_1180,uVar8);
    *(int *)(iVar17 + 0x70) = auStack_1170._0_4_;
    *(int *)(iVar17 + 0x74) = auStack_1170._4_4_;
    *(undefined4 *)(iVar17 + 0x78) = uStack_1168;
    *(undefined4 *)(iVar17 + 0x7c) = uStack_1164;
    fVar23 = (float)func_0x00222fd0(iVar5 + 0x3b0);
    *(float *)(iVar17 + 0x80) =
         (*(float *)(iVar17 + 0x84) *
         (*(float *)(iVar17 + 0xec) + *(float *)(iVar5 + 0x354) + fVar23)) / 512.0;
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x60));
    func_0x00202890(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 100));
    func_0x00202938(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x68));
    func_0x002027e8(uVar24,auStack_430,auStack_430);
    uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_11b0);
    func_0x00222df0(auStack_11a0,auStack_430,uVar8);
    *(int *)(iVar17 + 0x50) = auStack_11a0._0_4_;
    *(int *)(iVar17 + 0x54) = auStack_11a0._4_4_;
    *(undefined4 *)(iVar17 + 0x58) = uStack_1198;
    *(undefined4 *)(iVar17 + 0x5c) = uStack_1194;
    auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
    auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
    auVar25 = _vadd(auVar25,auVar26);
    auVar25 = _sqc2(auVar25);
    *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    break;
  case 10:
    iVar5 = iGpffff8610 + *(int *)(iVar17 + 0xd0) * 0x510;
    if (*(short *)(iVar17 + 0x1e) == 1) {
      if ((((*(byte *)(iVar17 + 0x1a) & 1) == 0) && (*(float *)(iVar17 + 0x24) != 0.0)) &&
         ((uVar2 & 0x8000) != 0)) {
        if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3b) < 0) {
          *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0xef;
        }
        else {
          *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0xef | 0x10;
        }
        __pl__7FVectorCFRC7FVector(auStack_11f0,iVar5 + 0x160,iVar5 + 0x3a0);
        uVar8 = func_0x00222f00(auStack_1210,auStack_210);
        Get3DAngle__F7FVector(&uStack_1200,uVar8);
        fStack_1f8 = (float)uStack_11f8;
        auStack_200 = (undefined1  [8])uStack_1200;
        uStack_1f4 = uStack_11f4;
        while ((float)auStack_200._4_4_ < -180.0) {
          auStack_200._4_4_ = (float)auStack_200._4_4_ + 360.0;
        }
        while (180.0 < (float)auStack_200._4_4_) {
          auStack_200._4_4_ = (float)auStack_200._4_4_ - 360.0;
        }
        *(float *)(iVar17 + 0xe4) = -(float)auStack_200._4_4_ - *(float *)(iVar5 + 0x184);
        while (*(float *)(iVar17 + 0xe4) < -180.0) {
          *(float *)(iVar17 + 0xe4) = *(float *)(iVar17 + 0xe4) + 360.0;
        }
        while (180.0 < *(float *)(iVar17 + 0xe4)) {
          *(float *)(iVar17 + 0xe4) = *(float *)(iVar17 + 0xe4) - 360.0;
        }
        *(byte *)(iVar17 + 0x18) = *(byte *)(iVar17 + 0x18) & 0x7f | 0x80;
      }
      if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3b) < 0) {
        fVar23 = 0.0;
        if ((*(byte *)(iVar17 + 0x1a) & 1) == 0) {
          fVar23 = ((float)bStack_44e / 60.0 - (float)bStack_44d / 60.0) *
                   *(float *)(iVar17 + 0x24) * 30.0;
        }
        for (unaff_f20 = fVar23 + *(float *)(iVar17 + 0xe4); unaff_f20 < -180.0;
            unaff_f20 = unaff_f20 + 360.0) {
        }
        for (; 180.0 < unaff_f20; unaff_f20 = unaff_f20 - 360.0) {
        }
        *(undefined4 *)(iVar17 + 0xe8) = 0xc1f00000;
        *(undefined4 *)(iVar17 + 0xec) = 0x42960000;
      }
      else {
        fVar23 = 0.0;
        if ((*(byte *)(iVar17 + 0x1a) & 1) == 0) {
          fVar23 = ((float)bStack_44e / 60.0 - (float)bStack_44d / 60.0) *
                   *(float *)(iVar17 + 0x24) * 30.0;
        }
        for (unaff_f20 = fVar23 + *(float *)(iVar17 + 0xe4); unaff_f20 < -180.0;
            unaff_f20 = unaff_f20 + 360.0) {
        }
        for (; 180.0 < unaff_f20; unaff_f20 = unaff_f20 - 360.0) {
        }
        *(undefined4 *)(iVar17 + 0xe8) = 0xc1700000;
        *(undefined4 *)(iVar17 + 0xec) = 0x42200000;
      }
    }
    else if (*(short *)(iVar17 + 0x1e) == 0) {
      if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3b) < 0) {
        *(undefined4 *)(iVar17 + 0xe0) = 0;
        *(undefined4 *)(iVar17 + 0xe8) = 0xc1f00000;
        *(undefined4 *)(iVar17 + 0xec) = 0x42960000;
      }
      else {
        *(undefined4 *)(iVar17 + 0xe0) = 0;
        *(undefined4 *)(iVar17 + 0xe8) = 0xc1700000;
        *(undefined4 *)(iVar17 + 0xec) = 0x42200000;
      }
      __pl__7FVectorCFRC7FVector(auStack_11c0,iVar5 + 0x160,iVar5 + 0x3a0);
      uVar8 = func_0x00222f00(auStack_11e0,auStack_210);
      Get3DAngle__F7FVector(&uStack_11d0,uVar8);
      fStack_1f8 = (float)uStack_11c8;
      auStack_200 = (undefined1  [8])uStack_11d0;
      uStack_1f4 = uStack_11c4;
      while ((float)auStack_200._4_4_ < -180.0) {
        auStack_200._4_4_ = (float)auStack_200._4_4_ + 360.0;
      }
      while (180.0 < (float)auStack_200._4_4_) {
        auStack_200._4_4_ = (float)auStack_200._4_4_ - 360.0;
      }
      *(float *)(iVar17 + 0xe4) = -(float)auStack_200._4_4_ - *(float *)(iVar5 + 0x184);
      while (*(float *)(iVar17 + 0xe4) < -180.0) {
        *(float *)(iVar17 + 0xe4) = *(float *)(iVar17 + 0xe4) + 360.0;
      }
      while (180.0 < *(float *)(iVar17 + 0xe4)) {
        *(float *)(iVar17 + 0xe4) = *(float *)(iVar17 + 0xe4) - 360.0;
      }
      unaff_f20 = *(float *)(iVar17 + 0xe4);
      *(undefined2 *)(iVar17 + 0x1e) = 1;
    }
    for (fVar23 = *(float *)(iVar5 + 0x184) + unaff_f20; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 <= fVar23; fVar23 = fVar23 - 360.0) {
    }
    FUN_004baab0(*(undefined4 *)(iVar17 + 0xe8),fVar23,0,0x3f800000,auStack_1220);
    *(int *)(iVar17 + 0x60) = auStack_1220._0_4_;
    *(int *)(iVar17 + 100) = auStack_1220._4_4_;
    *(undefined4 *)(iVar17 + 0x68) = uStack_1218;
    *(undefined4 *)(iVar17 + 0x6c) = uStack_1214;
    __pl__7FVectorCFRC7FVector(auStack_1230,iVar5 + 0x160,iVar5 + 0x3a0);
    *(int *)(iVar17 + 0x70) = auStack_1230._0_4_;
    *(int *)(iVar17 + 0x74) = auStack_1230._4_4_;
    *(undefined4 *)(iVar17 + 0x78) = uStack_1228;
    *(undefined4 *)(iVar17 + 0x7c) = uStack_1224;
    *(undefined4 *)(iVar17 + 0x74) = 0;
    fVar23 = (float)func_0x00222fd0(iVar5 + 0x3b0);
    *(float *)(iVar17 + 0x80) =
         (*(float *)(iVar17 + 0x84) *
         (*(float *)(iVar17 + 0xec) + *(float *)(iVar5 + 0x354) + fVar23)) / 512.0;
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x60));
    func_0x00202890(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 100));
    func_0x00202938(uVar24,auStack_430,auStack_430);
    uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_1250);
    func_0x00222df0(auStack_1240,auStack_430,uVar8);
    *(int *)(iVar17 + 0x50) = auStack_1240._0_4_;
    *(int *)(iVar17 + 0x54) = auStack_1240._4_4_;
    *(undefined4 *)(iVar17 + 0x58) = uStack_1238;
    *(undefined4 *)(iVar17 + 0x5c) = uStack_1234;
    auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
    auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
    auVar25 = _vadd(auVar25,auVar26);
    auVar25 = _sqc2(auVar25);
    *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    bVar4 = false;
    for (fVar23 = *(float *)(iVar5 + 0x184) + *(float *)(iVar17 + 0xe4); fVar23 < -180.0;
        fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 <= fVar23; fVar23 = fVar23 - 360.0) {
    }
    if (*(float *)(iVar17 + 0x50) < -*(float *)(iGpffff8610 + 0x40b4) / 2.0 + 5.0) {
      if ((*(float *)(iVar17 + 100) < 50.0) || (130.0 < *(float *)(iVar17 + 100))) {
        bVar4 = true;
      }
      if ((fVar23 < 50.0) || (130.0 < fVar23)) {
        bVar4 = true;
      }
    }
    if (*(float *)(iGpffff8610 + 0x40b4) / 2.0 - 5.0 < *(float *)(iVar17 + 0x50)) {
      if ((-50.0 < *(float *)(iVar17 + 100)) || (*(float *)(iVar17 + 100) < -130.0)) {
        bVar4 = true;
      }
      if ((-50.0 < fVar23) || (fVar23 < -130.0)) {
        bVar4 = true;
      }
    }
    if (*(float *)(iVar17 + 0x58) < -*(float *)(iGpffff8610 + 0x40bc) / 2.0 + 5.0) {
      if ((*(float *)(iVar17 + 100) < -40.0) || (40.0 < *(float *)(iVar17 + 100))) {
        bVar4 = true;
      }
      if ((fVar23 < -40.0) || (40.0 < fVar23)) {
        bVar4 = true;
      }
    }
    if (*(float *)(iGpffff8610 + 0x40bc) / 2.0 - 5.0 < *(float *)(iVar17 + 0x58)) {
      if ((-140.0 < *(float *)(iVar17 + 100)) && (*(float *)(iVar17 + 100) < 140.0)) {
        bVar4 = true;
      }
      if ((-140.0 < fVar23) && (fVar23 < 140.0)) {
        bVar4 = true;
      }
    }
    if (bVar4) {
      FUN_004baab0(*(undefined4 *)(iVar17 + 0xe8),fVar23,0,0x3f800000,auStack_1260);
      *(int *)(iVar17 + 0x60) = auStack_1260._0_4_;
      *(int *)(iVar17 + 100) = auStack_1260._4_4_;
      *(undefined4 *)(iVar17 + 0x68) = uStack_1258;
      *(undefined4 *)(iVar17 + 0x6c) = uStack_1254;
      auVar25 = _vmr32(in_vf0);
      auVar26 = _vmr32(auVar25);
      auVar27 = _vmr32(auVar26);
      auStack_400 = _sqc2(in_vf0);
      auStack_410 = _sqc2(auVar25);
      auStack_420 = _sqc2(auVar26);
      auStack_430 = _sqc2(auVar27);
      uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x60));
      func_0x00202890(uVar24,auStack_430,auStack_430);
      uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 100));
      func_0x00202938(uVar24,auStack_430,auStack_430);
      uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_1280);
      func_0x00222df0(auStack_1270,auStack_430,uVar8);
      *(int *)(iVar17 + 0x50) = auStack_1270._0_4_;
      *(int *)(iVar17 + 0x54) = auStack_1270._4_4_;
      *(undefined4 *)(iVar17 + 0x58) = uStack_1268;
      *(undefined4 *)(iVar17 + 0x5c) = uStack_1264;
      auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
      auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _vadd(auVar25,auVar26);
      auVar25 = _sqc2(auVar25);
      *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    }
    else {
      *(float *)(iVar17 + 0xe4) = unaff_f20;
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    __pl__7FVectorCFRC7FVector(auStack_12b0,iVar5 + 0x160,iVar5 + 0x3a0);
    uVar8 = FUN_004baab0(0,-*(float *)(iVar5 + 0x3b4) - 5.0,0,0x3f800000,auStack_12c0);
    __pl__7FVectorCFRC7FVector(auStack_12a0,auStack_12b0,uVar8);
    __mi__7FVectorCFRC7FVector(&uStack_1290,auStack_12a0,iVar17 + 0x50);
    uStack_208._0_4_ = (float)uStack_1288;
    _auStack_210 = uStack_1290;
    uStack_208._4_4_ = (float)uStack_1284;
    __mi__7FVectorCFRC7FVector(&uStack_12d0,iVar17 + 0x70,iVar17 + 0x50);
    fStack_1f8 = (float)uStack_12c8;
    auStack_200 = (undefined1  [8])uStack_12d0;
    uStack_1f4 = uStack_12c4;
    uVar8 = func_0x00222f00(auStack_12f0,auStack_210);
    Get3DAngle__F7FVector(auStack_12e0,uVar8);
    fStack_1f0 = auStack_12e0._0_4_;
    fStack_1ec = auStack_12e0._4_4_;
    fStack_1e8 = fStack_12d8;
    uStack_1e4 = uStack_12d4;
    uVar8 = func_0x00222f00(auStack_1310,auStack_200);
    Get3DAngle__F7FVector(auStack_1300,uVar8);
    fStack_1e0 = auStack_1300._0_4_;
    fStack_1dc = auStack_1300._4_4_;
    fStack_1d8 = fStack_12f8;
    uStack_1d4 = uStack_12f4;
    for (; fStack_1f0 < -180.0; fStack_1f0 = fStack_1f0 + 360.0) {
    }
    for (; 180.0 < fStack_1f0; fStack_1f0 = fStack_1f0 - 360.0) {
    }
    for (; fStack_1e0 < -180.0; fStack_1e0 = fStack_1e0 + 360.0) {
    }
    for (; 180.0 < fStack_1e0; fStack_1e0 = fStack_1e0 - 360.0) {
    }
    fVar23 = fStack_1e0;
    if (fStack_1f0 <= fStack_1e0) {
      fVar23 = fStack_1f0;
    }
    fVar22 = fStack_1e0;
    if (fStack_1e0 <= fStack_1f0) {
      fVar22 = fStack_1f0;
    }
    for (fVar22 = fVar22 - fVar23; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
    }
    for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
    }
    *(float *)(iVar17 + 0x60) = -(fVar23 + fVar22 / 2.0);
    while (*(float *)(iVar17 + 0x60) < -180.0) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 0x60)) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
    }
    for (; fStack_1ec < -180.0; fStack_1ec = fStack_1ec + 360.0) {
    }
    for (; 180.0 < fStack_1ec; fStack_1ec = fStack_1ec - 360.0) {
    }
    for (; fStack_1dc < -180.0; fStack_1dc = fStack_1dc + 360.0) {
    }
    for (; 180.0 < fStack_1dc; fStack_1dc = fStack_1dc - 360.0) {
    }
    fVar23 = fStack_1dc;
    if (fStack_1ec <= fStack_1dc) {
      fVar23 = fStack_1ec;
    }
    fVar22 = fStack_1dc;
    if (fStack_1dc <= fStack_1ec) {
      fVar22 = fStack_1ec;
    }
    for (fVar22 = fVar22 - fVar23; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
    }
    for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
    }
    *(float *)(iVar17 + 100) = -(fVar23 + fVar22 / 2.0);
    while (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    break;
  case 0xb:
    *(byte *)(iVar17 + 0x1a) = *(byte *)(iVar17 + 0x1a) & 0xfd;
    iVar5 = iGpffff8610 + *(int *)(iVar17 + 0xd0) * 0x510;
    iVar15 = iGpffff8610 + *(int *)(iVar17 + 0xd4) * 0x510;
    if ((((*(byte *)(iVar17 + 0x1a) & 1) == 0) && (*(float *)(iVar17 + 0x24) != 0.0)) &&
       ((uVar2 & 0x8000) != 0)) {
      if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3b) < 0) {
        *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0xef;
      }
      else {
        *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0xef | 0x10;
        *(undefined4 *)(iVar17 + 0xe0) = 0;
      }
      *(byte *)(iVar17 + 0x1a) = *(byte *)(iVar17 + 0x1a) & 0xfd | 2;
      *(byte *)(iVar17 + 0x18) = *(byte *)(iVar17 + 0x18) & 0x7f | 0x80;
    }
    if (*(short *)(iVar17 + 0x1e) == 0) {
      __pl__7FVectorCFRC7FVector(&uStack_1320,iVar15 + 0x160,iVar15 + 0x3a0);
      uStack_208._0_4_ = (float)uStack_1318;
      _auStack_210 = uStack_1320;
      uStack_208._4_4_ = (float)uStack_1314;
      __pl__7FVectorCFRC7FVector(auStack_1330,iVar5 + 0x160,iVar5 + 0x3a0);
      auVar26 = _lqc2(auStack_1330);
      auVar25 = _lqc2(_auStack_210);
      auVar25 = _vsub(auVar25,auVar26);
      _auStack_210 = _sqc2(auVar25);
      fVar23 = (float)func_0x00222fd0(auStack_210);
      if (-((*(float *)(iVar15 + 0x164) + *(float *)(iVar15 + 0x3a4)) - *(float *)(iVar15 + 0x3b4))
          * 2.0 * 10.0 + *(float *)(iVar5 + 0x354) + *(float *)(iVar15 + 0x354) <= fVar23) {
        *(undefined2 *)(iVar17 + 0x1e) = 1;
      }
      else {
        *(undefined2 *)(iVar17 + 0x1e) = 2;
      }
      *(byte *)(iVar17 + 0x1a) = *(byte *)(iVar17 + 0x1a) & 0xfd | 2;
    }
    if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3b) < 0) {
      __pl__7FVectorCFRC7FVector(auStack_1840,iVar5 + 0x160,iVar5 + 0x3a0);
      uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar5 + 0x3b4),0,0x3f800000,auStack_1850);
      __pl__7FVectorCFRC7FVector(auStack_1830,auStack_1840,uVar8);
      __pl__7FVectorCFRC7FVector(auStack_1870,iVar15 + 0x160,iVar15 + 0x3a0);
      uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar15 + 0x3b4),0,0x3f800000,auStack_1880);
      __pl__7FVectorCFRC7FVector(auStack_1860,auStack_1870,uVar8);
      fStack_1e0 = auStack_1860._0_4_;
      fStack_1dc = auStack_1860._4_4_;
      fStack_1d8 = fStack_1858;
      uStack_1d4 = uStack_1854;
      __pl__7FVectorCFRC7FVector(auStack_1890,auStack_200,&fStack_1e0);
      *(int *)(iVar17 + 0x70) = auStack_1890._0_4_;
      *(int *)(iVar17 + 0x74) = auStack_1890._4_4_;
      *(undefined4 *)(iVar17 + 0x78) = uStack_1888;
      *(undefined4 *)(iVar17 + 0x7c) = uStack_1884;
      func_0x00223030(0x40000000,iVar17 + 0x70);
      *(undefined4 *)(iVar17 + 0x74) = 0;
      __pl__7FVectorCFRC7FVector(&uStack_18a0,iVar5 + 0x160,iVar5 + 0x3a0);
      uStack_208._0_4_ = (float)uStack_1898;
      _auStack_210 = uStack_18a0;
      uStack_208._4_4_ = (float)uStack_1894;
      __pl__7FVectorCFRC7FVector(&uStack_18b0,iVar15 + 0x160,iVar15 + 0x3a0);
      fStack_1f8 = (float)uStack_18a8;
      auStack_200 = (undefined1  [8])uStack_18b0;
      uStack_1f4 = uStack_18a4;
      auVar26 = _lqc2(_auStack_200);
      auVar25 = _lqc2(_auStack_210);
      auVar25 = _vsub(auVar25,auVar26);
      _auStack_210 = _sqc2(auVar25);
      fVar23 = (float)func_0x00222fd0(auStack_210);
      fVar22 = *(float *)(iVar15 + 0x354) + *(float *)(iVar5 + 0x354) + fVar23 + 10.0;
      fVar23 = ((*(float *)(iGpffff8610 + 0x40b4) + *(float *)(iGpffff8610 + 0x40bc) + 10.0 + 10.0)
               / 2.0) / 1.5;
      if (fVar22 <= fVar23) {
        fVar23 = fVar22;
      }
      *(undefined4 *)(iVar17 + 0x84) = 0x44000000;
      *(float *)(iVar17 + 0x80) = (fVar23 * *(float *)(iVar17 + 0x84)) / 512.0;
      if ((long)((ulong)*(byte *)(iVar17 + 0x1a) << 0x3e) < 0) {
        uVar8 = func_0x00222f00(auStack_18d0,iVar17 + 0x70);
        Get3DAngle__F7FVector(&uStack_18c0,uVar8);
        uStack_208._0_4_ = (float)uStack_18b8;
        _auStack_210 = uStack_18c0;
        uStack_208._4_4_ = (float)uStack_18b4;
        *(float *)(iVar17 + 0xe0) = -(float)((ulong)uStack_18c0 >> 0x20);
        while (*(float *)(iVar17 + 0xe0) < -180.0) {
          *(float *)(iVar17 + 0xe0) = *(float *)(iVar17 + 0xe0) + 360.0;
        }
        while (180.0 <= *(float *)(iVar17 + 0xe0)) {
          *(float *)(iVar17 + 0xe0) = *(float *)(iVar17 + 0xe0) - 360.0;
        }
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(0xc1a00000);
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0xe0));
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_18f0);
        func_0x00222df0(auStack_18e0,auStack_430,uVar8);
        *(int *)(iVar17 + 0x50) = auStack_18e0._0_4_;
        *(int *)(iVar17 + 0x54) = auStack_18e0._4_4_;
        *(undefined4 *)(iVar17 + 0x58) = uStack_18d8;
        *(undefined4 *)(iVar17 + 0x5c) = uStack_18d4;
        auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
        auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
        auVar25 = _vadd(auVar25,auVar26);
        auVar25 = _sqc2(auVar25);
        *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
      }
      else {
        fVar23 = 0.0;
        if ((*(byte *)(iVar17 + 0x1a) & 1) == 0) {
          fVar23 = ((float)bStack_44e / 60.0 - (float)bStack_44d / 60.0) *
                   *(float *)(iVar17 + 0x24) * 30.0;
        }
        for (fVar23 = fVar23 + *(float *)(iVar17 + 0xe0); fVar23 < -180.0; fVar23 = fVar23 + 360.0)
        {
        }
        for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
        }
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(0xc1a00000);
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(fVar23);
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_1910);
        func_0x00222df0(auStack_1900,auStack_430,uVar8);
        *(int *)(iVar17 + 0x50) = auStack_1900._0_4_;
        *(int *)(iVar17 + 0x54) = auStack_1900._4_4_;
        *(undefined4 *)(iVar17 + 0x58) = uStack_18f8;
        *(undefined4 *)(iVar17 + 0x5c) = uStack_18f4;
        auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
        auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
        auVar25 = _vadd(auVar25,auVar26);
        auVar25 = _sqc2(auVar25);
        *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
        bVar4 = false;
        fVar22 = *(float *)(iVar17 + 0xe0);
        if (*(float *)(iVar17 + 0x50) < -*(float *)(iGpffff8610 + 0x40b4) / 2.0 + 5.0) {
          if ((fVar23 < 50.0) || (130.0 < fVar23)) {
            bVar4 = true;
          }
          if ((fVar22 < 50.0) || (130.0 < fVar22)) {
            bVar4 = true;
          }
        }
        if (*(float *)(iGpffff8610 + 0x40b4) / 2.0 - 5.0 < *(float *)(iVar17 + 0x50)) {
          if ((-50.0 < fVar23) || (fVar23 < -130.0)) {
            bVar4 = true;
          }
          if ((-50.0 < fVar22) || (fVar22 < -130.0)) {
            bVar4 = true;
          }
        }
        if (*(float *)(iVar17 + 0x58) < -*(float *)(iGpffff8610 + 0x40bc) / 2.0 + 5.0) {
          if ((fVar23 < -40.0) || (40.0 < fVar23)) {
            bVar4 = true;
          }
          if ((fVar22 < -40.0) || (40.0 < fVar22)) {
            bVar4 = true;
          }
        }
        if (*(float *)(iGpffff8610 + 0x40bc) / 2.0 - 5.0 < *(float *)(iVar17 + 0x58)) {
          if ((-140.0 < fVar23) && (fVar23 < 140.0)) {
            bVar4 = true;
          }
          if ((-140.0 < fVar22) && (fVar22 < 140.0)) {
            bVar4 = true;
          }
        }
        if (bVar4) {
          auVar25 = _vmr32(in_vf0);
          auVar26 = _vmr32(auVar25);
          auVar27 = _vmr32(auVar26);
          auStack_400 = _sqc2(in_vf0);
          auStack_410 = _sqc2(auVar25);
          auStack_420 = _sqc2(auVar26);
          auStack_430 = _sqc2(auVar27);
          uVar24 = func_0x00222e40(0xc1a00000);
          func_0x00202890(uVar24,auStack_430,auStack_430);
          uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0xe0));
          func_0x00202938(uVar24,auStack_430,auStack_430);
          uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_1930);
          func_0x00222df0(auStack_1920,auStack_430,uVar8);
          *(int *)(iVar17 + 0x50) = auStack_1920._0_4_;
          *(int *)(iVar17 + 0x54) = auStack_1920._4_4_;
          *(undefined4 *)(iVar17 + 0x58) = uStack_1918;
          *(undefined4 *)(iVar17 + 0x5c) = uStack_1914;
          auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
          auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
          auVar25 = _vadd(auVar25,auVar26);
          auVar25 = _sqc2(auVar25);
          *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
        }
        else {
          *(float *)(iVar17 + 0xe0) = fVar23;
        }
      }
    }
    else {
      __pl__7FVectorCFRC7FVector(&uStack_1340,iVar15 + 0x160,iVar15 + 0x3a0);
      uStack_208._0_4_ = (float)uStack_1338;
      _auStack_210 = uStack_1340;
      uStack_208._4_4_ = (float)uStack_1334;
      __pl__7FVectorCFRC7FVector(auStack_1350,iVar5 + 0x160,iVar5 + 0x3a0);
      auVar26 = _lqc2(auStack_1350);
      auVar25 = _lqc2(_auStack_210);
      auVar25 = _vsub(auVar25,auVar26);
      _auStack_210 = _sqc2(auVar25);
      FUN_004baab0(*(undefined4 *)(iGpffff8610 + 0x40b4),0,*(undefined4 *)(iGpffff8610 + 0x40bc),
                   0x3f800000,auStack_1360);
      fVar23 = (float)func_0x00222fd0(auStack_210);
      fVar22 = (float)func_0x00222fd0(auStack_200);
      *(float *)(iVar17 + 0x84) = (fVar23 / (fVar22 * 0.75) + 1.2) * 512.0;
      if (*(short *)(iVar17 + 0x1e) == 1) {
        uVar8 = func_0x00222f00(auStack_1380,auStack_210);
        Get3DAngle__F7FVector(&uStack_1370,uVar8);
        fStack_1f8 = (float)uStack_1368;
        auStack_200 = (undefined1  [8])uStack_1370;
        uStack_1f4 = uStack_1364;
        fVar23 = *(float *)(iVar5 + 0x3b4) * 0.75;
        if (fVar23 < 4.0) {
          fVar23 = 4.0;
        }
        fVar21 = (float)func_0x00222fd0(iVar5 + 0x3b0);
        fVar20 = *(float *)(iVar5 + 0x354);
        fVar19 = *(float *)(iVar17 + 0x84);
        fVar22 = -(float)auStack_200._0_4_;
        if ((fVar22 <= 40.0) && (fVar22 = fVar22 * 1.25 - 10.0, fVar22 < -10.0)) {
          fVar22 = -10.0;
        }
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(fVar22);
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-((fVar19 * (fVar20 + fVar21 + 20.0)) / 512.0),0x3f800000,
                             auStack_13a0);
        func_0x00222df0(&uStack_1390,auStack_430,uVar8);
        uStack_208._0_4_ = (float)uStack_1388;
        _auStack_210 = uStack_1390;
        uStack_208._4_4_ = (float)uStack_1384;
        __pl__7FVectorCFRC7FVector(auStack_13d0,auStack_210,iVar5 + 0x160);
        __pl__7FVectorCFRC7FVector(auStack_13c0,auStack_13d0,iVar5 + 0x3a0);
        uVar8 = FUN_004baab0(0,-*(float *)(iVar5 + 0x3b4) - fVar23,0,0x3f800000,auStack_13e0);
        __pl__7FVectorCFRC7FVector(auStack_13b0,auStack_13c0,uVar8);
        *(int *)(iVar17 + 0x50) = auStack_13b0._0_4_;
        *(int *)(iVar17 + 0x54) = auStack_13b0._4_4_;
        *(undefined4 *)(iVar17 + 0x58) = uStack_13a8;
        *(undefined4 *)(iVar17 + 0x5c) = uStack_13a4;
        if (-10.0 < *(float *)(iVar17 + 0x54)) {
          *(undefined4 *)(iVar17 + 0x54) = 0xc1200000;
        }
      }
      else {
        __pl__7FVectorCFRC7FVector(&uStack_13f0,iVar15 + 0x160,iVar15 + 0x3a0);
        uStack_208._0_4_ = (float)uStack_13e8;
        _auStack_210 = uStack_13f0;
        uStack_208._4_4_ = (float)uStack_13e4;
        __pl__7FVectorCFRC7FVector(auStack_1400,iVar5 + 0x160,iVar5 + 0x3a0);
        auVar26 = _lqc2(auStack_1400);
        auVar25 = _lqc2(_auStack_210);
        auVar25 = _vsub(auVar25,auVar26);
        _auStack_210 = _sqc2(auVar25);
        uVar8 = func_0x00222f00(auStack_1420,auStack_210);
        Get3DAngle__F7FVector(&uStack_1410,uVar8);
        fStack_1f8 = (float)uStack_1408;
        auStack_200 = (undefined1  [8])uStack_1410;
        uStack_1f4 = uStack_1404;
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(-(float)((ulong)uStack_1410 >> 0x20));
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(*(float *)(iVar5 + 0x354) * 2.0,0,0,0x3f800000,auStack_1440);
        func_0x00222df0(auStack_1430,auStack_430,uVar8);
        fStack_1f0 = auStack_1430._0_4_;
        fStack_1ec = auStack_1430._4_4_;
        fStack_1e8 = fStack_1428;
        uStack_1e4 = uStack_1424;
        uVar8 = FUN_004baab0(-*(float *)(iVar5 + 0x354) * 2.0,0,0,0x3f800000,auStack_1460);
        func_0x00222df0(auStack_1450,auStack_430,uVar8);
        fStack_1e0 = auStack_1450._0_4_;
        fStack_1dc = auStack_1450._4_4_;
        fStack_1d8 = fStack_1448;
        uStack_1d4 = uStack_1444;
        bVar3 = *(byte *)(iVar17 + 0x19) >> 6;
        if (bVar3 == 2) {
          __pl__7FVectorCFRC7FVector(auStack_17b0,iVar5 + 0x160,iVar5 + 0x3a0);
          __pl__7FVectorCFRC7FVector(&uStack_17a0,auStack_17b0,&fStack_1e0);
          uStack_208._0_4_ = (float)uStack_1798;
          _auStack_210 = uStack_17a0;
          uStack_208._4_4_ = (float)uStack_1794;
          __pl__7FVectorCFRC7FVector(auStack_17d0,iVar15 + 0x160,iVar15 + 0x3a0);
          __mi__7FVectorCFRC7FVector(auStack_17c0,auStack_17d0,auStack_210);
          uVar8 = func_0x00222f00(auStack_17f0,auStack_200);
          Get3DAngle__F7FVector(&uStack_17e0,uVar8);
          fStack_1f8 = (float)uStack_17d8;
          auStack_200 = (undefined1  [8])uStack_17e0;
          uStack_1f4 = uStack_17d4;
          fVar23 = -(float)uStack_17e0;
          if ((fVar23 <= 40.0) && (fVar23 = fVar23 * 1.25 - 10.0, fVar23 < -10.0)) {
            fVar23 = -10.0;
          }
          fVar20 = (float)func_0x00222fd0(iVar5 + 0x3b0);
          fVar22 = *(float *)(iVar5 + 0x354);
          fVar21 = *(float *)(iVar17 + 0x84);
          auVar25 = _vmr32(in_vf0);
          auVar26 = _vmr32(auVar25);
          auVar27 = _vmr32(auVar26);
          auStack_400 = _sqc2(in_vf0);
          auStack_410 = _sqc2(auVar25);
          auStack_420 = _sqc2(auVar26);
          auStack_430 = _sqc2(auVar27);
          uVar24 = func_0x00222e40(fVar23);
          func_0x00202890(uVar24,auStack_430,auStack_430);
          uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
          func_0x00202938(uVar24,auStack_430,auStack_430);
          uVar8 = FUN_004baab0(0,0,-((fVar21 * (fVar22 + fVar20 + 20.0)) / 512.0),0x3f800000,
                               auStack_1810);
          func_0x00222df0(&uStack_1800,auStack_430,uVar8);
          fStack_1f8 = (float)uStack_17f8;
          auStack_200 = (undefined1  [8])uStack_1800;
          uStack_1f4 = uStack_17f4;
          __pl__7FVectorCFRC7FVector(&uStack_1820,auStack_210,auStack_200);
          auStack_300._8_4_ = uStack_1818;
          auStack_300._0_8_ = uStack_1820;
          auStack_300._12_4_ = uStack_1814;
          *(int *)(iVar17 + 0x50) = (int)uStack_1820;
          *(int *)(iVar17 + 0x54) = (int)((ulong)uStack_1820 >> 0x20);
          *(undefined4 *)(iVar17 + 0x58) = uStack_1818;
          *(undefined4 *)(iVar17 + 0x5c) = uStack_1814;
        }
        else if (bVar3 == 1) {
          __pl__7FVectorCFRC7FVector(auStack_1720,iVar5 + 0x160,iVar5 + 0x3a0);
          __pl__7FVectorCFRC7FVector(&uStack_1710,auStack_1720,&fStack_1f0);
          uStack_208._0_4_ = (float)uStack_1708;
          _auStack_210 = uStack_1710;
          uStack_208._4_4_ = (float)uStack_1704;
          __pl__7FVectorCFRC7FVector(auStack_1740,iVar15 + 0x160,iVar15 + 0x3a0);
          __mi__7FVectorCFRC7FVector(auStack_1730,auStack_1740,auStack_210);
          uVar8 = func_0x00222f00(auStack_1760,auStack_200);
          Get3DAngle__F7FVector(&uStack_1750,uVar8);
          fStack_1f8 = (float)uStack_1748;
          auStack_200 = (undefined1  [8])uStack_1750;
          uStack_1f4 = uStack_1744;
          fVar23 = -(float)uStack_1750;
          if ((fVar23 <= 40.0) && (fVar23 = fVar23 * 1.25 - 10.0, fVar23 < -10.0)) {
            fVar23 = -10.0;
          }
          fVar20 = (float)func_0x00222fd0(iVar5 + 0x3b0);
          fVar22 = *(float *)(iVar5 + 0x354);
          fVar21 = *(float *)(iVar17 + 0x84);
          auVar25 = _vmr32(in_vf0);
          auVar26 = _vmr32(auVar25);
          auVar27 = _vmr32(auVar26);
          auStack_400 = _sqc2(in_vf0);
          auStack_410 = _sqc2(auVar25);
          auStack_420 = _sqc2(auVar26);
          auStack_430 = _sqc2(auVar27);
          uVar24 = func_0x00222e40(fVar23);
          func_0x00202890(uVar24,auStack_430,auStack_430);
          uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
          func_0x00202938(uVar24,auStack_430,auStack_430);
          uVar8 = FUN_004baab0(0,0,-((fVar21 * (fVar22 + fVar20 + 20.0)) / 512.0),0x3f800000,
                               auStack_1780);
          func_0x00222df0(&uStack_1770,auStack_430,uVar8);
          fStack_1f8 = (float)uStack_1768;
          auStack_200 = (undefined1  [8])uStack_1770;
          uStack_1f4 = uStack_1764;
          __pl__7FVectorCFRC7FVector(&uStack_1790,auStack_210,auStack_200);
          afStack_30c[1] = (float)uStack_1788;
          _auStack_310 = uStack_1790;
          afStack_30c[2] = (float)uStack_1784;
          *(int *)(iVar17 + 0x50) = (int)uStack_1790;
          *(int *)(iVar17 + 0x54) = (int)((ulong)uStack_1790 >> 0x20);
          *(undefined4 *)(iVar17 + 0x58) = uStack_1788;
          *(undefined4 *)(iVar17 + 0x5c) = uStack_1784;
        }
        else if (bVar3 == 0) {
          __pl__7FVectorCFRC7FVector(auStack_1480,iVar5 + 0x160,iVar5 + 0x3a0);
          __pl__7FVectorCFRC7FVector(auStack_1470,auStack_1480,&fStack_1f0);
          __pl__7FVectorCFRC7FVector(auStack_14a0,iVar15 + 0x160,iVar15 + 0x3a0);
          __mi__7FVectorCFRC7FVector(auStack_1490,auStack_14a0,auStack_210);
          uVar8 = func_0x00222f00(auStack_14c0,auStack_200);
          Get3DAngle__F7FVector(&uStack_14b0,uVar8);
          fStack_1f8 = (float)uStack_14a8;
          auStack_200 = (undefined1  [8])uStack_14b0;
          uStack_1f4 = uStack_14a4;
          fVar23 = -(float)uStack_14b0;
          if ((fVar23 <= 40.0) && (fVar23 = fVar23 * 1.25 - 10.0, fVar23 < -10.0)) {
            fVar23 = -10.0;
          }
          fVar20 = (float)func_0x00222fd0(iVar5 + 0x3b0);
          fVar22 = *(float *)(iVar5 + 0x354);
          fVar21 = *(float *)(iVar17 + 0x84);
          auVar25 = _vmr32(in_vf0);
          auVar26 = _vmr32(auVar25);
          auVar27 = _vmr32(auVar26);
          auStack_400 = _sqc2(in_vf0);
          auStack_410 = _sqc2(auVar25);
          auStack_420 = _sqc2(auVar26);
          auStack_430 = _sqc2(auVar27);
          uVar24 = func_0x00222e40(fVar23);
          func_0x00202890(uVar24,auStack_430,auStack_430);
          uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
          func_0x00202938(uVar24,auStack_430,auStack_430);
          uVar8 = FUN_004baab0(0,0,-((fVar21 * (fVar22 + fVar20 + 20.0)) / 512.0),0x3f800000,
                               auStack_14e0);
          func_0x00222df0(auStack_14d0,auStack_430,uVar8);
          __pl__7FVectorCFRC7FVector(&uStack_14f0,auStack_210,auStack_200);
          afStack_30c[1] = (float)uStack_14e8;
          _auStack_310 = uStack_14f0;
          afStack_30c[2] = (float)uStack_14e4;
          __pl__7FVectorCFRC7FVector(auStack_1510,iVar5 + 0x160,iVar5 + 0x3a0);
          __pl__7FVectorCFRC7FVector(auStack_1500,auStack_1510,&fStack_1e0);
          __pl__7FVectorCFRC7FVector(auStack_1530,iVar15 + 0x160,iVar15 + 0x3a0);
          __mi__7FVectorCFRC7FVector(auStack_1520,auStack_1530,auStack_210);
          uVar8 = func_0x00222f00(auStack_1550,auStack_200);
          Get3DAngle__F7FVector(&uStack_1540,uVar8);
          fStack_1f8 = (float)uStack_1538;
          auStack_200 = (undefined1  [8])uStack_1540;
          uStack_1f4 = uStack_1534;
          fVar23 = -(float)uStack_1540;
          if ((fVar23 <= 40.0) && (fVar23 = fVar23 * 1.25 - 10.0, fVar23 < -10.0)) {
            fVar23 = -10.0;
          }
          fVar20 = (float)func_0x00222fd0(iVar5 + 0x3b0);
          fVar22 = *(float *)(iVar5 + 0x354);
          fVar21 = *(float *)(iVar17 + 0x84);
          auVar25 = _vmr32(in_vf0);
          auVar26 = _vmr32(auVar25);
          auVar27 = _vmr32(auVar26);
          auStack_400 = _sqc2(in_vf0);
          auStack_410 = _sqc2(auVar25);
          auStack_420 = _sqc2(auVar26);
          auStack_430 = _sqc2(auVar27);
          uVar24 = func_0x00222e40(fVar23);
          func_0x00202890(uVar24,auStack_430,auStack_430);
          uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
          func_0x00202938(uVar24,auStack_430,auStack_430);
          uVar8 = FUN_004baab0(0,0,-((fVar21 * (fVar22 + fVar20 + 20.0)) / 512.0),0x3f800000,
                               auStack_1570);
          func_0x00222df0(auStack_1560,auStack_430,uVar8);
          __pl__7FVectorCFRC7FVector(&uStack_1580,auStack_210,auStack_200);
          auStack_300._8_4_ = uStack_1578;
          auStack_300._0_8_ = uStack_1580;
          auStack_300._12_4_ = uStack_1574;
          __pl__7FVectorCFRC7FVector(auStack_15a0,iVar5 + 0x160,iVar5 + 0x3a0);
          __mi__7FVectorCFRC7FVector(auStack_1590,auStack_15a0,auStack_310);
          uVar24 = func_0x00222fd0(auStack_210);
          uVar8 = func_0x00222f00(auStack_15c0,auStack_210);
          Get3DAngle__F7FVector(&uStack_15b0,uVar8);
          uStack_208._0_4_ = (float)uVar24;
          _auStack_210 = uStack_15b0;
          uStack_208._4_4_ = (float)uStack_15a4;
          __pl__7FVectorCFRC7FVector(auStack_15e0,iVar15 + 0x160,iVar15 + 0x3a0);
          __mi__7FVectorCFRC7FVector(&uStack_15d0,auStack_15e0,auStack_310);
          fStack_1f8 = (float)uStack_15c8;
          auStack_200 = (undefined1  [8])uStack_15d0;
          uStack_1f4 = uStack_15c4;
          auStack_200 = (undefined1  [8])(uStack_15d0 & 0xffffffff);
          uVar24 = func_0x00222fd0(auStack_200);
          uVar8 = func_0x00222f00(auStack_1600,auStack_200);
          Get3DAngle__F7FVector(&uStack_15f0,uVar8);
          fStack_1f8 = (float)uVar24;
          auStack_200 = (undefined1  [8])uStack_15f0;
          uStack_1f4 = uStack_15e4;
          __pl__7FVectorCFRC7FVector(auStack_1620,iVar5 + 0x160,iVar5 + 0x3a0);
          __mi__7FVectorCFRC7FVector(auStack_1610,auStack_1620,auStack_300);
          fStack_1e8 = (float)uStack_1608;
          uStack_1e4 = uStack_1604;
          fStack_1ec = 0.0;
          fVar23 = (float)func_0x00222fd0(&fStack_1f0);
          uVar8 = func_0x00222f00(auStack_1640,&fStack_1f0);
          Get3DAngle__F7FVector(auStack_1630,uVar8);
          fStack_1f0 = (float)auStack_1630._0_8_;
          fStack_1ec = SUB84(auStack_1630._0_8_,4);
          uStack_1e4 = uStack_1624;
          fStack_1e8 = fVar23;
          __pl__7FVectorCFRC7FVector(auStack_1660,iVar15 + 0x160,iVar15 + 0x3a0);
          __mi__7FVectorCFRC7FVector(auStack_1650,auStack_1660,auStack_300);
          fStack_1d8 = (float)uStack_1648;
          uStack_1d4 = uStack_1644;
          fStack_1dc = 0.0;
          fVar23 = (float)func_0x00222fd0(&fStack_1e0);
          uVar8 = func_0x00222f00(auStack_1680,&fStack_1e0);
          Get3DAngle__F7FVector(auStack_1670,uVar8);
          fStack_1e0 = (float)auStack_1670._0_8_;
          fStack_1dc = SUB84(auStack_1670._0_8_,4);
          uStack_1d4 = uStack_1664;
          iVar12 = 0;
          iVar18 = 0;
          fStack_1d8 = fVar23;
          for (iVar13 = 0; iVar13 < 0xc; iVar13 = iVar13 + 1) {
            if (((((*(byte *)(iGpffff8610 + iVar13 * 0x510 + 0xb0) & 1) != 0) &&
                 ((long)((ulong)*(byte *)(iGpffff8610 + iVar13 * 0x510 + 0xb0) << 0x3e) < 0)) &&
                (-1 < (long)((ulong)*(byte *)(iGpffff8610 + iVar13 * 0x510 + 0xb2) << 0x3c))) &&
               ((iVar13 != *(int *)(iVar17 + 0xd0) && (iVar13 != *(int *)(iVar17 + 0xd4))))) {
              __pl__7FVectorCFRC7FVector
                        (auStack_16a0,iGpffff8610 + iVar13 * 0x510 + 0x160,
                         iGpffff8610 + iVar13 * 0x510 + 0x3a0);
              __mi__7FVectorCFRC7FVector(auStack_1690,auStack_16a0,auStack_310);
              fStack_1d0 = auStack_1690._0_4_;
              fStack_1cc = auStack_1690._4_4_;
              uStack_1c8 = uStack_1688;
              uStack_1c4 = uStack_1684;
              fVar23 = (float)func_0x00222fd0(&fStack_1d0);
              uVar8 = func_0x00222f00(auStack_16c0,&fStack_1d0);
              Get3DAngle__F7FVector(auStack_16b0,uVar8);
              fStack_1d0 = auStack_16b0._0_4_;
              fStack_1cc = auStack_16b0._4_4_;
              uStack_1c8 = uStack_16a8;
              uStack_1c4 = uStack_16a4;
              if (fVar23 < (float)uStack_208 + *(float *)(iVar5 + 0x354) + 10.0) {
                for (fVar22 = fStack_1cc - fStack_20c; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
                }
                for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
                }
                if ((-60.0 <= fVar22) && (fVar22 <= 60.0)) {
                  iVar12 = iVar12 + 1;
                }
              }
              if (fVar23 < fStack_1f8 + *(float *)(iVar15 + 0x354) + 10.0) {
                for (fVar23 = fStack_1cc - (float)auStack_200._4_4_; fVar23 < -180.0;
                    fVar23 = fVar23 + 360.0) {
                }
                for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
                }
                if ((-60.0 <= fVar23) && (fVar23 <= 60.0)) {
                  iVar12 = iVar12 + 1;
                }
              }
              __pl__7FVectorCFRC7FVector
                        (auStack_16e0,iGpffff8610 + iVar13 * 0x510 + 0x160,
                         iGpffff8610 + iVar13 * 0x510 + 0x3a0);
              __mi__7FVectorCFRC7FVector(auStack_16d0,auStack_16e0,auStack_300);
              fStack_1d0 = auStack_16d0._0_4_;
              fStack_1cc = auStack_16d0._4_4_;
              uStack_1c8 = uStack_16c8;
              uStack_1c4 = uStack_16c4;
              fVar23 = (float)func_0x00222fd0(&fStack_1d0);
              uVar8 = func_0x00222f00(auStack_1700,&fStack_1d0);
              Get3DAngle__F7FVector(auStack_16f0,uVar8);
              fStack_1d0 = auStack_16f0._0_4_;
              fStack_1cc = auStack_16f0._4_4_;
              uStack_1c8 = uStack_16e8;
              uStack_1c4 = uStack_16e4;
              if (fVar23 < fStack_1e8 + *(float *)(iVar5 + 0x354) + 10.0) {
                for (fVar22 = fStack_1cc - fStack_1ec; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
                }
                for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
                }
                if ((-60.0 <= fVar22) && (fVar22 <= 60.0)) {
                  iVar18 = iVar18 + 1;
                }
              }
              if (fVar23 < fStack_1d8 + *(float *)(iVar15 + 0x354) + 10.0) {
                for (fVar23 = fStack_1cc - fStack_1dc; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
                }
                for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
                }
                if ((-60.0 <= fVar23) && (fVar23 <= 60.0)) {
                  iVar18 = iVar18 + 1;
                }
              }
            }
          }
          if (iVar12 < iVar18) {
            *(int *)(iVar17 + 0x50) = auStack_310;
            *(int *)(iVar17 + 0x54) = auStack_310._4_4_;
            *(float *)(iVar17 + 0x58) = afStack_30c[1];
            *(float *)(iVar17 + 0x5c) = afStack_30c[2];
            *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0x3f | 0x40;
          }
          else if (iVar18 < iVar12) {
            *(int *)(iVar17 + 0x50) = auStack_300._0_4_;
            *(int *)(iVar17 + 0x54) = auStack_300._4_4_;
            *(undefined4 *)(iVar17 + 0x58) = auStack_300._8_4_;
            *(undefined4 *)(iVar17 + 0x5c) = auStack_300._12_4_;
            *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0x3f | 0x80;
          }
          else {
            fVar23 = (float)func_0x00222fd0(auStack_310);
            fVar22 = (float)func_0x00222fd0(auStack_300);
            if (fVar23 < fVar22) {
              *(int *)(iVar17 + 0x50) = auStack_310;
              *(int *)(iVar17 + 0x54) = auStack_310._4_4_;
              *(float *)(iVar17 + 0x58) = afStack_30c[1];
              *(float *)(iVar17 + 0x5c) = afStack_30c[2];
              *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0x3f | 0x40;
            }
            else {
              *(int *)(iVar17 + 0x50) = auStack_300._0_4_;
              *(int *)(iVar17 + 0x54) = auStack_300._4_4_;
              *(undefined4 *)(iVar17 + 0x58) = auStack_300._8_4_;
              *(undefined4 *)(iVar17 + 0x5c) = auStack_300._12_4_;
              *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0x3f | 0x80;
            }
          }
        }
        if (-10.0 < *(float *)(iVar17 + 0x54)) {
          *(undefined4 *)(iVar17 + 0x54) = 0xc1200000;
        }
      }
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    __pl__7FVectorCFRC7FVector(auStack_1960,iVar15 + 0x160,iVar15 + 0x3a0);
    uVar8 = FUN_004baab0(0,-*(float *)(iVar15 + 0x3b4),0,0x3f800000,auStack_1970);
    __pl__7FVectorCFRC7FVector(auStack_1950,auStack_1960,uVar8);
    __mi__7FVectorCFRC7FVector(&uStack_1940,auStack_1950,iVar17 + 0x50);
    uStack_208._0_4_ = (float)uStack_1938;
    _auStack_210 = uStack_1940;
    uStack_208._4_4_ = (float)uStack_1934;
    __pl__7FVectorCFRC7FVector(auStack_19a0,iVar15 + 0x160,iVar15 + 0x3a0);
    uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar15 + 0x3b4),0,0x3f800000,auStack_19b0);
    __pl__7FVectorCFRC7FVector(auStack_1990,auStack_19a0,uVar8);
    __mi__7FVectorCFRC7FVector(&uStack_1980,auStack_1990,iVar17 + 0x50);
    fStack_1f8 = (float)uStack_1978;
    auStack_200 = (undefined1  [8])uStack_1980;
    uStack_1f4 = uStack_1974;
    __pl__7FVectorCFRC7FVector(auStack_19e0,iVar5 + 0x160,iVar5 + 0x3a0);
    uVar8 = FUN_004baab0(0,-*(float *)(iVar5 + 0x3b4),0,0x3f800000,auStack_19f0);
    __pl__7FVectorCFRC7FVector(auStack_19d0,auStack_19e0,uVar8);
    __mi__7FVectorCFRC7FVector(auStack_19c0,auStack_19d0,iVar17 + 0x50);
    fStack_1f0 = auStack_19c0._0_4_;
    fStack_1ec = auStack_19c0._4_4_;
    fStack_1e8 = fStack_19b8;
    uStack_1e4 = uStack_19b4;
    if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3b) < 0) {
      __pl__7FVectorCFRC7FVector(auStack_1a60,iVar5 + 0x160,iVar5 + 0x3a0);
      uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar5 + 0x3b4),0,0x3f800000,auStack_1a70);
      __pl__7FVectorCFRC7FVector(auStack_1a50,auStack_1a60,uVar8);
      __mi__7FVectorCFRC7FVector(auStack_1a40,auStack_1a50,iVar17 + 0x50);
      fStack_1e0 = auStack_1a40._0_4_;
      fStack_1dc = auStack_1a40._4_4_;
      fStack_1d8 = fStack_1a38;
      uStack_1d4 = uStack_1a34;
    }
    else {
      __pl__7FVectorCFRC7FVector(auStack_1a20,iVar5 + 0x160,iVar5 + 0x3a0);
      uVar8 = FUN_004baab0(0,*(float *)(iVar5 + 0x3b4) * 0.5,0,0x3f800000,auStack_1a30);
      __pl__7FVectorCFRC7FVector(auStack_1a10,auStack_1a20,uVar8);
      __mi__7FVectorCFRC7FVector(auStack_1a00,auStack_1a10,iVar17 + 0x50);
      fStack_1e0 = auStack_1a00._0_4_;
      fStack_1dc = auStack_1a00._4_4_;
      fStack_1d8 = fStack_19f8;
      uStack_1d4 = uStack_19f4;
    }
    uVar8 = func_0x00222f00(auStack_1a90,auStack_210);
    Get3DAngle__F7FVector(auStack_1a80,uVar8);
    fStack_1d0 = auStack_1a80._0_4_;
    fStack_1cc = auStack_1a80._4_4_;
    uStack_1c8 = uStack_1a78;
    uStack_1c4 = uStack_1a74;
    uVar8 = func_0x00222f00(auStack_1ab0,auStack_200);
    Get3DAngle__F7FVector(auStack_1aa0,uVar8);
    afStack_1c0[0] = auStack_1aa0._0_4_;
    afStack_1c0[1] = auStack_1aa0._4_4_;
    afStack_1c0[2] = (float)uStack_1a98;
    afStack_1c0[3] = (float)uStack_1a94;
    uVar8 = func_0x00222f00(auStack_1ad0,&fStack_1f0);
    Get3DAngle__F7FVector(auStack_1ac0,uVar8);
    afStack_1c0[4] = auStack_1ac0._0_4_;
    afStack_1c0[5] = auStack_1ac0._4_4_;
    afStack_1c0[6] = (float)uStack_1ab8;
    afStack_1c0[7] = (float)uStack_1ab4;
    uVar8 = func_0x00222f00(auStack_1af0,&fStack_1e0);
    Get3DAngle__F7FVector(auStack_1ae0,uVar8);
    afStack_1c0[8] = (float)auStack_1ae0._0_4_;
    afStack_1c0[9] = (float)auStack_1ae0._4_4_;
    afStack_1c0[10] = (float)uStack_1ad8;
    afStack_1c0[0xb] = (float)uStack_1ad4;
    for (; fStack_1d0 < -180.0; fStack_1d0 = fStack_1d0 + 360.0) {
    }
    for (; 180.0 < fStack_1d0; fStack_1d0 = fStack_1d0 - 360.0) {
    }
    fVar23 = fStack_1d0;
    fVar22 = fStack_1d0;
    for (iVar5 = 5; iVar5 < 8; iVar5 = iVar5 + 1) {
      while (*(float *)(auStack_210 + iVar5 * 0x10) < -180.0) {
        *(float *)(auStack_210 + iVar5 * 0x10) = *(float *)(auStack_210 + iVar5 * 0x10) + 360.0;
      }
      while (180.0 < *(float *)(auStack_210 + iVar5 * 0x10)) {
        *(float *)(auStack_210 + iVar5 * 0x10) = *(float *)(auStack_210 + iVar5 * 0x10) - 360.0;
      }
      if (*(float *)(auStack_210 + iVar5 * 0x10) < fVar23) {
        fVar23 = *(float *)(auStack_210 + iVar5 * 0x10);
      }
      if (fVar22 < *(float *)(auStack_210 + iVar5 * 0x10)) {
        fVar22 = *(float *)(auStack_210 + iVar5 * 0x10);
      }
    }
    for (fVar22 = fVar22 - fVar23; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
    }
    for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
    }
    *(float *)(iVar17 + 0x60) = -(fVar23 + fVar22 / 2.0);
    while (*(float *)(iVar17 + 0x60) < -180.0) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 0x60)) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
    }
    for (fVar23 = fStack_1cc - afStack_1c0[5]; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
    }
    *(float *)(iVar17 + 100) = -(afStack_1c0[5] + fVar23 / 2.0);
    while (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    *(undefined4 *)(iVar17 + 0x68) = 0;
    break;
  case 0xc:
    iVar5 = iGpffff8610 + *(int *)(iVar17 + 0xd4) * 0x510;
    if (*(short *)(iVar17 + 0x1e) == 1) {
      if ((((*(byte *)(iVar17 + 0x1a) & 1) == 0) && (*(float *)(iVar17 + 0x24) != 0.0)) &&
         ((uVar2 & 0x8000) != 0)) {
        if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3b) < 0) {
          *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0xef;
          *(undefined4 *)(iVar17 + 0xe8) = 0xc1700000;
        }
        else {
          *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0xef | 0x10;
          *(undefined4 *)(iVar17 + 0xe8) = 0xc1f00000;
        }
        __pl__7FVectorCFRC7FVector(auStack_1b30,iVar5 + 0x160,iVar5 + 0x3a0);
        uVar8 = func_0x00222f00(auStack_1b50,auStack_210);
        Get3DAngle__F7FVector(&uStack_1b40,uVar8);
        fStack_1f8 = (float)uStack_1b38;
        auStack_200 = (undefined1  [8])uStack_1b40;
        uStack_1f4 = uStack_1b34;
        while ((float)auStack_200._4_4_ < -180.0) {
          auStack_200._4_4_ = (float)auStack_200._4_4_ + 360.0;
        }
        while (180.0 < (float)auStack_200._4_4_) {
          auStack_200._4_4_ = (float)auStack_200._4_4_ - 360.0;
        }
        *(float *)(iVar17 + 0xe4) = -(float)auStack_200._4_4_ - *(float *)(iVar5 + 0x184);
        while (*(float *)(iVar17 + 0xe4) < -180.0) {
          *(float *)(iVar17 + 0xe4) = *(float *)(iVar17 + 0xe4) + 360.0;
        }
        while (180.0 < *(float *)(iVar17 + 0xe4)) {
          *(float *)(iVar17 + 0xe4) = *(float *)(iVar17 + 0xe4) - 360.0;
        }
        *(byte *)(iVar17 + 0x18) = *(byte *)(iVar17 + 0x18) & 0x7f | 0x80;
      }
      fVar23 = 0.0;
      if ((*(byte *)(iVar17 + 0x1a) & 1) == 0) {
        fVar23 = ((float)bStack_44e / 60.0 - (float)bStack_44d / 60.0) *
                 *(float *)(iVar17 + 0x24) * 30.0;
      }
      for (unaff_f20 = fVar23 + *(float *)(iVar17 + 0xe4); unaff_f20 < -180.0;
          unaff_f20 = unaff_f20 + 360.0) {
      }
      for (; 180.0 < unaff_f20; unaff_f20 = unaff_f20 - 360.0) {
      }
      if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3b) < 0) {
        *(undefined4 *)(iVar17 + 0xe8) = 0xc1f00000;
        iVar15 = *(int *)(iVar17 + 0xd8);
        if (iVar15 == 2) {
          *(undefined4 *)(iVar17 + 0xec) = 0x42e60000;
        }
        else if (iVar15 == 1) {
          *(undefined4 *)(iVar17 + 0xec) = 0x42d20000;
        }
        else if (iVar15 == 0) {
          *(undefined4 *)(iVar17 + 0xec) = 0x42be0000;
        }
      }
      else {
        *(undefined4 *)(iVar17 + 0xe8) = 0xc1700000;
        iVar15 = *(int *)(iVar17 + 0xd8);
        if (iVar15 == 2) {
          *(undefined4 *)(iVar17 + 0xec) = 0x42b40000;
        }
        else if (iVar15 == 1) {
          *(undefined4 *)(iVar17 + 0xec) = 0x42a00000;
        }
        else if (iVar15 == 0) {
          *(undefined4 *)(iVar17 + 0xec) = 0x428c0000;
        }
      }
    }
    else if (*(short *)(iVar17 + 0x1e) == 0) {
      if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3b) < 0) {
        *(undefined4 *)(iVar17 + 0xe0) = 0;
        *(undefined4 *)(iVar17 + 0xe8) = 0xc1f00000;
        iVar15 = *(int *)(iVar17 + 0xd8);
        if (iVar15 == 2) {
          *(undefined4 *)(iVar17 + 0xec) = 0x42e60000;
        }
        else if (iVar15 == 1) {
          *(undefined4 *)(iVar17 + 0xec) = 0x42d20000;
        }
        else if (iVar15 == 0) {
          *(undefined4 *)(iVar17 + 0xec) = 0x42be0000;
        }
      }
      else {
        *(undefined4 *)(iVar17 + 0xe0) = 0;
        *(undefined4 *)(iVar17 + 0xe8) = 0xc1700000;
        iVar15 = *(int *)(iVar17 + 0xd8);
        if (iVar15 == 2) {
          *(undefined4 *)(iVar17 + 0xec) = 0x42b40000;
        }
        else if (iVar15 == 1) {
          *(undefined4 *)(iVar17 + 0xec) = 0x42a00000;
        }
        else if (iVar15 == 0) {
          *(undefined4 *)(iVar17 + 0xec) = 0x428c0000;
        }
      }
      __pl__7FVectorCFRC7FVector(auStack_1b00,iVar5 + 0x160,iVar5 + 0x3a0);
      uVar8 = func_0x00222f00(auStack_1b20,auStack_210);
      Get3DAngle__F7FVector(&uStack_1b10,uVar8);
      fStack_1f8 = (float)uStack_1b08;
      auStack_200 = (undefined1  [8])uStack_1b10;
      uStack_1f4 = uStack_1b04;
      while ((float)auStack_200._4_4_ < -180.0) {
        auStack_200._4_4_ = (float)auStack_200._4_4_ + 360.0;
      }
      while (180.0 < (float)auStack_200._4_4_) {
        auStack_200._4_4_ = (float)auStack_200._4_4_ - 360.0;
      }
      *(float *)(iVar17 + 0xe4) = -(float)auStack_200._4_4_ - *(float *)(iVar5 + 0x184);
      while (*(float *)(iVar17 + 0xe4) < -180.0) {
        *(float *)(iVar17 + 0xe4) = *(float *)(iVar17 + 0xe4) + 360.0;
      }
      while (180.0 < *(float *)(iVar17 + 0xe4)) {
        *(float *)(iVar17 + 0xe4) = *(float *)(iVar17 + 0xe4) - 360.0;
      }
      *(undefined2 *)(iVar17 + 0x1e) = 1;
      unaff_f20 = *(float *)(iVar17 + 0xe4);
    }
    for (fVar23 = *(float *)(iVar5 + 0x184) + unaff_f20; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 <= fVar23; fVar23 = fVar23 - 360.0) {
    }
    FUN_004baab0(*(undefined4 *)(iVar17 + 0xe8),fVar23,0,0x3f800000,auStack_1b60);
    *(int *)(iVar17 + 0x60) = auStack_1b60._0_4_;
    *(int *)(iVar17 + 100) = auStack_1b60._4_4_;
    *(undefined4 *)(iVar17 + 0x68) = uStack_1b58;
    *(undefined4 *)(iVar17 + 0x6c) = uStack_1b54;
    __pl__7FVectorCFRC7FVector(auStack_1b70,iVar5 + 0x160,iVar5 + 0x3a0);
    *(int *)(iVar17 + 0x70) = auStack_1b70._0_4_;
    *(int *)(iVar17 + 0x74) = auStack_1b70._4_4_;
    *(undefined4 *)(iVar17 + 0x78) = uStack_1b68;
    *(undefined4 *)(iVar17 + 0x7c) = uStack_1b64;
    *(undefined4 *)(iVar17 + 0x74) = 0;
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x60));
    func_0x00202890(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 100));
    func_0x00202938(uVar24,auStack_430,auStack_430);
    fVar23 = (float)func_0x00222fd0(iVar5 + 0x3b0);
    fVar23 = *(float *)(iVar5 + 0x354) + fVar23 + 30.0;
    if (*(float *)(iVar17 + 0xec) < fVar23) {
      *(float *)(iVar17 + 0xec) = fVar23;
    }
    *(float *)(iVar17 + 0x80) = (*(float *)(iVar17 + 0xec) * *(float *)(iVar17 + 0x84)) / 512.0;
    uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_1b90);
    func_0x00222df0(auStack_1b80,auStack_430,uVar8);
    *(int *)(iVar17 + 0x50) = auStack_1b80._0_4_;
    *(int *)(iVar17 + 0x54) = auStack_1b80._4_4_;
    *(undefined4 *)(iVar17 + 0x58) = uStack_1b78;
    *(undefined4 *)(iVar17 + 0x5c) = uStack_1b74;
    auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
    auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
    auVar25 = _vadd(auVar25,auVar26);
    auVar25 = _sqc2(auVar25);
    *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    bVar4 = false;
    for (fVar23 = *(float *)(iVar5 + 0x184) + *(float *)(iVar17 + 0xe4); fVar23 < -180.0;
        fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 <= fVar23; fVar23 = fVar23 - 360.0) {
    }
    if (*(float *)(iVar17 + 0x50) < -*(float *)(iGpffff8610 + 0x40b4) / 2.0 + 5.0) {
      if ((*(float *)(iVar17 + 100) < 50.0) || (130.0 < *(float *)(iVar17 + 100))) {
        bVar4 = true;
      }
      if ((fVar23 < 50.0) || (130.0 < fVar23)) {
        bVar4 = true;
      }
    }
    if (*(float *)(iGpffff8610 + 0x40b4) / 2.0 - 5.0 < *(float *)(iVar17 + 0x50)) {
      if ((-50.0 < *(float *)(iVar17 + 100)) || (*(float *)(iVar17 + 100) < -130.0)) {
        bVar4 = true;
      }
      if ((-50.0 < fVar23) || (fVar23 < -130.0)) {
        bVar4 = true;
      }
    }
    if (*(float *)(iVar17 + 0x58) < -*(float *)(iGpffff8610 + 0x40bc) / 2.0 + 5.0) {
      if ((*(float *)(iVar17 + 100) < -40.0) || (40.0 < *(float *)(iVar17 + 100))) {
        bVar4 = true;
      }
      if ((fVar23 < -40.0) || (40.0 < fVar23)) {
        bVar4 = true;
      }
    }
    if (*(float *)(iGpffff8610 + 0x40bc) / 2.0 - 5.0 < *(float *)(iVar17 + 0x58)) {
      if ((-140.0 < *(float *)(iVar17 + 100)) && (*(float *)(iVar17 + 100) < 140.0)) {
        bVar4 = true;
      }
      if ((-140.0 < fVar23) && (fVar23 < 140.0)) {
        bVar4 = true;
      }
    }
    if (bVar4) {
      FUN_004baab0(*(undefined4 *)(iVar17 + 0xe8),fVar23,0,0x3f800000,auStack_1ba0);
      *(int *)(iVar17 + 0x60) = auStack_1ba0._0_4_;
      *(int *)(iVar17 + 100) = auStack_1ba0._4_4_;
      *(undefined4 *)(iVar17 + 0x68) = uStack_1b98;
      *(undefined4 *)(iVar17 + 0x6c) = uStack_1b94;
      auVar25 = _vmr32(in_vf0);
      auVar26 = _vmr32(auVar25);
      auVar27 = _vmr32(auVar26);
      auStack_400 = _sqc2(in_vf0);
      auStack_410 = _sqc2(auVar25);
      auStack_420 = _sqc2(auVar26);
      auStack_430 = _sqc2(auVar27);
      uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x60));
      func_0x00202890(uVar24,auStack_430,auStack_430);
      uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 100));
      func_0x00202938(uVar24,auStack_430,auStack_430);
      *(float *)(iVar17 + 0x80) = (*(float *)(iVar17 + 0xec) * *(float *)(iVar17 + 0x84)) / 512.0;
      uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_1bc0);
      func_0x00222df0(auStack_1bb0,auStack_430,uVar8);
      *(int *)(iVar17 + 0x50) = auStack_1bb0._0_4_;
      *(int *)(iVar17 + 0x54) = auStack_1bb0._4_4_;
      *(undefined4 *)(iVar17 + 0x58) = uStack_1ba8;
      *(undefined4 *)(iVar17 + 0x5c) = uStack_1ba4;
      auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
      auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _vadd(auVar25,auVar26);
      auVar25 = _sqc2(auVar25);
      *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    }
    else {
      *(float *)(iVar17 + 0xe4) = unaff_f20;
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    __pl__7FVectorCFRC7FVector(auStack_1bf0,iVar5 + 0x160,iVar5 + 0x3a0);
    uVar8 = FUN_004baab0(0,-*(float *)(iVar5 + 0x3b4) - 5.0,0,0x3f800000,auStack_1c00);
    __pl__7FVectorCFRC7FVector(auStack_1be0,auStack_1bf0,uVar8);
    __mi__7FVectorCFRC7FVector(&uStack_1bd0,auStack_1be0,iVar17 + 0x50);
    uStack_208._0_4_ = (float)uStack_1bc8;
    _auStack_210 = uStack_1bd0;
    uStack_208._4_4_ = (float)uStack_1bc4;
    __mi__7FVectorCFRC7FVector(&uStack_1c10,iVar17 + 0x70,iVar17 + 0x50);
    fStack_1f8 = (float)uStack_1c08;
    auStack_200 = (undefined1  [8])uStack_1c10;
    uStack_1f4 = uStack_1c04;
    uVar8 = func_0x00222f00(auStack_1c30,auStack_210);
    Get3DAngle__F7FVector(auStack_1c20,uVar8);
    fStack_1f0 = auStack_1c20._0_4_;
    fStack_1ec = auStack_1c20._4_4_;
    fStack_1e8 = fStack_1c18;
    uStack_1e4 = uStack_1c14;
    uVar8 = func_0x00222f00(auStack_1c50,auStack_200);
    Get3DAngle__F7FVector(auStack_1c40,uVar8);
    fStack_1e0 = auStack_1c40._0_4_;
    fStack_1dc = auStack_1c40._4_4_;
    fStack_1d8 = fStack_1c38;
    uStack_1d4 = uStack_1c34;
    for (; fStack_1f0 < -180.0; fStack_1f0 = fStack_1f0 + 360.0) {
    }
    for (; 180.0 < fStack_1f0; fStack_1f0 = fStack_1f0 - 360.0) {
    }
    for (; fStack_1e0 < -180.0; fStack_1e0 = fStack_1e0 + 360.0) {
    }
    for (; 180.0 < fStack_1e0; fStack_1e0 = fStack_1e0 - 360.0) {
    }
    fVar23 = fStack_1e0;
    if (fStack_1f0 <= fStack_1e0) {
      fVar23 = fStack_1f0;
    }
    fVar22 = fStack_1e0;
    if (fStack_1e0 <= fStack_1f0) {
      fVar22 = fStack_1f0;
    }
    for (fVar22 = fVar22 - fVar23; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
    }
    for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
    }
    *(float *)(iVar17 + 0x60) = -(fVar23 + fVar22 / 2.0);
    while (*(float *)(iVar17 + 0x60) < -180.0) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 0x60)) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
    }
    for (; fStack_1ec < -180.0; fStack_1ec = fStack_1ec + 360.0) {
    }
    for (; 180.0 < fStack_1ec; fStack_1ec = fStack_1ec - 360.0) {
    }
    for (; fStack_1dc < -180.0; fStack_1dc = fStack_1dc + 360.0) {
    }
    for (; 180.0 < fStack_1dc; fStack_1dc = fStack_1dc - 360.0) {
    }
    fVar23 = fStack_1dc;
    if (fStack_1ec <= fStack_1dc) {
      fVar23 = fStack_1ec;
    }
    fVar22 = fStack_1dc;
    if (fStack_1dc <= fStack_1ec) {
      fVar22 = fStack_1ec;
    }
    for (fVar22 = fVar22 - fVar23; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
    }
    for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
    }
    *(float *)(iVar17 + 100) = -(fVar23 + fVar22 / 2.0);
    while (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    break;
  case 0xd:
    *(byte *)(iVar17 + 0x1a) = *(byte *)(iVar17 + 0x1a) & 0xfd;
    iVar5 = iGpffff8610 + *(int *)(iVar17 + 0xd0) * 0x510;
    iVar15 = iGpffff8610 + *(int *)(iVar17 + 0xd4) * 0x510;
    if ((((*(byte *)(iVar17 + 0x1a) & 1) == 0) && (*(float *)(iVar17 + 0x24) != 0.0)) &&
       ((uVar2 & 0x8000) != 0)) {
      if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3b) < 0) {
        *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0xef;
      }
      else {
        *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0xef | 0x10;
      }
      *(byte *)(iVar17 + 0x1a) = *(byte *)(iVar17 + 0x1a) & 0xfd | 2;
      *(byte *)(iVar17 + 0x18) = *(byte *)(iVar17 + 0x18) & 0x7f | 0x80;
    }
    if (*(short *)(iVar17 + 0x1e) == 0) {
      __pl__7FVectorCFRC7FVector(auStack_1c60,iVar5 + 0x160,iVar5 + 0x3a0);
      *(int *)(iVar17 + 0x100) = auStack_1c60._0_4_;
      *(int *)(iVar17 + 0x104) = auStack_1c60._4_4_;
      *(undefined4 *)(iVar17 + 0x108) = uStack_1c58;
      *(undefined4 *)(iVar17 + 0x10c) = uStack_1c54;
      __pl__7FVectorCFRC7FVector(auStack_1c70,iVar15 + 0x160,iVar15 + 0x3a0);
      *(int *)(iVar17 + 0x110) = auStack_1c70._0_4_;
      *(int *)(iVar17 + 0x114) = auStack_1c70._4_4_;
      *(undefined4 *)(iVar17 + 0x118) = uStack_1c68;
      *(undefined4 *)(iVar17 + 0x11c) = uStack_1c64;
      __mi__7FVectorCFRC7FVector(&uStack_1c80,iVar17 + 0x110,iVar17 + 0x100);
      uStack_208._0_4_ = (float)uStack_1c78;
      _auStack_210 = uStack_1c80;
      uStack_208._4_4_ = (float)uStack_1c74;
      _auStack_210 = uStack_1c80 & 0xffffffff;
      func_0x00222f20(auStack_210);
      _auStack_200 = _auStack_210;
      func_0x00223010(*(undefined4 *)(iVar5 + 0x354),auStack_200);
      auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x100));
      auVar25 = _lqc2(_auStack_200);
      auVar25 = _vadd(auVar25,auVar26);
      _auStack_200 = _sqc2(auVar25);
      fVar23 = 500.0;
      fVar22 = fVar23;
      if ((float)auStack_210 < 0.0) {
        fVar22 = (-*(float *)(iGpffff8610 + 0x40b4) / 2.0 - (float)auStack_200._0_4_) /
                 (float)auStack_210;
      }
      if (0.0 < (float)auStack_210) {
        fVar22 = (*(float *)(iGpffff8610 + 0x40b4) / 2.0 - (float)auStack_200._0_4_) /
                 (float)auStack_210;
      }
      if ((float)uStack_208 < 0.0) {
        fVar23 = (-*(float *)(iGpffff8610 + 0x40bc) / 2.0 - fStack_1f8) / (float)uStack_208;
      }
      if (0.0 < (float)uStack_208) {
        fVar23 = (*(float *)(iGpffff8610 + 0x40bc) / 2.0 - fStack_1f8) / (float)uStack_208;
      }
      if (fVar22 <= fVar23) {
        fVar23 = fVar22;
      }
      func_0x00223010(fVar23,auStack_210);
      __pl__7FVectorCFRC7FVector(auStack_1c90,auStack_210,auStack_200);
      *(int *)(iVar17 + 0x120) = auStack_1c90._0_4_;
      *(int *)(iVar17 + 0x124) = auStack_1c90._4_4_;
      *(undefined4 *)(iVar17 + 0x128) = uStack_1c88;
      *(undefined4 *)(iVar17 + 300) = uStack_1c84;
      *(undefined4 *)(iVar17 + 0x124) = *(undefined4 *)(iVar17 + 0x114);
      *(undefined2 *)(iVar17 + 0x1e) = 1;
      *(byte *)(iVar17 + 0x1a) = *(byte *)(iVar17 + 0x1a) & 0xfd | 2;
    }
    if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3b) < 0) {
      uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar5 + 0x3b4),0,0x3f800000,auStack_2040);
      __pl__7FVectorCFRC7FVector(&uStack_2030,iVar17 + 0x100,uVar8);
      fStack_1f8 = (float)uStack_2028;
      auStack_200 = (undefined1  [8])uStack_2030;
      uStack_1f4 = uStack_2024;
      uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar15 + 0x3b4),0,0x3f800000,auStack_2060);
      __pl__7FVectorCFRC7FVector(auStack_2050,iVar17 + 0x120,uVar8);
      fStack_1e0 = auStack_2050._0_4_;
      fStack_1dc = auStack_2050._4_4_;
      fStack_1d8 = fStack_2048;
      uStack_1d4 = uStack_2044;
      __pl__7FVectorCFRC7FVector(auStack_2070,auStack_200,&fStack_1e0);
      *(int *)(iVar17 + 0x70) = auStack_2070._0_4_;
      *(int *)(iVar17 + 0x74) = auStack_2070._4_4_;
      *(undefined4 *)(iVar17 + 0x78) = uStack_2068;
      *(undefined4 *)(iVar17 + 0x7c) = uStack_2064;
      func_0x00223030(0x40000000,iVar17 + 0x70);
      *(undefined4 *)(iVar17 + 0x74) = 0;
      __mi__7FVectorCFRC7FVector(&uStack_2080,iVar17 + 0x100,iVar17 + 0x120);
      uStack_208._0_4_ = (float)uStack_2078;
      _auStack_210 = uStack_2080;
      uStack_208._4_4_ = (float)uStack_2074;
      fVar22 = (float)func_0x00222fd0(auStack_210);
      fVar23 = *(float *)(iVar5 + 0x354);
      fVar20 = *(float *)(iVar15 + 0x354);
      *(undefined4 *)(iVar17 + 0x84) = 0x44000000;
      *(float *)(iVar17 + 0x80) =
           ((fVar20 + fVar23 + fVar22 + 10.0) * *(float *)(iVar17 + 0x84)) / 512.0;
      if ((long)((ulong)*(byte *)(iVar17 + 0x1a) << 0x3e) < 0) {
        uVar8 = func_0x00222f00(auStack_20a0,iVar17 + 0x70);
        Get3DAngle__F7FVector(&uStack_2090,uVar8);
        uStack_208._0_4_ = (float)uStack_2088;
        _auStack_210 = uStack_2090;
        uStack_208._4_4_ = (float)uStack_2084;
        *(float *)(iVar17 + 0xe0) = -(float)((ulong)uStack_2090 >> 0x20);
        while (*(float *)(iVar17 + 0xe0) < -180.0) {
          *(float *)(iVar17 + 0xe0) = *(float *)(iVar17 + 0xe0) + 360.0;
        }
        while (180.0 < *(float *)(iVar17 + 0xe0)) {
          *(float *)(iVar17 + 0xe0) = *(float *)(iVar17 + 0xe0) - 360.0;
        }
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(0xc1f00000);
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0xe0));
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_20c0);
        func_0x00222df0(auStack_20b0,auStack_430,uVar8);
        *(int *)(iVar17 + 0x50) = auStack_20b0._0_4_;
        *(int *)(iVar17 + 0x54) = auStack_20b0._4_4_;
        *(undefined4 *)(iVar17 + 0x58) = uStack_20a8;
        *(undefined4 *)(iVar17 + 0x5c) = uStack_20a4;
        auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
        auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
        auVar25 = _vadd(auVar25,auVar26);
        auVar25 = _sqc2(auVar25);
        *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
      }
      else {
        fVar23 = 0.0;
        if ((*(byte *)(iVar17 + 0x1a) & 1) == 0) {
          fVar23 = ((float)bStack_44e / 60.0 - (float)bStack_44d / 60.0) *
                   *(float *)(iVar17 + 0x24) * 30.0;
        }
        for (fVar23 = fVar23 + *(float *)(iVar17 + 0xe0); fVar23 < -180.0; fVar23 = fVar23 + 360.0)
        {
        }
        for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
        }
        for (; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
        }
        for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
        }
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(0xc1f00000);
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(fVar23);
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_20e0);
        func_0x00222df0(auStack_20d0,auStack_430,uVar8);
        *(int *)(iVar17 + 0x50) = auStack_20d0._0_4_;
        *(int *)(iVar17 + 0x54) = auStack_20d0._4_4_;
        *(undefined4 *)(iVar17 + 0x58) = uStack_20c8;
        *(undefined4 *)(iVar17 + 0x5c) = uStack_20c4;
        auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
        auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
        auVar25 = _vadd(auVar25,auVar26);
        auVar25 = _sqc2(auVar25);
        *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
        bVar4 = false;
        fVar22 = *(float *)(iVar17 + 0xe0);
        if (*(float *)(iVar17 + 0x50) < -*(float *)(iGpffff8610 + 0x40b4) / 2.0 + 5.0) {
          if ((fVar23 < 50.0) || (130.0 < fVar23)) {
            bVar4 = true;
          }
          if ((fVar22 < 50.0) || (130.0 < fVar22)) {
            bVar4 = true;
          }
        }
        if (*(float *)(iGpffff8610 + 0x40b4) / 2.0 - 5.0 < *(float *)(iVar17 + 0x50)) {
          if ((-50.0 < fVar23) || (fVar23 < -130.0)) {
            bVar4 = true;
          }
          if ((-50.0 < fVar22) || (fVar22 < -130.0)) {
            bVar4 = true;
          }
        }
        if (*(float *)(iVar17 + 0x58) < -*(float *)(iGpffff8610 + 0x40bc) / 2.0 + 5.0) {
          if ((fVar23 < -40.0) || (40.0 < fVar23)) {
            bVar4 = true;
          }
          if ((fVar22 < -40.0) || (40.0 < fVar22)) {
            bVar4 = true;
          }
        }
        if (*(float *)(iGpffff8610 + 0x40bc) / 2.0 - 5.0 < *(float *)(iVar17 + 0x58)) {
          if ((-140.0 < fVar23) && (fVar23 < 140.0)) {
            bVar4 = true;
          }
          if ((-140.0 < fVar22) && (fVar22 < 140.0)) {
            bVar4 = true;
          }
        }
        if (bVar4) {
          auVar25 = _vmr32(in_vf0);
          auVar26 = _vmr32(auVar25);
          auVar27 = _vmr32(auVar26);
          auStack_400 = _sqc2(in_vf0);
          auStack_410 = _sqc2(auVar25);
          auStack_420 = _sqc2(auVar26);
          auStack_430 = _sqc2(auVar27);
          uVar24 = func_0x00222e40(0xc1f00000);
          func_0x00202890(uVar24,auStack_430,auStack_430);
          uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0xe0));
          func_0x00202938(uVar24,auStack_430,auStack_430);
          uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_2100);
          func_0x00222df0(auStack_20f0,auStack_430,uVar8);
          *(int *)(iVar17 + 0x50) = auStack_20f0._0_4_;
          *(int *)(iVar17 + 0x54) = auStack_20f0._4_4_;
          *(undefined4 *)(iVar17 + 0x58) = uStack_20e8;
          *(undefined4 *)(iVar17 + 0x5c) = uStack_20e4;
          auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
          auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
          auVar25 = _vadd(auVar25,auVar26);
          auVar25 = _sqc2(auVar25);
          *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
        }
        else {
          *(float *)(iVar17 + 0xe0) = fVar23;
        }
      }
    }
    else {
      __mi__7FVectorCFRC7FVector(auStack_1ca0,iVar17 + 0x120,iVar17 + 0x100);
      FUN_004baab0(*(undefined4 *)(iGpffff8610 + 0x40b4),0,*(undefined4 *)(iGpffff8610 + 0x40bc),
                   0x3f800000,auStack_1cb0);
      fVar23 = (float)func_0x00222fd0(auStack_210);
      fVar22 = (float)func_0x00222fd0(auStack_200);
      *(float *)(iVar17 + 0x84) = (fVar23 / (fVar22 * 0.75) + 1.2) * 512.0;
      __mi__7FVectorCFRC7FVector(&uStack_1cc0,iVar17 + 0x120,iVar17 + 0x100);
      uStack_208._0_4_ = (float)uStack_1cb8;
      _auStack_210 = uStack_1cc0;
      uStack_208._4_4_ = (float)uStack_1cb4;
      uVar8 = func_0x00222f00(auStack_1ce0,auStack_210);
      Get3DAngle__F7FVector(&uStack_1cd0,uVar8);
      fStack_1f8 = (float)uStack_1cc8;
      auStack_200 = (undefined1  [8])uStack_1cd0;
      uStack_1f4 = uStack_1cc4;
      auVar25 = _vmr32(in_vf0);
      auVar26 = _vmr32(auVar25);
      auVar27 = _vmr32(auVar26);
      auStack_400 = _sqc2(in_vf0);
      auStack_410 = _sqc2(auVar25);
      auStack_420 = _sqc2(auVar26);
      auStack_430 = _sqc2(auVar27);
      uVar24 = func_0x00222e40(-(float)((ulong)uStack_1cd0 >> 0x20));
      func_0x00202938(uVar24,auStack_430,auStack_430);
      uVar8 = FUN_004baab0(*(float *)(iVar5 + 0x354) * 2.0,0,0,0x3f800000,auStack_1d00);
      func_0x00222df0(auStack_1cf0,auStack_430,uVar8);
      fStack_1f0 = auStack_1cf0._0_4_;
      fStack_1ec = auStack_1cf0._4_4_;
      fStack_1e8 = fStack_1ce8;
      uStack_1e4 = uStack_1ce4;
      uVar8 = FUN_004baab0(-*(float *)(iVar5 + 0x354) * 2.0,0,0,0x3f800000,auStack_1d20);
      func_0x00222df0(auStack_1d10,auStack_430,uVar8);
      fStack_1e0 = auStack_1d10._0_4_;
      fStack_1dc = auStack_1d10._4_4_;
      fStack_1d8 = fStack_1d08;
      uStack_1d4 = uStack_1d04;
      bVar3 = *(byte *)(iVar17 + 0x19) >> 6;
      if (bVar3 == 2) {
        __pl__7FVectorCFRC7FVector(&uStack_1fc0,iVar17 + 0x100,&fStack_1e0);
        uStack_208._0_4_ = (float)uStack_1fb8;
        _auStack_210 = uStack_1fc0;
        uStack_208._4_4_ = (float)uStack_1fb4;
        __mi__7FVectorCFRC7FVector(auStack_1fd0,iVar17 + 0x120,auStack_210);
        uVar8 = func_0x00222f00(auStack_1ff0,auStack_200);
        Get3DAngle__F7FVector(&uStack_1fe0,uVar8);
        fStack_1f8 = (float)uStack_1fd8;
        auStack_200 = (undefined1  [8])uStack_1fe0;
        uStack_1f4 = uStack_1fd4;
        fVar23 = -(float)uStack_1fe0;
        if ((fVar23 <= 40.0) && (fVar23 = fVar23 * 1.25 - 10.0, fVar23 < -10.0)) {
          fVar23 = -10.0;
        }
        fVar20 = (float)func_0x00222fd0(iVar5 + 0x3b0);
        fVar22 = *(float *)(iVar5 + 0x354);
        fVar21 = *(float *)(iVar17 + 0x84);
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(fVar23);
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-((fVar21 * (fVar22 + fVar20 + 30.0)) / 512.0),0x3f800000,
                             auStack_2010);
        func_0x00222df0(&uStack_2000,auStack_430,uVar8);
        fStack_1f8 = (float)uStack_1ff8;
        auStack_200 = (undefined1  [8])uStack_2000;
        uStack_1f4 = uStack_1ff4;
        __pl__7FVectorCFRC7FVector(&uStack_2020,auStack_210,auStack_200);
        auStack_300._8_4_ = uStack_2018;
        auStack_300._0_8_ = uStack_2020;
        auStack_300._12_4_ = uStack_2014;
        *(int *)(iVar17 + 0x50) = (int)uStack_2020;
        *(int *)(iVar17 + 0x54) = (int)((ulong)uStack_2020 >> 0x20);
        *(undefined4 *)(iVar17 + 0x58) = uStack_2018;
        *(undefined4 *)(iVar17 + 0x5c) = uStack_2014;
      }
      else if (bVar3 == 1) {
        __pl__7FVectorCFRC7FVector(&uStack_1f50,iVar17 + 0x100,&fStack_1f0);
        uStack_208._0_4_ = (float)uStack_1f48;
        _auStack_210 = uStack_1f50;
        uStack_208._4_4_ = (float)uStack_1f44;
        __mi__7FVectorCFRC7FVector(auStack_1f60,iVar17 + 0x120,auStack_210);
        uVar8 = func_0x00222f00(auStack_1f80,auStack_200);
        Get3DAngle__F7FVector(&uStack_1f70,uVar8);
        fStack_1f8 = (float)uStack_1f68;
        auStack_200 = (undefined1  [8])uStack_1f70;
        uStack_1f4 = uStack_1f64;
        fVar23 = -(float)uStack_1f70;
        if ((fVar23 <= 40.0) && (fVar23 = fVar23 * 1.25 - 10.0, fVar23 < -10.0)) {
          fVar23 = -10.0;
        }
        fVar20 = (float)func_0x00222fd0(iVar5 + 0x3b0);
        fVar22 = *(float *)(iVar5 + 0x354);
        fVar21 = *(float *)(iVar17 + 0x84);
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(fVar23);
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-((fVar21 * (fVar22 + fVar20 + 30.0)) / 512.0),0x3f800000,
                             auStack_1fa0);
        func_0x00222df0(&uStack_1f90,auStack_430,uVar8);
        fStack_1f8 = (float)uStack_1f88;
        auStack_200 = (undefined1  [8])uStack_1f90;
        uStack_1f4 = uStack_1f84;
        __pl__7FVectorCFRC7FVector(&uStack_1fb0,auStack_210,auStack_200);
        afStack_30c[1] = (float)uStack_1fa8;
        _auStack_310 = uStack_1fb0;
        afStack_30c[2] = (float)uStack_1fa4;
        *(int *)(iVar17 + 0x50) = (int)uStack_1fb0;
        *(int *)(iVar17 + 0x54) = (int)((ulong)uStack_1fb0 >> 0x20);
        *(undefined4 *)(iVar17 + 0x58) = uStack_1fa8;
        *(undefined4 *)(iVar17 + 0x5c) = uStack_1fa4;
      }
      else if (bVar3 == 0) {
        __pl__7FVectorCFRC7FVector(auStack_1d30,iVar17 + 0x100,&fStack_1f0);
        __mi__7FVectorCFRC7FVector(auStack_1d40,iVar17 + 0x120,auStack_210);
        uVar8 = func_0x00222f00(auStack_1d60,auStack_200);
        Get3DAngle__F7FVector(&uStack_1d50,uVar8);
        fStack_1f8 = (float)uStack_1d48;
        auStack_200 = (undefined1  [8])uStack_1d50;
        uStack_1f4 = uStack_1d44;
        fVar23 = -(float)uStack_1d50;
        if ((fVar23 <= 40.0) && (fVar23 = fVar23 * 1.25 - 10.0, fVar23 < -10.0)) {
          fVar23 = -10.0;
        }
        fVar20 = (float)func_0x00222fd0(iVar5 + 0x3b0);
        fVar22 = *(float *)(iVar5 + 0x354);
        fVar21 = *(float *)(iVar17 + 0x84);
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(fVar23);
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-((fVar21 * (fVar22 + fVar20 + 30.0)) / 512.0),0x3f800000,
                             auStack_1d80);
        func_0x00222df0(auStack_1d70,auStack_430,uVar8);
        __pl__7FVectorCFRC7FVector(&uStack_1d90,auStack_210,auStack_200);
        afStack_30c[1] = (float)uStack_1d88;
        _auStack_310 = uStack_1d90;
        afStack_30c[2] = (float)uStack_1d84;
        __pl__7FVectorCFRC7FVector(auStack_1da0,iVar17 + 0x100,&fStack_1e0);
        __mi__7FVectorCFRC7FVector(auStack_1db0,iVar17 + 0x120,auStack_210);
        uVar8 = func_0x00222f00(auStack_1dd0,auStack_200);
        Get3DAngle__F7FVector(&uStack_1dc0,uVar8);
        fStack_1f8 = (float)uStack_1db8;
        auStack_200 = (undefined1  [8])uStack_1dc0;
        uStack_1f4 = uStack_1db4;
        fVar23 = -(float)uStack_1dc0;
        if ((fVar23 <= 40.0) && (fVar23 = fVar23 * 1.25 - 10.0, fVar23 < -10.0)) {
          fVar23 = -10.0;
        }
        fVar20 = (float)func_0x00222fd0(iVar5 + 0x3b0);
        fVar22 = *(float *)(iVar5 + 0x354);
        fVar21 = *(float *)(iVar17 + 0x84);
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(fVar23);
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-((fVar21 * (fVar22 + fVar20 + 30.0)) / 512.0),0x3f800000,
                             auStack_1df0);
        func_0x00222df0(auStack_1de0,auStack_430,uVar8);
        __pl__7FVectorCFRC7FVector(&uStack_1e00,auStack_210,auStack_200);
        auStack_300._8_4_ = uStack_1df8;
        auStack_300._0_8_ = uStack_1e00;
        auStack_300._12_4_ = uStack_1df4;
        __mi__7FVectorCFRC7FVector(auStack_1e10,iVar17 + 0x100,auStack_310);
        uVar24 = func_0x00222fd0(auStack_210);
        uVar8 = func_0x00222f00(auStack_1e30,auStack_210);
        Get3DAngle__F7FVector(&uStack_1e20,uVar8);
        uStack_208._0_4_ = (float)uVar24;
        _auStack_210 = uStack_1e20;
        uStack_208._4_4_ = (float)uStack_1e14;
        __mi__7FVectorCFRC7FVector(&uStack_1e40,iVar17 + 0x120,auStack_310);
        fStack_1f8 = (float)uStack_1e38;
        auStack_200 = (undefined1  [8])uStack_1e40;
        uStack_1f4 = uStack_1e34;
        auStack_200 = (undefined1  [8])(uStack_1e40 & 0xffffffff);
        uVar24 = func_0x00222fd0(auStack_200);
        uVar8 = func_0x00222f00(auStack_1e60,auStack_200);
        Get3DAngle__F7FVector(&uStack_1e50,uVar8);
        fStack_1f8 = (float)uVar24;
        auStack_200 = (undefined1  [8])uStack_1e50;
        uStack_1f4 = uStack_1e44;
        __mi__7FVectorCFRC7FVector(auStack_1e70,iVar17 + 0x100,auStack_300);
        fStack_1e8 = (float)uStack_1e68;
        uStack_1e4 = uStack_1e64;
        fStack_1ec = 0.0;
        fVar23 = (float)func_0x00222fd0(&fStack_1f0);
        uVar8 = func_0x00222f00(auStack_1e90,&fStack_1f0);
        Get3DAngle__F7FVector(auStack_1e80,uVar8);
        fStack_1f0 = (float)auStack_1e80._0_8_;
        fStack_1ec = SUB84(auStack_1e80._0_8_,4);
        uStack_1e4 = uStack_1e74;
        fStack_1e8 = fVar23;
        __mi__7FVectorCFRC7FVector(auStack_1ea0,iVar17 + 0x120,auStack_300);
        fStack_1d8 = (float)uStack_1e98;
        uStack_1d4 = uStack_1e94;
        fStack_1dc = 0.0;
        fVar23 = (float)func_0x00222fd0(&fStack_1e0);
        uVar8 = func_0x00222f00(auStack_1ec0,&fStack_1e0);
        Get3DAngle__F7FVector(auStack_1eb0,uVar8);
        fStack_1e0 = (float)auStack_1eb0._0_8_;
        fStack_1dc = SUB84(auStack_1eb0._0_8_,4);
        uStack_1d4 = uStack_1ea4;
        iVar12 = 0;
        iVar18 = 0;
        fStack_1d8 = fVar23;
        for (iVar13 = 0; iVar13 < 0xc; iVar13 = iVar13 + 1) {
          if (((((*(byte *)(iGpffff8610 + iVar13 * 0x510 + 0xb0) & 1) != 0) &&
               ((long)((ulong)*(byte *)(iGpffff8610 + iVar13 * 0x510 + 0xb0) << 0x3e) < 0)) &&
              (-1 < (long)((ulong)*(byte *)(iGpffff8610 + iVar13 * 0x510 + 0xb2) << 0x3c))) &&
             ((iVar13 != *(int *)(iVar17 + 0xd0) && (iVar13 != *(int *)(iVar17 + 0xd4))))) {
            __pl__7FVectorCFRC7FVector
                      (auStack_1ee0,iGpffff8610 + iVar13 * 0x510 + 0x160,
                       iGpffff8610 + iVar13 * 0x510 + 0x3a0);
            __mi__7FVectorCFRC7FVector(auStack_1ed0,auStack_1ee0,auStack_310);
            fStack_1d0 = auStack_1ed0._0_4_;
            fStack_1cc = auStack_1ed0._4_4_;
            uStack_1c8 = uStack_1ec8;
            uStack_1c4 = uStack_1ec4;
            fVar23 = (float)func_0x00222fd0(&fStack_1d0);
            uVar8 = func_0x00222f00(auStack_1f00,&fStack_1d0);
            Get3DAngle__F7FVector(auStack_1ef0,uVar8);
            fStack_1d0 = auStack_1ef0._0_4_;
            fStack_1cc = auStack_1ef0._4_4_;
            uStack_1c8 = uStack_1ee8;
            uStack_1c4 = uStack_1ee4;
            if (fVar23 < (float)uStack_208 + *(float *)(iVar5 + 0x354) + 10.0) {
              for (fVar22 = fStack_1cc - fStack_20c; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
              }
              for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
              }
              if ((-60.0 <= fVar22) && (fVar22 <= 60.0)) {
                iVar12 = iVar12 + 1;
              }
            }
            if (fVar23 < fStack_1f8 + *(float *)(iVar15 + 0x354) + 10.0) {
              for (fVar23 = fStack_1cc - (float)auStack_200._4_4_; fVar23 < -180.0;
                  fVar23 = fVar23 + 360.0) {
              }
              for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
              }
              if ((-60.0 <= fVar23) && (fVar23 <= 60.0)) {
                iVar12 = iVar12 + 1;
              }
            }
            __pl__7FVectorCFRC7FVector
                      (auStack_1f20,iGpffff8610 + iVar13 * 0x510 + 0x160,
                       iGpffff8610 + iVar13 * 0x510 + 0x3a0);
            __mi__7FVectorCFRC7FVector(auStack_1f10,auStack_1f20,auStack_300);
            fStack_1d0 = auStack_1f10._0_4_;
            fStack_1cc = auStack_1f10._4_4_;
            uStack_1c8 = uStack_1f08;
            uStack_1c4 = uStack_1f04;
            fVar23 = (float)func_0x00222fd0(&fStack_1d0);
            uVar8 = func_0x00222f00(auStack_1f40,&fStack_1d0);
            Get3DAngle__F7FVector(auStack_1f30,uVar8);
            fStack_1d0 = auStack_1f30._0_4_;
            fStack_1cc = auStack_1f30._4_4_;
            uStack_1c8 = uStack_1f28;
            uStack_1c4 = uStack_1f24;
            if (fVar23 < fStack_1e8 + *(float *)(iVar5 + 0x354) + 10.0) {
              for (fVar22 = fStack_1cc - fStack_1ec; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
              }
              for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
              }
              if ((-60.0 <= fVar22) && (fVar22 <= 60.0)) {
                iVar18 = iVar18 + 1;
              }
            }
            if (fVar23 < fStack_1d8 + *(float *)(iVar15 + 0x354) + 10.0) {
              for (fVar23 = fStack_1cc - fStack_1dc; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
              }
              for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
              }
              if ((-60.0 <= fVar23) && (fVar23 <= 60.0)) {
                iVar18 = iVar18 + 1;
              }
            }
          }
        }
        if (iVar12 < iVar18) {
          *(int *)(iVar17 + 0x50) = auStack_310;
          *(int *)(iVar17 + 0x54) = auStack_310._4_4_;
          *(float *)(iVar17 + 0x58) = afStack_30c[1];
          *(float *)(iVar17 + 0x5c) = afStack_30c[2];
          *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0x3f | 0x40;
        }
        else if (iVar18 < iVar12) {
          *(int *)(iVar17 + 0x50) = auStack_300._0_4_;
          *(int *)(iVar17 + 0x54) = auStack_300._4_4_;
          *(undefined4 *)(iVar17 + 0x58) = auStack_300._8_4_;
          *(undefined4 *)(iVar17 + 0x5c) = auStack_300._12_4_;
          *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0x3f | 0x80;
        }
        else {
          fVar23 = (float)func_0x00222fd0(auStack_310);
          fVar22 = (float)func_0x00222fd0(auStack_300);
          if (fVar23 < fVar22) {
            *(int *)(iVar17 + 0x50) = auStack_310;
            *(int *)(iVar17 + 0x54) = auStack_310._4_4_;
            *(float *)(iVar17 + 0x58) = afStack_30c[1];
            *(float *)(iVar17 + 0x5c) = afStack_30c[2];
            *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0x3f | 0x40;
          }
          else {
            *(int *)(iVar17 + 0x50) = auStack_300._0_4_;
            *(int *)(iVar17 + 0x54) = auStack_300._4_4_;
            *(undefined4 *)(iVar17 + 0x58) = auStack_300._8_4_;
            *(undefined4 *)(iVar17 + 0x5c) = auStack_300._12_4_;
            *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0x3f | 0x80;
          }
        }
      }
      if (-10.0 < *(float *)(iVar17 + 0x54)) {
        *(undefined4 *)(iVar17 + 0x54) = 0xc1200000;
      }
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    uVar8 = FUN_004baab0(0,-*(float *)(iVar15 + 0x3b4),0,0x3f800000,auStack_2130);
    __pl__7FVectorCFRC7FVector(auStack_2120,iVar17 + 0x120,uVar8);
    __mi__7FVectorCFRC7FVector(&uStack_2110,auStack_2120,iVar17 + 0x50);
    uStack_208._0_4_ = (float)uStack_2108;
    _auStack_210 = uStack_2110;
    uStack_208._4_4_ = (float)uStack_2104;
    uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar15 + 0x3b4),0,0x3f800000,auStack_2160);
    __pl__7FVectorCFRC7FVector(auStack_2150,iVar17 + 0x120,uVar8);
    __mi__7FVectorCFRC7FVector(&uStack_2140,auStack_2150,iVar17 + 0x50);
    fStack_1f8 = (float)uStack_2138;
    auStack_200 = (undefined1  [8])uStack_2140;
    uStack_1f4 = uStack_2134;
    uVar8 = FUN_004baab0(0,-*(float *)(iVar5 + 0x3b4),0,0x3f800000,auStack_2190);
    __pl__7FVectorCFRC7FVector(auStack_2180,iVar17 + 0x100,uVar8);
    __mi__7FVectorCFRC7FVector(auStack_2170,auStack_2180,iVar17 + 0x50);
    fStack_1f0 = auStack_2170._0_4_;
    fStack_1ec = auStack_2170._4_4_;
    fStack_1e8 = fStack_2168;
    uStack_1e4 = uStack_2164;
    if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3b) < 0) {
      uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar5 + 0x3b4),0,0x3f800000,auStack_21f0);
      __pl__7FVectorCFRC7FVector(auStack_21e0,iVar17 + 0x100,uVar8);
      __mi__7FVectorCFRC7FVector(auStack_21d0,auStack_21e0,iVar17 + 0x50);
      fStack_1e0 = auStack_21d0._0_4_;
      fStack_1dc = auStack_21d0._4_4_;
      fStack_1d8 = fStack_21c8;
      uStack_1d4 = uStack_21c4;
    }
    else {
      uVar8 = FUN_004baab0(0,*(float *)(iVar5 + 0x3b4) * 0.5,0,0x3f800000,auStack_21c0);
      __pl__7FVectorCFRC7FVector(auStack_21b0,iVar17 + 0x100,uVar8);
      __mi__7FVectorCFRC7FVector(auStack_21a0,auStack_21b0,iVar17 + 0x50);
      fStack_1e0 = auStack_21a0._0_4_;
      fStack_1dc = auStack_21a0._4_4_;
      fStack_1d8 = fStack_2198;
      uStack_1d4 = uStack_2194;
    }
    uVar8 = func_0x00222f00(auStack_2210,auStack_210);
    Get3DAngle__F7FVector(auStack_2200,uVar8);
    fStack_1d0 = auStack_2200._0_4_;
    fStack_1cc = auStack_2200._4_4_;
    uStack_1c8 = uStack_21f8;
    uStack_1c4 = uStack_21f4;
    uVar8 = func_0x00222f00(auStack_2230,auStack_200);
    Get3DAngle__F7FVector(auStack_2220,uVar8);
    afStack_1c0[0] = auStack_2220._0_4_;
    afStack_1c0[1] = auStack_2220._4_4_;
    afStack_1c0[2] = (float)uStack_2218;
    afStack_1c0[3] = (float)uStack_2214;
    uVar8 = func_0x00222f00(auStack_2250,&fStack_1f0);
    Get3DAngle__F7FVector(auStack_2240,uVar8);
    afStack_1c0[4] = auStack_2240._0_4_;
    afStack_1c0[5] = auStack_2240._4_4_;
    afStack_1c0[6] = (float)uStack_2238;
    afStack_1c0[7] = (float)uStack_2234;
    uVar8 = func_0x00222f00(auStack_2270,&fStack_1e0);
    Get3DAngle__F7FVector(auStack_2260,uVar8);
    afStack_1c0[8] = (float)auStack_2260._0_4_;
    afStack_1c0[9] = (float)auStack_2260._4_4_;
    afStack_1c0[10] = (float)uStack_2258;
    afStack_1c0[0xb] = (float)uStack_2254;
    for (; fStack_1d0 < -180.0; fStack_1d0 = fStack_1d0 + 360.0) {
    }
    for (; 180.0 < fStack_1d0; fStack_1d0 = fStack_1d0 - 360.0) {
    }
    fVar23 = fStack_1d0;
    fVar22 = fStack_1d0;
    for (iVar5 = 5; iVar5 < 8; iVar5 = iVar5 + 1) {
      while (*(float *)(auStack_210 + iVar5 * 0x10) < -180.0) {
        *(float *)(auStack_210 + iVar5 * 0x10) = *(float *)(auStack_210 + iVar5 * 0x10) + 360.0;
      }
      while (180.0 < *(float *)(auStack_210 + iVar5 * 0x10)) {
        *(float *)(auStack_210 + iVar5 * 0x10) = *(float *)(auStack_210 + iVar5 * 0x10) - 360.0;
      }
      if (*(float *)(auStack_210 + iVar5 * 0x10) < fVar23) {
        fVar23 = *(float *)(auStack_210 + iVar5 * 0x10);
      }
      if (fVar22 < *(float *)(auStack_210 + iVar5 * 0x10)) {
        fVar22 = *(float *)(auStack_210 + iVar5 * 0x10);
      }
    }
    for (fVar22 = fVar22 - fVar23; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
    }
    for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
    }
    *(float *)(iVar17 + 0x60) = -(fVar23 + fVar22 / 2.0);
    while (*(float *)(iVar17 + 0x60) < -180.0) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 0x60)) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
    }
    for (fVar23 = fStack_1cc - afStack_1c0[5]; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
    }
    *(float *)(iVar17 + 100) = -(afStack_1c0[5] + fVar23 / 2.0);
    while (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    *(undefined4 *)(iVar17 + 0x68) = 0;
    break;
  case 0xe:
    *(byte *)(iVar17 + 0x1a) = *(byte *)(iVar17 + 0x1a) & 0xfd;
    iVar5 = iGpffff8610 + *(int *)(iVar17 + 0xd0) * 0x510;
    iVar15 = iGpffff8610 + *(int *)(iVar17 + 0xd4) * 0x510;
    if ((((*(byte *)(iVar17 + 0x1a) & 1) == 0) && (*(float *)(iVar17 + 0x24) != 0.0)) &&
       ((uVar2 & 0x8000) != 0)) {
      if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3b) < 0) {
        *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0xef;
      }
      else {
        *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0xef | 0x10;
      }
      *(undefined4 *)(iVar17 + 0xe0) = 0;
      *(byte *)(iVar17 + 0x1a) = *(byte *)(iVar17 + 0x1a) & 0xfd | 2;
      *(byte *)(iVar17 + 0x18) = *(byte *)(iVar17 + 0x18) & 0x7f | 0x80;
    }
    if (*(short *)(iVar17 + 0x1e) == 0) {
      __pl__7FVectorCFRC7FVector(auStack_2280,iVar5 + 0x160,iVar5 + 0x3a0);
      *(int *)(iVar17 + 0x100) = auStack_2280._0_4_;
      *(int *)(iVar17 + 0x104) = auStack_2280._4_4_;
      *(undefined4 *)(iVar17 + 0x108) = uStack_2278;
      *(undefined4 *)(iVar17 + 0x10c) = uStack_2274;
      __pl__7FVectorCFRC7FVector(auStack_2290,iVar15 + 0x160,iVar15 + 0x3a0);
      *(int *)(iVar17 + 0x110) = auStack_2290._0_4_;
      *(int *)(iVar17 + 0x114) = auStack_2290._4_4_;
      *(undefined4 *)(iVar17 + 0x118) = uStack_2288;
      *(undefined4 *)(iVar17 + 0x11c) = uStack_2284;
      __mi__7FVectorCFRC7FVector(&uStack_22a0,iVar17 + 0x110,iVar17 + 0x100);
      uStack_208._0_4_ = (float)uStack_2298;
      _auStack_210 = uStack_22a0;
      uStack_208._4_4_ = (float)uStack_2294;
      _auStack_210 = uStack_22a0 & 0xffffffff;
      fVar23 = (float)func_0x00222fd0(auStack_210);
      fVar23 = fVar23 - *(float *)(iVar5 + 0x354);
      if ((*(int *)(iVar17 + 0xd8) != 0) || (20.0 < fVar23)) {
        if ((*(int *)(iVar17 + 0xd8) != 1) || (30.0 < fVar23)) {
          if ((*(int *)(iVar17 + 0xd8) != 2) || (40.0 < fVar23)) {
            *(undefined2 *)(iVar17 + 0x1e) = 2;
          }
          else {
            *(undefined2 *)(iVar17 + 0x1e) = 1;
          }
        }
        else {
          *(undefined2 *)(iVar17 + 0x1e) = 1;
        }
      }
      else {
        *(undefined2 *)(iVar17 + 0x1e) = 1;
      }
      *(byte *)(iVar17 + 0x1a) = *(byte *)(iVar17 + 0x1a) & 0xfd | 2;
    }
    __mi__7FVectorCFRC7FVector(&uStack_22b0,iVar17 + 0x100,iVar17 + 0x110);
    afStack_30c[1] = (float)uStack_22a8;
    _auStack_310 = uStack_22b0;
    afStack_30c[2] = (float)uStack_22a4;
    _auStack_310 = uStack_22b0 & 0xffffffff;
    func_0x00222f20(auStack_310);
    func_0x00223010(*(undefined4 *)(iVar5 + 0x354),auStack_310);
    auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x100));
    auVar25 = _lqc2(_auStack_310);
    auVar25 = _vadd(auVar25,auVar26);
    _auStack_310 = _sqc2(auVar25);
    __mi__7FVectorCFRC7FVector(&uStack_22c0,iVar17 + 0x110,iVar17 + 0x100);
    auStack_300._8_4_ = uStack_22b8;
    auStack_300._0_8_ = uStack_22c0;
    auStack_300._12_4_ = uStack_22b4;
    auStack_300._0_8_ = uStack_22c0 & 0xffffffff;
    func_0x00222f20(auStack_300);
    iVar12 = *(int *)(iVar17 + 0xd8);
    if (iVar12 == 2) {
      if (40.0 < *(float *)(iVar15 + 0x354)) {
        func_0x00223010(*(undefined4 *)(iVar15 + 0x354),auStack_300);
      }
      else {
        func_0x00223010(0x42200000,auStack_300);
      }
    }
    else if (iVar12 == 1) {
      if (30.0 < *(float *)(iVar15 + 0x354)) {
        func_0x00223010(*(undefined4 *)(iVar15 + 0x354),auStack_300);
      }
      else {
        func_0x00223010(0x41f00000,auStack_300);
      }
    }
    else if (iVar12 == 0) {
      if (20.0 < *(float *)(iVar15 + 0x354)) {
        func_0x00223010(*(undefined4 *)(iVar15 + 0x354),auStack_300);
      }
      else {
        func_0x00223010(0x41a00000,auStack_300);
      }
    }
    auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x110));
    auVar25 = _lqc2(auStack_300);
    auVar25 = _vadd(auVar25,auVar26);
    auStack_300 = _sqc2(auVar25);
    if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3b) < 0) {
      __pl__7FVectorCFRC7FVector(auStack_26e0,auStack_310,auStack_300);
      *(int *)(iVar17 + 0x70) = auStack_26e0._0_4_;
      *(int *)(iVar17 + 0x74) = auStack_26e0._4_4_;
      *(undefined4 *)(iVar17 + 0x78) = uStack_26d8;
      *(undefined4 *)(iVar17 + 0x7c) = uStack_26d4;
      func_0x00223030(0x40000000,iVar17 + 0x70);
      *(undefined4 *)(iVar17 + 0x74) = 0;
      __mi__7FVectorCFRC7FVector(&uStack_26f0,auStack_310,auStack_300);
      uStack_208._0_4_ = (float)uStack_26e8;
      _auStack_210 = uStack_26f0;
      uStack_208._4_4_ = (float)uStack_26e4;
      fVar23 = (float)func_0x00222fd0(auStack_210);
      iVar12 = *(int *)(iVar17 + 0xd8);
      if (iVar12 == 2) {
        unaff_f20 = 115.0;
      }
      else if (iVar12 == 1) {
        unaff_f20 = 95.0;
      }
      else if (iVar12 == 0) {
        unaff_f20 = 75.0;
      }
      if (unaff_f20 <= fVar23 + 10.0) {
        unaff_f20 = fVar23 + 10.0;
      }
      *(undefined4 *)(iVar17 + 0x84) = 0x44000000;
      *(float *)(iVar17 + 0x80) = (unaff_f20 * *(float *)(iVar17 + 0x84)) / 512.0;
      if ((long)((ulong)*(byte *)(iVar17 + 0x1a) << 0x3e) < 0) {
        uVar8 = func_0x00222f00(auStack_2710,iVar17 + 0x70);
        Get3DAngle__F7FVector(&uStack_2700,uVar8);
        uStack_208._0_4_ = (float)uStack_26f8;
        _auStack_210 = uStack_2700;
        uStack_208._4_4_ = (float)uStack_26f4;
        *(float *)(iVar17 + 0xe0) = -(float)((ulong)uStack_2700 >> 0x20);
        while (*(float *)(iVar17 + 0xe0) < -180.0) {
          *(float *)(iVar17 + 0xe0) = *(float *)(iVar17 + 0xe0) + 360.0;
        }
        while (180.0 < *(float *)(iVar17 + 0xe0)) {
          *(float *)(iVar17 + 0xe0) = *(float *)(iVar17 + 0xe0) - 360.0;
        }
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(0xc1f00000);
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0xe0));
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_2730);
        func_0x00222df0(auStack_2720,auStack_430,uVar8);
        *(int *)(iVar17 + 0x50) = auStack_2720._0_4_;
        *(int *)(iVar17 + 0x54) = auStack_2720._4_4_;
        *(undefined4 *)(iVar17 + 0x58) = uStack_2718;
        *(undefined4 *)(iVar17 + 0x5c) = uStack_2714;
        auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
        auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
        auVar25 = _vadd(auVar25,auVar26);
        auVar25 = _sqc2(auVar25);
        *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
      }
      else {
        fVar23 = 0.0;
        if ((*(byte *)(iVar17 + 0x1a) & 1) == 0) {
          fVar23 = ((float)bStack_44e / 60.0 - (float)bStack_44d / 60.0) *
                   *(float *)(iVar17 + 0x24) * 30.0;
        }
        for (fVar23 = fVar23 + *(float *)(iVar17 + 0xe0); fVar23 < -180.0; fVar23 = fVar23 + 360.0)
        {
        }
        for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
        }
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(0xc1f00000);
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(fVar23);
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_2750);
        func_0x00222df0(auStack_2740,auStack_430,uVar8);
        *(int *)(iVar17 + 0x50) = auStack_2740._0_4_;
        *(int *)(iVar17 + 0x54) = auStack_2740._4_4_;
        *(undefined4 *)(iVar17 + 0x58) = uStack_2738;
        *(undefined4 *)(iVar17 + 0x5c) = uStack_2734;
        auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
        auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
        auVar25 = _vadd(auVar25,auVar26);
        auVar25 = _sqc2(auVar25);
        *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
        bVar4 = false;
        fVar22 = *(float *)(iVar17 + 0xe0);
        if (*(float *)(iVar17 + 0x50) < -*(float *)(iGpffff8610 + 0x40b4) / 2.0 + 5.0) {
          if ((fVar23 < 50.0) || (130.0 < fVar23)) {
            bVar4 = true;
          }
          if ((fVar22 < 50.0) || (130.0 < fVar22)) {
            bVar4 = true;
          }
        }
        if (*(float *)(iGpffff8610 + 0x40b4) / 2.0 - 5.0 < *(float *)(iVar17 + 0x50)) {
          if ((-50.0 < fVar23) || (fVar23 < -130.0)) {
            bVar4 = true;
          }
          if ((-50.0 < fVar22) || (fVar22 < -130.0)) {
            bVar4 = true;
          }
        }
        if (*(float *)(iVar17 + 0x58) < -*(float *)(iGpffff8610 + 0x40bc) / 2.0 + 5.0) {
          if ((fVar23 < -40.0) || (40.0 < fVar23)) {
            bVar4 = true;
          }
          if ((fVar22 < -40.0) || (40.0 < fVar22)) {
            bVar4 = true;
          }
        }
        if (*(float *)(iGpffff8610 + 0x40bc) / 2.0 - 5.0 < *(float *)(iVar17 + 0x58)) {
          if ((-140.0 < fVar23) && (fVar23 < 140.0)) {
            bVar4 = true;
          }
          if ((-140.0 < fVar22) && (fVar22 < 140.0)) {
            bVar4 = true;
          }
        }
        if (bVar4) {
          auVar25 = _vmr32(in_vf0);
          auVar26 = _vmr32(auVar25);
          auVar27 = _vmr32(auVar26);
          auStack_400 = _sqc2(in_vf0);
          auStack_410 = _sqc2(auVar25);
          auStack_420 = _sqc2(auVar26);
          auStack_430 = _sqc2(auVar27);
          uVar24 = func_0x00222e40(0xc1f00000);
          func_0x00202890(uVar24,auStack_430,auStack_430);
          uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0xe0));
          func_0x00202938(uVar24,auStack_430,auStack_430);
          uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_2770);
          func_0x00222df0(auStack_2760,auStack_430,uVar8);
          *(int *)(iVar17 + 0x50) = auStack_2760._0_4_;
          *(int *)(iVar17 + 0x54) = auStack_2760._4_4_;
          *(undefined4 *)(iVar17 + 0x58) = uStack_2758;
          *(undefined4 *)(iVar17 + 0x5c) = uStack_2754;
          auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
          auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
          auVar25 = _vadd(auVar25,auVar26);
          auVar25 = _sqc2(auVar25);
          *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
        }
        else {
          *(float *)(iVar17 + 0xe0) = fVar23;
        }
      }
    }
    else if (*(short *)(iVar17 + 0x1e) == 1) {
      *(undefined4 *)(iVar17 + 0x84) = 0x44000000;
      *(undefined4 *)(iVar17 + 0xe4) = 0xc1a00000;
      iVar12 = *(int *)(iVar17 + 0xd8);
      if (iVar12 == 2) {
        *(undefined4 *)(iVar17 + 0xe8) = 0x42b40000;
      }
      else if (iVar12 == 1) {
        *(undefined4 *)(iVar17 + 0xe8) = 0x428c0000;
      }
      else if (iVar12 == 0) {
        *(undefined4 *)(iVar17 + 0xe8) = 0x42480000;
      }
      *(int *)(iVar17 + 0x70) = (int)*(undefined8 *)(iVar17 + 0x110);
      *(int *)(iVar17 + 0x74) = (int)((ulong)*(undefined8 *)(iVar17 + 0x110) >> 0x20);
      *(undefined4 *)(iVar17 + 0x78) = *(undefined4 *)(iVar17 + 0x118);
      *(undefined4 *)(iVar17 + 0x7c) = *(undefined4 *)(iVar17 + 0x11c);
      *(float *)(iVar17 + 0x80) = (*(float *)(iVar17 + 0xe8) * *(float *)(iVar17 + 0x84)) / 512.0;
      if ((long)((ulong)*(byte *)(iVar17 + 0x1a) << 0x3e) < 0) {
        uVar8 = func_0x00222f00(auStack_22e0,iVar17 + 0x70);
        Get3DAngle__F7FVector(&uStack_22d0,uVar8);
        uStack_208._0_4_ = (float)uStack_22c8;
        _auStack_210 = uStack_22d0;
        uStack_208._4_4_ = (float)uStack_22c4;
        *(float *)(iVar17 + 0xe0) = -(float)((ulong)uStack_22d0 >> 0x20);
        while (*(float *)(iVar17 + 0xe0) < -180.0) {
          *(float *)(iVar17 + 0xe0) = *(float *)(iVar17 + 0xe0) + 360.0;
        }
        while (180.0 < *(float *)(iVar17 + 0xe0)) {
          *(float *)(iVar17 + 0xe0) = *(float *)(iVar17 + 0xe0) - 360.0;
        }
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0xe4));
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0xe0));
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_2300);
        func_0x00222df0(auStack_22f0,auStack_430,uVar8);
        *(int *)(iVar17 + 0x50) = auStack_22f0._0_4_;
        *(int *)(iVar17 + 0x54) = auStack_22f0._4_4_;
        *(undefined4 *)(iVar17 + 0x58) = uStack_22e8;
        *(undefined4 *)(iVar17 + 0x5c) = uStack_22e4;
        auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
        auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
        auVar25 = _vadd(auVar25,auVar26);
        auVar25 = _sqc2(auVar25);
        *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
      }
      else {
        fVar23 = 0.0;
        if ((*(byte *)(iVar17 + 0x1a) & 1) == 0) {
          fVar23 = ((float)bStack_44e / 60.0 - (float)bStack_44d / 60.0) *
                   *(float *)(iVar17 + 0x24) * 30.0;
        }
        for (fVar23 = fVar23 + *(float *)(iVar17 + 0xe0); fVar23 < -180.0; fVar23 = fVar23 + 360.0)
        {
        }
        for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
        }
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0xe4));
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(fVar23);
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_2320);
        func_0x00222df0(auStack_2310,auStack_430,uVar8);
        *(int *)(iVar17 + 0x50) = auStack_2310._0_4_;
        *(int *)(iVar17 + 0x54) = auStack_2310._4_4_;
        *(undefined4 *)(iVar17 + 0x58) = uStack_2308;
        *(undefined4 *)(iVar17 + 0x5c) = uStack_2304;
        auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
        auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
        auVar25 = _vadd(auVar25,auVar26);
        auVar25 = _sqc2(auVar25);
        *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
        bVar4 = false;
        fVar22 = *(float *)(iVar17 + 0xe0);
        if (*(float *)(iVar17 + 0x50) < -*(float *)(iGpffff8610 + 0x40b4) / 2.0 + 5.0) {
          if ((fVar23 < 50.0) || (130.0 < fVar23)) {
            bVar4 = true;
          }
          if ((fVar22 < 50.0) || (130.0 < fVar22)) {
            bVar4 = true;
          }
        }
        if (*(float *)(iGpffff8610 + 0x40b4) / 2.0 - 5.0 < *(float *)(iVar17 + 0x50)) {
          if ((-50.0 < fVar23) || (fVar23 < -130.0)) {
            bVar4 = true;
          }
          if ((-50.0 < fVar22) || (fVar22 < -130.0)) {
            bVar4 = true;
          }
        }
        if (*(float *)(iVar17 + 0x58) < -*(float *)(iGpffff8610 + 0x40bc) / 2.0 + 5.0) {
          if ((fVar23 < -40.0) || (40.0 < fVar23)) {
            bVar4 = true;
          }
          if ((fVar22 < -40.0) || (40.0 < fVar22)) {
            bVar4 = true;
          }
        }
        if (*(float *)(iGpffff8610 + 0x40bc) / 2.0 - 5.0 < *(float *)(iVar17 + 0x58)) {
          if ((-140.0 < fVar23) && (fVar23 < 140.0)) {
            bVar4 = true;
          }
          if ((-140.0 < fVar22) && (fVar22 < 140.0)) {
            bVar4 = true;
          }
        }
        if (bVar4) {
          auVar25 = _vmr32(in_vf0);
          auVar26 = _vmr32(auVar25);
          auVar27 = _vmr32(auVar26);
          auStack_400 = _sqc2(in_vf0);
          auStack_410 = _sqc2(auVar25);
          auStack_420 = _sqc2(auVar26);
          auStack_430 = _sqc2(auVar27);
          uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0xe4));
          func_0x00202890(uVar24,auStack_430,auStack_430);
          uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0xe0));
          func_0x00202938(uVar24,auStack_430,auStack_430);
          uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_2340);
          func_0x00222df0(auStack_2330,auStack_430,uVar8);
          *(int *)(iVar17 + 0x50) = auStack_2330._0_4_;
          *(int *)(iVar17 + 0x54) = auStack_2330._4_4_;
          *(undefined4 *)(iVar17 + 0x58) = uStack_2328;
          *(undefined4 *)(iVar17 + 0x5c) = uStack_2324;
          auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
          auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
          auVar25 = _vadd(auVar25,auVar26);
          auVar25 = _sqc2(auVar25);
          *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
        }
        else {
          *(float *)(iVar17 + 0xe0) = fVar23;
        }
      }
    }
    else {
      __mi__7FVectorCFRC7FVector(auStack_2350,iVar17 + 0x110,iVar17 + 0x100);
      FUN_004baab0(*(undefined4 *)(iGpffff8610 + 0x40b4),0,*(undefined4 *)(iGpffff8610 + 0x40bc),
                   0x3f800000,auStack_2360);
      fVar23 = (float)func_0x00222fd0(auStack_210);
      fVar22 = (float)func_0x00222fd0(auStack_200);
      *(float *)(iVar17 + 0x84) = (fVar23 / (fVar22 * 0.75) + 1.2) * 512.0;
      __mi__7FVectorCFRC7FVector(&uStack_2370,iVar17 + 0x110,iVar17 + 0x100);
      uStack_208._0_4_ = (float)uStack_2368;
      _auStack_210 = uStack_2370;
      uStack_208._4_4_ = (float)uStack_2364;
      uVar8 = func_0x00222f00(auStack_2390,auStack_210);
      Get3DAngle__F7FVector(&uStack_2380,uVar8);
      fStack_1f8 = (float)uStack_2378;
      auStack_200 = (undefined1  [8])uStack_2380;
      uStack_1f4 = uStack_2374;
      auVar25 = _vmr32(in_vf0);
      auVar26 = _vmr32(auVar25);
      auVar27 = _vmr32(auVar26);
      auStack_400 = _sqc2(in_vf0);
      auStack_410 = _sqc2(auVar25);
      auStack_420 = _sqc2(auVar26);
      auStack_430 = _sqc2(auVar27);
      uVar24 = func_0x00222e40(-(float)((ulong)uStack_2380 >> 0x20));
      func_0x00202938(uVar24,auStack_430,auStack_430);
      uVar8 = FUN_004baab0(*(float *)(iVar5 + 0x354) * 2.0,0,0,0x3f800000,auStack_23b0);
      func_0x00222df0(auStack_23a0,auStack_430,uVar8);
      fStack_1f0 = auStack_23a0._0_4_;
      fStack_1ec = auStack_23a0._4_4_;
      fStack_1e8 = fStack_2398;
      uStack_1e4 = uStack_2394;
      uVar8 = FUN_004baab0(-*(float *)(iVar5 + 0x354) * 2.0,0,0,0x3f800000,auStack_23d0);
      func_0x00222df0(auStack_23c0,auStack_430,uVar8);
      fStack_1e0 = auStack_23c0._0_4_;
      fStack_1dc = auStack_23c0._4_4_;
      fStack_1d8 = fStack_23b8;
      uStack_1d4 = uStack_23b4;
      bVar3 = *(byte *)(iVar17 + 0x19) >> 6;
      if (bVar3 == 2) {
        __pl__7FVectorCFRC7FVector(&uStack_2670,iVar17 + 0x100,&fStack_1e0);
        uStack_208._0_4_ = (float)uStack_2668;
        _auStack_210 = uStack_2670;
        uStack_208._4_4_ = (float)uStack_2664;
        __mi__7FVectorCFRC7FVector(auStack_2680,iVar17 + 0x110,auStack_210);
        uVar8 = func_0x00222f00(auStack_26a0,auStack_200);
        Get3DAngle__F7FVector(&uStack_2690,uVar8);
        fStack_1f8 = (float)uStack_2688;
        auStack_200 = (undefined1  [8])uStack_2690;
        uStack_1f4 = uStack_2684;
        fVar23 = -(float)uStack_2690;
        if ((fVar23 <= 40.0) && (fVar23 = fVar23 * 1.25 - 10.0, fVar23 < -10.0)) {
          fVar23 = -10.0;
        }
        fVar20 = (float)func_0x00222fd0(iVar5 + 0x3b0);
        fVar22 = *(float *)(iVar5 + 0x354);
        fVar21 = *(float *)(iVar17 + 0x84);
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(fVar23);
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-((fVar21 * (fVar22 + fVar20 + 30.0)) / 512.0),0x3f800000,
                             auStack_26c0);
        func_0x00222df0(&uStack_26b0,auStack_430,uVar8);
        fStack_1f8 = (float)uStack_26a8;
        auStack_200 = (undefined1  [8])uStack_26b0;
        uStack_1f4 = uStack_26a4;
        __pl__7FVectorCFRC7FVector(auStack_26d0,auStack_210,auStack_200);
        *(int *)(iVar17 + 0x50) = auStack_26d0._0_4_;
        *(int *)(iVar17 + 0x54) = auStack_26d0._4_4_;
        *(undefined4 *)(iVar17 + 0x58) = uStack_26c8;
        *(undefined4 *)(iVar17 + 0x5c) = uStack_26c4;
      }
      else if (bVar3 == 1) {
        __pl__7FVectorCFRC7FVector(&uStack_2600,iVar17 + 0x100,&fStack_1f0);
        uStack_208._0_4_ = (float)uStack_25f8;
        _auStack_210 = uStack_2600;
        uStack_208._4_4_ = (float)uStack_25f4;
        __mi__7FVectorCFRC7FVector(auStack_2610,iVar17 + 0x110,auStack_210);
        uVar8 = func_0x00222f00(auStack_2630,auStack_200);
        Get3DAngle__F7FVector(&uStack_2620,uVar8);
        fStack_1f8 = (float)uStack_2618;
        auStack_200 = (undefined1  [8])uStack_2620;
        uStack_1f4 = uStack_2614;
        fVar23 = -(float)uStack_2620;
        if ((fVar23 <= 40.0) && (fVar23 = fVar23 * 1.25 - 10.0, fVar23 < -10.0)) {
          fVar23 = -10.0;
        }
        fVar20 = (float)func_0x00222fd0(iVar5 + 0x3b0);
        fVar22 = *(float *)(iVar5 + 0x354);
        fVar21 = *(float *)(iVar17 + 0x84);
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(fVar23);
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-((fVar21 * (fVar22 + fVar20 + 30.0)) / 512.0),0x3f800000,
                             auStack_2650);
        func_0x00222df0(&uStack_2640,auStack_430,uVar8);
        fStack_1f8 = (float)uStack_2638;
        auStack_200 = (undefined1  [8])uStack_2640;
        uStack_1f4 = uStack_2634;
        __pl__7FVectorCFRC7FVector(auStack_2660,auStack_210,auStack_200);
        *(int *)(iVar17 + 0x50) = auStack_2660._0_4_;
        *(int *)(iVar17 + 0x54) = auStack_2660._4_4_;
        *(undefined4 *)(iVar17 + 0x58) = uStack_2658;
        *(undefined4 *)(iVar17 + 0x5c) = uStack_2654;
      }
      else if (bVar3 == 0) {
        __pl__7FVectorCFRC7FVector(auStack_23e0,iVar17 + 0x100,&fStack_1f0);
        __mi__7FVectorCFRC7FVector(auStack_23f0,iVar17 + 0x110,auStack_210);
        uVar8 = func_0x00222f00(auStack_2410,auStack_200);
        Get3DAngle__F7FVector(&uStack_2400,uVar8);
        fStack_1f8 = (float)uStack_23f8;
        auStack_200 = (undefined1  [8])uStack_2400;
        uStack_1f4 = uStack_23f4;
        fVar23 = -(float)uStack_2400;
        if ((fVar23 <= 40.0) && (fVar23 = fVar23 * 1.25 - 10.0, fVar23 < -10.0)) {
          fVar23 = -10.0;
        }
        fVar20 = (float)func_0x00222fd0(iVar5 + 0x3b0);
        fVar22 = *(float *)(iVar5 + 0x354);
        fVar21 = *(float *)(iVar17 + 0x84);
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(fVar23);
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-((fVar21 * (fVar22 + fVar20 + 30.0)) / 512.0),0x3f800000,
                             auStack_2430);
        func_0x00222df0(auStack_2420,auStack_430,uVar8);
        __pl__7FVectorCFRC7FVector(auStack_2440,auStack_210,auStack_200);
        uStack_2f0 = auStack_2440._0_4_;
        uStack_2ec = auStack_2440._4_4_;
        uStack_2e8 = uStack_2438;
        uStack_2e4 = uStack_2434;
        __pl__7FVectorCFRC7FVector(auStack_2450,iVar17 + 0x100,&fStack_1e0);
        __mi__7FVectorCFRC7FVector(auStack_2460,iVar17 + 0x110,auStack_210);
        uVar8 = func_0x00222f00(auStack_2480,auStack_200);
        Get3DAngle__F7FVector(&uStack_2470,uVar8);
        fStack_1f8 = (float)uStack_2468;
        auStack_200 = (undefined1  [8])uStack_2470;
        uStack_1f4 = uStack_2464;
        fVar23 = -(float)uStack_2470;
        if ((fVar23 <= 40.0) && (fVar23 = fVar23 * 1.25 - 10.0, fVar23 < -10.0)) {
          fVar23 = -10.0;
        }
        fVar20 = (float)func_0x00222fd0(iVar5 + 0x3b0);
        fVar22 = *(float *)(iVar5 + 0x354);
        fVar21 = *(float *)(iVar17 + 0x84);
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(fVar23);
        func_0x00202890(uVar24,auStack_430,auStack_430);
        uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
        func_0x00202938(uVar24,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-((fVar21 * (fVar22 + fVar20 + 30.0)) / 512.0),0x3f800000,
                             auStack_24a0);
        func_0x00222df0(auStack_2490,auStack_430,uVar8);
        __pl__7FVectorCFRC7FVector(auStack_24b0,auStack_210,auStack_200);
        uStack_2e0 = auStack_24b0._0_4_;
        uStack_2dc = auStack_24b0._4_4_;
        uStack_2d8 = uStack_24a8;
        uStack_2d4 = uStack_24a4;
        __mi__7FVectorCFRC7FVector(auStack_24c0,iVar17 + 0x100,&uStack_2f0);
        uVar24 = func_0x00222fd0(auStack_210);
        uVar8 = func_0x00222f00(auStack_24e0,auStack_210);
        Get3DAngle__F7FVector(&uStack_24d0,uVar8);
        uStack_208._0_4_ = (float)uVar24;
        _auStack_210 = uStack_24d0;
        uStack_208._4_4_ = (float)uStack_24c4;
        __mi__7FVectorCFRC7FVector(&uStack_24f0,iVar17 + 0x110,&uStack_2f0);
        fStack_1f8 = (float)uStack_24e8;
        auStack_200 = (undefined1  [8])uStack_24f0;
        uStack_1f4 = uStack_24e4;
        auStack_200 = (undefined1  [8])(uStack_24f0 & 0xffffffff);
        uVar24 = func_0x00222fd0(auStack_200);
        uVar8 = func_0x00222f00(auStack_2510,auStack_200);
        Get3DAngle__F7FVector(&uStack_2500,uVar8);
        fStack_1f8 = (float)uVar24;
        auStack_200 = (undefined1  [8])uStack_2500;
        uStack_1f4 = uStack_24f4;
        __mi__7FVectorCFRC7FVector(auStack_2520,iVar17 + 0x100,&uStack_2e0);
        fStack_1e8 = (float)uStack_2518;
        uStack_1e4 = uStack_2514;
        fStack_1ec = 0.0;
        fVar23 = (float)func_0x00222fd0(&fStack_1f0);
        uVar8 = func_0x00222f00(auStack_2540,&fStack_1f0);
        Get3DAngle__F7FVector(auStack_2530,uVar8);
        fStack_1f0 = (float)auStack_2530._0_8_;
        fStack_1ec = SUB84(auStack_2530._0_8_,4);
        uStack_1e4 = uStack_2524;
        fStack_1e8 = fVar23;
        __mi__7FVectorCFRC7FVector(auStack_2550,iVar17 + 0x110,&uStack_2e0);
        fStack_1d8 = (float)uStack_2548;
        uStack_1d4 = uStack_2544;
        fStack_1dc = 0.0;
        fVar23 = (float)func_0x00222fd0(&fStack_1e0);
        uVar8 = func_0x00222f00(auStack_2570,&fStack_1e0);
        Get3DAngle__F7FVector(auStack_2560,uVar8);
        fStack_1e0 = (float)auStack_2560._0_8_;
        fStack_1dc = SUB84(auStack_2560._0_8_,4);
        uStack_1d4 = uStack_2554;
        iVar12 = 0;
        iVar18 = 0;
        fStack_1d8 = fVar23;
        for (iVar13 = 0; iVar13 < 0xc; iVar13 = iVar13 + 1) {
          if (((((*(byte *)(iGpffff8610 + iVar13 * 0x510 + 0xb0) & 1) != 0) &&
               ((long)((ulong)*(byte *)(iGpffff8610 + iVar13 * 0x510 + 0xb0) << 0x3e) < 0)) &&
              (-1 < (long)((ulong)*(byte *)(iGpffff8610 + iVar13 * 0x510 + 0xb2) << 0x3c))) &&
             ((iVar13 != *(int *)(iVar17 + 0xd0) && (iVar13 != *(int *)(iVar17 + 0xd4))))) {
            __pl__7FVectorCFRC7FVector
                      (auStack_2590,iGpffff8610 + iVar13 * 0x510 + 0x160,
                       iGpffff8610 + iVar13 * 0x510 + 0x3a0);
            __mi__7FVectorCFRC7FVector(auStack_2580,auStack_2590,auStack_310);
            fStack_1d0 = auStack_2580._0_4_;
            fStack_1cc = auStack_2580._4_4_;
            uStack_1c8 = uStack_2578;
            uStack_1c4 = uStack_2574;
            fVar23 = (float)func_0x00222fd0(&fStack_1d0);
            uVar8 = func_0x00222f00(auStack_25b0,&fStack_1d0);
            Get3DAngle__F7FVector(auStack_25a0,uVar8);
            fStack_1d0 = auStack_25a0._0_4_;
            fStack_1cc = auStack_25a0._4_4_;
            uStack_1c8 = uStack_2598;
            uStack_1c4 = uStack_2594;
            if (fVar23 < (float)uStack_208 + *(float *)(iVar5 + 0x354) + 10.0) {
              for (fVar22 = fStack_1cc - fStack_20c; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
              }
              for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
              }
              if ((-60.0 <= fVar22) && (fVar22 <= 60.0)) {
                iVar12 = iVar12 + 1;
              }
            }
            if (fVar23 < fStack_1f8 + *(float *)(iVar15 + 0x354) + 10.0) {
              for (fVar23 = fStack_1cc - (float)auStack_200._4_4_; fVar23 < -180.0;
                  fVar23 = fVar23 + 360.0) {
              }
              for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
              }
              if ((-60.0 <= fVar23) && (fVar23 <= 60.0)) {
                iVar12 = iVar12 + 1;
              }
            }
            __pl__7FVectorCFRC7FVector
                      (auStack_25d0,iGpffff8610 + iVar13 * 0x510 + 0x160,
                       iGpffff8610 + iVar13 * 0x510 + 0x3a0);
            __mi__7FVectorCFRC7FVector(auStack_25c0,auStack_25d0,auStack_300);
            fStack_1d0 = auStack_25c0._0_4_;
            fStack_1cc = auStack_25c0._4_4_;
            uStack_1c8 = uStack_25b8;
            uStack_1c4 = uStack_25b4;
            fVar23 = (float)func_0x00222fd0(&fStack_1d0);
            uVar8 = func_0x00222f00(auStack_25f0,&fStack_1d0);
            Get3DAngle__F7FVector(auStack_25e0,uVar8);
            fStack_1d0 = auStack_25e0._0_4_;
            fStack_1cc = auStack_25e0._4_4_;
            uStack_1c8 = uStack_25d8;
            uStack_1c4 = uStack_25d4;
            if (fVar23 < fStack_1e8 + *(float *)(iVar5 + 0x354) + 10.0) {
              for (fVar22 = fStack_1cc - fStack_1ec; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
              }
              for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
              }
              if ((-60.0 <= fVar22) && (fVar22 <= 60.0)) {
                iVar18 = iVar18 + 1;
              }
            }
            if (fVar23 < fStack_1d8 + *(float *)(iVar15 + 0x354) + 10.0) {
              for (fVar23 = fStack_1cc - fStack_1dc; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
              }
              for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
              }
              if ((-60.0 <= fVar23) && (fVar23 <= 60.0)) {
                iVar18 = iVar18 + 1;
              }
            }
          }
        }
        if (iVar12 < iVar18) {
          *(undefined4 *)(iVar17 + 0x50) = uStack_2f0;
          *(undefined4 *)(iVar17 + 0x54) = uStack_2ec;
          *(undefined4 *)(iVar17 + 0x58) = uStack_2e8;
          *(undefined4 *)(iVar17 + 0x5c) = uStack_2e4;
          *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0x3f | 0x40;
        }
        else if (iVar18 < iVar12) {
          *(undefined4 *)(iVar17 + 0x50) = uStack_2e0;
          *(undefined4 *)(iVar17 + 0x54) = uStack_2dc;
          *(undefined4 *)(iVar17 + 0x58) = uStack_2d8;
          *(undefined4 *)(iVar17 + 0x5c) = uStack_2d4;
          *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0x3f | 0x80;
        }
        else {
          fVar23 = (float)func_0x00222fd0(&uStack_2f0);
          fVar22 = (float)func_0x00222fd0(&uStack_2e0);
          if (fVar23 < fVar22) {
            *(undefined4 *)(iVar17 + 0x50) = uStack_2f0;
            *(undefined4 *)(iVar17 + 0x54) = uStack_2ec;
            *(undefined4 *)(iVar17 + 0x58) = uStack_2e8;
            *(undefined4 *)(iVar17 + 0x5c) = uStack_2e4;
            *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0x3f | 0x40;
          }
          else {
            *(undefined4 *)(iVar17 + 0x50) = uStack_2e0;
            *(undefined4 *)(iVar17 + 0x54) = uStack_2dc;
            *(undefined4 *)(iVar17 + 0x58) = uStack_2d8;
            *(undefined4 *)(iVar17 + 0x5c) = uStack_2d4;
            *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0x3f | 0x80;
          }
        }
      }
      if (-10.0 < *(float *)(iVar17 + 0x54)) {
        *(undefined4 *)(iVar17 + 0x54) = 0xc1200000;
      }
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    uVar8 = FUN_004baab0(0,-*(float *)(iVar15 + 0x3b4),0,0x3f800000,auStack_27a0);
    __pl__7FVectorCFRC7FVector(auStack_2790,auStack_300,uVar8);
    __mi__7FVectorCFRC7FVector(&uStack_2780,auStack_2790,iVar17 + 0x50);
    uStack_208._0_4_ = (float)uStack_2778;
    _auStack_210 = uStack_2780;
    uStack_208._4_4_ = (float)uStack_2774;
    uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar15 + 0x3b4),0,0x3f800000,auStack_27d0);
    __pl__7FVectorCFRC7FVector(auStack_27c0,auStack_300,uVar8);
    __mi__7FVectorCFRC7FVector(&uStack_27b0,auStack_27c0,iVar17 + 0x50);
    fStack_1f8 = (float)uStack_27a8;
    auStack_200 = (undefined1  [8])uStack_27b0;
    uStack_1f4 = uStack_27a4;
    uVar8 = FUN_004baab0(0,-*(float *)(iVar5 + 0x3b4),0,0x3f800000,auStack_2800);
    __pl__7FVectorCFRC7FVector(auStack_27f0,auStack_310,uVar8);
    __mi__7FVectorCFRC7FVector(auStack_27e0,auStack_27f0,iVar17 + 0x50);
    fStack_1f0 = auStack_27e0._0_4_;
    fStack_1ec = auStack_27e0._4_4_;
    fStack_1e8 = fStack_27d8;
    uStack_1e4 = uStack_27d4;
    if ((long)((ulong)*(byte *)(iVar17 + 0x19) << 0x3b) < 0) {
      uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar5 + 0x3b4),0,0x3f800000,auStack_2860);
      __pl__7FVectorCFRC7FVector(auStack_2850,auStack_310,uVar8);
      __mi__7FVectorCFRC7FVector(auStack_2840,auStack_2850,iVar17 + 0x50);
      fStack_1e0 = auStack_2840._0_4_;
      fStack_1dc = auStack_2840._4_4_;
      fStack_1d8 = fStack_2838;
      uStack_1d4 = uStack_2834;
    }
    else {
      uVar8 = FUN_004baab0(0,*(float *)(iVar5 + 0x3b4) * 0.5,0,0x3f800000,auStack_2830);
      __pl__7FVectorCFRC7FVector(auStack_2820,auStack_310,uVar8);
      __mi__7FVectorCFRC7FVector(auStack_2810,auStack_2820,iVar17 + 0x50);
      fStack_1e0 = auStack_2810._0_4_;
      fStack_1dc = auStack_2810._4_4_;
      fStack_1d8 = fStack_2808;
      uStack_1d4 = uStack_2804;
    }
    uVar8 = func_0x00222f00(auStack_2880,auStack_210);
    Get3DAngle__F7FVector(auStack_2870,uVar8);
    fStack_1d0 = auStack_2870._0_4_;
    fStack_1cc = auStack_2870._4_4_;
    uStack_1c8 = uStack_2868;
    uStack_1c4 = uStack_2864;
    uVar8 = func_0x00222f00(auStack_28a0,auStack_200);
    Get3DAngle__F7FVector(auStack_2890,uVar8);
    afStack_1c0[0] = auStack_2890._0_4_;
    afStack_1c0[1] = auStack_2890._4_4_;
    afStack_1c0[2] = (float)uStack_2888;
    afStack_1c0[3] = (float)uStack_2884;
    uVar8 = func_0x00222f00(auStack_28c0,&fStack_1f0);
    Get3DAngle__F7FVector(auStack_28b0,uVar8);
    afStack_1c0[4] = auStack_28b0._0_4_;
    afStack_1c0[5] = auStack_28b0._4_4_;
    afStack_1c0[6] = (float)uStack_28a8;
    afStack_1c0[7] = (float)uStack_28a4;
    uVar8 = func_0x00222f00(auStack_28e0,&fStack_1e0);
    Get3DAngle__F7FVector(auStack_28d0,uVar8);
    afStack_1c0[8] = (float)auStack_28d0._0_4_;
    afStack_1c0[9] = (float)auStack_28d0._4_4_;
    afStack_1c0[10] = (float)uStack_28c8;
    afStack_1c0[0xb] = (float)uStack_28c4;
    for (; fStack_1d0 < -180.0; fStack_1d0 = fStack_1d0 + 360.0) {
    }
    for (; 180.0 < fStack_1d0; fStack_1d0 = fStack_1d0 - 360.0) {
    }
    fVar23 = fStack_1d0;
    fVar22 = fStack_1d0;
    for (iVar5 = 5; iVar5 < 8; iVar5 = iVar5 + 1) {
      while (*(float *)(auStack_210 + iVar5 * 0x10) < -180.0) {
        *(float *)(auStack_210 + iVar5 * 0x10) = *(float *)(auStack_210 + iVar5 * 0x10) + 360.0;
      }
      while (180.0 < *(float *)(auStack_210 + iVar5 * 0x10)) {
        *(float *)(auStack_210 + iVar5 * 0x10) = *(float *)(auStack_210 + iVar5 * 0x10) - 360.0;
      }
      if (*(float *)(auStack_210 + iVar5 * 0x10) < fVar23) {
        fVar23 = *(float *)(auStack_210 + iVar5 * 0x10);
      }
      if (fVar22 < *(float *)(auStack_210 + iVar5 * 0x10)) {
        fVar22 = *(float *)(auStack_210 + iVar5 * 0x10);
      }
    }
    for (fVar22 = fVar22 - fVar23; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
    }
    for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
    }
    *(float *)(iVar17 + 0x60) = -(fVar23 + fVar22 / 2.0);
    while (*(float *)(iVar17 + 0x60) < -180.0) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 0x60)) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
    }
    for (fVar23 = fStack_1cc - afStack_1c0[5]; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
    }
    *(float *)(iVar17 + 100) = -(afStack_1c0[5] + fVar23 / 2.0);
    while (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    *(undefined4 *)(iVar17 + 0x68) = 0;
    break;
  case 0xf:
    if (*(short *)(iVar17 + 0x1e) == 1) {
LAB_005a2aa0:
      fVar23 = 0.0;
      if ((*(byte *)(iVar17 + 0x1a) & 1) == 0) {
        fVar23 = ((float)bStack_44e / 60.0 - (float)bStack_44d / 60.0) *
                 *(float *)(iVar17 + 0x24) * 30.0;
      }
      if (fVar23 != 0.0) {
        if (0.0 < fVar23) {
          *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0xdf;
        }
        else {
          *(byte *)(iVar17 + 0x19) = *(byte *)(iVar17 + 0x19) & 0xdf | 0x20;
        }
      }
      *(float *)(iVar17 + 0xe4) = *(float *)(iVar17 + 0xe4) + fVar23;
    }
    else if (*(short *)(iVar17 + 0x1e) == 0) {
      *(undefined4 *)(iVar17 + 0xe0) = 0;
      *(undefined4 *)(iVar17 + 0xe4) = 0;
      *(undefined4 *)(iVar17 + 0xe8) = 0xc1c80000;
      *(undefined4 *)(iVar17 + 0xec) = 0;
      *(undefined4 *)(iVar17 + 0xdc) = 0;
      *(undefined2 *)(iVar17 + 0x1e) = 1;
      goto LAB_005a2aa0;
    }
    FUN_004baab0(*(undefined4 *)(iVar17 + 0xe8),*(undefined4 *)(iVar17 + 0xe4),0,0x3f800000,
                 auStack_28f0);
    *(int *)(iVar17 + 0x60) = auStack_28f0._0_4_;
    *(int *)(iVar17 + 100) = auStack_28f0._4_4_;
    *(undefined4 *)(iVar17 + 0x68) = uStack_28e8;
    *(undefined4 *)(iVar17 + 0x6c) = uStack_28e4;
    FUN_004baab0(0,0,0,0x3f800000,auStack_2900);
    *(int *)(iVar17 + 0x70) = auStack_2900._0_4_;
    *(int *)(iVar17 + 0x74) = auStack_2900._4_4_;
    *(undefined4 *)(iVar17 + 0x78) = uStack_28f8;
    *(undefined4 *)(iVar17 + 0x7c) = uStack_28f4;
    *(float *)(iVar17 + 0x80) =
         (*(float *)(iVar17 + 0x84) *
         (*(float *)(iVar17 + 0xec) +
         ((*(float *)(iGpffff8610 + 0x40b4) + *(float *)(iGpffff8610 + 0x40bc) + 10.0 + 10.0) / 2.0)
         / 1.5)) / 512.0;
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x60));
    func_0x00202890(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 100));
    func_0x00202938(uVar24,auStack_430,auStack_430);
    uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_2920);
    func_0x00222df0(auStack_2910,auStack_430,uVar8);
    *(int *)(iVar17 + 0x50) = auStack_2910._0_4_;
    *(int *)(iVar17 + 0x54) = auStack_2910._4_4_;
    *(undefined4 *)(iVar17 + 0x58) = uStack_2908;
    *(undefined4 *)(iVar17 + 0x5c) = uStack_2904;
    auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
    auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
    auVar25 = _vadd(auVar25,auVar26);
    auVar25 = _sqc2(auVar25);
    *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    if (-10.0 < *(float *)(iVar17 + 0x54)) {
      *(undefined4 *)(iVar17 + 0x54) = 0xc1200000;
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    break;
  case 0x10:
    if (*(int *)(iVar17 + 0xd0) < 0x80) {
      iVar5 = iGpffff8610 + *(int *)(iVar17 + 0xd0) * 0x510;
      if ((((long)((ulong)*(byte *)(iVar5 + 0xb4) << 0x39) < 0) ||
          ((long)((ulong)*(byte *)(iVar5 + 0xb5) << 0x3c) < 0)) ||
         ((long)((ulong)*(byte *)(iVar5 + 0xb1) << 0x3a) < 0)) {
        uVar8 = FUN_004baab0(*(undefined4 *)(iVar5 + 0x3a0),0,*(undefined4 *)(iVar5 + 0x3a8),
                             0x3f800000,auStack_2960);
        __pl__7FVectorCFRC7FVector(auStack_2950,iVar5 + 0x170,uVar8);
        *(int *)(iVar17 + 0x70) = auStack_2950._0_4_;
        *(int *)(iVar17 + 0x74) = auStack_2950._4_4_;
        *(undefined4 *)(iVar17 + 0x78) = uStack_2948;
        *(undefined4 *)(iVar17 + 0x7c) = uStack_2944;
      }
      else {
        uVar8 = FUN_004baab0(*(undefined4 *)(iVar5 + 0x3a0),0,*(undefined4 *)(iVar5 + 0x3a8),
                             0x3f800000,auStack_2940);
        __pl__7FVectorCFRC7FVector(auStack_2930,iVar5 + 0x160,uVar8);
        *(int *)(iVar17 + 0x70) = auStack_2930._0_4_;
        *(int *)(iVar17 + 0x74) = auStack_2930._4_4_;
        *(undefined4 *)(iVar17 + 0x78) = uStack_2928;
        *(undefined4 *)(iVar17 + 0x7c) = uStack_2924;
      }
    }
    else {
      FUN_004baab0(*(undefined4 *)(iGpffff8610 + (*(int *)(iVar17 + 0xd0) + -0x80) * 8 + 0x403c),0,
                   *(undefined4 *)(iGpffff8610 + (*(int *)(iVar17 + 0xd0) + -0x80) * 8 + 0x4040),
                   0x3f800000,auStack_2970);
      *(int *)(iVar17 + 0x70) = auStack_2970._0_4_;
      *(int *)(iVar17 + 0x74) = auStack_2970._4_4_;
      *(undefined4 *)(iVar17 + 0x78) = uStack_2968;
      *(undefined4 *)(iVar17 + 0x7c) = uStack_2964;
    }
    *(float *)(iVar17 + 0x80) = (*(float *)(iVar17 + 0x84) * 150.0) / 512.0;
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x100));
    func_0x00202890(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x104));
    func_0x00202938(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x108));
    func_0x002027e8(uVar24,auStack_430,auStack_430);
    uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_29a0);
    func_0x00222df0(auStack_2990,auStack_430,uVar8);
    __pl__7FVectorCFRC7FVector(&uStack_2980,auStack_2990,iVar17 + 0x70);
    uStack_208._0_4_ = fStack_2978;
    _auStack_210 = uStack_2980;
    uStack_208._4_4_ = (float)uStack_2974;
    fVar23 = (float)uStack_2980 / 4.0;
    auStack_210 = (undefined1  [4])fVar23;
    uStack_208._0_4_ =
         (fStack_2978 + (*(float *)(iGpffff8610 + 0x40bc) + 10.0) / 2.0) / 2.0 -
         (*(float *)(iGpffff8610 + 0x40bc) + 10.0) / 2.0;
    if (*(int *)(iVar17 + 0xdc) == 0) {
      *(float *)(iVar17 + 0x50) = fVar23;
      *(int *)(iVar17 + 0x54) = (int)((ulong)uStack_2980 >> 0x20);
      *(float *)(iVar17 + 0x58) = (float)uStack_208;
      *(undefined4 *)(iVar17 + 0x5c) = uStack_2974;
    }
    else {
      auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _lqc2(_auStack_210);
      auVar25 = _vsub(auVar25,auVar26);
      _auStack_210 = _sqc2(auVar25);
      fVar23 = (float)func_0x00222fd0(auStack_210);
      if (*(float *)(iVar17 + 0x24) * 300.0 < fVar23) {
        func_0x00222f20(auStack_210);
        func_0x00223010(*(float *)(iVar17 + 0x24) * 300.0,auStack_210);
      }
      auVar26 = _lqc2(_auStack_210);
      auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _vadd(auVar25,auVar26);
      auVar25 = _sqc2(auVar25);
      *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    __mi__7FVectorCFRC7FVector(&uStack_29b0,iVar17 + 0x70,iVar17 + 0x50);
    uStack_208._0_4_ = (float)uStack_29a8;
    _auStack_210 = uStack_29b0;
    uStack_208._4_4_ = (float)uStack_29a4;
    uVar8 = func_0x00222f00(auStack_29d0,auStack_210);
    Get3DAngle__F7FVector(&uStack_29c0,uVar8);
    fStack_1f8 = (float)uStack_29b8;
    auStack_200 = (undefined1  [8])uStack_29c0;
    uStack_1f4 = uStack_29b4;
    auVar25 = _auStack_200;
    auStack_200._0_4_ = (undefined4)uStack_29c0;
    auStack_200._4_4_ = (undefined4)((ulong)uStack_29c0 >> 0x20);
    if (*(int *)(iVar17 + 0xdc) == 0) {
      *(float *)(iVar17 + 0x60) = -(float)auStack_200._0_4_;
      *(float *)(iVar17 + 100) = -(float)auStack_200._4_4_;
    }
    else {
      for (fVar23 = -(float)auStack_200._0_4_ - *(float *)(iVar17 + 0x60); fVar23 < -180.0;
          fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 0x60) =
           *(float *)(iVar17 + 0x60) + fVar23 * 7.5 * *(float *)(iVar17 + 0x24);
      for (fVar23 = -(float)auStack_200._4_4_ - *(float *)(iVar17 + 100); fVar23 < -180.0;
          fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + fVar23 * 7.5 * *(float *)(iVar17 + 0x24)
      ;
    }
    while (*(float *)(iVar17 + 0x60) < -180.0) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 0x60)) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
    }
    while (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    *(undefined4 *)(iVar17 + 0x68) = 0;
    *(undefined4 *)(iVar17 + 0xdc) = 1;
    _auStack_200 = auVar25;
    break;
  case 0x11:
    iVar5 = iGpffff8610 + *(int *)(iVar17 + 0xd0) * 0x510;
    iVar15 = iGpffff8610 + *(int *)(iVar17 + 0xd4) * 0x510;
    if (*(short *)(iVar17 + 0x1e) == 0) {
      __pl__7FVectorCFRC7FVector(&uStack_29e0,iVar15 + 0x160,iVar15 + 0x3a0);
      uStack_208._0_4_ = (float)uStack_29d8;
      _auStack_210 = uStack_29e0;
      uStack_208._4_4_ = (float)uStack_29d4;
      __pl__7FVectorCFRC7FVector(auStack_29f0,iVar5 + 0x160,iVar5 + 0x3a0);
      auVar26 = _lqc2(auStack_29f0);
      auVar25 = _lqc2(_auStack_210);
      auVar25 = _vsub(auVar25,auVar26);
      _auStack_210 = _sqc2(auVar25);
      fVar23 = (float)func_0x00222fd0(auStack_210);
      if (-((*(float *)(iVar15 + 0x164) + *(float *)(iVar15 + 0x3a4)) - *(float *)(iVar15 + 0x3b4))
          * 2.0 * 10.0 + *(float *)(iVar5 + 0x354) + *(float *)(iVar15 + 0x354) <= fVar23) {
        *(undefined2 *)(iVar17 + 0x1e) = 1;
      }
      else {
        *(undefined2 *)(iVar17 + 0x1e) = 2;
      }
    }
    __pl__7FVectorCFRC7FVector(&uStack_2a00,iVar15 + 0x160,iVar15 + 0x3a0);
    uStack_208._0_4_ = (float)uStack_29f8;
    _auStack_210 = uStack_2a00;
    uStack_208._4_4_ = (float)uStack_29f4;
    __pl__7FVectorCFRC7FVector(auStack_2a10,iVar5 + 0x160,iVar5 + 0x3a0);
    auVar26 = _lqc2(auStack_2a10);
    auVar25 = _lqc2(_auStack_210);
    auVar25 = _vsub(auVar25,auVar26);
    _auStack_210 = _sqc2(auVar25);
    FUN_004baab0(*(undefined4 *)(iGpffff8610 + 0x40b4),0,*(undefined4 *)(iGpffff8610 + 0x40bc),
                 0x3f800000,&uStack_2a20);
    fStack_1f8 = (float)uStack_2a18;
    auStack_200 = (undefined1  [8])uStack_2a20;
    uStack_1f4 = uStack_2a14;
    fVar23 = (float)func_0x00222fd0(auStack_210);
    fVar22 = (float)func_0x00222fd0(auStack_200);
    *(float *)(iVar17 + 0x84) = (fVar23 / (fVar22 * 0.75) + 1.2) * 512.0;
    if (*(short *)(iVar17 + 0x1e) == 2) {
      __pl__7FVectorCFRC7FVector(&uStack_2ab0,iVar15 + 0x160,iVar15 + 0x3a0);
      uStack_208._0_4_ = (float)uStack_2aa8;
      _auStack_210 = uStack_2ab0;
      uStack_208._4_4_ = (float)uStack_2aa4;
      __pl__7FVectorCFRC7FVector(auStack_2ac0,iVar5 + 0x160,iVar5 + 0x3a0);
      auVar26 = _lqc2(auStack_2ac0);
      auVar25 = _lqc2(_auStack_210);
      auVar25 = _vsub(auVar25,auVar26);
      _auStack_210 = _sqc2(auVar25);
      uVar8 = func_0x00222f00(auStack_2ae0,auStack_210);
      Get3DAngle__F7FVector(auStack_2ad0,uVar8);
      auVar25 = _vmr32(in_vf0);
      auVar26 = _vmr32(auVar25);
      auVar27 = _vmr32(auVar26);
      auStack_400 = _sqc2(in_vf0);
      auStack_410 = _sqc2(auVar25);
      auStack_420 = _sqc2(auVar26);
      auStack_430 = _sqc2(auVar27);
      uVar24 = func_0x00222e40(-fStack_2acc);
      func_0x00202938(uVar24,auStack_430,auStack_430);
      uVar8 = FUN_004baab0(*(float *)(iVar5 + 0x354) * 2.0,0,0,0x3f800000,auStack_2b00);
      func_0x00222df0(auStack_2af0,auStack_430,uVar8);
      fStack_1f0 = auStack_2af0._0_4_;
      fStack_1ec = auStack_2af0._4_4_;
      fStack_1e8 = (float)uStack_2ae8;
      uStack_1e4 = uStack_2ae4;
      uVar8 = FUN_004baab0(-*(float *)(iVar5 + 0x354) * 2.0,0,0,0x3f800000,auStack_2b20);
      func_0x00222df0(auStack_2b10,auStack_430,uVar8);
      fStack_1e0 = auStack_2b10._0_4_;
      fStack_1dc = auStack_2b10._4_4_;
      fStack_1d8 = (float)uStack_2b08;
      uStack_1d4 = uStack_2b04;
      __pl__7FVectorCFRC7FVector(auStack_2b40,iVar5 + 0x160,iVar5 + 0x3a0);
      __pl__7FVectorCFRC7FVector(auStack_2b30,auStack_2b40,&fStack_1f0);
      __pl__7FVectorCFRC7FVector(auStack_2b60,iVar15 + 0x160,iVar15 + 0x3a0);
      __mi__7FVectorCFRC7FVector(auStack_2b50,auStack_2b60,auStack_210);
      uVar8 = func_0x00222f00(auStack_2b80,auStack_200);
      Get3DAngle__F7FVector(&uStack_2b70,uVar8);
      fStack_1f8 = (float)uStack_2b68;
      auStack_200 = (undefined1  [8])uStack_2b70;
      uStack_1f4 = uStack_2b64;
      fVar23 = -(float)uStack_2b70;
      if ((fVar23 <= 40.0) && (fVar23 = fVar23 * 1.25 - 10.0, fVar23 < -10.0)) {
        fVar23 = -10.0;
      }
      fVar20 = (float)func_0x00222fd0(iVar5 + 0x3b0);
      fVar22 = *(float *)(iVar5 + 0x354);
      fVar21 = *(float *)(iVar17 + 0x84);
      auVar25 = _vmr32(in_vf0);
      auVar26 = _vmr32(auVar25);
      auVar27 = _vmr32(auVar26);
      auStack_400 = _sqc2(in_vf0);
      auStack_410 = _sqc2(auVar25);
      auStack_420 = _sqc2(auVar26);
      auStack_430 = _sqc2(auVar27);
      uVar24 = func_0x00222e40(fVar23);
      func_0x00202890(uVar24,auStack_430,auStack_430);
      uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
      func_0x00202938(uVar24,auStack_430,auStack_430);
      uVar8 = FUN_004baab0(0,0,-((fVar21 * (fVar22 + fVar20 + 20.0)) / 512.0),0x3f800000,
                           auStack_2ba0);
      func_0x00222df0(auStack_2b90,auStack_430,uVar8);
      __pl__7FVectorCFRC7FVector(&uStack_2bb0,auStack_210,auStack_200);
      afStack_30c[1] = (float)uStack_2ba8;
      _auStack_310 = uStack_2bb0;
      afStack_30c[2] = (float)uStack_2ba4;
      __pl__7FVectorCFRC7FVector(auStack_2bd0,iVar5 + 0x160,iVar5 + 0x3a0);
      __pl__7FVectorCFRC7FVector(auStack_2bc0,auStack_2bd0,&fStack_1e0);
      __pl__7FVectorCFRC7FVector(auStack_2bf0,iVar15 + 0x160,iVar15 + 0x3a0);
      __mi__7FVectorCFRC7FVector(auStack_2be0,auStack_2bf0,auStack_210);
      uVar8 = func_0x00222f00(auStack_2c10,auStack_200);
      Get3DAngle__F7FVector(&uStack_2c00,uVar8);
      fStack_1f8 = (float)uStack_2bf8;
      auStack_200 = (undefined1  [8])uStack_2c00;
      uStack_1f4 = uStack_2bf4;
      fVar23 = -(float)uStack_2c00;
      if ((fVar23 <= 40.0) && (fVar23 = fVar23 * 1.25 - 10.0, fVar23 < -10.0)) {
        fVar23 = -10.0;
      }
      fVar20 = (float)func_0x00222fd0(iVar5 + 0x3b0);
      fVar22 = *(float *)(iVar5 + 0x354);
      fVar21 = *(float *)(iVar17 + 0x84);
      auVar25 = _vmr32(in_vf0);
      auVar26 = _vmr32(auVar25);
      auVar27 = _vmr32(auVar26);
      auStack_400 = _sqc2(in_vf0);
      auStack_410 = _sqc2(auVar25);
      auStack_420 = _sqc2(auVar26);
      auStack_430 = _sqc2(auVar27);
      uVar24 = func_0x00222e40(fVar23);
      func_0x00202890(uVar24,auStack_430,auStack_430);
      uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
      func_0x00202938(uVar24,auStack_430,auStack_430);
      uVar8 = FUN_004baab0(0,0,-((fVar21 * (fVar22 + fVar20 + 20.0)) / 512.0),0x3f800000,
                           auStack_2c30);
      func_0x00222df0(auStack_2c20,auStack_430,uVar8);
      __pl__7FVectorCFRC7FVector(&uStack_2c40,auStack_210,auStack_200);
      auStack_300._8_4_ = uStack_2c38;
      auStack_300._0_8_ = uStack_2c40;
      auStack_300._12_4_ = uStack_2c34;
      __pl__7FVectorCFRC7FVector(auStack_2c60,iVar5 + 0x160,iVar5 + 0x3a0);
      __mi__7FVectorCFRC7FVector(auStack_2c50,auStack_2c60,auStack_310);
      uVar24 = func_0x00222fd0(auStack_210);
      uVar8 = func_0x00222f00(auStack_2c80,auStack_210);
      Get3DAngle__F7FVector(&uStack_2c70,uVar8);
      uStack_208._0_4_ = (float)uVar24;
      _auStack_210 = uStack_2c70;
      uStack_208._4_4_ = (float)uStack_2c64;
      __pl__7FVectorCFRC7FVector(auStack_2ca0,iVar15 + 0x160,iVar15 + 0x3a0);
      __mi__7FVectorCFRC7FVector(&uStack_2c90,auStack_2ca0,auStack_310);
      fStack_1f8 = (float)uStack_2c88;
      auStack_200 = (undefined1  [8])uStack_2c90;
      uStack_1f4 = uStack_2c84;
      auStack_200 = (undefined1  [8])(uStack_2c90 & 0xffffffff);
      uVar24 = func_0x00222fd0(auStack_200);
      uVar8 = func_0x00222f00(auStack_2cc0,auStack_200);
      Get3DAngle__F7FVector(&uStack_2cb0,uVar8);
      fStack_1f8 = (float)uVar24;
      auStack_200 = (undefined1  [8])uStack_2cb0;
      uStack_1f4 = uStack_2ca4;
      __pl__7FVectorCFRC7FVector(auStack_2ce0,iVar5 + 0x160,iVar5 + 0x3a0);
      __mi__7FVectorCFRC7FVector(auStack_2cd0,auStack_2ce0,auStack_300);
      fStack_1e8 = (float)uStack_2cc8;
      uStack_1e4 = uStack_2cc4;
      fStack_1ec = 0.0;
      fVar23 = (float)func_0x00222fd0(&fStack_1f0);
      uVar8 = func_0x00222f00(auStack_2d00,&fStack_1f0);
      Get3DAngle__F7FVector(auStack_2cf0,uVar8);
      fStack_1f0 = (float)auStack_2cf0._0_8_;
      fStack_1ec = SUB84(auStack_2cf0._0_8_,4);
      uStack_1e4 = uStack_2ce4;
      fStack_1e8 = fVar23;
      __pl__7FVectorCFRC7FVector(auStack_2d20,iVar15 + 0x160,iVar15 + 0x3a0);
      __mi__7FVectorCFRC7FVector(auStack_2d10,auStack_2d20,auStack_300);
      fStack_1d8 = (float)uStack_2d08;
      uStack_1d4 = uStack_2d04;
      fStack_1dc = 0.0;
      fVar23 = (float)func_0x00222fd0(&fStack_1e0);
      uVar8 = func_0x00222f00(auStack_2d40,&fStack_1e0);
      Get3DAngle__F7FVector(auStack_2d30,uVar8);
      fStack_1e0 = (float)auStack_2d30._0_8_;
      fStack_1dc = SUB84(auStack_2d30._0_8_,4);
      uStack_1d4 = uStack_2d24;
      iVar12 = 0;
      iVar18 = 0;
      fStack_1d8 = fVar23;
      for (iVar13 = 0; iVar13 < 0xc; iVar13 = iVar13 + 1) {
        if (((((*(byte *)(iGpffff8610 + iVar13 * 0x510 + 0xb0) & 1) != 0) &&
             ((long)((ulong)*(byte *)(iGpffff8610 + iVar13 * 0x510 + 0xb0) << 0x3e) < 0)) &&
            (-1 < (long)((ulong)*(byte *)(iGpffff8610 + iVar13 * 0x510 + 0xb2) << 0x3c))) &&
           ((iVar13 != *(int *)(iVar17 + 0xd0) && (iVar13 != *(int *)(iVar17 + 0xd4))))) {
          __pl__7FVectorCFRC7FVector
                    (auStack_2d60,iGpffff8610 + iVar13 * 0x510 + 0x160,
                     iGpffff8610 + iVar13 * 0x510 + 0x3a0);
          __mi__7FVectorCFRC7FVector(auStack_2d50,auStack_2d60,auStack_310);
          fStack_1d0 = auStack_2d50._0_4_;
          fStack_1cc = auStack_2d50._4_4_;
          uStack_1c8 = uStack_2d48;
          uStack_1c4 = uStack_2d44;
          fVar23 = (float)func_0x00222fd0(&fStack_1d0);
          uVar8 = func_0x00222f00(auStack_2d80,&fStack_1d0);
          Get3DAngle__F7FVector(auStack_2d70,uVar8);
          fStack_1d0 = auStack_2d70._0_4_;
          fStack_1cc = auStack_2d70._4_4_;
          uStack_1c8 = uStack_2d68;
          uStack_1c4 = uStack_2d64;
          if (fVar23 < (float)uStack_208 + *(float *)(iVar5 + 0x354) + 10.0) {
            for (fVar22 = fStack_1cc - fStack_20c; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
            }
            for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
            }
            if ((-60.0 <= fVar22) && (fVar22 <= 60.0)) {
              iVar12 = iVar12 + 1;
            }
          }
          if (fVar23 < fStack_1f8 + *(float *)(iVar15 + 0x354) + 10.0) {
            for (fVar23 = fStack_1cc - (float)auStack_200._4_4_; fVar23 < -180.0;
                fVar23 = fVar23 + 360.0) {
            }
            for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
            }
            if ((-60.0 <= fVar23) && (fVar23 <= 60.0)) {
              iVar12 = iVar12 + 1;
            }
          }
          __pl__7FVectorCFRC7FVector
                    (auStack_2da0,iGpffff8610 + iVar13 * 0x510 + 0x160,
                     iGpffff8610 + iVar13 * 0x510 + 0x3a0);
          __mi__7FVectorCFRC7FVector(auStack_2d90,auStack_2da0,auStack_300);
          fStack_1d0 = auStack_2d90._0_4_;
          fStack_1cc = auStack_2d90._4_4_;
          uStack_1c8 = uStack_2d88;
          uStack_1c4 = uStack_2d84;
          fVar23 = (float)func_0x00222fd0(&fStack_1d0);
          uVar8 = func_0x00222f00(auStack_2dc0,&fStack_1d0);
          Get3DAngle__F7FVector(auStack_2db0,uVar8);
          fStack_1d0 = auStack_2db0._0_4_;
          fStack_1cc = auStack_2db0._4_4_;
          uStack_1c8 = uStack_2da8;
          uStack_1c4 = uStack_2da4;
          if (fVar23 < fStack_1e8 + *(float *)(iVar5 + 0x354) + 10.0) {
            for (fVar22 = fStack_1cc - fStack_1ec; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
            }
            for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
            }
            if ((-60.0 <= fVar22) && (fVar22 <= 60.0)) {
              iVar18 = iVar18 + 1;
            }
          }
          if (fVar23 < fStack_1d8 + *(float *)(iVar15 + 0x354) + 10.0) {
            for (fVar23 = fStack_1cc - fStack_1dc; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
            }
            for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
            }
            if ((-60.0 <= fVar23) && (fVar23 <= 60.0)) {
              iVar18 = iVar18 + 1;
            }
          }
        }
      }
      if (iVar12 < iVar18) {
        *(int *)(iVar17 + 0x50) = auStack_310;
        *(int *)(iVar17 + 0x54) = auStack_310._4_4_;
        *(float *)(iVar17 + 0x58) = afStack_30c[1];
        *(float *)(iVar17 + 0x5c) = afStack_30c[2];
      }
      else if (iVar18 < iVar12) {
        *(int *)(iVar17 + 0x50) = auStack_300._0_4_;
        *(int *)(iVar17 + 0x54) = auStack_300._4_4_;
        *(undefined4 *)(iVar17 + 0x58) = auStack_300._8_4_;
        *(undefined4 *)(iVar17 + 0x5c) = auStack_300._12_4_;
      }
      else {
        fVar23 = (float)func_0x00222fd0(auStack_310);
        fVar22 = (float)func_0x00222fd0(auStack_300);
        if (fVar23 < fVar22) {
          *(int *)(iVar17 + 0x50) = auStack_310;
          *(int *)(iVar17 + 0x54) = auStack_310._4_4_;
          *(float *)(iVar17 + 0x58) = afStack_30c[1];
          *(float *)(iVar17 + 0x5c) = afStack_30c[2];
        }
        else {
          *(int *)(iVar17 + 0x50) = auStack_300._0_4_;
          *(int *)(iVar17 + 0x54) = auStack_300._4_4_;
          *(undefined4 *)(iVar17 + 0x58) = auStack_300._8_4_;
          *(undefined4 *)(iVar17 + 0x5c) = auStack_300._12_4_;
        }
      }
      if (-10.0 < *(float *)(iVar17 + 0x54)) {
        *(undefined4 *)(iVar17 + 0x54) = 0xc1200000;
      }
    }
    else if (*(short *)(iVar17 + 0x1e) == 1) {
      uVar8 = func_0x00222f00(auStack_2a40,auStack_210);
      Get3DAngle__F7FVector(&uStack_2a30,uVar8);
      fStack_1f8 = (float)uStack_2a28;
      auStack_200 = (undefined1  [8])uStack_2a30;
      uStack_1f4 = uStack_2a24;
      fVar23 = *(float *)(iVar5 + 0x3b4) * 0.75;
      if (fVar23 < 4.0) {
        fVar23 = 4.0;
      }
      fVar21 = (float)func_0x00222fd0(iVar5 + 0x3b0);
      fVar20 = *(float *)(iVar5 + 0x354);
      fVar19 = *(float *)(iVar17 + 0x84);
      fVar22 = -(float)auStack_200._0_4_;
      if ((fVar22 <= 40.0) && (fVar22 = fVar22 * 1.25 - 10.0, fVar22 < -10.0)) {
        fVar22 = -10.0;
      }
      auVar25 = _vmr32(in_vf0);
      auVar26 = _vmr32(auVar25);
      auVar27 = _vmr32(auVar26);
      auStack_400 = _sqc2(in_vf0);
      auStack_410 = _sqc2(auVar25);
      auStack_420 = _sqc2(auVar26);
      auStack_430 = _sqc2(auVar27);
      uVar24 = func_0x00222e40(fVar22);
      func_0x00202890(uVar24,auStack_430,auStack_430);
      uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
      func_0x00202938(uVar24,auStack_430,auStack_430);
      uVar8 = FUN_004baab0(0,0,-((fVar19 * (fVar20 + fVar21 + 20.0)) / 512.0),0x3f800000,
                           auStack_2a60);
      func_0x00222df0(&uStack_2a50,auStack_430,uVar8);
      uStack_208._0_4_ = (float)uStack_2a48;
      _auStack_210 = uStack_2a50;
      uStack_208._4_4_ = (float)uStack_2a44;
      __pl__7FVectorCFRC7FVector(auStack_2a90,auStack_210,iVar5 + 0x160);
      __pl__7FVectorCFRC7FVector(auStack_2a80,auStack_2a90,iVar5 + 0x3a0);
      uVar8 = FUN_004baab0(0,-*(float *)(iVar5 + 0x3b4) - fVar23,0,0x3f800000,auStack_2aa0);
      __pl__7FVectorCFRC7FVector(auStack_2a70,auStack_2a80,uVar8);
      *(int *)(iVar17 + 0x50) = auStack_2a70._0_4_;
      *(int *)(iVar17 + 0x54) = auStack_2a70._4_4_;
      *(undefined4 *)(iVar17 + 0x58) = uStack_2a68;
      *(undefined4 *)(iVar17 + 0x5c) = uStack_2a64;
      if (-10.0 < *(float *)(iVar17 + 0x54)) {
        *(undefined4 *)(iVar17 + 0x54) = 0xc1200000;
      }
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    __pl__7FVectorCFRC7FVector(auStack_2df0,iVar15 + 0x160,iVar15 + 0x3a0);
    uVar8 = FUN_004baab0(0,-*(float *)(iVar15 + 0x3b4),0,0x3f800000,auStack_2e00);
    __pl__7FVectorCFRC7FVector(auStack_2de0,auStack_2df0,uVar8);
    __mi__7FVectorCFRC7FVector(&uStack_2dd0,auStack_2de0,iVar17 + 0x50);
    uStack_208._0_4_ = (float)uStack_2dc8;
    _auStack_210 = uStack_2dd0;
    uStack_208._4_4_ = (float)uStack_2dc4;
    __pl__7FVectorCFRC7FVector(auStack_2e30,iVar15 + 0x160,iVar15 + 0x3a0);
    uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar15 + 0x3b4),0,0x3f800000,auStack_2e40);
    __pl__7FVectorCFRC7FVector(auStack_2e20,auStack_2e30,uVar8);
    __mi__7FVectorCFRC7FVector(&uStack_2e10,auStack_2e20,iVar17 + 0x50);
    fStack_1f8 = (float)uStack_2e08;
    auStack_200 = (undefined1  [8])uStack_2e10;
    uStack_1f4 = uStack_2e04;
    __pl__7FVectorCFRC7FVector(auStack_2e70,iVar5 + 0x160,iVar5 + 0x3a0);
    uVar8 = FUN_004baab0(0,-*(float *)(iVar5 + 0x3b4),0,0x3f800000,auStack_2e80);
    __pl__7FVectorCFRC7FVector(auStack_2e60,auStack_2e70,uVar8);
    __mi__7FVectorCFRC7FVector(auStack_2e50,auStack_2e60,iVar17 + 0x50);
    fStack_1f0 = auStack_2e50._0_4_;
    fStack_1ec = auStack_2e50._4_4_;
    fStack_1e8 = fStack_2e48;
    uStack_1e4 = uStack_2e44;
    __pl__7FVectorCFRC7FVector(auStack_2eb0,iVar5 + 0x160,iVar5 + 0x3a0);
    uVar8 = FUN_004baab0(0,*(float *)(iVar5 + 0x3b4) * 0.5,0,0x3f800000,auStack_2ec0);
    __pl__7FVectorCFRC7FVector(auStack_2ea0,auStack_2eb0,uVar8);
    __mi__7FVectorCFRC7FVector(auStack_2e90,auStack_2ea0,iVar17 + 0x50);
    fStack_1e0 = auStack_2e90._0_4_;
    fStack_1dc = auStack_2e90._4_4_;
    fStack_1d8 = fStack_2e88;
    uStack_1d4 = uStack_2e84;
    uVar8 = func_0x00222f00(auStack_2ee0,auStack_210);
    Get3DAngle__F7FVector(auStack_2ed0,uVar8);
    fStack_1d0 = auStack_2ed0._0_4_;
    fStack_1cc = auStack_2ed0._4_4_;
    uStack_1c8 = uStack_2ec8;
    uStack_1c4 = uStack_2ec4;
    uVar8 = func_0x00222f00(auStack_2f00,auStack_200);
    Get3DAngle__F7FVector(auStack_2ef0,uVar8);
    afStack_1c0[0] = auStack_2ef0._0_4_;
    afStack_1c0[1] = auStack_2ef0._4_4_;
    afStack_1c0[2] = (float)uStack_2ee8;
    afStack_1c0[3] = (float)uStack_2ee4;
    uVar8 = func_0x00222f00(auStack_2f20,&fStack_1f0);
    Get3DAngle__F7FVector(auStack_2f10,uVar8);
    afStack_1c0[4] = auStack_2f10._0_4_;
    afStack_1c0[5] = auStack_2f10._4_4_;
    afStack_1c0[6] = (float)uStack_2f08;
    afStack_1c0[7] = (float)uStack_2f04;
    uVar8 = func_0x00222f00(auStack_2f40,&fStack_1e0);
    Get3DAngle__F7FVector(auStack_2f30,uVar8);
    afStack_1c0[8] = (float)auStack_2f30._0_4_;
    afStack_1c0[9] = (float)auStack_2f30._4_4_;
    afStack_1c0[10] = (float)uStack_2f28;
    afStack_1c0[0xb] = (float)uStack_2f24;
    for (; fStack_1d0 < -180.0; fStack_1d0 = fStack_1d0 + 360.0) {
    }
    for (; 180.0 < fStack_1d0; fStack_1d0 = fStack_1d0 - 360.0) {
    }
    fVar23 = fStack_1d0;
    fVar22 = fStack_1d0;
    for (iVar5 = 5; iVar5 < 8; iVar5 = iVar5 + 1) {
      while (*(float *)(auStack_210 + iVar5 * 0x10) < -180.0) {
        *(float *)(auStack_210 + iVar5 * 0x10) = *(float *)(auStack_210 + iVar5 * 0x10) + 360.0;
      }
      while (180.0 < *(float *)(auStack_210 + iVar5 * 0x10)) {
        *(float *)(auStack_210 + iVar5 * 0x10) = *(float *)(auStack_210 + iVar5 * 0x10) - 360.0;
      }
      if (*(float *)(auStack_210 + iVar5 * 0x10) < fVar23) {
        fVar23 = *(float *)(auStack_210 + iVar5 * 0x10);
      }
      if (fVar22 < *(float *)(auStack_210 + iVar5 * 0x10)) {
        fVar22 = *(float *)(auStack_210 + iVar5 * 0x10);
      }
    }
    for (fVar22 = fVar22 - fVar23; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
    }
    for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
    }
    *(float *)(iVar17 + 0x60) = -(fVar23 + fVar22 / 2.0);
    while (*(float *)(iVar17 + 0x60) < -180.0) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 0x60)) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
    }
    for (fVar23 = fStack_1cc - afStack_1c0[5]; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
    }
    *(float *)(iVar17 + 100) = -(afStack_1c0[5] + fVar23 / 2.0);
    while (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    *(undefined4 *)(iVar17 + 0x68) = 0;
    break;
  case 0x12:
    iVar5 = iGpffff8610 + *(int *)(iVar17 + 0xd0) * 0x510;
    *(undefined4 *)(iVar17 + 0xd4) = *(undefined4 *)(iVar5 + 0xbc);
    iVar15 = iGpffff8610 + *(int *)(iVar17 + 0xd4) * 0x510;
    if (*(short *)(iVar17 + 0x1e) != 1) {
      if (*(short *)(iVar17 + 0x1e) != 0) break;
      *(undefined4 *)(iVar17 + 0xd8) = 0;
      *(undefined4 *)(iVar17 + 0xdc) = 0;
      fVar23 = (float)func_0x00222fd0(iVar5 + 0x370);
      fVar22 = (float)func_0x00222fd0(iVar15 + 0x370);
      *(float *)(iVar17 + 0xe0) = fVar23 + fVar22 + 15.0;
      __pl__7FVectorCFRC7FVector(&uStack_2f50,iVar15 + 0x360,iVar15 + 0x160);
      uStack_208._0_4_ = (float)uStack_2f48;
      _auStack_210 = uStack_2f50;
      uStack_208._4_4_ = (float)uStack_2f44;
      __pl__7FVectorCFRC7FVector(auStack_2f60,iVar5 + 0x360,iVar5 + 0x160);
      auVar26 = _lqc2(auStack_2f60);
      auVar25 = _lqc2(_auStack_210);
      auVar25 = _vsub(auVar25,auVar26);
      auVar25 = _sqc2(auVar25);
      fStack_20c = auVar25._4_4_;
      uStack_208 = auVar25._8_8_;
      auStack_210 = auVar25._0_4_;
      fStack_20c = fStack_20c / 2.0;
      fVar23 = (float)func_0x00222fd0(auStack_210);
      *(float *)(iVar17 + 0x80) =
           (*(float *)(iVar17 + 0x84) * (*(float *)(iVar17 + 0xe0) + fVar23 / 2.0)) / 512.0;
      uVar8 = func_0x00222f00(auStack_2f80,auStack_210);
      Get3DAngle__F7FVector(&uStack_2f70,uVar8);
      fStack_1f8 = (float)uStack_2f68;
      auStack_200 = (undefined1  [8])uStack_2f70;
      uStack_1f4 = uStack_2f64;
      *(int *)(iVar17 + 0xe4) = (int)((ulong)uStack_2f70 >> 0x20);
      *(undefined4 *)(iVar17 + 0xe8) = *(undefined4 *)(iVar17 + 0x84);
      *(undefined2 *)(iVar17 + 0x1e) = 1;
    }
    __pl__7FVectorCFRC7FVector(&uStack_2f90,iVar15 + 0x360,iVar15 + 0x160);
    uStack_208._0_4_ = (float)uStack_2f88;
    _auStack_210 = uStack_2f90;
    uStack_208._4_4_ = (float)uStack_2f84;
    __pl__7FVectorCFRC7FVector(auStack_2fa0,iVar5 + 0x360,iVar5 + 0x160);
    auVar26 = _lqc2(auStack_2fa0);
    auVar25 = _lqc2(_auStack_210);
    auVar25 = _vsub(auVar25,auVar26);
    auVar25 = _sqc2(auVar25);
    fStack_20c = auVar25._4_4_;
    uStack_208 = auVar25._8_8_;
    auStack_210 = auVar25._0_4_;
    fStack_20c = fStack_20c / 2.0;
    fVar23 = (float)func_0x00222fd0(auStack_210);
    *(float *)(iVar17 + 0x80) =
         *(float *)(iVar17 + 0x80) +
         ((*(float *)(iVar17 + 0x84) * (*(float *)(iVar17 + 0xe0) + fVar23 / 2.0)) / 512.0 -
         *(float *)(iVar17 + 0x80)) * 3.75 * *(float *)(iVar17 + 0x24);
    __pl__7FVectorCFRC7FVector(&uStack_2fb0,iVar15 + 0x3a0,iVar15 + 0x160);
    uStack_208._0_4_ = (float)uStack_2fa8;
    _auStack_210 = uStack_2fb0;
    uStack_208._4_4_ = (float)uStack_2fa4;
    __pl__7FVectorCFRC7FVector(auStack_2fc0,iVar5 + 0x3a0,iVar5 + 0x160);
    auVar26 = _lqc2(auStack_2fc0);
    auVar25 = _lqc2(_auStack_210);
    auVar25 = _vsub(auVar25,auVar26);
    auVar25 = _sqc2(auVar25);
    fStack_20c = auVar25._4_4_;
    uStack_208 = auVar25._8_8_;
    auStack_210 = auVar25._0_4_;
    fStack_20c = fStack_20c / 2.0;
    if (*(int *)(iVar17 + 0xd8) == 0) {
      uVar8 = func_0x00222f00(auStack_2fe0,auStack_210);
      Get3DAngle__F7FVector(&uStack_2fd0,uVar8);
      fVar23 = (float)((ulong)uStack_2fd0 >> 0x20);
      fStack_1f8 = (float)uStack_2fc8;
      auStack_200 = (undefined1  [8])uStack_2fd0;
      uStack_1f4 = uStack_2fc4;
      for (fVar22 = fVar23 - *(float *)(iVar17 + 0xe4); fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
      }
      for (; 180.0 <= fVar22; fVar22 = fVar22 - 360.0) {
      }
      if ((fVar22 <= *(float *)(iVar17 + 0x24) * -30.0) ||
         (*(float *)(iVar17 + 0x24) * 30.0 <= fVar22)) {
        if (0.0 < fVar22) {
          *(undefined4 *)(iVar17 + 0xd8) = 1;
          *(float *)(iVar17 + 0xe4) = *(float *)(iVar17 + 0xe4) + *(float *)(iVar17 + 0x24) * 24.0;
        }
        else {
          *(undefined4 *)(iVar17 + 0xd8) = 2;
          *(float *)(iVar17 + 0xe4) = *(float *)(iVar17 + 0xe4) - *(float *)(iVar17 + 0x24) * 24.0;
        }
      }
      else {
        *(float *)(iVar17 + 0xe4) = fVar23;
      }
    }
    else if (*(int *)(iVar17 + 0xd8) == 1) {
      *(float *)(iVar17 + 0xe4) = *(float *)(iVar17 + 0xe4) + *(float *)(iVar17 + 0x24) * 24.0;
    }
    else {
      *(float *)(iVar17 + 0xe4) = *(float *)(iVar17 + 0xe4) - *(float *)(iVar17 + 0x24) * 24.0;
    }
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    uVar24 = func_0x00222e40(0xc1200000);
    func_0x00202890(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(-*(float *)(iVar17 + 0xe4));
    func_0x00202938(uVar24,auStack_430,auStack_430);
    if (*(int *)(iVar17 + 0xdc) == 0) {
      uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_3000);
      func_0x00222df0(auStack_2ff0,auStack_430,uVar8);
      *(int *)(iVar17 + 0x50) = auStack_2ff0._0_4_;
      *(int *)(iVar17 + 0x54) = auStack_2ff0._4_4_;
      *(undefined4 *)(iVar17 + 0x58) = uStack_2fe8;
      *(undefined4 *)(iVar17 + 0x5c) = uStack_2fe4;
      __pl__7FVectorCFRC7FVector(&uStack_3010,iVar15 + 0x360,iVar15 + 0x160);
      uStack_208._0_4_ = (float)uStack_3008;
      _auStack_210 = uStack_3010;
      uStack_208._4_4_ = (float)uStack_3004;
      __pl__7FVectorCFRC7FVector(auStack_3020,iVar5 + 0x360,iVar5 + 0x160);
      auVar26 = _lqc2(auStack_3020);
      auVar25 = _lqc2(_auStack_210);
      auVar25 = _vsub(auVar25,auVar26);
      _auStack_210 = _sqc2(auVar25);
      func_0x00223030(0x40000000,auStack_210);
      fStack_20c = 0.0;
      uVar8 = FUN_004baab0(*(undefined4 *)(iVar5 + 0x160),0,*(undefined4 *)(iVar5 + 0x168),
                           0x3f800000,auStack_3040);
      __pl__7FVectorCFRC7FVector(auStack_3030,iVar5 + 0x360,uVar8);
      auVar26 = _lqc2(auStack_3030);
      auVar25 = _lqc2(_auStack_210);
      auVar25 = _vadd(auVar25,auVar26);
      _auStack_210 = _sqc2(auVar25);
      auVar26 = _lqc2(_auStack_210);
      auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _vadd(auVar25,auVar26);
      auVar25 = _sqc2(auVar25);
      *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    }
    else {
      uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_3060);
      func_0x00222df0(&uStack_3050,auStack_430,uVar8);
      uStack_208._0_4_ = (float)uStack_3048;
      _auStack_210 = uStack_3050;
      uStack_208._4_4_ = (float)uStack_3044;
      __pl__7FVectorCFRC7FVector(&uStack_3070,iVar15 + 0x360,iVar15 + 0x160);
      fStack_1f8 = (float)uStack_3068;
      auStack_200 = (undefined1  [8])uStack_3070;
      uStack_1f4 = uStack_3064;
      __pl__7FVectorCFRC7FVector(auStack_3080,iVar5 + 0x360,iVar5 + 0x160);
      auVar26 = _lqc2(auStack_3080);
      auVar25 = _lqc2(_auStack_200);
      auVar25 = _vsub(auVar25,auVar26);
      _auStack_200 = _sqc2(auVar25);
      func_0x00223030(0x40000000,auStack_200);
      auStack_200._4_4_ = 0;
      uVar8 = FUN_004baab0(*(undefined4 *)(iVar5 + 0x160),0,*(undefined4 *)(iVar5 + 0x168),
                           0x3f800000,auStack_30a0);
      __pl__7FVectorCFRC7FVector(auStack_3090,iVar5 + 0x360,uVar8);
      auVar26 = _lqc2(auStack_3090);
      auVar25 = _lqc2(_auStack_200);
      auVar25 = _vadd(auVar25,auVar26);
      _auStack_200 = _sqc2(auVar25);
      auVar26 = _lqc2(_auStack_200);
      auVar25 = _lqc2(_auStack_210);
      auVar25 = _vadd(auVar25,auVar26);
      auVar25 = _sqc2(auVar25);
      auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _lqc2(auVar25);
      auVar25 = _vsub(auVar25,auVar26);
      _auStack_210 = _sqc2(auVar25);
      __ml__7FVectorCFf(*(float *)(iVar17 + 0x24) * 7.5,auStack_30b0,auStack_210);
      auVar26 = _lqc2(auStack_30b0);
      auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _vadd(auVar25,auVar26);
      auVar25 = _sqc2(auVar25);
      *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    __pl__7FVectorCFRC7FVector(auStack_30d0,iVar5 + 0x360,iVar5 + 0x160);
    __mi__7FVectorCFRC7FVector(&uStack_30c0,auStack_30d0,iVar17 + 0x50);
    uStack_208._0_4_ = (float)uStack_30b8;
    _auStack_210 = uStack_30c0;
    uStack_208._4_4_ = (float)uStack_30b4;
    __pl__7FVectorCFRC7FVector(auStack_30f0,iVar15 + 0x360,iVar15 + 0x160);
    __mi__7FVectorCFRC7FVector(&uStack_30e0,auStack_30f0,iVar17 + 0x50);
    fStack_1f8 = (float)uStack_30d8;
    auStack_200 = (undefined1  [8])uStack_30e0;
    uStack_1f4 = uStack_30d4;
    uVar8 = func_0x00222f00(auStack_3110,auStack_210);
    Get3DAngle__F7FVector(auStack_3100,uVar8);
    fStack_1f0 = auStack_3100._0_4_;
    fStack_1ec = auStack_3100._4_4_;
    fStack_1e8 = fStack_30f8;
    uStack_1e4 = uStack_30f4;
    uVar8 = func_0x00222f00(auStack_3130,auStack_200);
    Get3DAngle__F7FVector(auStack_3120,uVar8);
    fStack_1e0 = auStack_3120._0_4_;
    fStack_1dc = auStack_3120._4_4_;
    fStack_1d8 = fStack_3118;
    uStack_1d4 = uStack_3114;
    for (fVar23 = fStack_1e0 - fStack_1f0; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 <= fVar23; fVar23 = fVar23 - 360.0) {
    }
    if (*(int *)(iVar17 + 0xdc) == 0) {
      *(float *)(iVar17 + 0x60) = -(fStack_1f0 + fVar23 / 2.0);
    }
    else {
      for (fVar23 = -(fStack_1f0 + fVar23 / 2.0) - *(float *)(iVar17 + 0x60); fVar23 < -180.0;
          fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 <= fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 0x60) =
           *(float *)(iVar17 + 0x60) + fVar23 * 7.5 * *(float *)(iVar17 + 0x24);
    }
    while (*(float *)(iVar17 + 0x60) < -180.0) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
    }
    while (180.0 <= *(float *)(iVar17 + 0x60)) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
    }
    for (fVar23 = fStack_1dc - fStack_1ec; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 <= fVar23; fVar23 = fVar23 - 360.0) {
    }
    if (*(int *)(iVar17 + 0xdc) == 0) {
      *(float *)(iVar17 + 100) = -(fStack_1ec + fVar23 / 2.0);
    }
    else {
      for (fVar23 = -(fStack_1ec + fVar23 / 2.0) - *(float *)(iVar17 + 100); fVar23 < -180.0;
          fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 <= fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + fVar23 * 7.5 * *(float *)(iVar17 + 0x24)
      ;
    }
    while (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    while (180.0 <= *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    *(undefined4 *)(iVar17 + 0x68) = 0;
    *(undefined4 *)(iVar17 + 0xdc) = 1;
    break;
  case 0x13:
    FUN_005ad3b0(param_1);
    break;
  case 0x14:
    FUN_005b6fa0(param_1);
    break;
  case 0x15:
    FUN_005bd330(param_1);
    break;
  case 0x16:
    iVar5 = iGpffff8610 + *(int *)(iVar17 + 0xd0) * 0x510;
    if (*(short *)(iVar17 + 0x1e) != 1) {
      if (*(short *)(iVar17 + 0x1e) != 0) break;
      __pl__7FVectorCFRC7FVector(auStack_3150,iVar5 + 0x160,iVar5 + 0x3a0);
      __mi__7FVectorCFRC7FVector(&uStack_3140,auStack_3150,iVar17 + 0x100);
      uStack_208._0_4_ = (float)uStack_3138;
      _auStack_210 = uStack_3140;
      uStack_208._4_4_ = (float)uStack_3134;
      _auStack_210 = uStack_3140 & 0xffffffff;
      uVar8 = func_0x00222f00(auStack_3170,auStack_210);
      Get3DAngle__F7FVector(auStack_3160,uVar8);
      fStack_370 = auStack_3160._0_4_;
      fStack_36c = auStack_3160._4_4_;
      fStack_368 = fStack_3158;
      fStack_364 = fStack_3154;
      *(float *)(iVar17 + 0xe0) = fStack_36c;
      *(undefined4 *)(iVar17 + 0xe4) = 0xc1a00000;
      auVar25 = _vmr32(in_vf0);
      auVar26 = _vmr32(auVar25);
      auVar27 = _vmr32(auVar26);
      auStack_400 = _sqc2(in_vf0);
      auStack_410 = _sqc2(auVar25);
      auStack_420 = _sqc2(auVar26);
      auStack_430 = _sqc2(auVar27);
      func_0x00202890(0xbeb2b8c3,auStack_430,auStack_430);
      uVar24 = func_0x00222e40(-*(float *)(iVar17 + 0xe0));
      func_0x00202938(uVar24,auStack_430,auStack_430);
      fVar23 = (float)func_0x00222fd0(iVar5 + 0x3b0);
      *(float *)(iVar17 + 0x80) = *(float *)(iVar5 + 0x354) + fVar23 + 50.0;
      uVar8 = FUN_004baab0(0,0,(-*(float *)(iVar17 + 0x80) * *(float *)(iVar17 + 0x84)) / 512.0,
                           0x3f800000,auStack_3190);
      func_0x00222df0(auStack_3180,auStack_430,uVar8);
      *(int *)(iVar17 + 0x50) = auStack_3180._0_4_;
      *(int *)(iVar17 + 0x54) = auStack_3180._4_4_;
      *(undefined4 *)(iVar17 + 0x58) = uStack_3178;
      *(undefined4 *)(iVar17 + 0x5c) = uStack_3174;
      *(int *)(iVar17 + 0x70) = (int)*(undefined8 *)(iVar17 + 0x100);
      *(int *)(iVar17 + 0x74) = (int)((ulong)*(undefined8 *)(iVar17 + 0x100) >> 0x20);
      *(undefined4 *)(iVar17 + 0x78) = *(undefined4 *)(iVar17 + 0x108);
      *(undefined4 *)(iVar17 + 0x7c) = *(undefined4 *)(iVar17 + 0x10c);
      *(undefined4 *)(iVar17 + 0x74) = *(undefined4 *)(iVar5 + 0x3a4);
      auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
      auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _vadd(auVar25,auVar26);
      auVar25 = _sqc2(auVar25);
      *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
      CameraYPosCheck__9BtlCameraFv(param_1);
      __mi__7FVectorCFRC7FVector(auStack_31a0,iVar17 + 0x100,iVar17 + 0x50);
      __pl__7FVectorCFRC7FVector(auStack_31c0,iVar5 + 0x160,iVar5 + 0x3a0);
      __mi__7FVectorCFRC7FVector(auStack_31b0,auStack_31c0,iVar17 + 0x50);
      uVar8 = func_0x00222f00(auStack_31e0,auStack_210);
      Get3DAngle__F7FVector(auStack_31d0,uVar8);
      fStack_1f0 = auStack_31d0._0_4_;
      fStack_1ec = auStack_31d0._4_4_;
      fStack_1e8 = fStack_31c8;
      uStack_1e4 = uStack_31c4;
      uVar8 = func_0x00222f00(auStack_3200,auStack_200);
      Get3DAngle__F7FVector(auStack_31f0,uVar8);
      fStack_1e0 = auStack_31f0._0_4_;
      fStack_1dc = auStack_31f0._4_4_;
      fStack_1d8 = fStack_31e8;
      uStack_1d4 = uStack_31e4;
      for (fVar23 = fStack_1f0 - fStack_1e0; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 0x60) = -(fStack_1e0 + fVar23 / 2.0);
      while (*(float *)(iVar17 + 0x60) < -180.0) {
        *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
      }
      while (180.0 < *(float *)(iVar17 + 0x60)) {
        *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
      }
      for (fVar23 = fStack_1ec - fStack_1dc; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 100) = -(fStack_1dc + fVar23 / 2.0);
      while (*(float *)(iVar17 + 100) < -180.0) {
        *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
      }
      while (180.0 < *(float *)(iVar17 + 100)) {
        *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
      }
      *(undefined4 *)(iVar17 + 0x68) = 0;
      *(undefined2 *)(iVar17 + 0x1e) = 1;
    }
    __pl__7FVectorCFRC7FVector(auStack_3220,iVar5 + 0x160,iVar5 + 0x3a0);
    __mi__7FVectorCFRC7FVector(&uStack_3210,auStack_3220,iVar17 + 0x100);
    uStack_208._0_4_ = (float)uStack_3208;
    _auStack_210 = uStack_3210;
    uStack_208._4_4_ = (float)uStack_3204;
    _auStack_210 = uStack_3210 & 0xffffffff;
    uVar8 = func_0x00222f00(auStack_3240,auStack_210);
    Get3DAngle__F7FVector(auStack_3230,uVar8);
    fStack_370 = auStack_3230._0_4_;
    fStack_36c = auStack_3230._4_4_;
    fStack_368 = fStack_3228;
    fStack_364 = fStack_3224;
    for (fVar23 = fStack_36c - *(float *)(iVar17 + 0xe0); fVar23 < -180.0; fVar23 = fVar23 + 360.0)
    {
    }
    for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
    }
    if (0.0 <= fVar23) {
      if (*(float *)(iVar17 + 0x24) * 30.0 < fVar23) {
        fVar23 = *(float *)(iVar17 + 0x24) * 30.0;
      }
    }
    else if (fVar23 < *(float *)(iVar17 + 0x24) * -30.0) {
      fVar23 = *(float *)(iVar17 + 0x24) * -30.0;
    }
    *(float *)(iVar17 + 0xe0) = *(float *)(iVar17 + 0xe0) + fVar23;
    *(float *)(iVar17 + 0xe4) =
         *(float *)(iVar17 + 0xe4) +
         ((-60.0 - *(float *)(iVar17 + 0xe4)) / 40.0) * *(float *)(iVar17 + 0x24) * 60.0;
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0xe4));
    func_0x00202890(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(-*(float *)(iVar17 + 0xe0));
    func_0x00202938(uVar24,auStack_430,auStack_430);
    uVar8 = FUN_004baab0(0,0,(-*(float *)(iVar17 + 0x80) * *(float *)(iVar17 + 0x84)) / 512.0,
                         0x3f800000,auStack_3260);
    func_0x00222df0(auStack_3250,auStack_430,uVar8);
    *(int *)(iVar17 + 0x50) = auStack_3250._0_4_;
    *(int *)(iVar17 + 0x54) = auStack_3250._4_4_;
    *(undefined4 *)(iVar17 + 0x58) = uStack_3248;
    *(undefined4 *)(iVar17 + 0x5c) = uStack_3244;
    auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
    auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
    auVar25 = _vadd(auVar25,auVar26);
    auVar25 = _sqc2(auVar25);
    *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    CameraYPosCheck__9BtlCameraFv(param_1);
    __mi__7FVectorCFRC7FVector(&uStack_3270,iVar17 + 0x100,iVar17 + 0x50);
    uStack_208._0_4_ = (float)uStack_3268;
    _auStack_210 = uStack_3270;
    uStack_208._4_4_ = (float)uStack_3264;
    __pl__7FVectorCFRC7FVector(auStack_3290,iVar5 + 0x160,iVar5 + 0x3a0);
    __mi__7FVectorCFRC7FVector(&uStack_3280,auStack_3290,iVar17 + 0x50);
    fStack_1f8 = (float)uStack_3278;
    auStack_200 = (undefined1  [8])uStack_3280;
    uStack_1f4 = uStack_3274;
    uVar8 = func_0x00222f00(auStack_32b0,auStack_210);
    Get3DAngle__F7FVector(auStack_32a0,uVar8);
    fStack_1f0 = auStack_32a0._0_4_;
    fStack_1ec = auStack_32a0._4_4_;
    fStack_1e8 = fStack_3298;
    uStack_1e4 = uStack_3294;
    uVar8 = func_0x00222f00(auStack_32d0,auStack_200);
    Get3DAngle__F7FVector(auStack_32c0,uVar8);
    fStack_1e0 = auStack_32c0._0_4_;
    fStack_1dc = auStack_32c0._4_4_;
    fStack_1d8 = fStack_32b8;
    uStack_1d4 = uStack_32b4;
    for (fVar23 = fStack_1f0 - fStack_1e0; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
    }
    for (fVar23 = -(fStack_1e0 + fVar23 / 2.0) - *(float *)(iVar17 + 0x60); fVar23 < -180.0;
        fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
    }
    if (0.0 <= fVar23) {
      if (*(float *)(iVar17 + 0x24) * 30.0 < fVar23) {
        fVar23 = *(float *)(iVar17 + 0x24) * 30.0;
      }
    }
    else if (fVar23 < *(float *)(iVar17 + 0x24) * -30.0) {
      fVar23 = *(float *)(iVar17 + 0x24) * -30.0;
    }
    *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + fVar23;
    while (*(float *)(iVar17 + 0x60) < -180.0) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 0x60)) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
    }
    for (fVar23 = fStack_1ec - fStack_1dc; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
    }
    for (fVar23 = -(fStack_1dc + fVar23 / 2.0) - *(float *)(iVar17 + 100); fVar23 < -180.0;
        fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
    }
    if (0.0 <= fVar23) {
      if (*(float *)(iVar17 + 0x24) * 30.0 < fVar23) {
        fVar23 = *(float *)(iVar17 + 0x24) * 30.0;
      }
    }
    else if (fVar23 < *(float *)(iVar17 + 0x24) * -30.0) {
      fVar23 = *(float *)(iVar17 + 0x24) * -30.0;
    }
    *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + fVar23;
    while (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    *(undefined4 *)(iVar17 + 0x68) = 0;
    break;
  case 0x17:
    iVar5 = 0;
    for (uVar14 = 0; (int)uVar14 < 0xc; uVar14 = uVar14 + 1) {
      if ((*(uint *)(iVar17 + 0xd0) & 1 << (uVar14 & 0x1f)) != 0) {
        __pl__7FVectorCFRC7FVector
                  (auStack_32e0,iGpffff8610 + uVar14 * 0x510 + 0x160,
                   iGpffff8610 + uVar14 * 0x510 + 0x3a0);
        iVar15 = iVar5 * 0x10;
        *(int *)(auStack_210 + iVar15) = auStack_32e0._0_4_;
        *(int *)(auStack_210 + iVar15 + 4) = auStack_32e0._4_4_;
        *(undefined4 *)(auStack_210 + iVar15 + 8) = uStack_32d8;
        *(undefined4 *)(auStack_210 + iVar15 + 0xc) = uStack_32d4;
        *(undefined4 *)(auStack_310 + iVar5 * 0x10) =
             *(undefined4 *)(iGpffff8610 + uVar14 * 0x510 + 0x354);
        *(undefined4 *)(auStack_310 + iVar5 * 0x10 + 4) =
             *(undefined4 *)(iGpffff8610 + uVar14 * 0x510 + 0x3b4);
        iVar5 = iVar5 + 1;
      }
    }
    _auStack_380 = _auStack_210;
    for (iVar15 = 1; iVar15 < iVar5; iVar15 = iVar15 + 1) {
      auVar26 = _lqc2(*(undefined1 (*) [16])(auStack_210 + iVar15 * 0x10));
      auVar25 = _lqc2(_auStack_380);
      auVar25 = _vadd(auVar25,auVar26);
      _auStack_380 = _sqc2(auVar25);
    }
    func_0x00223030((float)iVar5,auStack_380);
    FUN_004baab0(0,0,0,0x3f800000,auStack_32f0);
    fStack_390 = auStack_32f0._0_4_;
    fStack_38c = auStack_32f0._4_4_;
    fStack_388 = (float)uStack_32e8;
    fStack_384 = fStack_32e4;
    for (iVar15 = 0; iVar15 < iVar5; iVar15 = iVar15 + 1) {
      __mi__7FVectorCFRC7FVector(auStack_3300,auStack_210 + iVar15 * 0x10,auStack_380);
      fStack_110 = auStack_3300._0_4_;
      fStack_108 = fStack_32f8;
      fStack_104 = fStack_32f4;
      fStack_10c = 0.0;
      fVar22 = (float)func_0x00222fd0(&fStack_110);
      fVar23 = *(float *)(auStack_310 + iVar15 * 0x10) + fVar22;
      if (*(float *)(auStack_310 + iVar15 * 0x10) + fVar22 <= fStack_390) {
        fVar23 = fStack_390;
      }
      fStack_390 = fVar23;
      fStack_110 = *(float *)(auStack_210 + iVar15 * 0x10 + 4) -
                   *(float *)(auStack_310 + iVar15 * 0x10 + 4);
      fStack_110 = (*(float *)(auStack_210 + iVar15 * 0x10 + 4) -
                   *(float *)(auStack_310 + iVar15 * 0x10 + 4)) - (float)auStack_380._4_4_;
      fStack_10c = (*(float *)(auStack_210 + iVar15 * 0x10 + 4) +
                   *(float *)(auStack_310 + iVar15 * 0x10 + 4)) - (float)auStack_380._4_4_;
      if (fStack_110 < 0.0) {
        fStack_110 = fStack_110 * -1.0;
      }
      if (fStack_10c < 0.0) {
        fStack_10c = fStack_10c * -1.0;
      }
      if (fStack_38c < fStack_110) {
        fStack_38c = fStack_110;
      }
      if (fStack_38c < fStack_10c) {
        fStack_38c = fStack_10c;
      }
    }
    fStack_388 = fStack_390;
    *(int *)(iVar17 + 0x70) = auStack_380._0_4_;
    *(int *)(iVar17 + 0x74) = auStack_380._4_4_;
    *(float *)(iVar17 + 0x78) = fStack_378;
    *(float *)(iVar17 + 0x7c) = fStack_374;
    fVar23 = (float)func_0x00222fd0(&fStack_390);
    *(float *)(iVar17 + 0x80) = (*(float *)(iVar17 + 0x84) * (fStack_390 + fVar23 + 35.0)) / 512.0;
    if (*(int *)(iVar17 + 0xdc) == 0) {
      iVar5 = 0;
      for (fVar23 = -3.1415927; fVar23 <= 2.3561945; fVar23 = fVar23 + 0.7853982) {
        auVar25 = _vmr32(in_vf0);
        auVar26 = _vmr32(auVar25);
        auVar27 = _vmr32(auVar26);
        auStack_400 = _sqc2(in_vf0);
        auStack_410 = _sqc2(auVar25);
        auStack_420 = _sqc2(auVar26);
        auStack_430 = _sqc2(auVar27);
        uVar24 = func_0x00222e40(0xc20c0000);
        func_0x00202890(uVar24,auStack_430,auStack_430);
        func_0x00202938(fVar23,auStack_430,auStack_430);
        uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_3330);
        func_0x00222df0(auStack_3320,auStack_430,uVar8);
        __pl__7FVectorCFRC7FVector(auStack_3310,auStack_3320,iVar17 + 0x70);
        iVar15 = iVar5 * 0x10;
        *(int *)(auStack_210 + iVar15) = auStack_3310._0_4_;
        *(int *)(auStack_210 + iVar15 + 4) = auStack_3310._4_4_;
        *(undefined4 *)(auStack_210 + iVar15 + 8) = uStack_3308;
        *(undefined4 *)(auStack_210 + iVar15 + 0xc) = uStack_3304;
        fVar20 = *(float *)(iGpffff8610 + 0x40b4) / 2.0 + *(float *)(auStack_210 + iVar5 * 0x10);
        fVar22 = *(float *)(iGpffff8610 + 0x40b4) / 2.0 - *(float *)(auStack_210 + iVar5 * 0x10);
        if (fVar20 <= fVar22) {
          fVar22 = fVar20;
        }
        *(float *)(auStack_310 + iVar5 * 0x10) = fVar22;
        fVar20 = *(float *)(iGpffff8610 + 0x40bc) / 2.0 + *(float *)(auStack_210 + iVar5 * 0x10 + 8)
        ;
        fVar22 = *(float *)(iGpffff8610 + 0x40bc) / 2.0 - *(float *)(auStack_210 + iVar5 * 0x10 + 8)
        ;
        if (fVar20 <= fVar22) {
          fVar22 = fVar20;
        }
        *(float *)(auStack_310 + iVar5 * 0x10 + 8) = fVar22;
        *(float *)(auStack_310 + iVar5 * 0x10 + 4) = fVar23;
        if ((10.0 < *(float *)(auStack_310 + iVar5 * 0x10)) &&
           (10.0 < *(float *)(auStack_310 + iVar5 * 0x10 + 8))) {
          iVar5 = iVar5 + 1;
        }
      }
      iVar15 = func_0x00232cc8();
      iVar15 = (int)((float)iVar5 * ((float)iVar15 / 2.1474836e+09));
      iVar5 = iVar15 * 0x10;
      uVar8 = *(undefined8 *)(auStack_210 + iVar5);
      uVar24 = *(undefined4 *)(auStack_210 + iVar5 + 8);
      uVar9 = *(undefined4 *)(auStack_210 + iVar5 + 0xc);
      *(int *)(iVar17 + 0x50) = (int)uVar8;
      *(int *)(iVar17 + 0x54) = (int)((ulong)uVar8 >> 0x20);
      *(undefined4 *)(iVar17 + 0x58) = uVar24;
      *(undefined4 *)(iVar17 + 0x5c) = uVar9;
      *(undefined4 *)(iVar17 + 0xe0) = *(undefined4 *)(auStack_310 + iVar15 * 0x10 + 4);
    }
    else {
      auVar25 = _vmr32(in_vf0);
      auVar26 = _vmr32(auVar25);
      auVar27 = _vmr32(auVar26);
      auStack_400 = _sqc2(in_vf0);
      auStack_410 = _sqc2(auVar25);
      auStack_420 = _sqc2(auVar26);
      auStack_430 = _sqc2(auVar27);
      uVar24 = func_0x00222e40(0xc20c0000);
      func_0x00202890(uVar24,auStack_430,auStack_430);
      func_0x00202938(*(undefined4 *)(iVar17 + 0xe0),auStack_430,auStack_430);
      uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_3360);
      func_0x00222df0(auStack_3350,auStack_430,uVar8);
      __pl__7FVectorCFRC7FVector(&uStack_3340,auStack_3350,iVar17 + 0x70);
      uStack_208._0_4_ = (float)uStack_3338;
      _auStack_210 = uStack_3340;
      uStack_208._4_4_ = (float)uStack_3334;
      auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _lqc2(_auStack_210);
      auVar25 = _vsub(auVar25,auVar26);
      _auStack_210 = _sqc2(auVar25);
      func_0x00223030(0x40800000,auStack_210);
      auVar26 = _lqc2(_auStack_210);
      auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _vadd(auVar25,auVar26);
      auVar25 = _sqc2(auVar25);
      *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    __mi__7FVectorCFRC7FVector(&uStack_3370,iVar17 + 0x70,iVar17 + 0x50);
    uStack_208._0_4_ = (float)uStack_3368;
    _auStack_210 = uStack_3370;
    uStack_208._4_4_ = (float)uStack_3364;
    uVar8 = func_0x00222f00(auStack_3390,auStack_210);
    Get3DAngle__F7FVector(&uStack_3380,uVar8);
    fStack_1f8 = (float)uStack_3378;
    auStack_200 = (undefined1  [8])uStack_3380;
    uStack_1f4 = uStack_3374;
    auVar25 = _auStack_200;
    auStack_200._0_4_ = (undefined4)uStack_3380;
    auStack_200._4_4_ = (undefined4)((ulong)uStack_3380 >> 0x20);
    if (*(int *)(iVar17 + 0xdc) == 0) {
      *(float *)(iVar17 + 0x60) = -(float)auStack_200._0_4_;
      *(float *)(iVar17 + 100) = -(float)auStack_200._4_4_;
    }
    else {
      for (fVar23 = -(float)auStack_200._0_4_ - *(float *)(iVar17 + 0x60); fVar23 < -180.0;
          fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 0x60) =
           *(float *)(iVar17 + 0x60) + fVar23 * 7.5 * *(float *)(iVar17 + 0x24);
      for (fVar23 = -(float)auStack_200._4_4_ - *(float *)(iVar17 + 100); fVar23 < -180.0;
          fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + fVar23 * 7.5 * *(float *)(iVar17 + 0x24)
      ;
    }
    while (*(float *)(iVar17 + 0x60) < -180.0) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 0x60)) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
    }
    while (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    *(undefined4 *)(iVar17 + 0x68) = 0;
    *(undefined4 *)(iVar17 + 0xdc) = 1;
    _auStack_200 = auVar25;
    break;
  case 0x18:
    iVar5 = 0;
    for (uVar14 = 0; (int)uVar14 < 0xc; uVar14 = uVar14 + 1) {
      if ((*(uint *)(iVar17 + 0xd0) & 1 << (uVar14 & 0x1f)) != 0) {
        __pl__7FVectorCFRC7FVector
                  (auStack_33a0,iGpffff8610 + uVar14 * 0x510 + 0x160,
                   iGpffff8610 + uVar14 * 0x510 + 0x3a0);
        iVar15 = iVar5 * 0x10;
        *(int *)(auStack_210 + iVar15) = auStack_33a0._0_4_;
        *(int *)(auStack_210 + iVar15 + 4) = auStack_33a0._4_4_;
        *(undefined4 *)(auStack_210 + iVar15 + 8) = uStack_3398;
        *(undefined4 *)(auStack_210 + iVar15 + 0xc) = uStack_3394;
        *(undefined4 *)(auStack_310 + iVar5 * 0x10) =
             *(undefined4 *)(iGpffff8610 + uVar14 * 0x510 + 0x354);
        *(undefined4 *)(auStack_310 + iVar5 * 0x10 + 4) =
             *(undefined4 *)(iGpffff8610 + uVar14 * 0x510 + 0x3b4);
        iVar5 = iVar5 + 1;
      }
    }
    _auStack_380 = _auStack_210;
    for (iVar15 = 1; iVar15 < iVar5; iVar15 = iVar15 + 1) {
      auVar26 = _lqc2(*(undefined1 (*) [16])(auStack_210 + iVar15 * 0x10));
      auVar25 = _lqc2(_auStack_380);
      auVar25 = _vadd(auVar25,auVar26);
      _auStack_380 = _sqc2(auVar25);
    }
    func_0x00223030((float)iVar5,auStack_380);
    FUN_004baab0(0,0,0,0x3f800000,auStack_33b0);
    fStack_390 = auStack_33b0._0_4_;
    fStack_38c = auStack_33b0._4_4_;
    fStack_388 = (float)uStack_33a8;
    fStack_384 = fStack_33a4;
    for (iVar15 = 0; iVar15 < iVar5; iVar15 = iVar15 + 1) {
      __mi__7FVectorCFRC7FVector(auStack_33c0,auStack_210 + iVar15 * 0x10,auStack_380);
      fStack_110 = auStack_33c0._0_4_;
      fStack_108 = fStack_33b8;
      fStack_104 = fStack_33b4;
      fStack_10c = 0.0;
      fVar22 = (float)func_0x00222fd0(&fStack_110);
      fVar23 = *(float *)(auStack_310 + iVar15 * 0x10) + fVar22;
      if (*(float *)(auStack_310 + iVar15 * 0x10) + fVar22 <= fStack_390) {
        fVar23 = fStack_390;
      }
      fStack_390 = fVar23;
      fStack_110 = *(float *)(auStack_210 + iVar15 * 0x10 + 4) -
                   *(float *)(auStack_310 + iVar15 * 0x10 + 4);
      fStack_110 = (*(float *)(auStack_210 + iVar15 * 0x10 + 4) -
                   *(float *)(auStack_310 + iVar15 * 0x10 + 4)) - (float)auStack_380._4_4_;
      fStack_10c = (*(float *)(auStack_210 + iVar15 * 0x10 + 4) +
                   *(float *)(auStack_310 + iVar15 * 0x10 + 4)) - (float)auStack_380._4_4_;
      if (fStack_110 < 0.0) {
        fStack_110 = fStack_110 * -1.0;
      }
      if (fStack_10c < 0.0) {
        fStack_10c = fStack_10c * -1.0;
      }
      if (fStack_38c < fStack_110) {
        fStack_38c = fStack_110;
      }
      if (fStack_38c < fStack_10c) {
        fStack_38c = fStack_10c;
      }
    }
    fStack_388 = fStack_390;
    iVar5 = iGpffff8610 + *(int *)(iVar17 + 0xd4) * 0x510;
    __pl__7FVectorCFRC7FVector(&uStack_33d0,iVar5 + 0x160,iVar5 + 0x3a0);
    uStack_208._0_4_ = (float)uStack_33c8;
    _auStack_210 = uStack_33d0;
    uStack_208._4_4_ = (float)uStack_33c4;
    auVar26 = _lqc2(_auStack_380);
    auVar25 = _lqc2(_auStack_210);
    auVar25 = _vsub(auVar25,auVar26);
    _auStack_210 = _sqc2(auVar25);
    FUN_004baab0(*(undefined4 *)(iGpffff8610 + 0x40b4),0,*(undefined4 *)(iGpffff8610 + 0x40bc),
                 0x3f800000,auStack_33e0);
    if (*(int *)(iVar17 + 0xdc) == 0) {
      fVar23 = (float)func_0x00222fd0(auStack_210);
      fVar22 = (float)func_0x00222fd0(auStack_200);
      *(float *)(iVar17 + 0x84) = (fVar23 / (fVar22 * 0.75) + 1.2) * 512.0;
    }
    else {
      fVar23 = (float)func_0x00222fd0(auStack_210);
      fVar22 = (float)func_0x00222fd0(auStack_200);
      *(float *)(iVar17 + 0x84) =
           *(float *)(iVar17 + 0x84) +
           ((fVar23 / (fVar22 * 0.75) + 1.2) * 512.0 - *(float *)(iVar17 + 0x84)) * 3.75 *
           *(float *)(iVar17 + 0x24);
    }
    uVar8 = func_0x00222f00(auStack_3400,auStack_210);
    Get3DAngle__F7FVector(&uStack_33f0,uVar8);
    fStack_1f8 = (float)uStack_33e8;
    auStack_200 = (undefined1  [8])uStack_33f0;
    uStack_1f4 = uStack_33e4;
    fVar23 = fStack_38c;
    if (fStack_38c < 4.0) {
      fVar23 = 4.0;
    }
    fVar20 = (float)func_0x00222fd0(&fStack_390);
    fVar20 = fStack_390 + fVar20;
    fVar21 = *(float *)(iVar17 + 0x84);
    fVar22 = -(float)auStack_200._0_4_;
    if ((fVar22 <= 40.0) && (fVar22 = fVar22 * 1.25 - 10.0, fVar22 < -10.0)) {
      fVar22 = -10.0;
    }
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    uVar24 = func_0x00222e40(fVar22);
    func_0x00202890(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(-(float)auStack_200._4_4_);
    func_0x00202938(uVar24,auStack_430,auStack_430);
    uVar8 = FUN_004baab0(0,0,-((fVar21 * (fVar20 + 30.0)) / 512.0),0x3f800000,auStack_3420);
    func_0x00222df0(&uStack_3410,auStack_430,uVar8);
    uStack_208._0_4_ = (float)uStack_3408;
    _auStack_210 = uStack_3410;
    uStack_208._4_4_ = (float)uStack_3404;
    uVar8 = FUN_004baab0(0,-fStack_38c - fVar23,0,0x3f800000,auStack_3440);
    __pl__7FVectorCFRC7FVector(auStack_3430,auStack_380,uVar8);
    auVar26 = _lqc2(auStack_3430);
    auVar25 = _lqc2(_auStack_210);
    auVar25 = _vadd(auVar25,auVar26);
    _auStack_210 = _sqc2(auVar25);
    if (-10.0 < fStack_20c) {
      fStack_20c = -10.0;
    }
    if (*(int *)(iVar17 + 0xdc) == 0) {
      *(int *)(iVar17 + 0x50) = auStack_210;
      *(int *)(iVar17 + 0x54) = auStack_210._4_4_;
      *(float *)(iVar17 + 0x58) = (float)uStack_208;
      *(float *)(iVar17 + 0x5c) = uStack_208._4_4_;
    }
    else {
      __mi__7FVectorCFRC7FVector(auStack_3450,auStack_210,iVar17 + 0x50);
      fStack_1f0 = auStack_3450._0_4_;
      fStack_1ec = auStack_3450._4_4_;
      fStack_1e8 = fStack_3448;
      uStack_1e4 = uStack_3444;
      __ml__7FVectorCFf(*(float *)(iVar17 + 0x24) * 7.5,auStack_3460,&fStack_1f0);
      auVar26 = _lqc2(auStack_3460);
      auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _vadd(auVar25,auVar26);
      auVar25 = _sqc2(auVar25);
      *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    __pl__7FVectorCFRC7FVector(auStack_3490,iVar5 + 0x160,iVar5 + 0x3a0);
    uVar8 = FUN_004baab0(0,-*(float *)(iVar5 + 0x3b4),0,0x3f800000,auStack_34a0);
    __pl__7FVectorCFRC7FVector(auStack_3480,auStack_3490,uVar8);
    __mi__7FVectorCFRC7FVector(&uStack_3470,auStack_3480,iVar17 + 0x50);
    uStack_208._0_4_ = (float)uStack_3468;
    _auStack_210 = uStack_3470;
    uStack_208._4_4_ = (float)uStack_3464;
    __pl__7FVectorCFRC7FVector(auStack_34d0,iVar5 + 0x160,iVar5 + 0x3a0);
    uVar8 = FUN_004baab0(0,*(undefined4 *)(iVar5 + 0x3b4),0,0x3f800000,auStack_34e0);
    __pl__7FVectorCFRC7FVector(auStack_34c0,auStack_34d0,uVar8);
    __mi__7FVectorCFRC7FVector(&uStack_34b0,auStack_34c0,iVar17 + 0x50);
    fStack_1f8 = (float)uStack_34a8;
    auStack_200 = (undefined1  [8])uStack_34b0;
    uStack_1f4 = uStack_34a4;
    uVar8 = FUN_004baab0(0,-fStack_38c,0,0x3f800000,auStack_3510);
    __pl__7FVectorCFRC7FVector(auStack_3500,auStack_380,uVar8);
    __mi__7FVectorCFRC7FVector(auStack_34f0,auStack_3500,iVar17 + 0x50);
    fStack_1f0 = auStack_34f0._0_4_;
    fStack_1ec = auStack_34f0._4_4_;
    fStack_1e8 = fStack_34e8;
    uStack_1e4 = uStack_34e4;
    uVar8 = FUN_004baab0(0,fStack_38c * 0.5,0,0x3f800000,auStack_3540);
    __pl__7FVectorCFRC7FVector(auStack_3530,auStack_380,uVar8);
    __mi__7FVectorCFRC7FVector(auStack_3520,auStack_3530,iVar17 + 0x50);
    fStack_1e0 = auStack_3520._0_4_;
    fStack_1dc = auStack_3520._4_4_;
    fStack_1d8 = fStack_3518;
    uStack_1d4 = uStack_3514;
    uVar8 = func_0x00222f00(auStack_3560,auStack_210);
    Get3DAngle__F7FVector(auStack_3550,uVar8);
    fStack_1d0 = auStack_3550._0_4_;
    fStack_1cc = auStack_3550._4_4_;
    uStack_1c8 = uStack_3548;
    uStack_1c4 = uStack_3544;
    uVar8 = func_0x00222f00(auStack_3580,auStack_200);
    Get3DAngle__F7FVector(auStack_3570,uVar8);
    afStack_1c0[0] = auStack_3570._0_4_;
    afStack_1c0[1] = auStack_3570._4_4_;
    afStack_1c0[2] = (float)uStack_3568;
    afStack_1c0[3] = (float)uStack_3564;
    uVar8 = func_0x00222f00(auStack_35a0,&fStack_1f0);
    Get3DAngle__F7FVector(auStack_3590,uVar8);
    afStack_1c0[4] = auStack_3590._0_4_;
    afStack_1c0[5] = auStack_3590._4_4_;
    afStack_1c0[6] = (float)uStack_3588;
    afStack_1c0[7] = (float)uStack_3584;
    uVar8 = func_0x00222f00(auStack_35c0,&fStack_1e0);
    Get3DAngle__F7FVector(auStack_35b0,uVar8);
    afStack_1c0[8] = (float)auStack_35b0._0_4_;
    afStack_1c0[9] = (float)auStack_35b0._4_4_;
    afStack_1c0[10] = (float)uStack_35a8;
    afStack_1c0[0xb] = (float)uStack_35a4;
    for (; fStack_1d0 < -180.0; fStack_1d0 = fStack_1d0 + 360.0) {
    }
    for (; 180.0 < fStack_1d0; fStack_1d0 = fStack_1d0 - 360.0) {
    }
    fVar23 = fStack_1d0;
    fVar22 = fStack_1d0;
    for (iVar5 = 5; iVar5 < 8; iVar5 = iVar5 + 1) {
      while (*(float *)(auStack_210 + iVar5 * 0x10) < -180.0) {
        *(float *)(auStack_210 + iVar5 * 0x10) = *(float *)(auStack_210 + iVar5 * 0x10) + 360.0;
      }
      while (180.0 < *(float *)(auStack_210 + iVar5 * 0x10)) {
        *(float *)(auStack_210 + iVar5 * 0x10) = *(float *)(auStack_210 + iVar5 * 0x10) - 360.0;
      }
      if (*(float *)(auStack_210 + iVar5 * 0x10) < fVar23) {
        fVar23 = *(float *)(auStack_210 + iVar5 * 0x10);
      }
      if (fVar22 < *(float *)(auStack_210 + iVar5 * 0x10)) {
        fVar22 = *(float *)(auStack_210 + iVar5 * 0x10);
      }
    }
    for (fVar22 = fVar22 - fVar23; fVar22 < -180.0; fVar22 = fVar22 + 360.0) {
    }
    for (; 180.0 < fVar22; fVar22 = fVar22 - 360.0) {
    }
    if (*(int *)(iVar17 + 0xdc) == 0) {
      *(float *)(iVar17 + 0x60) = -(fVar23 + fVar22 / 2.0);
    }
    else {
      for (fVar23 = -(fVar23 + fVar22 / 2.0) - *(float *)(iVar17 + 0x60); fVar23 < -180.0;
          fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 0x60) =
           *(float *)(iVar17 + 0x60) + fVar23 * 5.0 * *(float *)(iVar17 + 0x24);
    }
    while (*(float *)(iVar17 + 0x60) < -180.0) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 0x60)) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
    }
    for (fVar23 = fStack_1cc - afStack_1c0[5]; fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
    }
    for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
    }
    if (*(int *)(iVar17 + 0xdc) == 0) {
      *(float *)(iVar17 + 100) = -(afStack_1c0[5] + fVar23 / 2.0);
    }
    else {
      for (fVar23 = -(afStack_1c0[5] + fVar23 / 2.0) - *(float *)(iVar17 + 100); fVar23 < -180.0;
          fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + fVar23 * 7.5 * *(float *)(iVar17 + 0x24)
      ;
    }
    while (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    *(undefined4 *)(iVar17 + 0x68) = 0;
    *(undefined4 *)(iVar17 + 0xdc) = 1;
    break;
  case 0x19:
    if (*(short *)(iVar17 + 0x1e) != 1) {
      if (*(short *)(iVar17 + 0x1e) != 0) break;
      iVar5 = 0;
      for (iVar15 = 0; iVar15 < 0xc; iVar15 = iVar15 + 1) {
        if (((((*(byte *)(iGpffff8610 + iVar15 * 0x510 + 0xb0) & 1) != 0) &&
             ((long)((ulong)*(byte *)(iGpffff8610 + iVar15 * 0x510 + 0xb0) << 0x3e) < 0)) &&
            (-1 < (long)((ulong)*(byte *)(iGpffff8610 + iVar15 * 0x510 + 0xb2) << 0x3c))) &&
           (((*(byte *)(iGpffff8610 + iVar15 * 0x510 + 0xb4) & 1) == 0 ||
            (0 < *(int *)(iGpffff8610 + iVar15 * 0x510 + 0x130))))) {
          aiStack_100[iVar5] = iVar15;
          iVar5 = iVar5 + 1;
        }
      }
      __pl__7FVectorCFRC7FVector
                (&uStack_35d0,iGpffff8610 + aiStack_100[0] * 0x510 + 0x160,
                 iGpffff8610 + aiStack_100[0] * 0x510 + 0x3a0);
      uStack_208._0_4_ = (float)uStack_35c8;
      _auStack_210 = uStack_35d0;
      uStack_208._4_4_ = (float)uStack_35c4;
      for (iVar15 = 1; iVar15 < iVar5; iVar15 = iVar15 + 1) {
        __pl__7FVectorCFRC7FVector
                  (auStack_35e0,iGpffff8610 + aiStack_100[iVar15] * 0x510 + 0x160,
                   iGpffff8610 + aiStack_100[iVar15] * 0x510 + 0x3a0);
        auVar26 = _lqc2(auStack_35e0);
        auVar25 = _lqc2(_auStack_210);
        auVar25 = _vadd(auVar25,auVar26);
        _auStack_210 = _sqc2(auVar25);
      }
      func_0x00223030((float)iVar5,auStack_210);
      FUN_004baab0(auStack_210,0xc1200000,(float)uStack_208,0x3f800000,auStack_35f0);
      *(int *)(iVar17 + 0x70) = auStack_35f0._0_4_;
      *(int *)(iVar17 + 0x74) = auStack_35f0._4_4_;
      *(undefined4 *)(iVar17 + 0x78) = uStack_35e8;
      *(undefined4 *)(iVar17 + 0x7c) = uStack_35e4;
      fVar23 = 0.0;
      for (iVar15 = 0; iVar15 < iVar5; iVar15 = iVar15 + 1) {
        __pl__7FVectorCFRC7FVector
                  (&uStack_3600,iGpffff8610 + aiStack_100[iVar15] * 0x510 + 0x160,
                   iGpffff8610 + aiStack_100[iVar15] * 0x510 + 0x3a0);
        uStack_208._0_4_ = (float)uStack_35f8;
        _auStack_210 = uStack_3600;
        uStack_208._4_4_ = (float)uStack_35f4;
        fVar22 = fVar23;
        iVar12 = iVar15;
        while (fVar23 = fVar22, iVar12 = iVar12 + 1, iVar12 < iVar5) {
          __pl__7FVectorCFRC7FVector
                    (auStack_3620,iGpffff8610 + aiStack_100[iVar12] * 0x510 + 0x160,
                     iGpffff8610 + aiStack_100[iVar12] * 0x510 + 0x3a0);
          __mi__7FVectorCFRC7FVector(&uStack_3610,auStack_3620,auStack_210);
          fStack_1f8 = (float)uStack_3608;
          auStack_200 = (undefined1  [8])uStack_3610;
          uStack_1f4 = uStack_3604;
          auStack_200 = (undefined1  [8])(uStack_3610 & 0xffffffff);
          fVar22 = (float)func_0x00222fd0(auStack_200);
          if (fVar22 <= fVar23) {
            fVar22 = fVar23;
          }
        }
      }
      fVar23 = fVar23 / 2.0;
      if (fVar23 == 0.0) {
        fVar23 = (float)func_0x00222fd0(iGpffff8610 + aiStack_100[0] * 0x510 + 0x3b0);
      }
      *(float *)(iVar17 + 0x80) = ((fVar23 + 30.0) * *(float *)(iVar17 + 0x84)) / 512.0;
      *(undefined4 *)(iVar17 + 0x60) = 0x41200000;
      *(undefined4 *)(iVar17 + 0x68) = 0;
      *(undefined2 *)(iVar17 + 0x1e) = 1;
    }
    *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + *(float *)(iVar17 + 0x24) * 6.0;
    if (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    if (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 100));
    func_0x00202938(uVar24,auStack_430,auStack_430);
    uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_3640);
    func_0x00222df0(auStack_3630,auStack_430,uVar8);
    *(int *)(iVar17 + 0x50) = auStack_3630._0_4_;
    *(int *)(iVar17 + 0x54) = auStack_3630._4_4_;
    *(undefined4 *)(iVar17 + 0x58) = uStack_3628;
    *(undefined4 *)(iVar17 + 0x5c) = uStack_3624;
    auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
    auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
    auVar25 = _vadd(auVar25,auVar26);
    auVar25 = _sqc2(auVar25);
    *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    break;
  case 0x1a:
    FUN_005c3520(param_1);
    break;
  case 0x1b:
    if (*(short *)(iVar17 + 0x1e) == 1) {
      if (0.0 < *(float *)(iVar17 + 0xf0)) {
        *(float *)(iVar17 + 0xec) =
             *(float *)(iVar17 + 0xec) + *(float *)(iVar17 + 0x24) * *(float *)(iVar17 + 0xf0);
        *(float *)(iVar17 + 0xf0) = *(float *)(iVar17 + 0xf0) - *(float *)(iVar17 + 0x24) * 2.0;
      }
    }
    else if (*(short *)(iVar17 + 0x1e) == 0) {
      *(undefined4 *)(iVar17 + 0xf0) = 0x41200000;
      *(undefined2 *)(iVar17 + 0x1e) = 1;
    }
    *(float *)(iVar17 + 0xe0) = *(float *)(iVar17 + 0xe0) + *(float *)(iVar17 + 0x24);
    if (3.0 < *(float *)(iVar17 + 0xe0)) {
      *(undefined4 *)(iVar17 + 0xe0) = 0x40400000;
    }
    FUN_004baab0(0xc1200000,0x43340000,0,0x3f800000,auStack_3650);
    *(int *)(iVar17 + 0x60) = auStack_3650._0_4_;
    *(int *)(iVar17 + 100) = auStack_3650._4_4_;
    *(undefined4 *)(iVar17 + 0x68) = uStack_3648;
    *(undefined4 *)(iVar17 + 0x6c) = uStack_3644;
    fVar23 = (float)func_0x0021c7f8((*(float *)(iVar17 + 0xe0) * 3.1415927) / 3.0);
    fVar23 = (1.0 - fVar23) / 2.0;
    *(float *)(iVar17 + 0x80) =
         (*(float *)(iVar17 + 0x84) *
         (*(float *)(iVar17 + 0xec) + *(float *)(iVar17 + 0xe8) * fVar23)) / 512.0;
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x60));
    func_0x00202890(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 100));
    func_0x00202938(uVar24,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar17 + 0x68));
    func_0x002027e8(uVar24,auStack_430,auStack_430);
    uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_3670);
    func_0x00222df0(auStack_3660,auStack_430,uVar8);
    *(int *)(iVar17 + 0x50) = auStack_3660._0_4_;
    *(int *)(iVar17 + 0x54) = auStack_3660._4_4_;
    *(undefined4 *)(iVar17 + 0x58) = uStack_3658;
    *(undefined4 *)(iVar17 + 0x5c) = uStack_3654;
    auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x70));
    auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
    auVar25 = _vadd(auVar25,auVar26);
    auVar25 = _sqc2(auVar25);
    *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    *(float *)(iVar17 + 0x54) =
         *(float *)(iVar17 + 0x54) +
         fVar23 * (*(float *)(iVar17 + 0xe4) - *(float *)(iVar17 + 0x74));
    break;
  case 0x1c:
    if (*(short *)(iVar17 + 0x1e) == 0) {
      *(undefined4 *)(iVar17 + 0x60) = 0xc2b40000;
      *(undefined4 *)(iVar17 + 0x68) = 0;
      FUN_004baab0(0,(*(float *)(iVar17 + 0x84) * -22.0) / 512.0,0,0x3f800000,auStack_3680);
      *(int *)(iVar17 + 0x50) = auStack_3680._0_4_;
      *(int *)(iVar17 + 0x54) = auStack_3680._4_4_;
      *(undefined4 *)(iVar17 + 0x58) = uStack_3678;
      *(undefined4 *)(iVar17 + 0x5c) = uStack_3674;
      *(undefined2 *)(iVar17 + 0x1e) = 1;
    }
    *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + *(float *)(iVar17 + 0x24) * 30.0;
    while (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    *(float *)(iVar17 + 0x54) =
         *(float *)(iVar17 + 0x54) -
         (*(float *)(iVar17 + 0x24) * 13.0 * *(float *)(iVar17 + 0x84)) / 512.0;
    break;
  case 0x1d:
    iVar5 = iGpffff8610 + *(int *)(iVar17 + 0xd0) * 0x510;
    if ((((long)((ulong)*(byte *)(iVar5 + 0xb4) << 0x39) < 0) ||
        ((long)((ulong)*(byte *)(iVar5 + 0xb5) << 0x3c) < 0)) ||
       ((long)((ulong)*(byte *)(iVar5 + 0xb1) << 0x3a) < 0)) {
      __pl__7FVectorCFRC7FVector(auStack_36a0,iVar5 + 0x170,iVar5 + 0x3a0);
      *(int *)(iVar17 + 0x70) = auStack_36a0._0_4_;
      *(int *)(iVar17 + 0x74) = auStack_36a0._4_4_;
      *(undefined4 *)(iVar17 + 0x78) = uStack_3698;
      *(undefined4 *)(iVar17 + 0x7c) = uStack_3694;
    }
    else {
      __pl__7FVectorCFRC7FVector(auStack_3690,iVar5 + 0x160,iVar5 + 0x3a0);
      *(int *)(iVar17 + 0x70) = auStack_3690._0_4_;
      *(int *)(iVar17 + 0x74) = auStack_3690._4_4_;
      *(undefined4 *)(iVar17 + 0x78) = uStack_3688;
      *(undefined4 *)(iVar17 + 0x7c) = uStack_3684;
    }
    if ((*(int *)(iVar17 + 0xdc) != 0) &&
       (*(float *)(iVar17 + 0xe0) = *(float *)(iVar17 + 0xe0) - *(float *)(iVar17 + 0x24) * 15.0,
       *(float *)(iVar17 + 0xe0) < 10.0)) {
      *(undefined4 *)(iVar17 + 0xe0) = 0x41200000;
    }
    fVar23 = (float)func_0x00222fd0(iVar5 + 0x3b0);
    *(float *)(iVar17 + 0x80) =
         (*(float *)(iVar17 + 0x84) *
         (*(float *)(iVar17 + 0xe0) + *(float *)(iVar5 + 0x354) + fVar23)) / 512.0;
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    func_0x00202890(0xbe32b8c3,auStack_430,auStack_430);
    uVar24 = func_0x00222e40(*(undefined4 *)(iVar5 + 0x184));
    func_0x00202938(uVar24,auStack_430,auStack_430);
    uVar8 = FUN_004baab0(0,0,-*(float *)(iVar17 + 0x80),0x3f800000,auStack_36d0);
    func_0x00222df0(auStack_36c0,auStack_430,uVar8);
    __pl__7FVectorCFRC7FVector(&uStack_36b0,auStack_36c0,iVar17 + 0x70);
    uStack_208._0_4_ = (float)uStack_36a8;
    _auStack_210 = uStack_36b0;
    uStack_208._4_4_ = (float)uStack_36a4;
    if (*(int *)(iVar17 + 0xdc) == 0) {
      *(int *)(iVar17 + 0x50) = (int)uStack_36b0;
      *(int *)(iVar17 + 0x54) = (int)((ulong)uStack_36b0 >> 0x20);
      *(undefined4 *)(iVar17 + 0x58) = uStack_36a8;
      *(undefined4 *)(iVar17 + 0x5c) = uStack_36a4;
    }
    else {
      auVar26 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _lqc2(_auStack_210);
      auVar25 = _vsub(auVar25,auVar26);
      _auStack_210 = _sqc2(auVar25);
      func_0x00223030(0x40800000,auStack_210);
      auVar26 = _lqc2(_auStack_210);
      auVar25 = _lqc2(*(undefined1 (*) [16])(iVar17 + 0x50));
      auVar25 = _vadd(auVar25,auVar26);
      auVar25 = _sqc2(auVar25);
      *(undefined1 (*) [16])(iVar17 + 0x50) = auVar25;
    }
    CameraYPosCheck__9BtlCameraFv(param_1);
    __mi__7FVectorCFRC7FVector(&uStack_36e0,iVar17 + 0x70,iVar17 + 0x50);
    uStack_208._0_4_ = (float)uStack_36d8;
    _auStack_210 = uStack_36e0;
    uStack_208._4_4_ = (float)uStack_36d4;
    uVar8 = func_0x00222f00(auStack_3700,auStack_210);
    Get3DAngle__F7FVector(&uStack_36f0,uVar8);
    fStack_1f8 = (float)uStack_36e8;
    auStack_200 = (undefined1  [8])uStack_36f0;
    uStack_1f4 = uStack_36e4;
    auVar25 = _auStack_200;
    auStack_200._0_4_ = (undefined4)uStack_36f0;
    auStack_200._4_4_ = (undefined4)((ulong)uStack_36f0 >> 0x20);
    if (*(int *)(iVar17 + 0xdc) == 0) {
      *(float *)(iVar17 + 0x60) = -(float)auStack_200._0_4_;
      *(float *)(iVar17 + 100) = -(float)auStack_200._4_4_;
    }
    else {
      for (fVar23 = -(float)auStack_200._0_4_ - *(float *)(iVar17 + 0x60); fVar23 < -180.0;
          fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 0x60) =
           *(float *)(iVar17 + 0x60) + fVar23 * 7.5 * *(float *)(iVar17 + 0x24);
      for (fVar23 = -(float)auStack_200._4_4_ - *(float *)(iVar17 + 100); fVar23 < -180.0;
          fVar23 = fVar23 + 360.0) {
      }
      for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
      }
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + fVar23 * 7.5 * *(float *)(iVar17 + 0x24)
      ;
    }
    while (*(float *)(iVar17 + 0x60) < -180.0) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 0x60)) {
      *(float *)(iVar17 + 0x60) = *(float *)(iVar17 + 0x60) - 360.0;
    }
    while (*(float *)(iVar17 + 100) < -180.0) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) + 360.0;
    }
    while (180.0 < *(float *)(iVar17 + 100)) {
      *(float *)(iVar17 + 100) = *(float *)(iVar17 + 100) - 360.0;
    }
    *(undefined4 *)(iVar17 + 0x68) = 0;
    *(undefined4 *)(iVar17 + 0xdc) = 1;
    _auStack_200 = auVar25;
  }
  if (*(float *)(iVar17 + 0x1ec) != 0.0) {
    auVar25 = _vmr32(in_vf0);
    auVar26 = _vmr32(auVar25);
    auVar27 = _vmr32(auVar26);
    auStack_400 = _sqc2(in_vf0);
    auStack_410 = _sqc2(auVar25);
    auStack_420 = _sqc2(auVar26);
    auStack_430 = _sqc2(auVar27);
    iVar5 = func_0x00232cc8();
    func_0x002027e8(((float)iVar5 / 2.1474836e+09) * 6.2831855,auStack_430,auStack_430);
    iVar5 = func_0x00232cc8();
    uVar8 = FUN_004baab0(0,0,*(float *)(iVar17 + 0x1f0) * ((float)iVar5 / 2.1474836e+09),0x3f800000,
                         auStack_3720);
    func_0x00222df0(auStack_3710,auStack_430,uVar8);
    *(int *)(iVar17 + 0x200) = auStack_3710._0_4_;
    *(int *)(iVar17 + 0x204) = auStack_3710._4_4_;
    *(undefined4 *)(iVar17 + 0x208) = uStack_3708;
    *(undefined4 *)(iVar17 + 0x20c) = uStack_3704;
    if (*(float *)(iVar17 + 0x1ec) != -1.0) {
      *(float *)(iVar17 + 0x1ec) = *(float *)(iVar17 + 0x1ec) - *(float *)(iVar17 + 0x24);
      *(float *)(iVar17 + 0x1f0) = *(float *)(iVar17 + 0x1f0) * *(float *)(iVar17 + 500);
      if (*(float *)(iVar17 + 0x1ec) <= 0.0) {
        *(undefined4 *)(iVar17 + 0x1ec) = 0;
        *(undefined4 *)(iVar17 + 0x1f0) = 0;
        FUN_004baab0(0,0,0,0x3f800000,auStack_3730);
        *(int *)(iVar17 + 0x200) = auStack_3730._0_4_;
        *(int *)(iVar17 + 0x204) = auStack_3730._4_4_;
        *(undefined4 *)(iVar17 + 0x208) = uStack_3728;
        *(undefined4 *)(iVar17 + 0x20c) = uStack_3724;
      }
    }
  }
  UpdateCamera__9BtlCameraFv(param_1);
  if ((long)((ulong)*(byte *)(iVar17 + 0x18) << 0x38) < 0) {
    func_0x0038c860(uGpffff8374);
  }
  func_0x0022e230(&uStack_450,0xffffffffffffffff);
  func_0x0022e230(&uStack_440,0xffffffffffffffff);
  return 0;
}

