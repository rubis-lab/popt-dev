#include "task_set.hpp"

namespace rts {

TaskSet::TaskSet() {
}

void TaskSet::to_str() {
    if(tasks.size() == 0){
        std::cout << "TaskSet attributes not yet initialized" << std::endl;
    } else {
        // cout << "Task Set Length: " << _tasks.size() << 
        //     " Total Utilization: " << sum_task_util() << endl;
        for(size_t i(0); i < tasks.size(); i++){
            tasks.at(i).to_str();
        }
    }
}
}  // namespace rts
