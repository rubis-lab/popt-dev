#include "task.hpp"

namespace rts {
    Task::Task(): task_id(-1) {
        task_print();
    }

    Task::Task(int id, int pt, int ext, int dl, int prd){
        task_id = id;
        popt = pt;
        exec_time = ext;
        deadline = dl;
        period = prd;
    }

    void Task::task_print(){
        if(task_id == -1){
            std::cout << "task does not exist; create task_set object first or initialize the attributes" << std::endl;
        } else {
            std::cout << task_id << "\t" << exec_time << "\t" << 
            deadline << "\t" << period << "\t" << popt<< std::endl;
        }
    }

    void Task::set_task_id(int id){
        task_id = id;
    }
    void Task::set_popt(int pt){
        popt = pt;
    }
    void Task::set_exec_time(int ext){
        exec_time = ext;
    }
    void Task::set_deadline(int dl){
        deadline = dl;
    }
    void Task::set_period(int prd){
        period = prd;
    }

    int Task::get_task_id(){
        return task_id;
    }
    int Task::get_popt(){
        return popt;
    }
    int Task::get_exec_time(){
        return exec_time;
    }    
    int Task::get_deadline(){
        return deadline;
    }
    int Task::get_period(){
        return period;
    }
}
