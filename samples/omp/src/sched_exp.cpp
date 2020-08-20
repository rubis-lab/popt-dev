#include "sched_exp.hpp"
#include "dummy_workload.hpp"
#include <omp.h>

SchedExp::SchedExp(std::string _exp_cfg_file, std::string _ts_cfg_file) {
    // parse_config(fileName);
    return;
}

void SchedExp::parse_config(std::string exp_cfg_file) {
    std::ifstream inputFile(exp_cfg_file);
    nlohmann::json jf;
    inputFile >> jf;
    exp_name = jf["exp_name"];
    num_task = jf["task_set"].size();
    

    for(int i(0); i < num_task; i++) {
        // Initialize task-specific arguments
        struct task_arg temp;
        temp.option = popt_vec.at(i);
        temp.task_id = i;
        temp.parent = gettid();
        temp.deadline = jf["task_set"][i]["deadline"];
        temp.period = jf["task_set"][i]["period"];
        // Initialize thread-specific arguments
        std::vector<thr_arg> thread_args;
        for(int j(0); j < popt_vec.at(i); j ++){
            struct thr_arg temp;
            temp.exec_time = jf["task_set"][i]["options"][popt_vec.at(i)-1]["runtimes"][j];
            temp.thr_id = j;
            thread_args.push_back(temp);
        }
        temp.thr_set = thread_args;
        
        task_set.push_back(temp);
    }
}

bool SchedExp::run() {
    // 1. Print exp_name
    std::cout << exp_name << std::endl;
    // 2. Create Thread
    int numTask = task_set.size(); 
    std::vector<std::thread> thrs;
    for(int i(0); i < numTask; i ++){
        thrs.push_back(std::thread(work, 100, popt_vec.at(i)));
    }
    // 3. Release
    for(std::thread &t : thrs){
        t.join();
    }
    return true;
}