#ifndef __SCHED_DEADLINE_H__
#define __SCHED_DEADLINE_H__

#define SCHED_DEADLINE	6
#include "sched_core.hpp"
#include <iostream>

void routine_deadline(task_arg targ, int idx);
bool set_sched_deadline(int _tid, int _exec_time, int _deadline, int _period);
#endif
