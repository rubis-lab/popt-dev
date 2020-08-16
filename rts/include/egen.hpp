#ifndef __EGEN_H__
#define __EGEN_H__

#include "gen.hpp"
#include "tsutil.hpp"
#include <nlohmann/json.hpp>
#include "spdlog/spdlog.h"

namespace rts {
class Egen : public Gen::Gen {
public:
    int utilization_overflow;  // 1: True 0: False
    int last_id;
    double necessary_bound;
    TSUtil tsu;
    TaskSet ts;
    Egen();
    Egen(nlohmann::json _js);
    std::string to_str();
    Task next_task();
    TaskSet next_task_set();
    TaskSet create_new_task_set(Task _t);
};

}  // namespace rts
#endif  // __EGEN_H__