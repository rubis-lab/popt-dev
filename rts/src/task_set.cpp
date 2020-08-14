#include "task_set.hpp"

namespace rts {

TaskSet::TaskSet() {

}

std::string TaskSet::to_str() {
    std::string ret;
    for(unsigned int i = 0; i < tasks.size(); i++) {
        ret += tasks[i].to_str() + '\n';
    }
    return ret;
}

void TaskSet::append(Task _task) {
    tasks.push_back(_task);
    return;
}
}  // namespace rts