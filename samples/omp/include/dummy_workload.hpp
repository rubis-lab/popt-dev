#ifndef __DUMMY_WORKLOAD_H__
#define __DUMMY_WORKLOAD_H__
#include <omp.h>
#include <iostream>
#include <string>
#include "spdlog/spdlog.h"

void work(int iter, int popt, int task_id, int deadline, int period);

#endif
