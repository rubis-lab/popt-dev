#include <rts/gen.hpp>
#include <rts/gfb.hpp>
#include <rts/task.hpp>
#include <rts/task_set.hpp>
#include <rts/thread.hpp>
#include <rts/pt.hpp>
#include <rts/pts.hpp>
#include <rts/stat.hpp>

#include <iostream>
#include "spdlog/spdlog.h"
//#include "spdlog/sinks/basic_file_sink.h"
using namespace std;

int main(int argc, char **argv) {
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^-%L-%$] [thread %t] %v");
    
    // set generator
    rts::gen_attr gattr;
    gattr.num_task = 4;
    gattr.seed = 0;
    gattr.min_exec_time = 10.0;
    gattr.max_exec_time = 20.0;
    gattr.min_deadline = 12.0;
    gattr.max_deadline = 22.0;
    gattr.min_period = 14.0;
    gattr.max_period = 24.0;
    gattr.implicit_deadline = 0;
    gattr.constrained_deadline = 0;

    rts::Gen gen(gattr);
    cout << gen.to_str() << endl;

    // set GFB

    rts::GFB gfb;
    


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
