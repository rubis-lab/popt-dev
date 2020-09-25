#include "core/dag.hpp"

namespace rts {
DAG::DAG(rts::Pts _pts, nlohmann::json _js) {
    pts = _pts;
    name = _js["name"];
    nlohmann::json js_task_list = _js["task_list"];
    for(unsigned int i = 0; i < js_task_list.size(); i++) {
        task_node* temp = new task_node;
        temp->task = pts.pt_list.at(i);
        temp->name = js_task_list[i]["name"];
        temp->deadline = js_task_list[i]["deadline"];
        temp->index = js_task_list[i]["index"];
        task_list.push_back(*temp);
        std::cout << "pushed back task_node" << std::endl;
    }
    for(unsigned int i = 0; i < js_task_list.size(); i++) {
        std::cout << "task " << i+1 << std::endl;
        if(js_task_list[i]["predecessors"].size() != 0) {
            for(unsigned int j = 0; j < js_task_list[i]["predecessors"].size(); j++){
                struct task_node* temp = get_by_index(js_task_list[i]["predecessors"][j]);
                if(temp != NULL) {
                    task_list.at(i).predecessors.push_back(temp);
                }
            }
        } else {
            task_list.at(i).isHead = true;
        }
        if(js_task_list[i]["successors"].size() != 0) {
            for(unsigned int j = 0; j < js_task_list[i]["successors"].size(); j++) {
                struct task_node* temp = get_by_index(js_task_list[i]["successors"][j]);
                if(temp != NULL) {
                    task_list.at(i).successors.push_back(temp);
                }
            }
        } else {
            task_list.at(i).isLeaf = true;
        }
    }
}

bool DAG::is_ready(struct task_node* _task) {
    if(_task->predecessors.empty()) {
        return true;
    } else {
        for(unsigned int i = 0; i < _task->predecessors.size(); i++) {
            if(!((_task->predecessors.at(i))->isFinished)) {
                return false;
            }
        }
        return true;
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


//need to be removed later
void DAG::work(int _index) {
    int64_t t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
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
    task_list.at(_index).isFinished = true;
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
