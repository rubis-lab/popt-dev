#include "sched_deadline.hpp"


bool set_sched_deadline(int _tid, int _exec_time, int _deadline, int _period) {
    struct sched_attr attr;
    attr.size = sizeof(attr);
    attr.sched_flags = 0;
    attr.sched_nice = 0;
    attr.sched_priority = 0;

    attr.sched_policy = SCHED_DEADLINE; // 6
    attr.sched_runtime = _exec_time;
    attr.sched_deadline = _deadline;
    attr.sched_period = _period;

    int ret = sched_setattr(_tid, &attr, attr.sched_flags);
    if(ret < 0) {
        std::cerr << "[ERROR] sched_setattr failed." << std::endl;
        perror("sched_setattr");
        exit(-1);
        return false;
    }
    return true;
}

void routine_deadline(task_arg targ, int idx) {
    std::cout << "task_id: " << targ.task_id << std::endl;

    // Target Thread Arguments
    struct thr_arg tta = targ.thr_set.at(idx);
    // init workloads
    // configure thread attributes
    struct sched_attr attr;
    attr.size = sizeof(attr);
    attr.sched_flags = 0;
    attr.sched_nice = 0;
    attr.sched_priority = 0;

    attr.sched_policy = SCHED_DEADLINE; // 6
    attr.sched_deadline = targ.deadline;
    attr.sched_period = targ.period;
    // Thread specific
    attr.sched_runtime = tta.exec_time;
    
    int ret = sched_setattr(0, &attr, attr.sched_flags);
    if(ret < 0) {
        std::cerr << "[ERROR] sched_setattr failed." << std::endl;
        perror("sched_setattr");
        exit(-1);
    }

    // actual routine
    clock_t start_t, end_t;
    for(int iter = 0; iter < 100; iter++) {
        start_t = clock();

        // dummy waste-cycle
        int y = 0;
        int workload = (int)80 * tta.exec_time;
        while(y < workload) {
            y++;
        }

        end_t = clock();

        // analyze
        std::cout << "task_id: " << targ.task_id << "\tthr_id: " << tta.thr_id << "\titer: " << iter << "\tdeadline: " << targ.deadline << "\tstart_t: " << start_t << "\tend_t: " << end_t << "\tresponse_time: " << end_t - start_t << std::endl;

        sched_yield();
    }
    return;
}
