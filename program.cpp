#include "numbers.h"
#include "variables.h"
#include "functions.h"

#include <stdio.h>
#include <iostream>
#include <array>

using namespace numbers;
using namespace variables;
using namespace functions;

int main(){
    real num = 3ll;
    std::cout << num << std::endl;
    num += real(3, 4);
    std::cout << num << std::endl;
    num -= 4.3l;
    std::cout << num << std::endl;

    variable var("x");
    if (var.value()){
        std::cout << *var.value() << std::endl;
    }
    else{
        std::cout << *var.name() << " does not have any assigned value" << std::endl;
    }
    var = 12.5l;
    std::cout << var() << std::endl;
    
    function f([](real a){
        return a + a;
    });
    function g([&](real a, real b){
        return f(a) + b;
    });
    std::cout << g(6.9l, 2.3l) << std::endl;
    try{
        real a = 2ll, b = 3ll;
        a ^= b;
        std::cout << a << std::endl;
    }
    catch (const math_exceptions::not_implemented& ex){
        std::cout << "Not implemented: " << ex.what() << std::endl;
    }
}