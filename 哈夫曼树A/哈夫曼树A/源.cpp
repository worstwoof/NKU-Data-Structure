#include <iostream>
#include <algorithm>
using namespace std;
int main() {
	int n;
	long long stones[105];
	long long total_energy = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> stones[i];
	}
	for (int i = 0; i < n - 1; i++) {
		sort(stones + i, stones + n);
		long long current_cost = stones[i] + stones[i + 1];
		total_energy = total_energy + current_cost;
		stones[i + 1] = current_cost;
	}
	cout << total_energy << endl;
	return 0;
}