#include "helper.h"

void printOptions() {
	std::cout << "Usage: take-away [-h] [-c] [-p # piles] [-s # stones]\n";
	std::cout << "Options:\n" <<
		"\t-h\t Show this text.\n" <<
		"\t-c\t Play with computer.\n" <<
		"\t-p\t Manually set number of piles in the game.\n" <<
		"\t-p\t Manually set number of stones in the piles.\n" <<
		"(Min, Max) of piles and stones: (1, 99)";
}

void printPiles(const std::vector<int>& piles) {
	for (int nStones : piles) {
		for (int i = 0; i < nStones; ++i) {
			cout << "| ";
		}
		std::cout << '\n';
	}
	cout << "\n";
}