#ifndef __DAG__
#define __DAG__

#include "core/pts.hpp"
#include "core/pt.hpp"
#include "core/task.hpp"
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <nlohmann/json.hpp>
#include <memory>
#include <chrono>
#include <mutex>
#include <iostream>

namespace rts {

struct task_node {
    volatile bool isFinished = false;
    bool isHead;
    bool isLeaf;
    double deadline;
    int index;
    std::string name;
    rts::Pt task;
    std::vector<task_node*> predecessors;
    std::vector<task_node*> successors;
};

class DAG {
public:
    DAG(rts::Pts _pts, nlohmann::json _js);
    rts::Pts pts;
    std::string name;
    std::vector<task_node> task_list;
    
    bool is_ready(struct task_node* _task);
    std::vector<task_node*> get_head_nodes();
    struct task_node* get_by_name(std::string _name);
    std::vector<task_node*> get_next_nodes(struct task_node* _task);
    struct task_node* get_by_index(int _index);
    std::string to_str();

    void msec_work(int _msec);
    void work(int _index);
};

} // namespace rts
#endif  // __DAG__