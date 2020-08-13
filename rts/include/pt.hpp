#ifndef __PT_H__
#define __PT_H__

#include "task_set.hpp"
#include "thread.hpp"
#include <map>
#include <vector>

namespace rts {

class Pt {
public:
    int id;
    std::map<int, std::vector<Thread>> tsdict;
    static int _pt_cnt;
    Task base_task;
    Pt();
    Pt(Task _base_task);
    ~Pt();
    //void parse_pt_config(std::string fname);
    void populate_ts_table();
    void populate_ts_table_custom(std::vector<std::vector<int>>);
    std::string to_str();
};

}  // namespace rts
#endif  // __PT_H__
