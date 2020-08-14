#ifndef __BCL_H__
#define __BCL_H__

#include "tsutil.hpp"
#include <string>
#include <nlohmann/json.hpp>

namespace rts {
class BCL {
public:
    int num_core;
    BCL();
    BCL(nlohmann::json _js);
    std::string to_str();
    double calc_interference(Task _base_task, Task _inter_task);
    double sum_interference(TaskSet _ts, Task _base_task);
    bool is_schedulable(TaskSet _ts);
};

}  // namespace rts
#endif  // __BCL_H__