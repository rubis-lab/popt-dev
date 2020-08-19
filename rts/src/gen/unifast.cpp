#include "gen/unifast.hpp"

namespace rts{
Uni::Uni(): Gen() {

}

Uni::Uni(nlohmann::json _js): Gen(_js){
    min_period = _js["min_period"];
    max_period = _js["max_period"];
    num_task = _js["num_task"];
    max_util = (double) _js["num_core"];
}

void Uni::unifast_divide(int _num_task, double _tot_util){
    divided_util.clear();
    double util_sum = frand(0.0, _tot_util);
    //std::cout << "util_sum:" << util_sum << std::endl;
    for(unsigned int i = 0; i < (unsigned int) (_num_task - 1); i++){
        double temp_util = util_sum * pow(
            frand(0.0, 1.0), (1.0 / (_num_task - i)));
        divided_util.push_back(util_sum - temp_util);
        //std::cout << "pushed back:" << util_sum - temp_util << std::endl;
        util_sum = temp_util;
        //std::cout << "temp_util:" << temp_util << std::endl;
    }
    divided_util.push_back(util_sum);
    //  std::cout << "\n";
} 

Task Uni::next_task(double _util_candidate){
    double cand_util = _util_candidate;
    double period = frand(min_period, max_period);
    double exec_time = floor(period*cand_util);
    
    std::unordered_map<std::string, double> _tattr;
    _tattr.insert(std::pair<std::string, double>("exec_time", exec_time));
    // implicit deadline
    _tattr.insert(std::pair<std::string, double>("deadline", period));
    _tattr.insert(std::pair<std::string, double>("period", period));
    Task t(_tattr);
    return t;
}

TaskSet Uni::next_task_set(){
    ts.tasks.clear();
    unifast_divide(num_task, max_util);
    for(unsigned int i = 0; i < (unsigned int) num_task; i++){
        Task t = next_task(divided_util.at(i));
        ts.tasks.push_back(t);
    }
    return ts;
}

std::string Uni::to_str(){
    std::string info;
    info += Gen::to_str();
    info += "\nUunifast between period: " + std::to_string(min_period) + 
        + " " + std::to_string(max_period);
    return info;
}

double Uni::frand(double _min, double _max) {
    double f = (double)std::rand() / RAND_MAX;
    return _min + f * (_max - _min);   
}


} // namespcae rts
