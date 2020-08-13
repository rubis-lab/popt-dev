#include "pt.hpp"

namespace rts {
int Pt::_pt_cnt = 1;

Pt::Pt() {
    return;
}
Pt::Pt(Task _base_task) {
    base_task = _base_task;
}

Pt::~Pt(){
    _pt_cnt--;
}

void Pt::populate_ts_table(){
    //TODO
}


std::string Pt::to_str(){
    return std::to_string(id) + "\t" + base_task.to_str();
}

}  // namespace rts
