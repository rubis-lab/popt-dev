#include "sched_core.hpp"
#include "dummy_workload.hpp"
#include <rts/core/pts.hpp>
#include "spdlog/spdlog.h"
#include <iostream>
#include <fstream>
#include <string>


int main(int argc, const char *argv[]) {
    if(argc < 2) {
       std::cout << "usage: ./omp exp1.json ../data/ts/ts1.json" << std::endl;
       return -1;
    }
    //std::string current_exec_name = argv[0];
    //std::cout << "main thread id: " << gettid() << std::endl;

    //rts::Exp e(argv[1]);
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    // work(100, 4, 3, 50, 100, 200);

    std::ifstream _jf(argv[1]);
    nlohmann::json jf = nlohmann::json::parse(_jf);
    rts::Pts pts(jf);
    std::cout << "pts: " << pts.to_str() << std::endl;
    std::cout << "main dies: " << gettid() << std::endl;
    return 0;
}
