#include "sched_log.hpp"

SchedLog::SchedLog() {
    return;
}

SchedLog::SchedLog(std::string _logger_name, std::string _logger_out_path) {
    std::sort(data.thr_data.begin(), data.thr_data.end());
    bool file_exists = false;
    if(file_exist(_logger_out_path)) {
        file_exists = true;
    }
    async_logger = spdlog::basic_logger_mt<spdlog::async_factory>(_logger_name, _logger_out_path);
    // async_logger = spdlog::basic_logger_mt(_logger_name, _logger_out_path);
    if(!file_exists) {
        write_header();
    }
    // spdlog::info("SchedLog (init): \nfile_exists: " + std::to_string(file_exists) + " logger_name: " + _logger_name + " logger_out_path: " + _logger_out_path);

    return;
}

bool SchedLog::write_header() {
    std::string log_str;
    log_str += "task id\t";
    log_str += "iter\t";
    log_str += "exec time\t";
    log_str += "period\t";
    log_str += "deadline\t";
    log_str += "start time\t";
    log_str += "end time\t";
    log_str += "response time\t";
    log_str += "slack\n";
    async_logger->info(log_str);
    return true;
}

bool SchedLog::log_to_file(sched_data _data) {
    std::string task_str = std::to_string(_data.task_id)
        + " " + std::to_string(_data.iter)
        + " " + std::to_string(_data.runtime)
        + " " + std::to_string(_data.period)
        + " " + std::to_string(_data.deadline);
    
    std::vector<sched_data_thread> thr_data = _data.thr_data;
    for(unsigned int i = 0; i < thr_data.size(); i ++) {
        std::string log_str;
        log_str += task_str;
        log_str += " " + std::to_string(thr_data.at(i).start_t);
        log_str += " " + std::to_string(thr_data.at(i).end_t);
        log_str += " " + std::to_string(thr_data.at(i).response_t);
        log_str += " " + std::to_string(thr_data.at(i).slack);
        async_logger->info(log_str);
        //std::string file_name = std::to_string(data.task_id) + "_" + std::to_string(i) + "_" + ".txt";
    }
    return true;
}

bool SchedLog::file_exist(std::string fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}
