# Misc section-D classes

| class | JP | notes |
|---|---|---|
| `LineBlur` | 0x00326860.. | radial line blur: `Create()`, `SetCenter(x,y)`, `SetPower(f)`, `SetBlurRect`, `ChangeLine` (rebuilds the line fan), `GetUV(x,y,&u,&v)`, `SetPacket(_QWD*)`, `getPacket`; vptr 0x406c60; driven by VSM `blr*Line` calls and by battle |
| `HitShot` | 0x0030adc0.. | projectile path with `HitDynaKey` list (`AddKey`), `SetPoint(from,to)` (direction normalised), `AddTime(dt, speed)`, `IsAtEnd`, `SetUpdateMode`, `GetModdleSpeed`; data from `HTFH` (§Y) |
| `HitCylinder` | (EffectCore +0x36c) | cylinder volume around a model, `AddTime(f)`; created by `hitCreateCylinder` |
| `EffectSprite` / `EffectBlur` | | see effect_system.md |
| `EffectGunya`, `EffectBarin` | 0x0031d760.., 0x00321e20.. | lattice deformation / free polygon batch driven by `gny*`/`bng*` syscalls |
| `LsdEffectServer`, `LsdEffect` | 0x00324b00.. | `LSDPlayer` track handler for effect tracks (`Open(RingBuffer*)`, `Read`, `Event(handle,id,f,f)`, `Close`); static `handler` 0x00421e40; `CheckData(_LSDTrackHdr*)` validates the track header |
| `SmoothFilter` | 0x0038e4e0.. | full-screen smoothing/blur layer: `LayerSetUp(n)` allocates `n` capture layers, `FilterLevel(f)`, `FilterAlpha(a)`, `getPacket()` builds the 0x6a8-byte multi-pass sprite packet; enabled from the field by `CFieldSocket::SetSmoothFilter(f,i)` (0x003bdfc0) |
| `SoulEnergy` | 0x0028b3d0.. | menu widget (MenuTexture ×3) showing the soul-energy meter: `Create(tex,tex,tex)`, `SetMeter(f)`, `SetAlpha`, `SetOwner(MenuWindow*)`, `Update(int,int,ushort)` (3 KB sprite layout), `Connect(_QWD*)`; wrapper `CmdSoulEnergy` (command-menu item) |
| `CGhostEfx` | 0x003d3f50.. | spirit/ghost screen effect (distortion with `noiseData`): `Create()`, `AddTime`, `MakePacket` (2.4 KB), `CreateLight/ReleaseLight/UpdateLight` (a point light that follows the ghost), `UpdateS` static |
| `CBRingSoulOT`, `CBM412OT`, `CBM413OT`, `CBM524` | 0x003da6e0.. | `CBBPolygon` subclasses (section C base) for specific magic visuals: back-screen-texture (`BackScreenTexture`) + `LayeredTexture`, sequence key-frames (`SequenceBase::setKeyFrame`), particle arrays of 0x20 bytes, `AddTime(dt)` integrates `pos += vel`, rotates velocity by a small Z rotation each tick, samples colour key frames; `NewLifeMake(i)` respawns a particle (random tilt ±11°); `CBM524` additionally owns four `CPathControl` ribbons following the weapon-tip frame |
