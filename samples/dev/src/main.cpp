#include <iostream>
#include <rts/task.hpp>
#include <rts/task_set.hpp>
#include <rts/thread.hpp>
#include <rts/pt.hpp>
#include <rts/pts.hpp>
#include <rts/stat.hpp>
#include <rts/gen.hpp>
#include "spdlog/spdlog.h"
//#include "spdlog/sinks/basic_file_sink.h"
using namespace std;

int main(int argc, char **argv) {
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    rts::gen_attr gattr;
    gattr.num_task = 4;
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

    // rts::Pts pts;
    // pts.from_json("../data/ts/ts1.json");
    // rts::TaskSet _ts;
    // rts::Stat stat(_ts);
    // stat.add(0.5, true);
    // stat.add(0.5, true);
    // stat.add(0.5, true);
    // stat.add(0.5, true);
    // stat.add(0.5, true);
    // stat.add(0.5, true);
    // stat.add(0.5, false);
    // stat.add(0.5, false);
    // stat.add(0.5, false);
    // stat.add(0.5, false);
    // stat.print_short();
    return 0;
}
