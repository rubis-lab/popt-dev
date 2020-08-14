#include <rts/gen.hpp>
#include <rts/gfb.hpp>
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
    rts::Stat st(e.stat_attr);
    cout << st.to_str() << endl;
    rts::TSUtil tsu;

    for(int iter = 0; iter < e.iteration; iter++) {
        // generate task set
        rts::TaskSet ts = gen.next_task_set();
        cout << ts.to_str() << endl;
        double sum_util = tsu.sum_utilization(ts);

        // apply schedulability test
        bool sched_gfb = gfb.is_schedulable(ts);
        cout << sched_gfb << endl;
        
        st.add(sum_util, sched_gfb);    
    }

    // crunch output
    string res = st.crunch_minimal();
    cout << "finished run" << endl;
    cout << res << endl;
    return 0;
}
