/* Section H (BATTLE.BIN) — struct layouts used by the cleaned decompilation in this directory.
 * GENERATED from the Ghidra structs of program SH2JP_BATTLE.BIN (field names carry the Ghidra MCP Hungarian prefixes:
 * b=byte, n=short/int, w=ushort, dw=uint, fl=float, p=pointer, a=array, c=char).  Offsets/sizes are authoritative;
 * `/*+off*/` comments give the byte offset.  See notes/H/CBattle.md and notes/H/battle_rules.md. */
typedef unsigned char byte; typedef unsigned short ushort; typedef unsigned int uint;
typedef struct FVector { float x, y, z, w; } FVector;

typedef struct StatRec {  /* size 0xc */
    byte bSource;  /*+0x0*/
    byte bFlags;  /*+0x1*/
    byte bAux;  /*+0x2*/
    byte bFlags3;  /*+0x3*/
    byte bKind;  /*+0x4*/
    byte bTurns;  /*+0x5*/
    byte bChance;  /*+0x6*/
    byte bSrcChr;  /*+0x7*/
    int nValue;  /*+0x8*/
} StatRec;

typedef struct MONSETTbl {  /* size 0x10 */
    ushort wFormation;  /*+0x0*/
    short aMonsters[6];  /*+0x2*/
    ushort wFlags;  /*+0xe*/
} MONSETTbl;

typedef struct MONSTERParam {  /* size 0x38 */
    ushort wId;  /*+0x0*/
    short nModel;  /*+0x2*/
    byte bDefElement;  /*+0x4*/
    byte bF5;  /*+0x5*/
    ushort wHp;  /*+0x6*/
    ushort wMp;  /*+0x8*/
    ushort wPatk;  /*+0xa*/
    ushort wPdef;  /*+0xc*/
    ushort wSatk;  /*+0xe*/
    ushort wSdef;  /*+0x10*/
    byte bAgl;  /*+0x12*/
    byte bLuc;  /*+0x13*/
    byte bAtkElement;  /*+0x14*/
    byte bSizeClass;  /*+0x15*/
    short nSkill0;  /*+0x16*/
    short nSkill1OrSet;  /*+0x18*/
    short nItem1;  /*+0x1a*/
    short nItem2;  /*+0x1c*/
    byte bItemRate1;  /*+0x1e*/
    byte bItemRate2;  /*+0x1f*/
    byte pad_20[0x4];
    int nExp;  /*+0x24*/
    int nCash;  /*+0x28*/
    ushort wSpReward;  /*+0x2c*/
    ushort wW2e;  /*+0x2e*/
    ushort wAttackTable;  /*+0x30*/
    byte bResist;  /*+0x32*/
    byte pad_33[0x5];
} MONSTERParam;

typedef struct _PCParam_Ver00 {  /* size 0xc0 */
    byte pad_0[0x44];
    byte bFlags44;  /*+0x44*/
    byte pad_45[0x2];
    byte bLevel;  /*+0x47*/
    byte pad_48[0x18];
    ushort wMaxHP;  /*+0x60*/
    ushort wHp;  /*+0x62*/
    ushort wMaxMP;  /*+0x64*/
    ushort wMp;  /*+0x66*/
    byte bMaxSP;  /*+0x68*/
    byte bSp;  /*+0x69*/
    byte bStr;  /*+0x6a*/
    byte bVit;  /*+0x6b*/
    byte bIntl;  /*+0x6c*/
    byte bPow;  /*+0x6d*/
    byte bAgl;  /*+0x6e*/
    byte bLuc;  /*+0x6f*/
    byte bX70;  /*+0x70*/
    char cWeapon;  /*+0x71*/
    char cArmor;  /*+0x72*/
    char aAbility[3];  /*+0x73*/
    byte pad_76[0xa];
    uint dwExp;  /*+0x80*/
    short aAffinity[12];  /*+0x84*/
    byte bComboByte;  /*+0x9c*/
    byte bComboByte2;  /*+0x9d*/
    byte pad_9e[0x22];
} _PCParam_Ver00;

typedef struct BtlChr {  /* size 0x4f0 */
    byte bFlagsA;  /*+0x0*/
    byte bFlagsA1;  /*+0x1*/
    byte bFlagsA2;  /*+0x2*/
    byte bFlagsA3;  /*+0x3*/
    byte bFlagsB;  /*+0x4*/
    byte bFlagsB1;  /*+0x5*/
    byte bFlagsB2;  /*+0x6*/
    byte bFlagsB3;  /*+0x7*/
    byte bState;  /*+0x8*/
    byte bState2;  /*+0x9*/
    short nSubId;  /*+0xa*/
    int nFormation;  /*+0xc*/
    int nSlot;  /*+0x10*/
    byte pad_14[0x58];
    char * pNamePtr;  /*+0x6c*/
    short nCharId;  /*+0x70*/
    ushort wMaxHP;  /*+0x72*/
    short nHp;  /*+0x74*/
    ushort wMaxMP;  /*+0x76*/
    short nMp;  /*+0x78*/
    ushort wMaxSP;  /*+0x7a*/
    short nSp;  /*+0x7c*/
    ushort wAgl;  /*+0x7e*/
    ushort wLuc;  /*+0x80*/
    ushort wPatk;  /*+0x82*/
    ushort wSatk;  /*+0x84*/
    ushort wPdef;  /*+0x86*/
    ushort wSdef;  /*+0x88*/
    short nNameSuffix;  /*+0x8a*/
    byte pad_8c[0x8];
    void * pModel;  /*+0x94*/
    void * pParam;  /*+0x98*/
    byte pad_9c[0x4];
    float aPos[4];  /*+0xa0*/
    byte pad_b0[0x20];
    float flTurnInterval;  /*+0xd0*/
    float flTurnTimer;  /*+0xd4*/
    float flTurnWaited;  /*+0xd8*/
    byte pad_dc[0x8];
    void * pAiScript;  /*+0xe4*/
    void * pAiCursor;  /*+0xe8*/
    short aAiReg[8];  /*+0xec*/
    ushort wTurnCount;  /*+0xfc*/
    byte pad_fe[0x6];
    float flNextTurnMul;  /*+0x104*/
    StatRec aStatus[32];  /*+0x108*/
    byte pad_288[0x1d0];
    int nVulnTurn;  /*+0x458*/
    byte pad_45c[0x4];
    ushort wVulnCount;  /*+0x460*/
    byte pad_462[0x2];
    float flVulnA;  /*+0x464*/
    float flVulnB;  /*+0x468*/
    float flVariance;  /*+0x46c*/
    byte pad_470[0x3c];
    int nAtkTbl;  /*+0x4ac*/
    byte pad_4b0[0x26];
    short nSpFrac;  /*+0x4d6*/
    byte pad_4d8[0x18];
} BtlChr;

typedef struct CBattle {  /* size 0x4660 */
    byte pad_0[0x24];
    byte bFlags24;  /*+0x24*/
    byte bFlags25;  /*+0x25*/
    byte pad_26[0x2];
    short nPhase;  /*+0x28*/
    short nStep;  /*+0x2a*/
    char cActor;  /*+0x2c*/
    char cActorB;  /*+0x2d*/
    short nPartner;  /*+0x2e*/
    short nCurTurnChr;  /*+0x30*/
    ushort wTurnPendMask;  /*+0x32*/
    byte pad_34[0x2];
    short nComboCnt;  /*+0x36*/
    float flDeltaT;  /*+0x38*/
    byte pad_3c[0x4];
    int nTurnNo;  /*+0x40*/
    int nCmd0;  /*+0x44*/
    int nCmd1;  /*+0x48*/
    int nCmdKind;  /*+0x4c*/
    int nCmd3;  /*+0x50*/
    int nCmd4;  /*+0x54*/
    int nCmd5;  /*+0x58*/
    byte pad_5c[0x4];
    int nShortcutTarget;  /*+0x60*/
    byte pad_64[0x20];
    float flMenuTimer;  /*+0x84*/
    float flMenuTimer2;  /*+0x88*/
    byte pad_8c[0x8];
    void * pCbArg;  /*+0x94*/
    void * pCallback;  /*+0x98*/
    byte pad_9c[0x14];
    BtlChr aChr[12];  /*+0xb0*/
    byte pad_3bf0[0x224];
    short aTurnTbl[64];  /*+0x3e14*/
    short aSideAlive[2];  /*+0x3e94*/
    byte pad_3e98[0x44];
    byte bGmodFlags;  /*+0x3edc*/
    byte pad_3edd[0x1];
    ushort wGmodStat;  /*+0x3ede*/
    int nGmodValue;  /*+0x3ee0*/
    byte pad_3ee4[0x440];
    void * pCamera;  /*+0x4324*/
    void * pParamDisp;  /*+0x4328*/
    byte pad_432c[0x40];
    void * pTurnOrderDisp;  /*+0x436c*/
    byte pad_4370[0x14];
    void * pBtlMenu;  /*+0x4384*/
    byte pad_4388[0x1c];
    ushort wMonFormation;  /*+0x43a4*/
    ushort aMonIds[6];  /*+0x43a6*/
    byte bEscapeFlags;  /*+0x43b2*/
    byte pad_43b3[0x20f];
    byte bNoEvade;  /*+0x45c2*/
    byte bBattleSub;  /*+0x45c3*/
    byte pad_45c4[0x28];
    byte aMenuRes[4];  /*+0x45ec*/
    ushort wComboMask;  /*+0x45f0*/
    byte pad_45f2[0x2];
    ushort wResultFlags;  /*+0x45f4*/
    byte bTrophyCount;  /*+0x45f6*/
    byte bKillCount;  /*+0x45f7*/
    short aTrophyItem[6];  /*+0x45f8*/
    byte aTrophyChance[6];  /*+0x4604*/
    byte aTrophyCnt[6];  /*+0x460a*/
    int nRewardExp;  /*+0x4610*/
    int nRewardCash;  /*+0x4614*/
    uint dwRewardSP;  /*+0x4618*/
    short aKillList[18];  /*+0x461c*/
    byte aTrophyMon[6];  /*+0x4640*/
    byte aTrophyRare[6];  /*+0x4646*/
    byte pad_464c[0x14];
} CBattle;
