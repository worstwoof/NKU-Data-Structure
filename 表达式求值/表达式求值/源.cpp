#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <cctype>
using namespace std;
bool isOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}
bool isRightAssociative(char op) {
	return op == '^';
}
int getPrecedence(char op) {
	if (op == '^')return 3;
	if (op == '*' || op == '/' || op == '%')return 2;
	if (op == '+' || op == '-')return 1;
	return 0;
}
vector<string> infixToPostfix(const string& infix) {
	vector<string> postfix;
	stack<char> opStack;
	char lastToken = '(';
	for (int i = 0; i < infix.length(); i++) {
		char c = infix[i];
		if (isspace(c)) {
			continue;
		}
		if (isdigit(c) || c == '.') {
			if (lastToken == ')') {
				throw runtime_error("ERROR IN INFIX NOTATION");
			}
			string number;
			while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '.')) {
				number += infix[i];
				i++;
			}
			i--;
			postfix.push_back(number);
			lastToken = '0';
		}
		else if (c == '(') {
			if (lastToken == '0' || lastToken == ')') {
				throw runtime_error("ERROR IN INFIX NOTATION");
			}
			opStack.push(c);
			lastToken = '(';
		}
		else if (c == ')') {
			if (isOperator(lastToken) || lastToken == '(') {
				throw runtime_error("ERROR IN INFIX NOTATION");
			}
			while (!opStack.empty() && opStack.top() != '(') {
				postfix.push_back(string(1, opStack.top()));
				opStack.pop();
			}
			if (opStack.empty()) {
				throw runtime_error("ERROR IN INFIX NOTATION");
			}
			opStack.pop();
			lastToken = ')';
		}
		else if (isOperator(c)) {
			if (isOperator(lastToken) || lastToken == '(') {
				throw runtime_error("ERROR IN INFIX NOTATION");
			}
			while (!opStack.empty() && opStack.top() != '(' &&
				((getPrecedence(opStack.top()) > getPrecedence(c)) ||
					(getPrecedence(opStack.top()) == getPrecedence(c) && !isRightAssociative(c)))) {
				postfix.push_back(string(1, opStack.top()));
				opStack.pop();
			}
			opStack.push(c);
			lastToken = c;
		}
		else {
			throw runtime_error("ERROR IN INFIX NOTATION");
		}
	}
	while (!opStack.empty()) {
		if (opStack.top() == '(') {
			throw runtime_error("ERROR IN INFIX NOTATION");
		}
		postfix.push_back(string(1, opStack.top()));
		opStack.pop();
	}
	if (postfix.empty() && !infix.empty()) {
		bool onlySpaces = true;
		for (char ch : infix)if (!isspace(ch))onlySpaces = false;
		if(!onlySpaces)throw runtime_error("ERROR IN INFIX NOTATION");
	}
	return postfix;
}
double evaluatePostfix(const vector<string>& postfix) {
	if (postfix.empty()) {
		throw runtime_error("ERROR IN INFIX NOTATION");
	}
	stack<double> values;
	for (const string& token : postfix) {
		if (token.length() == 1 && isOperator(token[0])) {
			if (values.size() < 2) {
				throw runtime_error("ERROR IN INFIX NOTATION");
			}
			double b = values.top(); values.pop();
			double a = values.top(); values.pop();
			double result = 0.0;
			switch (token[0]) {
			case '+':result = a + b; break;
			case '-':result = a - b; break;
			case '*':result = a * b; break;
			case '/':
				if (b == 0)throw runtime_error("ERROR IN INFIX NOTATION");
				result = a / b;
				break;
			case '%':
				if (static_cast<int>(b) == 0)throw runtime_error("ERROR IN INFIX NOTATION");
				result = static_cast<double>(static_cast<int>(a) % static_cast<int>(b));
				break;
			case '^':
				result = pow(a, b);
				break;
			}
			values.push(result);
		}
		else {
			try {
				values.push(stod(token));
			}
			catch (const invalid_argument&) {
				throw runtime_error("ERROR IN INFIX NOTATION");
			}
		}
	}
	if (values.size() != 1) {
		throw runtime_error("ERROR IN INFIX NOTATION");
	}
	return values.top();
}
int main() {
	string line;
	while (getline(cin, line)) {
		if (line.empty()) {
			continue;
		}
		try {
			vector<string> postfix = infixToPostfix(line);
			double result = evaluatePostfix(postfix);
			cout << fixed << setprecision(2) << result << endl;
		}
		catch (const exception& e) {
			cout << "ERROR IN INFIX NOTATION" << endl;
		}
	}
	return 0;
}