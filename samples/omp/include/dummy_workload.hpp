#ifndef __DUMMY_WORKLOAD_H__
#define __DUMMY_WORKLOAD_H__
#include <omp.h>
#include <iostream>
#include <string>
#include <rts/core/pt.hpp>
#include "sched_log.hpp"
#include "sched_core.hpp"

void work(rts::Pt _task);

#endif
