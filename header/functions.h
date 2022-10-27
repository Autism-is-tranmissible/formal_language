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

    template <typename F>
    class operation: public function <F>{
    public:
        operation(std::string name, char symbol, const F& fun): function <F>(name, fun){
            sym = symbol;
        }

        char symbol(){
            return sym;
        }
    private:
        char sym;
    };

    operation addition("addition", '+', [](real a, real b){
        return a + b;
    });
    operation subtraction("subtraction", '-', [](real a, real b){
        return a - b;
    });
    operation multiplication("multiplication", '*', [](real a, real b){
        return a * b;
    });
    operation division("division", '/', [](real a, real b){
        return a / b;
    });
    operation exponentiation("exponentiation", '^', [](real a, real b){
        return a ^ b;
    });
}