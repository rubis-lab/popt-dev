#ifndef __PT_H__
#define __PT_H__

#include "core/task_set.hpp"
#include "core/task.hpp"
#include "core/thread.hpp"
#include <map>
#include <vector>

namespace rts {

class Pt {
public:
    int id;
    int max_opt;
    std::map<int, std::vector<Thread>> tsdict;
    static int _pt_cnt;
    Task base_task;
    Pt();
    Pt(int _max_opt, Task _base_task);
    ~Pt();
    void populate_ts_dict();
    std::string to_str();
};

}  // namespace rts
#endif  // __PT_H__
