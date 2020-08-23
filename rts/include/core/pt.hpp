#ifndef __PT_H__
#define __PT_H__

#include "core/task_set.hpp"
#include "core/task.hpp"
#include "core/thread.hpp"
#include <unordered_map>
#include <vector>


namespace rts {

class Pt {
public:
    int id;
    int max_opt;
    int selected_opt;
    std::unordered_map<int, std::vector<Thread>> tsdict;
    static int _pt_cnt;
    Task base_task;
    Pt();
    Pt(int _max_opt, Task _base_task);
    Pt(int _max_opt, Task _base_task, std::unordered_map<int, std::vector<double>> _exec_times_table, int _selected_opt);
    ~Pt();
    void populate_ts_dict();
    void populate_ts_dict_custom(std::unordered_map<int, std::vector<double>> _exec_times_table);
    std::string to_str();
};

}  // namespace rts
#endif  // __PT_H__
