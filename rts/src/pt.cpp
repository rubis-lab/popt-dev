#include "pt.hpp"

namespace rts {
    int Pt::count = 1;
    Pt::Pt(): id(count), max_opt(1), overhead(0.0), variance(1.0) {        count ++;
        count++;
        base_task = Task(id, 0, 1, 2, 3);
        TaskSet temp;
        //temp.get_task_list().push_back(base_task);
        //ts_table.push_back(temp);
        rts_print();
    }

    Pt::Pt(int mopt, double ovhd, double var){
        max_opt = mopt;
        overhead = ovhd;
        variance = var;
        Pt();
    }

    void rts_print(){

    }


}