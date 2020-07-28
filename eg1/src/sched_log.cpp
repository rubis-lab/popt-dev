#include "sched_log.hpp"
using namespace std;

SchedLog::SchedLog(string _fname) {
    fname = _fname;
    create_header();
}

string SchedLog::create_header() {
    string header_str = string("tid\t")
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
    string data_str = string("tid") + to_string(sdata.tid)
        + "\titer" + to_string(sdata.iter)
        + "\tstart_t" + to_string(sdata.start_t)
        + "\tend_t" + to_string(sdata.end_t)
        + "\treal_run" + to_string(sdata.real_run)
        + "\tslack" + to_string(sdata.slack);
    cout << data_str << endl;
    return true;
}
