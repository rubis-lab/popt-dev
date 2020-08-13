#include "pts.hpp"

namespace rts{
int Pts::_pts_cnt = 0;

Pts::Pts() {
    id = _pts_cnt++;
}

Pts::~Pts(){
    _pts_cnt--;
}

void Pts::populate_pt_list()
{
    for(Task t: base_ts.tasks){
        Pt temp(t);
        pt_list.push_back(temp);
    }
}

std::string Pts::to_str(){
    std::string t;
    for(size_t i(0); i < pts_serialized.size(); i++){
        t += pts_serialized.at(i).to_str();
    }    
    return t;
}

void Pts::from_json() {
    using json = nlohmann::json;
    std::ifstream ifs("filename.json");
    
    json j = json::parse(ifs);
    std::string tname = j["name"];
    std::map<std::string, double> task_input;

    for(int i=0; i<j["task_set"]->size(); i++) { 
        // j["task_set"][i] = { "name" : "", "options" : [], "deadline" : "", "period" : ""}
        double temp_deadline = j["task_set"][i]["deadline"];
        double temp_period = j["task_set"][i]["period"];

        for(int k=0; k<j["task_set"][i]["options"]->size(); k++]) {
            //j["task_set"][i]["options"][k] =  { "option": 1, "runtimes": [100000] }
            
            for(int m=0; m<j["task_set"][i]["options"][k]["runtimes"]->size(); m++) {
                //j["task_set"][i]["options"][k]["runtimes"][m] =  "33333 33335 33337"
                task_input["deadline"] = j["task_set"][i]["deadline"];
                task_input["period"] = j["task_set"][i]["period"];
                task_input["exec_time"] = j["task_set"][i]["options"][k]["runtimes"][m];
                Task temptask = Task(task_input);
                base_ts.addtask(temptask);

            }
        }
    }
    return;
}



} // namespace rts



// #include <iostream>
// #include <fstream>
// #include <nlohmann/json.hpp>

// int main(void) {
//     using json = nlohmann::json;

//     std::ifstream ifs("ts1.json");

//     // std::map<std::string, std::vector<int>> m = { {"a", {1, 2}}, {"b", {2, 3}} };
//     json j = json::parse(ifs);
//     std::cout << j << std::endl;
//     std::cout << j["name"] << std::endl;
//     std::cout << j["task_set"]<< std::endl;
//     std::cout << j["task_set"][0]["deadline"]<< std::endl;
//     return 0;
// }