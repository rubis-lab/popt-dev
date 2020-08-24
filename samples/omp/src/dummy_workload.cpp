#include "dummy_workload.hpp"


DummyWorkload::DummyWorkload(rts::Pt _pt, rts::Exp _exp) {
    pt = _pt;
    name = "DummyWorkload-" + _exp.name + "-" + std::to_string(pt.id);

    // logger for thread debug messages
    std::string thread_logger_name = "thread-" + name + "_logger";
    std::string thread_logger_out_path = "thread-" + name + ".out";

    thr_log = spdlog::basic_logger_mt<spdlog::async_factory>(thread_logger_name, thread_logger_out_path);
    thr_log->info(name + " (init): \npt: " + _pt.to_str() + "exp: " + _exp.to_str());

    // logger for sched analysis
    std::string sched_logger_name = name + "_logger";
    std::string sched_logger_out_path = name + ".out";
    sl = SchedLog(sched_logger_name, sched_logger_out_path);
    return;
}

void DummyWorkload::work() {
    int a = 0;
    int iter = 100;
    sched_data task_data;
    task_data.task_id = pt.id;
    thr_log->info(name + " (work): pt id: " + std::to_string(pt.id));
    task_data.iter = 0;
    //TODO - exec times!
    task_data.runtime = pt.base_task.exec_time;
    task_data.period = pt.base_task.period;
    task_data.deadline = pt.base_task.deadline;
    // to allow 1 ~ popt threads, remove omp_set_dynamic
    thr_log->info(name + " (work): Setting thread_num to: " + std::to_string(pt.selected_opt));
    omp_set_dynamic(0);
    #pragma omp parallel firstprivate(a) num_threads(pt.selected_opt)
    {
        double start_time = omp_get_wtime();
        #pragma omp for schedule(dynamic) nowait
            for(int y = 0; y < iter; y++) {
                a += 1;
            }
        //assume body task of func   
        double end_time = omp_get_wtime();
        sched_data_thread thread_data;
        thread_data.start_t = start_time;
        thread_data.end_t = end_time;
        thread_data.response_t = end_time - start_time;
        thread_data.slack = task_data.deadline - thread_data.response_t;
        #pragma omp critical
        {
            task_data.thr_data.push_back(thread_data);
            thr_log->info(name + " (work): Thread num: " + std::to_string(omp_get_thread_num()) + " tid: " + std::to_string(gettid()));
        }
    }
    #pragma omp barrier
    thr_log->info(name + " (work): Logging results.\n");
    sl.log_to_file(task_data);
    return;
}
