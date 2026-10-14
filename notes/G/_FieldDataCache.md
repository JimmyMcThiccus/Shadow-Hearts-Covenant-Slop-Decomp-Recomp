# _FieldDataCache

| JP addr | size | method |
|---|---|---|
| `0x004a4470` | 0x40 | `_FieldDataCache::GetName(char*)` |
| `0x004bf770` | 0x90 | `_FieldDataCache::Release()` |
| `0x004bf800` | 0x120 | `_FieldDataCache::FindKey(const char*)` |
| `0x004bf9d0` | 0x170 | `_FieldDataCache::EncodeKey(const char*, unsigned int&)` |
| `0x004bfb40` | 0x26c | `_FieldDataCache::DecodeKey(char*, unsigned int, unsigned int)` |
| `0x004bfdb0` | 0xc0 | `_FieldDataCache::Find(int, const char*)` |
| `0x004bfe70` | 0xe0 | `_FieldDataCache::GetNewData(int, const char*)` |

Decompiled source: `decomp/G/_FieldDataCache.c`.
