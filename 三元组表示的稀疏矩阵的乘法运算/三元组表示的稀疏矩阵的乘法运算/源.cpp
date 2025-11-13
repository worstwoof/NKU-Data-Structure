#include <iostream>
#include <vector>
using namespace std;
int main() {
	int row1, column1, count1;
	cin >> row1 >> column1 >> count1;
	vector<vector<int>> matrix1(row1, vector<int>(column1, 0));
	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < column1; j++) {
			matrix1[i][j] = 0;
		}
	}
	for (int i = 0; i < count1; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		matrix1[a - 1][b - 1] = c;
	}
	int row2, column2, count2;
	cin >> row2 >> column2 >> count2;
	vector<vector<int>> matrix2(row2, vector<int>(column2, 0));
	for (int i = 0; i < row2; i++) {
		for (int j = 0; j < column2; j++) {
			matrix2[i][j] = 0;
		}
	}
	for (int i = 0; i < count2; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		matrix2[a - 1][b - 1] = c;
	}
	if (column1 != row2) {
		cout << "ERROR";
		return 0;
	}
	vector<vector<int>> matrix(row1, vector<int>(column2));
	bool hasNonZero = false;
	int count = 0;
	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < column2; j++) {
			matrix[i][j] = 0;
			for (int row = 0, column = 0; row < row2, column < column1; row++, column++) {
				matrix[i][j] += matrix1[i][column] * matrix2[row][j];
			}
			if (matrix[i][j] != 0) {
				hasNonZero = true;
				cout << i + 1 << " " << j + 1 << " " << matrix[i][j] << endl;
			}
		}
	}
	if (!hasNonZero) {
		cout << "The answer is a Zero Matrix";
	}
}