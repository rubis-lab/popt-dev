import os
from datetime import datetime
from time import time
import math
import logparser


startfrom = 5
def get_min(lvalue):
    lvaluemin = 9999999999
    for arr in lvalue['data']:
        if lvaluemin > int(arr[3]):
            lvaluemin = int(arr[3])

    return lvaluemin
# True or False
def misscount(logdatas):
    linenum = 0
    deadlinemiss = 0
    for lkey in logdatas:

        lvalue = logdatas[lkey]
        linenum += lvalue['lines']-startfrom
        
        deadline = get_min(lvalue)
        
        for idx in range(startfrom, len(lvalue['data'])):
            line = lvalue['data'][idx]
            if int(line[2]) > deadline:
                deadlinemiss += 1
   
    return linenum, deadlinemiss

# def schedulable(missdata):
#     for misskey in missdata:
#         thr = missdata[misskey]
#         if thr > 0:
#             return False
#     return True

# sch = schedulable(logparser.parse_currentlogs())
# print(sch)
# exit()

# outputstyle:
# {'thr0-1': True, 'thr1-0': True, 'thr2-2': False, 'thr3-3': False, 'thr0-0': True, 'thr1-1': True}

# {
#     'thr0-1': {
#         'lines': 100,
#         'header': ['idx', 'perf', ...],
#         'data': [
#             ['1', '6000', ...],
#             ['1', '6000', ...],
#             ['1', '6000', ...],
#             ['1', '6000', ...],
#             ['1', '6000', ...],
#         ]
#     },
#     'thr1-0': {
#         'header': ['idx', 'perf', ...],
#         'data': [
#             ['1', '6000', ...],
#             ['1', '6000', ...],
#             ['1', '6000', ...],
#             ['1', '6000', ...],
#             ['1', '6000', ...],
#         ]
#     }
# }

# header
# 0   idx
# 1   perf
# 2   run
# 3   period
# 4   start
# 5   end
# 6   rel_st         
# 7   slack
# 8   c_duration
# 9   c_period
# 10  wu_lat

