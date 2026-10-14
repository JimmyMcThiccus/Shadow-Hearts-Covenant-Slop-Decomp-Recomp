/* Section G recovered types (JP FIELD.BIN overlay + main exe). Offsets are byte offsets from the object start.
 * These are the same structs created in Ghidra (SH2JP_FIELD.BIN / SLPM_602.19). */
#pragma once
typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16; typedef unsigned int u32; typedef int s32;

typedef struct FVector { float x, y, z, w; } FVector;                 /* 16 bytes, positions carry w=1 */
typedef struct Matrix  { FVector col[4]; } Matrix;                    /* libvu0 layout; col[3] = translation */

/* ---- MPS / SDB container ---- */
typedef struct SDB_tagHEADER { char tag[8]; u32 count; u32 data_off; u32 relocated; u32 pad[3]; } SDB_tagHEADER;   /* 0x20 */
typedef struct SDB_tagWORLD  { float size_x, size_z; u32 slices_along_x, slices_along_z; float origin_x, origin_z, unk18, unk1c; } SDB_tagWORLD; /* 0x20 */
typedef struct SDB_tagFTRIANGLE { void *v[3]; /* index in file, pointer after SetData */
                                  float max_c, min_c; u16 unk14; u8 blocked; u8 obstacle_id; u8 unk18[8]; } SDB_tagFTRIANGLE; /* 0x20 */
typedef struct SDB_tagEVENTBOX { u32 unk0; s32 id; u8 flags; u8 pad[7]; FVector center; float rot_a, rot_b; float pad2[2];
                                 FVector corner[4]; /* x, halfheight(corner 0), z */ } SDB_tagEVENTBOX;                 /* 0x70 */
typedef struct SDB_tagFCAMERA { u32 kind; u32 count; void *blob; u8 blend_flag; u8 pad[3]; } SDB_tagFCAMERA;          /* 0x10 */
typedef struct SDB_tagENTRYPOS { float x, y, z; s8 dir; u8 pad[3]; } SDB_tagENTRYPOS;                                 /* 0x10 */

typedef struct CSTGDB {                     /* 0x24, JP main 0x003c1f60.. */
    void *vt0; void *vt1;                   /* DelayDeleteObject header */
    void *vtbl;                             /* +8 */
    struct BufMemory *buf;                  /* +0xc */
    int order_id;                           /* +0x10 DvdromOrder id or -1 */
    int state;                              /* +0x14 0 empty, 1 loading, 2 ready */
    void *data;                             /* +0x18 whole file */
    int chunk_count;                        /* +0x1c */
    SDB_tagHEADER **chunks;                 /* +0x20 */
} CSTGDB;

typedef struct CFloorMan {                  /* 0x20, JP 0x004bc850.. */
    SDB_tagWORLD *world; FVector *vertices; SDB_tagFTRIANGLE *triangles; u32 *slices;
    SDB_tagFTRIANGLE *cached;               /* +0x10 */
    int slice_along_z; int slice_count; float rot_y;
} CFloorMan;

typedef struct CFieldEvent { int count; int is_camera; SDB_tagEVENTBOX *boxes; } CFieldEvent;  /* 0xc */

typedef struct CFieldCamera {               /* 0xd0 */
    struct GsxCamera *gsx; u8 pad4[2]; u8 flags /* b0 enabled b1 ext angles b2 compose b3 smooth */; u8 pad7[9];
    float roll, comp_time, comp_len, view_angle, prev_view_angle, final_angle, view_delay; float pad2c;
    FVector target, cam_pos, from_target, from_cam, final_target, final_cam, goal_target; float goal_angle; float pad[3];
    FVector vec_b0; float pitch_deg, yaw_deg, roll_deg, one;
} CFieldCamera;

typedef struct Fader { struct ScreenBright *bright; u8 state /* 0 idle 1 run 2 finishing, b4 paused */; u8 mode; u8 pad[2]; u16 cur; s16 total; } Fader; /* 0xc */
typedef struct CFieldSocket {               /* 0x6c, main exe */
    int pad0; void *vtbl; u8 polobj[0xc]; void *vt_polobj; u8 pad18[4]; void *vt_b;
    struct GsxCamera *camera; struct SmoothFilter *smooth; struct BlurFilter *blur; struct BufMemory *overlay_buf;
    Fader fader[2];                         /* +0x30, +0x3c */
    int entry_id;                           /* +0x48 entry id / worldMap* */
    int pad4c; int phase;                   /* +0x50 */
    int overlay_state;                      /* +0x54 */
    char map[16]; int pad68; struct dataAccess *data_access;
} CFieldSocket;
