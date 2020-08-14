#ifndef __EXP_H__
#define __EXP_H__
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
namespace rts {

class Exp{
public:
    std::string name;
    std::string scheduler;
    int iteration;
    nlohmann::json gen_attr;
    nlohmann::json sched_test_attr;
    nlohmann::json stat_attr;
    Exp();
    Exp(std::string _fname);
    std::string to_str();
};
}  // namespace rts
#endif  // __EXP_H__
