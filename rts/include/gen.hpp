#ifndef __GEN_H__
#define __GEN_H__

#include "task_set.hpp"
#include <cstdlib>
#include <random>

namespace rts {

class Gen {
public:
    int num_task;
    double min_exec_time;
    double max_exec_time;
    double min_deadline;
    double max_deadline;
    double min_period;
    double max_period;
    int implicit_deadline;      //0: False, 1: True
    int constrained_deadline;   //0: False, 1: True

    Gen();
    Gen(int _num_task, double _min_exec_time, double _max_exec_time,
        double _min_deadline, double _max_deadline, double _min_period, double _max_period,
        int _implicit_deadline, int _constrained_deadline);
    ~Gen();
    std::string to_str();
    Task next_task();
    TaskSet next_task_set();
    int get_random_number(int min, int max);
};

}  // namespace rts
#endif  // __GEN_H__
