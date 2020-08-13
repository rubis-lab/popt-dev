#include "pts.hpp"

namespace rts{
int Pts::_pts_cnt = 0;

Pts::Pts() {
    id = _pts_cnt++;
}

Pts::~Pts(){
    _pts_cnt--;
}

void Pts::populate_pt_list()
{
    for(Task t: base_ts.tasks){
        Pt temp(t);
        pt_list.push_back(temp);
    }
}

std::string Pts::to_str(){
    std::string t;
    for(size_t i(0); i < pts_serialized.size(); i++){
        t += pts_serialized.at(i).to_str();
    }    
    return t;
}



} // namespace rts