#include "sched_core.hpp"
#include "dummy_workload.hpp"
#include <rts/core/pts.hpp>
#include <rts/sched/cho.hpp>
#include <rts/op/exp.hpp>
#include "spdlog/spdlog.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
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

    std::vector<DummyWorkload> works;
    std::cout << pts.pt_list.size() << std::endl;
    for(unsigned int i = 0; i < pts.pt_list.size(); i++) {
        DummyWorkload dw(pts.pt_list.at(i), e);
        works.push_back(dw);
        // std::cout << pts.pt_list.at(i).id << std::endl;
    }

    std::vector<std::thread> thrs;
    for(unsigned int i = 0; i < pts.pt_list.size(); i++) {
        thrs.push_back(std::thread(&DummyWorkload::work, &works[i]));
    }

    for(std::thread &t: thrs){
        // std::cout << "Task thread ID: " << gettid() << std::endl;
        t.join(); //pauses until t finishes;
    }

    std::cout << "main dies: " << gettid() << std::endl;

    return 0;
}
