# cleaned-C generator for the US BATTLE overlay: Ghidra decompile -> readable C (CBattle/BtlChr field names, phase constants)
import sys,re
sys.path.insert(0,'.')
from lib import *
CB={0x24:'bFlags24',0x25:'bFlags25',0x28:'nPhase',0x2a:'nStep',0x2c:'cActor',0x2d:'cActorB',0x2e:'nPartner',0x30:'nCurTurnChr',0x32:'wTurnPendMask',0x36:'nComboCnt',0x38:'flDeltaT',
    0x44:'nCmd0_target',0x48:'nCmd1',0x4c:'nCmdKind',0x50:'nCmd3',0x54:'nCmdMask',0x60:'nShortcutTarget',0x84:'flMenuTimer',0x88:'flMenuTimer2',0x90:'flTurnPush',
    0x4038:'nDestCount',0x403a:'nDestIdx',0x403c:'aDest',0x407c:'bTarotFlags',0x407e:'nTarotCard',0x4080:'nTarotParam',
    0x45c4:'pCamera',0x45c8:'pParamDisp',0x460c:'pTurnOrderDisp',0x4628:'pBtlResult',0x462c:'nDataSlot',0x463c:'wChrMask',0x4848:'cPCCount',0x4861:'cDataId',0x4865:'cMesWinId',0x4868:'nIopHandle',
    0x4890:'cMesWinId2',0x4894:'wDeadMask',0x4896:'nMsgHandle'}
CH={0:'bFlagsA',1:'bFlagsA1',2:'bFlagsA2',4:'bFlagsB',5:'bFlagsB1',6:'bFlagsB2',8:'bState',9:'bState2',0x70:'nCharId',0x80:'nHp',0x8a:'nSp',0x9c:'pModel',0xa0:'pParam',0xb0:'aPos',0xc0:'aDest',0xe4:'flTurnTimer',0xe8:'flTurnWaited',0xec:'nMonId',0xf4:'pAiScript',0xf8:'pAiCursor',0xfc:'aAiReg',0x110:'wTurnCount'}
def clean(t,thisname='this'):
    t=re.sub(r'/\* WARNING: [^*]*\*/\s*','',t)
    IDX=r'(\*\((?:char|int|short) \*\)\(\w+ \+ 0x[0-9a-f]+\)|\w+)'
    def chrsub(m):
        base=m.group(2); idx=m.group(3); off=int(m.group(4),16)-0xb0
        return 'chr(%s,%s)->%s'%(base,idx,CH.get(off,'f%x'%off))
    t=re.sub(r'\*\((\w+) \*\)\((\w+) \+ '+IDX+r' \* 0x510 \+ (0x[0-9a-f]+)\)',chrsub,t)
    def fld(m):
        base=m.group(2); off=int(m.group(3),16)
        return '%s->%s'%(base,CB[off]) if off in CB else m.group(0)
    t=re.sub(r'\*\((\w+) \*\)\((\w+) \+ (0x[0-9a-f]+)\)',fld,t)
    t=re.sub(r'chr\((\w+),\*\(char \*\)\(\w+ \+ 0x2c\)\)','chr(\\1,\\1->cActor)',t)
    t=re.sub(r'chr\((\w+),\*\(int \*\)\(\w+ \+ 0x44\)\)','chr(\\1,\\1->nCmd0_target)',t)
    t=re.sub(r'(?<![\w])\((\w+)->(\w+)\)','\\1->\\2',t)
    m=re.search(r'(\w+) = \(int\)param_1;',t)
    if m:
        al=m.group(1); t=t.replace(m.group(0),'/* %s = param_1 */'%al); t=re.sub(r'\b'+al+r'\b',thisname,t)
    m=re.search(r'(\w+) = param_1;',t)
    t=re.sub(r'\bparam_1\b',thisname,t)
    return t
def outline(t):
    steps=sorted(set(int(x,0) for x in re.findall(r'nStep (?:==|!=|<|>|<=|>=) (0x[0-9a-f]+|\d+)',t))|set(int(x,0) for x in re.findall(r'nStep = (0x[0-9a-f]+|\d+);',t)))
    phases=sorted(set(int(x,0) for x in re.findall(r'nPhase = (0x[0-9a-f]+|\d+);',t)))
    states=sorted(set(int(x,0) for x in re.findall(r'bState = (0x[0-9a-f]+|\d+);',t)))
    msgs=sorted(set(int(x,0) for x in re.findall(r'SetBtlMessage__7CBattleFiPv\((?:\w+|[^,]+),(0x[0-9a-f]+|\d+)',t)))
    calls=re.findall(r'(?<![\w.>])([A-Z][A-Za-z0-9_]*__[0-9A-Za-z_]+)\s*\(',t)
    import collections
    cc=collections.Counter(calls)
    return steps,phases,states,msgs,cc
if __name__=='__main__':
    prog=sys.argv[1]; a=int(sys.argv[2],16)
    t=gh.get('decompile_function',prog,address='%08x'%a,timeout=300)
    print(clean(subst(prog,t)))
