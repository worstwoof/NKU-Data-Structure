#include <iostream>
#include <vector>
using namespace std;
bool isalleven(vector<int> a) {
	for (int i = 0; i < a.size(); i++) {
		if (a[i] % 2 != 0) {
			return 0;
		}
	}
	return 1;
}
int main() {
	int n;
	cin >> n;
	vector<vector<int>> matrix(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> matrix[i][j];
		}
	}
	vector<int> row;
	vector<int> list;
	for (int i = 0; i < n; i++) {
		int sum = 0;
		for (int j = 0; j < n; j++) {
			sum += matrix[i][j];
		}
		row.push_back(sum);
	}
	for (int j = 0; j < n; j++) {
		int sum = 0;
		for (int i = 0; i < n; i++) {
			sum += matrix[i][j];
		}
		list.push_back(sum);
	}
	if (isalleven(row) && isalleven(list)) {
		cout << "OK";
		return 0;
	}
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				row.clear();
				list.clear();
				matrix[i][j] = 0 - matrix[i][j] + 1;
				for (int l = 0; l < n; l++) {
					int sum = 0;
					for (int m = 0; m < n; m++) {
						sum += matrix[l][m];
					}
					row.push_back(sum);
				}
				for (int m = 0; m < n; m++) {
					int sum = 0;
					for (int l = 0; l < n; l++) {
						sum += matrix[l][m];
					}
					list.push_back(sum);
				}
				if (isalleven(row) && isalleven(list)) {
					cout << "Change bit ("<<i+1<<","<<j+1<<")";
					return 0;
				}
				matrix[i][j] = 0 - matrix[i][j] + 1;
			}
		}
	}
	cout << "Corrupt";
	return 0;
}