#include "gfb.hpp"

namespace rts{
GFB::GFB(): num_cores(4){

}

bool GFB::is_schedulable(TaskSet _ts){
    double max_density = tsutil.max_density(_ts);
    double tot_density = tsutil.sum_utilization(_ts);
    double rhs = num_cores * (1 - max_density) + max_density;
    return tot_density <= rhs;
}

bool GFB::is_schedulable(Pt _para_task, std::vector<int> popt_list){
    TaskSet ts;
    for(size_t i(0); i < popt_list.size(); i ++){
        std::vector<Thread> temp = _para_task.tsdict.at(popt_list.at(i));
        ts.tasks.insert(ts.tasks.end(), temp.begin(), temp.end());
    }
    return is_schedulable(ts);
}

}  // namespace rts