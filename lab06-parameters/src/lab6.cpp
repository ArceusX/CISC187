#include "lab6.h"

#include <cmath>
#include <limits> //For use of std::numeric_limits

mesa::trigon mesa::make_triple(const int16_t m, const int16_t n) {

	//Invalid parameters, so generate "null" trigon
	if (m <= n || n < 1) {
		return trigon(0.0, 0.0, 0.0);
	}
	else {
		return trigon(
			(pow(m, 2.0) - pow(n, 2.0)), 2 * m * n, (pow(m, 2.0) + pow(n, 2.0)));
	}
}

void mesa::scale(trigon& in, const float scale) {
	//Allow for some imprecision in the type
	if (scale >= 0.01 - std::numeric_limits<float>::epsilon()) {
		in.a *= scale;
		in.b *= scale;
		in.c *= scale;
	}
}

float mesa::area(const trigon& in) {
	if (in.a == 0 || in.b == 0 || in.c == 0) return 0;
	else {
		float s = (in.a + in.b + in.c) / 2;
		return sqrt(s * (s - in.a) * (s - in.b) * (s - in.c));
	}
}

mesa::trigon mesa::smallest(const std::vector<trigon>& in) {
	if (in.empty()) return trigon(0.0, 0.0, 0.0);


	else {
		auto smallest = in[0];
		float smallestArea = area(smallest);
		for (auto it = in.begin() + 1; it != in.end(); it++) {
			if (area(*it) < smallestArea) {
				smallestArea = area(*it);
				smallest = *it;
			}
		}
		return smallest;
	}
}