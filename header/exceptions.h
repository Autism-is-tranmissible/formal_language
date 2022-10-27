#pragma once

#include <exception>
#include <string>

namespace math_exceptions{
    class not_implemented: public std::exception{
    public:
        not_implemented(const char* msg): message(msg) {}
        const char* what() const noexcept{
            return message;
        }
    private:
        const char* message;
    };
}