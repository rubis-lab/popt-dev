#include "sched_core.hpp"
#include <rts/op/exp.hpp>
#include <iostream>


int main(int argc, char **argv) {
    if(argc < 2) {
        std::cout << "usage: ./omp exp1.json ts1.json" << std::endl;
        return -1;
    }
    std::cout << "main thread id: " << gettid() << std::endl;

    std::cout << "main dies: " << gettid() << std::endl;
    return 0;
}
