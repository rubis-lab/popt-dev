#include "egen.hpp"

namespace rts {
Egen::Egen(): Gen() {

}

Egen::Egen(nlohmann::json _js): Gen(_js) {
    necessary_bound = (double) _js["num_core"];
    last_id = 0;
    utilization_overflow = 0;
}

Task Egen::next_task() {
    std::unordered_map<std::string, double> tattr;
    tattr["deadline"] = frand(min_deadline, max_deadline);
    tattr["period"] = frand(min_period, max_period);
    tattr["exec_time"] = frand(min_exec_time, max_exec_time);
    std::cout << "param generated" << std::endl;
    // retry until exec_time > period (utilization > 1)
    if (utilization_overflow == 0) {
        while (tattr["exec_time"] > tattr["period"] + 0.1) {
            tattr["period"] = frand(min_period, max_period);
            tattr["exec_time"] = frand(min_exec_time, max_exec_time);
        }
    }
    std::cout << "utilization chedked" << std::endl;
    return Task(tattr);
}

TaskSet Egen::next_task_set() {
    Task t = next_task();

    // clear and gen new task, upon tot_util exceeding nec. bound
    if(tsu.sum_utilization(ts) + tsu.calc_utilization(t) >= necessary_bound) {
        return create_new_task_set(t);
    }

    // to maintain continuous id
    t.id = last_id++;

    ts.tasks.push_back(t);
    return ts;
}

TaskSet Egen::create_new_task_set(Task _t) {
    std::cout << "creating new task set" << std::endl;
    ts.tasks.clear();

    // new task (just one) may exceed nec bound.
    if(tsu.calc_utilization(_t) <= necessary_bound) {
        last_id = 0;
        _t.id = 0;
        ts.tasks.push_back(_t);
        std::cout << "ts created. " << ts.to_str() << std::endl;
        return ts;
    } else {
        spdlog::error("Cannot create new task set, tried utilization: {}", tsu.calc_utilization(_t));
        return ts;  // todo: exit here, or try/catch
    }
}

std::string Egen::to_str() {
    std::string info;
    info += Gen::to_str();
    info += "\nnecessary_bound = " + std::to_string(necessary_bound);
    info += "\nutil_over = " + std::to_string(utilization_overflow);
    return info;
}

}  // namespace rts
