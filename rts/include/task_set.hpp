#ifndef __TASK_SET_H__
#define __TASK_SET_H__

#include <iostream>
#include <vector>
#include "task.hpp"
#include "task_set.hpp"

namespace rts {
class TaskSet {
public:
    std::vector<Task> tasks;
    TaskSet();
    void append(Task _task);
    std::string to_str();
};    

}  // namespace rts
#endif  // __TASK_SET_H__
