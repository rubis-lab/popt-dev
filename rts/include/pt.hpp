#ifndef __PT_H__
#define __PT_H__

#include "task_set.hpp"
#include "thread.hpp"

namespace rts{
    class Pt{
    private:
        int id;
        static int count;
        int max_opt;
        double overhead;
        double variance;
        Task base_task;
        std::vector<TaskSet> ts_table;
    public:
        Pt();
        ~Pt();
        Pt(int max_opt, double overhead, double variance);
        //void parse_pt_config(std::string fname);
        void populate_ts_table();
        void populate_ts_table_custom(std::vector<std::vector<int>>);
        void pt_print();
        void set_base_task(Task);
    };
}
#endif