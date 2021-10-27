import os
from datetime import datetime
from time import time
import math
import logparser


startfrom = 5

# True or False
def schedulable(logdatas):
    ret = {}
    for lkey in logdatas:
        sched = True
        lvalue = logdatas[lkey]
        deadline = int(lvalue['data'][startfrom][3])
        
        for idx in range(startfrom, len(lvalue['data'])):
            line = lvalue['data'][idx]
            if int(line[2]) > deadline:
                sched = False
                break

        ret[lkey] = sched
    
    return ret


# sch = schedulable(logparser.parse_currentlogs())
# print(sch)
# exit()

# outputstyle:
# {'thr0-1': True, 'thr1-0': True, 'thr2-2': False, 'thr3-3': False, 'thr0-0': True, 'thr1-1': True}

# {
#     'thr0-1': {
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

