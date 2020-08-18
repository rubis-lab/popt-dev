#ifndef __TASK_H__
#define __TASK_H__

#include <unordered_map>
#include <string>

namespace rts {

class Task {
private: 
    static int _count;
public:
    int id;
    double exec_time;
    double deadline;
    double period;
    Task();
    Task(std::unordered_map<std::string, double> _tattr);
    std::string to_str();
    bool operator==(const Task&);
    bool operator!=(const Task&);
};

}  // namespace rts
#endif  // __TASK_H__
