#include "core/pts.hpp"

namespace rts {
int Pts::_pts_cnt = 0;

Pts::Pts() {
    id = _pts_cnt++;
    return;
}

Pts::Pts(int _max_opt, TaskSet _base_ts) {
    max_opt = _max_opt;
    base_ts = _base_ts;
    populate_pt_list();
    return;
}

Pts::~Pts() {
    _pts_cnt--;
    return;
}

Pts::Pts(nlohmann::json _js) {
    // std::string ts_name = _js["name"];
    max_opt = _js["max_opt"];
    popt_strategy = _js["popt_strategy"];
    id = _js["id"];
    popt_list.clear();
    for(unsigned int i = 0; i < _js["popt_list"].size(); i++) {
        popt_list.push_back((int)_js["popt_list"][i]);
    }

    nlohmann::json ts_dict = _js["pts"];
    for(unsigned int i = 0; i < ts_dict.size(); i++) {
        nlohmann::json task_info = ts_dict[i];
        // task_info = { "name" : "", "options" : [], "deadline" : "", "period" : ""}
        int t_id = task_info["id"];
        // std::string t_name = task_info["name"];
        double t_deadline = task_info["deadline"];
        double t_period = task_info["period"];

        // thr_info =  { "option": 1, "exec_times": [100000, ...] }    
        nlohmann::json thr_info = task_info["options"][0];

        // option 1
        std::unordered_map<std::string, double> tattr;
        tattr["deadline"] = t_deadline;
        tattr["period"] = t_period;
        tattr["exec_time"] = thr_info["exec_times"][0];
        tattr["id"] = t_id;
        Task t = Task(tattr);
        base_ts.append(t);

        // create exec_times_table with a single option
        std::unordered_map<int, std::vector<double>> exec_times_table;
        std::vector<double> exec_times;
        exec_times.push_back(thr_info["exec_times"][0]);
        exec_times_table.insert(std::pair<int, std::vector<double>>(1, exec_times));

        // has more options
        if(task_info["options"].size() > 1) {
            for(unsigned int k = 1; k < task_info["options"].size(); k++) {
                // append additional tasks
                nlohmann::json thr_info = task_info["options"][k];
                tattr["exec_time"] = thr_info["exec_times"][0];
                // Task tt = Task(tattr);
                // base_ts.append(tt);
                // create exec_times_table, this time with multiple exec_times
                exec_times.clear();
                for(unsigned int l = 0; l < thr_info["exec_times"].size(); l++) {
                    exec_times.push_back(thr_info["exec_times"][l]);
                }
                exec_times_table.insert(std::pair<int, std::vector<double>>(k + 1, exec_times));
            }
        }
        // finally, create a pt
        pt_list.push_back(Pt(max_opt, t, exec_times_table, popt_list[i]));

    }

    // serialize created pts
    serialize_pts();

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
    if(popt_strategy == "single") {
        popt_list.clear();
        for(unsigned int i = 0; i < pt_list.size(); i++) {
            popt_list.push_back(1);
        }
    } else if(popt_strategy == "max") {
        popt_list.clear();
        for(unsigned int i = 0; i < pt_list.size(); i++) {
            popt_list.push_back(max_opt);
        }
    } else if(popt_strategy == "random") {
        popt_list.clear();
        for(unsigned int i = 0; i < pt_list.size(); i++) {
            int rand = (int)(std::rand() % max_opt + 1);
            popt_list.push_back(rand);
        }
    } else if(popt_strategy == "custom") {
        // Assume popt is initialized.
    } else {
        spdlog::error("Parallelization strategy not defined");
    }

    pts_serialized.clear();
    for(unsigned int i = 0; i < popt_list.size(); i++) {
        // threads of i-th task
        // with selected option: popt_list[i]
        std::vector<Thread> thr = pt_list[i].tsdict[popt_list[i]];
        // merge all threads into a single serialized task set
        pts_serialized.insert(pts_serialized.end(), thr.begin(), thr.end());
    }
}

std::string Pts::to_str() {
    std::string ret;
    for(unsigned int i =0; i < pts_serialized.size(); i++) {
        ret += pts_serialized[i].to_str() + "\n";
    }
    return ret;
}

} // namespace rts
