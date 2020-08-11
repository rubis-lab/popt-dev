#include "sched_exp.hpp"
#include <omp.h>
using namespace std;
using json = nlohmann::json;

SchedExp::SchedExp(string fname, vector<int> popt) {
    fileName = fname;
    popt_vec = popt;
    parse_config(fileName);
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
        temp.option = popt_vec.at(i);
        temp.task_id = i;
        temp.parent = gettid();
        temp.deadline = json["task_set"][i]["deadline"];
        temp.period = json["task_set"][i]["period"];
        // Initialize thread-specific arguments
        vector<thr_arg> thread_args;
        for(int j(0); j < popt_vec.at(i); j ++){
            struct thr_arg temp;
            temp.exec_time = json["task_set"][i]["options"][popt_vec.at(i)-1]["runtimes"][j];
            temp.thr_id = j;
            thread_args.push_back(temp);
        }
        temp.thr_set = thread_args;
        
        task_set.push_back(temp);
    }
}

bool SchedExp::run() {
    // 1. Print exp_name
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
    for(int i(0); i < numTask; i++){
        omp_set_dynamic(0);
        omp_set_num_threads(thrs.size());
        #pragma omp parallel
        for(thread &t : thrs){
            t.join();
        }
    }
    return true;
}