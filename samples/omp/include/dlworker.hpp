#ifndef __DLWORKER_H__
#define __DLWORKER_H__
#include <omp.h>
#include <cmath>
#include <string>
#include <vector>
#include <rts/core/pt.hpp>
#include <rts/op/exp.hpp>
#include "sched_log.hpp"
#include "sched_core.hpp"
#include "sched_deadline.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"

class DLWorker {
public:
    std::string name;
    std::shared_ptr<spdlog::logger> thr_log;
    std::vector<int> omp_thr_ids;
    rts::Pt pt;
    SchedLog sl;
    DLWorker(rts::Pt _pt, rts::Exp _exp);
    void apply_rt();
    void msec_work(int msec);
    void work();
};

#endif
