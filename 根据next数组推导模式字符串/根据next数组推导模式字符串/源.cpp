#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
	int a, b, n;
	cin >> a >> b >> n;
	int* next = new int[n];
	int* p = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> next[i];
	}
	if (next[0] != -1) {
		cout << "ERROR";
		delete[] next;
		delete[] p;
		return 0;
	}
	for (int i = 1; i < n; i++) {
		if (next[i] >= i || next[i] < -1) {
			cout << "ERROR";
			delete[] next;
			delete[]p;
			return 0;
		}
	}
	p[0] = a;
	p[n - 1] = b;
	for (int i = 1; i <= n - 2; i++) {
		bool ok0 = false;
		bool ok1 = false;
		int k = next[i];
		while (k >= 0 && p[k] != 0) {
			k = next[k];
		}
		if (k + 1 == next[i + 1]) {
			ok0 = true;
		}
		k = next[i];
		while (k >= 0 && p[k] != 1) {
			k = next[k];
		}
		if (k + 1 == next[i + 1]) {
			ok1 = true;
		}
		if (ok0 && !ok1) {
			p[i] = 0;
		}
		else if (!ok0 && ok1) {
			p[i] = 1;
		}
		else {
			cout << "ERROR";
			delete[] next;
			delete[] p;
			return 0;
		}
	}
	for (int i = 0; i < n; i++) {
		cout << p[i];
	}
}
