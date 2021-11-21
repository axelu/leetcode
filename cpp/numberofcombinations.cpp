#include <iostream>

// number of combinations


using namespace std;

// Returns factorial of n
long long fact(int n) {
	long long res = 1;
	for (int i = 2; i <= n; i++)
		res = res * (long long)i;
	return res;
}

int nCr(int n, int r) {
	return fact(n) / (fact(r) * fact(n - r));
}

int main() {
	int n = 20, r = 10;
	cout << nCr(n, r);
	return 0;
}
