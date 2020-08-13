#include "gfb.hpp"

namespace rts{
Gfb::Gfb(): num_cores(4){

}

bool Gfb::is_schedulable(TaskSet _task_set){
    TSUtil tsutil;
    double max_density = tsutil.max_density(_task_set);
    double tot_density = tsutil.sum_utilization(_task_set);
    return tot_density <= (num_cores*(1-max_density) + max_density);
}

bool Gfb::is_schedulable(Pt _para_task, std::vector<int> popt_list){
    TaskSet ts;
    for(size_t i(0); i < popt_list.size(); i ++){
        std::vector<Thread> temp = _para_task.tsdict.at(popt_list.at(i));
        ts.tasks.insert(ts.tasks.end(), temp.begin(), temp.end());
    }
    is_schedulable(ts);
}

}  // namespace rts