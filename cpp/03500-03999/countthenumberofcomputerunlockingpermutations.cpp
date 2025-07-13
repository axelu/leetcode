
// 3577. Count the Number of Computer Unlocking Permutations
// https://leetcode.com/problems/count-the-number-of-computer-unlocking-permutations/





class Solution {
private:
    int MOD = 1000000007;

    long long modPow(long long a, long long x) {
        // return a^x mod MOD
        long long res = 1;
        while(x>0) {
            if( x & 1 ) res = (res*a) % MOD;
            a = (a*a) % MOD;
            x >>= 1;
        }
        return res;
    }

    long long modInverse(long long a) {
        // return modular multiplicative of: a mod MOD
        return modPow(a,MOD-2);
    }

    long long modPermutations(long long n, long long k) {
        // regular permutations formula P(n,k) = n!/(n-k)!
        // return P(n,k) mod MOD
        long long numerator = 1; // n!
        int i;
        for(i=1;i<=n;i++) numerator = (numerator*i) %MOD;

        long long denominator = 1; // n-k!
        for(i=1;i<=n-k;i++) denominator = (denominator*i) %MOD;

        long long res = modInverse(denominator);
        res = (res*numerator)%MOD;
        return res;
    }

public:
    int countPermutations(vector<int>& complexity) {
        int n = complexity.size();

        // if any complexities >= complexity[0], then
        // there is no solution
        int complexity0 = complexity[0];
        for(int i = 1; i < n; ++i) {
            if( complexity[i] <= complexity0 )
                return 0;
        }

        // as we can always unlock with computer 0,
        // any permutation (n-1) is valid

        return modPermutations(n-1, n-1);
    }
};
