#include "sched_core.hpp"
#include "dlworker.hpp"
#include "dagworker.hpp"
#include <rts/core/pts.hpp>
#include <rts/sched/cho.hpp>
#include <rts/op/exp.hpp>
#include <rts/core/dag.hpp>
#include "spdlog/spdlog.h"
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
    // rts::Cho cho;
    // cho.max_opt = 4;
    // cho.num_core = 4;
    // std::cout << (cho.is_schedulable(pts, e)) << std::endl;

    
    // std::vector<int> result2 = dag.get_topological_order();
    // for(unsigned int i = 0; i < result2.size(); i++) {
    //     std::cout << result2.at(i);
    // }

    rts::DAG dag(pts, jf_dag);
    std::vector<std::vector<int>> result;
    std::vector<int> prev;
    dag.get_all_topological_order(result, prev);
    
    for(unsigned int i = 0; i < result.size(); i++) {
        for(unsigned int j = 0; j < result.at(i).size(); j++) {
            std::cout << result.at(i).at(j) << " -> ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    std::vector<std::thread> thrs;
    for(unsigned int i = 0; i < 4; i++) {
        thrs.push_back(std::thread(&rts::DAG::work, &dag, i));
    }
    
    for(std::thread &t: thrs) {
        t.join();
    }
    

    // std::vector<DAGWorker> workers;

    // for(unsigned int i = 0; i < 4; i++) { 
    //     DAGWorker dag(pts.pt_list[0], e);
    //     workers.push_back(dag);
    // }
   
    // std::vector<std::thread> thrs;
    // for(unsigned int i = 0; i < 4; i++) {
    //     thrs.push_back(std::thread(&DAGWorker::work, &workers[i], i));
    // }
    // for(std::thread &t: thrs) {
    //     t.join();
    // }

    // std::vector<DLWorker> workers;
    // std::cout << pts.pt_list.size() << std::endl;
    // for(unsigned int i = 0; i < pts.pt_list.size(); i++) {
    //     DLWorker dw(pts.pt_list[i], e);
    //     workers.push_back(dw);
    // }

    // std::vector<std::thread> thrs;
    // for(unsigned int i = 0; i < pts.pt_list.size(); i++) {
    //     thrs.push_back(std::thread(&DLWorker::work, &workers[i]));
    // }

    std::cout << "main dies: " << gettid() << std::endl;

    return 0;
}
