#ifndef __CHO_H__
#define __CHO_H__

#include "task_set.hpp"
#include "pts.hpp"
#include "thread.hpp"
#include "tsutil.hpp"
#include <unordered_map>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

namespace rts{
class Cho{
public:
    int num_core;
    int max_opt;
    TSUtil tsutil;
    std::vector<std::unordered_map<int, double>> tolerance_table;
    Cho();
    Cho(int _max_opt, nlohmann::json _js);
    void create_tolerance_table(Pts _pts);
    bool is_schedulable(Pts _pts);
    std::string to_str();
};
}  // namespace rts
#endif // __CHO_H__
