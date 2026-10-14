/* Section I -- US retail OPENING.BIN overlay + retail title glue in SLUS_210.41 (cleaned Ghidra output).
 *
 * Ghidra program SH2US_OPENING.BIN (image base 0x0045ea80, MWo3 header 0x80 bytes, code 0x45eb00..0x46c6b8,
 * data 0x46c6e0..0x46cb00, 104 functions, no static ctors).  Calls into the main executable (SLUS_210.41)
 * are shown by their SLUS names.  The overlay's globals live in the *main* image's .sbss (0x440030..0x440060) and
 * its vtables are pre-placed in main .data (0x43f7c0..0x43f980) -- the overlay has no relocations.
 *
 * Conventions: u8/u16/u32 unsigned; `VCALL(o, off, ...)` = call through the vtable word at *(o+0x14) (CPolObj-
 * derived objects: vtable at +0x14, DelayDelete vtable at +0x20) or *(o+8) (MenuObj/MenuScene derived).
 * Analysis output, NOT compilable source.  Rust translation: port/crates/sh2_menu/src/title.rs (Build::Retail).
 * Notes: notes/I/opening.md.
 */

/* ------------------------------------------------------------------------------------------------------------
 * Shared title state (SLUS .bss 0x0045e940, 0x108 bytes; getter GetTitleShared() 0x415a60).
 * The first 0x100 bytes are the in-RAM image of the *SystemFile common block* (EE RAM 0x100000, see
 * notes/F/SystemFile.md / save_format.md): byte 0, byte 1, u8 flags[0x40] @+2, u8 flags2[0x40] @+0x42, bytes @+0x82/+0x83,
 * u32 @+0x84 (latest timestamp, merge = max), u32 @+0x88, u8 rest[0x74] @+0x8c.
 * ------------------------------------------------------------------------------------------------------------ */
typedef struct TitleShared {
    u8  common[0x100];   /* merged (bitwise OR) from every device's system file by deviceChecker::mCheckSystem */
    u8  merged;          /* +0x100 (0x45ea40): common[] has been OR-ed with 0x100000 once (CDMYStage::Start)    */
    u8  save_found;      /* +0x101 : a usable save exists  -> "Continue" is the default row                      */
    u8  intro_done;      /* +0x102 : the boot intro (device check + disclaimer + opening movie) was shown        */
    u8  pad;
    u32 device_save_mask;/* +0x104 (0x45ea44) : GetDeviceSaveMask()/SetDeviceSaveMask(), bit n = device n has save */
} TitleShared;

/* ------------------------------------------------------------------------------------------------------------
 * openingMessage (retail, 0x120 bytes).  JP: 0x3a83f0.. (0x1000-byte Polling); here Polling = 0x45f340 (0x1840 B).
 * ------------------------------------------------------------------------------------------------------------ */
typedef struct openingMessage {
    /* 0x00 */ u8  _cpolobj[0x14];   /* CPolObj base: owner/next/prev/flags/priority                               */
    /* 0x14 */ void **vptr;          /* 0x43f7d0 {+8 __dt__14openingMessageFv, +0xc Polling}                       */
    /* 0x18 */ void *_d18, *_d1c;    /* DelayDeleteObject (CList node), vtable at +0x20 = 0x43f7e0                 */
    /* 0x20 */ void **dd_vptr;
    /* 0x24 */ u8  _pad24[4];
    /* 0x28 */ int (*cb)(int event, void *arg); /* owner callback (CDMYStage::CBTitle), called with events 2,3,4  */
    /* 0x2c */ void *cb_arg;
    /* 0x30 */ GsxCamera *cam;       /* 640x448 / 512x448 GsxCamera, global CApp-like camera slot g_43feac        */
    /* 0x40 */ float cam_pos[4];     /* camera translation (vec4)                                                   */
    /* 0x50 */ float cam_rot[3];     /* rotation (x,y,z) applied with RotMatrixX/Y/Z in changeDispMode               */
    /* 0x64 */ int disp_w;           /* 0x280 (640) or 0x200 (512)                                                  */
    /* 0x68 */ int disp_h;           /* 0x1c0                                                                       */
    /* 0x6c */ primSound *snd;       /* menu SE (MenuSound @+0x2c); SE 0 = cursor, 2 = confirm, 3 = cancel          */
    /* 0x70 */ primMusic *bgm;       /* title BGM "OPENING/BGM803.SSV" (streamed)                                    */
    /* 0x74 */ primWin  *fader;      /* full-screen cover polygon; see Fader protocol below                          */
    /* 0x78 */ primTex  *res;        /* "opening/opening.dat" bundle (20 images + message table #20)                 */
    /* 0x7c */ u32 _d7c;
    /* 0x80 */ primWin  *title;      /* title window: 5 textured polys (copyright, emblem, rule, logo, PRESS START) */
    /* 0x84 */ primWin  *menu;       /* menu window (5 rows + 6 decoration polys) / disclaimer window while state 5-6 */
    /* 0x88 */ primCursor *cursor;   /* menu cursor                                                                  */
    /* 0x8c */ float _d8c, _d90f;    /* saved cursor position                                                       */
    /* 0x90 */ BufMemory *res_buf;   /* opening.dat buffer passed to initialize()                                    */
    /* 0x94 */ u8  return_mode;      /* from opening(u8): 1 = attract battle ended naturally (replay movie), 0 = skip */
    /* 0x98 */ prim2D *swirl[7];     /* title background layers (0 = backdrop tex 1, 1..6 = additive swirl tex 13..18)*/
    /* 0xd4 */ int n_swirl;          /* 7                                                                           */
    /* 0xd8 */ int sel;              /* row confirmed (0 New Game, 1 Continue, 2 Options, 3 Installation, 4 Theater) */
    /* 0xdc */ int pulse;            /* PRESS START pulse counter 0..0x7f                                           */
    /* 0xe0 */ int cur;              /* row under the cursor                                                        */
    /* 0xe4 */ u8  nav_a, nav_b;     /* remembered row/column used by the 5-slot cursor topology                    */
    /* 0xe6 */ u8  has_install;      /* (SSHSys+0x3c & 7) != 0 : "Installation" row enabled                          */
    /* 0xe7 */ u8  has_theater;      /* TitleShared.common[1] != 0 : "Theater" row enabled                           */
    /* 0xe8 */ TitleShared *shared;
    /* 0xec */ OptionMenu *options;  /* Options menu object (state 0x1d)                                             */
    /* 0xf0 */ dataAccess *load;     /* load screen (main-image dataAccess) while state 0x17/0x18                    */
    /* 0xf4 */ dataAccess *devchk;   /* boot device check (OPENING.BIN dataAccess, mode 2)                           */
    /* 0xf8 */ install *inst;        /* never created in retail (dead state 0x16)                                    */
    /* 0x100*/ int state;
    /* 0x104*/ int next_state;
    /* 0x108*/ int _d108;
    /* 0x10c*/ int timer;
    /* 0x110*/ int cb_event;         /* last event reported by dataAccess / Menu through CBEntry()                   */
} openingMessage;

/* Fader protocol (primWin at openingMessage+0x74, field offsets inside that object):
 *   +0x10c speed (frames)  +0x108 target (0 = cover, = speed -> reveal)  +0x118 busy  +0x11c mode (2 cover, 3 reveal)
 *   +0x102 "clear" flag: set when a reveal finished, cleared by a cover.
 *   cover(n)  = { +0x10c=n; +0x108=0; +0x118=1; +0x102=0; +0x11c=2 }       (original fadein)
 *   reveal(n) = { +0x10c=n; +0x108=n; +0x118=1;            +0x11c=3 }       (original fadeout)
 *   colour of the fader polygon: black 0x80000000 normally; white 0x80ffffff around the opening movie.            */

/* 0x45eb00  free function -- event sink passed to Menu/dataAccess (cb(event, arg, owner)) */
int cbOpeningEvent(int event, void *a1, void *a2)
{
    g_opening_event = event;    /* 0x440038 */
    g_opening_cb_a1 = a1;       /* 0x440030 */
    g_opening_cb_a2 = a2;       /* 0x440034 */
    return 1;
}

/* 0x45eb40  LSDPlayer start callback (plugged into LSDPlayer+0x7c) */
int LSD_CB__14openingMessageFv(void) { g_lsd_started = 1; return 1; }   /* 0x44003c */

/* 0x45eb60 */
openingMessage *__ct__14openingMessageFP10TitleShared(openingMessage *this, TitleShared *shared)
{
    __ct__7CPolObjFv(this);
    this->_d18 = this->_d1c = 0;
    this->dd_vptr = __vt__DelayDeleteObject;                  /* 0x437f60 */
    this->vptr    = __vt__14openingMessage;                   /* 0x43f7d0 */
    this->dd_vptr = __vt__14openingMessage_DelayDelete;       /* 0x43f7e0 */
    memset(&this->cam_pos, 0, 0x10); memset(&this->cam_rot, 0, 0x10);
    if (g_camera /*0x43feac*/) { __dt__9GsxCameraFv(g_camera, 1); g_camera = 0; }
    this->shared = shared;
    this->fader = this->_d7c = this->title = this->menu = this->cursor = this->snd = this->bgm = NULL;
    this->options = this->load = this->devchk = this->inst = NULL;
    this->cb_event = 0; this->state = 0; this->return_mode = 1; this->cam = 0; this->disp_w = this->disp_h = 0;
    this->swirl_ptrs = 0; this->timer = 0; this->pulse = 0;
    return this;
}

/* 0x45ec90 -- destructor; also releases fader (0x460c80), poller entry, music (0x3e2ce0), sound (0x3e2880) */
openingMessage *__dt__14openingMessageFv(openingMessage *this, short del) { /* ... */ }

/* 0x45ee20 */
void Finish__14openingMessageFv(openingMessage *this)
{
    this->state = 0x28;                  /* terminal state: Polling() is a no-op            */
    VCALL(this, 0xc /*Polling*/);        /* run once more so the object can be freed         */
}

/* 0x45ee60 */
void SetReturnMode__14openingMessageFUc(openingMessage *this, u8 mode) { this->return_mode = mode; }

/* 0x45ee90 -- called by CDMYStage::StartTitle (via 0x415d00) once opening.dat has arrived */
void initialize__14openingMessageFP9BufMemoryPFiPv_vPv(openingMessage *this, BufMemory *res, cbfunc cb, void *arg)
{
    this->res_buf = res;  this->cb = cb;  this->cb_arg = arg;
    if (this->cb) this->cb(1, this->cb_arg);                      /* event 1 = ready                                */
    this->res = new primTex();  primTex_initialize(this->res, res, 0);
    CPoller_Entry(&app->poller0, this, 0x80, 0);
    this->snd = new primSound(); primSound_initialize(this->snd);
    mSetupFader(this);                                            /* black cover, opaque                            */
    SaveMenuSection_Update();                                     /* apply brightness / sound mode / vibration      */
    if (this->shared->intro_done == 0) {                          /* first time since power on                       */
        this->shared->intro_done = 1;
        this->state = 1;                                          /* -> boot device check                            */
    } else if (this->return_mode == 0) {
        this->state = 0x12;                                       /* returned from attract battle that a key skipped -> title  */
    } else {                                                      /* returned after a full attract battle -> opening movie again */
        reveal(this->fader, 1);  this->state = 0x0b;
    }
}

/* 0x45f090 -- (re)create the 2D camera for a 640x448 or 512x448 display and reset the screen mode */
void changeDispMode__14openingMessageFii(openingMessage *this, int w, int h)
{
    if (this->disp_w == w) return;
    this->disp_w = w; this->disp_h = h;
    if (this->cam) { __dt__9GsxCameraFv(this->cam, 1); this->cam = 0; }
    this->cam = new GsxCamera(w, h, 0, 0x18, 0xb);                /* __ct__9GsxCameraFUiUiUiUiUi                    */
    g_camera = this->cam; this->cam->clearcol = 0;
    this->cam->near = 10.0f; this->cam->far = 32000.0f;
    if (w == 0x280) { SetViewMatrix(this->cam, 640.0f, 1.0f, 0.9333f, 1.0f, 16777000.0f);
                      Gsx_SetFFMode(0, 0, 1); Gsx_SetInter30(1); }          /* 640 wide: field mode, 30 Hz interlace   */
    else            { SetViewMatrix(this->cam, 512.0f, 0.8f,   0.9333f, 1.0f, 16777000.0f);
                      Gsx_SetFFMode(0, 1, 1); Gsx_SetInter30(1); }          /* 512 wide: frame mode                    */
    World_SetCamera(&m_World, 0, 0, this->cam);
    /* view matrix = identity * RotX(cam_rot[0]) * RotY(cam_rot[1]) * RotZ(cam_rot[2]); translation = cam_pos */
    GsxCamera_ApplyFrame(this->cam);
}

/* 0x45f340 -- Polling.  trigger = CPad(active)->core+0x6c, repeat = core+0x70, dirs = repeat & 0xf0.
 * 'key' = trigger & 0x2008 (CIRCLE | START).  Pad bits: 0x10 up, 0x20 right, 0x40 down, 0x80 left. */
int Polling__14openingMessageFv(openingMessage *this)
{
    CPad *pad = CPad_GetActive(0);
    u16 trigger = pad->core->trigger, dirs = pad->core->repeat & 0xf0, keys = dirs | trigger;
    bool key = (trigger & 0x2008) != 0;
    TitleShared *sh = this->shared;
    primWin *F = this->fader;

    switch (this->state) {
    /* ---------------- boot sequence (first run after power on) ---------------- */
    case 0x00:                                      /* wait for RegDat + JRing data to be loaded                        */
        if (RegDatApi_CheckRegDat() && JRing_DataLoadEndCheck()) this->state = 1;
        break;
    case 0x01:                                      /* start the boot device check (dataAccess mode 2, OPENING.BIN copy) */
        this->devchk = new dataAccess(); dataAccess_initialize(this->devchk, /*mode*/2, this->res, CBEntry, this);
        reveal(F, 1);
        this->state = 2;
        break;
    case 0x02:                                      /* cb_event comes from dataAccess via CBEntry (0x460ad0)             */
        if (this->cb_event == 6) changeDispMode(this, 0x200, 0x1c0);        /* UI wants the 512x448 screen            */
        else if (this->cb_event == 3) { sh->save_found = 1; this->state = 4; }  /* a save exists                     */
        else if (this->cb_event == 2)               { this->state = 4; }        /* nothing usable / user said "no"   */
        break;
    case 0x04:                                      /* event 4 = device-check UI finished                                */
        if (this->cb_event == 4) { this->state = 5; cover(F, 1); }
        break;
    case 0x05:                                      /* DISCLAIMER ("This story is a work of fiction...", opening.dat #0) */
        if (!F->clear) { if (!F->busy) { changeDispMode(this, 0x280, 0x1c0); mSetupTrialWin(this, 0); reveal(F, 0x20); } }
        else { this->timer = 0; this->state = 6; }
        break;
    case 0x06:
        this->timer++;
        if (key) { PlaySE(this->snd, 2); this->timer = 0x1c2; }
        if (this->timer > 0x1c2) { this->state = 7; cover(F, 0x20); }      /* 450 frames (7.5 s) or any key             */
        break;
    case 0x07:
        if (!F->busy) { mReleaseTrialWin(this); reveal(F, 1); this->state = 0x0b; }
        break;
    case 0x0b:                                      /* opening movie                                                     */
        changeDispMode(this, 0x280, 0x1c0);
        mSetupLSD(this);                            /* new LSDPlayer, PlugDevice x3 (0x4597d0/0x459940/0x459840), start-cb  */
        if (LSDPlayer_Reset(g_LSDPlayer)) {         /* player idle                                                       */
            g_lsd_started = 0;
            LSDPlayer_startStream(g_LSDPlayer, SysTool_SetPathname("opening/demo.lsd"));
            this->state = 0x0c;
        }
        break;
    case 0x0c:
        if (g_lsd_started) {
            set_fader_colour(F, 0xff,0xff,0xff, 0x80);                     /* white                                      */
            if (key || LSDPlayer_Reset(g_LSDPlayer)) {                     /* skipped, or finished                       */
                int speed = key ? 0x20 : 4;
                this->state = 0x0d;
                cover(F, speed);                                           /* fade to white                              */
            }
        }
        break;
    case 0x0d:
        if (!F->busy) {
            if (!LSDPlayer_Reset(g_LSDPlayer)) { LSDPlayer_Pause(g_LSDPlayer); LSDPlayer_Stop(g_LSDPlayer); }
            this->timer = 0x10; this->state = 0x0e;
        }
        break;
    case 0x0e:
        if (this->timer == 0) { LSDPlayer_Reset(g_LSDPlayer); delete g_LSDPlayer; g_LSDPlayer = 0;
                                Gsx_SetFFMode(0, 1, 1); this->state = 0x12; }
        else this->timer--;
        break;
    /* ---------------- title ---------------- */
    case 0x12:                                      /* build title screen; music starts inside mSetupTitleWin            */
        if (!F->clear) { if (!F->busy) { changeDispMode(this, 0x280, 0x1c0); mSetupTitleWin(this); reveal(F, 0x20); } }
        else { this->timer = 0; this->state = 0x13; }
        break;
    case 0x13:                                      /* PRESS START                                                       */
        this->timer++;
        if (this->timer <= 0x4b0) {
            if (!key) {                             /* pulse polygon 4 (PRESS START): alpha 0..0x7e..0 over 128 frames     */
                this->pulse++;
                if (this->pulse < 0x40)      poly_alpha(this->title, 4, this->pulse * 2);
                else if (this->pulse < 0x80) poly_alpha(this->title, 4, (this->pulse - 0x40) * -2 + 0x80);
                else                         this->pulse = 0;
            } else {
                PlaySE(this->snd, 2);
                mSetupMenuWin(this);                /* 5 rows + cursor; default row = sh->save_found ? 1 : 0             */
                this->state = 0x14; this->timer = 0;
                poly_alpha(this->title, 4, 0);
            }
        } else {                                    /* 1201 frames idle -> attract battle                                */
            primMusic_stop(this->bgm);              /* fade out 0x32                                                     */
            set_fader_colour(F, 0, 0, 0, 0x80);
            cover(F, 0x20);
            this->state = 0x15; this->next_state = 0x23;
            if (this->cb) this->cb(2, this->cb_arg); /* CDMYStage::CBTitle(2): create + start the battle demo           */
        }
        break;
    case 0x14:                                      /* MENU                                                              */
        if (!key) { if (keys) { this->timer = 0; mMoveMenuCursor(this, keys); } }
        else {
            primMusic_stop(this->bgm); if (this->bgm) { delete this->bgm; this->bgm = 0; }
            PlaySE(this->snd, 2);
            this->state = 0x15; set_fader_colour(F, 0, 0, 0, 0x80); cover(F, 0x20);
            switch (this->sel) {
            case 0:  /* NEW GAME */
                if (!this->load /*dataAccess unused*/) {
                    memcpy(0x100000 /*system common block*/, sh->common, 0x100);   /* bytes 0,1,[2..0x41],[0x42..0x81],0x82,0x83,0x84,0x88,[0x8c..0xff] */
                    mInitNewGame(this);             /* SaveData reset, world-map flags &= ~7, MENU[0x80]=0, FUN_003bc710(0,0) */
                    InitNewGameFlags(GetDeviceSaveMask());
                    this->next_state = 0x26;
                }
                break;
            case 1:  /* CONTINUE -> main-image dataAccess in load mode */
                this->next_state = 0x17;
                this->load = new dataAccess(); dataAccess_initialize(this->load, /*load*/1, CBEntry, this);
                break;
            case 2:  /* OPTIONS */
                this->next_state = 0x1d; g_opening_event = 0;
                this->options = new OptionMenu(/*first scene*/0x10, cbOpeningEvent, &this->cb);
                break;
            default: /* 3 Installation (only selectable if SSHSys flags&7) / 4 Theater */
                if (this->cb) this->cb(3, this->cb_arg);   /* CDMYStage::CBTitle(3) -> StartTheater() (FIELD.BIN, opening/theater.dat) */
                this->next_state = 0x20;
                break;
            }
        }
        this->timer++;
        if (this->timer > 0xe10) {                  /* 3600 frames idle on the menu -> attract battle                    */
            primMusic_stop(this->bgm);
            this->state = 0x15; this->next_state = 0x23;
            if (this->cb) this->cb(2, this->cb_arg);
            set_fader_colour(F, 0, 0, 0, 0x80); cover(F, 0x20);
        }
        break;
    case 0x15:                                      /* wait for the cover, then tear the title down and go to next_state */
        if (!F->busy) { mReleaseTitleWin(this); mReleaseMenuWin(this);
                        if (this->bgm) { delete this->bgm; this->bgm = 0; }
                        this->state = this->next_state; }
        break;
    case 0x16:                                      /* DEAD in retail: HDD "install" start                               */
        changeDispMode(this, 0x200, 0x1c0); install_start(this->inst); this->inst = 0; reveal(F, 1); this->state = 0x18; break;
    case 0x17:                                      /* CONTINUE: the load screen takes over                              */
        changeDispMode(this, 0x200, 0x1c0);
        dataAccess_start(this->load, /*STARTMODE*/1, 0, 0); this->load = 0;   /* object frees itself on event 4          */
        reveal(F, 1); this->state = 0x18;
        break;
    case 0x18:
        if (this->cb_event == 3) this->state = 0x19;       /* load screen quit (O on "quit")                                 */
        else if (this->cb_event == 5) this->state = 0x27;  /* a slot was loaded; dataAccess already did FieldMapJump        */
        break;
    case 0x19:
        if (this->cb_event == 4) { cover(F, 1); this->state = 0x12; }   /* load screen finished -> rebuild title            */
        break;
    case 0x1d:                                      /* OPTIONS                                                           */
        if (!F->clear) { if (!F->busy) { changeDispMode(this, 0x200, 0x1c0); this->options->start_flag = 0x11; reveal(F, 0x10); } }
        else this->state = 0x1e;
        break;
    case 0x1e:
        if (g_opening_event == 5) { this->state = 0x1f; cover(F, 0x10); }   /* Menu reported "closed" (event 5)           */
        break;
    case 0x1f:
        if (!F->busy) this->state = 0x12;
        break;
    case 0x20:                                      /* THEATER / generic exit: reveal, then tell the owner we are done    */
        if (!F->clear) { if (!F->busy) { changeDispMode(this, 0x200, 0x1c0); reveal(F, 0x20); } }
        else { int r = this->cb ? this->cb(4, this->cb_arg) : 0; DelayDelete(this); this->state = 0x21; }
        break;
    case 0x22:
        if (!F->busy) this->state = 0x12;
        break;
    case 0x23:                                      /* ATTRACT BATTLE: this object ends; CDMYStage runs the battle        */
        if (this->bgm) { delete this->bgm; this->bgm = 0; }
        reveal(F, 1);
        changeDispMode(this, 0x200, 0x1c0);
        Gsx_SetFFMode(0, 1, 2);
        if (this->cb) this->cb(4, this->cb_arg);    /* CBTitle(4): CDMYStage forgets us                                  */
        DelayDelete(this);
        this->timer = 0; this->state = 0x24;
        break;
    case 0x26:                                      /* NEW GAME: first map                                               */
        FieldMapJump("OP_00_U", 0);                 /* JP demo used "WORLDMAP"                                           */
        reveal(F, 1); changeDispMode(this, 0x200, 0x1c0);
        this->state = 0x27;
        break;
    case 0x27:                                      /* leave (also after a successful load)                              */
        this->state = 0x28;
        if (this->cb) this->cb(4, this->cb_arg);
        DelayDelete(this);
        break;
    }
    return 0;
}

/* 0x460ad0 */ void CBEntry__14openingMessageFiPv(int event, openingMessage *this) { this->cb_event = event; }

/* 0x460b00 -- fader: one 640x448 black polygon on MenuObj layer, cover(1) so the screen starts black */
void mSetupFader__14openingMessageFv(openingMessage *this)
{
    primWin *w = new primWin();  this->fader = w;
    CPoller_Entry(&app->poller0, w, 0x80, 0);
    w->tex = 0; w->autoRelease = 1; VCALL(w, 0x44+0x20 /*Init*/);
    w->mode = 0;
    primWin_setItem(w, 1, 1, 0);                     /* 1 tex block, 1 poly, 0 text */
    primWin_createPoly(w, 0, 0, 0, 0, 0x280, 0x1c0); /* fullscreen */
    set_poly_colour(w, 0, 0,0,0, 0x80);
    primWin_buildWin(w, 0xf, -0x40, 0, 0, 0, 0);
    cover(w, 1);
}
void mReleaseFader__14openingMessageFv(openingMessage *this)       /* 0x460c80 */
{ if (this->fader) { ReleaseOT(&this->fader->win); VCALL(this->fader, dd, 0xc); this->fader = 0; } }

/* 0x460d10 -- one-polygon window showing resource #idx (disclaimer = 0) */
void mSetupTrialWin__14openingMessageFi(openingMessage *this, int idx)
{
    primWin *w = new primWin(); this->menu = w; CPoller_Entry(&app->poller0, w, 0x80, 0);
    w->tex = this->res; w->autoRelease = 1;
    primWin_setItem(w, 1, 1, 0);
    w->texblock[0] = primTex_setWinTex(this->res, &w->win, idx + 0 /*opening.dat #idx*/, 0);
    primWin_createTexPoly(w, 0, 0, 0, 0, 0, 0);
    primWin_buildWin(w, 3, -0x40, 0, 0, 0, 0);
    reveal(w, 0x20);
}
void mReleaseTrialWin__14openingMessageFv(openingMessage *this) { /* 0x460e70: same release pattern on this->menu */ }

/* 0x460f00 -- TITLE window: 5 textured polys + 7 prim2D swirls + BGM */
void mSetupTitleWin__14openingMessageFv(openingMessage *this)
{
    static const short pos[5][2]  = { {0x38,0x176}, {0xe8,0x54}, {0x34,0xad}, {0x64,0x7c}, {0xd0,0x122} };  /* x-0x40, y @0x46c700 */
    primWin *w = new primWin(); this->title = w; w->tex = this->res; /* ... */
    primWin_setItem(w, 5, 5, 0);
    for (int i = 0; i < 5; i++) {                   /* opening.dat #2..#6: copyright, emblem, rule, SHADOW HEARTS II, PRESS START button */
        w->texblock[i] = primTex_setWinTex(this->res, &w->win, i + 2, i);
        primWin_createTexPoly(w, i, i, pos[i][0] - 0x40, pos[i][1], 0, 0);
    }
    poly_alpha(w, 4, 0);                            /* PRESS START invisible until the pulse starts */
    this->pulse = 0;
    /* swirl layers: prim2D(layer 6): [0] backdrop #1 at (-64,0) ; [1..4] #13..#16 centre modes 4,1,3,0, rot -0.0002 ; [5] #17 rot +0.0006 mode 2 ; [6] #18 mode 2 */
    for (i = 0; i < 7; i++) { this->swirl[i] = new prim2D(6); this->swirl[i]->tex = this->res->data; prim2D_setDisp(this->swirl[i], tex_ids[i], ...);
                              setRGBA(7f,7f,7f,0x19); setBlendMode(1); setCenterMode(modes[i]); }
    this->n_swirl = 7;
    this->bgm = new primMusic(); primMusic_initialize(this->bgm, 1 /*stream*/); primMusic_play(this->bgm, "OPENING/BGM803.SSV");
}
void mReleaseTitleWin__14openingMessageFv(openingMessage *this)    /* 0x461c60: prim2D::DelayDeleteRequest x7, release title window */
{ for (i = 0; i < this->n_swirl; i++) if (this->swirl[i]) { prim2D_DelayDeleteRequest(this->swirl[i]); this->swirl[i] = 0; }
  if (this->title) { release_win(this->title); this->title = 0; } }

/* 0x461d60 -- MENU: 5 rows (3 texture blocks = opening.dat #7/#8/#9: disabled / normal / highlighted) + 6 frame pieces (#10) + primCursor */
void mSetupMenuWin__14openingMessageFv(openingMessage *this)
{
    static const short row_xy[5][2] = { {108,264}, {268,296}, {406,264}, {108,324}, {406,324} };   /* @0x46c720: 0 NewGame, 1 Continue, 2 Options, 3 Installation, 4 Theater */
    this->cur = this->sel = this->shared->save_found ? 1 : 0;
    this->nav_a = this->nav_b = 0;
    this->has_install = (SSHSys_sys->flags & 7) != 0;
    this->has_theater = this->shared->common[1] != 0;
    /* ... primWin with 4 tex blocks (#7,#8,#9,#10), 11 polys, setItem(4, 11, 0) */
    for (u = 0; u < 5; u++) {
        int blk = (u == this->cur) ? 2 : ((u == 3 && !this->has_install) ? 0 : 1);   /* 2 = highlighted, 0 = disabled */
        createTexPoly(w, u, blk, row_xy[u][0], row_xy[u][1], 0, u);                   /* row u of the 128x160 atlas */
        if (blk == 0) { set_poly_colour(w, u, 0x20,0x20,0x20, 0x80); }
    }
    for (i = 0; i < 6; i++) { createTexPoly(w, 5 + i, 3, decor[i].x, decor[i].y, 0, 0); SetUV(decor_uv[i]); SetSize(decor[i].w, decor[i].h); }
    if (!this->has_theater) { hide polys 0x5c4/0x668/0x290 ...; }    /* frame pieces around row 4 / 3 hidden when the row is unavailable */
    this->cursor = new primCursor(); createCursor(this->cursor, 0, 2, 8, 1); /* priority 10 */
    cursor_select(this->cursor, GetPlace(this->menu, 0, this->cur)); QuickMove(this->cursor);
}

void mSetupLSD__14openingMessageFv(openingMessage *this)   /* 0x462620 */
{
    if (!g_LSDPlayer) { g_LSDPlayer = new LSDPlayer();                 /* 0xc0 bytes, registers on system poller */
                        LSDPlayer_PlugDevice(0x4597d0); LSDPlayer_PlugDevice(0x459940); LSDPlayer_PlugDevice(0x459840);
                        g_LSDPlayer->start_cb = LSD_CB__14openingMessageFv; LSDPlayer_Reset(g_LSDPlayer); }
}

/* 0x4626d0 -- cursor movement on the 5-slot topology
 *      0 (NewGame)        2 (Options)
 *             1 (Continue)
 *      3 (Installation)   4 (Theater)       keys: 0x10 up 0x20 right 0x40 down 0x80 left               */
void mMoveMenuCursor__14openingMessageFUs(openingMessage *this, u16 keys)
{
    int old = this->cur;
    set_poly_state(this->menu, this->sel, 1 /*normal*/);
    switch (this->cur) {
    case 4: if (keys & 0x80) { if (!this->has_install) this->cur = 1; else { this->nav_b = 0; this->cur = 3; } }
            else if (keys & 0x10) this->cur = 1; break;
    case 3: if (keys & 0x20) { if (!this->has_theater) this->cur = 1; else { this->nav_b = 1; this->cur = 4; } }
            else if (keys & 0x10) this->cur = 1; break;
    case 2: if (keys & 0x80) { this->nav_b = 0; this->cur = 0; } else if (keys & 0x40) this->cur = 1; break;
    case 1: if (keys & 0x20)      { if (!this->nav_a || !this->has_theater) { this->nav_a = 0; this->cur = 2; } else { this->nav_a = 1; this->cur = 4; } }
            else if (keys & 0x80) { if (!this->nav_a || !this->has_install) { this->nav_a = 0; this->cur = 0; } else { this->nav_a = 1; this->cur = 3; } }
            else if (keys & 0x10) { this->cur = this->nav_b ? 2 : 0; }
            else if (keys & 0x40) { if ((!this->nav_b || !this->has_theater) && this->has_install) { this->nav_b = 0; this->cur = 3; }
                                    else if ((this->nav_b || !this->has_install) && this->has_theater) { this->nav_b = 1; this->cur = 4; } }
            break;
    case 0: if (keys & 0x20) { this->nav_b = 1; this->cur = 2; } else if (keys & 0x40) this->cur = 1; break;
    }
    if (old != this->cur) PlaySE(this->snd, 0);
    this->sel = this->cur; set_poly_state(this->menu, this->sel, 2 /*highlighted*/);
    cursor_select(this->cursor, GetPlace(this->menu, 0, this->sel));
}

void mReleaseMenuWin__14openingMessageFv(openingMessage *this)    /* 0x462cd0 */
{ release_win(this->menu); this->menu = 0; if (this->cursor) { ReleaseOT cursor; delete cursor; this->cursor = 0; } }

/* 0x462e70 -- New Game initialisation */
void mInitNewGame__14openingMessageFv(void)
{
    SaveData_Reset(&g_SaveData /*0x457ef0*/);        /* FUN_00360440 */
    InitFieldSaveData();                             /* FUN_003f7b90 = FUN_003fe1f0 + FUN_003f3750 */
    u8 *wm = GetWorldMapSection() /*"WM"*/ ;
    for (int i = 0; i < 0x40; i++) wm[0xc + i] &= ~7;/* clear the three per-area progress bits */
    MENU->data[0x80] = 0;
    FUN_003bc710(0, 0);                              /* big default-apply routine (0x2150 bytes)  */
}

/* ------------------------------------------------------------------------------------------------------------
 * deviceChecker (0x462f60..0x4649xx) -- the boot-time memory-card / "PlayStation BB Unit" scan (JP 0x3990f0)
 * struct (0x100 bytes): +0x14 vptr 0x43f7f0 {+8 dtor, +0xc Polling}; +0x18 mode (0 idle, 1 mCheckAll, 2 mPollMC,
 * 3 mCheckSystem); +0x1c u32 saves found; +0x20 step; +0x24 done flag (set when a mode finished); +0x25 changed
 * flag (hot-plug); +0x28..0x40 McRaw state; +0x80 sceMc info buf; +0xc0 TitleShared* (OR target);
 * per device d (0 = MC slot1, 1 = MC slot2, 2 = HDD) at +0xc0+d*0x10:
 *     +4 probed, +5 present(formatted), +6 has_system_file, +7 has_save_dir(+HDD: mounted), +8 error,
 *     +9 error2, +0xa flag, +0xc free KB(int), +0x10 pad
 * ------------------------------------------------------------------------------------------------------------ */
/* 0x463040 */ void initialize__13deviceCheckerFPUc(deviceChecker *d, TitleShared *sh) { d->shared = sh; d->mode = 0; d->step = 0; d->done = d->changed = 0; CPoller_Entry(&app->poller0, d, 0x80, 0); }
/* 0x4630b0 */ void checkDeviceAll(deviceChecker *d) { if (d->shared) memset(d->shared, 0, 0x100); d->mode = 1; d->step = 0; d->saves = 0; d->done = 0; }
/* 0x463120 */ void checkPollMC(deviceChecker *d)   { d->mode = 2; d->step = 0; d->changed = 0; d->done = 0; }
/* 0x463160 */ void finishPollMC(deviceChecker *d)  { d->mode = 0; SaveData_Close(&g_SaveData); }
/* 0x4631a0 */ int  Polling(deviceChecker *d) { switch (d->mode) { case 1: mCheckAll(d); break; case 2: mPollMC(d); break; case 3: mCheckSystem(d); break; } return 0; }
/* 0x463240 */ int  recheck(deviceChecker *d) { d->mode = 3; d->saves = 0; d->done = 0;
                    if (!dev0.present || !dev1.has_system) { d->step = 2; return 1; } d->step = 0; return 0; }
/* mCheckSystem (0x4632c0) / mPollMC (0x463a00) / mCheckAll (0x463d30): per device d: SaveData_Open(d) -> poll io state (0x457f14: 1 busy,
 * 2 ok, 3 failed) -> read slot/system info (0x457f10) -> fill device record -> if the system file exists: SaveData_ReadCommon(d->shared)
 * with byte-wise OR merge of the 0x100-byte common block (+ max of the timestamp at +0x84) -> count used slots -> SaveData_Close.
 * mCheckAll then runs mMcRawCheck (0x464940: sceMc GetInfo/Format probe of port 0/1) and finally SetDeviceSaveMask(bits). */

/* ------------------------------------------------------------------------------------------------------------
 * dataAccess, OPENING.BIN copy (0x464c70..0x468830): only the INITIAL DEVICE CHECK path of the JP class (mode 2).
 * The load/save screen stays in the main image (0x3d37d0..).  This object: vptr 0x43f800 / DelayDelete 0x43f810;
 *   +0x24 cb, +0x28 cb arg, +0x2c primSound, +0x30 msg table #0 (saveLoad.dat res 0x25), +0x34 msg table #1 (opening.dat #20),
 *   +0x38 primTex (opening.dat), +0x3c main window, +0x40 warning window, +0x44 progress window, +0x78 sel, +0x7c n_items,
 *   +0x80 list window, +0x88 cursor, +0xa4 mode(2), +0x12c state, +0x134 result/message class, +0x13c deviceChecker*,
 *   +0x140 TitleShared*, +0x150 outer state, +0x15c variant, +0x161..0x163 flags, +0x170.. required-KB table.
 * ------------------------------------------------------------------------------------------------------------ */
/* 0x464f70 initialize: g_saveload_ready=0; ReadOrder("saveLoad/saveLoad.dat", DVD_CBFunc 0x464bb0, this); creates the
 *          deviceChecker (0x100 B), primSound, hooks the poller; sets required KB table from SaveData_GetSize(). */
/* 0x4651a0 Polling (outer): state 0 -> mInitialDeviceCheck(keys) returns 1 when done -> if result==4 -> 0x1f else release
 *          windows -> 0x1e; 0x1e waits for fader; 0x1f: event 4 callback and DelayDelete.                                  */

/* mInitialDeviceCheck state machine (0x4664a0, state @+0x12c):
 *  0  start deviceChecker.checkDeviceAll(); -> 2
 *  1  (re-check after cancel) close device, rebuild; -> 2
 *  2  wait deviceChecker.done: decide message class (+0x134):
 *        active devices == 0                                  -> class 0  -> state 10
 *        usable device with enough free KB (getFreeDeviceNum)  -> state 3 (event 2 "no problem"/3 "save found") or 5
 *        otherwise class 1..0x10 chosen from (isMC1/isMC2/isHDD/getStatusE8/E9/EA) -> state 10 (show warning)
 *  3  wait saveload.dat; event 3 (save found) / 2 (none); -> 4
 *  4  return 1 (done)
 *  5  UI wanted: wait saveload.dat, build BG (mSetupBG), cb(6) "need UI" -> 6;   6 progress / system-save check; 7 hold 60 frames; 8 wait O;
 *  9  fade out; 10 setup warning window (mSetupInitialWarning, list of "Start the game." / "Don't start the game." rows); 11 choose (up/down
 *     mCheckDirKey, O confirm, X cancel); 12 return 1; 13/14 close device -> restart / event cb(2|3) -> 12.                                */

/* ------------------------------------------------------------------------------------------------------------
 * Options menu: OptionMenu (Menu subclass, 0xa40 B, 0x46adb0) with scenes: OptionScene (0x3210 B, id 0x10),
 * PictureScene (help picture), CursorScene, HelpScene (help strip), PanelScene (label panel).  Callback events
 * (cbOpeningEvent): 6 ask-to-open, 0 opened, 1 first scene ready, 2 closing, 3 closed, 5 destroyed.
 * OptionScene items (MSD text ids with bit mask 0x4e = ids 1,2,3,6):  1 Vibration (MENU[8] b0-1: 0 ON / 2 OFF as in JP),
 * 2 Sound out (MENU[8] b2-3, UpdateSoundOut), 3 Brightness (MENU[0x278] 1..10, CApp::SetBright(v*0.03+0.7)),
 * 6 (MENU[9] b0-1).  Choices disabled when (SSHSys+0x3c >> 3 & 7) == 0.  Apply() runs on exit: SaveMenuSection::UpdateVibration, UpdateSoundOut.
 * State handlers are MW pointer-to-member-functions (table 0x46c860): stOpen 0x469a90 -> stMain 0x469f90 -> stClose 0x469d80.
 * ------------------------------------------------------------------------------------------------------------ */

/* ============================================================================================================
 * Main-image side (SLUS_210.41)
 * ============================================================================================================ */

/* 0x415aa0 */ int opening__Fv(void)  { if (g_stage) return 1; g_stage = new CDMYStage(); return SSHSys_SetAPI(SSHSys_sys, g_stage); }
/* 0x415b20 */ void ReturnToTitle__Fv(void) { opening__Fv(); }                    /* SSHSys request 0x40 target            */
/* 0x415b40 */ int opening__FUc(u8 return_mode)                                   /* returning from the attract battle       */
{ if (g_stage) return 1; g_stage = new CDMYStage(); CDMYStage_SetReturnMode(g_stage, return_mode); return SSHSys_SetAPI(SSHSys_sys, g_stage); }

/* CDMYStage (0x2c bytes in the allocator call, fields to +0x29) : SSHApi @0, CPolObj @8 (priority 0x80 on poller 0x48)
 *   +0x20 openingMessage*, +0x24 last owner-event, +0x28 return mode, +0x29 "keep resident data / special exit" flag.
 *   statics: stage state 0x43ff0c (0 idle, 1 load needed, 2 loading, 3 running, 4 closing, 5 ready-to-unload),
 *            0x43fef8 opening.dat BufMemory*, 0x43fefc pending action (2 demo, 3 theater), 0x43ff00 g_stage, 0x43ff04 demo*, 0x43ff10 demo index. */
/* 0x415c50 */ CDMYStage *__ct__9CDMYStageFv(CDMYStage *s) { /* vptrs 0x43c0e0/0x43c100 */ s->title = 0; s->event = 0; s->has_mode = 0; g_stage_state = 1; return s; }
/* 0x415f00 */ int preLoad__9CDMYStageFv(CDMYStage *s)                                  /* SSHApi::preLoad, called every frame by SSHSys::Polling until it returns 1 */
{ int r = 0; if (g_stage_state == 3) r = 1;
  else if (g_stage_state != 2 && g_stage_state == 1) { int l = Overlay_Load(&SSHSys_sys->overlay, "OPENING.BIN", CBOverlay, 0, s);
                                                       if (l == 0) g_stage_state = 2; else if (l == 3) g_stage_state = 3; }
  return r; }
/* 0x415ee0 */ void CBOverlay__9CDMYStageFiPv(...) { g_stage_state = 3; }
/* 0x415fe0 */ int Start__9CDMYStageFv(CDMYStage *s)
{ CPoller_Entry(&app->poller0, &s->polobj, 0x80, 0);
  /* merge the in-game system common block back into the title state */
  for (i = 0; i < 0x100; i++) g_title_shared.common[i] |= ((u8*)0x100000)[i];  (byte ranges as in TitleShared)
  s->title = new openingMessage(&g_title_shared);                                    /* OPENING.BIN 0x45eb60 */
  changeDispMode(s->title, 0x280, 0x1c0);                                            /* OPENING.BIN 0x45f090 */
  if (!s->has_mode) ReadOrder(SetPathname("opening/opening.dat"), _dvd_callback, 0, 0, s, 0);
  else StartTitle(s);
  g_title_shared.merged = 1; return 1; }
/* 0x4161f0 */ int _dvd_callback__FiP9BufMemoryiPcPv(int tag, BufMemory *b, ...) { g_opening_dat = b; if (g_stage) StartTitle(g_stage); return 0; }
/* 0x415d00 */ void StartTitle__9CDMYStageFv(CDMYStage *s)
{ if (s->has_mode) openingMessage_SetReturnMode(s->title, s->mode);                   /* 0x45ee60 */
  s->has_mode = 0;
  openingMessage_initialize(s->title, g_opening_dat, CBTitle, s); }                  /* 0x45ee90 */
/* 0x415d70 */ void CBTitle__9CDMYStageFiPv(int ev, CDMYStage *s) { s->event = ev; if (ev == 4) s->title = 0; }
/* 0x416240 */ bool closeInquiry__9CDMYStageFv(void)
{ bool busy = g_stage_state != 5;
  if (busy) g_stage_state = 4; else { Overlay_Unload(&SSHSys_sys->overlay, 0); g_stage_state = 0; }
  return busy; }
/* 0x4162a0 */ int Polling__9CDMYStageFv(CDMYStage *s)
{ if (g_stage_state == 4) {                                          /* closing requested */
    if (s->event != 2 && s->event != 3) {
      if (!s->has_mode) { if (!s->title) g_stage_state = 5; else { openingMessage_Finish(s->title); s->title = 0; } }
      else { if (g_pending == 2) openingBattleDemo_start(g_demo); else if (g_pending == 3) InitFieldSocketCB(StartTheater, 0);
             g_stage_state = 5; } } }
  else if (g_stage_state == 3 && s->event == 2) {                    /* title asked for the attract battle */
    s->has_mode = 1; g_demo = new openingBattleDemo(); openingBattleDemo_initialize(g_demo, g_opening_dat->data, 0x13, &g_title_shared);
    g_stage_state = 4; g_pending = 2; }
  else if (g_stage_state == 3 && s->event == 3) { s->has_mode = 1; g_stage_state = 4; g_pending = 3; }  /* theater */
  return 0; }

/* 0x415be0  StartTheater: creates the FIELD.BIN "theater" object (0x553ad0, 0x1bc B; loads opening/theater.dat) */
/* 0x3f4dc0  InitFieldSocketCB(cb,arg): CFieldSocket in callback mode (+0x34 cb / +0x38 arg replace the map load) */

/* ------------------------------------------------------------------------------------------------------------
 * openingBattleDemo (retail, main image 0x416510..0x416ed0): attract-mode battle through BtlSocket.
 * +0x14 vptr 0x43c120 {+8 dtor, +0xc Polling}; +0x28 state; +0x2c done(btl cb 0 seen) ; +0x2d (cb 2 seen); +0x2e not_skipped;
 * +0x2f go; +0x30 over; +0x34 timer; +0x38 battle no (BtlSocket+0x190); +0x3c bgm; +0x40 monster-set id; +0x44/48/4c prim2D banners;
 * +0x50 tex data; +0x54 layer.
 * Table @0x4306b0, 6 x 16 bytes { s16 monset, scenario, battle, bgm, party[4] } (party -1 = none):
 *   0: monset   3 scn 0 battle 77 bgm 401 party {5,11}        3: monset 146 scn 3 battle 42 bgm 407 party {8,9,10}
 *   1: monset  16 scn 1 battle  6 bgm 401 party {0,1,2}       4: monset 227 scn 4 battle 89 bgm 405 party {1,4,6,7}
 *   2: monset  82 scn 2 battle 28 bgm 401 party {0,2,5,6}     5: monset 249 scn 5 battle 73 bgm 403 party {0,2,3,5}
 * Rotation: v = ((TitleShared.common[0x14] & 0x40) != 0) + ((common[0x14] & 0x80) != 0);   (= flags1[0x12] bits 6/7, system-file progress bits)
 *      v == 0: indices 0..2 cycle      v == 1: 3..5 cycle (first pick 3)       v == 2: 0..5 cycle.
 * ------------------------------------------------------------------------------------------------------------ */
/* 0x4166b0 initialize(demo, tex, layer, shared) */
{ v = bit6(shared->common[0x14]) + bit7(shared->common[0x14]);
  if (v == 2)      { idx = g_demo_idx++; if (g_demo_idx > 5) g_demo_idx = 0; }          /* idx = value before the increment */
  else if (v == 1) { if (g_demo_idx < 3) g_demo_idx = 3; idx = g_demo_idx++; if (g_demo_idx > 5) g_demo_idx = 3; }
  else             { idx = g_demo_idx++; if (g_demo_idx > 2) g_demo_idx = 0; }
  e = &tbl_attract_battles[idx];
  demo->monset = e.monset; demo->battle = e.battle; demo->bgm = e.bgm;
  MENU->data[0x80] = 0; FUN_00287990(0); SaveMenuSection_ClearBattleTeam(0);
  for (k = 0; k < 4; k++) if (e.party[k] != -1) { FUN_002873a0(e.party[k], 0); SaveMenuSection_JoinBattle(e.party[k], 0, 0); FUN_003c02f0(e.party[k], e.scenario); }
  demo->state = 0; CPoller_Entry(&app->poller0, demo, 0x80, 0); demo->tex = tex; demo->layer = layer; }
/* 0x4169a0 Polling: 0 wait go -> banner prim2D (layer 0xe, tex data +0x50, uv (1,1,0xd2,0x78), rgba 7f, fade-in 0x10)
 *   1: InitBtlSocket(); btl->cb = BtlCallBack; btl->arg = demo; btl->demoFlag(+0x19c)=1; btl+0x190 = battle; SetBtlBGMNumber(bgm);
 *      SetPC from MENU party; SetMonsterSet(RegDat(0x35, monset))                    (this call replaces CDMYStage by BtlSocket in SSHSys)
 *   2: run; timer++; key (0x2008) after 60 frames -> not_skipped = 0 and timer = 0xa8c; battle cb 2 (+0x2d) before 0xa8c -> fade banner + state 3;
 *      timer >= 0xa8c (2700 frames = 45 s) -> fade banner + state 3
 *   3: BattleEnd handling (FUN_00368b60); when cb 0 seen (+0x2c): release banners, state 4, opening(not_skipped), self delete
 *   4: done flag (+0x30) */
