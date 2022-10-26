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
    cout << num << endl;
    num += real(3, 4);
    cout << num << endl;
    num -= 4.3l;
    cout << num << endl;

    variable var("x");
    if (var.value()){
        cout << *var.value() << endl;
    }
    else{
        cout << *var.name() << " does not have any assigned value" << endl;
    }
    var = 12.5l;
    cout << var() << endl;

    auto add = [](const array <real, 2ul>& arr) -> real{
        return arr[0] + arr[1];
    };
    function f(add);
    cout << f({{6.9l, 2.2l}}) << endl;
}

// argument types are: (lambda [](const std::array<numbers::real, 2UL> &arr)->numbers::real)