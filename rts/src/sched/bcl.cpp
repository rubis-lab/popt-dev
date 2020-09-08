#include "sched/bcl.hpp"
namespace rts {

BCL::BCL() {
    return;
}

BCL::BCL(nlohmann::json _js) {
    num_core = _js["num_core"];
    return;
}

std::string BCL::to_str() {
    std::string ret;
    ret += "BCL: num_core = " + std::to_string(num_core) + "\n";
    return ret;
}

double BCL::calc_interference(Task _base_task, Task _inter_task) {
    TSUtil tsutil;
    double i_sum = tsutil.workload_in_interval_edf(_inter_task, _base_task.deadline);
    i_sum = std::max(0.0, std::min(i_sum, 
        _base_task.deadline - _base_task.exec_time + 1.0));
    return i_sum;
}


double BCL::sum_interference(TaskSet _ts, Task _base_task) {
    double sum_j = 0.0;
    for(Task inter_task : _ts.tasks){
        if (inter_task != _base_task){
            sum_j += calc_interference(_base_task, inter_task);
        }
    }
    return floor(sum_j / num_core);
}

bool BCL::is_schedulable(TaskSet _ts) {
    for(Task base_task: _ts.tasks){
        double interference = sum_interference(_ts, base_task);
        if (interference > (base_task.deadline - base_task.exec_time) + 0.1){
            return false;
        }
    }
    return true;
}

 
//slack
double BCL::calc_interference_slack(Task _base_task, Task _inter_task) {
    TSUtil tsutil;
    double i_sum = tsutil.workload_in_interval_edf_slack(_inter_task, _base_task.deadline);
    i_sum = std::max(0.0, std::min(i_sum, 
        _base_task.deadline - _base_task.exec_time + 1.0));
    return i_sum;
}

double BCL::sum_interference_slack(TaskSet _ts, Task _base_task) {
    double sum_j = 0.0;
    for(Task inter_task : _ts.tasks){
        if (inter_task != _base_task){
            sum_j += calc_interference_slack(_base_task, inter_task);
        }
    }
    return floor(sum_j / num_core);
}

bool BCL::is_schedulable_slack(TaskSet _ts) {
    bool slack_updated = true;
    bool potentially_not_schedulable = true;
    double slack;
    while(slack_updated) {
        slack_updated = false;
        for(Task base_task: _ts.tasks) {
            double interference = sum_interference_slack(_ts, base_task);
            slack = (base_task.deadline - base_task.exec_time) + 0.1 - interference;
            if(slack > base_task.slack) {
                base_task.slack = slack;
                slack_updated = true;
            } else if(slack < 0) {
                potentially_not_schedulable = true;
            }
        }
        if(!potentially_not_schedulable)
            return true;
    }
    return false;
}

}  // namespace rts