#include "sched/gfb.hpp"

namespace rts{
GFB::GFB() {
    return;
}

GFB::GFB(nlohmann::json _js) {
    num_core = _js["num_core"];
    return;
}

std::string GFB::to_str() {
    std::string ret;
    ret += "GFB: num_core = " + std::to_string(num_core) + "\n";
    return ret;
}

bool GFB::is_schedulable(TaskSet _ts){
    double max_density = tsutil.max_density(_ts);
    double tot_density = tsutil.sum_density(_ts);
    double rhs = num_core * (1 - max_density) + max_density;
    return tot_density <= rhs;
}

bool GFB::is_schedulable(Pts _para_tasks){
    TaskSet temp;
    temp.tasks.assign(_para_tasks.pts_serialized.begin(), _para_tasks.pts_serialized.end());
    is_schedulable(temp);
    return false;
}

}  // namespace rts