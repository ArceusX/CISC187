#ifndef MESA_CISC187_LAB06
#define MESA_CISC187_LAB06

#include <cstdint>
#include <vector>

namespace mesa {
	struct trigon {
		trigon(float a, float b, float c) : a(a), b(b), c(c) {}

		float a;
		float b;
		float c;
	};

	trigon make_triple(const int16_t m, const int16_t n);

	void scale(trigon&, const float);

	float area(const trigon&);

	trigon smallest(const std::vector<trigon>&);

}
#endif