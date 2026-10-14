/* ModelServer.cpp — LSD (cutscene) track handler that instantiates models.  JP 0x00384d20..0x00387300 */

/* JP: 0x00384d80 ModelServerHandler::CheckData — track magic 0x534c444d == "MDLS" */
bool ModelServerHandler::CheckData(_LSDTrackHdr *h) { return *(u32 *)h == 'SLDM'; }

/* JP: 0x00384da0 Open(RingBuffer *rb) — read a 0x32-byte LSDModel descriptor, link into ModelServer list unless
 *      descriptor.flags(+0x50) bit 2 is set ("LOD data for an existing model"); allocate BufMemory(modelBytes<<4, align 0x80) */
/* JP: 0x00384ec0 Read(handle, rb) — stream 'size<<4' bytes into the BufMemory; on completion
 *      (a) bit 2 set: ModelServer::SerchModel(name) -> Model::createLevelofDetale(bufmem, 2)
 *      (b) else: new MCESModel (0x4d0) -> vtbl+0x20 (create(BufMemory*)); then by (file[10] & 0x3f) >> 3:
 *            1: ShadowControl::setDropShadow(model); model.flags484 |= 2
 *            2: ShadowControl::setReciveShadow(model)
 */
/* JP: 0x00385060 Event(handle, id) — 1/3: World::AddDoubleOT(OT 3,6 for drop-shadow models, 2,5 for receivers),
 *      2: ReleaseOT, 4: ReleaseOT + ShadowControl::releaseShadow */
/* JP: 0x003851a0 Close — DAT_0042b7b4 = 1; ~LSDModel */

/* ModelServer (0xb0 bytes, singleton ModelServer::sys @0x0040acf4): two CLists (+0x00 model list, +0x58 camera/anim list)
 * JP: 0x00387290 SerchHdr(name) — walk list, strcmp(node+0x40, name), return &node->hdr ; SerchModel(name) returns node->model(+8) */
