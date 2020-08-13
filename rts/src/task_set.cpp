#include "task_set.hpp"
using json = nlohmann::json;
using namespace std;
namespace rts {
    TaskSet::TaskSet(string fname, vector<int> popt){
        parse_config(fname);
        popt_vec = popt;
        task_set_print();
    }

    void TaskSet::parse_config(string fname){
        ifstream inputFile(fname);
        json json;
        inputFile >> json;

        exp_name = json["exp_name"];
        int num_task = json["task_set"].size();
        for(int i(0); i < num_task; i ++){
            Task temp;
            temp.set_task_id(i);
            temp.set_popt(popt_vec.at(i));
            temp.set_exec_time(json["task_set"][i]["options"][popt_vec.at(i)-1]["runtimes"][0]);
            temp.set_deadline(json["task_set"][i]["deadline"]);
            temp.set_period(json["task_set"][i]["period"]);
            task_list.push_back(temp);
        }
    } 

    int TaskSet::task_set_print() {
        cout << "Experiment name: " << exp_name << endl;
        // cout << "Task Set Length: " << task_list.size() << 
        //     " Total Utilization: " << sum_task_util() << endl;
        for(int i(0); i < task_list.size(); i++){
            task_list.at(i).task_print();
        }
    }

    vector<Task> TaskSet::get_task_list(){
        return task_list;
    }
}
