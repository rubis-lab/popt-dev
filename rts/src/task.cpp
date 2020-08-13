#include "task.hpp"

namespace rts {

Task::Task() {
    return;
}

Task::Task(std::map<std::string, double> _tattr) {
    exec_time = _tattr["exec_time"];
    deadline = _tattr["deadline"];
    period = _tattr["period"];
    return;
}

void Task::to_str() {
    if(id == -1) {
        std::cout << "task does not exist; create task_set object first or initialize the attributes" << std::endl;
    } else {
        std::cout << id << "\t" << exec_time << "\t" << deadline << "\t" << period << std::endl;
    }
    return;
}
}  // namespace rts
