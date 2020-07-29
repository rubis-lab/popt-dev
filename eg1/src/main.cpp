#include <thread>
#include <vector>
#include <iostream>
#include "sched_deadline.hpp"
using namespace std;

// int main(int argc, char **argv) {
int main() {
    cout << "main thread id: " << gettid() << endl;

    // two task example
    int num_task = 2;
    vector<thread> thrs;
    for(int i = 0; i < num_task; i++) {
        struct thr_arg targ;
        targ.task_id = i;
        targ.thr_id = 0;
        targ.parent = gettid();
        targ.exec_time = 10000;
        targ.deadline = 15000;
        targ.period = 20000;
        thrs.push_back(thread(routine_deadline, targ));
    }
    
    for(thread &t : thrs)
        t.join();

    cout << "main dies: " << gettid() << endl;

    return 0;
}
