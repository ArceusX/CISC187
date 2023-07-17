#pragma once

#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <iostream>

class Calculator {
private:
	static const std::vector<char> operators;
	static const std::string helpMessage;

	enum class MODE { Postfix, Prefix, Infix };
	MODE mode = MODE::Postfix;

	// args: getline(cin)
	// exprs: receive from args or from textfile
	std::vector<std::string> exprs, args;
	std::string filename;
	bool quitting = false, verbose = false, on = false;

	static std::string getHelpMessage();
	bool handleOptions();
	std::string evaluate(const std::string& expression);

public:

	// Skip argv + 0 because it is command to run program
	Calculator(int argc, char** argv) :
		args(argv + 1, argv + argc) {
		run();
	}

	void run();

	static bool prefixToPostfix(std::string& exp);
	static bool infixToPostfix(std::string& exp);

	// Convert to string with trailing 0's after . removed
	static std::string trimDouble(double x);
	static int precedence(char c);
};

std::string& trim(std::string& str, const std::string& ws = " ");
std::vector<std::string> split(const std::string& str, const char delim = ' ');
