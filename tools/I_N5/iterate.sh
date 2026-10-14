#!/bin/sh
# usage: iterate.sh dir prog tag n
cd $1
for i in $(seq 1 $4); do
 python3 refresh.py $2 >/dev/null && python3 gaps.py >/dev/null && THETA=0.3 python3 step2.py >/dev/null 2>&1 && python3 select_.py >/dev/null && python3 apply_.py $2 $3d$i | head -1
 python3 refresh.py $2 >/dev/null && python3 gaps.py >/dev/null && python3 step3.py >/dev/null && python3 apply_.py $2 $3t$i | head -1
done
python3 refresh.py $2; python3 gaps.py | sed -n 2p
