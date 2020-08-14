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
    return;
}

}  // namespace rts
