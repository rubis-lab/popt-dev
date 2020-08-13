#ifndef __STAT_H__
#define __STAT_H__

#include <math.h>
#include <iomanip>
#include <iostream>
#include "task.hpp"
#include "task_set.hpp"
namespace rts{

class Stat{
public:
    Stat();
    Stat(TaskSet _ts);
    double min;
    double max;
    double inc;
    int size;
    std::vector<Task> _tasks;
    std::vector<std::tuple<int, int>> raw_data;
    std::vector<double> norm_data;
    int conv_idx(double _idx);
    void add(double _idx, bool _data);
    void normalize();
    std::string to_str();
    void print_short();
    void print_minimal();
};

} //namespace rts
#endif // __STAT_H__