#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct Node {
	int i, v, d;
};
int main() {
	int n;
	cin >> n;
	if (n == 0) {
		cout << "False" << endl;
		return 0;
	}
	vector<int> a(n);
	for (int k = 0; k < n; k++) {
		cin >> a[k];
	}
	if (a[0] == 0) {
		cout << "False" << endl;
		return 0;
	}
	int target = 2 * a[0];
	queue<Node>q;
	q.push({ 0,a[0],1 });
	while (!q.empty()) {
		Node t = q.front();
		q.pop();
		int i = t.i;
		int v = t.v;
		int d = t.d;
		int l = 2 * i + 1;
		int r = 2 * i + 2;
		bool hasL = (l < n && a[l] != 0);
		bool hasR = (r < n && a[r] != 0);
		if (!hasL && !hasR) {
			if (v == target) {
				cout << "True " << d << endl;
				return 0;
			}
		}
		if (hasL)q.push({ l,v + a[l],d + 1 });
		if (hasR)q.push({ r,v + a[r],d + 1 });
	}
	cout << "False" << endl;
	return 0;
}