/*
 * LSDTrackHandlers.c -- remaining LSD device handlers owned by section E
 *   MPSServerHandler ('MPS ')   JP 0x0038e030..0x0038e3d0  MPSServer.cpp
 *   LsdEffectServer  ('.EFD')   JP 0x00324b00..0x00325000  LsdEffectServer.cpp
 *   LSDCaptionHandler('SBTD')   JP 0x0028a5c0..0x0028b3d0  CLSDCaptionHandler.cpp
 *   BGMServerHandler ('PCMS'/'DLBY')  JP 0x003897b0..0x0038a0b0  BGMServer.cpp
 * (ModelServerHandler, AnimServerHandler, CameraServerHandler, LightServerHandler, LipsHandler belong to section C.)
 */
/* ---- MPSServerHandler.  Open: new MPSModel(0xb0); read 0x32 bytes (track hdr + 0x12) into +0x20; if hdr.mode(+0x12)==0 the map data
 * streams in: BufMemory(total_blocks<<4).  non-zero mode => the map is an alias of a previously loaded one (+0x50 bit5 clear => register
 * with ModelServer list).  Read: copy payload to BufMemory at running offset; when complete create CFieldBG, CFieldBG::Create(buf,1),
 * remember model 0's root (+0x70).  Event: 1/3 -> CFieldBG::Dsp (show), 2/4 -> Clr (hide), 0 -> CFieldBG::Update(time). Close: ~MPSModel.
 */
/* ---- LsdEffectServer ('.EFD' = effect package, same HECO container as EFFECT.PKB, see notes/E/script_vm.md).
 * Open: new LsdEffect(0x40); header 0x20 bytes into +0x10; BufMemory(blocks<<4); Read: append; when full -> new Effect(0x48), Effect::Create(buf).
 * Event: 1 Run, 2 Stop, 3 Continue, 4 Stop, 5 Stop(pause), 6 Continue(resume).  Close: delete the Effect. */
/* ---- LSDCaptionHandler ('SBTD' subtitles).  Open: new LSDCaptionData(0x270): hdr 0x20 bytes at +0x1c; if hdr.mode==0 BufMemory(blocks<<4).
 * Read: payload = caption pack: { s16 nLines, s16 nWordsPerPage..., +0x14/+0x18 table offsets, fonts at +0x18 & +0x20 }; pointers are rebased
 * in place (+base); CreateFont(2, ...) (and 3 if present); FontDraw::Create(PSM 0x2c, 640x512); builds a MenuWindow with 2 MenuMessage
 * rows (0x98 bytes each) + optional extra word rows.  Event(time): closes the current line when time >= line.end (+0x18), opens the first line whose
 * [start(+0x14), end(+0x18)) contains `time`; SetWords() fills MenuMessage from LSDWordsData/Info.  Suppressed while the save menu is open.
 */
/* ---- BGMServerHandler ('PCMS' = PCM/ADPCM stream, 'DLBY' = Dolby).  See notes/E/audio.md for the Sdrv stream protocol.
 * CheckData: tag 'PCMS' (0x534d4350) -> type 2/3 ; 'DLBY' (0x59424c44) -> type 1.
 * Open: copy 0x40 header to +0x44 ; RingBuffer(u16@+0x58 * u32@+0x5c * 16) ; Sdrv::StreamOpen(0), StreamAllocBuf(h, 0x20000), StreamCreate(h, 2, 2),
 *       StreamSetParam(h, 0x3fff3fff /*L/R volume*/, rate/48000*4096 /*pitch*/)   rate = u16@hdr+0x26 (0xbb80)
 * Read: copy packet payload into the ring (only if it fits, otherwise return 0 = retry)
 * Event: 1 -> mark started, entry into FileIOLib poller (Polling feeds the stream);  4 -> StreamStop (fade if time>0);
 *        5 -> StreamPause(0) (once);  6 -> StreamPause(1)
 * Polling: IntrDisabled; track Sdrv status handles (flags +0xb8 b0/b1); when both ready and started: StreamStart(h,1) (b2);
 *          then each time Sdrv reports a free write window: if the ring has 0x1000 contiguous bytes -> memcpy to the IOP write buffer and
 *          StreamWriteData(h, 0x1000, 0x8000).
 * Close: two-phase: dispose poller; then wait until stream stat==3 -> StreamClose, free the ring.
 */
