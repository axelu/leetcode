
// 1175. Prime Arrangements
// https://leetcode.com/problems/prime-arrangements/submissions/


class Solution {
public:
    int numPrimeArrangements(int n) {
        int primes[25]{2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
        // count primes up to and including n
        int cnt = 0;
        for(int i = 0; i < 25; ++i) if( primes[i]<=n ) ++cnt;

        int MOD = 1000000007;
        long r = 1;
        for(int i = 1; i <= cnt; ++i)
            r = ((r % MOD) * i) % MOD;

        for(int i = 1; i <= n - cnt; ++i)
            r = ((r % MOD) * (i % MOD)) % MOD;

        return r;
    }
};
