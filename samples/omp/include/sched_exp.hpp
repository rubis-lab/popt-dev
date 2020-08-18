#ifndef __SCHED_EXP_H__
#define __SCHED_EXP_H__

#include "sched_core.hpp"
#include "sched_deadline.hpp"
#include <nlohmann/json.hpp>
#include <thread>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

class SchedExp {
private:
    std::string exp_name;
    int num_task;
    std::string popt;
    std::vector<int> popt_vec;
    std::string fileName; 
    std::vector<std::thread> thread_set;
    std::vector<task_arg> task_set;
    void parse_config(std::string fname);
public:
    SchedExp(std::string fname, std::vector<int> popt);
    bool run();
};
#endif
