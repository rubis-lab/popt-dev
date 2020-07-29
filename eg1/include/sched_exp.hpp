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
    std::vector<std::vector<std::thread>> tasks;
    thr_arg parse_config(std::string fname);
public:
    SchedExp(std::string fname);
    bool run();
};
#endif
