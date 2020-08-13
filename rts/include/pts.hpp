#ifndef __PTS_H__
#define __PTS_H__

#include "task.hpp"
#include "task_set.hpp"
#include "thread.hpp"
#include "pt.hpp"

namespace rts{
    class Pts{
    private:
        Pts::~Pts();
        int max_opt;
        double overhead;
        double variance;
        static int count;
        int id;
        std::string popt_strategy;
        int popt_list[];
        Task base_task;
        TaskSet base_task_set;
        std::vector<Pt> pt_list;
        std::vector<Thread> pts_serialized;
    public:
        Pts::Pts();
        void populate_pt_list();
        void serialize_pts();
        void pts_print();
        void set_pts_item(Thread, int);
        Thread get_pts_item(int);
        void clear();
    };
}

#endif