#ifndef __GEN_H__
#define __GEN_H__

#include "task.hpp"
#include "task_set.hpp"
#include <cstdlib>
#include <unordered_map>
#include <cmath>
#include <ctime>
#include <string>
#include <nlohmann/json.hpp>

namespace rts {

class Gen {
public:
    int num_task;
    unsigned int seed;
    double min_exec_time;
    double max_exec_time;
    double min_deadline;
    double max_deadline;
    double min_period;
    double max_period;
    int implicit_deadline;      //0: False, 1: True
    int constrained_deadline;   //0: False, 1: True
    Gen();
    Gen(nlohmann::json _js);
    std::string to_str();
    Task next_task();
    TaskSet next_task_set();
    double frand(double _min, double _max);
};

}  // namespace rts
#endif  // __GEN_H__
