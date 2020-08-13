#include "thread.hpp"

namespace rts {
Thread::Thread(int _tid) {
    tid = _tid;
    to_str();
}

std::string Thread::to_str(){
    return std::to_string(tid) + "\t" + Task::to_str();
}

}  // namespace rts