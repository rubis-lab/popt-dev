#include "dummy_workload.hpp"

void work(int iter) {
    int a = 0;
    #pragma omp_jdskfjdskl 
    for(int y = 0; y < iter; y++) {
        a += 1;
    }
    return;
}