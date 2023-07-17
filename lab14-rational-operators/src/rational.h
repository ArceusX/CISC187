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

	operator double() const {
		if (den == (T)0.0) return std::numeric_limits<double>::infinity();
		else return (double)num / den;
	}

	double to_double() const {
		if (den == (T)0.0) return std::numeric_limits<double>::infinity();
		else return (double)num / den;
	}

	operator std::string() const {
		if (den == (T)0.0) return "inf";
		else if (num == (T)0.0) return "0";
		else if (num == den) return "1";
		else return std::string(std::to_string(num) + "\/" + std::to_string(den));
	};

	bool operator==(const rational<T>& rhs) {
		return ((num * rhs.den) == (den * rhs.num));
	}

	bool operator!=(const rational<T>& rhs) {
		return !(this == rhs);
	}

	bool operator<(const rational<T>& rhs) {
		return ((num * rhs.den) < (den * rhs.num));
	}

	bool operator>(const rational<T>& rhs) {
		return ((num * rhs.den) > (den * rhs.num));
	}

	bool operator<=(const rational<T>& rhs) {
		return !(this > rhs);
	}

	bool operator>=(const rational<T>& rhs) {
		return !(this < rhs);
	}

	rational<T> operator+(const rational<T>& rhs) {
		return rational<T>((this->num * rhs.den) + (this->den * rhs.num), (this->den * rhs.den));
	}

	rational<T> operator-(const rational<T>& rhs) {
		return rational<T>((this->num * rhs.den) - (this->den * rhs.num), (this->den * rhs.den));
	}

	rational<T> operator*(const rational<T>& rhs) {
		return rational<T>((this->num * rhs.num), (this->den * rhs.den));
	}

	rational<T> operator/(const rational<T>& rhs) {
		return rational<T>((this->num * rhs.den), (this->den * rhs.num));
	}

	rational<T>& operator+=(const rational<T>& rhs) {
		this->num = (this->num * rhs.den) + (this->den * rhs.num);
		this->den = (this->den * rhs.den);
		return *this;
	}

	rational<T>& operator-=(const rational<T>& rhs) {
		this->num = (this->num * rhs.den) - (this->den * rhs.num);
		this->den = (this->den * rhs.den);
		return *this;
	}

	rational<T>& operator*=(const rational<T>& rhs) {
		this->num = (this->num * rhs.num);
		this->den = (this->den * rhs.den);
		return *this;
	}

	rational<T>& operator/=(const rational<T>& rhs) {
		this->num = (this->num * rhs.den);
		this->den = (this->den * rhs.num);
		return *this;
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const rational<T>& r) {
	os << std::string(r);
	return os;
}

#endif