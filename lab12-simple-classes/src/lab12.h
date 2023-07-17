#include <string>

namespace mesa {
class clock {
private:
	double t = 0.0;

public:
	double time();
	void time(double val);
};
}

class complex {
private:
	double realVal;
	double imaginaryVal;
public:
	complex(double real = 0.0, double imaginary = 0.0);

	double real();
	double imaginary();
};

class truck {
private:
	uint16_t nTires;
public:
	truck(uint16_t nTires = 6) : nTires(nTires) {};

	void pop_tire() { nTires = (nTires > 0) ? nTires - 1 : 0; }
	uint16_t tires() { return nTires; }
};

enum class dog_size { SMALL, MEDIUM, LARGE };

class dog {
private:
	std::string n;
	dog_size sz;

public:
	dog(std::string n = "Fido", dog_size sz = dog_size::MEDIUM) :
		n(n), sz(sz) {}

	std::string name() { return n; }
	void name(std::string n) { this->n = n; }
	dog_size size() { return sz; }

	std::string bark() {
		switch (sz) {
			case dog_size::SMALL: return "Yip";
			case dog_size::MEDIUM: return "Ruff";
			case dog_size::LARGE: return "Woof";
		}
	}
};
