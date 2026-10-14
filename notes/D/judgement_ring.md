# Judgement Ring (`JRing`) — battle input mechanic

Source: `JRing.cpp`, JP demo `SLPM_602.19`, contiguous at `0x002bf6f0 .. 0x002e0fa0` (+ `HitMes/HitBar/HitArea`
at `0x002e4040..0x002e80a0`, `CrackJRing` `0x002e80a0..0x002f6e90`, `CutJRing` `0x002f6e90..0x002fb470`,
loader/statics `0x002fb470..0x002fc0c0`).  Rust port: `port/crates/sh2_gfx/src/effects/jring.rs`
(logic only, 9 unit tests, `cargo test` clean).  Decompiled sources: `decomp/D/JRing.c`.

## 1. What it is

`JRing` is a `CPolObj` (polled by `CPoller(0x48)`, prio 0x80) *and* a `VIF1Prim` (drawn in World ordering table
`ot_layer`) *and* a `DelayDeleteObject` (three bases: vptr at +0x14, VIF1Prim at +0x18 (its getPacket thunk
`@24@getPacket`), DelayDeleteObject vptr at +0x34 (thunk `@44@__dt__`)).  All live rings are chained in a global
doubly linked list (`JRTop/JREnd`, links at +0x38/+0x3c; `Entry/Release`).  Class statics:

| symbol | meaning |
|---|---|
| `JRTop/JREnd__5JRing` (0x40ac8c/90) | list of live rings |
| `Pad__5JRing` (0x40ac94) | `CPad::GetActive(0)`; button word read at `m_pCoreArray[pad->+4]+0x6c` |
| `JRData__5JRing` | `BufMemory*` of `COMMON/JRING.BIN` (texture container, 4..8 images, loaded through `DvdromOrder::ReadOrder`; `ReadCallBack` creates one `JRCTex` per image: PSM 0x1b (PSMT8) if `entry.flags&7==1` else 0x2c (PSMT4HH)) |
| `System__5JRing` | bits0-1: 0 idle / 1 loading / 2 loaded; bit2 textures built |
| `JRTexInfo` + `JRTex[8]` | texture count / per-texture w,h / `JRCTex*` |

Lifecycle: `new JRing(id, otLayer)` → ctor sets defaults, `Initialize` (clears areas, builds the view-screen matrix at
+0x590 for a 512x448 camera) → state 0 (`AutoLoad`).  `SystemInitialize()` is called once from `SSHSys::Initialize`
(also `new HNMSnd`).  `Destruct(bool)` deletes cut/crack/combo objects, hit sprites and unlinks from the OT/poller.

## 2. Public API as used by battle code (JP names)

| function | effect |
|---|---|
| `SetMode(intro, type, endMiss, endOk, endStrike)` | +0x4a..+0x52 (see §5/§6) |
| `SetEventRing(t, flag, arg)` | event-ring presets: t=0 → type 2, laps 1; t=1 → type 3, laps=arg; t=2 → type 5, laps 0; t=3 → type 4, laps 1, end anims (1,3,3); all with intro 5. `flag` = +0x42 bit6 (event ring: closing animation handled by caller) |
| `SetEventRingAbnormal(n)` | n=0 small ring (`abn_d`&1), 1 hidden (`abn_d`&2), 2 smooth speed wobble (`abn_d`&0x20, amp 1.4), 3 accelerating (`abn_c`&0x40), 4 reversed (`abn_d`&8), 5 jerky speed wobble (`abn_d`&0x40, amp 1.2) |
| `AddStepArea(start,width,col,tag)` / `AddStrikeArea(start,width,strike,c0,c1)` / `AddModulateArea(start,width,minPct,strike,c0,c1,c2)` / `AddEventRingArea(start,width,colourId 1..4)` | fill the first free slot (kind byte == 0xff) of `areas[12]`, bump `area_count`; widths must be >0 (strike: `strike<=width`) |
| `AllAreaInitialize` | wipe both tables, count=0, forget custom data |
| `SetCombo(f)` | f==-1 disable combo trial, else enable with window `f` seconds (+0xe0) |
| `SetRingPos(x,y)` | +0x68/+0x6c (default 256,224) |
| `SetRotSpeed(period,lapAdd,lapMul)` | +0xb4 default period (1.6 s/rev), +0xc0, +0xc4 — note `RingActive` resets +0xc0=0,+0xc4=1 and copies +0xb4→+0xbc, so lap params only survive when set after `RingActive` |
| `SetCallBack(fn,user,mask)` | +0xf8/+0xf4/+0xf0, see §7 |
| `RingActive()` | start a run (state 3) |
| `RingClose(k)` | k=2 → state 8, k=1 → state 7, else 6 (force close) |
| `RingSleep()` / `RingSleepCheck()` | hide, state 2 / `state==2` |
| `AutoLoadSet()` / `AutoLoadEndCheck()` | trigger/poll the asynchronous load of `JRING.BIN` |
| `SetAreaBlink(i,mode,mode2)` | i==-1 all, 0..11, 12 = gamble area; mode (0..3) blink pulse, mode2 selects colour pair |
| `Destruct(b)` | delete |

`ComboTrial(ring, kind, mode)` objects are the "press the shown button!" prompts (§8); `HitMes/HitBar/HitArea` are the
transient feedback sprites.  `Hit*Entry/Release/AllHit*Delete` maintain per-ring lists of them (+0x558.., +0x560.., +0x568..).

## 3. Object layout (`JRing`, Ghidra struct `JRing`, 0x5d0 bytes; JRAREA = 0x24)

| off | type | name | notes |
|---|---|---|---|
| 0x14/0x34 | ptr | vtbl / DelayDelete vtbl | `__vt__5JRing` 0x4066c0 (size 0x34) |
| 0x38/0x3c | ptr | prev/next | global ring list |
| 0x40 | u8 | flagsA | b7 ring on (drawn), b1-2 area packet dirty, b3-4 bar dirty, b5-6 ring dirty (packets rebuilt lazily by `MakePacket`) |
| 0x41 | u8 | flagsB | b0 ring visible, b1 pointer visible, **b2-3 ring kind** (0 normal, 1 "limited-lap" ring, 2 "x1.2 strike/modulate" ring, 3 gamble ring), b4 CrackJRing exists, b5 CutJRing exists, b6 registered in OT, b7 *armed* (a press is currently accepted) |
| 0x42 | u8 | flagsC | b0 first-press bonus still available ("lap_ok": no strike-tail penalty), b1 combo trial enabled, b2 custom areas valid, b3 destruct, b4 **pause** (dt=0), b5 combo failed, b6 event ring, b7 no-end-wait |
| 0x43 | u8 | flagsD | b0 lap lock (pointer returned to the same area index; hit disabled until next lap) |
| 0x44 | s16 | id | ctor arg |
| 0x46 | s16 | state | §4 |
| 0x48 | s16 | substate | |
| 0x4a..0x52 | s16 | intro, ring_type, end_miss, end_ok, end_strike | |
| 0x54 | f32 | wait | delay before the state machine continues |
| 0x58 | u32 | last timer (ms) | `SysTool::GetTimer` |
| 0x5c | f32 | dt | seconds since last poll |
| 0x60 | i32 | cur_area | index into the area table of the area that is "armed" |
| 0x64 | i32 | inside_at_start | pointer was already inside the area when it became current |
| 0x68/0x6c | f32 | ring centre | 256,224 |
| 0x70 | f32[4] | ring rotation (x,y,z, w=1) | intro/combo flip animations |
| 0x80/0x84 | f32 | scale_x / scale_y | |
| 0x88 | i32 | flip state | combo flip: 0 front, 1 seen back, 2 returned |
| 0x8c/0x90/0x94 | f32 | animation timers a/b/c | (a) is also the "overshoot degrees" accumulator while running |
| 0xa0 | f32[4] | home rotation | (-0.5236, 0.9603, 0, 1) = tilted ring |
| 0xb0/0xb4/0xb8 | f32 | home scale_y 0.85 / default period 1.6 s / home scale_x 1.0 | |
| 0xbc | f32 | **period** | seconds per revolution; sign = direction; clamped to [0.5333, 4.8] each frame |
| 0xc0/0xc4 | f32 | lap_add / lap_mul | applied to |period| each lap (`period=(period±lap_add)*lap_mul`) |
| 0xc8 | f32 | accel | `period += accel*dt*60` (sign follows direction) |
| 0xcc..0xd8 | f32 | wobble amp / target / step / current | speed wobble abnormalities |
| 0xe0 | f32 | combo window (s), default 0.2 | |
| 0xe4 | f32 | combo spin period | |
| 0xf0/0xf4/0xf8 | u16/ptr/fn | callback mask / user / function | |
| 0xfc | i32 | area_count | |
| 0x100 | JRAREA[12] | `areas` | as registered |
| 0x2b0 | JRAREA[12] | `custom` | after `CustomConvert` |
| 0x460 | JRAREA | `gamble` | kind-3 ring |
| 0x484 | JRAREA | `fake` | decoy area (abnormal `abn_d`&0x10) |
| 0x4ac/0x4b0 | f32 | cur_angle / prev_angle | degrees, wrapped to [-180,180]; positive = clockwise from 12 o'clock |
| 0x4b4 | f32[9] | angle history | filled with cur_angle |
| 0x4dc | i32 | result_total | hits the ring demands (`ResultInit` return) |
| 0x4e0 | i32 | hits | hits+skipped areas so far |
| 0x4e4 | i32 | laps_allowed | 0 = "single press ring" (see below) |
| 0x4e8 | i32 | laps_done | pointer crossings of angle 0 |
| 0x4ec / 0x4f0 | ptr | CrackJRing* / CutJRing* | closing shard animation (0x5a0 / 0x2f0 bytes) |
| 0x4f4 | ptr | JRCUSTOM* | 20 bytes, see §9 |
| 0x508 | i32 | combo button 0..3 | 0 circle 0x2000, 1 cross 0x4000, 2 triangle 0x1000, 3 square 0x8000 |
| 0x50c/0x50d | u8 | abnormal flags | c: b0 period/2, b1 period*2, b2 zones/2 (shrink), b3 zones x2, b4 zones = whole ring, b5 strike = whole zone, b6 accelerating, b7 period*0.75 decelerating; d: b0 small ring, b1/b2 hidden, b3 reverse, b4 fake area, b5/b6 wobble |
| 0x510 | s16 | has_modulate | |
| 0x512 | u8 | result flags | b1-2 grade (0 fail, 1 partial, 2 clean, 3 clean + strike), b3 combo ok, b4 auto ring, b5 has strike tail, b6 combo prompt shown |
| 0x514/0x516 | s16 | hit_count / total | |
| 0x518/0x51c/0x520/0x524 | i32 | base 10000 / percent / strike mult 12000 / damage mult 10000 | `percent` = score of the last hit (×100), `damage_mult` ×0.9 per miss |
| 0x528 | u8[32] | grades | 2 bits per hit: 1 = score 100, 2 = score <100 (ramp), 3 = strike (>100) |
| 0x548 | s16 | auto_aim | angle the autoplayer wants to press at, -1 = deliberately miss |
| 0x558.. | ptr | HitMes/HitBar/HitArea sprite lists | |
| 0x574/0x578 | ptr | ComboTrial A (the prompt) / B (the verdict) | |
| 0x57c | i32 | OT layer | |
| 0x580/0x584 | i32 | max percent 12000 / base percent 10000 | |
| 0x588 | i32 | event result | tag of the hit area, or lap/hit count; -1 until set |
| 0x58c/0x58e | s16 | auto mode / sub | see §10 |
| 0x590 | f32[16] | view-screen matrix | |

### JRAREA (0x24)
`+0 u16 flags` b0-2 phase (0 outside, 1 inside, 2 passed), b3 visible, b4-5 blink request, b6 blink-down, b7-8 colour mode, **b9-10 hit flash grade**;
`+2 s8 kind` (0 step, 1 strike, 2 modulate, 0xff free); `+3 u8 mod_pct` (modulate: minimum score of the ramp part; ≥100 = flat);
`+4 s16 start`, `+6 s16 width` (≥360 ⇒ whole ring), `+8 s16 strike` (width of the critical tail at the *end* of the zone in the direction of travel),
`+10 s16 sub` (modulate: width of the full-score band = (width-strike)/3, or width-strike when mod_pct>=100),
`+0xc/+0x10/+0x14 rgba` (base / strike / modulate-strike colours), `+0x18 s16 tag`, `+0x1a s16 result` (last score, 0xffff none),
`+0x1c f32` blink phase (0..1.5, init 0.75), `+0x20 f32` hit flash fade (1→0 at 6/s).

Default colours: step (0,0xa4,0x50), strike (0xe0,0x98,0x40)+tail (0xff,0x20,0x18), modulate (white; ramp/100 band 0x20,0xc8,0xfa; tail 0xff,0x20,0x18).

## 4. Main state machine (`Sequence`, 0x002c0cf0, ~28 KB)

```
0 AUTOLOAD --JRING.BIN loaded--> RingSleep -> 2
1 LOAD (sub0: DataLoad, sub1: wait) ------> RingSleep -> 2
2 SLEEP   (idle, hidden)         RingActive() -> 3
3 INTRO   (animation chosen by `intro`; 0.8 s) -> 4  [cb 0x002, SE 0x2001 (0x3000000 for type 5)]
4 RUN     (dispatch on ring_type, §5) -> 5 | 6 | 7 | 8
5 COMBO   combo trial (§8)            -> 7 | 8
6 END_MISS / 7 END_OK / 8 END_STRIKE  closing animation chosen by end_miss/end_ok/end_strike (§6) -> RingSleep -> 2
```
`wait` (+0x54) delays any state: while non-zero it counts down by dt and `Sequence` returns.  When the run ends
(`state` becomes 5..8) `SeEnd(0x2001)` is issued and, for 6..8, `MakeResult()` fires the result callback.

### Intro animations (state 3, `intro`)
1 instant; 2 grow x scale 0→home over 0.8 s (exp. approach `/7*60*dt`); 3 grow y scale; 4 spin-in (rot x/y start at -5.49 / +6.28 rad, decay /7 per frame, scale x grows); 5 same with scale y + SE 0x2002; 6 rotates about z until 0.8 s.
On entering state 4: pointer becomes visible if `abn_d&4==0 && ring_type∉{0,6}`.

### Pointer integration (every running frame)
```
prev = cur;  cur += 360/period * dt;  wrap to [-180,180]
period += accel*dt*60 (sign-aware); wobble handling (abn_d b5: slow random target; b6: random steps every few frames)
lap: positive dir: prev<0 && cur>=0  (negative dir: prev>0 && cur<=0)  => laps_done++, period += ±lap_add, period *= lap_mul, lap_lock=false
|period| clamped to [32/60 = 0.5333, 4.8]
```

## 5. Ring types (`ring_type`, +0x4c) while RUN

* **1 SINGLE** (the normal attack ring; used for weapons, magic, items): the area list is walked *in order of registration*
  (`cur_area` ascending for clockwise, descending for counter-clockwise, wrapping).  Each area waits for one button
  press (any of the 4 face buttons).  Per frame:
  1. `press?` human: `pad&0xf000`; autoplayer: `JRingAuto()`.
  2. If pressed: `score = HitCheck(area[cur])`, `-1` if `lap_lock`.
     * `score<0` (or `laps_allowed==0 && score<101`): miss → SE 0x2007, cb 0x008, `armed=false`, HitMes(variant 1).  Normally the ring ends (state 6, wait 1.0 s) with grade bits `hits==0 ? 0 : 1`.  Exception: kind-1 rings with laps budget only lose 10 % damage (`damage_mult*=0.9`, extra 10 % if the press missed the previous area too) and continue.
     * hit: flash the area (`grade` 1 for <101, 2 for strike tail), spawn `HitArea`, cb 0x004, store grade bits/percent (`record_grade`), `hit_count++`, `hits++`.
       * if that was the last required hit (`hits >= total_hits`): final grade = 1 (some skipped), 2 (all hit) or 3 (all hit and still `lap_ok`, i.e. never used a strike-less hit on a strike area); pointer snaps to `HitStopAngle`; SE 0x2004/0x2005; kind-2 rings additionally demand the last hit to be a clean score (grade 3 for modulate); then state → 5 (COMBO) if `combo_enabled`, else 7 (`lap_ok==false`) or 8 (still `lap_ok`) with `wait=0.5` (0 if `no_end_wait`).
       * else `HitBar` at the stop angle, `HitMes`, advance `cur_area`, `AreaOverCheckInit`, autoplayer re-aims.
  3. Every frame `AreaOverCheck()`: if the pointer left the current area unpressed (phase 2): kind-1 rings with a lap budget auto-skip the area (miss, ×0.9 damage, `hits++`, advance); otherwise accumulate the overshoot `|360/period*dt|` in `anim_a`, and at **7.5°** the whole ring fails (cb 0x010, state 6).
  4. Lap budget: gamble ring ends after 1 lap, others when `laps_allowed!=0 && laps_done>=laps_allowed` (cb 0x020, state 6).
* **2/3/4 LAPS_A/B/C** (`SetEventRing` 0/1/3: "hit every area each lap, N laps"): same hit/area logic but
  every hit flashes grade 3, `hits` counts towards `total_hits = areas × laps`; `ring_type 3` reports `hits/area_count` (laps cleared) and 2/4 report `hits` in `event_value`; ring ends with state 7 when all hits landed, state 6 on a miss/timeout.  Uses the `custom` table (never `areas`).
* **5 EVENT_SPIN** (press-and-spin "slot" ring): substate 1 rotates until a press; then `anim_a=360`, substate 2 decelerates the pointer (`step = min(360/period*dt, anim_a/50 (≥0.2))`) until 0.1° remain; `HitCheck` (type-5 variant: first area containing the pointer, returns the index, score = the area's `tag`) → `event_value=tag` (or 0 on none) → state 7.
* **6 SPIN_ONLY**: just spins `rot.z`.
* **0**: no pointer (ring displayed only).

## 6. Closing animations (states 6/7/8, `end_*`)
(skipped entirely for event rings — the caller closes them)
* 1 shrink: `anim_a += 4*home_scale_x*dt`; `scale_x = home - anim_a`; sleep at end. Start: SE 0x2008, cb 0x100.
* 2 flatten: `scale_y = (1-anim_a)*home_scale_y`, rate 4/s.
* 3 **CrackJRing** (ring splinters into 9..17 shards), 4 **CutJRing** (ring cut in two halves along a random line; variant 1 = combo failed (fast shake), 2 = combo ok (extra SE 0x2000002 after 1/3 s)).  Shard life starts at `home_scale_x` and decays at `1.5*home_scale_x/s` (after 1/3 s for variant 2); ring sleeps when life==0 and no ComboTrial objects remain; cb 0x200 on sleep.

## 7. Callbacks (`fn(code, arg, user)`; delivered if `(mask & bit)`):

| code | mask bit | when | arg |
|---|---|---|---|
| 1 | 0x001 | JRING.BIN ready, ring asleep | – |
| 2 | 0x002 | intro finished (state 4) | – |
| 4 | 0x004 | a hit registered | – |
| 8 | 0x008 | button pressed outside any area | – |
| 0x10 | 0x010 | area passed without press | – |
| 0x20 | 0x020 | lap budget exhausted | – |
| 0x40 | 0x040 | **result** (type 1 rings) | `&ring->+0x510` (JrResult) |
| 0x80 | 0x080 | **result** (types 2..5) | `&ring->+0x588` |
| 0x100 | 0x100 | closing animation started | – |
| 0x200 | 0x200 | slept after closing | – |

`MakeResult` post-processes the result before delivering: kind-2: strike multiplier ×1.2 (`max_percent*12/10`); kind-1 rings drop the "has strike" flag; gamble rings expand the single grade over all areas × laps; `laps_allowed==0` collapses to one grade/total=-1; kind-1 compacts skipped (zero) grade entries.

The battle damage formula consumes `JrResult` (`percent`, `grades`, `damage_mult`, `strike_mult`, `flags`) — see section H notes (`TotalHitInfo`, `ComboForm`).

## 8. ComboTrial and combo (state 5)
After the last hit with `combo_enabled`: `ComboTrial(ring,0,0)` ("press now" banner, A at +0x574) spawns, `wait=0.5`, substate 0 plays SE 0x2000001, `JRingAutoInit(null)` decides whether the autoplayer will succeed.  Substate 1 spins the ring up (`anim_a→1`, `combo_spin = 0.2/anim_a` s/rev) while it flips about the y axis (`rot.y += 2π/combo_spin*dt`); the face the player sees alternates between the ring and the glyph of `combo_button` (`e8 = combo_button+2` selects the sprite).  Substate 2: window of `combo_window` seconds (`anim_b`); pressing the right face button → `result.flags|=8`, ComboTrial(1,3) "OK" (B), SE 0x2004/0x2005, state 7/8; a wrong button → `combo_failed`, ComboTrial(2,2), SE 0x2007 (for kind-1 rings a wrong button is ignored until timeout); timeout → `combo_failed`.  A is told to fade (`phase=2`).

## 9. Ring customisation (`CustomConvert`, `JRCUSTOM`)
The ring-custom menu (`CmdRingCustom*` in FIELD.BIN) stores 4 byte tables of 5 entries per character weapon/ring: `[0..5)` widen, `[5..10)` narrow, `[10..15)` strike widen, `[15..20)` strike narrow (degrees).  `CustomConvert` copies `areas→custom`, computes `delta = widen-narrow`, then for every area grows/shrinks one degree at a time, never closer than 5° to its neighbours (and inside [5°, 355°]); `JRCustomCheck(JRCUSTOM*)` runs the same algorithm on a scratch copy to validate a candidate configuration for the menu.  Quirk reproduced: area indices ≥5 alias into the next table.  Then the abnormal-ring transformations apply (zones ×2 / ÷2 / whole ring / strike=zone) and kind-2 rings scale zones to 3/4 (start += w/8), kind-1 rings drop the strike tail.  Finally modulate sub-widths are recomputed.

## 10. Auto play (`JRingAutoInit/JRingAuto`, `auto_mode` +0x58c)
Used by the "Auto Ring" accessory/tutorial demonstrations.  `auto_mode` 0 = human; 1,6..10 press when the pointer is about to leave the (centre of the) area; 2 aims at the strike tail; 3,4,5 pre-roll a random aim angle inside the zone (`auto_aim`) with success probability depending on zone size and pointer speed (`JRingAutoInit`), 5 never deliberately misses; 7 only the first hit; 8 prefers the 100 % band; 9/10 combo-prompt specialists (10 = 100 % success).  `RingActive` forces `combo_button=2` (triangle) for mode 9.

## 11. Hit tests
* `EasyAreaHitCheck(a,start,w)`: `wrap360(a-start) <= w` (w≥360 ⇒ true).
* `AreaHitCheck(cur,prev,start,w,inclusive)`: inside-now → true; previous inside and `inclusive` → true; else sweep test: normalise `cur-prev` to (-180,180] and check whether the swept arc crossed the start edge.  This makes the check frame-rate independent (a fast pointer cannot tunnel through a thin zone).
* `HitCheck(area)`: **100** = in the plain/ramp-less zone; **0x78 (120)** = in the strike tail (not for kind-1 rings); modulate: tail → 0x78, full band `[start+w-strike-sub, +sub]` → 100, ramp region → `mod_pct + offset*(100-mod_pct)/(w-strike-sub)` (clamped to 100); `lap_ok` is cleared by any hit on a zone that has a strike tail unless the tail itself was hit.  Returns -1 otherwise.  Type-5 rings: index of first area containing the pointer.
* `HitStopAngle` clamps the pointer to the edge of the sub-zone that was hit (used for the HitBar flash and to freeze the pointer).

## 12. Effect objects spawned
`HitMes` (0xb0 bytes; floating text sprite, variants by area kind/score: "Miss", "Good", "Excellent", percentages; lives 0.9 s, rotates in over 0.25 s, rises with speed 3 - 5.5 t),
`HitBar` (0x60; thin flash line at the stop angle, 0.7 s), `HitArea` (0x70; fade of the hit zone, 0.15 s),
`ComboTrial` (0xb0), `CutJRing` (0x2f0), `CrackJRing` (0x5a0).  All are `CPolObj` + `VIF1Prim` + `DelayDeleteObject` with `Polling`/`MakePacket`; their packet builders are GS rendering code (not ported).

## 13. US build
Retail `SLUS_210.41` contains the same functions at shifted addresses (mapping in `notes/D/us_map.txt`).  `Initialize`, `AddModulateArea`, `MakeResult`, `AreaHitCheck`, `EasyAreaHitCheck`, `HitStopAngle`, `SetEventRing` are byte-identical modulo relocations; `Polling` (89 %), `Sequence` (87 %), `RingActive` (85 %) differ only slightly.  Differences found by instruction-level diff are listed in `us_map.txt` (score column).  Open: confirm whether the US balance changes touch `HitCheck`/`AreaOverCheck` thresholds (7.5°, 5° gaps).

## 14. Open questions
* Who sets `flagsB` kind bits 2-3 and `no_end_wait` — done by the battle overlay (BATTLE.BIN) directly on the object; kind meanings inferred from behaviour.
* `MakeFakeArea` rescaling branch (several real areas) ported from the decompile but not exercised by tests.
* Exact `CrackJRing::Initialize2` / `Initialize1` shard layouts (visual only).
