# CFieldEvent — EVENTBOX / CAMEVENT trigger volumes (JP 0x004befa0 … 0x004bf6b0, 8 methods, object 0xc)

`{int count; int is_camera; SDB::tagEVENTBOX* boxes;}`. Port: `event.rs`. `HitCheck(pos, a, mode)`; box layout in `mps_format.md`.
Users: `CField::Polling` (enter/leave/examine events -> `SetFieldEvent`), `UpdateFieldCamera` (CAMEVENT -> camera index), `CallFunc` (script queries `GetEventBoxFromID/Group`).
The centre of 196/197 JP event boxes is inside its own box (validation).
