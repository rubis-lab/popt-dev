#include "sched_deadline.hpp"

using namespace std;

void routine_deadline(thr_arg targ) {
    cout << "task_id: " << targ.task_id << endl;
    cout << "parent: " << targ.parent << endl;

    // init workloads

    // configure thread attributes
    struct sched_attr attr;
    attr.size = sizeof(attr);
    attr.sched_flags = 0;
    attr.sched_nice = 0;
    attr.sched_priority = 0;

    attr.sched_policy = SCHED_DEADLINE; // 6
    attr.sched_runtime = targ.exec_time;
    attr.sched_deadline = targ.deadline;
    attr.sched_period = targ.period;
    
    int ret = sched_setattr(0, &attr, attr.sched_flags);
    if(ret < 0) {
        cout << "[ERROR] sched_setattr failed." << endl;
        perror("sched_setattr");
        exit(-1);
    }

    // actual routine
    clock_t start_t, end_t;
    for(int iter = 0; iter < 100; iter++) {
        start_t = clock();

        // dummy waste-cycle
        int y = 0;
        int workload = (int)80 * targ.exec_time;
        while(y < workload) {
            y++;
        }

        end_t = clock();

        // analyze
        cout << "task_id: " << targ.task_id << "thr_id: " << targ.thr_id << "\titer: " << iter << "\tdeadline: " << targ.deadline << "\tstart_t: " << start_t << "\tend_t: " << end_t << "\tresponse_time: " << end_t - start_t << endl;

        sched_yield();
    }
    return;
}
