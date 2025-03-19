#include <iostream>

// number of combinations
// binomial coefficient
// (number of combinations is same as binomial coefficient)
// typically the notation is different, but it is the same
// see here https://math.stackexchange.com/questions/2835377/combination-notation-vs-binomial-coefficient-formula

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
