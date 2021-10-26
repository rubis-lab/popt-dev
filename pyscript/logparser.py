import os
from datetime import datetime
from time import time
import math

log_dir = '/home/rtss/rt-app/rubis/log'

logs = []

def f2s(fullname):
    if len(f.split('.')) > 2:
        return False
    if f.split('.')[-1] != 'log':
        return False
    filename = f.split('.log')[0]
    if filename.split('.')[-1] == 'swp':
        return False
    if filename.split('-')[0] != 'rubis':
        return False
    return filename.split('rubis-')[-1]

def s2f(shortname):
    return 'rubis-'+shortname+'.log'

for f in os.listdir(log_dir):
    shortname = f2s(f)
    if shortname is not False:
        logs.append(shortname.split('rubis-')[-1])


logdatas = {}


for log in logs:
    with open(log_dir+'/'+s2f(log), 'r') as lines:
        newdict = {}        
        header = []
        data = {}
        # exception not handled. assume log is fine
        for line in lines:
            arr = ' '.join(line.split()).split(' ')
            newdict['data'] = {}
            # print(logstr)

            if arr[0] == '#idx':
                arr[0] = arr[0].split('#')[-1]
                for _ in arr:
                    header.append(_)
                
                newdict['header'] = header
                # print(newdict)
            
            
            print(newdict)
        exit()

        newdict['header']
        newdict['data']
        
        logdatas[log] = newdict