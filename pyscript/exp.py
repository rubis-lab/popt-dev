import os
from datetime import datetime
from time import time
import math
import logparser
import schedulable
import json
import shutil

jsondir = '/home/rtss/json'

final_logfile = "/home/rtss/final.log"


def create_logdir(jsonfile):
    with open(jsonfile, "r") as f:
        j = json.loads(f.read())

    logdir = j["global"]["logdir"]
    if not os.path.exists(logdir):
        os.makedirs(logdir)
    
    return logdir

def delete_logdir(logdir):
    shutil.rmtree(logdir)
    return

if __name__=="__main__":
    
    jsonfiles = os.listdir(jsondir)

    num = 0
    for jsonfile in jsonfiles:
        if jsonfile.split(".")[-1] != "json":
            continue
        jsonfile_path = os.path.join(jsondir, jsonfile)
        # print(f"running {jsonfile_path}...")
        logdir = create_logdir(jsonfile_path)
        os.system(f"rt-app {jsonfile_path}")
        
        logdatas = logparser.parse_currentlogs(logdir)
        # print(f"logdatas: {logdatas}")

        exp_name = jsonfile.split(".")[0]
        linenum, deadlinemiss = schedulable.misscount(logdatas)
        
        res_str = f"{exp_name}\t{linenum}\t{deadlinemiss}\n"
        delete_logdir(logdir)

        print(res_str)
        with open(final_logfile, "a") as logfile:
            logfile.write(res_str)
        num += 1 
        
        if num >= 1:
            break


    # sch = schedulable.missoccur(logparser.parse_currentlogs())
    # print(sch)
    # is_schedulable = schedulable.schedulable(sch)
    # exit()

# outputstyle:
# {'thr0-1': True, 'thr1-0': True, 'thr2-2': False, 'thr3-3': False, 'thr0-0': True, 'thr1-1': True}