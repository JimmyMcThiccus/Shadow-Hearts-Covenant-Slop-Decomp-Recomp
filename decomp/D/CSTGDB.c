// decomp/D/CSTGDB.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x003c1f60  __ct__6CSTGDBFv  =  CSTGDB::CSTGDB
undefined4 * CSTGDB::CSTGDB(undefined4 *this)

{
  *this = 0;
  this[1] = 0;
  this[2] = DelayDeleteObject::__vt;
  this[2] = CSTGDB::__vt;
  this[3] = 0;
  this[6] = 0;
  this[7] = 0;
  this[8] = 0;
  this[5] = 0;
  this[4] = 0xffffffff;
  return this;
}

// JP: 0x003c1fe0  __dt__6CSTGDBFv  =  CSTGDB::~CSTGDB
int CSTGDB::~CSTGDB(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 8) = CSTGDB::__vt;
    CSTGDB::ClearData(this);
    if (this != 0) {
      *(undefined1 **)(this + 8) = DelayDeleteObject::__vt;
    }
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x003c2070  SetData__6CSTGDBFPv  =  CSTGDB::SetData
undefined8 CSTGDB::SetData(int this,undefined4 param_2)

{
  undefined8 uVar1;
  
  if (this->i32_14 == 0) {
    this->u32_18 = param_2;
    if (this->i32_20 != 0) {
      __dla(this->u32_20);
      this->u32_20 = 0;
      this->u32_1c = 0;
    }
    this->u32_14 = 2;
    uVar1 = CSTGDB::InitSDB(this);
  }
  else {
    this->u32_14 = 0xffffffff;
    uVar1 = 0;
  }
  return uVar1;
}

// JP: 0x003c2110  CheckVersion__6CSTGDBFUl  =  CSTGDB::CheckVersion
undefined4 CSTGDB::CheckVersion(int this,long param_2)

{
  undefined4 uVar1;
  
  if ((this->i32_18 == 0) || (**(long **)(this + 0x18) != param_2)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

// JP: 0x003c2170  InitSDB__6CSTGDBFv  =  CSTGDB::InitSDB
undefined4 CSTGDB::InitSDB(int this)

{
  undefined4 uVar1;
  long *plVar2;
  int iVar3;
  int iVar4;
  
  if (this->i32_18 == 0) {
    uVar1 = 0;
  }
  else if (((*(long *)(this->i32_18 + 0x10) == 0x20524448454c4946) &&
           (**(long **)(this + 0x18) == 0x30312e3020444253 ||
            **(long **)(this + 0x18) == 0x31312e3020444253)) &&
          (*(long *)(this->i32_18 + 8) == 0x3332363031313130)) {
    plVar2 = (long *)(*(int *)(this->i32_18 + 0x1c) + this->i32_18);
    if ((*plVar2 == 0x205244484b4e494c) && ((int)plVar2[1] != 0)) {
      iVar3 = *(int *)((int)plVar2 + 0xc) + (int)plVar2;
      this->i32_1c = (int)plVar2[1];
      uVar1 = __nwa((int)plVar2[1] << 2);
      this->u32_20 = uVar1;
      for (iVar4 = 0; iVar4 < (int)plVar2[1]; iVar4 = iVar4 + 1) {
        *(int *)(this->i32_20 + iVar4 * 4) = iVar3 + iVar3->i32_c;
        iVar3 = iVar3 + 0x10;
      }
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// JP: 0x003c2390  Load__6CSTGDBFPCc  =  CSTGDB::Load
undefined4 CSTGDB::Load(int this,undefined4 param_2)

{
  undefined4 uVar1;
  
  if ((this->i32_c == 0) && (this->i32_14 == 0)) {
    uVar1 = DvdromOrder::ReadOrder
                      (DvdromOrder::Dvdromour,param_2,0x3c1ef0,0,this,0);
    this->u32_10 = uVar1;
    this->u32_14 = 1;
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// JP: 0x003c2420  LoadCB__6CSTGDBFP9BufMemoryi  =  CSTGDB::LoadCB
undefined4 CSTGDB::LoadCB(int this,int param_2,int param_3)

{
  undefined4 uVar1;
  long lVar2;
  
  this->u32_10 = 0xffffffff;
  this->i32_c = param_2;
  this->u32_14 = 0;
  if ((param_3 == 0) &&
     (lVar2 = CSTGDB::SetData(this,param_2->u32_4), lVar2 != 0)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// JP: 0x003c24c0  ClearData__6CSTGDBFv  =  CSTGDB::ClearData
undefined4 CSTGDB::ClearData(int this)

{
  if (this->i32_10 != -1) {
    DvdromOrder::deleteOrder(DvdromOrder::Dvdromour,this->u32_10);
    this->u32_10 = 0xffffffff;
  }
  if (this->i32_c != 0) {
    BufMemory::~BufMemory(this->u32_c,1);
    this->u32_c = 0;
  }
  this->u32_14 = 0;
  if (this->i32_20 != 0) {
    __dla(this->u32_20);
    this->u32_20 = 0;
  }
  return 1;
}

// JP: 0x003c2580  Find__6CSTGDBFUl  =  CSTGDB::Find
undefined4 CSTGDB::Find(int this,long param_2)

{
  int iVar1;
  
  if (this->i32_14 == 2) {
    for (iVar1 = 0; iVar1 < this->i32_1c; iVar1 = iVar1 + 1) {
      if (param_2 == **(long **)(this->i32_20 + iVar1 * 4)) {
        return *(undefined4 *)(this->i32_20 + iVar1 * 4);
      }
    }
  }
  return 0;
}

// JP: 0x003c2630  GetDataNum__6CSTGDBFPQ23SDB9tagHEADER  =  CSTGDB::GetDataNum
undefined4 CSTGDB::GetDataNum(undefined8 this,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = param_2->u32_8;
  }
  return uVar1;
}

// JP: 0x003c2670  GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER  =  CSTGDB::GetDataAddr
int CSTGDB::GetDataAddr(undefined8 this,int param_2)

{
  if (param_2 == 0) {
    param_2 = 0;
  }
  else {
    param_2 = param_2 + param_2->i32_c;
  }
  return param_2;
}

// JP: 0x003c26c0  FindGenericData__6CSTGDBFPCc  =  CSTGDB::FindGenericData
char * CSTGDB::FindGenericData(undefined4 this,char *param_2)

{
  int iVar1;
  char *__s1;
  int iVar2;
  long lVar3;
  int iVar4;
  
  lVar3 = CSTGDB::Find(this,0x20434952454e4547);
  if (lVar3 != 0) {
    iVar1 = CSTGDB::GetDataNum(this,lVar3);
    __s1 = (char *)CSTGDB::GetDataAddr(this,lVar3);
    for (iVar4 = 0; iVar4 < iVar1; iVar4 = iVar4 + 1) {
      iVar2 = strcmp(__s1,param_2);
      if (iVar2 == 0) {
        return __s1;
      }
      __s1 = __s1 + __s1->i32_10;
    }
  }
  return (char *)0x0;
}
