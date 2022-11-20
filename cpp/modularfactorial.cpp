



    long mod = 1000000007;

    // Returns factorial of n mod 10e9+7
    long fact(long n) {
        long res = 1;
        for(long i = 2; i <= n; ++i)
            res = (res * i) % mod;
        return res;
    }

