#include "thread.hpp"

namespace rts {
Thread::Thread(int _tid) {
    tid = _tid;
    to_str();
}

void Thread::to_str(){
    std::cout << "Thread id: " << tid << "\t";
}

}  // namespace rts