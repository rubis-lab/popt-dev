#include <iostream>
#include <rts/task.hpp>
#include <rts/thread.hpp>
#include <rts/pt.hpp>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
using namespace std;

int main(int argc, char **argv) {
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    rts::Task temp;
    rts::Task temp2;
    // temp.set_task_id(1);
    // temp.set_popt(5);
    // temp.set_exec_time(10);
    // temp.set_deadline(10);
    // temp.set_period(50);
    // temp.task_print();
    return 0;
}
