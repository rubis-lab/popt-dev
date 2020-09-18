#include "core/dag.hpp"

namespace rts {
DAG::DAG(rts::Pts _pts) {
    pts = _pts;
    for(unsigned int i = 0; i < pts.pt_list.size(); i++) {
        task_node temp;
        temp.task = pts.pt_list.at(i);
        task_list.push_back(temp);
    }
}

void DAG::work(int _index) {
    int64_t t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << "index " << _index << " entering work: " << t0 << std::endl;
    while(!isReady(task_list.at(_index))){
        ;
    }
    int iter = 1;
    for(int task_iter = 0; task_iter < iter; task_iter++) {
        // create task data for logging
        // actual work    
        for(int y = 0; y < 100; y++) {
            msec_work((100 - y)/10);
        }
        //sched_yield();
    }  // task loop
    int64_t t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << "index " << _index << " end time: "
              << t1 << '\n';
    task_list.at(_index).isFinished = true;
    for(unsigned int i = 0; i < task_list.size(); i++) {
        for(unsigned int j = 0; j < task_list.at(i).predecessors.size(); j++) {
            if(!(task_list.at(i).predecessors.at(j).isFinished)) {
                task_list.at(i).predecessors.at(j).isFinished = true;
                break;
            }
        }
    }
    return;
}

bool DAG::isReady(struct task_node _task) {
    if(_task.predecessors.empty()) {
        return true;
    } else {
        for(unsigned int i = 0; i < _task.predecessors.size(); i++) {
            if(!(_task.predecessors.at(i).isFinished)) {
                return false;
            }
        }
        return true;
    }
}

void DAG::msec_work(int _msec) {
    // 600000 addition takes about 1msec on an 1.2GHz CPU
    unsigned int iter = 600000 * _msec;
    int sum = 0;
    for(unsigned int i = 0; i < iter; i++) {
        sum++;
    }
    return;
}

} // namespace rts