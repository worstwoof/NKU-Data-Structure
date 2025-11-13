#include <iostream>
using namespace std;
int jisuan(int a, int jishu) {
	int n=0;
	while (jishu!=1) {
		a = a / 10;
		jishu--;
	}
	return a - (a / 10) * 10;
}
int main() {
	int n;
	cin >> n;
	int* a = new int[n];
	int* bijiao = new int[n];

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int max = a[0];
	for (int i = 0; i < n; i++) {
		if (a[i] > max) {
			max = a[i];
		}
	}
	int l = 0;
	while (max != 0) {
		max = max / 10;
		l++;
	}
	for (int i = 1; i <= l; i++) {
		for (int j = 0; j < n; j++) {
			bijiao[j] = jisuan(a[j], i);
		}
		for (int m = 0; m < n - 1; m++) {
			for (int k = 0; k < n - 1 - m; k++) {
				if (bijiao[k] > bijiao[k + 1]) {
					swap(bijiao[k], bijiao[k + 1]);
					swap(a[k], a[k + 1]);
				}
			}
		}
		for (int m = 0; m < n; m++) {
			cout << a[m]; // 先输出数字
			if (m < n - 1) { // 如果不是最后一个数
				cout << " "; // 才输出空格
			}
		}
		cout << endl;
		}
	delete[] a;
	delete[] bijiao;
}