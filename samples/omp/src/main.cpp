#include "sched_core.hpp"
#include "dlworker.hpp"
#include <rts/core/pts.hpp>
#include <rts/sched/cho.hpp>
#include <rts/op/exp.hpp>
#include "spdlog/spdlog.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <omp.h>


int main(int argc, const char *argv[]) {
    if(argc < 3) {
       std::cout << "usage: ./omp ../data/exp/exp1.json ../data/ts/ts1.json" << std::endl;
       return -1;
    }
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^-%L-%$] [thread %t] %v");
    std::string current_exec_name = argv[0];
    std::cout << "main thread id: " << gettid() << std::endl;
    //omp_set_num_threads(20);

    rts::Exp e(argv[1]);
    
    std::ifstream _jf(argv[2]);
    nlohmann::json jf = nlohmann::json::parse(_jf);
    rts::Pts pts(jf, e);

    // rts::Cho cho;
    // cho.max_opt = 4;
    // cho.num_core = 4;
    // std::cout << (cho.is_schedulable(pts, e)) << std::endl;

    std::vector<DLWorker> workers;
    std::cout << pts.pt_list.size() << std::endl;
    for(unsigned int i = 0; i < pts.pt_list.size(); i++) {
        DLWorker dw(pts.pt_list[i]], e);
        workers.push_back(dw);
    }

    std::vector<std::thread> thrs;
    for(unsigned int i = 0; i < pts.pt_list.size(); i++) {
        thrs.push_back(std::thread(&DLWorker::work, &workers[i]));
    }

    for(std::thread &t: thrs){
        t.join();
    }

    std::cout << "main dies: " << gettid() << std::endl;

    return 0;
}
