#include <iostream>
#include <rts/task.hpp>
#include <rts/task_set.hpp>
#include <rts/thread.hpp>
#include <rts/pt.hpp>
#include <rts/pts.hpp>
#include <rts/stat.hpp>
#include "spdlog/spdlog.h"
//#include "spdlog/sinks/basic_file_sink.h"
using namespace std;

int main(int argc, char **argv) {
    // spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    // rts::Pts pts;
    // pts.from_json("../data/ts/ts1.json");
    rts::TaskSet _ts;
    rts::Stat stat(_ts);
    stat.add(0.5, true);
    stat.add(0.5, true);
    stat.add(0.5, true);
    stat.add(0.5, true);
    stat.add(0.5, true);
    stat.add(0.5, true);
    stat.add(0.5, false);
    stat.add(0.5, false);
    stat.add(0.5, false);
    stat.add(0.5, false);
    stat.print_short();
    return 0;
}
