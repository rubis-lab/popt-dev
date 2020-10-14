#ifndef __SEQ_LOG_H__
#define __SEQ_LOG_H__

#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"

struct seq_data {
    double start_t;
    double end_t;
    double exec_t;
    int test_case;
    int tid;
};

class SeqLog {
public:
    seq_data data;
    std::shared_ptr<spdlog::logger> async_logger;
    SeqLog();
    SeqLog(std::string _logger_name, std::string _logger_out_path);
    bool log_to_file(std::vector<seq_data> _data);
    bool write_header();
    bool file_exist(std::string fileName);
};

#endif
