#include "pts.hpp"

namespace rts{
int Pts::_pts_cnt = 0;

Pts::Pts() {
    id = _pts_cnt++;
    base_ts = TaskSet();
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

void Pts::from_json(std::string _fname) {
    using json = nlohmann::json;
    std::ifstream json_file(_fname);
    
    json jf = json::parse(json_file);
    std::string ts_name = jf["name"];

    json ts_dict = jf["task_set"];
    for(int i = 0; i < jf["task_set"].size(); i++) {
        json task_info = jf["task_set"][i];
        // task_info = 
        //      { "name" : "", "options" : [], "deadline" : "", "period" : ""}
        std::string t_name = task_info["name"];
        double t_deadline = task_info["deadline"];
        double t_period = task_info["period"];

        for(int k = 0; k < task_info["options"].size(); k++) {
            json thr_info = task_info["options"][k];
            // thr_info = 
            //      { "option": 1, "runtimes": [100000] }
            for(int m = 0; m < thr_info["runtimes"].size(); m++) {
                //thr_info["runtimes"][m] =  "33333 33335 33337"
                std::map<std::string, double> tattr;
                tattr["deadline"] = task_info["deadline"];
                tattr["period"] = task_info["period"];
                tattr["exec_time"] = thr_info["runtimes"][m];
                Task t = Task(tattr);
                base_ts.append(t);
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