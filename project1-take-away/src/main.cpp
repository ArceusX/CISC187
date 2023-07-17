#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

#include "helper.h"

using namespace std;

int main(int argc, char** argv) {
	std::vector<int> piles = { 1, 3, 5, 7 };

	std::string namePlayer1;
	std::string namePlayer2("Computer");

	bool isPlayer1Turn = true;
	bool withComputer = false;
	int nPiles = -1;
	int nStones = -1;

	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0) {
			printOptions();
			exit(EXIT_SUCCESS);
		}
	}

	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-c") == 0) {
			withComputer = true;
		}
		else if (strcmp(argv[i], "-p") == 0) {
			nPiles = 0;
		}
		else if (strcmp(argv[i], "-s") == 0) {
			nStones = 0;
		}
	}

	if (nPiles != -1) {
		cout << "How many piles do you request?: ";
		cin >> nPiles;
		while (std::cin.fail() || nPiles < 1 || nPiles > 99) {
			std::cout << "Invalid. Must be between 1-99. Try again: \n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> nPiles;
		}
		cout << "\n";
	}

	if (nStones != -1) {
		piles.clear();

		if (nPiles == -1) {
			cout << "Nim is traditionally played with 4 piles.\n\n";
		}
		else {
			cout << "You manually selected for " << nPiles << " piles.\n\n";
			piles.reserve(nPiles);
		}

		std::string line, temp;
		cout << "Enter number of stones for piles, delimited by space:\n";
		cin.ignore();
		std::getline(std::cin, line);

		stringstream ss;

		ss << line;

		while (!ss.eof() && nPiles > 0) {
			ss >> temp;

			if (stringstream(temp) >> nStones) {
				piles.push_back(nStones);
				nPiles--;
			}
		}
		cout << "\n";
	}
	else if (nPiles != -1) {
		for (int i = 4; i < nPiles; i++) {
			piles.push_back(1 + 2 * i);
		}
	}

	printPiles(piles);

	cout << "\nEnter player1\'s name: ";
	cin >> namePlayer1;

	if (!withComputer) {
		cout << "\nEnter player2\'s name: ";
		cin >> namePlayer2;
	}

	int whichPile;

	while (!piles.empty()) {
		cout << "\n";
		printPiles(piles);

		if (!withComputer || isPlayer1Turn) {
			if (isPlayer1Turn) {
				std::cout << namePlayer1;
			}
			else {
				std::cout << namePlayer2;
			}

			std::cout << "\'s turn:\n" << "Which pile? ";
			cin >> whichPile;

			while (std::cin.fail() || whichPile < 1 || whichPile > piles.size()) {
				std::cout << "Invalid. Must be between 1-" << piles.size() << ". Try again: \n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> whichPile;
			}

			std::cout << "How many stones?: ";
			cin >> nStones;

			while (true) {
				if (std::cin.fail()) {
					std::cout << "Invalid. Must be between 1-" << piles.size();
				}

				else if (nStones < 1) {
					std::cout << "Invalid. Must remove at least 1 stone";
				}
				else if (nStones > piles[whichPile - 1]) {
					std::cout << "Invalid. Pile " << whichPile << " contains only " << piles[whichPile - 1] << " stones";
				}
				else break;
				std::cout << ". Try again: \n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> nStones;
			}
		}
		else {
			whichPile = (rand() % piles.size()) + 1;
			nStones = (rand() % piles[whichPile-1]) + 1;
		}

		piles[whichPile - 1] -= nStones;
		if (piles[whichPile - 1] == 0) piles.erase(piles.begin() + whichPile - 1);

		if (isPlayer1Turn) {
			std::cout << namePlayer1;
		}
		else {
			std::cout << namePlayer2;
		}
		std::cout << " removes " << nStones << " stone" << ((nStones > 1) ? "s" : "") <<
			" from Pile " << whichPile << "\n\n";

		isPlayer1Turn = !isPlayer1Turn;
	}

	if (isPlayer1Turn) {
		std::cout << namePlayer2;
	}
	else {
		std::cout << namePlayer1;
	}
	std::cout <<" wins!";
}

