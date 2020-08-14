#include <rts/gen.hpp>
#include <rts/gfb.hpp>
#include <rts/bcl.hpp>
#include <rts/task.hpp>
#include <rts/task_set.hpp>
#include <rts/tsutil.hpp>
#include <rts/thread.hpp>
#include <rts/pt.hpp>
#include <rts/pts.hpp>
#include <rts/stat.hpp>
#include <rts/exp.hpp>

#include <iostream>
#include "spdlog/spdlog.h"
//#include "spdlog/sinks/basic_file_sink.h"
using namespace std;

int main(int argc, char **argv) {
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^-%L-%$] [thread %t] %v");

    string j_in = "../data/exp/exp1.json";
    rts::Exp e(j_in);
    cout << e.to_str() << endl;
    rts::Gen gen(e.gen_attr);
    cout << gen.to_str() << endl;
    rts::GFB gfb(e.sched_test_attr);
    cout << gfb.to_str() << endl;
    rts::BCL bcl(e.sched_test_attr);
    cout << bcl.to_str() << endl;

    rts::Stat gfb_st(e.stat_attr);
    cout << gfb_st.to_str() << endl;
    rts::Stat bcl_st(e.stat_attr);
    cout << bcl_st.to_str() << endl;
    rts::TSUtil tsu;

    for(int iter = 0; iter < e.iteration; iter++) {
        // generate task set
        rts::TaskSet ts = gen.next_task_set();
        double sum_util = tsu.sum_utilization(ts);

        // apply schedulability test
        bool sched_gfb = gfb.is_schedulable(ts);
        gfb_st.add(sum_util, sched_gfb);

        bool sched_bcl = bcl.is_schedulable(ts);
        bcl_st.add(sum_util, sched_gfb);
    }

    // crunch output
    string gfb_res = gfb_st.crunch_minimal();
    string bcl_res = bcl_st.crunch_minimal();
    cout << "GFB" << endl;
    cout << gfb_res << endl;
    cout << "BCL" << endl;
    cout << bcl_res << endl;
    return 0;
}
