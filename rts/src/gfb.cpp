#include "gfb.hpp"

namespace rts{
GFB::GFB(): num_cores(4){

}

bool GFB::is_schedulable(TaskSet _task_set){
    TSUtil tsutil;
    double max_density = tsutil.max_density(_task_set);
    double tot_density = tsutil.sum_utilization(_task_set);
    return tot_density <= (num_cores*(1-max_density) + max_density);
}

bool GFB::is_schedulable(Pts _para_tasks){
    TaskSet temp;
    temp.tasks.assign(_para_tasks.pts_serialized.begin(), _para_tasks.pts_serialized.end());
    is_schedulable(temp);
    return false;
}

}  // namespace rts