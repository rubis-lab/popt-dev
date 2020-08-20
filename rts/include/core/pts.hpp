#ifndef __PTS_H__
#define __PTS_H__

#include "core/task_set.hpp"
#include "core/task.hpp"
#include "core/pt.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <nlohmann/json.hpp>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace rts {

class Pts {
public:
    int id;
    static int _pts_cnt;
    int max_opt;
    TaskSet base_ts;

    std::string popt_strategy;
    std::vector<int> popt_list;

    std::vector<Pt> pt_list;
    std::vector<Thread> pts_serialized;
    Pts();
    Pts(int _max_opt, TaskSet _base_ts);
    ~Pts();
    Pts(nlohmann::json _js);
    void populate_pt_list();
    void serialize_pts();
    std::string to_str();
};

}  // namespace rts
#endif  // __PTS_H__
