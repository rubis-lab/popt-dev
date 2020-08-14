#include "egen.hpp"

namespace rts {
Egen::Egen(): Gen(), tot_util(4.0), last_id(1), 
    utilization_overflow(0) {
    
}
Egen::Egen(nlohmann::json _js): Gen(_js), tot_util(4.0), 
    last_id(1), utilization_overflow(0) {

}
Task Egen::next_task(){
    std::map<std::string, double> tattr;
    tattr["deadline"] = frand(min_deadline, max_deadline);
    tattr["period"] = frand(min_period, max_period);
    tattr["exec_time"] = frand(min_exec_time, max_exec_time);
    
    if (utilization_overflow==0) {
        while (tattr["exec_time"] > tattr["period"] + 0.1) {
            tattr["period"] = frand(min_period, max_period);
            tattr["exec_time"] = frand(min_exec_time, max_exec_time);
        }
    }

    return Task(tattr);
}
TaskSet Egen::next_task_set(){
    Task t = next_task();
    TSUtil tsu;
    if(tsu.sum_utilization(_ts) + 
        tsu.calc_utilization(t) >= tot_util){
            return create_new_task_set(t);
        }
    t.id = last_id++;
    _ts.tasks.push_back(t);
    return _ts;
}
TaskSet Egen::create_new_task_set(Task _t){
    _ts.tasks.clear();
    TSUtil tsu;
    if(tsu.calc_utilization(_t) <= tot_util){
        last_id = 0;
        _t.id = 0;
        _ts.tasks.push_back(_t);
        return _ts;
    } else {
        std::cout << "Cannot create new task set, tried utilization: " <<
            tsu.calc_utilization(_t) << std::endl;
    }
}
std::string Egen::to_str(){
    std::string info;
    info += Gen::to_str();
    info += '\n' + "tot_util = " + std::to_string(tot_util);
    info += '\n' + "util_over = " + std::to_string(utilization_overflow);
    return info;
}

}  // namespace rts