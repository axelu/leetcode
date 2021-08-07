#include <iostream>



// https://en.wikipedia.org/wiki/Modular_exponentiation


using namespace std;

long MOD = 1000000007;

int modular_pow(unsigned long long base, int exponent) {
    unsigned long long c = 1;
    for(int i = 0; i < exponent; ++i)
        c = (c * base) % MOD;
    return c;
}


int main() {

    cout << modular_pow(2,99998) << endl;





    return 0;
}
