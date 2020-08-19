#include "core/pts.hpp"

namespace rts {
int Pts::_pts_cnt = 0;

Pts::Pts() {
    id = _pts_cnt++;
    return;
}

Pts::~Pts() {
    _pts_cnt--;
    return;
}

Pts::Pts(int _max_opt, TaskSet _base_ts) {
    max_opt = _max_opt;
    base_ts = _base_ts;
    populate_pt_list();
    return;
}

void Pts::populate_pt_list() {
    // add tasks to pt_list to be serialized
    for(Task t: base_ts.tasks) {
        Pt p(max_opt, t);
        pt_list.push_back(p);
    }
    return;
}

void Pts::serialize_pts() {
    popt_list.clear();
    pts_serialized.clear();

    if(popt_strategy == "single") {
        for(unsigned int i = 0; i < pt_list.size(); i++) {
            popt_list.push_back(1);
        }
    } else if(popt_strategy == "max") {
        for(unsigned int i = 0; i < pt_list.size(); i++) {
            popt_list.push_back(max_opt);
        }
    } else if(popt_strategy == "random") {
        for(unsigned int i = 0; i < pt_list.size(); i++) {
            int rand = (int)(std::rand() % max_opt + 1);
            popt_list.push_back(rand);
        }
    } else if(popt_strategy == "custom") {
        // Assume popt is initialized.
    } else {
        spdlog::error("Parallelization strategy not defined");
    }
    for(unsigned int i = 0; i < popt_list.size(); i++) {
        // threads of i-th task
        // with selected option: popt_list[i]
        std::vector<Thread> thr = pt_list[i].tsdict[popt_list[i]];
        // merge all threads into a single serialized task set
        pts_serialized.insert(pts_serialized.end(), thr.begin(), thr.end());
    }
}

std::string Pts::to_str(){
    std::string t;
    for(unsigned int i =0; i < (unsigned int) pts_serialized.size(); i++) {
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
    for(unsigned int i = 0; i < jf["task_set"].size(); i++) {
        json task_info = jf["task_set"][i];
        // task_info = 
        //      { "name" : "", "options" : [], "deadline" : "", "period" : ""}
        std::string t_name = task_info["name"];
        double t_deadline = task_info["deadline"];
        double t_period = task_info["period"];

        for(unsigned int k = 0; k < task_info["options"].size(); k++) {
            json thr_info = task_info["options"][k];
            // thr_info = 
            //      { "option": 1, "runtimes": [100000] }
            for(unsigned int m = 0; m < thr_info["runtimes"].size(); m++) {
                //thr_info["runtimes"][m] =  "33333 33335 33337"
                std::unordered_map<std::string, double> tattr;
                tattr["deadline"] = t_deadline;
                tattr["period"] = t_period;
                tattr["exec_time"] = thr_info["runtimes"][m];
                Task t = Task(tattr);
                base_ts.append(t);
            }
        }
    }
    return;
}



} // namespace rts
