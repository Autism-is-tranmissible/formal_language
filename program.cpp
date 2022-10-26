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

    auto add = [](const std::array <real, 2ul>& arr) -> real{
        return arr[0] + arr[1];
    };
    function f(add);
    std::cout << f({{6.9l, 2.2l}}) << std::endl;
}