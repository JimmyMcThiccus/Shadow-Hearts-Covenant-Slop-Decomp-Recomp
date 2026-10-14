# Field maps for section-F classes: {class: (base_class, {offset: (type, name)})}
# Offsets are byte offsets from the start of the object as seen through `this`.
F = {}
def cls(name, base, d): F[name] = (base, d)

cls("DelayDeleteObject", None, {0x0: ("void *", "link_prev"), 0x4: ("void *", "link_next"), 0x8: ("void **", "vptr")})
# ---------------------------------------------------------------- MenuObj hierarchy
cls("MenuObj", "DelayDeleteObject", {
    0xc: ("MenuObj *", "next"),           # MenuObjTable chain (priority ordered)
    0x10: ("u8", "dirty0"), 0x11: ("u8", "dirty1"),  # per VIF buffer: 1 hdr, 2 env, 8 rect, 0x10 rgba, 0x20 uv ...
    0x12: ("u8", "flags"),                # bit0 render, bit1 poll, bit2 in-table, bit3 delay-delete, bit4 created
    0x14: ("s16", "priority"), 0x16: ("s16", "id"),
})
cls("MenuPlace", "MenuObj", {
    0x18: ("MenuWindow *", "owner"), 0x1c: ("s16", "col"), 0x1e: ("s16", "row"),
    0x20: ("u8", "state"), 0x21: ("u8", "pflags"),   # bit1 selectable, bit2 selected, bit4 key place, bit5 alpha-relative
    0x22: ("u16", "label"),
    0x24: ("f32", "x"), 0x28: ("f32", "y"), 0x2c: ("f32", "w"), 0x30: ("f32", "h"),
    0x34: ("MenuObj *", "attached"), 0x38: ("MenuPlace *", "next_place"),
})
cls("MenuPacket", None, {0x0: ("void **", "vptr"), 0x4: ("void *", "pkt0"), 0x8: ("void *", "pkt1"), 0xc: ("u16", "qwc"), 0xe: ("u8", "pflags")})
cls("MenuItem", "MenuPlace", {
    0x3c: ("MenuPacket", "packet"), 0x40: ("void *", "pkt0"), 0x44: ("void *", "pkt1"), 0x48: ("u16", "qwc"), 0x4a: ("u8", "pktflags"),
    0x4c: ("u8", "r"), 0x4d: ("u8", "g"), 0x4e: ("u8", "b"), 0x4f: ("u8", "a"),
    0x50: ("s16", "blink_phase"), 0x52: ("u8", "blink_period"), 0x53: ("u8", "blink_base"),
})
cls("MenuSprite", "MenuItem", {0x54: ("u16", "u0"), 0x56: ("u16", "v0"), 0x58: ("u16", "u1"), 0x5a: ("u16", "v1"), 0x5c: ("MenuObj *", "linked")})
cls("MenuPolygon", "MenuItem", {
    0x54: ("f32", "vx0"), 0x58: ("f32", "vy0"), 0x5c: ("f32", "vx1"), 0x60: ("f32", "vy1"), 0x64: ("f32", "vx2"), 0x68: ("f32", "vy2"),
    0x6c: ("f32", "vx3"), 0x70: ("f32", "vy3"), 0x74: ("u8", "col1[4]"), 0x78: ("u8", "col2[4]"), 0x7c: ("u8", "col3[4]"), 0x80: ("u16 *", "uv"),
})
cls("FontItem", "MenuItem", {
    0x54: ("void *", "font_draw"), 0x58: ("u8", "fflags"), 0x59: ("u8", "line_gap"), 0x5a: ("u8", "shadow_x"), 0x5b: ("u8", "shadow_y"),
    0x5c: ("s8", "spacing"), 0x5d: ("u8", "csa"), 0x5e: ("u8", "fflags2"), 0x5f: ("u8", "fflags3"), 0x60: ("void *", "string"),
    0x64: ("u8", "color2_r"), 0x65: ("u8", "color2_g"), 0x66: ("u8", "color2_b"),
})
cls("MenuText", "FontItem", {0x74: ("s16", "rx0"), 0x76: ("s16", "ry0"), 0x78: ("s16", "rx1"), 0x7a: ("s16", "ry1"), 0x7c: ("s16", "nchars")})
cls("PluralFontItem", "FontItem", {})
cls("MenuMessage", "PluralFontItem", {
    0x20: ("u8", "state"),     # 9 = typing, 10 = waiting on macro/wait, 1 = finished
    0x68: ("MenuObjTable", "icons"),
    0x74: ("u16", "stride"), 0x76: ("u16", "n_chars"), 0x78: ("u16", "n_visible"), 0x7a: ("u16", "cur_char"), 0x7c: ("u16", "n_rects"),
    0x7e: ("u16", "n_lines"), 0x80: ("u16", "fade_from"), 0x82: ("u16", "cursor_x"), 0x84: ("u16", "cursor_y"), 0x86: ("u16", "line_no"),
    0x88: ("u16", "n_macro"), 0x8a: ("u16", "cur_macro"), 0x8c: ("s16", "char_interval"), 0x8e: ("s16", "char_timer"), 0x90: ("u32", "fade_rate"),
    0x94: ("SendOnLocal *", "kbd_icon"),
})
cls("MenuGroup", "MenuPlace", {0x3c: ("f32", "min_x"), 0x40: ("f32", "min_y"), 0x44: ("u16", "alpha"), 0x48: ("MenuPlace *", "key_place"), 0x4c: ("MenuPlace *", "children")})
cls("MenuObjTable", None, {0x0: ("void **", "vptr"), 0x4: ("MenuObj *", "head")})
cls("Scissor", None, {})
cls("MenuWindow", "MenuObj", {
    0x18: ("MenuObjTable", "objs"), 0x24: ("MenuPacket", "packet"),
    0x34: ("WindowRec *", "rec"), 0x38: ("MenuPlace *", "places"), 0x3c: ("MenuWindowObject *", "frame"),
    0x40: ("ScrollData *", "scroll"), 0x44: ("ScrollMark *", "mark"), 0x48: ("MenuObj *", "extra"), 0x4c: ("Scissor", "scissor"),
    0x58: ("u16", "pktqw"), 0x5c: ("s16", "clip_x"), 0x5e: ("s16", "clip_y"), 0x60: ("s16", "clip_w"), 0x62: ("s16", "clip_h"),
    0x64: ("f32", "x"), 0x68: ("f32", "y"), 0x6c: ("f32", "w"), 0x70: ("f32", "h"),
    0x84: ("s16", "clip0_x"), 0x86: ("s16", "clip0_y"), 0x88: ("s16", "clip0_w"), 0x8a: ("s16", "clip0_h"),
    0x8c: ("f32", "scroll_x"), 0x90: ("f32", "scroll_y"),
    0x94: ("s32", "anim_time"), 0x98: ("f32", "anim_a"), 0x9c: ("f32", "anim_b"), 0xa0: ("f32", "anim_da"), 0xa4: ("f32", "anim_db"),
    0xa8: ("u8", "state"),     # 0 closed, 1 open, 5 move, 6 zoom, 7 fade, 8 ?
    0xa9: ("u8", "mark_mask"), 0xaa: ("u8", "env_dirty"), 0xab: ("u8", "env_dirty2"), 0xac: ("u16", "alpha"),
    0xb0: ("u16", "wflags0"), 0xb1: ("u8", "wflags1"), 0xb2: ("u16", "wflags2"),
})
cls("ScrollData", None, {
    0x0: ("void *", "link_prev"), 0x4: ("void *", "link_next"), 0x8: ("void **", "vptr"), 0xc: ("s32", "cell_count"),
    0x10: ("void *", "pkt0"), 0x14: ("void *", "pkt1"), 0x18: ("s16", "cols"), 0x1a: ("s16", "rows"), 0x1c: ("f32", "cell_w"), 0x20: ("f32", "cell_h"),
    0x24: ("f32", "target_x"), 0x28: ("f32", "target_y"), 0x2c: ("f32", "max_step_x"), 0x30: ("f32", "max_step_y"), 0x34: ("u16", "mode_bits"),
    0x36: ("s16", "scrolling"), 0x38: ("FontDraw *", "font_draw"),
})
cls("Cursor", "MenuObj", {
    0x18: ("MenuSound *", "sound"), 0x1c: ("MenuPolygon", "poly"), 0xa0: ("SendOnLocal", "send"),
    0xd0: ("MenuPolygon *", "shadow"), 0xd4: ("MenuFlare *", "flare"), 0xd8: ("u8 *", "pos"),   # pos[0..1]=x,y  pos[2..3]=image w,h
    0xdc: ("f32", "off_x"), 0xe0: ("f32", "off_y"), 0xe4: ("f32", "target_x"), 0xe8: ("f32", "target_y"),
    0xec: ("MenuPlace *", "place"), 0xf0: ("MenuSprite *", "back"), 0xf4: ("f32", "angle"), 0xf8: ("u8", "move_state"),
    0xf9: ("s8", "gap"), 0xfa: ("u16", "cflags"), 0xfb: ("u8", "cflags2"),
})
cls("MenuScene", "DelayDeleteObject", {
    0xc: ("BufMemory *", "heap"), 0x10: ("Menu *", "menu"), 0x18: ("Cursor *", "cursor"), 0x1c: ("s16", "scene_id"),
    0x20: ("u8", "ready"), 0x22: ("u8", "s22"), 0x23: ("u8", "sflags"),
    0x24: ("Chunk *", "tab_resource"), 0x28: ("Chunk *", "tab_text"), 0x2c: ("Chunk *", "tab_fontdraw"), 0x30: ("Chunk *", "tab_cursor"),
    0x34: ("Chunk *", "tab_window"), 0x38: ("Chunk *", "tab_group"), 0x3c: ("Chunk *", "tab_sprite"), 0x40: ("Chunk *", "tab_polygon"),
    0x44: ("Chunk *", "tab_text2"), 0x48: ("Chunk *", "tab_message"), 0x4c: ("Chunk *", "tab_font"), 0x50: ("Chunk *", "tab_italic"),
    0x54: ("Chunk *", "tab_attach"),
})
cls("GameOverScene", "MenuScene", {0x58: ("ptmf", "state_fn"), 0x64: ("GameOverRealize *", "realize"), 0x68: ("GameOverSelect *", "select"), 0x6c: ("dataAccess *", "data_access")})
cls("Menu", "CPolObj", {
    0x20: ("void **", "vptr_dd"), 0x28: ("MenuDataTable", "table"), 0x34: ("MenuScene *", "active"), 0x38: ("MenuScene *", "scenes"),
    0x3c: ("u8", "m3c"), 0x3e: ("u16", "m3e"), 0x48: ("u16", "keys"),
})
cls("CPolObj", "DelayDeleteObject", {})   # CPolObj is section A; 0x14 = vptr in derived
cls("MenuDataTable", None, {0x0: ("u8 *", "data"), 0x4: ("BufMemory *", "heap"), 0x8: ("u8", "loading"), 0x9: ("u8", "release_pending")})
# ---------------------------------------------------------------- save system
cls("SaveDataSection", None, {0x0: ("void **", "vptr"), 0x4: ("SaveDataSection *", "next"), 0x8: ("SectionHdr *", "hdr")})
cls("SaveData", "CPolObj", {
    0x14: ("void **", "vptr"), 0x18: ("SaveDataSection *", "sections"), 0x1c: ("SaveHdr *", "heap"), 0x20: ("SaveDevice *", "device"),
    0x24: ("s32", "state"), 0x28: ("u8", "last_op"), 0x29: ("u8", "pending_op"), 0x2a: ("u8", "op2a"), 0x2b: ("u8", "slot"),
})
cls("SaveDevice", None, {
    0x0: ("void **", "vptr"), 0x4: ("u8", "port"), 0x5: ("u8", "dflags"), 0x6: ("u8", "op"), 0x7: ("u8", "step"),
    0x8: ("s16", "io_phase"), 0xa: ("s16", "io_step"), 0xc: ("s32", "format_flag"), 0x10: ("s32", "free_kb"),
    0x14: ("s32", "mc_result"), 0x18: ("s32", "mc_cmd"), 0x1c: ("SystemFile", "sysfile"), 0x20: ("BufMemory *", "icon_buf"),
    0x24: ("u8 *", "icon_data"), 0x28: ("u8[0x3c4]", "icon_sys"), 0x3ec: ("u8 *", "io_ptr"), 0x3f0: ("s32", "io_len"),
    0x3f4: ("s32", "mc_type"), 0x3f8: ("s32", "mc_fd"),
})
cls("SystemFile", None, {0x0: ("SystemFileHdr *", "buf")})
cls("BtlSaveSec", "SaveDataSection", {})
cls("SaveMenuSection", "SaveDataSection", {0xc: ("u8 *", "data"), 0x10: ("MenuDataTable", "places")})
cls("CFieldSaveData", "SaveDataSection", {0xc: ("u16", "capacity_units"), 0xe: ("u16", "used_units")})
cls("dispTime", "CPolObj", {0x18: ("primWin *", "win"), 0x1c: ("primTex *", "tex0"), 0x20: ("primTex *", "tex1"), 0x28: ("f32", "x"), 0x2c: ("f32", "y"), 0x30: ("s32", "ms"), 0x34: ("u8", "running"), 0x35: ("u8", "autostart"), 0x36: ("u8[10]", "digits")})
cls("dispCash", "CPolObj", {0x0: ("primWin *", "win"), 0x18: ("s32", "cash"), 0x1c: ("u8[10]", "digits")})
cls("dataAccess", "CPolObj", {
    0x24: ("fn", "callback"), 0x28: ("void *", "cb_arg"), 0x2c: ("primCursor *", "cursor"), 0x30: ("udScrollMark *", "scrollmark"),
    0x34: ("primSound *", "snd"), 0x38: ("primWin *", "fader"), 0x40: ("primWin *", "bg"), 0x4c: ("primWin *", "popup"),
    0x80: ("s32", "device_sel"), 0x88: ("primWin *", "win"), 0x90: ("primCursor *", "main_cursor"),
    0xa8: ("s32", "mode"),                # ACCESSMODE: 0 save, 1 load, 2 initial device check, 4 quit/none
    0xac: ("u8[15]", "slot_empty"), 0x110: ("s32[3]", "disp_visible"), 0x11c: ("dispSaveFile *[3]", "disp"),
    0x130: ("SaveDataInfo *", "info"), 0x134: ("s32", "cur_slot"), 0x138: ("s32", "slot_count"), 0x13c: ("s32", "scroll_timer"),
    0x150: ("s32", "mode2"), 0x160: ("s32", "state"), 0x164: ("s32", "next_state"), 0x168: ("s32", "progress"), 0x16c: ("s32", "dev_kind"),
    0x178: ("s32", "retry"), 0x17c: ("s32", "reset_lock"), 0x180: ("s32", "result"),
})
cls("openingMessage", "CPolObj", {
    0x28: ("GsxCamera *", "cam"), 0x54: ("s32", "disp_w"), 0x58: ("s32", "disp_h"), 0x5c: ("primSound *", "snd"), 0x60: ("primMusic *", "bgm"),
    0x64: ("primWin *", "fader"), 0x6c: ("primWin *", "title"), 0x70: ("primWin *", "menu"), 0x74: ("primCursor *", "cursor"), 0x78: ("s32", "sel"),
    0x80: ("prim2D *[6]", "title_sprite"), 0xbc: ("s32", "n_title_sprite"), 0xc4: ("s32", "pulse"), 0xd0: ("void *", "d0"),
    0xd4: ("openingBattleDemo *", "demo"), 0xd8: ("dataAccess *", "data_access"), 0xdc: ("install *", "install"),
    0xe0: ("s32", "state"), 0xe4: ("s32", "next_state"), 0xe8: ("s32", "e8"), 0xec: ("s32", "timer"), 0xf0: ("s32", "cb_event"),
})
cls("openingBattleDemo", "CPolObj", {
    0x1c: ("s32", "state"), 0x20: ("u8", "btl_done"), 0x21: ("u8", "not_skipped"), 0x22: ("u8", "go"), 0x23: ("u8", "finished"),
    0x24: ("s32", "timer"), 0x28: ("s32", "battle_no"), 0x2c: ("s32", "bgm"), 0x30: ("s32", "monset"),
    0x34: ("prim2D *", "banner"), 0x38: ("prim2D *", "p38"), 0x3c: ("prim2D *", "p3c"), 0x40: ("s32", "tex"), 0x44: ("s32", "layer"),
})
cls("GameOver", "Menu", {0x50: ("GsxCamera *", "cam")})

def resolve(cname):
    """flattened {offset: (type,name)} for a class including bases"""
    out = {}
    chain = []
    c = cname
    while c and c in F:
        chain.append(c)
        c = F[c][0]
    for c in reversed(chain):
        out.update(F[c][1])
    return out
