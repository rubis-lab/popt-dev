#ifndef __STAT_H__
#define __STAT_H__

#include "core/task.hpp"
#include "core/task_set.hpp"
#include <math.h>
#include <iomanip>
#include <nlohmann/json.hpp>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace rts {

class Stat {
public:
    struct sched_data {
        int num_tot;
        int num_sched;
    };
    double x_min;
    double x_max;
    double x_inc;
    unsigned int x_size;
    std::vector<sched_data> raw_data;
    std::vector<double> normalized_data;
    Stat();
    Stat(nlohmann::json _js);
    std::string to_str();
    int conv_idx(double _idx);
    void add(double _idx, bool _data);
    void normalize();
    // void print_short();
    std::string crunch_minimal();
};

}  //namespace rts
#endif  // __STAT_H__