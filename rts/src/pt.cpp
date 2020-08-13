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


void Pt::to_str(){
    std::cout << id << "\n";
    base_task.to_str(); 
}
}  // namespace rts
