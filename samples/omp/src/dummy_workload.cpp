#include "dummy_workload.hpp"

void work(int _iter, int _popt, int _task_id, int _runtime, int _deadline, int _period) {
    //logging
    //spdlog::info("Profiling work function");

    int a = 0;
    sched_data task_data;
    task_data.task_id = _task_id;
    task_data.iter += 1;
    task_data.runtime = _runtime;
    task_data.period = _period;
    // to allow 1 ~ popt threads, remove omp_set_dynamic
    omp_set_dynamic(0);
    omp_set_num_threads(_popt);
    #pragma omp parallel firstprivate(a)
    {
        double start_time = omp_get_wtime();
        #pragma omp for schedule(dynamic) nowait
        //assume body task of func
        for(int y = 0; y < _iter; y++) {
            a += 1;
        }   
        double end_time = omp_get_wtime();
        sched_data_thread thread_data;
        thread_data.start_t = start_time;
        thread_data.end_t = end_time;
        thread_data.response_t = end_time - start_time;
        thread_data.slack = _deadline - thread_data.response_t;
        #pragma omp critical
        task_data.thr_data.push_back(thread_data);
        //printf("Time taken by thread id %d is %f\n", omp_get_thread_num(), end_time - start_time);
    }
    SchedLog s(task_data);
    s.log_to_file();
    return;
}
