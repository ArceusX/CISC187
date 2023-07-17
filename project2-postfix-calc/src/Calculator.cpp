#include "Calculator.h"

const std::vector<char> Calculator::operators = { '^', 'x','*','/', '+','-' };
const std::string Calculator::helpMessage = getHelpMessage();

void Calculator::run() {
	std::string cmd;

	if (args.empty()) std::cout << Calculator::helpMessage;
	else handleOptions();

	while (!quitting) {
		std::cout << "Prompt: ";

		while (args.empty()) {
			std::getline(std::cin, cmd);
			cmd = trim(cmd);

			if (cmd.empty()) std::cout << "You entered blank. Try again: ";
			else args = split(cmd);
		}

		if (!handleOptions()) exprs.push_back(cmd);

		if (!filename.empty()) {
			std::cout << "\n" << filename;

			std::ifstream inFile(filename);
			if (inFile.is_open()) {
				std::cout << "\n" << std::string(filename.length(), '-') << "\n";

				std::string line;
				while (std::getline(inFile, line)) {
					if (line[0] != '#') {
						line = trim(line);
						if (!line.empty()) exprs.push_back(line);
					}
				}
			}
			else std::cout << " cannot be opened\n\n";
		}
		filename.clear();

		for (std::string& expr : exprs) {
			std::cout << std::string(40, '-') << "\n" << expr;

			bool isValid = true;

			if (mode == MODE::Infix) {
				std::cout << " [    infix]";
				isValid = infixToPostfix(expr);
			}
			else if (mode == MODE::Prefix) {
				std::cout << " [    prefix]";
				isValid = prefixToPostfix(expr);
			}

			if (isValid) {
				if (mode != MODE::Postfix) {
					std::cout << "\n" << expr << " [--> postfix]\n";
				}

				std::cout << evaluate(expr) << "\n";
			}
			else std::cout << "\n" << expr << "\n";
		}
		exprs.clear();
	}

	std::cout << "Quitting...";
	exit(EXIT_SUCCESS);
}

std::string Calculator::getHelpMessage() {
	std::string message;
	message.reserve(725);

	message.append("Options:\n");
	message.append("\t -m [postfix | prefix | infix]; Default = postfix\n");
	message.append("\t -v (to toggle verbose: ");
	message.append("on -> print steps in postfix calculation); Default = off\n");
	message.append("\t -h (to output this help message again)\n");
	message.append("\t -q | quit (to exit)\n\n");

	message.append("Usage 1: Pass input_file.txt as [< input_file.txt]\n\n");
	message.append("\t Each line of input_file.txt is evaluated as separate expr\n");
	message.append("\t Lines began with # to be ignored\n\n");

	message.append("Usage 2: Pass expr directly to prompt. () allowed only for infix\n");
	message.append("\t Expression must be in notation matching mode. Default = postfix\n\n");

	message.append("\t ie equivalent exprs in different modes, ans = 15\n\n");

	message.append("\t Postfix: 1 2 + 3 4 * +\n");
	message.append("\t Prefix : + + 1 2 * 3 4\n");
	message.append("\t Infix  : 1 + 2 + ( 3 * 4 )\n\n");

	return message;
}

bool Calculator::handleOptions() {
	std::string tempfile, extension;

	// By index: 0: update calculator mode,		1: flip verbose,
	//			 2: cout help					3: file error code
	int flags[] = { 0, 0, 0, 0 };

	for (auto it = args.begin(); it != args.end(); ++it) {

		if (*it == "-m") {
			if (it != args.end()) {
				++it;

				flags[0] = 1;

				// If specify invalid mode, revert flags[0] to no-change default
				if (*it == "postfix") mode = MODE::Postfix;
				else if (*it == "prefix") mode = MODE::Prefix;
				else if (*it == "infix") mode = MODE::Infix;
				else flags[0] = 0;
			}
		}

		else if (*it == "-v") {
			verbose = !verbose;
			flags[1] = 1;
		}

		else if (*it == "-h") {
			flags[2] = 1;
		}

		if (*it == "-q" || *it == "quit") {
			quitting = true;
			break;
		}

		else if (*it == "<") {
			if (it == args.end()) flags[3] = 1;
			else {
				std::string tempfile = *(++it);
				size_t pos = tempfile.find_last_of(".");

				// If . not found or no non-wspace char follows .
				if (pos == std::string::npos || (pos == tempfile.size() - 1)) {
					flags[3] = 2;
				}
				else {
					extension = tempfile.substr(pos + 1);

					if (extension != "txt") flags[3] = 3;
					else filename = tempfile;
				}
			}
		}
	}
	args.clear();

	if (flags[0]) {
		std::cout << "Change mode to [";
		if (mode == MODE::Postfix) std::cout << "postfix]: operator [after]";
		else if (mode == MODE::Prefix) std::cout << "prefix]: operator [before]";
		else std::cout << "infix]: operator [between]";

		std::cout << " operands" << std::endl;
	}
	if (flags[1]) std::cout << "Verbose turned " << (verbose ? "on" : "off") << "\n";
	if (flags[2]) std::cout << Calculator::helpMessage;

	switch (flags[3]) {
		// case 0: No attempt to < filename or < (valid) filename
	case 1:
		std::cout << "Filename does not immediately follow <\n";
		break;

	case 2:
		std::cout << "File " << tempfile << " has no extension\n";
		break;

	case 3:
		std::cout << "Expect .txt: " << extension << " not an accepted extension\n";
		break;
	}

	if (!filename.empty() ||
		std::any_of(std::begin(flags), std::end(flags),
			[](int x) {return x != 0; })) {
		std::cout << "\n";
		return true;
	}
	else return false;
}

std::string Calculator::evaluate(const std::string& expr) {
	std::stack<double> stack;

	// When logging intermediates in verbose mode, use
	// tempstack to restore stack after pops
	std::stack<double> tempstack;

	// numStr: Numeric token onto which chars are appended.
	//		   Clear upon each new num written into stack
	std::string numStr;

	// outStr: to return. If verbose mode, also holds
	//		   intermediate computations, separated by \n
	std::string outStr;

	// hasNegative, hasDecimal: Track if char invalidates numStr
	// Reset both to false upon new push to stack
	bool hasNegative = false, hasDecimal = false;

	size_t i = 0, len = expr.size();
	for (; i < len; i++) {
		char c = expr[i];

		if (std::isdigit(c)) {
			numStr.push_back(c);
		}

		// . treated like digit, except for situations that
		// invalidates numeric str
		else if (c == '.') {
			// Invalid: If more than 1 . in numStr
			if (hasDecimal) {
				outStr += "\n[Error] Multiple . (decimal pt) in single term";
				break;
			}

			// Invalid: If . not neighbored by digit on either side
			else if ((i == 0 || !std::isdigit(expr[i - 1])) &&
				((i + 1) == len || !std::isdigit(expr[i + 1]))) {
				outStr += "\n[Error] . not followed or preceded by digit";
				break;
			}

			numStr.push_back(c);
			hasDecimal = true;
		}

		// Read as negative sign if: -, not already found,
		// precedes digit (no " ' between) or . (decimal)
		else if (c == '-' && !hasNegative && (i + 1) < len
			&& (isdigit(expr[i + 1]) || expr[i + 1] == '.')) {

			numStr.push_back(c);
			hasNegative = true;
		}

		// Treat ~ as unary negation operator. Used by expr passed
		// by prefixToPostfix to demarcate from (binary) substraction
		else if (c == '~') {
			if (!numStr.empty()) {
				stack.push(std::stod(numStr));
				numStr.clear();
				hasDecimal = hasNegative = false;
			}
			else if (stack.empty()) {
				outStr += "[Error] No operand precedes ~";
				break;
			}

			stack.top() *= -1;
		}
		else if (std::find(operators.begin(), operators.end(), c)
			!= operators.end()) {

			// Give operator trait of space: it writes then clears numStr
			if (!numStr.empty()) {
				stack.push(std::stod(numStr));
				numStr.clear();
				hasDecimal = hasNegative = false;
			}

			if (stack.size() < 2) {
				outStr += "[Error] Fewer than 2 useable operands precede ";
				outStr += c; outStr += "\n";
				break;
			}

			double oper2 = stack.top();
			stack.pop();
			double oper1 = stack.top();
			stack.pop();

			switch (c) {
			case '+':
				stack.push(oper1 + oper2);
				break;
			case '-':
				stack.push(oper1 - oper2);
				break;
			case 'x':
			case '*':
				stack.push(oper1 * oper2);
				break;
			case '/':
				stack.push(oper1 / oper2);
				break;
			case '^':
				stack.push(pow(oper1, oper2));
			}

			if (verbose) {
				std::string intermediate("\n");
				while (!stack.empty()) {
					tempstack.push(stack.top());
					stack.pop();
				}

				while (tempstack.size() > 1) {
					intermediate += trimDouble(tempstack.top()) + ' ';
					stack.push(tempstack.top());
					tempstack.pop();
				}

				if (!tempstack.empty()) {
					intermediate += '{' + trimDouble(tempstack.top()) + '}';
					stack.push(tempstack.top());
					tempstack.pop();
				}

				intermediate.append(expr.substr(i + 1));
				outStr += intermediate + "\n";
			}
		}
		else if (c == ' ') {
			if (!numStr.empty()) {
				stack.push(std::stod(numStr));
				numStr.clear();
				hasDecimal = hasNegative = false;
			}
		}
		else {
			outStr += "\n[Error] Invalid char in ";
			outStr += c; outStr += "\n";
			break;
		}
	}

	// If no error in tokens, final validation of number of tokens
	if (i == len) {
		if (!numStr.empty()) stack.push(std::stod(numStr));

		if (stack.size() > 1) {
			outStr += "\n[Error] Leftover operands not followed by operator";
		}
		else outStr += "\n= " + trimDouble(stack.top()) + "\n";
	}

	return outStr;
}

bool Calculator::prefixToPostfix(std::string& expr) {
	// To make unncessary checking (i + 1) < len for
	// "else if (c == '-' && std::isdigit(expr[i + 1])"
	if (expr.back() == '-') {
		expr = "\n[Error] Fewer than 2 useable operands follow -\n";
		return false;
	}

	std::stack<std::string> stack;
	std::string numStr;

	for (int i = expr.size() - 1; i >= 0; i--) {
		char c = expr[i];

		// Treat . as digit and assign job to evaluate func to 
		// raise error in postfix expr if such error with .
		if (std::isdigit(c) || c == '.') {
			numStr += c;
		}

		// prefix expr "- o1 o2" --> postfix expr "o1 o2 - "  
		// prefix expr "-o1"	 --> postfix expr "-o1 "
		else if ((c == '-' && std::isdigit(expr[i + 1])) ||
			(c == ' ' && !numStr.empty())) {

			// Append puts + on right: reverse then puts it to left
			if (c == '-') numStr += '-';

			std::reverse(numStr.begin(), numStr.end());

			// Separator must be put at end regardless of c
			numStr += ' ';
			stack.push(numStr);
			numStr.clear();
		}
		else if (std::find(operators.begin(), operators.end(), c) != operators.end()) {
			if (stack.size() < 2) {
				expr = "\n[Error] Fewer than 2 useable operands follow ";
				expr += c; expr += "\n";
				return false;
			}

			std::string oper1 = stack.top();
			stack.pop();
			std::string oper2 = stack.top();
			stack.pop();

			stack.push(oper1 + oper2 + c + ' ');
		}
		else if (c != ' ') {
			expr = "\n[Error] Invalid char in ";
			expr += c; expr += "\n";
			return false;
		}
	}

	if (!numStr.empty()) stack.push(numStr);

	if (stack.size() == 1) {
		expr = trim(stack.top());
		return true;
	}
	else {
		expr = "\n[Error] Leftover operands not preceded by operator";
		return false;
	}
}

//TODO TODO TODO (1 + 2 * 3 * 4) * 5;
bool Calculator::infixToPostfix(std::string& expr) {
	std::string postExpr; postExpr.reserve(expr.size());
	std::stack<char> stack, tempstack;

	for (size_t i = 0, len = expr.size(); i < len; i++) {
		char c = expr[i];

		if (std::isdigit(c) || c == '.') {
			postExpr += c;
		}
		else if (c == '(') {
			stack.push('(');
		}
		else if (c == ')') {
			bool needOpen = true;
			while (!stack.empty() && needOpen) {
				if (stack.top() == '(') {
					needOpen = false;
					stack.pop();

					if (!stack.empty() && stack.top() == '~') {
						postExpr += ' '; postExpr += '~';
						stack.pop();
					}
				}
				else {
					postExpr += ' '; postExpr += stack.top();
					stack.pop();
				}
			}

			if (needOpen) {
				expr = "\n[Error] close-) without paired open-(";
				return false;
			}
		}
		else if (c == '-' && (i + 1) < len && expr[i + 1] == '(') {
			stack.push('~');
		}
		else if (c == '^' && !stack.empty() && stack.top() == '^') {
			stack.push('^');
		}
		else if (std::find(operators.begin(), operators.end(), c) != operators.end()) {

			while (!stack.empty()) {
				if (stack.top() == '(') break;
				else if (precedence(stack.top()) >= precedence(c)) {
					postExpr += stack.top();
				}
				else tempstack.push(stack.top());

				stack.pop();
			}

			while (!tempstack.empty()) {
				stack.push(tempstack.top());
				tempstack.pop();
			}

			stack.push(c);
		}
		else if (c == ' ') {
			if (!postExpr.empty() && postExpr.back() != ' ') postExpr += ' ';
		}
		else {
			expr = "\n[Error] Invalid char in ";
			expr += c; expr += "\n";
			return false;
		}
	}

	while (!stack.empty()) {
		if (!postExpr.empty() && postExpr.back() != ' ') postExpr += ' ';
		postExpr += stack.top();
		stack.pop();
	}
	expr = postExpr;
	return true;
}

std::string Calculator::trimDouble(double x) {
	std::string str = std::to_string(x);
	size_t iPoint = str.find_last_of('.');
	size_t iFinal = str.find_last_not_of('0');

	// If . is not last not-'0', erase chars after, but not, last not-'0'
	// If . is last not-'0', erase it too, for being useless .
	if (iPoint <= iFinal) str.erase(iFinal + (iFinal != iPoint));

	return str;
}

int Calculator::precedence(char c) {
	switch (c) {
	case '^':
		return 3;

	case 'x':
	case '*':
	case '/':
		return 2;

	case '+':
	case '-':
		return 1;

	default:
		return 0;
	}
}

std::string& trim(std::string& str, const std::string& ws) {
	const auto strBegin = str.find_first_not_of(ws);

	if (strBegin == std::string::npos) str = "";
	else {
		const auto strEnd = str.find_last_not_of(ws);
		str = str.substr(strBegin, strEnd - strBegin + 1);
	}
	return str;
}

// Calculator.h defines default delim as ' '
std::vector<std::string> split(const std::string& str, const char delim) {
	std::vector<std::string> tokens;
	size_t end = 0, start;

	// Searching from end delim of previous iter, find start for
	// current substr. Will relay its end delim to next iter to use 
	while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {

		// Search for end delim. Current substr builds up to, but
		// excludes, this delim. Next substr starts from this delim
		end = str.find(delim, start);

		// end - start: As many chars from start to, excluding end delim
		tokens.push_back(str.substr(start, end - start));
	}
	return tokens;
}