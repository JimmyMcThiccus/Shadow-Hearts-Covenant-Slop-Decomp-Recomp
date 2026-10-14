# BgEffectMan / CBgElement / CSTGDB

* `CSTGDB` (stage database, 0x24 bytes, JP 0x003c1f60): loads an `SDB` file (`DvdromOrder::ReadOrder` → `LoadCB` → `SetData` → `InitSDB`). Format: first u64 = `"SDB 0.10"` or `"SDB 0.11"`
  (as little-endian text `SBD`-swapped: bytes `53 42 44 20 30 2e 31 30`), at +8 u64 build id, at +0x10 `"FILEHDR "`, at +0x1c offset of the link table `"LINKHDR "`
  (count at +8, entries of 0x10 bytes `{u64 key, ?, u32 offset (relative to the entry)}`); `Find(key)` returns the record, `GetDataNum/GetDataAddr(rec)` its count/payload,
  `FindGenericData(name)` a named record.  Keys are 8-char ASCII tags, e.g. `"LIGHT   "` (0x202020544847494c).
* `CBgElement` (0x288 bytes): one background element definition loaded from an SDB (`Create(uchar* sdb, bool)` reads the `LIGHT   ` records into up to 16 lights — type/colour/pos/dir —
  `UpdateLight(dt)` animates them, `LgtAttachFrame(i, Frame*)` binds a light to a model frame, `Dsp/Clr` show/hide, `Clear` frees them).
* `BgEffectMan : PutiManager` (0x420+ bytes; static `eff__11BgEffectMan` 0x40adb0 = current instance, `cmnTexture` 0x40adac common texture pack `+0x401700` path loaded in `Init`, `m_curMagic` 0x40adb4):
  8 sets × 64 slots of `PutiPrim*` at +0x20; `CreateEffect(set, slot, type, params)` → `CreateFpEffect` (<0x100) or `CreateFldBGEffect`, `ClearEffect(set, slot|-1)`, `DeleteAll(set|-1)`,
  `Dsp(set)`/`Clr(set)` (virtual +0x38 show/hide on every prim of the set), `EffectAlpha(set, slot, alpha)` (virtual +0x34 `SetAlphaPower`), `InitCmnTex` builds the common texture descriptor table
  (+0x1c: 0x14-byte entries {pixels*, clut*, w, h, psm}) from the `GetFileCount/GetFileEntry` texture container.
