# tailor (JP 0x004eafe0 … 0x004f20a0, 27 methods; + dRoll (a scrolling roll; role inferred), bookScrollMark)

The costume shop ("Tailor"): select a character, browse costumes on a 3D sketch book (`primModel` + `mSetPage`, `mMakeSketchBook`, `mReadModel(i)`),
pay/confirm (YesNo windows), apply (`mSetCloth` -> party costume flags in the save), plus a magic-star effect (`mSetupMagic`, `mMoveStars` with `mStarPos`) and the cloth-change cinematic (`dRoll::start/stop`, scrolling name roll).
Launched by `CField::cbTailor` (JP 0x004b0b40). Tables: `tailorMess_*_J` (cloth note/ruby/messages). Polling: `tailor::Polling` -> `mTailorPolling(buttons)` (state 0..0x1a: 2 setup, 4 page turn + `CmdElement::ReCreate`, 0xa/0xb confirm, 0xd..0x11 apply and cutscene, 0x12/0x13 magic, 0x15..0x17 second confirm, 0x1a close) and `mMenuPolling`.
