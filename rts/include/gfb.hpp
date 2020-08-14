#ifndef __GFB_H__
#define __GFB_H__

#include "task_set.hpp"
#include "pt.hpp"
#include "tsutil.hpp"

namespace rts {

class GFB {
public:
    GFB();
    int num_cores;
    TSUtil tsutil;
    bool is_schedulable(TaskSet _task_set);
    bool is_schedulable(Pt _para_task, std::vector<int> popt_list);
};

} // namespace rts
#endif // __PTS_H__
