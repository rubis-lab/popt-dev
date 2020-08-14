#ifndef __TASK_SET_H__
#define __TASK_SET_H__

#include "task.hpp"
#include <vector>
#include <string>


namespace rts {
class TaskSet {
public:
    std::vector<Task> tasks;
    TaskSet();
    std::string to_str();
    void append(Task _task);
};    

}  // namespace rts
#endif  // __TASK_SET_H__
