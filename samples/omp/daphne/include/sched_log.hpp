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
    int iter = 0;
    bool operator<(const sched_data_thread &a) const {
        return response_t > a.response_t;
    }
};

class SchedLog {
public:
    sched_data data;
    std::shared_ptr<spdlog::logger> async_logger;
    SchedLog();
    SchedLog(std::string _logger_name, std::string _logger_out_path);
    bool log_to_file(sched_data _data);
    bool write_header();
    bool compare(const sched_data_thread &a, const sched_data_thread &b);
    bool file_exist(std::string fileName);
};

#endif
