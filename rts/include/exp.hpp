#ifndef __EXP_H__
#define __EXP_H__
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
namespace rts {

class Exp{
public:
    std::string name;
    std::string scheduler;
    int iteration;
    nlohmann::json gen_attr;
    Exp();
    Exp(std::string _fname);
};
}  // namespace rts
#endif  // __EXP_H__
