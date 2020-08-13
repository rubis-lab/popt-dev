#ifndef __GFB_H__
#define __GFB_H__

#include "task_set.hpp"
#include "pt.hpp"
#include "tsutil.hpp"

namespace rts{

class Gfb{
public:
    Gfb();
    int num_cores;
    bool Gfb_schedulable(TaskSet _task_set);
    bool Gfb_schedulable(Pt _para_task, std::vector<int> popt_list);
};

} // namespace rts
#endif // __PTS_H__