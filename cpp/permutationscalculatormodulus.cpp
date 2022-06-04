

// based on:
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

