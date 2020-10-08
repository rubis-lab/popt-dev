#include "core/dag.hpp"

namespace rts {
DAG::DAG(rts::Pts _pts, nlohmann::json _js) {
    pts = _pts;
    name = _js["name"];
    nlohmann::json js_task_list = _js["task_list"];
    for(unsigned int i = 0; i < js_task_list.size(); i++) {
        task_node* temp = new task_node;
        //temp->task = pts.pt_list.at(i);
        temp->name = js_task_list[i]["name"];
        temp->deadline = js_task_list[i]["deadline"];
        temp->index = js_task_list[i]["index"];
        task_list.push_back(*temp);
    }
    for(unsigned int i = 0; i < js_task_list.size(); i++) {
        if(js_task_list[i]["predecessors"].size() != 0) {
            for(unsigned int j = 0; j < js_task_list[i]["predecessors"].size(); j++){
                struct task_node* temp = get_by_index(js_task_list[i]["predecessors"][j]);
                if(temp != NULL) {
                    task_list.at(i).predecessors.push_back(temp);
                }
            }
        } else {
            task_list.at(i).is_head = true;
        }
        if(js_task_list[i]["successors"].size() != 0) {
            for(unsigned int j = 0; j < js_task_list[i]["successors"].size(); j++) {
                struct task_node* temp = get_by_index(js_task_list[i]["successors"][j]);
                if(temp != NULL) {
                    task_list.at(i).successors.push_back(temp);
                }
            }
        } else {
            task_list.at(i).is_leaf = true;
        }
    }
}

std::vector<task_node*> DAG::get_head_nodes() {
    std::vector<task_node*> temp;
    for(unsigned int i = 0; i < task_list.size(); i++) {
        if(task_list.at(i).predecessors.size() == 0) {
            temp.push_back(&task_list.at(i));
        }
    }
    return temp;
}

struct task_node* DAG::get_by_name(std::string _name) {
    task_node* temp = new task_node;
    for(unsigned int i = 0; i < task_list.size(); i++){
        if(task_list.at(i).name == _name){
            temp = &task_list.at(i);
            return temp;
        }
    }
    return NULL;
}

std::vector<task_node*> DAG::get_next_nodes(struct task_node* _task){
    std::vector<task_node*> temp;
    for(unsigned int i = 0; i < _task->successors.size(); i++) {
        temp.push_back(_task->successors.at(i));
    }
    return temp;
}
struct task_node* DAG::get_by_index(int _index) {
    task_node* temp = new task_node;
    for(unsigned int i = 0; i < task_list.size(); i++) {
        if(task_list.at(i).index == _index) {
            temp = &task_list.at(i);
            return temp;
        }
    }
    return NULL;
}

std::string DAG::to_str() {
    std::string ret;
    ret += "DAG name: " + name + "\n";
    for(unsigned int i = 0; i < task_list.size(); i++) {
        ret += task_list.at(i).task.to_str();
        ret += "\tnode deadline" + std::to_string(task_list.at(i).deadline) + "\n";
    }
    return NULL;
}

bool DAG::is_ready(struct task_node* _task) {
    if(_task->predecessors.empty()) {
        return true;
    } else {
        for(unsigned int i = 0; i < _task->predecessors.size(); i++) {
            if(!((_task->predecessors.at(i))->is_finished)) {
                return false;
            }
        }
        return true;
    }
}

bool DAG::is_in_free_list(struct task_node* _task) {
    if(_task->is_visited) {
        return false;
    } else if(_task->predecessors.empty()){
        return true;
    }
    else {
        for(unsigned int i = 0; i < _task->predecessors.size(); i++) {
            if(!((_task->predecessors.at(i))->is_visited)) {
                return false;
            }
        }
        return true;
    }
}

std::vector<int> DAG::get_topological_order() {
    // find the first head
    // can be modified
    std::vector<int> ret;
    std::queue<task_node*> q;
    for(unsigned int i = 0; i < get_head_nodes().size(); i++) {
        q.push(get_head_nodes().at(i));
    }
    while(ret.size() != task_list.size()) {
        task_node* q_pop = q.front();
        q.pop();
        q_pop->is_visited = true;
        ret.push_back(q_pop->index);
        for(unsigned int i = 0; i < q_pop->successors.size(); i++) {
            if(is_in_free_list(q_pop->successors.at(i))) {
                q.push(q_pop->successors.at(i));
            }
        }
    }
    return ret;
}

//usage: empty 2d vector, 1d vector, 0
void DAG::get_all_topological_order(std::vector<std::vector<int>> &_result, std::vector<int> prev) {
    std::vector<int> free_list = get_free_list();
    for(unsigned int i = 0; i < free_list.size(); i++) {
        get_by_index(free_list.at(i))->is_visited = true;
        std::vector<int> copy = prev;
        copy.push_back(free_list.at(i));
        get_all_topological_order(_result, copy);
        get_by_index(free_list.at(i))->is_visited = false;
    }
    if(free_list.size() == 0){
        // for(unsigned int i = 0; i < prev.size(); i++) {
        //     std::cout << prev.at(i);
        // }
        // std::cout << "\n";
        _result.push_back(prev);
    }
}

//TODO refactor using get_by_index
std::vector<int> DAG::get_free_list() {
    std::vector<int> res;
    for(unsigned int i = 0; i < task_list.size(); i++){
        if(is_in_free_list(&task_list.at(i))) {
            res.push_back(task_list.at(i).index);
        }
    }
    return res;
}

void DAG::reset_is_visited() {  
    for(unsigned int i = 0; i < task_list.size(); i++) {
        task_list.at(i).is_visited = false;
    }
    return;
}


//need to be removed later
void DAG::work(int _index) {
    //int64_t t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    while(!is_ready(&task_list.at(_index))){
        ;
    }
    int iter = 1;
    for(int task_iter = 0; task_iter < iter; task_iter++) {
        // create task data for logging
        // actual work    
        for(int y = 0; y < 100; y++) {
            msec_work((100 - y)/10);
        }
        //sched_yield();
    }  // task loop
    int64_t t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << "index " << _index << " end time: "
              << t1 << '\n';
    task_list.at(_index).is_finished = true;
    return;
}

void DAG::msec_work(int _msec) {
    // 600000 addition takes about 1msec on an 1.2GHz CPU
    unsigned int iter = 600000 * _msec;
    int sum = 0;
    for(unsigned int i = 0; i < iter; i++) {
        sum++;
    }
    return;
}

} // namespace rts
