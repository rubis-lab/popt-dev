import os
from datetime import datetime
from time import time
import math
import logparser
import schedulable
import json

jsondir = '/home/rtss/json'


def create_logdir(jsonfile):
    with open(jsonfile, "r") as f:
        j = json.loads(f.read())

    logdir = j["global"]["logdir"]
    if not os.path.exists(logdir):
        os.makedirs(logdir)
    
    return

if __name__=="__main__":
    
    jsonfiles = os.listdir(jsondir)


    for jsonfile in jsonfiles:
        if jsonfile.split(".")[-1] != "json":
            continue
        jsonfile_path = os.path.join(jsondir, jsonfile)
        print(f"running {jsonfile_path}...")
        create_logdir(jsonfile_path)
        os.system(f"rt-app {jsonfile_path}")
        
        exit()

    sch = schedulable.missoccur(logparser.parse_currentlogs())
    print(sch)
    is_schedulable = schedulable.schedulable(sch)
    exit()

# outputstyle:
# {'thr0-1': True, 'thr1-0': True, 'thr2-2': False, 'thr3-3': False, 'thr0-0': True, 'thr1-1': True}