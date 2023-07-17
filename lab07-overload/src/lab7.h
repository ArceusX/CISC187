#ifndef MESA_CISC187_LAB02_LAB_07
#define MESA_CISC187_LAB02_LAB_07

#include <iostream>

namespace mesa {
	
	// constexpr functions are implicitly inline (must be 
	// defined in same translation unit (file and its 
	// includes) it is declared)
	template <typename T> constexpr T abs(const T value) {
		return value < 0 ? -value : value;
	}

	struct point {
		int x;
		int y;
	};
}

// Inline must be declared and defined in same file (typically .h)
inline bool operator==(const mesa::point& lhs, const mesa::point& rhs) {
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

inline bool operator!=(const mesa::point& lhs, const mesa::point& rhs) {
	return (lhs.x != rhs.x) || (lhs.y != rhs.y);
}

std::ostream& operator<<(std::ostream& os, const mesa::point& pt) {
	os << "[" << pt.x << "," << pt.y << "]";
	return os;
}

#endif