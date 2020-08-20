#include "sched_log.hpp"

SchedLog::SchedLog(std::string _fname) {
    fname = _fname;
    create_header();
}

std::string SchedLog::create_header() {
    std::string header_str = std::string("tid\t")
        + "iter\t"
        + "runtime\t"
        + "deadline\t"
        + "period\t"
        + "start\t"
        + "end\t"
        + "run\t"
        + "slack\t"
        + "realrun";
    return header_str;
}

bool SchedLog::append(sched_data sdata) {
    std::string data_str = std::string("tid") + std::to_string(sdata.tid)
        + "\titer" + std::to_string(sdata.iter)
        + "\tstart_t" + std::to_string(sdata.start_t)
        + "\tend_t" + std::to_string(sdata.end_t)
        + "\treal_run" + std::to_string(sdata.real_run)
        + "\tslack" + std::to_string(sdata.slack);
    std::cout << data_str << std::endl;
    return true;
}
