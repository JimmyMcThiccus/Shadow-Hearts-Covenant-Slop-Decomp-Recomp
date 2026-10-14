import re, os
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
def struct_table(name):
    t = open(os.path.join(ROOT, 'decomp/H/types.h')).read()
    m = re.search(r'typedef struct %s \{\s*/\* size (0x[0-9a-f]+) \*/(.*?)\} %s;' % (name, name), t, re.S)
    if not m: return ''
    rows = ['| off | type | field |', '|---|---|---|']
    for l in m.group(2).splitlines():
        r = re.match(r'\s*(.+?) (\w+)(\[[^\]]+\])?;\s*/\*\+(0x[0-9a-f]+)\*/', l)
        if r:
            rows.append('| %s | `%s` | `%s%s` |' % (r.group(4), r.group(1), r.group(2), r.group(3) or ''))
        else:
            r = re.match(r'\s*byte pad_(\w+)\[(0x[0-9a-f]+)\];', l)
            if r: rows.append('| 0x%s | _unknown_ | pad (%s bytes) |' % (r.group(1), r.group(2)))
    return 'Struct `%s`, total size %s (Ghidra struct applied to `this`; field names are provisional, derived from use):\n\n' % (name, m.group(1)) + '\n'.join(rows)
SINGLE = '(Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. '
PROSE = {}
PROSE['CBattle'] = """The battle director. A singleton (`Sys__7CBattle`), allocated by `BtlSocket::Polling` state 1 (`new 0x4660`), a `CPolObj` descendant.
`Polling` (0x004314a0, 105 KB) is a switch over `phase = *(u16*)(this+0x28)`, `step = *(u16*)(this+0x2a)`; see `battle_flow.md` section 2 for the phase table
and `battle_rules.md` for every formula (GetMaxHP/GetStr/.../GetPAtkDamage/GetSAtkDamage/GetTurnInterval/TurnEnd/GetEscapeRate/BtlEndCheck/AddTrophy).
Rust: `sh2_battle::{rules, structs, flow}`.

Method groups (167 total): lifecycle (`__ct`, `Start`, `End`, `Destruct`, `Polling`), menu protocol (`BtlMenuCallBack`, `BtlMenuCBFunc`, `BtlMenuFunc`),
turn system (`InitTurnTiming`, `GetTurnInterval`, `GetNextTurnChr`, `TurnEnd`, `MakeTurnOrderTable`, `TurnInitSubFunc`, `TurnBeforeFunc`), stats (`GetMaxHP/MP/SP`, `GetStr/Vit/Int/Pow/Agl/Luc`, `GetPAtk/SAtk/PDef/SDef`, `Get*Rate`),
actions (`AttackFunc`, `PAtkHitSet`, `EffectFunc`, `EffectDamageSet`, `CheckCycleHit`, `CheckComboSkill`, `MaxComboFunc`), AI (`AITurnFunc`, AIS VM), status (`SetStatus`, `ResetStatus`, `Aroma*`, `Berserk*`),
rewards (`AddTrophy`, `MakeResultTrophy`), end (`BtlEndCheck`, `DeathInit`, `DeadReset`), camera hooks (`Set*Camera1`), pad/ring (`SetJRingStatus`, `GetJRingAreaResult`).

""" + struct_table('CBattle') + """

Character array: 12 `BtlChr` at `this+0xb0+idx*0x4f0` (idx 0-3 PC front row, 4-7 PC reserve, 8-11 enemies - see `structs::chr`). Decompiler offsets = element offset + 0xb0.
Turn table `aTurnTbl` (+0x3e14, 64 x s16) is the predicted order shown by `TurnOrderDisp`.

### `BtlChr` (0x4f0 bytes, `CBattle+0xb0+i*0x4f0`)

""" + struct_table('BtlChr') + """

Status list: 32 x `StatRec` (12 bytes) at element +0x108: `{s16 turns; s16 chance; s16 percent; u16 kind; i32 value}` - exact decoding in `structs::parse_status_record`.
`kind` values 0x0c..0x47 (max HP ... status bitfield) are the 'modifier kinds' in `rules::modkind`.
"""
PROSE['BtlMenu'] = """Command UI. Mostly static (`uGpffff86ec/86e8` hold the callback + user pointer; `iGpffff86f0` is the linked list of live `BMesWin` windows).
Menu builders: `SetMainMenu` (0x005adc70, 54 KB), `SetTargetMenu`, `SetMagicMenu`, `SetItemMenu`, `SetSkill1Menu`, `SetComboSkillMenu`, `SetBaseAromaMenu/SetAddAromaMenu`,
`SetComboShortCutMenu`, `SetFusionMenu`, `SetGuardMenu`, `SetMoveMenu`, `SetTutorialMenu`. Each constructs `BMesWin` windows + one `BCursole` and reports through the callback
(codes 0-23, table in `battle_flow.md` section 3, reproduced in Rust as `flow::MenuEvent`). `MakeMesWin(x,y,text,w)` picks the first free window id by walking the list and `new BMesWin(0x138)`.
Menu item labels (27) are `flow::MenuItem`.
"""
PROSE['BMesWin'] = "Message/menu window object (0x138 bytes). Linked list node: `+0x28` next, `+0x2c` id. Created by `BtlMenu::MakeMesWin`; draws the frame via `BtlWin`, text via the main-exe text printer.\n"
PROSE['BCursole'] = "Menu cursor sprite (spelling 'Cursole' is original). Owned by `BtlMenu`; follows the selected row of a `BMesWin`.\n"
PROSE['BtlWin'] = "Window-frame drawing helper used by `BMesWin`, `ParamDisp` and `TurnOrderDisp`.\n"
PROSE['BtlModel'] = """Battle model wrapper: skeleton/motion set, weapon models, bounding boxes (`BtlModel::EventCallBack/MotionEndCallBack` forward motion events to `CBattle::MotionEventCallBack`
(0x004a2bf0, 22 KB: damage frames, SE, effects) and `MotionEndCallBack`). 45 methods incl. alpha (`SetBtlModelAlpha`), attach points, weapon show/hide, colour tint. Uses `sh2_formats::{model,motion}` in the port.
"""
PROSE['BtlCamera'] = "Camera director. `CBattle` calls one of ~25 situation setters (`SetMoveCamera1`, `SetFusionCamera1`, `SetWinCamera1`, `SetLoseCamera1`, command/target cameras, per-character camera by `BtlChr+0x57a`).\nEach interpolates position/look-at over time in `Polling`.\n"
PROSE['BtlBG'] = "Battle background manager (`SetBtlBG(id)` from `BtlSocket`, `BtlBGSequence` per frame). Loads the BG model/texture set from BTLDATA.PKB.\n"
PROSE['ParamDisp'] = "Party status panel (HP/MP/SP bars and numbers for the 4 front PCs). `MakePacket` (10.7 KB) draws the numbers and gauges; reads `BtlChr.nHp/nMp/nSp` and max values.\n"
PROSE['TurnOrderDisp'] = "Turn-order timeline strip. Reads `CBattle.aTurnTbl` (64 x s16), produced by `MakeTurnOrderTable`; mirrored by `rules::predict_turn_order`.\n"
PROSE['ComboForm'] = "Combo formation indicator: shows which PCs are linked into a combo and the combo ring/area while selecting; mask is `CBattle.wComboMask` (+0x45f0).\n"
for c, t in {
 'TotalHitInfo': 'Accumulated total-damage readout for a multi-hit action.', 'HitInfo': 'Per-hit damage number popup.', 'TargetInfo': 'Target name/HP popup.',
 'HitMark': 'Hit spark marks.', 'HitImpact': 'Impact flash.', 'HitCntEff': 'Combo hit counter display.', 'CmbBreak': 'Combo-break effect (death break).',
 'BreakBBox': 'Bounding-box shatter effect on death.', 'NormalDeathEfct': 'Standard enemy death dissolve.', 'AbnIcon': 'Status-ailment icons above characters.',
 'MgcInvkParticle': 'Magic invocation particles.', 'CBtlPAfter': 'Post-attack afterimage effect.', 'CBtlPAfter2': 'Post-attack afterimage effect, variant 2.',
 'BtlBlear': 'Screen blur/blear effect.', 'BtlScrnCapture': 'Screen capture to texture (judgement ring backdrop / transitions).',
 'CircleArea': 'Circular target area marker.', 'StraightArea': 'Line target area marker.', 'StraightCircleArea': 'Line+circle target area marker.',
 'EffMdl': 'Effect model object (model-based effects driven from the effect VM).', 'BtlEff': 'Effect base class.', 'BMCLUT': 'CLUT (palette) helper for battle menu textures.',
 'DownSmoke': 'Smoke when a character is knocked down.', 'DownHitSmokeCall': 'Knock-down hit smoke spawner.', 'FrictionSmokeCall': 'Foot-friction smoke spawner.',
 'Bullet1': 'Projectile type 1.', 'Bullet2': 'Projectile type 2.', 'Bullet3': 'Projectile type 3 (spawns Bullet3Child).', 'Bullet3Child': 'Child particle of Bullet3.', 'Bullet4': 'Projectile type 4.',
 'BtlFree': 'Free functions in BATTLE.BIN (btlsub.cpp / btlapi.cpp): effect helpers (`EffectDamageSet`, `CharactorShow`, `WeaponShow`, `ComboStopOff`, `GetFusionCharactor`, `CharacterTargetMove`, `BeginMagicEffectClear`...).',
}.items():
    PROSE[c] = t + ' ' + ('' if c == 'BtlFree' else SINGLE) + '\n'
for c in ['SwordLocusEffect1', 'SwordLocusEffect2', 'SwordLocusEffect3', 'FanLocusEffect1', 'WhipLocusEffect', 'BlowLocusEffect1']:
    PROSE[c] = 'Weapon swing trail ("locus") effect for ' + c.replace('LocusEffect', '').replace('1', '').replace('2','').replace('3','') + ' weapons. ' + SINGLE + '\n'
for c in ['SwordAddAttribute1', 'BBoxAddAttribute1', 'WpnBBoxAddAttribute1', 'FanAddAttribute1', 'WpnBoxAddAttribute1', 'BoxAddAttribute1', 'ScytheAddAttribute1', 'RaidenAddAttribute1']:
    PROSE[c] = 'Elemental weapon glow/attribute overlay for a weapon type (' + c + '). ' + SINGLE + '\n'
