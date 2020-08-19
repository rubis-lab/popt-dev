#ifndef __UNIFAST_H__
#define __UNIFAST_H__


#include <random>
#include <math.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include "gen.hpp"
#include "task.hpp"
#include "tsutil.hpp"
#include <nlohmann/json.hpp>
#include "spdlog/spdlog.h"

namespace rts{
class Uni: public Gen::Gen{
public:
    double min_period;
    double max_period;
    int num_task;
    double max_util;
    std::vector<double> divided_util;
    TaskSet ts;
    Uni();
    Uni(nlohmann::json _js);
    void unifast_divide(int _num_task, double _tot_util);
    Task next_task(double _util_candidate);
    TaskSet next_task_set();
    double frand(double _min, double _max);
    std::string to_str();
};
}  // namespace rts
#endif // __UNIFAST_H__