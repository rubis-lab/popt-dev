#ifndef __DAGWORKER__
#define __DAGWORKER__

#include <vector>
#include <mutex>
#include <iostream>
#include <rts/core/pt.hpp>
#include <rts/op/exp.hpp>
#include "sched_log.hpp"
#include "sched_core.hpp"
#include "sched_deadline.hpp"

class DAGWorker {
public:
    std::string name;
    int count;
    DAGWorker(rts::Pt _pt, rts::Exp _exp);
    std::vector<int> thr_ids;
    std::vector<int> dependence_order;
    rts::Pt pt;
    void msec_work(int _msec);
    void work(int _index);
};

#endif