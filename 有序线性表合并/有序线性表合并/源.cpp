#include <iostream>
using namespace std;
int* insert(int a[], int k,int len) {
	int* c = new int[len + 1];
	for (int i = 0; i < len; i++){
		if (k < a[i]) {
			c[i] = k;
			for (int j = i + 1; j < len + 1; j++) {
				c[j] = a[j - 1];
			}
			return c;
		}
		c[i] = a[i];
	}
	c[len] = k;
	return c;
}
int main() {
	int m, n;
	cin >> m >> n;
	int* a = new int[m];
	int* b = new int[n];
	int* result = a;
	int current = m;
	for (int i = 0; i < m; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
	for (int i = 0; i < n; i++) {
		int* temp = insert(result, b[i], m + i);
		if (result != a) {
			delete[] result;
		}
		result = temp;
		current++;
	}
	for (int i = 0; i < m+n; i++) {
		cout << result[i]<<" ";
	}
}