#ifndef __EXP_H__
#define __EXP_H__
#include <fstream>
#include <nlohmann/json.hpp>
namespace rts {

class Exp{
public:
    Exp();
    Exp(std::string _fname);
};
}  // namespace rts
#endif  // __EXP_H__
