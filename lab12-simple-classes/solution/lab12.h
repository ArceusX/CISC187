#ifndef MESA_LAB12_H
#define MESA_LAB12_H

#include <cstdint>
#include <string>

namespace mesa {

class clock {
  public:
    double time() const;
    void   time(double new_time);
  private:
    double time_ = 0;
};

} // end namespace mesa

class complex {
  public:
    complex() = default;
    complex(double real, double imaginary);
    double real() const;
    double imaginary() const;
  private:
    double re_ = 0;
    double im_ = 0;
};



class truck {
  public:
    truck();
    explicit truck(uint16_t num_tires);
    void pop_tire();
    uint16_t tires() const;
  private:
    uint16_t tires_;
    static constexpr uint16_t default_tires = 6;
};


enum class dog_size {SMALL, MEDIUM, LARGE};

class dog {
  public:
    dog () = default;
    dog (std::string name, dog_size s);

    std::string name() const { return name_; }
    dog_size    size() const { return sz_; }
    std::string bark() const;
    void        name(const std::string& name);
  private:
    std::string  name_ = "Fido";
    dog_size     sz_ = dog_size::MEDIUM;
};

#endif

