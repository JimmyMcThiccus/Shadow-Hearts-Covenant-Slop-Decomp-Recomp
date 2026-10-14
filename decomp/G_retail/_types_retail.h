/* Retail (US) field engine types. Offsets are byte offsets in the US objects (SH2US_FIELD.BIN / SLUS_210.41).
 * JP reference types: ../G/_types.h. Layout derivation: notes/G_retail/*.md. Accessor macros are used instead of full structs because the
 * retail CField is a 0x2770 byte object whose middle part is only partially understood. */
#pragma once
#include "../G/_types.h"

#define RF(t, o, self) (*(t *)((u8 *)(self) + (o)))

/* ---- CField (0x2770) ---- */
#define CFIELD_SIZE 0x2770
#define CF_VTBL(f)          RF(void *, 0x14, f)
#define CF_STATE(f)         RF(u16, 0x28, f)        /* 1 loading models, 2 running, 3 frozen */
#define CF_ENTRY_ID(f)      RF(s16, 0x2a, f)
#define CF_SE(f)            RF(void *, 0x15c, f)
#define CF_NAVIMAP(f)       RF(struct CNaviMap *, 0x160, f)
#define CF_TEAMCHG(f)       RF(void *, 0x174, f)
#define CF_FLAGS178(f)      RF(u8, 0x178, f)        /* b0-1 delete reason (1 game over, 2 scene 0x40), b5-7 follow mode */
#define CF_FLAGS179(f)      RF(u8, 0x179, f)        /* b0 teardown, b1 displayed, b2 menu requested, b4 init */
#define CF_FLAGS17A(f)      RF(u8, 0x17a, f)
#define CF_CTRL_MODE(f)     RF(u8, 0x17c, f)        /* 0 free, 1 scripted latch, 2 wait fader, 3 ready */
#define CF_PAUSE(f)         RF(u8, 0x17d, f)        /* 0 run, 1 hold input, 2 sleeping */
#define CF_BATTLE(f)        RF(u8, 0x17e, f)        /* 1 normal, 2 boss */
#define CF_HUDSTATE(f)      RF(u8, 0x186, f)
#define CF_COUNTDOWN(f)     RF(u8, 0x187, f)
#define CF_SIGHT_TRIG(f)    RF(u8, 0x189, f)        /* index+1 of the monster that noticed its target */
#define CF_MODEL_COUNT(f)   RF(u8, 0x18a, f)
#define CF_SCRCAM(f)        RF(u8, 0x18b, f)
#define CF_PAD(f)           RF(void *, 0x1a4, f)
#define CF_EVENT_BOXES(f)   RF(struct CFieldEvent *, 0x1a8, f)
#define CF_CAM_EVENTS(f)    RF(struct CFieldEvent *, 0x1ac, f)
#define CF_FLOOR(f)         RF(struct CFloorMan *, 0x1b0, f)
#define CF_CAMERA(f)        RF(struct CFieldCamera *, 0x1b4, f)
#define CF_MODEL(f, i)      RF(struct CFieldModel *, 0x1b8 + 4 * (i), f)
#define CF_BG(f)            RF(struct CFieldBG *, 0x3b8, f)
#define CF_WINDOW(f, i)     ((u8 *)(f) + 0x910 + 0x14 * (i))   /* +0 FieldMessage*, +6 flags, +8 pos, +0xc size */
#define CF_FACE(f, i)       RF(void *, 0x9b4 + 4 * (i), f)
#define CF_CUR_WINDOW(f)    RF(u8, 0x9c4, f)
#define CF_MCES_STATE(f)    RF(u8, 0x9a8, f)
#define CF_CAMERA_ID(f)     RF(s16, 0x9e0, f)
#define CF_FOLLOW_STAMP(f)  RF(u32, 0x9f0, f)
#define CF_FOLLOW_HEAD(f)   RF(float, 0x9f4, f)      /* stored stick heading */
#define CF_YAW_ADJUST(f)    RF(float, 0x9f8, f)
#define CF_STICK_SPEED(f)   RF(float, 0xa10, f)      /* latched MakeMoveControl results */
#define CF_STICK_ANGLE(f)   RF(float, 0xa14, f)
#define CF_OBJSE(f, i)      ((u8 *)(f) + 0xa58 + 0x2c * (i)) /* stride 0x2c (JP 0x28) */
#define CF_PRELOAD_NAME(f)  ((char *)(f) + 0xa35)    /* char[13], script op 0x21 */
#define CF_CAM_POS(f)       RF(FVector, 0x2110, f)
#define CF_CAM_ANGLE(f)     RF(FVector, 0x2120, f)   /* .y = yaw (deg) */
#define CF_PLAYER_POS(f)    RF(FVector, 0x2130, f)

/* ---- CFieldCamera (0xf0) ---- */
#define CC_GSX(c)           RF(void *, 0x00, c)
#define CC_FLAGS(c)         RF(u8, 0x06, c)          /* b0 enabled, b1 external angles, b2 compose, b3 smooth ease */
#define CC_COMP_TIME(c)     RF(float, 0x14, c)
#define CC_COMP_LEN(c)      RF(float, 0x18, c)
#define CC_FOV(c)           RF(float, 0x1c, c)
#define CC_FOV_PREV(c)      RF(float, 0x20, c)
#define CC_FOV_FINAL(c)     RF(float, 0x24, c)
#define CC_DELAY(c)         RF(float, 0x28, c)
#define CC_TARGET(c)        RF(FVector, 0x30, c)
#define CC_CAM(c)           RF(FVector, 0x40, c)
#define CC_FROM_TARGET(c)   RF(FVector, 0x50, c)
#define CC_FROM_CAM(c)      RF(FVector, 0x60, c)
#define CC_FINAL_TARGET(c)  RF(FVector, 0x70, c)
#define CC_FINAL_CAM(c)     RF(FVector, 0x80, c)
#define CC_PITCH(c)         RF(float, 0xc0, c)
#define CC_YAW(c)           RF(float, 0xc4, c)
#define CC_ROLL(c)          RF(float, 0xc8, c)
#define CC_POS_OFS(c)       RF(FVector, 0xd0, c)     /* retail: camera FX position offset */
#define CC_ANG_OFS(c)       RF(FVector, 0xe0, c)     /* retail: camera FX pitch (.x) / roll (.z) offsets */

/* ---- CFieldSocket (0x74) ---- */
#define CS_DATAACCESS(s)    RF(void *, 0x30, s)
#define CS_START_CB(s)      RF(void (*)(void *), 0x34, s)
#define CS_START_ARG(s)     RF(void *, 0x38, s)
#define CS_PHASE(s)         RF(int, 0x3c, s)
#define CS_OVERLAY_STATE(s) RF(int, 0x40, s)
#define CS_FADER(s, i)      ((u8 *)(s) + 0x44 + 0xc * (i))   /* +0 ScreenBright*, +4 state, +5 mode, +8 cur, +0xa total */
#define CS_ENTRY(s)         RF(int, 0x5c, s)
#define CS_MAPNAME(s)       ((char *)(s) + 0x64)
