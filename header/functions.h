#pragma once

#include "numbers.h"

#include <array>

namespace functions{
    using namespace std;
    using namespace numbers;

    template <typename F, size_t argc = 2>
    class function{
    public:
        template <typename F>
        function(const F& lamb): func(lamb){
            
        }

        real operator()(const array <real, argc>& arr){
            return func(arr);
        }
    private:
        F func;
        string nm;
    };
}