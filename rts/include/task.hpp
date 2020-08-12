#ifndef __TASK_H__
#define __TASK_H__

#include <iostream>
namespace rts {
    class Task {
    private:
        int task_id = -1;
        int popt;
        int exec_time;
        int deadline;
        int period; 
    public:
        Task();
        void task_print();
        void set_task_id(int id);
        void set_popt(int pt);
        void set_exec_time(int ext);
        void set_deadline(int dl);
        void set_period(int prd);
        int get_task_id();
        int get_popt();
        int get_exec_time();
        int get_deadline();
        int get_period();
    };
}

#endif