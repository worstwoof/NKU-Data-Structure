#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
string pre, in;
map<char, int> mp;
int h(int pl, int pr, int il, int ir) {
	if (pl > pr) {
		return 0;
	}
	char root = pre[pl];
	int idx = mp[root];
	int l_size = idx - il;
	int lh = h(pl + 1, pl + l_size, il, idx - 1);
	int rh = h(pl + l_size + 1, pr, idx + 1, ir);
	return 1 + max(lh, rh);
}
int main() {
	int n;
	cin >> n >> pre >> in;
	for (int i = 0; i < n; i++) {
		mp[in[i]] = i;
	}
	cout << h(0, n - 1, 0, n - 1) << endl;
	return 0;
}