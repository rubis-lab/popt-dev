#ifndef __TASK_SET_H__
#define __TASK_SET_H__

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include "task.hpp"

namespace rts {
    class TaskSet {
    private:
        void parse_config(std::string fname);
        std::vector<Task> task_list;
        std::string exp_name;
        std::vector<int> popt_vec;
    public:
        TaskSet(std::string fname, std::vector<int> popt);
        int task_set_print();
        std::vector<Task> get_task_list();
    };
}

#endif