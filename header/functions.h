#pragma once

#include "numbers.h"

#include <string>
#include <optional>

namespace functions{
    using namespace numbers;

    template <typename F>
    class function{
    public:
        function(const F& fun): func(fun){
            
        }
        function(std::string name, const F& fun): func(fun){
            nm = name;
        }

        std::optional <std::string> name(){
            return nm;
        }
        template <typename... T>
        real operator()(T... args){
            return func(args...);
        }
    private:
        std::optional <std::string> nm;
        F func;
    };
}