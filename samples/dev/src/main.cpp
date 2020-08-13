#include <iostream>
#include <rts/task.hpp>
#include <rts/thread.hpp>
using namespace std;

int main(int argc, char **argv) {
    rts::Thread temp(1);
    // temp.set_task_id(1);
    // temp.set_popt(5);
    // temp.set_exec_time(10);
    // temp.set_deadline(10);
    // temp.set_period(50);
    // temp.task_print();
    return 0;
}
