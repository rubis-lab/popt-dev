#ifndef __THR_H__
#define __THR_H__

#include <iostream>
#include "task.hpp"

namespace rts{
    class Thread : public Task::Task{
    private:
        int tid;
    public:
        Thread(int thr_id);
        int get_thr_id();
        void thread_print();
    };
}

#endif