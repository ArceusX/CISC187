#pragma once 

#include <string>

struct Animal {
    virtual ~Animal() = default;
    virtual std::string make_sound() const = 0;
    virtual std::string name() const = 0;
};

