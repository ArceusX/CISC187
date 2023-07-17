#ifndef MESA_CISC187_LAB02_LAB_08
#define MESA_CISC187_LAB02_LAB_08

#include <cmath>

namespace mesa {

	// template <typename T, typename std::enable_if_t<std::is_arithmetic<T>::value, int> = 0>
	// constexpr double area(const T radius) {
	//	 return 3.1415926535897932 * radius * radius;
	// }

	template <typename T>
	constexpr double area(const T radius) {
		if (radius < 0) return 0;
		else return 3.14159265358979323846 * radius * radius;
	}

	template <typename T>
	constexpr double perimeter(const T length, int16_t num_sides) {
		if (length < 0 || num_sides < 3) return 0;
		else return length * num_sides;
	}

	template <typename T, int16_t num_sides>
	constexpr double apothem(const T length) {
		if (num_sides < 3 || length < 0) return 0.0;
		else return 0.5 * length / (tan(3.14159265358979323846 / num_sides));
	}

	template <typename T, int16_t num_sides>
	// auto .. -> decltype() lets compiler deduces itself return type
	constexpr auto area(const T length) -> decltype(length * 1.0f) {
		return (apothem<T, num_sides>(length) * perimeter(length, num_sides)/2);
	}
}

#endif