#include "sched_deadline.hpp"

/* XXX use the proper syscall numbers */
#ifdef __x86_64__
#define __NR_sched_setattr		314
#define __NR_sched_getattr		315
#endif

#ifdef __i386__
#define __NR_sched_setattr		351
#define __NR_sched_getattr		352
#endif

#ifdef __arm__
#define __NR_sched_setattr		380
#define __NR_sched_getattr		381
#endif

#define BUFFER_SIZE 5000
#define MAX_TOKEN_COUNT 128

using namespace std;

// system call hook to call SCHED_DEADLINE
int sched_setattr(pid_t pid,
    const struct sched_attr *attr,
    unsigned int flags)
{
	return syscall(__NR_sched_setattr, pid, attr, flags);
}

int sched_getattr(pid_t pid,
    struct sched_attr *attr,
    unsigned int size,
    unsigned int flags)
{
	return syscall(__NR_sched_getattr, pid, attr, size, flags);
}

void routine_deadline(thr_arg targ) {
    // struct thr_arg targ = *((struct thr_arg *) _targ);
    // free(_targ);
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
