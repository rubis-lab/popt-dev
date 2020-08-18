#include <iostream>
#include "sched_exp.hpp"
using namespace std;

int main(int argc, char **argv) {
    if(argc < 2) {
        cout << "usage: ./omp exp1.json ts1.json" << endl;
        return -1;
    }
    cout << "main thread id: " << gettid() << endl;

    SchedExp se(argv[1], argv[2]);
    se.run();
    cout << "main dies: " << gettid() << endl;
    return 0;
}
