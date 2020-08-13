#include "tsutil.hpp"

namespace rts{

    double calc_utilization(Task _t){
        return _t.exec_time/_t.period;
    }

    double sum_utilization(TaskSet _ts){
        double sum = 0.0;
        for(Task t : _ts.tasks){
            sum += calc_utilization(t);
        }
        return sum;
    }

    double calc_density(Task _t){
        return _t.exec_time/_t.deadline;
    }

    double sum_density(TaskSet _ts){
        double sum = 0.0;
        for(Task t : _ts.tasks){
            sum += calc_density(t);
        }
        return sum;
    }

    double max_utilization(TaskSet _ts){
        double max = 0.0;
        for(Task t : _ts.tasks){
            double temp = calc_utilization(t);
            if(temp > max){
                max = temp;
            }
        }
        return max;
    }

    double max_density(TaskSet _ts){
        double max = 0.0;
        for(Task t : _ts.tasks){
            double temp = calc_density(t);
            if(temp > max){
                max = temp;
            }
        }
        return max;
    }
}