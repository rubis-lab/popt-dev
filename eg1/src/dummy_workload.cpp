#include "dummy_workload.hpp"
#include <omp.h>

void work(int iter, int popt) {
    int a = 0;

    // to allow 1 ~ popt threads, remove omp_set_dynamic
    omp_set_dynamic(0);
    omp_set_num_threads(popt);
    #pragma omp parallel firstprivate(a)
    for(int y = 0; y < iter; y++) {
        a += 1;
    }
    return;
}