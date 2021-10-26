import os
from datetime import datetime
from time import time
import math

log_dir = '/home/rtss/rt-app/rubis/log'

logs = []

for f in os.listdir(log_dir):
    if len(f.split('.')) > 2:
        continue
    if f.split('.')[-1] != 'log':
        continue
    if f.split('-')[0] != 'rubis':
        continue
    
    logs.append(f)

logdatas = []

for log in logs:
    with open(log_dir+'/'+log, 'r') as lines:
        datas = {}

        # exception not handled. assume log is fine
        for line in lines:
            splited = ' '.join(line.split()).split(' ')
            print(splited)
            

        


    