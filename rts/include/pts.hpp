#ifndef __PTS_H__
#define __PTS_H__

#include "task_set.hpp"
#include "thread.hpp"
#include "pt.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

namespace rts{

class Pts{
public:
    ~Pts();
    static int pts_cnt;
    int id;
    std::string popt_strategy;
    std::vector<int> popt_list;
    TaskSet base_ts;
    std::vector<Pt> pt_list;
    std::vector<Thread> pts_serialized;
    Pts();
    void populate_pt_list();
    void serialize_pts();
    void to_str();
    void from_json();
};

}  // namespace rts
#endif  // __PTS_H__