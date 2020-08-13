#include "pts.hpp"

namespace rts{


Pts::Pts() {
}

Pts::~Pts(){
    pts_cnt--;
}

void Pts::populate_pt_list(){
    for(Task t: base_task_set.get_task_list()){
        Pt p_t(max_opt, overhead, variance);
        p_t.set_base_task(base_task);
        pt_list.push_back(p_t);
    }
}

void Pts::to_str(){
    for(size_t i(0); i < pts_serialized.size(); i++){
        pts_serialized.at(i).to_str();
    }    
}



} // namespace rts