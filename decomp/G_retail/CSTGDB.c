/* CSTGDB (retail US 0x003f8cc0..0x003f9290): identical to the demo, see ../G/CSTGDB.c. Addresses: ctor 3f8cc0, dtor 3f8d10, SetData 3f8d80, CheckVersion 3f8df0,
 * InitSDB 3f8e20 ("SBD 0.1x" + "01110623" + "FILEHDR " + "LINKHDR "), Load 3f8fb0 (GetMapName + DvdromOrder::ReadOrder with sdbReadCB 3f8c70), LoadCB 3f9020, ClearData 3f9080,
 * Find 3f9100 (linear scan comparing the u64 tag), GetDataNum 3f9170 (hdr+8), GetDataAddr 3f9190 (hdr + *(u32*)(hdr+0xc)), FindGenericData 3f91c0 (strcmp over GENERIC records, stride at +0x10). */
