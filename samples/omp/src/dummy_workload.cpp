#include "dummy_workload.hpp"

void work(rts::Pt _task) {
    //logging
    //spdlog::info("Profiling work function");

    int a = 0;
    int iter = 100;
    sched_data task_data;
    task_data.task_id = _task.id;
    task_data.iter += 1;
    //TODO - exec times!
    task_data.runtime = _task.base_task.exec_time;
    task_data.period = _task.base_task.period;
    task_data.deadline = _task.base_task.deadline;
    // to allow 1 ~ popt threads, remove omp_set_dynamic
    omp_set_dynamic(0);
    omp_set_num_threads(_task.max_opt);
    #pragma omp parallel firstprivate(a)
    {
        double start_time = omp_get_wtime();
        #pragma omp for schedule(dynamic) nowait
        //assume body task of func
        for(int y = 0; y < iter; y++) {
            a += 1;
        }   
        double end_time = omp_get_wtime();
        sched_data_thread thread_data;
        thread_data.start_t = start_time;
        thread_data.end_t = end_time;
        thread_data.response_t = end_time - start_time;
        thread_data.slack = task_data.deadline - thread_data.response_t;
        #pragma omp critical
        task_data.thr_data.push_back(thread_data);
        std::cout << "Thread num: " << omp_get_thread_num() << " tid: " << gettid() << std::endl;
        //printf("Time taken by thread id %d is %f\n", omp_get_thread_num(), end_time - start_time);
    }
    SchedLog s(task_data);
    s.log_to_file();
    return;
}
