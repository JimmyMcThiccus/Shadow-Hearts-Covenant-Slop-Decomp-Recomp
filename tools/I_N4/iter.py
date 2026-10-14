import subprocess,sys,pickle,json,urllib.request,re,os
from concurrent.futures import ThreadPoolExecutor
def sh(c): return subprocess.run(c,shell=True,capture_output=True,text=True)
import gh
t=gh.get('list_functions',gh.MAIN); open('us_now.txt','w').write(t)
print(sh('python3 setup.py').stdout[-200:])
print(sh('python3 gaps.py').stdout[:200])
print(sh('python3 fetch3.py').stdout[-50:])
r=sh('python3 real2.py'); print(r.stdout[-300:], r.stderr[-200:])
