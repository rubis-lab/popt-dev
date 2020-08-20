#ifndef __DUMMY_WORKLOAD_H__
#define __DUMMY_WORKLOAD_H__
#include <omp.h>
#include <iostream>
#include <string>
#include "sched_log.hpp"

void work(int _iter, int _popt, int _task_id, int _runtime, 
    int _deadline, int _period);

#endif
