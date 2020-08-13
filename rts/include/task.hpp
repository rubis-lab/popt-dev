#ifndef __TASK_H__
#define __TASK_H__

#include <iostream>
#include <map>
namespace rts {

class Task {
public:
    int id;
    double exec_time;
    double deadline;
    double period;
    Task();
    Task(std::map<std::string, double> _tattr);
    void to_str();
};

}  // namespace rts
#endif  // __TASK_H__
