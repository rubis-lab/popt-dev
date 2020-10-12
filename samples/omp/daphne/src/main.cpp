#include "sched_core.hpp"
#include <rts/core/pts.hpp>
#include <rts/sched/cho.hpp>
#include <rts/op/exp.hpp>
#include <rts/core/dag.hpp>
#include "spdlog/spdlog.h"
#include "p2i_kernel.hpp"
#include "p2i_worker.hpp"
#include "euc_kernel.hpp"
#include "euc_worker.hpp"
#include "ndt_kernel.hpp"
#include "ndt_worker.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <omp.h>


int main(int argc, const char *argv[]) {
    if(argc < 3) {
       std::cout << "usage: ./omp ../data/exp/exp1.json ../data/ts/ts1.json  ../data/dag/dag.json" << std::endl;
       return -1;
    }
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^-%L-%$] [thread %t] %v");
    std::string current_exec_name = argv[0];
    std::cout << "main thread id: " << gettid() << std::endl;
    //omp_set_num_threads(20);

    rts::Exp e(argv[1]);
    std::ifstream _jf(argv[2]);
    std::ifstream _jf_dag(argv[3]);
    nlohmann::json jf = nlohmann::json::parse(_jf);
    nlohmann::json jf_dag = nlohmann::json::parse(_jf_dag);
    rts::Pts pts(jf, e);

    std::vector<EUCWorker> workers;
    std::cout << pts.pt_list.size() << std::endl;
    for(unsigned int i = 0; i < pts.pt_list.size(); i++) {
        EUCWorker dw(pts.pt_list[i], e);
        workers.push_back(dw);
    }

    std::vector<std::thread> thrs;
    for(unsigned int i = 0; i < pts.pt_list.size(); i++) {
        thrs.push_back(std::thread(&EUCWorker::work, &workers[i]));
    }

    std::cout << "main dies: " << gettid() << std::endl;

    return 0;
}
