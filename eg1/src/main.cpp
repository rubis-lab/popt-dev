#include <iostream>
#include "sched_exp.hpp"
using namespace std;

int main(int argc, char **argv) {
    if(argc < 2) {
        cout << "usage: ./EG1 sample.json" << endl;
        return -1;
    }
    cout << "main thread id: " << gettid() << endl;
    //temp vector
    vector<int> temp;
    temp.push_back(1);
    temp.push_back(4);

    SchedExp se(argv[1], temp);
    se.run();
    cout << "main dies: " << gettid() << endl;
    return 0;
}
