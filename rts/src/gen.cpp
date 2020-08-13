#include "gen.hpp"


GEN::get_random_number(double min, double max) {
    std::random_device rn;
    std::mt19937_64 rnd(rn());
    std::uniform_real_distribution<double> range(min, max);
    return range(rnd);   
}

GEN::GEN() {
    return;
}

GEN::GEN(int _num_task, double _min_exec_time, double _max_exec_time,
        double _min_deadline, double _max_deadline, double _min_period, double _max_period,
        int _implicit_deadline, int _constrained_deadline) {

    num_task = num_task;
    min_exec_time = _min_exec_time;
    max_exec_time = _max_exec_time;
    min_deadline = _min_deadline;
    max_deadline = _max_deadline;
    min_period = _min_period;
    max_period = _max_period;
    implicit_deadline = _implicit_deadline;
    constrained_deadline = _constrained_deadline;
    
    return;
}

std::string GEN::to_str() {
    std::string info;
    info += "min_exec_time = " + std::to_string(min_exec_time) + "\n";
    info += "max_exec_time = " + std::to_string(max_exec_time) + "\n";
    info += "min_deadline = " + std::to_string(min_deadline) + "\n";
    info += "max_deadline = " + std::to_string(max_deadline) + "\n";
    info += "min_period = " + std::to_string(min_period) + "\n";
    info += "max_period = " + std::to_string(max_period) + "\n";
    info += "implicit_deadline = " + std::to_string(implicit_deadline) + "\n";
    info += "constrained_deadline = " + std::to_string(constrained_deadline) + "\n";
    
    return info
}

Task next_task() {
    std::map<std::string, double> tattr;
    Task t;
    tattr["deadline"] = get_random_number(min_deadline, max_deadline);
    tattr["period"] = get_random_number(min_period, max_period);
    tattr["exec_time"] = get_random_number(min_exec_time, max_exec_time);

    t = Task(tattr);
    return t;
}

Task next_task_set() {
    TaskSet ts;
    for(int i = 0; i < num_task; i++) {
        t = next_task();
        ts.append(t);
    }
    return ts;
}
