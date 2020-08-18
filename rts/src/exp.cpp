#include "exp.hpp"
namespace rts {

Exp::Exp() {

}

Exp::Exp(std::string _fname) {
    using json = nlohmann::json;
    std::ifstream json_file(_fname);
    json jf = json::parse(json_file);
    name = jf["name"];
    scheduler = jf["scheduler"];
    iteration = jf["iteration"];
    gen_attr = jf["generator"];
    sched_test_attr = jf["sched_test"];
    stat_attr = jf["stat"];
    para_attr = jf["para"];
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
