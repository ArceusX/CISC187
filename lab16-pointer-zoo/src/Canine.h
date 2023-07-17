#pragma once

#include <string>

#include "Pet.h"
#include "Animal.h"

class Canine : public Animal {

  public:
    virtual ~Canine() = default;
    virtual std::string make_sound()       const override {
      return "woof!";
    }
    virtual bool        is_domesticated()  const = 0;

};

