#include <cstdint>
#include <string>
#include <utility>

#include "lab12.h"

double mesa::clock::time() const {
  return time_;
}
void mesa::clock::time(double new_time) {
  time_ = new_time;
}

complex::complex(double real, double imaginary)
  : re_{real}
  , im_{imaginary}
{ }
double complex::real() const {
  return re_;
}
double complex::imaginary() const {
  return im_;
}


truck::truck()
  : tires_{default_tires}
{ }

truck::truck(uint16_t tires)
  : tires_{tires}
{ }


void truck::pop_tire() {
 if (tires_ != 0u) {
    --tires_;
 }
}
uint16_t truck::tires() const {
  return tires_;
}


dog::dog (std::string name, dog_size s) 
  : name_{std::move(name)}
  , sz_{s}
{ }

void dog::name(const std::string& name) {
  name_ = name;
}

std::string dog::bark() const {
  if (sz_ == dog_size::SMALL) {
    return "Yip";
  }
  if (sz_ == dog_size::MEDIUM) {
    return "Ruff";
  }
  return "Woof";
}

