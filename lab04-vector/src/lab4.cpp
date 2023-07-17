#include "lab4.h"

#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>

std::vector<int> make_vector(int argc, const char* argv[]) {

	std::vector<int> out(argc);
	for (int i = 0; i < argc; i++) {
		out[i] = atoi(argv[i]);
	}

	return out;
}

int add(int argc, const char* argv[]) {
	std::vector<int> vec = make_vector(argc, argv);
	return std::accumulate(begin(vec), end(vec), 
		0, [](int& a, int& b) {return a + b; });
}
double mean(int argc, const char* argv[]) {
	if (argc == 0) return 0.0;
	else return ((double) add(argc, argv)) / argc;
}
std::vector<int> odd(std::vector<int> in) {
	
	// Rearrange so evens moved to right, then remove right/even side
	in.erase(std::remove_if(in.begin(), in.end(), [](const int& x) {
		return x % 2 == 0;
	}), in.end());

	return in;
}
std::vector<int> reverse(std::vector<int> in) {
	int n = in.size();

	//Swap upper and lower ends, then move them into middle
	for (std::size_t i = 0; i < n / 2; i++) {
		int temp = in[i];
		in[i] = in[n - i - 1];
		in[n - i - 1] = temp;
	}
	return in;
}