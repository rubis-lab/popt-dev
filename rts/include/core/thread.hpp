#ifndef __THR_H__
#define __THR_H__

#include "core/task.hpp"

namespace rts {

class Thread : public Task::Task {
public:
    int tid;
    Thread(int _tid);
    std::string to_str();
    bool operator==(const Thread&);
    bool operator!=(const Thread&);
};

}  // namespace rts
#endif  // __THR_H__
