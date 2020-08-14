#include "bcl.hpp"

namespace rts{
    double BCL::calc_interference(Task _base_task, Task _inter_task){
        TSUtil tsutil;
        double i_sum = tsutil.workload_in_interval_edf(_inter_task, _base_task.deadline);
        i_sum = std::max(0.0, std::min(i_sum, 
            _base_task.deadline - _base_task.exec_time + 1.0));
        return i_sum;
    }

    double BCL::sum_interference(TaskSet _ts, Task _base_task, int _num_core){
        double sum_j = 0.0;
        for(Task inter_task : _ts.tasks){
            if (inter_task != _base_task){
                sum_j += calc_interference(_base_task, inter_task);
            }
        }
        return floor(sum_j/_num_core);
    }

    bool BCL::is_schedulable(TaskSet _ts, int _num_cores){
        for(Task base_task: _ts.tasks){
            double interference = sum_interference(_ts, base_task, _num_cores);
            if (interference > (base_task.deadline - base_task.exec_time) + 0.1){
                return false;
            }
        }
        return true;
    }
}