#include <iostream>
#include "sched_exp.hpp"
using namespace std;

int main(int argc, char **argv) {
    if(argc < 2) {
        cout << "usage: ./EG1 sample.json" << endl;
        return -1;
    }
    cout << "main thread id: " << gettid() << endl;
    SchedExp se(argv[1], 4);
    se.run();
    cout << "main dies: " << gettid() << endl;
    return 0;
}
