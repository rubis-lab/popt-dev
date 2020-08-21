#include "core/pt.hpp"

namespace rts {
int Pt::_pt_cnt = 1;

Pt::Pt() {
    selected_opt = 1;
    return;
}

Pt::Pt(int _max_opt, Task _base_task) {
    selected_opt = 1;
    max_opt = _max_opt;
    base_task = _base_task;
    populate_ts_dict();
    return;
}

Pt::Pt(int _max_opt, Task _base_task, std::unordered_map<int, std::vector<double>> _exec_times_table, int _selected_opt) {
    max_opt = _max_opt;
    base_task = _base_task;
    selected_opt = _selected_opt;
    populate_ts_dict_custom(_exec_times_table);
    return;
}

Pt::~Pt(){
    _pt_cnt--;
}

void Pt::populate_ts_dict() {
    // ts_dict holds a map of vector of threads
    // vector is initialized by parallelizing the task according to the popt
    for(unsigned int i = 1; i <= (unsigned int) max_opt; i++) {
        std::vector<Thread> thrs_opt_i;
        //TODO: assigning meaningfull exec_time
        double exec_time_split_evenly = base_task.exec_time / i;
        for(unsigned int j = 0; j < i; j++) {
            Thread thr(j);
            thr.exec_time = exec_time_split_evenly;
            thr.deadline = base_task.deadline;
            thr.period = base_task.period;
            thr.id = base_task.id;
            thrs_opt_i.push_back(thr);
        }
        tsdict.insert(std::pair<unsigned int, std::vector<Thread>>(i, thrs_opt_i));
    }
    return;
}

void Pt::populate_ts_dict_custom(std::unordered_map<int, std::vector<double>> _exec_times_table) {
    for(unsigned int i = 1; i <= (unsigned int) max_opt; i++) {
        std::vector<Thread> thrs_opt_i;
        std::vector<double> exec_times = _exec_times_table[(int)i];
        for(unsigned int j = 0; j < i; j++) {
            Thread thr(j);
            thr.exec_time = exec_times[j];
            thr.deadline = base_task.deadline;
            thr.period = base_task.period;
            thr.id = base_task.id;
            thrs_opt_i.push_back(thr);
        }
        tsdict.insert(std::pair<unsigned int, std::vector<Thread>>(i, thrs_opt_i));
    }
    return;
}


std::string Pt::to_str() {
    std::string ret = "selected option: " + std::to_string(selected_opt) + "\n";
    ret += "base task:\n" + base_task.to_str() + "\n";
    std::vector<Thread> thrs = tsdict[selected_opt];
    for(unsigned int i = 0; i < thrs.size(); i++) {
        ret += thrs[i].to_str() + "\n";
    }
    return ret;
}

}  // namespace rts
