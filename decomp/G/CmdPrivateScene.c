/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdPrivateScene   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdPrivateScene.md).
 */

/* JP: 0x0044b700  CmdPrivateScene::CmdPrivateScene()   [__ct__15CmdPrivateSceneFv]  size=0x44 */
int __ct__15CmdPrivateSceneFv(int param_1)

{
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__15CmdPrivateScene;
  *(undefined4 *)(param_1 + 0x58) = 0;
  return param_1;
}

/* JP: 0x0044b750  CmdPrivateScene::~CmdPrivateScene()   [__dt__15CmdPrivateSceneFv]  size=0x74 */
int __dt__15CmdPrivateSceneFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__15CmdPrivateScene;
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0044b7d0  CmdPrivateScene::Update(short)   [Update__15CmdPrivateSceneFs]  size=0x10 */
void Update__15CmdPrivateSceneFs(void)

{
  return;
}

/* JP: 0x0044b7e0  CmdPrivateScene::ReadyScene()   [ReadyScene__15CmdPrivateSceneFv]  size=0x14 */
undefined8 ReadyScene__15CmdPrivateSceneFv(void)

{
  return 0;
}

/* JP: 0x0044b800  CmdPrivateScene::DisposeScene()   [DisposeScene__15CmdPrivateSceneFv]  size=0x10 */
void DisposeScene__15CmdPrivateSceneFv(void)

{
  return;
}

/* JP: 0x0044b810  CmdPrivateScene::BackGroundRun()   [BackGroundRun__15CmdPrivateSceneFv]  size=0x10 */
void BackGroundRun__15CmdPrivateSceneFv(void)

{
  return;
}
