#include "op/stat.hpp"
namespace rts {

Stat::Stat() {
    return;
}

Stat::Stat(nlohmann::json _js) {
    x_min = _js["x_min"];
    x_max = _js["x_max"];
    x_inc = _js["x_inc"];
    x_size = (unsigned int)floor((x_max - x_min) / x_inc);
    for(unsigned int i = 0; i < x_size; i++){
        // {num_tot, num_sched}
        raw_data.push_back({0, 0});
    }
    return;
}

std::string Stat::to_str() {
    std::string ret;
    ret += "x_min = " + std::to_string(x_min) + "\n";
    ret += "x_max = " + std::to_string(x_max) + "\n";
    ret += "x_inc = " + std::to_string(x_inc) + "\n";
    return ret;
}

int Stat::conv_idx(double _x) {
    return (int)(floor((_x - x_min)/x_inc));
}

void Stat::add(double _x, bool _sched) {
    unsigned int x_idx = conv_idx(_x);
    if(x_idx < x_size) {
        raw_data[x_idx].num_tot += 1;
        if(_sched) {
            raw_data[x_idx].num_sched += 1;
        }
    } else {
        spdlog::error("Invalid _x: {} > {}", _x, x_size);
    }
    return;
}
 
void Stat::normalize() {
    normalized_data.clear();
    for(unsigned int i = 0; i < x_size; i ++) {
        if(raw_data[i].num_tot == 0) {
            normalized_data.push_back(0.0);
        } else {
            normalized_data.push_back((double) raw_data[i].num_sched / (double) raw_data[i].num_tot);
        }
    }
}

// void Stat::print_short(){
//     std::cout << "checking" << std::endl;
//     normalize();
//     for(int i(0); i < size; i++){
//         std::cout << (min + i*inc) << ", " << norm_data.at(i) << std::endl;
//     }
// }

std::string Stat::crunch_minimal() {
    normalize();
    std::string ret;
    for(unsigned int i = 0; i < x_size; i++){
        ret += std::to_string(normalized_data[i]) + "\n";
    }
    return ret;
}
} // namespace rts