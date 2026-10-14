/*
 * EventHandler.c -- 'LSCR' track handler + GenericDataHandler ('LGDT')   (JP main 0x003cc010..0x003cd0c0, EventServer.cpp)
 */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32; typedef int s32;

/* _EventWork (sizeof = u16@hdr+0x10 *16 rounded): allocated by EventHandler::Open
 *   +0x00 tag 'LSCR'   +0x08 owner handler   +0x10 CScript*   +0x18 u32 (time,code)[] timed-event table  (points into hdr)
 *   +0x1c u16 count    +0x1e u16 next index   +0x20 ... the track header (0x20 prefix) followed by the embedded script image
 * `InitScript(script, name, ew+0x20)`: the script image starts right after the 0x20-byte common prefix. */

/* 0x003cc830 Open(ring): read 0x20 + remaining header from the ring; scan EVNT directory for the kind-1 section
 *            (u16@+8 == 1): ew->table = sec+0xc, ew->count = u16@sec+0xa;
 *            create LSDScrEx singleton if needed (sys__8LSDScrEx), new CScript (0x28), Create(NULL, 0x10 regs, 0x200 stack, slice 5),
 *            InitScript("LSCR"?, hdr+0x20), LSDScrEx::LinkA(ew), CScript::StartScript()  -> returns ew
 * 0x003ccbd0 Read: not used for payload (script is in the header) -> returns packet size
 * 0x003ccc40 Close: LSDScrEx::Delete; CScript::Delete; free
 * 0x003cccb0 Event(code): 1 -> LSDScrEx::Init()  (start music hook, Entry)
 *                         4 -> CScript::EndScene(script); then falls into 6
 *                         5 -> CFieldSocket::PauseFader(0)       6 -> PauseFader(1)
 * 0x003cca90 EventHandlerUpdate(ew): if next < count: tick = (u32)(LSDPlayer.time * ticks_per_sec);
 *            if table[next].time <= tick: ++next; CScript::CallEventT(script, table[next-1].time, 0,0,0)   -- fires LSD timed events
 */
void EventHandlerUpdate(struct _EventWork *ew) {
    if (ew->next < ew->count) {
        float t = sys_LSDPlayer->time * (float)sys_LSDPlayer->ticks_per_sec;
        u32 tick = (u32)t;
        u32 *e = (u32 *)((u8 *)ew->table + ew->next * 8);
        if (*e <= tick) { ew->next++; CScript_CallEventT(ew->script, *e, 0, 0, 0); }
    }
}

/* ---------------- GenericDataHandler  ('LGDT' tracks; static sys__18GenericDataHandler 0x42beb0, list m_pData 0x40adcc) -------------
 * Named data blobs delivered over the LSD stream and looked up by name from LSDScrEx (vibration tables, images, BGM, motions).
 * _GenericDataInfo (0x40): +0x00 tag, +0x08 owner, +0x10 name[16], +0x24 u32 w, +0x28 u32 h, +0x2c BufMemory*, +0x30 write cursor,
 *                          +0x34 size, +0x38 u8 (lo nibble = 0 main RAM, !=0 SPU/IOP sound memory)
 * 0x003cc100 Open: header 0x40 bytes (2x0x20); memset; name = hdr+0x20 (16 bytes); flags = byte@+0x30 >> 4; size = blocks<<4; AddData (linked list)
 * 0x003cc220 Read: first packet allocates BufMemory (size) -- or, for sound data (flag!=0), Sdrv::GetSoundMemory(0, size) -- then copies payload
 * 0x003cc3e0 Event: code 4 -> RemoveData(info, false);  0x003cc1f0 Close -> RemoveData(info, true)
 * 0x003cc420 Find(name): linear search by strcmp(name) over the list;  0x003cc4e0 AddData / 0x003cc590 RemoveData / 0x003cc6a0 ReleaseData
 */
