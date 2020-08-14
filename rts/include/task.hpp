#ifndef __TASK_H__
#define __TASK_H__

#include <map>
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
    Task(std::map<std::string, double> _tattr);
    std::string to_str();
};

}  // namespace rts
#endif  // __TASK_H__
