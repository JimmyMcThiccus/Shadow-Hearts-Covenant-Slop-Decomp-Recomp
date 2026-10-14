# CFieldCamera (JP 0x004a34a0 … 0x004bef20, 15 methods, object 0xd0)

Port: `port/crates/sh2_field/src/camera.rs` (`FieldCamera::apply`, `comp_frame`, `eval_camera` kinds 0-3). 

| off | type | name |
|---|---|---|
| 0x00 | GsxCamera* | camera (`camera__4CApp`) |
| 0x06 | u8 | flags: b0 enabled, b1 external angles, b2 compose, b3 smooth ease |
| 0x10 | f32 | roll (deg) |
| 0x14 / 0x18 | f32 | transition time left / length (default 50) |
| 0x1c / 0x20 / 0x24 | f32 | view angle / previous view angle / composed view angle (default 0.625 = 320/512) |
| 0x28 | f32 | smoothing delay (`SetViewDelay`), 0 = off |
| 0x30 / 0x40 | FVector | target / camera position (logical) |
| 0x50 / 0x60 | FVector | blend-from target / camera (`CompFrame` copies 0x70/0x80 here) |
| 0x70 / 0x80 | FVector | composed target / camera actually used |
| 0x90 / 0xa0 | FVector / f32 | smoothing goals (target / view angle) used while delay > 0 |
| 0xc0 / 0xc4 / 0xc8 / 0xcc | f32 | pitch / yaw / roll (deg, +180 offset) / 1.0 |

`Apply(dt)`: optional exponential chase (delay), optional transition blend with quadratic or atan ease between the previous composed pose and the new one,
then yaw = atan2(dx,dz)*57.29579+180, pitch from the Y-rotated delta, matrix = RotZ(roll) RotX(pitch) RotY(yaw) + translate(cam), `SetViewMatrix(320/fov, 0.8, 0.9333, 1.0, 16777000)`.
The CAMERA table (see mps_format.md) selects *what* target/position to feed: `CField::UpdateFieldCamera` (JP 0x004a8be0, 0x19fc) — kinds 0..5.
