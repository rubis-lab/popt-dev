#ifndef __DUMMY_WORKLOAD_H__
#define __DUMMY_WORKLOAD_H__
#include <omp.h>
#include <iostream>
#include <string>
#include <rts/core/pt.hpp>
#include <rts/op/exp.hpp>
#include "sched_log.hpp"
#include "sched_core.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"

class DummyWorkload {
public:
    std::string name;
    std::shared_ptr<spdlog::logger> thr_log;
    void work();
    DummyWorkload(rts::Pt _pt, rts::Exp _exp);
    rts::Pt pt;
    SchedLog sl;
};

#endif
