#include "task_set.hpp"

namespace rts {

TaskSet::TaskSet() {
}

std::string TaskSet::to_str() {
    std::string t;
    for(size_t i(0); i < tasks.size(); i++){
        t+=tasks.at(i).to_str();
    }
}
}  // namespace rts
