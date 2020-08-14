#ifndef __BCL_H__
#define __BCL_H__

#include "tsutil.hpp"

namespace rts{
class BCL{
    double calc_interference(Task _base_task, Task _inter_task);
    double sum_interference(TaskSet _ts, Task _base_task, int _num_core);
    bool is_schedulable(TaskSet _ts, int _num_cores);
};

}  // namespace rts
#endif  // __BCL_H__