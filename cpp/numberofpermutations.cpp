#include <iostream>

// number of permutations


using namespace std;

// Returns factorial of n
long long fact(int n) {
	long long res = 1;
	for (int i = 2; i <= n; i++)
		res = res * (long long)i;
	return res;
}

int nPr(int n, int r) {
	return fact(n) / fact(n - r);
}

int main() {
	int n = 4, r = 2;
	cout << nPr(n, r);
	return 0;
}
