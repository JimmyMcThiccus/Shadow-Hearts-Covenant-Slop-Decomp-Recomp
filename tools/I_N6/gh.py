import urllib.request, urllib.parse, json, sys
BASE='http://127.0.0.1:8089/'
def get(ep, program, timeout=300, **kw):
    kw['program']=program
    url=BASE+ep+'?'+urllib.parse.urlencode(kw)
    return urllib.request.urlopen(url, timeout=timeout).read().decode('utf-8','replace')
def post(ep, program, body=None, timeout=300, **kw):
    kw['program']=program
    url=BASE+ep+'?'+urllib.parse.urlencode(kw)
    data=urllib.parse.urlencode(body or {}).encode()
    req=urllib.request.Request(url,data=data,method='POST')
    return urllib.request.urlopen(req, timeout=timeout).read().decode('utf-8','replace')
if __name__=='__main__':
    ep=sys.argv[1]; prog=sys.argv[2]
    kw=dict(a.split('=',1) for a in sys.argv[3:])
    print(get(ep,prog,**kw))
