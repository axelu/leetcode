
// 3352. Count K-Reducible Numbers Less Than N
// https://leetcode.com/problems/count-k-reducible-numbers-less-than-n/


// initialize once, precompute factorial and modinverse
int steps_required[801];
long long factorial[801];
long long inverse[801];
bool init = false;

class Solution {
private:
    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    int solve(int x) {
        // return the number of steps required to
        // reduce a number if x set bits to 1
        // 1 <= x < 800

        if( x == 1 )
            return 1;

        int steps = 1;

        while( x != 1 ) {
            ++steps;
            x = countSetBits(x);
        }

       return steps;
    }

    int mod = 1000000007;

    long long modPow(long long a, long long x) {
        // return a^x mod MOD
        long long res = 1;
        while(x>0) {
            if( x & 1 ) res = (res*a) % mod;
            a = (a*a) % mod;
            x >>= 1;
        }
        return res;
    }

    long long modInverse(long long a) {
        // return modular multiplicative of: a mod MOD
        return modPow(a,mod-2);
    }

    long long modCombinations(long long n, long long k) {
        return ((factorial[n] * inverse[k]) % mod * inverse[n-k]) % mod;
    }

public:
    int countKReducibleNumbers(string s, int k) {
        if( !init ) {
            init = true;
        
            factorial[0] = 1LL;
            inverse[0] = 1LL;
            for(int i = 1; i <= 800; ++i) {
                steps_required[i] = solve(i);
                factorial[i] = (factorial[i-1] * i) % mod;
                inverse[i]   = modInverse(factorial[i]);
            }
        }
                
        int n = s.size(); // 1 <= s <= s

        // worst case n = 800, and s = "10000...000", so basically
        // we can make a number with 799 bits set
        // and k = 5
        /*
        for(int i = 1; i < 800; ++i)
            cout << "set bits " << i << " steps " << solve(i) << endl;
        */

        // let b be the number of bits we can set
        // how many number with 1 to b bits set are there,
        // that can be reduced to 1 in up to k steps?

        long ans = 0L;
        /*
        for(int i = 1; i <= 799; ++i) {
            ans = (ans + modCombinations(799,i)) % MOD;
        }
        */

        // TODO can we do i in up to k steps?

        // TODO what if 10010011?  meaning we have 1's to the very right?

        int cnt = 0; // leftmost bit in s is 1
        for(int pos = 0; pos < n; ++pos) {
            if( s[pos] == '1' ) {
                if( cnt > 0 && steps_required[cnt] <= k )
                    ans = (ans + 1) % mod;
                
                int i_max = n - (pos+1);
                for(int i = 1; i <= i_max; ++i) {
                    if( steps_required[i+cnt] > k )
                        continue;
                    ans = (ans + modCombinations(i_max,i)) % mod;
                }
            
                ++cnt;
            }
            
        }

        return ans;
    }
};
