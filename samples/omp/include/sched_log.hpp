#ifndef __SCHED_LOG_H__
#define __SCHED_LOG_H__

#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"

struct sched_data_thread {
    double start_t;
    double end_t;
    double response_t;
    double slack;
    bool operator<(const sched_data_thread &a) const {
        return response_t > a.response_t;
    }
};

struct sched_data {
    int task_id;
    int iter = 0;
    double runtime;
    double period;
    std::vector<sched_data_thread> thr_data;
};

class SchedLog {
public:
    sched_data data;
    std::shared_ptr<spdlog::logger> async_logger;
    SchedLog(sched_data _data);
    bool log_to_file();
    bool write_header();
    bool compare(const sched_data_thread &a, const sched_data_thread &b);
};

#endif
