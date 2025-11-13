#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;
bool are_case_paired(char x, char y) {
	return (tolower(x) == tolower(y) && x != y);
}
int main() {
	string s;
	cin >> s;
	string result = "";
	for (char c : s) {
		if (!result.empty() && are_case_paired(result.back(), c)) {
			result.pop_back();
		}
		else {
			result.push_back(c);
		}
	}
	if (result.empty()) {
		cout << "-1";
	}
	else {
		cout << result;
	}
	return 0;
}