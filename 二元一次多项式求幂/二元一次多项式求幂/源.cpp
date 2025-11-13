#include <iostream>
#include <cmath>
using namespace std;
long long factorial(int n) {
	long long res = 1;
	for (int i = 1; i <= n; i++) {
		res *= i;
	}
	return res;
}
long long combinations(int n, int k) {
	if (k<0 || k>n) {
		return 0;
	}
	return factorial(n)/
}