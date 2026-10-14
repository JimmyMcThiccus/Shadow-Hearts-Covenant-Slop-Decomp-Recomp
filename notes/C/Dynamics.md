# Dynamics / DynamicsControl / BRN_* — hair, cloth and tail chains (`DYNH` extension block)

JP: `DynamicsControl` 0x00252e60..0x00253288, `Dynamics` 0x00253290..0x00253cb4, `BRN_LinkList` 0x00249290..0x0024b46c (soft chain
physics: `setLinkParams`, `applyForces`, `applyConstraint`, `integrate`, `sym_tridiag_solver`, bending forces), `BRN_inertia` 0x00252850,
`BoundingCircle` 0x00253cc0 (collision circles from `DHSH` blocks), `BRN_Math::gauss`.  ("BRN" = the programmer's soft-body library.)

## DYNH block (extension chain entry, `EXHD`+`DYNH`, 16-byte units)
```
+0x00  "EXHD" "DYNH" u16 version=1 u16 ?=1  u32 size_in_16B
+0x10  chain[chain_count]   (chain_count = u16 @ block+0x0a... in code: `*(u16*)(block+10)`; here the sample has 1)
chain header (0x10):  char name[8]            e.g. "KUBI" (neck)
                      u16 node_count          @+8
                      u16 flags               @+0xa  bit3 = bending-force enabled (initBendingForce); bits 6.. = damping (value*0.01)
                      u16 gravity             @+0xc  gravity.y = value * 0.01 * 9.8
                      u16 air_resistance      @+0xe  value * 0.01
nodes[node_count] (0x30 bytes): char frame_name[...]  (searchFrame(name) -> Frame*), params..., FVector rest_world_pos @+0x20
```
`DynamicsControl` (0x14 bytes): `+0 block*`, `+4 Dynamics[]` (0x30 each), `+8 BoundingCircle*`, `+0xc` enable=1, `+0x10` dt (set by `addTime`).
`Dynamics` (0x30 bytes): `+0 chain hdr`, `+4 nodes`, `+8 BRN_LinkList*` (0x5b0 bytes, node_count-1 links), `+0xc Frame*[]`
(per-node bound frame), `+0x10 BoundingCircle*`, `+0x14 dt`, `+0x18 root Frame*` (`Init`: `frames + rec.parent*0x1f0` of node 0),
`+0x20 FVector` accumulated.
`Create`: link i gets `setLinkParams(i-1, node[i].pos - node[0].pos, (0,0,0,1)/*up*/, ...)`.  `ResetLink`: re-seeds the chain from the current
world positions of the bound frames (`getWorldPos`) and root orientation (`Quaternion(Matrix)` normalised) -> `BRN_LinkList::resetLink`.
`Model::DynaFunction(1)` resets all chains (called on motion changes), `DynaReset`, `SetDynaGRV(vec, chain)` overrides gravity.
Rust: `sh2_formats::model::ExtBlock` keeps the raw bytes; typed parser is a TODO (physics not ported).

---

# Solver and per-frame flow (ported 2026-10-09: `sh2_gfx::model::{brn, dynamics}`)

Everything below was read from the decompilation (Ghidra `SLPM_602.19`, 0x00249290..0x0025a900); the Rust port keeps the formulas, constants and
call order.  Tests: `sh2_gfx/src/model/brn.rs` (tridiagonal solver, rest equilibrium, finite swinging) and `sh2_gfx/tests/dynamics_runtime.rs`
(every `DYNH` model of the JP disc -- 35 `.SET` / `.BCM` characters -- simulated for 5 s with a turning / travelling actor: finite, rigid matrices).

## Constants and defaults (`BRN_LinkList::BRN_LinkList(int)` 0x00249290, `Dynamics::Create` 0x00253480)
| offset | default | meaning |
|---|---|---|
| +0x00 i32 | 2 | sub-steps per call (then 1 / 2 / 4 / 8 from the largest `|d|^2 - L^2` of the last constraint solve: > 0.25 / 0.5 / 1) |
| +0x04 | n | link count = `node_count - 1` (<= 5) |
| +0x08 | 50.0 | air resistance (`DYNH` +0xe raw * 0.01 when non-zero) |
| +0x10 FVector | (0, **24.5**, 0, 1) | gravity (y = raw * 0.01 * 9.8 when `DYNH` +0xc is non-zero; **raw 0 keeps the default 24.5**, e.g. PC 005's hair) |
| +0x594 / +0x598 / +0x59c | 250 / 1000 / 100 | force clamp, Baumgarte beta, gamma |
| +0x5a0 | 0.95 | velocity multiplier per sub-step (`DYNH` flags >> 6 * 0.01 when non-zero) |
| `BRN_inertia` limits | 1.5 / 30 / 6.3 / 6.3 | max-norm clamps of root velocity / acceleration / angular velocity / angular acceleration |
| link mass | `node.param_c` (0.1 / 0.025) | link `i-1` takes the mass of node `i` |

`BRN_Link` (0x60): +0x10 pos (relative to the root joint), +0x20 vel, +0x30 force, +0x40 mass, +0x44 rest length, +0x50 pseudo acceleration.

## Per update (`Model::calcMatrix` 0x00240f30: `Frame::calcMatrix`, **`DynamicsControl::calcMatrix`**, IK, `FrameWeight::calcWeight`)
1. `Dynamics::setRootPos` (0x00253780, only when `addTime` stored a non-zero dt): `calcNextLinkList(1/30 s, rootPos, rootQuat)` with `rootPos` =
   `getWorldPos(frames[0])` and `rootQuat` = the rotation of `rootFrame->world` (the *parent* frame of node 0, `Dynamics::Init`).  **The step is the
   constant 0x3d088889 = 1/30 s regardless of the real delta**; the port steps a 1/30 s accumulator.
2. `calcNextLinkList` (0x00249670), `n` = sub-steps, `h = (1/30 / n) * 2`: for each sub-step `f = (s+1)/n`: attitude `slerp(prev, root, f)`, position
   `prev*(1-f) + root*f` -> `BRN_inertia::moveTo(h, ...)` (v = dp/h, a = dv/h, omega = 2/h * vec(q_new * conj(q_prev)), alpha = d omega / h, all clamped)
   -> `clearForces` -> `applyForces` -> `applyConstraint(h)` -> `dissipateEnergy` -> `integrate(h)` -> `prev = links`.  A collision callback
   (`BoundingCircle::CollisionFnc` from the `DHSH` circles) re-runs the sub-step once with collision forces (ported: `brn::calc_next_collide`).
3. `applyForces` per link: `f = gravity*m`, pseudo acceleration `-acc + 0.4*(omega x v) - 0.04*(omega x (omega x v)) - 0.04*(alpha x p)` times `m`,
   bending force (below) and `-m*10 * p (p.v)/(p.p)` when bending is enabled, clamp to 250, drag `-(v*(air + |v|*0.02)*1e-4)/m`.
4. `applyConstraint` (0x0024a420): `d_i = p_i - p_{i-1}` (`d_0 = p_0`), tridiagonal `J M^-1 J^T lambda = rhs` with
   `diag_0 = d0.d0/m0`, `diag_i = (1/m_i + 1/m_{i-1}) d_i.d_i`, `off_i = -(d_i.d_{i-1})/m_{i-1}`,
   `rhs_i = -dv_i.dv_i - d_i.a_i - 1000 (d_i.d_i - L_i^2) - 100 (d_i.dv_i)` (`a_i` = force/m difference), all scaled by their max (`sym_tridiag_solver`
   0x0024af20 = Thomas algorithm); then `v_i += (d_i lambda_i - d_{i+1} lambda_{i+1}) * h * (scale ratio)`.  **There is no `1/m` in this update**
   (the loaded chain stretches a little; only the directions are used afterwards).  `integrate` = kick-drift, `applyConstraint(h/2...)`, kick-drift.
5. `initBendingForce` (0x0024b260, `DYNH` flags bit 3): `BRN_BendCalc::calcBendForce` walks from the tip: `rhs = gravity*m_i + d_{i+1} lambda_{i+1}`,
   `lambda_i = d_i . rhs`, `bend_i = -(rhs - lambda_i d_i)` (the Gauss elimination of the 4x4 `[I d; d^T 0]` system), i.e. the force that holds each
   segment at its rest direction.  At run time the stored vector is rotated by the root attitude (`BRN_RotVecWithQuatInv`).
6. `Dynamics::calcDynaLink` (0x00253820), per node but the last: `d = normalise(J(i+1) - J(i))` from the frames' **current** world matrices,
   `v = normalise(getLinkGeometry(i))` (link `i` minus link `i-1`), `q = shortest arc d -> v` (`(axis/(2cos), cos)` in the original), and the frame's
   `world[buf]` becomes `T(J) R(q) T(-J) * world`.  The original does **not** move child frames (their joints stay on the animation); the port rotates
   the descendants as well (`DynamicsControl::propagate_children`) so strands stay connected.
7. `Model::DynaFunction(v)` (`DYNA` event): 0 = disable (frames keep the animation pose), 1 = enable (re-seed with `Dynamics::ResetLink` when it was
   disabled), 2 = `DynaReset`.  `ResetLink` copies the animated joint positions into the links (`setLinkPosition(i-1, p_i - p_0)`, zero velocity)
   and `resetLink(rootPos, q)`.

## Joint positions (important)
`Frame::getWorldPos(frame)` (0x00243b20) = `world[buf] * (-t)` with `t` = the record vector at `FRHD +0x20` (negated!): the rest joint is
`pivot = -t` in mesh space (equal to the `DYNH` node `+0x20` vector, e.g. PC 005 `KAMIO` (0, -16.65, 0.51)); it is **not** `(R*T).pos`
(bone rotations other than the usual (-1,0,0,0) make `R*t` meaningless).  `Skeleton::joint_world(pose, i) = pose[i] * (-t_i)`.

## Where it is used
`sh2_gfx::model::ModelInstance` owns an `Option<DynamicsControl>` (created from the `DYNH` blocks; `SH2_NO_DYNAMICS=1` disables), advanced in
`add_time`, applied in `update_pose` right after the skeleton and before the `WFRH` virtual frames.  The model-to-world matrix (`set_world`, fed by
`bevy::model::animate_models` from the holder's `GlobalTransform`) makes gravity point down and lets actor turns / moves excite the chains
(a teleport > 25 units re-seeds).  Census (JP disc): 109 models carry `DYNH` (PC hair `kami` / `Rmomi` / `Lmomi`, Joachim's cross / coat tails `CROSS`
`CARP_B`, Roger / Gepetto / Kanako belts and tapes, 25 hair-weapon `.WPN` packages ...); retail US: 611.
Ported 2026-10-09 (see notes/integration/actors.md section 8): `BoundingCircle` (`DHSH` collision circles, 86 JP models: `model::dynamics::check_collision`, retry pass with `applyCollisionForce`), `SetDynaGRV` (`ModelInstance::set_dyna_grv`, cutscene `GRV` event).  `IKControl` is dead code (never allocated).  Not ported: `chrDynaReset`.
