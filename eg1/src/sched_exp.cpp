#include "sched_exp.hpp"

using namespace std;
using json = nlohmann::json;

SchedExp::SchedExp(string fname, int popt) {
    fileName = fname;
    this->popt = popt;
}

void SchedExp::parse_config(string fname) {
    ifstream inputFile(fname);
    json json;
    inputFile >> json;
    exp_name = json["exp_name"];
    num_task = json["task_set"].size();
    
    cout << "num_task: " << num_task << endl;

    for(int i(0); i < num_task; i++){
        struct task_arg temp;
        temp.option = popt;
        temp.task_id = i;
        temp.parent = gettid();
        temp.deadline = json["task_set"][i]["deadline"];
        temp.period = json["task_set"][i]["period"];
        vector<thr_arg> thread_args;
        for(int j(0); j < popt; j ++){
            struct thr_arg temp;
            temp.exec_time = json["task_set"][i]["options"][popt-1]["runtimes"][j];
            cout << temp.exec_time << endl;
            temp.thr_id = j;
            thread_args.push_back(temp);
        }
        temp.thr_set = thread_args;
        task_set.push_back(temp);
    }
    // for(int k(0); k < task_args.size(); k ++){
    //     struct task_arg m = task_args.at(k);
    //     cout << "hi" << endl;
    //     cout << m.option << m.deadline << m.period << endl;
    //     cout << "runtime " << m.thr_set.at(0).exec_time << endl;
    // }
}

bool SchedExp::run() {
    // 1. Parse
    parse_config(fileName);
    cout << exp_name << endl;
    // 2. Thread
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