
// number of combinations
// binomial coefficient
// (number of combinations is same as binomial coefficient)
// typically the notation is different, but it is the same
// see here https://math.stackexchange.com/questions/2835377/combination-notation-vs-binomial-coefficient-formula


// resources:
//   calculate number of combinations MOD 10^9+7
//   https://barkingbogart.wordpress.com/2013/02/21/cnk-mod-1000000007/


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

    long long modCombinations(long long n, long long k) {
        // regular combinations formula C(n,k) = n!/(k!(n-k)!)
        // return C(n,k) mod MOD
        long long numerator = 1; // n*(n-1)* ... * (n-k+1)
        int i;
        for(i=0;i<k;i++) numerator = (numerator*(n-i))%MOD;

        long long denominator = 1; // k!
        for(i=1;i<=k;i++) denominator = (denominator*i) %MOD;

        long long res = modInverse(denominator);
        res = (res*numerator)%MOD;
        return res;
    }


// that does not work when mod is not a prime !!!
// then we need to use other means to calculate for an arbitrary mod
// using Lucas's Theorem and Chinese Remainder Theorem
// see here
// https://fishi.devtail.io/weblog/2015/06/25/computing-large-binomial-coefficients-modulo-prime-non-prime/
// https://cp-algorithms.com/combinatorics/binomial-coefficients.html#binomial-coefficient-modulo-an-arbitrary-number


// here implementation for mod 10
// credits to https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-ii/solutions/6457300/easy-to-understand-c-code-using-binomial-coefficients
    int binmod10(int n, int k) {
        int mod2 = binmod2(n, k);
        int mod5 = binmod5(n, k);
        for (int i = 0; i < 10; i++) {
            if (i % 2 == mod2 && i % 5 == mod5)
                return i;
        }
        return 0;
    }

    int binmod2(int n, int k) {
        while (k > 0) {
            if ((k & 1) > (n & 1))
                return 0;
            n >>= 1;
            k >>= 1;
        }
        return 1;
    }

    int binmod5(int n, int k) {
        int res = 1;
        while (n > 0 || k > 0) {
            int nd = n % 5;
            int kd = k % 5;
            if (kd > nd)
                return 0;
            res = (res * binsmall(nd, kd)) % 5;
            n /= 5;
            k /= 5;
        }
        return res;
    }

    int binsmall(int n, int k) {
        if (k > n)
            return 0;
        int fact[5] = {1, 1, 2, 1, 4};
        int numerator = fact[n];
        int denominator = (fact[k] * fact[n - k]) % 5;
        int deninv = 0;
        for (int i = 0; i < 5; i++) {
            if ((denominator * i) % 5 == 1) {
                deninv = i;
                break;
            }
        }
        return (numerator * deninv) % 5;
    }



