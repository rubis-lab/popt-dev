#ifndef __GFB_H__
#define __GFB_H__

#include "task_set.hpp"
#include "pts.hpp"
#include "tsutil.hpp"
#include <nlohmann/json.hpp>

namespace rts {

class GFB {
public:
    int num_core;
    TSUtil tsutil;
    GFB();
    GFB(nlohmann::json _js);
    std::string to_str();
    bool is_schedulable(TaskSet _task_set);
    bool is_schedulable(Pts _para_tasks);
};

} // namespace rts
#endif // __PTS_H__
