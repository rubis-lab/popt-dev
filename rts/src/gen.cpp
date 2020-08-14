#include "gen.hpp"
namespace rts {

Gen::Gen() {
    return;
}


Gen::Gen(nlohmann::json _js) {
    num_task = _js["num_task"];
    seed = _js["seed"];
    min_exec_time = _js["min_exec_time"];
    max_exec_time = _js["max_exec_time"];
    min_deadline = _js["min_deadline"];
    max_deadline = _js["max_deadline"];
    min_period = _js["min_period"];
    max_period = _js["max_period"];
    implicit_deadline = _js["implicit_deadline"];
    constrained_deadline = _js["constrained_deadline"];
    if(seed == 0) {
        seed = time(NULL);
    }
    std::srand(seed);
} 

std::string Gen::to_str() {
    std::string ret;
    ret += "num_task = " + std::to_string(num_task) + "\n";
    ret += "seed = " + std::to_string(seed) + "\n";
    ret += "min_exec_time = " + std::to_string(min_exec_time) + "\n";
    ret += "max_exec_time = " + std::to_string(max_exec_time) + "\n";
    ret += "min_deadline = " + std::to_string(min_deadline) + "\n";
    ret += "max_deadline = " + std::to_string(max_deadline) + "\n";
    ret += "min_period = " + std::to_string(min_period) + "\n";
    ret += "max_period = " + std::to_string(max_period) + "\n";
    ret += "implicit_deadline = " + std::to_string(implicit_deadline) + "\n";
    ret += "constrained_deadline = " + std::to_string(constrained_deadline) + "\n";
    
    return ret;
}

Task Gen::next_task() {
    std::map<std::string, double> tattr;
    tattr["deadline"] = frand(min_deadline, max_deadline);
    tattr["period"] = frand(min_period, max_period);
    tattr["exec_time"] = frand(min_exec_time, max_exec_time);
    return Task(tattr);
}

TaskSet Gen::next_task_set() {
    TaskSet ts;
    for(int i = 0; i < num_task; i++) {
        Task t = next_task();
        ts.append(t);
    }
    return ts;
}

double Gen::frand(double _min, double _max) {
    // std::random_device rn;
    // std::mt19937_64 rnd(rn());
    // std::uniform_real_distribution<double> range(min, max);
    // return range(rnd);
    double f = (double)std::rand() / RAND_MAX;
    return std::round(_min + f * (_max - _min));   
}

}  // namespace rts
