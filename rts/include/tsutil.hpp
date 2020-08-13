#ifndef __TSUTIL_H__
#define __TSUTIL_H__

#include "task.hpp"
#include "task_set.hpp"

namespace rts {

class TSUtil{
public:    
    double calc_utilization(Task _t);
    double sum_utilization(TaskSet _ts);
    double calc_density(Task _t);
    double sum_density(TaskSet _ts);
    double max_utilization(TaskSet _ts);
    double max_density(TaskSet _ts);
    //TODO ~ workload funcs
};

} // namespace rts
#endif // __TSUTIL_H__