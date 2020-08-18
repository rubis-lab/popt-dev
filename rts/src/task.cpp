#include "task.hpp"

namespace rts {
int Task::_count = 0;
Task::Task() {
    id = _count++;
    return;
}

Task::Task(std::unordered_map<std::string, double> _tattr) {
    id = _count++;
    std::cout << "hi" << std::endl;
    exec_time = _tattr["exec_time"];
    std::cout << "exec_time: " << exec_time << std::endl;
    deadline = _tattr["deadline"];
    std::cout << "deadline: " << deadline << std::endl;
    period = _tattr["period"];
    std::cout << "period: " << period << std::endl;
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

bool Task::operator==(const Task& other){
    if(id == other.id && exec_time == other.exec_time &&
        deadline == other.deadline && period == other.period){
            return true;
        } else {
            return false;
        }
}

bool Task::operator!=(const Task& other){
    return !(*this == other);
}

}  // namespace rts
