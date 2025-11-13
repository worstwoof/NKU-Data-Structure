#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
int main() {
	string s;
	vector<string> a;
	getline(cin, s);
	string current_component;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '/') {
			a.push_back(current_component);
			current_component = "";
		}
		else {
			current_component += s[i];
		}
	}
	a.push_back(current_component);
	vector<string> b;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == ""||a[i]==".") {
			continue;
		}
		else if (a[i] == "..") {
				if (b.empty()) {
					continue;
				}
				else {
					b.pop_back();
				}
		}
		else {
			b.push_back(a[i]);
		}
	}
	for (int i = 0;i<b.size();i++) {
		if (i != b.size()) {
			cout << "/";
		}
		cout << b[i];
	}
	if (b.size() == 0) {
		cout << "/";
	}
}