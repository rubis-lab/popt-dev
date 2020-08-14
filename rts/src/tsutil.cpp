#include "tsutil.hpp"

namespace rts {

double TSUtil::calc_utilization(Task _t){
    return _t.exec_time/_t.period;
}

double TSUtil::sum_utilization(TaskSet _ts){
    double sum = 0.0;
    for(Task t : _ts.tasks){
        sum += calc_utilization(t);
    }
    return sum;
}

double TSUtil::calc_density(Task _t){
    return _t.exec_time/_t.deadline;
}

double TSUtil::sum_density(TaskSet _ts){
    double sum = 0.0;
    for(Task t : _ts.tasks){
        sum += calc_density(t);
    }
    return sum;
}

double TSUtil::max_utilization(TaskSet _ts){
    double max = 0.0;
    for(Task t : _ts.tasks){
        double temp = calc_utilization(t);
        if(temp > max){
            max = temp;
        }
    }
    return max;
}

double TSUtil::max_density(TaskSet _ts){
    double max = 0.0;
    for(Task t : _ts.tasks){
        double temp = calc_density(t);
        if(temp > max){
            max = temp;
        }
    }
    return max;
}

double TSUtil::workload_in_interval_edf(Task _t, double _interval){
    int num_body_job = floor(_interval / _t.period);
    double workload_body_job = _t.exec_time * num_body_job;
    // slack = 0
    double workload_carry_in = fmod(_interval, _t.period);
    if(workload_carry_in < 0.0){
        workload_carry_in = 0.0;
    }
    workload_carry_in = std::min(_t.exec_time, workload_carry_in);
    return workload_carry_in + workload_body_job;
}

}  // namespace rts