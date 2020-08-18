#include "pts.hpp"

namespace rts {
int Pts::_pts_cnt = 0;

Pts::Pts() {
    max_opt = 4;
    id = _pts_cnt++;
    base_ts = TaskSet();
}

Pts::~Pts() {
    _pts_cnt--;
}

void Pts::populate_pt_list() {
    for(Task t: base_ts.tasks) {
        Pt temp(t);
        pt_list.push_back(temp);
    }
}

void Pts::serialize_pts() {
    popt_list.clear();
    pts_serialized.clear();
    if(popt_strategy == "single") {
        for(unsigned int i(0); i < pt_list.size(); i++) {
            popt_list.push_back(1);
        }
    } else if(popt_strategy == "max") {
        for(unsigned int i(0); i < pt_list.size(); i++) {
            popt_list.push_back(max_opt);
        }
    } else if(popt_strategy == "random") {
        for(unsigned int i(0); i < pt_list.size(); i++) {
            int rand = std::rand() % max_opt + 1;
            popt_list.push_back(rand);
        }
    } else if(popt_strategy == "custom") {
        // Assume popt is initialized.
    } else{
        spdlog::error("Parallelization strategy not defined");
    }
    for(unsigned int i = 0; i < popt_list.size(); i++) {
	int popt_i = popt_list[i];
	std::cout << "popt_i: " << popt_list[i] << std::endl;
	std::vector<Thread> tmp = pt_list[i].tsdict[popt_i];
	pts_serialized.insert(pts_serialized.end(), tmp.begin(), tmp.end());
    }
}

std::string Pts::to_str(){
    std::string t;
    for(size_t i(0); i < (size_t) pts_serialized.size(); i++){
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
    for(size_t i = 0; i < jf["task_set"].size(); i++) {
        json task_info = jf["task_set"][i];
        // task_info = 
        //      { "name" : "", "options" : [], "deadline" : "", "period" : ""}
        std::string t_name = task_info["name"];
        double t_deadline = task_info["deadline"];
        double t_period = task_info["period"];

        for(size_t k = 0; k < task_info["options"].size(); k++) {
            json thr_info = task_info["options"][k];
            // thr_info = 
            //      { "option": 1, "runtimes": [100000] }
            for(size_t m = 0; m < thr_info["runtimes"].size(); m++) {
                //thr_info["runtimes"][m] =  "33333 33335 33337"
                std::unordered_map<std::string, double> tattr;
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
