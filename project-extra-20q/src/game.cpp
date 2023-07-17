#include <fstream>
#include <iostream>
#include <algorithm>

#include "game.h"
#include "helper.h"
#include "node.h"

using namespace std;

void Game20Questions(const char* inFile) {
	Node* root = nullptr;

	std::ifstream instream(inFile);

	// If inFile is readable, store QA tree into root
	if (instream) instream >> root;

	// If not, request starting question and answers
	else {
		std::cout << "The file you passed cannot be found or read\n\n";

		cout << "Write a Yes-No question: ";
		std::string question = getInput();

		cout << "\nWhat is the Yes answer? ";
		Node* ifYes = new Node(getInput());

		cout << "\nWhat is the No answer? ";
		Node* ifNo = new Node(getInput());

		root = new Node(question, ifYes, ifNo);
		cout << endl;
	}
	instream.close();

	std::cout << "Let\'s play \"20 Questions\"!\n\n";

	Node* current = root;
	while (current) {

		// If know current to have child, it is question
		if (current->ifYes) {

			std::cout << current->data << " "; // Print question

			// Get response to question. Continue down to child
			// either another question to followup (this "if"
			// branch) or object to confirm ("else" branch)

			current = getYesNo() ? current->ifYes : current->ifNo;
			cout << endl;
		}

		// If know current to lack child, it is answer
		else {
			std::cout << "I know. I guess it is a " << current->data << ". Yes or no?\n";
			if (getYesNo()) {
				cout << "I guess right. Yay!";
			}
			else {
				// Incorrect guess, so record new entry into tree
				learnNew(current);
			}
			cout << endl;

			std::cout << "Play again? ";
			if (getYesNo()) {
				// Return to root/first question and continue play loop
				current = root;
			}
			else {
				// To signal to exit loop and end game
				current = nullptr;
			}
			cout << endl;
		}
	}

	std::string outFile;
	std::cout << "Would you like to save your game? ";
	if (getYesNo()) {
		while (true) {

			// Valid file was read from: give it as option to write to
			if (instream) {
				std::cout << "Would you like to save to the same file you read from? ";
				
				if (getYesNo()) outFile = inFile;
			}
			if (outFile.empty()) {
				std::cout << "What file would you like to write to? ";
				outFile = getInput();
			}

			ofstream out(outFile);
			if (out) {
				// Write modified tree to outFile
				out << root << std::flush;
				out.close();
				break;
			}
			else {
				cout << "Write-permission is denied to " << outFile 
					 << ". Choose another.\n";
			}
		}
	}

	delete root;
}

bool getYesNo() {
	std::string answer;
	while (true) {
		getline(cin, answer);
		answer = trim(answer);
		std::transform(answer.begin(), answer.end(), answer.begin(),
			[](unsigned char c) { return std::tolower(c); });

		if (answer[0] == 'y') return true;

		else if (answer[0] == 'n') return false;

		std::cout << "Answer y/yes or n/no: ";
	}
}

std::string getInput() {
	string answer = "";

	do {
		getline(cin, answer);
		answer = trim(answer);;
	} while (answer == "");

	return answer;
}

void learnNew(Node* current) {
	std::string objectNew;

	std::cout << "\nWhat is your object? ";
	objectNew = getInput();

	Node* nodeNew = new Node(objectNew);

	// Create new child with data being answer of current
	// Current will have its answer replaced by question
	Node* nodeCopy = new Node(current->data);

	cout << "\nWhat is a Yes/No question I can use to tell a "
		 << current->data << " from a " << objectNew << "?\n";

	current->data = getInput();

	cout << "\nFor a " << objectNew << ", is the answer Yes or No?\n";

	// Make copy of current node and newNode both answer branches 
	if (getYesNo()) {
		current->ifYes = nodeNew;
		current->ifNo = nodeCopy;
	}
	else {
		current->ifYes = nodeCopy;
		current->ifNo = nodeNew;
	}
}