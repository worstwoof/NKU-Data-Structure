#include <iostream>
using namespace std;
int main() {
	int n;
	cin >> n;
	int nums[100];
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (nums[i] > nums[j]) {
				swap(nums[i], nums[j]);
			}
		}
	}
	if (n == 1) {
		cout << nums[0] + 1;
		return 0;
	}
	for (int i = 0; i < n; i++) {
		if (nums[i] != nums[0] + i) {
			cout << nums[0] + i;
			return 0;
		}
	}
	cout << nums[n - 1] + 1;
	return 0;
}