#include "task.hpp"

namespace rts {
int Task::_count = 0;
Task::Task() {
    id = _count++;
    return;
}

Task::Task(std::map<std::string, double> _tattr) {
    id = _count++;
    exec_time = _tattr["exec_time"];
    deadline = _tattr["deadline"];
    period = _tattr["period"];
    return;
}

std::string Task::to_str() {
    std::string ret;
    ret += std::to_string(id);
    ret += "\t";
    ret += std::to_string(exec_time);
    ret += "\t";
    ret += std::to_string(deadline);
    ret += "\t";
    ret += std::to_string(period);
    return ret;
}
}  // namespace rts
