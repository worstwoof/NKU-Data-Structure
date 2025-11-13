#include <iostream>
#include <queue>
#include <vector>
#include <utility>
using namespace std;
using point = pair<int, int>;
int main() {
	int n, m;
	cin >> n >> m;
	char a[101][101];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	queue<point> q;
	q.push({ 1,1 });
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		if (x == n && y == m) {
			cout << "Yes";
			return 0;
		}
		q.pop();
		int x1 = x + 1;
		int y1 = y;
		if (x1 >= 1 && x1 <= n && y1 >= 1 && y1 <= m && a[x1][y1] == '.') {
			q.push({ x1,y1 });
			a[x1][y1] = '#';
		}
		int x2 = x;
		int y2 = y+1;
		if (x2 >= 1 && x2 <= n && y2 >= 1 && y2 <= m && a[x2][y2] == '.') {
			q.push({ x2,y2 });
			a[x2][y2] = '#';
		}
		int x3 = x-1;
		int y3 = y;
		if (x3 >= 1 && x3 <= n && y3 >= 1 && y3 <= m && a[x3][y3] == '.') {
			q.push({ x3,y3 });
			a[x3][y3] = '#';
		}
		int x4 = x;
		int y4 = y - 1;
		if (x4 >= 1 && x4 <= n && y4 >= 1 && y4 <= m && a[x4][y4] == '.') {
			q.push({ x4,y4 });
			a[x4][y4] = '#';
		}
	}
	cout << "No";
	return 0;
}