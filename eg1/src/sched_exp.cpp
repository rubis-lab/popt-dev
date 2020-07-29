#include "sched_exp.hpp"

using namespace std;
using json = nlohmann::json;

SchedExp::SchedExp(string fname) {
    parse_config(fname);
    cout << exp_name << endl;
}

thr_arg SchedExp::parse_config(string fname) {
    ifstream i(fname);
    json j;
    i >> j;
    exp_name = j["exp_name"];
    num_task = j["tasks"].size();
    cout << "num_task: " << num_task << endl;

    thr_arg targ;
    return targ;
}

bool SchedExp::run() {
    // two task example
    // int num_task = 2;
    // vector<thread> thrs;
    // for(int i = 0; i < num_task; i++) {
    //     struct thr_arg targ;
    //     targ.task_id = i;
    //     targ.thr_id = 0;
    //     targ.parent = gettid();
    //     targ.exec_time = 10000;
    //     targ.deadline = 15000;
    //     targ.period = 20000;
    //     thrs.push_back(thread(routine_deadline, targ));
    // }
    
    // for(thread &t : thrs)
    //     t.join();
    return true;
}