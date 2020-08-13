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
}  // namespace rts