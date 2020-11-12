#include <rts/gen/egen.hpp>
#include <rts/sched/gfb.hpp>
#include <rts/sched/bcl.hpp>
#include <rts/core/task_set.hpp>
#include <rts/op/tsutil.hpp>
#include <rts/op/stat.hpp>
#include <rts/op/exp.hpp>
#include <rts/sched/cho.hpp>
#include <rts/gen/unifast.hpp>
#include <iostream>
#include "spdlog/spdlog.h"
//#include "spdlog/sinks/basic_file_sink.h"
#include <nlohmann/json.hpp>
using namespace std;

int main(int argc, char **argv) {
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^-%L-%$] [thread %t] %v");

    std::string current_exec_name = argv[0];
    rts::Exp e(argv[1]);
    std::ifstream _jf(argv[2]);
    nlohmann::json jf = nlohmann::json::parse(_jf);
    // string j_in = "../data/exp/exp1.json";
    // rts::Exp e(j_in);
    cout << e.to_str() << endl;
    int max_opt = e.para_attr["max_opt"];

    // Generators
    // rts::Gen gen(e.gen_attr);
    // cout << gen.to_str() << endl;
    // rts::Egen egen(e.gen_attr);
    // cout << egen.to_str() << endl;
    rts::Uni uni(e.gen_attr);
    cout << uni.to_str() << endl;

    // Schedulability Tests
    rts::GFB gfb(e.sched_test_attr);
    cout << gfb.to_str() << endl;
    rts::BCL bcl(e.sched_test_attr);
    cout << bcl.to_str() << endl;
    rts::BCL bcl_slack(e.sched_test_attr);
    cout << bcl_slack.to_str_slack() << endl;
    rts::Cho cho(max_opt, e.sched_test_attr);
    cout << cho.to_str() << endl;

    rts::Stat gfb_st(e.stat_attr);
    cout << gfb_st.to_str() << endl;
    rts::Stat bcl_st(e.stat_attr);
    cout << bcl_st.to_str() << endl;
    rts::Stat bcl_st_slack(e.stat_attr);
    cout << bcl_st_slack.to_str() << endl;
    rts::Stat cho_st(e.stat_attr);
    cout << cho_st.to_str() << endl;
    rts::TSUtil tsu;

    for(int iter = 0; iter < e.iteration; iter++) {
        // generate task set
        // rts::TaskSet ts = gen.next_task_set();
        // rts::TaskSet ts = egen.next_task_set();
        rts::TaskSet ts = uni.next_task_set();
        double sum_util = tsu.sum_utilization(ts);
        rts::Pts pts(jf, e);
        pts.popt_strategy = "single";
        pts.serialize_pts();
        // apply schedulability test
        bool sched_gfb = gfb.is_schedulable(ts);
        gfb_st.add(sum_util, sched_gfb);
        bool sched_bcl = bcl.is_schedulable(ts);
        bcl_st.add(sum_util, sched_bcl);
        bool sched_bcl_slack = bcl.is_schedulable_slack(ts);
        bcl_st_slack.add(sum_util, sched_bcl_slack);

        //exp?
        // bool sched_cho = cho.is_schedulable(pts, e);
        // cho_st.add(sum_util, sched_cho);
    }
    // crunch output
    string gfb_res = gfb_st.crunch_minimal();
    string bcl_res = bcl_st.crunch_minimal();
    string bcl_res_slack = bcl_st_slack.crunch_minimal();
    string cho_res = cho_st.crunch_minimal();
    cout << "GFB" << endl;
    cout << gfb_res << endl;
    cout << "BCL" << endl;
    cout << bcl_res << endl;
    cout << "BCL_SLACK" << endl;
    cout << bcl_res_slack << endl;
    // cout << "Cho" << endl;
    // cout << cho_res << endl;
    return 0;
}
