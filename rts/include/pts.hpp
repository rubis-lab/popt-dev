#ifndef __PTS_H__
#define __PTS_H__

#include "task_set.hpp"
#include "thread.hpp"
#include "pt.hpp"
#include "spdlog/spdlog.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

namespace rts {

class Pts {
public:
    ~Pts();
    static int _pts_cnt;
    int id;
    int max_opt;
    std::string popt_strategy;
    std::vector<int> popt_list;
    TaskSet base_ts;
    std::vector<Pt> pt_list;
    std::vector<Thread> pts_serialized;
    Pts();
    void populate_pt_list();
    void serialize_pts();
    std::string to_str();
    void from_json(std::string _fname);
};

}  // namespace rts
#endif  // __PTS_H__
