#include "euc_worker.hpp"

extern kernel& EUCKernel;

EUCWorker::EUCWorker(rts::Pt _pt, rts::Exp _exp) {
    pt = _pt;
    name = "DLWorker-" + _exp.name + "-" + std::to_string(pt.id);

    // logger for thread debug messages
    std::string thread_logger_name = "thread-" + name + "_logger";
    std::string thread_logger_out_path = "thread-" + name + ".out";

    thr_log = spdlog::basic_logger_mt<spdlog::async_factory>(thread_logger_name, thread_logger_out_path);
    thr_log->info("(init): \npt: " + _pt.to_str() + "exp: " + _exp.to_str());

    // logger for sched analysis
    std::string sched_logger_name = name + "_logger";
    std::string sched_logger_out_path = name + ".out";
    sl = SchedLog(sched_logger_name, sched_logger_out_path);
    return;
}

void EUCWorker::apply_rt() {
    // check rt constraints applied to openmp thread
    int tid = gettid();
    if(std::find(omp_thr_ids.begin(), omp_thr_ids.end(), tid)!=omp_thr_ids.end()) {
        // thr_log->info("(work): rt-constraints already applied");
    } else {
        int _tperiod = (int)std::round(pt.base_task.period);
        int _tdeadline = (int)std::round(pt.base_task.deadline);
        int _texec_time = (int)std::round(pt.tsdict[pt.selected_opt][0].exec_time);
        thr_log->info("(work): setting rt-constraints for " + std::to_string(tid));
        set_sched_deadline(tid, _texec_time, _tdeadline, _tperiod);
        omp_thr_ids.push_back(tid);
    }
    return;
}

void EUCWorker::work() {
    // task loop
    int iter = 1;
    std::cout << "hi" << pt.selected_opt << std::endl;
    std::chrono::high_resolution_clock::time_point start,end;
    std::chrono::duration<double> elapsed;
    std::chrono::high_resolution_clock timer;
    euclidean_clustering euc = euclidean_clustering();
    kernel& EUCKernel = euc;
    for(int task_iter = 0; task_iter < iter; task_iter++) {
        // create task data for logging
        sched_data task_data;
        task_data.task_id = pt.id;
        task_data.iter = task_iter;
        task_data.runtime = pt.base_task.exec_time;
        task_data.period = pt.base_task.period;
        task_data.deadline = pt.base_task.deadline;
        omp_set_dynamic(0);
        #pragma omp parallel num_threads(1)
        {
            //apply_rt();
            #pragma omp barrier

            // actual work
            double start_time = omp_get_wtime();
            // #pragma omp for schedule(dynamic, 1) nowait
            std::cout << "start time " << start_time << std::endl;
            EUCKernel.init();
            std::cout << "init done" << std::endl;
            // measure the runtime of the kernel
            start = timer.now();

            // execute the kernel
            EUCKernel.run(1);
            std::cout << "run done" << std::endl;
            // measure the runtime of the kernel
            if (!pause) 
            {
            end = timer.now();
                elapsed += end-start;
            }
            std::cout <<  "elapsed time: "<< elapsed.count() << " seconds, average time per testcase (#"
                << EUCKernel.testcases << "): " << elapsed.count() / (double) EUCKernel.testcases
                << " seconds" << std::endl;

            // read the desired output  and compare
            if (EUCKernel.check_output())
            {
                std::cout << "result ok\n";
            } else
            {
                std::cout << "error: wrong result\n";
            }
            double end_time = omp_get_wtime();

            // log work
            sched_data_thread thr_data;
            thr_data.start_t = start_time;
            thr_data.end_t = end_time;
            thr_data.response_t = (end_time - start_time) * 1e9;
            thr_data.slack = task_data.deadline - thr_data.response_t;
            thr_data.iter = task_iter;
            #pragma omp critical
            {
                task_data.thr_data.push_back(thr_data);
                thr_log->info("(work): openmp_thread_idx: " + std::to_string(omp_get_thread_num()));
            }
            thr_log->info("num iter " + std::to_string(thr_data.iter));
        }

        thr_log->info("(work): iter " + std::to_string(task_iter) + " completed.");
        sl.log_to_file(task_data);
        sched_yield();
    }  // task loop
    thr_log->info("(work) task exiting..");

    return;
}
