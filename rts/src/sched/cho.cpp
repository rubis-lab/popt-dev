#include "sched/cho.hpp"
namespace rts{

Cho::Cho() {
    return;
}

Cho::Cho(int _max_opt, nlohmann::json _js){
    max_opt = _max_opt;
    num_core = _js["num_core"];
    return;
}

std::string Cho::to_str() {
    std::string ret;
    ret += "Cho: num_core = " + std::to_string(num_core) + "\n";
    return ret;
}

void Cho::create_tolerance_table(Pts _pts) {
    tolerance_table.clear();
    unsigned int num_task = _pts.base_ts.tasks.size();
    for(unsigned int i = 0; i < num_task; i++) {
        std::unordered_map<unsigned int, double> thr_tolerance;
        for(unsigned int j = 1; j <= (unsigned int) max_opt; j++) {
            // only need to calculate once with thread of longest exec_time
            Thread thr = _pts.pt_list[i].tsdict[j][0];
            // calculate d - c for the first thread
            double lax = thr.deadline - thr.exec_time;
            // populate laxity dictionary 
            thr_tolerance.insert(std::pair<unsigned int,double>(j, lax));
        }
        tolerance_table.push_back(thr_tolerance);
    }
    return;
}

bool Cho::is_schedulable(Pts _pts) {
    create_tolerance_table(_pts);
    // Init
    _pts.popt_strategy = "single";
    _pts.serialize_pts();
    int num_task = _pts.pts_serialized.size();
    // popt starts with 1
    std::vector<int> selected_opt;
    for(unsigned int i= 0; i < (unsigned int) num_task; i++){
        selected_opt.push_back(1);
    }
    
    while(true){
        std::vector<double> i_sum_list;
        for(unsigned int i(0); i < (unsigned int) num_task; i++){
            // First thread used in calculating laxity
            Thread base_thr = _pts.pt_list.at(i).tsdict.at(selected_opt.at(i)).at(0);
            double i_sum = 0.0;
            // Iterate through the serialized threads and calculate interference
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

        std::vector<int> selected_opt_copy(selected_opt);
        // Increment popt
        for(unsigned int i = 0; i < (unsigned int) num_task; i++){
            while(selected_opt.at(i) < max_opt){
                if(i_sum_list.at(i) > tolerance_table.at(i)[selected_opt.at(i)] + 0.1){
                    selected_opt.at(i) += 1;
                } else {
                    break;
                }
            }
        }
        // break condition
        // if popt reached max_opt and i_sum > tolerance, return false;
        if(selected_opt == selected_opt_copy){
            for(unsigned int i = 0; i < (unsigned int) num_task; i++){
                if(selected_opt.at(i) == max_opt){
                    if(i_sum_list.at(i) > tolerance_table.at(i)[selected_opt.at(i)] + 0.1){
                        return false;
                    }
                }

            }
            _pts.popt_strategy = "custom";
            _pts.popt_list = selected_opt;
            _pts.serialize_pts();
            return true;
        }
    }

}
} // namespace rts
