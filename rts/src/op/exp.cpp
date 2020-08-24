#include "op/exp.hpp"
namespace rts {

Exp::Exp() {

}

Exp::Exp(std::string _exp_config_file) {
    using json = nlohmann::json;
    std::ifstream json_file(_exp_config_file);
    json jf = json::parse(json_file);
    if(jf.contains("name")) {
        name = jf["name"];
    }
    if(jf.contains("scheduler")) {
        scheduler = jf["scheduler"];
    }
    if(jf.contains("iteration")) {
        iteration = jf["iteration"];
    }
    if(jf.contains("generator")) {
        gen_attr = jf["generator"];
    }
    if(jf.contains("sched_test")) {
        sched_test_attr = jf["sched_test"];
    }
    if(jf.contains("stat")) {
        stat_attr = jf["stat"];
    }
    if(jf.contains("para")) {
        para_attr = jf["para"];
    }
    if(jf.contains("strategy")) {
        strategy = jf["strategy"];
        if(strategy == "custom") {
            if(jf.contains("custom_option")) {
                custom_popt.clear();
                for(unsigned int i = 0; i < jf["para"]["max_opt"]; i++) {
                    custom_popt.push_back(jf["custom_option"][i]); 
                }
            }
        }
    }
    if(jf.contains("num_tasks")) {
        num_tasks = jf["num_tasks"];
    }
    return;
}

std::string Exp::to_str() {
    std::string ret;
    ret += "name = " + name + "\n";
    ret += "scheduler = " + scheduler + "\n";
    ret += "iteration = " + std::to_string(iteration) + "\n";
    return ret;
}
}  // namespace rts
