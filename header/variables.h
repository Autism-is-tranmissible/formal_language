#pragma once

#include "numbers.h"

#include <optional>

namespace variables{
    using namespace numbers;
    using namespace std;
    
    class variable{
    public:
        variable(string name){
            nm = name;
        }
        variable(real value){
            val = value;
        }
        variable(string name, real value){
            nm = name;
            val = value;
        }

        variable& operator=(const string& name){
            nm = name;
            return *this;
        }
        variable& operator=(const real& value){
            val = value;
            return *this;
        }

        optional <string> name(){
            return nm;
        }
        optional <real> value(){
            return val;
        }
        real operator()(){
            return *val;
        }
    private:
        optional <string> nm;
        optional <real> val;
    };
}
