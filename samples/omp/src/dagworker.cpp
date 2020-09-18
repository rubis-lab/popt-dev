#include "dagworker.hpp"

volatile int mutex = 0;

DAGWorker::DAGWorker(rts::Pt _pt, rts::Exp _exp) {
    pt = _pt;
    name = "DAGWorker-" + _exp.name + "-" + std::to_string(pt.id);
    count = 0;
    mutex = 0;
    return;
}


void DAGWorker::msec_work(int _msec) {
    // 600000 addition takes about 1msec on an 1.2GHz CPU
    unsigned int iter = 600000 * _msec;
    int sum = 0;
    for(unsigned int i = 0; i < iter; i++) {
        sum++;
    }
    return;
}

void DAGWorker::work(int _index) {
    // task loop
    while(mutex != _index) {
        ;
    }
    std::mutex mu;
    mu.lock();
    std::cout << "entering work" << std::endl;
    int iter = 1;
    for(int task_iter = 0; task_iter < iter; task_iter++) {
        // create task data for logging
        // actual work    
        for(int y = 0; y < 100; y++) {
            msec_work((100 - y)/10);
        }
        //sched_yield();
    }  // task loop
    std::cout << "index " << _index << " completed" << std::endl;
    mutex++;
    std::cout << mutex << std::endl;
    mu.unlock();
    return;
}