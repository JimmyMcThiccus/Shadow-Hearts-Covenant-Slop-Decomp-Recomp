/* CNaviMap - retail deltas only (SH2US_FIELD.BIN 0x00514390..). The rest equals ../G/CNaviMap.c. */
#include "_types_retail.h"
/* new animation block */
#define NM_PHASE(n)   RF(float, 0xc0, n)   /* pulse phase 0..1 */
#define NM_SCALE(n)   RF(float, 0xc4, n)
#define NM_ALPHA(n)   RF(float, 0xc8, n)
#define NM_FLAGS(n)   RF(u8, 0xcc, n)      /* JP +0xc0: bit4 hide-mask, ... */

/* US 0x00514970 CNaviMap::Update(float dt, float yaw, FVector *player) - first lines */
void CNaviMap_Update(float dt, float yaw, CNaviMap *n, FVector *player) {
    NM_PHASE(n) += dt * 0.7f;  if (NM_PHASE(n) > 1.0f) NM_PHASE(n) -= 1.0f;     /* RETAIL: pulsing cursor phase */
    /* ... JP part: centre on the player, rebuild packets (MakePacket / MakeMapPacket / MakeMaskPacket / MakeItemPacket) ... */
}
/* US 0x00517660 MakeItemPacket: item loop stride 7 (JP 6); marker size (NM_SCALE + 22.0) * NM_ALPHA; arrows rotated by (angle deg) * 0.017453289;
 * fade ramp: t < 0.7 ? t/0.7 : 1 - (t - 0.7)/0.3 (applied to colour alpha); wobble (NM_PHASE - 0.5) * -10. */
