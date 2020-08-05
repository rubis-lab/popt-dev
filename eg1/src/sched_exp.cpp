#include "sched_exp.hpp"

using namespace std;
using json = nlohmann::json;

SchedExp::SchedExp(string fname, int popt) {
    fileName = fname;
    // Can be modified to give thread-specific parallelization options
    this->popt = popt;
}

void SchedExp::parse_config(string fname) {
    ifstream inputFile(fname);
    json json;
    inputFile >> json;
    exp_name = json["exp_name"];
    num_task = json["task_set"].size();

    for(int i(0); i < num_task; i++){
        // Initialize task-specific arguments
        struct task_arg temp;
        temp.option = popt;
        temp.task_id = i;
        temp.parent = gettid();
        temp.deadline = json["task_set"][i]["deadline"];
        temp.period = json["task_set"][i]["period"];
        // Initialize thread-specific arguments
        vector<thr_arg> thread_args;
        for(int j(0); j < popt; j ++){
            struct thr_arg temp;
            temp.exec_time = json["task_set"][i]["options"][popt-1]["runtimes"][j];
            temp.thr_id = j;
            thread_args.push_back(temp);
        }
        temp.thr_set = thread_args;
        
        task_set.push_back(temp);
    }
}

bool SchedExp::run() {
    // 1. Parse
    parse_config(fileName);
    cout << exp_name << endl;
    // 2. Create Thread
    int numTask = task_set.size(); 
    vector<thread> thrs;
    for(int i(0); i < numTask; i ++){
        int numThread = task_set.at(i).thr_set.size();
        for(int j(0); j < numThread; j++){
            thrs.push_back(thread(routine_deadline, task_set.at(i), j));
        }
    }
    // 3. Release
    for(thread &t : thrs)
        t.join();
    return true;
}