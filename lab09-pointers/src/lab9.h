#ifndef MESA_CISC187_LAB_09
#define MESA_CISC187_LAB_09

#include <ctype.h>
#include <stddef.h>
#include <vector>

namespace mesa {
	void to_lower(char*);

	char* copy(const char* source, const size_t count);

	size_t count(const char*, const char);

	template<typename T = int, typename Pointer = std::vector<int>::iterator>
	Pointer min(Pointer begin, Pointer end) {
		return std::min_element(begin, end);
	}
}

#endif