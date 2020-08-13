#ifndef __GEN_H__
#define __GEN_H__

#include "task_set.hpp"
#include <cstdlib>
#include <random>

namespace rts {

struct gen_attr {
    int num_task;
    double min_exec_time;
    double max_exec_time;
    double min_deadline;
    double max_deadline;
    double min_period;
    double max_period;
    int implicit_deadline;      //0: False, 1: True
    int constrained_deadline;   //0: False, 1: True
};

class Gen {
public:
    

    gen_attr _gattr;
    Gen();
    Gen(gen_attr gattr);
    std::string to_str();
    Task next_task();
    TaskSet next_task_set();
    double get_random_number(double min, double max);
};

}  // namespace rts
#endif  // __GEN_H__
