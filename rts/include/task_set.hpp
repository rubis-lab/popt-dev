#ifndef __TASK_SET_H__
#define __TASK_SET_H__

#include <iostream>
#include <vector>
#include "task.hpp"

namespace rts {
class TaskSet {
public:
    std::vector<Task> tasks;
    TaskSet();
    void to_str();
    void from_json();
};    

}  // namespace rts
#endif  // __TASK_SET_H__
