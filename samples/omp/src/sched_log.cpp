#include "sched_log.hpp"

SchedLog::SchedLog(sched_data _data) {
    data = _data;
    std::sort(data.thr_data.begin(), data.thr_data.end());
    async_logger = spdlog::basic_logger_mt<spdlog::async_factory>("async_file_logger", "./log/task.txt");
    write_header();
}

bool SchedLog::write_header(){
    std::string log_str;
    log_str += "task id\t";
    log_str += "iter\t";
    log_str += "exec time\t";
    log_str += "period\t";
    log_str += "start time\t";
    log_str += "end time\t";
    log_str += "response time\t";
    log_str += "slack\n";
    async_logger -> info(log_str);
    return true;
}

bool SchedLog::log_to_file() {
    std::string task_str = std::to_string(data.task_id)
        + " " + std::to_string(data.iter)
        + " " + std::to_string(data.runtime)
        + " " + std::to_string(data.period);
    for(unsigned int i = 0; i < data.thr_data.size(); i ++){
        std::string log_str;
        log_str += task_str;
        log_str += " " + std::to_string(data.thr_data.at(i).start_t);
        log_str += " " + std::to_string(data.thr_data.at(i).end_t);
        log_str += " " + std::to_string(data.thr_data.at(i).response_t);
        log_str += " " + std::to_string(data.thr_data.at(i).slack);
        async_logger->info(log_str);
        //std::string file_name = std::to_string(data.task_id) + "_" + std::to_string(i) + "_" + ".txt";
    }
    return true;
}




//@TODO: deadline print