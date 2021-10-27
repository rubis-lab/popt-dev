import os
from datetime import datetime
from time import time
import math
import logparser
import schedulable

jsondir = '/home/rtss/rt-app/rubis'

if __name__=="__main__":
    # os.system("rt-app "+jsondir+"/rubis_test.json")
    sch = schedulable.missoccur(logparser.parse_currentlogs())
    print(sch)
    is_schedulable = schedulable.schedulable(sch)
    exit()

# outputstyle:
# {'thr0-1': True, 'thr1-0': True, 'thr2-2': False, 'thr3-3': False, 'thr0-0': True, 'thr1-1': True}