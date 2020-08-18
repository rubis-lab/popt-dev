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

void Cho::create_tolerance_table(Pts _pts) {
    std::cout << "check a0" << std::endl;
    tolerance_table.clear();
    unsigned int num_task = _pts.base_ts.tasks.size();
    std::cout << "num_task: " << num_task << std::endl;
    for(unsigned int i = 0; i < num_task; i++) {
        std::cout << "i: " << i << std::endl;
        std::vector<double> thr_tolerance;
        //option 0 not used
        thr_tolerance.push_back(-1.0);
        for(unsigned int j = 0; j < (unsigned int) max_opt; j++) {
            std::cout << "j: " << j << std::endl;
            // 
            Thread thr = _pts.pt_list[i].tsdict[j + 1][0];
            std::cout << "thr: " << thr.to_str() << std::endl;
            // calculate d - c for the first thread
            double lax = thr.deadline - thr.exec_time;
            thr_tolerance.push_back(lax);
        }
        std::cout << "check a1" << std::endl;
        tolerance_table.push_back(thr_tolerance);
        std::cout << "check a2" << std::endl;
    }
    return;
}

bool Cho::is_schedulable(Pts _pts) {
    create_tolerance_table(_pts);
    // Init
    std::cout << "check a" << std::endl;
    _pts.popt_strategy = "single";
    _pts.serialize_pts();
    std::cout << "check b" << std::endl;
    int num_task = _pts.pts_serialized.size();
    std::vector<int> selected_opt;
    for(unsigned int i(0); i < (unsigned int) num_task; i++){
        selected_opt.push_back(1);
    }
    std::cout << "check c" << std::endl;

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
        std::cout << "first part done" << std::endl;
        std::vector<int> selected_opt_copy(selected_opt);
        for(unsigned int i(0); i < (unsigned int) num_task; i++){
            while(selected_opt.at(i) < max_opt){
                if(i_sum_list.at(i) > tolerance_table.at(i).at(selected_opt.at(i)) + 0.1){
                    selected_opt.at(i) += 1;
                } else {
                    break;
                }
            }
        }
        //break condition
        std::cout << (selected_opt == selected_opt_copy)<< std::endl;
        for(unsigned int i = 0; i < selected_opt.size(); i ++){
            std::cout << selected_opt_copy.at(i) << " " << selected_opt.at(i) << std::endl;
        }
        if(selected_opt == selected_opt_copy){
            for(unsigned int i(0); i < (unsigned int) num_task; i++){
                std::cout << "check 10: " << i << std::endl;  
                if(selected_opt.at(i) == max_opt){
                    std::cout << "check 11: " << std::endl;
                    if(i_sum_list.at(i) > tolerance_table.at(i).at(selected_opt.at(i)) + 0.1){
                        std::cout << "returning false" << std::endl;
                        return false;
                    }
                }

            }
            std::cout << "returning true" << std::endl;
            _pts.popt_strategy = "custom";
            _pts.popt_list = selected_opt;
            _pts.serialize_pts();
            std::cout << "info" << std::endl;
            return true;
        }
    }

}
} // namespace rts
