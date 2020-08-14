#include "stat.hpp"

namespace rts {
Stat::Stat(){

}

Stat::Stat(TaskSet _ts): min(0.0), max(1.0), inc(0.1){
    _tasks = _ts.tasks;
    size = (int)floor((max-min)/inc);
    for(size_t i(0); i < (size_t) size; i++){
        //<num_true, num_tot>
        raw_data.push_back(std::tuple<int,int>(0,0));
    }
}

int Stat::conv_idx(double _idx){
    return (int)(floor((_idx - min)/inc));
}

void Stat::add(double _idx, bool _data){
    int idx = conv_idx(_idx);
    if(idx < size){
        //increment num_tot
        std::get<1>(raw_data.at(idx))+=1;

        //increment num_true if _data is true
        if(_data){
            std::get<0>(raw_data.at(idx))+=1;
        }
    }
}

void Stat::normalize(){
    for(size_t i(0); i < (size_t) size; i ++){
        if(std::get<0>(raw_data.at(i)) == 0){
            norm_data.push_back(0.0);
        } else {
            // push back num_true / num_tot
            norm_data.push_back(((double) std::get<0>(raw_data.at(i))) / (double) std::get<1>(raw_data.at(i)));
        }
    }
}

void Stat::print_short(){
    std::cout << "checking" << std::endl;
    normalize();
    for(size_t i(0); i < (size_t) size; i++){
        std::cout << (min + i*inc) << ", " << norm_data.at(i) << std::endl;
    }
}

void Stat::print_minimal(){
    normalize();
    for(size_t i(0); i < (size_t) size; i++){
        std::cout << norm_data.at(i) << std::endl;
    }
}

std::string Stat::to_str(){
    return std::to_string(min) + "\t" + std::to_string(max) +
        "\t" + std::to_string(inc);
}

} // namespace rts