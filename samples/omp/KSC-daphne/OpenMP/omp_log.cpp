#include "omp_log.hpp"

OmpLog::OmpLog() {
    return;
}

OmpLog::OmpLog(std::string _logger_name, std::string _logger_out_path) {
    bool file_exists = false;
    if(file_exist(_logger_out_path)) {
        file_exists = true;
    }
    async_logger = spdlog::basic_logger_mt<spdlog::async_factory>(_logger_name, _logger_out_path);
    if(!file_exists) {
        write_header();
    }
    return;
}

bool OmpLog::write_header() {
    std::string log_str;
    log_str += "start time\t";
    log_str += "end time\t";
    log_str += "exec time\t";
    log_str += "iter\t";
    log_str += "test_case\t";
    log_str += "thread id\t";;
    async_logger->info(log_str);
    return true;
}

bool OmpLog::log_to_file(std::vector<std::vector<omp_data>> _data) {
    for(unsigned int i = 0; i < _data.size(); i++) {
        for(unsigned int j = 0; j < _data.at(i).size(); j++){
            std::string log_str = std::to_string(_data.at(i).at(j).start_t)
            + "\t" + std::to_string(_data.at(i).at(j).end_t)
            + "\t" + std::to_string(_data.at(i).at(j).exec_t)
            + "\t" + std::to_string(_data.at(i).at(j).test_case)
            + "\t" + std::to_string(_data.at(i).at(j).tid);
            async_logger->info(log_str);
        }
    }
    return true;
}

bool OmpLog::file_exist(std::string fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}
