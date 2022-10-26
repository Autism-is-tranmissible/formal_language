#pragma once

#include "numbers.h"

#include <optional>
#include <string>

namespace variables{
    using namespace numbers;

    class variable{
    public:
        variable(std::string name){
            nm = name;
        }
        variable(real value){
            val = value;
        }
        variable(std::string name, real value){
            nm = name;
            val = value;
        }

        variable& operator=(const std::string& name){
            nm = name;
            return *this;
        }
        variable& operator=(const real& value){
            val = value;
            return *this;
        }

        std::optional <std::string> name(){
            return nm;
        }
        std::optional <real> value(){
            return val;
        }
        real operator()(){
            return *val;
        }
    private:
        std::optional <std::string> nm;
        std::optional <real> val;
    };
}
