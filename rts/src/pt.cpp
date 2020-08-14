#include "pt.hpp"

namespace rts {
int Pt::_pt_cnt = 1;

Pt::Pt(): max_opt(4) {
    return;
}
Pt::Pt(Task _base_task) {
    base_task = _base_task;
}

Pt::~Pt(){
    _pt_cnt--;
}

void Pt::populate_ts_dict(){
    for(size_t i(1); i <= (size_t) max_opt; i++){
        std::vector<Thread> temp;
        //TODO: assigning meaningfull exec_time
        int tmp_exec_time = (base_task.exec_time / i);
        for(size_t j(0); j < i; j++){
            Thread temp_thr(j);
            temp_thr.exec_time = tmp_exec_time;
            temp_thr.deadline = base_task.deadline;
            temp_thr.period = base_task.period;
            temp_thr.id = base_task.id;
            temp.push_back(temp_thr);
        }
        tsdict.insert(std::pair<int, std::vector<Thread>>(i, temp));
    }
}


std::string Pt::to_str(){
    return std::to_string(id) + "\t" + base_task.to_str();
}

}  // namespace rts
