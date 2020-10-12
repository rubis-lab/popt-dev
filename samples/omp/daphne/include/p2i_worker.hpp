#ifndef __P2IDLWORKER_H__
#define __P2IDLWORKER_H__
#include <omp.h>
#include <cmath>
#include <string>
#include <vector>
#include <rts/core/pt.hpp>
#include <rts/op/exp.hpp>
#include "p2i_kernel.hpp"
#include "sched_log.hpp"
#include "sched_core.hpp"
#include "sched_deadline.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"

class P2IWorker {
public:
    std::string name;
    std::shared_ptr<spdlog::logger> thr_log;
    std::vector<int> omp_thr_ids;
    rts::Pt pt;
    SchedLog sl;
    P2IWorker(rts::Pt _pt, rts::Exp _exp);
    void apply_rt();
    void msec_work(int msec);
    void work();
};

#endif
