#include "sched_core.hpp"
#include <rts/exp.hpp>
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
    if(argc < 2) {
        cout << "usage: ./omp exp1.json ts1.json" << endl;
        return -1;
    }
    cout << "main thread id: " << gettid() << endl;

    rts::Exp e(argv[1]);
    cout << e.to_str() << endl;

    cout << "main dies: " << gettid() << endl;
    return 0;
}
