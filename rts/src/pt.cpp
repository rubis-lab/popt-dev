#include "pt.hpp"

namespace rts {
    int Pt::count = 1;

    Pt::Pt(): id(count++), max_opt(1), 
        overhead(0.0), variance(1.0) 
    {
        base_task = Task(id, 0, 1, 2, 3);
        TaskSet temp;
        temp.get_task_list().push_back(base_task);
        ts_table.push_back(temp);
        //pt_print();
        //parse and check if custom or not
        //populate_table...
    }

    Pt::Pt(int mopt, double ovhd, double var){
        max_opt = mopt;
        overhead = ovhd;
        variance = var;
        Pt();
    }
    
    

    void Pt::populate_ts_table_custom(std::vector<std::vector<int>> exec_times){
        if(max_opt >=2){
            for(size_t i(0); i < (size_t) max_opt; i++){
                TaskSet ts;
                for(size_t j(0); j < exec_times.at(i).size(); j++){
                    Thread t1(base_task.get_task_id());
                    t1.set_exec_time(exec_times.at(i).at(j));
                    t1.set_deadline(base_task.get_deadline());
                    t1.set_popt(base_task.get_popt());
                    t1.set_period(base_task.get_deadline());
                    ts.get_task_list().push_back(t1);
                }
                ts_table.push_back(ts);
            }
        }
    }

    void Pt::set_base_task(Task t){
        base_task = t;
    }

    Pt::~Pt(){
        count--;
    }

    void Pt::populate_ts_table(){
        //TODO
    }

    void Pt::pt_print(){
        std::cout << "rts_print()" << std::endl;
        std::cout << id << "\t" << max_opt << "\n";
        base_task.task_print(); 
        if(max_opt >=2){
            for(size_t i(0); i <= (size_t) max_opt; i++){
                //TODO
                std::cout << overhead << "\t" << variance << std::endl;
            }
        }
    }
}