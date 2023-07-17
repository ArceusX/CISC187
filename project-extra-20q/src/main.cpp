#include <iostream>

#include "node.h"
#include "game.h"

using namespace std;

int main (int nargs, char** argv) {

	// No flag passed or -h passed as first flag
	if ((nargs == 1) || strcmp(argv[1], "-h") == 0) {
		cout <<
			"Usage: [-h] [-f filename]\n" <<
			"\nOptions: \n" <<
			"\t-h\tShow this text.\n" <<
			"\t-f\tLoad game tree from file.\n" <<
			"\nQuestions are read from [-filename] and modified" <<
			"\nquestions and answers can be written into same file\n";

		return -1;
	}

	for (char** arg = argv; arg != argv + nargs; arg++) {
		// If -f flagged, process proceeding arg as filename
		if (strcmp(*arg, "-f") == 0) {
			Game20Questions(*(arg+1) ? *(arg + 1) : "data.txt");
			return 0;
		}
	}
}