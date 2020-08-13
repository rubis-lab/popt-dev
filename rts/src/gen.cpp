#include "gen.hpp"
namespace rts {



Gen::Gen() {
    return;
}

Gen::Gen(gen_attr gattr) {
    _gattr = gattr;
    return;
}

std::string Gen::to_str() {
    std::string info;
    info += "min_exec_time = " + std::to_string(_gattr.min_exec_time) + "\n";
    info += "max_exec_time = " + std::to_string(_gattr.max_exec_time) + "\n";
    info += "min_deadline = " + std::to_string(_gattr.min_deadline) + "\n";
    info += "max_deadline = " + std::to_string(_gattr.max_deadline) + "\n";
    info += "min_period = " + std::to_string(_gattr.min_period) + "\n";
    info += "max_period = " + std::to_string(_gattr.max_period) + "\n";
    info += "implicit_deadline = " + std::to_string(_gattr.implicit_deadline) + "\n";
    info += "constrained_deadline = " + std::to_string(_gattr.constrained_deadline) + "\n";
    
    return info;
}

double Gen::get_random_number(double min, double max) {
    std::random_device rn;
    std::mt19937_64 rnd(rn());
    std::uniform_real_distribution<double> range(min, max);
    return range(rnd);   
}

Task Gen::next_task() {
    std::map<std::string, double> tattr;
    Task t;
    tattr["deadline"] = get_random_number(_gattr.min_deadline, _gattr.max_deadline);
    tattr["period"] = get_random_number(_gattr.min_period, _gattr.max_period);
    tattr["exec_time"] = get_random_number(_gattr.min_exec_time, _gattr.max_exec_time);

    t = Task(tattr);
    return t;
}

TaskSet Gen::next_task_set() {
    TaskSet ts;
    for(int i = 0; i < _gattr.num_task; i++) {
        Task t = next_task();
        ts.append(t);
    }
    return ts;
}

}  // namespace rts
