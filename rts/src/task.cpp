#include "task.hpp"

namespace rts {
int Task::_count = 0;
Task::Task() {
    spdlog::info("spdlog info test");
    spdlog::warn("spdlog warn test");
    id = _count++;
    return;
}

Task::Task(std::map<std::string, double> _tattr) {
    spdlog::info("spdlog info test");
    id = _count++;
    exec_time = _tattr["exec_time"];
    deadline = _tattr["deadline"];
    period = _tattr["period"];
    return;
}

std::string Task::to_str() {
    std::string t;
    t += std::to_string(id);
    t += "\t";
    t += std::to_string(exec_time);
    t += "\t";
    t += std::to_string(deadline);
    t += "\t";
    t += std::to_string(period);
    return t;
}
}  // namespace rts
