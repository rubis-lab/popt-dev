#ifndef __OMP_LOG_H__
#define __OMP_LOG_H__

#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"

struct omp_data {
    double start_t;
    double end_t;
    double exec_t;
    int iter;
    int test_case;
    int tid;
};

class OmpLog {
public:
    omp_data data;
    std::shared_ptr<spdlog::logger> async_logger;
    OmpLog();
    OmpLog(std::string _logger_name, std::string _logger_out_path);
    bool log_to_file(std::vector<std::vector<omp_data>> _data);
    bool write_header();
    bool file_exist(std::string fileName);
};

#endif
