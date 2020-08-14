#include "gen.hpp"
namespace rts {

Gen::Gen() {
    return;
}

Gen::Gen(gen_attr gattr) {
    _gattr = gattr;
    std::srand(_gattr.seed);
    return;
}

std::string Gen::to_str() {
    std::string ret;
    ret += "num_task = " + std::to_string(_gattr.num_task) + "\n";
    ret += "seed = " + std::to_string(_gattr.seed) + "\n";
    ret += "min_exec_time = " + std::to_string(_gattr.min_exec_time) + "\n";
    ret += "max_exec_time = " + std::to_string(_gattr.max_exec_time) + "\n";
    ret += "min_deadline = " + std::to_string(_gattr.min_deadline) + "\n";
    ret += "max_deadline = " + std::to_string(_gattr.max_deadline) + "\n";
    ret += "min_period = " + std::to_string(_gattr.min_period) + "\n";
    ret += "max_period = " + std::to_string(_gattr.max_period) + "\n";
    ret += "implicit_deadline = " + std::to_string(_gattr.implicit_deadline) + "\n";
    ret += "constrained_deadline = " + std::to_string(_gattr.constrained_deadline) + "\n";
    
    return ret;
}

double Gen::frand(double _min, double _max) {
    // std::random_device rn;
    // std::mt19937_64 rnd(rn());
    // std::uniform_real_distribution<double> range(min, max);
    // return range(rnd);
    double f = (double)std::rand() / RAND_MAX;
    return _min + f * (_max - _min);
    
}

Task Gen::next_task() {
    std::map<std::string, double> tattr;
    tattr["deadline"] = frand(_gattr.min_deadline, _gattr.max_deadline);
    tattr["period"] = frand(_gattr.min_period, _gattr.max_period);
    tattr["exec_time"] = frand(_gattr.min_exec_time, _gattr.max_exec_time);
    return Task(tattr);
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
