#include <iostream>
#include <rts/task.hpp>
using namespace std;

int main(int argc, char **argv) {
    // if(argc < 2) {
    //     cout << "usage: ./dev " << endl;
    //     return -1;
    // }
    cout << "(dev)" << endl;
    rts::task_print(1);
    return 0;
}
