#include "node.h"
#include "helper.h"

using namespace std;

/*
Each line read as node's data. Line contains either 'Q' or 'A'
to depict question or answer, then whitespace for human
readability, and finally text of question or answer.

Each 'Q' line proceded by two blocks of 'Q' and 'A' lines.
1st block depicts followup of "Yes" answer to question for
parent node. 2nd block depicts followup of "No" answer.
Either child's data can store followup question to response 

Q Does it live on land?
Q	Is it bigger than a human? ('Y' to parent)
A		Shark
A		Eel
A	Cat ('N' to parent)

Whitespace skipped by program/unrequired for program to do task
*/

void Node::write(std::ostream& out, const Node* node, std::string whitespace) {

	if (node) {
		// Node with no child is answer node: mark with 'Q'
		char nodeType = node->ifYes ? 'Q' : 'A';

		whitespace.append("    ");
		out << nodeType << whitespace << node->data << endl;

		write(out, node->ifYes, whitespace);
		write(out, node->ifNo, whitespace);
	}
}

// Read from in and store into node in tree format
void Node::read(istream& in, Node*& node) {
	char nodeType;

	in >> nodeType; // Question: Q, Answer: A
	std::string response;
	getline(in, response);

	Node* yesAnswer = nullptr;
	Node* noAnswer = nullptr;

	if (nodeType == 'Q' || nodeType == 'q') {
		read(in, yesAnswer);
		read(in, noAnswer);
	}

	node = new Node(trim(response), yesAnswer, noAnswer);
}

Node::~Node() {
	if (ifYes) delete ifYes;
	if (ifNo) delete ifNo;
}
