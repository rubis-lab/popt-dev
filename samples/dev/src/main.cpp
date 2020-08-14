#include <rts/gen.hpp>
#include <rts/gfb.hpp>
#include <rts/task.hpp>
#include <rts/task_set.hpp>
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

    for(int iter = 0; iter < 10; iter++) {
        // generate task set
        rts::TaskSet ts = gen.next_task_set();
        cout << ts.to_str() << endl;

        // apply schedulability test
        bool sched_gfb = gfb.is_schedulable(ts);
        cout << sched_gfb << endl;
        // crunch output
    }
    return 0;
}
