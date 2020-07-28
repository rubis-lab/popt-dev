#ifndef __SCHED_LOG_H__
#define __SCHED_LOG_H__

#include <ctime>
#include <string>
#include <iostream>
#include <fstream>


struct sched_data {
    int tid;
    int iter;
    int start_t;
    int end_t;
    int real_run;
    int slack;
};


class SchedLog {
private:
    std::string fname;
    std::ofstream out_stream;

    // data related
    int exec_time;
    int deadline;
    int period;

    std::string create_header();
public:
    SchedLog(std::string _fname);
    bool append(sched_data sdata);
};

#endif
