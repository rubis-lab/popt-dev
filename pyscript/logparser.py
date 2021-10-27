import os
from datetime import datetime
from time import time
import math

# log_dir = '/home/rtss/rt-app/rubis/log'
log_dir = '/home/rtss/popt-dev/pyscript/test'

def f2s(fullname):
    if len(fullname.split('.')) > 2:
        return False
    if fullname.split('.')[-1] != 'log':
        return False
    filename = fullname.split('.log')[0]
    if filename.split('.')[-1] == 'swp':
        return False
    # if filename.split('-')[0] != 'rubis':
    #     return False
    # return filename.split('rubis-')[-1]
    return filename

def s2f(shortname):
    # return 'rubis-'+shortname+'.log'
    return shortname+'.log'

def parse_currentlogs():
    logs = []

    for f in os.listdir(log_dir):
        shortname = f2s(f)
        if shortname is not False:
            logs.append(shortname.split('rubis-')[-1])

    logdatas = {}

    for log in logs:
        with open(log_dir+'/'+s2f(log), 'r') as lines:
            newdict = {}
            header = []
            data = []     
            # exception not handled. assume log is fine
            for line in lines:
                linedata = []

                arr = ' '.join(line.split()).split(' ')
                # print(logstr)

                if arr[0] == '#idx':
                    arr[0] = arr[0].split('#')[-1]
                    for _ in arr:
                        header.append(_)
                    # print(newdict)
                else:
                    for _ in arr:
                        linedata.append(_)
                    data.append(linedata)
            
            newdict['header'] = header
            newdict['data'] = data

            logdatas[log] = newdict
        
    return logdatas

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





