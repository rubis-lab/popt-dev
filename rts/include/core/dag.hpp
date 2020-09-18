#ifndef __DAG__
#define __DAG__

#include "core/pts.hpp"
#include "core/pt.hpp"
#include <vector>
#include <memory>
#include <chrono>
#include <mutex>
#include <iostream>

namespace rts {

struct task_node {
    rts::Pt task;
    volatile bool isFinished = false;
    std::vector<task_node> predecessors;
    std::vector<task_node> successors;
};

class DAG {
public:
    DAG(rts::Pts _pts);
    rts::Pts pts;
    std::vector<task_node> task_list;
    void msec_work(int _msec);
    void work(int _index);
    bool isReady(struct task_node _task);
};

} // namespace rts
#endif