#include <thread>
#include <vector>
#include <unistd.h>
#include <iostream>
#include "sched_deadline.hpp"
using namespace std;

struct thr_arg {
    int task_id;
    int thr_id;
    int parent;
    int exec_time;
    int deadline;
    int period;
};

void routine1(void *data) {
    struct thr_arg targ = *((struct thr_arg *) data);
    free(data);
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

// int main(int argc, char **argv) {
int main() {
    cout << "main thread id: " << gettid() << endl;

    // two task example
    int num_task = 2;
    vector<thread> thrs;
    for(int i = 0; i < num_task; i++) {
        struct thr_arg targ;
        struct thr_arg* targ_ptr = &targ;
        targ_ptr->task_id = i;
        targ_ptr->thr_id = 0;
        targ_ptr->parent = gettid();
        targ_ptr->exec_time = 10000;
        targ_ptr->deadline = 15000;
        targ_ptr->period = 20000;

        struct thr_arg *arg = (struct thr_arg *) malloc(sizeof(*arg));
        *arg = targ;
        if(!arg) {
            fprintf(stderr, 
                "[ERROR] Couldn't allocate memory for thread arg.\n");
            exit(EXIT_FAILURE);
        }
        thrs.push_back(thread(routine1, arg));
    }
    
    for(thread &t : thrs)
        t.join();

    cout << "main dies: " << gettid() << endl;

    return 0;
}
