#pragma once 

#include <string>

struct Pet {
    virtual ~Pet() = default;
    virtual bool is_friendly() const = 0;
    virtual void play() = 0;
    virtual std::string name() const = 0;
};

