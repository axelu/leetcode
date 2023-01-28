
// 2539. Count the Number of Good Subsequences
// https://leetcode.com/problems/count-the-number-of-good-subsequences/

// looking at other solutions, one optimization would be to 
// precalculate the modInverse and factorials
// also see "Fermat little theorem"




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

public:
    int countGoodSubsequences(string s) {
        // 1 <= s.length <= 10000
        int n = s.size();

        int cnt[26];memset(cnt,0,sizeof cnt);
        for(int i = 0; i < n; ++i)
            ++cnt[s[i]-'a'];

        // idea:
        // we can select a given char 1 to x times, where x is that chars' number of occurences -> x = cnt[i]
        // if we select a char k times, where k < x,
        //    then we can select it from different slots (number of occurences) -> n choose k (combination)
        //
        // ( (C(cnt[0],k) + 1) * (C(cnt[1],k) + 1) * ...... * (C(cnt[25],k) + 1) ) - 1
        // C(n,k) number of combinations if we take k a's, k b's, ..., k z's from
        //    na's, nb's, ...; if we have less of the respective char than k, then it is 0
        // to compensate for not chosing any, + 1 is needed
        // we need to discount empty subsequence

        long ans = 0;

        for(int k = 1; k <= n; ++k) { // frequency

            long t = 1;
            for(int i = 0; i < 26; ++i) {
                if( cnt[i] >= k ) {
                    t = (t * (modCombinations(cnt[i],k) + 1)) % MOD;

                }
            }
            t = t - 1; // discount empty subsequence
            ans = (ans + t) % MOD;
        }

        return ans;
    }
};
