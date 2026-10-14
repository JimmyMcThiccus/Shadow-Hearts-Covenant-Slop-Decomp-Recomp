# Integration baseline (before any consolidation edit)

Date: 2026-10-09. Environment: `SH2_DISC_DIR` = JP Furokuban folder, `SH2_US_DISC_DIR` = US retail disc 1 folder,
`CARGO_TARGET_DIR` = private dir (the shared `port/target` was avoided because other agents build concurrently),
`cargo ... --offline`.

## `cargo check --workspace`

First run (the crates as the eight section agents left them): **green**, 4 warnings (3 in `sh2_script`).

## `cargo test --workspace`

Run #1 (a few minutes later, after a renderer agent had added `sh2_gfx/src/bevy/*`): **build failure**, no test executed.

| # | Failure | Cause | Owner / action |
|---|---|---|---|
| 1 | `sh2_gfx` (lib) `src/bevy/model.rs:249,263,269`: `expected glam::Vec3, found bevy::bevy_math::Vec3`, `expected &mut Mesh, found AssetMut<Mesh>` | the workspace pinned `glam = "0.30"` but **Bevy 0.19.1 re-exports glam 0.32**, so every `Vec3/Mat4` of `sh2_formats::math` is a different type from Bevy's. | Fixed by me: workspace `glam = "0.32"` (this removes the two `Vec3` errors). The `AssetMut<Mesh>` vs `&mut Mesh` error was in the renderer agent's in-flight file and disappeared in the next run (their fix). |
| 2 | `sh2_app` (bin, test) `src/viewer.rs:323`: `TextFont { font_size: 16.0 }` expected `FontSize` | Bevy 0.19 `TextFont::font_size` is a `FontSize` enum, file is another agent's work in progress (`sh2_app` is out of my edit scope) | requests.md: use `FontSize::Px(16.0)` (build of `sh2_app` excluded from my test runs until fixed) |

Run #2 (`cargo test --workspace --exclude sh2_app`, glam 0.32): **all green**.

| crate | unit | integration |
|---|---:|---|
| sh2_battle | 38 | - |
| sh2_core | 28 | - |
| sh2_field | 9 | `real_data` 4 (incl. `us_maps_parse` against the US disc) |
| sh2_formats | 4 | `model_real` 4 |
| sh2_gfx | 70 | `model_runtime` 1, `texture_cross_check` 1 |
| sh2_menu | 26 | - |
| sh2_script | 3 | `lsd_real` 2, `real_scripts` 3, `vsm_real` 1 |

Warnings at baseline: `sh2_script` 3 (lib); none that fail the build.

(Counts moved by a few between runs because other agents were adding tests concurrently.)
