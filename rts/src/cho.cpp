#include "cho.hpp"
namespace rts{

Cho::Cho() {
    return;
}

Cho::Cho(nlohmann::json _js): max_opt(4){
    //max_opt = _js["max_opt"];
    num_core = _js["num_core"];
    return;
}

std::string Cho::to_str() {
    std::string ret;
    ret += "Cho: num_core = " + std::to_string(num_core) + "\n";
    return ret;
}

void Cho::create_ip_table(Pts _pts) {
    unsigned int num_task = _pts.base_ts.tasks.size();
    for(unsigned int i(0); i < num_task; i++){
        //option 0
        std::vector<double> temp;
        temp.push_back(-1.0);
        ip_table.push_back(temp);
        for(unsigned int j(0); j < (unsigned int) max_opt; j++) {
            std::cout << "hi" << std::endl;
            std::vector<Thread> thrs_i_oj = _pts.pt_list.at(i).tsdict.at(j+1);
            std::vector<double> lax;
            for(unsigned int k(0); k < thrs_i_oj.size(); k++) {
                lax.push_back(thrs_i_oj.at(k).deadline - thrs_i_oj[k].exec_time);
            }
            ip_table.at(i).push_back(*std::min_element(lax.begin(), lax.end()));
        }
    }
}

bool Cho::is_schedulable(Pts _pts) {
    create_ip_table(_pts);
    
    // Init
    _pts.popt_strategy = "single";
    _pts.serialize_pts();
    int num_task = _pts.pts_serialized.size();
    std::vector<int> selected_opt;
    for(unsigned int i(0); i < (unsigned int) num_task; i++){
        selected_opt.push_back(1);
    }

    while(true){
        std::vector<double> i_sum_list;
        for(unsigned int i(0); i < (unsigned int) num_task; i++){
            Thread base_thr = _pts.pt_list.at(i).tsdict.at(selected_opt.at(i)).at(0);
            double i_sum = 0.0;
            for(unsigned int j(0); j < _pts.pts_serialized.size(); j++){
                Thread inter_thr = _pts.pts_serialized.at(j);
                if(base_thr == inter_thr){
                    continue;
                }
                double i_sum_tmp = tsutil.workload_in_interval_edf(inter_thr, base_thr.deadline);
                i_sum += std::max(0.0, std::min(i_sum_tmp, base_thr.deadline - base_thr.exec_time + 1.0));
            }
            i_sum = floor(i_sum/num_core);
            i_sum_list.push_back(i_sum);
        }

        std::vector<int> selected_opt_copy = selected_opt;
        for(unsigned int i(0); i < (unsigned int) num_task; i++){
            while(selected_opt.at(i) < max_opt){
                if(i_sum_list.at(i) > ip_table.at(i).at(selected_opt.at(i)) + 0.1){
                    selected_opt.at(i) += 1;
                } else {
                    break;
                }
            }
        }
        //break condition
        if(selected_opt == selected_opt_copy){
            for(unsigned int i(0); i < (unsigned int) num_task; i++){
                if(selected_opt.at(i) == max_opt){
                    if(i_sum_list.at(i) > ip_table.at(i).at(selected_opt.at(i)) + 0.1){
                        return false;
                    }
                }
            }
        }
        _pts.popt_strategy = "custom";
        _pts.popt_list = selected_opt;
        _pts.serialize_pts();
        return true;
    }
}
} // namespace rts
