/* World.c -- class World (ordering tables), VIF1Prim, VIF1PrimChain.   libgsx.cpp  JP 0x002257d0..0x00226520
 *
 * There is exactly one World: CApp::m_World  @0x0042bf10  (size 0x4120), accessed everywhere via literal 0x42bf10.
 *
 * struct World (Ghidra "World"):
 *   +0x0000 GsxCamera* cam[2]          cam[0] = main camera (also assigned to GsxCamera::m_pActiveCamera)
 *   +0x0008 uint       lastEnv         last "env" DMA address emitted into the current chain (init 0xffffffff)
 *   +0x000c VIF1PrimChain chain[16]    16 ordering-table layers, each a sorted doubly linked list (12 B per header)
 *   +0x00d0 QWD  buf[2][0x200]         two DMA-chain build buffers, 0x2000 bytes each (512 qwords)
 *   +0x40d0 int  layerCount[16]        number of prims in each layer (layer skipped when 0)
 *   +0x4110 uint bufIdx                buffer being *built*; flipped by EndUpdate
 *
 * struct VIF1PrimChain { next; prev; VIF1Prim* prim }       (header node has prim==0, chain[l].next == first)
 * struct VIF1Prim (size 0x14, polymorphic):
 *   +0x00,+0x04  (subclass-dependent; DelayDeleteObject / CPolObj vptr slots)
 *   +0x08 uint pEnv        optional shared GS-state packet (DMA addr).  LayerGetPacket emits "call pEnv" once
 *                          whenever pEnv != World.lastEnv  (state-change elision across consecutive prims).
 *   +0x0c u8 flags         bit0 "seen/active this frame"(cleared in changebActiveFlg), bits1-2 per-frame pass counter (0..3),
 *                          bit3 = skip/hidden (LayerGetPacket skips prim when set), bit4 = "z-fixed" (changeZvolume ignores)
 *   +0x0e s16 zvolume      sort key inside a layer.  List is sorted DESCENDING by zvolume (largest first = drawn first)
 *   +0x10 vptr             vtable: [0]=dtor(this,delflag)  [1]=virtual QWD* getPacket()  [2..] subclass
 *
 * VIF1Prim::getPacket() base impl returns NULL (0x00225f60).  Subclasses return the DMA address of a *sub-chain*
 * terminated by a `ret` tag (0x60000000).
 */

/* 0x002257d0 VIF1Prim::VIF1Prim(): pEnv=0; zvolume=0; flags=0; vptr=&__vt__8VIF1Prim */
/* 0x002257f0 VIF1Prim::~VIF1Prim(): World::FindOT(this) -- NOTE only a find; callers must ReleaseOT first       */
/* 0x00225860 VIF1Prim::setZvolume(s16 z): if (z != zvolume) { zvolume = z; World::changeZvolume(this); }         */

/* 0x00225ca0 VIF1PrimChain::VIF1PrimChain(): next=prev=prim=0                                                   */
/* 0x002258b0 insert(VIF1PrimChain* n)  : insert n right after this                                              */
/* 0x002258f0 add(n): descending insert: walk while next.prim.zvolume >= n.prim.zvolume                          */
/* 0x00225970 addPrim(VIF1Prim* p): n = new VIF1PrimChain{prim=p}; add(n)                                        */
/* 0x002259e0 findPrim(p) -> bool ; 0x00225a40 findPrimP(p) -> node*                                             */
/* 0x00225a90 remove(): unlink                                    0x00225ad0 releasePrim(p): unlink+delete node  */

/* 0x00225b50 World::World(): chain[] constructed; bufIdx=0; lastEnv=-1; layerCount[]=0; both buffers zeroed       */

/* 0x00225d30 World::WorldGetPacket()   -- build the DMA chain for ONE frame
 *     QWD* p = buf[bufIdx];
 *     for l in 0..16: if (layerCount[l]) p = LayerGetPacket(l, p);
 *     *(u32*)p = 0x70000000;               // DMA tag END
 */
QWD* World_LayerGetPacket(World* w, int layer, QWD* p)   /* 0x00225e40 */
{
    if (layer < 0 || layer > 15) return NULL;
    for (node = w->chain[layer].next; node; node = node->next) {
        VIF1Prim* pr = node->prim;
        if (pr->flags & 8) continue;                      /* hidden */
        QWD* sub = pr->vptr->getPacket(pr);                /* virtual: let the object (re)build its packet */
        pr->flags = (pr->flags & ~6) | ((((pr->flags >> 1) & 3) + 1) & 3) << 1;   /* pass counter++ */
        if (!sub) continue;
        if (pr->pEnv && w->lastEnv != pr->pEnv) {          /* state packet, emitted only on change */
            p->tag = DMA_CALL(qwc=0, addr=pr->pEnv); p++;
            w->lastEnv = pr->pEnv;
        }
        p->tag = DMA_CALL(qwc=0, addr=sub); p++;           /* tag word0=0x50000000, word1=addr */
    }
    return p;
}
/* 0x00225db0 changebActiveFlg(): for every prim in every layer: flags &= ~1; flags &= ~6;  Env flip:
 *            m_Env__8VIF1Prim ^= 1   (static byte @0x0040abb0)  -- THE double-buffer parity used by every prim
 *            (prims keep 2 packet buffers and use m_Env&1 to pick the one NOT currently being DMA'd)         */

/* 0x00225f70 WorldRender(): FlushCache(0); DmaMan::DmaSend(1 /*VIF1 channel*/, &buf[bufIdx])   -- kicks the chain.
 * 0x00225fb0 ReleaseOT(prim): remove from ALL layers, decrement layerCount; returns true if found
 * 0x00226060 FindOT(prim) bool;  0x002260e0 FindOTindex(prim) -> layer or -1
 * 0x00226160 AddDoubleOT(la, lb, prim): AddOT twice (prim appears in two layers)
 * 0x002261d0 AddOT(layer, prim): 0<=layer<16 && prim: layerCount[layer]++; chain[layer].addPrim(prim)
 * 0x00226240 AddOTBefor(ref, prim): same layer as ref, node inserted before ref's node
 * 0x00226300 AddOTAfter(ref, prim): after
 * 0x002263c0 changeZvolume(prim): unless flags&0x10: for each layer containing prim: remove node, re-add (sort)
 * 0x00226460 BeginUpdate(): if (cam[0]->flags & 4) cam[0]->ClearRaster();  changebActiveFlg();
 * 0x002264b0 EndUpdate(): bufIdx ^= 1
 * 0x002264c0 SetCamera(idx<2, cam) -> old; idx 0 also sets GsxCamera::m_pActiveCamera
 * 0x00226500 GetCamera(idx)
 */
