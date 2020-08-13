#include "exp.hpp"
namespace rts {

Exp::Exp() {

}

Exp::Exp(std::string _fname) {
    using json = nlohmann::json;
    std::ifstream json_file(_fname);
    json jf = json::parse(json_file);
    std::string name = jf["name"];
    std::string scheduler = jf["scheduler"];
    std::string iteration = jf["iteration"];
    return;
}

}  // namespace rts
