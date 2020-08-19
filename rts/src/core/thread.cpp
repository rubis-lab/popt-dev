#include "core/thread.hpp"

namespace rts {
Thread::Thread(int _tid) {
    tid = _tid;
    to_str();
}

std::string Thread::to_str(){
    return std::to_string(tid) + "\t" + Task::to_str();
}

bool Thread::operator==(const Thread& other){
    if(id == other.id && exec_time == other.exec_time &&
        deadline == other.deadline && period == other.period && tid == other.tid){
            return true;
        } else {
            return false;
        }
}

bool Thread::operator!=(const Thread& other){
    return !(*this == other);
}

}  // namespace rts