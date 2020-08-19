#ifndef __TSUTIL_H__
#define __TSUTIL_H__

#include "core/task.hpp"
#include "core/task_set.hpp"
#include <math.h>

namespace rts {

class TSUtil {
public:    
    double calc_utilization(Task _t);
    double sum_utilization(TaskSet _ts);
    double calc_density(Task _t);
    double sum_density(TaskSet _ts);
    double max_utilization(TaskSet _ts);
    double max_density(TaskSet _ts);
    double workload_in_interval_edf(Task _t, double _interval);
};

} // namespace rts
#endif // __TSUTIL_H__