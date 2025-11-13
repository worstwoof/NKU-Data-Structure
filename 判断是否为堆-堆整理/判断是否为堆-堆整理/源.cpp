#include <iostream>
#include <vector>
using namespace std;
int n;
vector<int> v;
void print() {
	for (int i = 0; i < n; ++i) {
		cout << v[i];
		if (i < n - 1) {
			cout << " ";
		}
	}
	cout << endl;
}
void sift_max(int p, int len) {
	int c = 2 * p + 1;
	while (c < len) {
		int r = c + 1;
		if (r < len && v[r] >= v[c]) {
			c = r;
		}
		if (v[p] >= v[c]) {
			break;
		}
		swap(v[p], v[c]);
		p = c;
		c = 2 * p + 1;
	}
}
void sift_min(int p, int len) {
	int c = 2 * p + 1;
	while (c < len) {
		int r = c + 1;
		if (r < len && v[r] <= v[c]) {
			c = r;
		}
		if (v[p] <= v[c]) {
			break;
		}
		swap(v[p], v[c]);
		p = c;
		c = 2 * p + 1;
	}
}
void build_max() {
	for (int i = (n - 2) / 2; i >= 0; i--) {
		sift_max(i, n);
	}
}
void build_min() {
	for (int i = (n - 2) / 2; i >= 0; i--) {
		sift_min(i, n);
	}
}
int main() {
	cin >> n;
	v.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}
	bool is_max = true;
	bool is_min = true;
	for (int i = 0; i <= (n - 2) / 2; i++) {
		int l = 2 * i + 1;
		int r = 2 * i + 2;
		if (l < n && v[i] < v[l])is_max = false;
		if (r < n && v[i] < v[r])is_max = false;
		if (l < n && v[i] > v[l]) is_min = false;
		if (r < n && v[i] > v[r]) is_min = false;
	}
		if (is_max && is_min) {
			cout << "max min" << endl;
		}
		else if (is_max) {
			cout << "max ";
			build_min();
			print();
		}
		else if (is_min) {
			cout << "min ";
			build_max();
			print();
		}
		else {
			build_max();
			print();
		}
	return 0;
}