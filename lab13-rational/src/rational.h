#ifndef MESA_CISC187_RATIONAL
#define MESA_CISC187_RATIONAL

#include <type_traits>
#include <limits>

template<typename T>
class rational {
static_assert(std::is_integral<T>::value,
		"Integral types required.");
private:
	T num, den;
public:
	rational(T num = (T)0, T den = (T)1) : num(num), den(den) {};

	T numerator() { return num; }
	T denominator () { return den; }

	double to_double() const {
		if (den == (T) 0) return std::numeric_limits<double>::infinity();
		else return (double)num / den;
	}

	operator double() const {
		return to_double();
	}

	operator std::string() const {
		if (num == (T)0) return "0";
		else if (num == den) return "1";
		else if (den == (T)0) return "inf";
		else return std::to_string(num) + "\/" + std::to_string(den);
	};
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const rational<T>& r) {
	os << std::string(r);
	return os;
}

#endif