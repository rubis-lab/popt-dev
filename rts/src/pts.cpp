#include "pts.hpp"

namespace rts{
    int Pts::count = 0;
    Pts::Pts(): id(count++), max_opt(1), 
        overhead(0.0), variance(0.0)
    {
        base_task = Task(id, 0, 1, 2, 3);
        base_task_set.get_task_list().push_back(base_task);
    }

    void Pts::populate_pt_list(){
        for(Task t: base_task_set.get_task_list()){
            Pt p_t(max_opt, overhead, variance);
            p_t.set_base_task(base_task);
            pt_list.push_back(p_t);
        }
    }

    void Pts::serialize_pts(){
        //TODO
    }

    void Pts::clear(){
        if(pts_serialized.size() != 0){
            pts_serialized.clear();
        }
        if(pt_list.size() != 0){
            pt_list.clear();
        }
    }

    void Pts::set_pts_item(Thread thr, int idx){
        pts_serialized.at(idx) = thr;
    }

    Thread Pts::get_pts_item(int idx){
        return pts_serialized.at(idx);
    }

    void Pts::pts_print(){
        for(size_t i(0); i < pts_serialized.size(); i++){
            pts_serialized.at(i).thread_print();
        }    
    }

    Pts::~Pts(){
        count --;
    }
}