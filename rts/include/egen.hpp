#ifndef __EGEN_H__
#define __EGEN_H__

#include "gen.hpp"
#include "tsutil.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

namespace rts{
class Egen : public Gen::Gen{
    int utilization_overflow; // 1: True 0: False
    int last_id;
    double tot_util;
    Egen();
    Egen(nlohmann::json _js);
    std::string to_str();
    Task next_task();
    TaskSet next_task_set();
    TaskSet create_new_task_set(Task _t);
    TaskSet _ts;
};

}

#endif  // __EGEN_H__