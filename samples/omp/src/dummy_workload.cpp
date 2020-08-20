#include "dummy_workload.hpp"

void work(int iter, int popt, int task_id, int deadline, int period) {
    //logging
    //spdlog::info("Profiling work function");

    int a = 0;
    std::string log = std::to_str(task_id);
    log += "\t";
    log += std::to_str(deadline);
    log += "\t";
    log += std::to_str(period);
    log += "\t";
    // to allow 1 ~ popt threads, remove omp_set_dynamic
    omp_set_dynamic(0);
    omp_set_num_threads(popt);
    #pragma omp parallel firstprivate(a, log) reduction(+: log)
    {
        double start_time = omp_get_wtime();
        #pragma omp for schedule(dynamic) nowait
        //assume body task of func
        for(int y = 0; y < iter; y++) {
            a += 1;
        }   
        double end_time = omp_get_wtime();
        log += std::to_str(start_time);
        log += "\t";
        log += std::to_str(end_time - start_time);
        log += "\n";
        //printf("Time taken by thread id %d is %f\n", omp_get_thread_num(), end_time - start_time);
    }
    std::cout << log << std::endl;
    return;
}