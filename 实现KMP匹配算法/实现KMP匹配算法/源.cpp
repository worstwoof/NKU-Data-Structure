#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
int main() {
	string a, b;
	cin >> a >> b;
	if (b.empty()) {
		cout << (a.empty() ? "1" : "no") << endl;
		return 0;
	}
	int m = b.length();
	int n = a.length();
	vector<int> next(m);
	next[0] = 0;
	int j = 0;
	for (int i = 1; i < m; i++) {
		while (j > 0 && b[i] != b[j]) {
			j = next[j - 1];
		}
		if (b[i] == b[j]) {
			j++;
		}
		next[i] = j;
	}
	int i = 0;
	j = 0;
	while (i < n) {
		if (a[i] == b[j]&&j!=m-1) {
			i++;
			j++;
			continue;
		}
		if (a[i] == b[j] && j == m - 1) {
			cout << i - j;
			return 0;
		}
		if (a[i] != b[j]&&j>0) {
			j = next[j - 1];
		}
		if (a[i] != b[j] && j == 0) {
			i++;
		}
	}
	cout << "no";
}