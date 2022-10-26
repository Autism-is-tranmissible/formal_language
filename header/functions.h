#pragma once

#include "numbers.h"

#include <array>
#include <string>

namespace functions{
    using namespace numbers;

    template <typename F, size_t argc = 2>
    class function{
    public:
        function(const F& lamb) requires std::is_invocable_r_v <real, F, const std::array <real, argc>>: func(lamb){
            
        }

        real operator()(const std::array <real, argc>& arr){
            return func(arr);
        }
    private:
        F func;
        std::string nm;
    };
}