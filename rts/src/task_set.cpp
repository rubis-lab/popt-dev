#include "task_set.hpp"
using json = nlohmann::json;

namespace rts {
    TaskSet::TaskSet(){
        //task_set_print();
    }
    
    TaskSet::TaskSet(std::string fname, std::vector<int> popt): popt_vec(popt){
        // parse_config(fname);
        // task_set_print();
    }

    void TaskSet::parse_config(std::string fname){
        std::ifstream inputFile(fname);
        json json;
        inputFile >> json;

        exp_name = json["exp_name"];
        int num_task = json["task_set"].size();
        for(size_t i(0); i < num_task; i ++){
            Task temp;
            temp.set_task_id(i);
            temp.set_popt(popt_vec.at(i));
            temp.set_exec_time(json["task_set"][i]["options"][popt_vec.at(i)-1]["runtimes"][0]);
            temp.set_deadline(json["task_set"][i]["deadline"]);
            temp.set_period(json["task_set"][i]["period"]);
            task_list.push_back(temp);
        }
    } 

    void TaskSet::task_set_print() {
        std::cout << "task_set_print()" << std::endl;
        if(task_list.size() == 0){
            std::cout << "TaskSet attributes not yet initialized" << std::endl;
        } else {
            std::cout << "Experiment name: " << exp_name << std::endl;
            // cout << "Task Set Length: " << task_list.size() << 
            //     " Total Utilization: " << sum_task_util() << endl;
            for(size_t i(0); i < task_list.size(); i++){
                task_list.at(i).task_print();
            }
        }
    }

    std::vector<Task> TaskSet::get_task_list(){
        return task_list;
    }

    std::vector<int> TaskSet::get_popt_vec(){
        return popt_vec;
    }

    void TaskSet::set_task_list(std::vector<Task> tl){
        if(tl.size() == 0){
            std::cout << "Task vector is empty; not intialized" << std::endl;
        } else {
            task_list = tl;
        }
    }
    
    void TaskSet::set_popt_vec(std::vector<int> pv){
        if(pv.size() == 0){
            std::cout << "P.opt vector is empty; not intialized" << std::endl;
        } else {
            popt_vec = pv;
        }
    }
}
