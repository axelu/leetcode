
// 3183. The Number of Ways to Make the Sum
// https://leetcode.com/problems/the-number-of-ways-to-make-the-sum/




/*
    1  2  6    paired with either 0 fours, 1 four or 2 fours
    x
       x
          x
    -------
    x  x
    x     x
       x  x
    -------
    x  x  x
 */
class Solution {
private:
    const long mod = 1000000007;

    // long mem[100001][3];

    long one(int target, int coin) {
        // cout << "one target " << target << " coin " << coin << endl;
        return target < coin || target % coin ? 0L : 1L;
    }

    long two(int target, int coin1, int coin2) {

        /*
        int key;
        if( coin1 == 1 && coin2 == 2 )
            key = 0;
        else if( coin1 == 1 && coin2 == 6 )
            key = 1;
        else // coin1 == 2 && coin2 == 6
            key = 2;

        if( mem[target][key] != -1L )
            return mem[target][key];
        */
        long ret = 0L;
        for(int i = 1; (i * coin1) <= (target - coin2) ; ++i)
            ret = (ret + one(target - i*coin1, coin2)) % mod;
        // return mem[target][key] = ret;
        return ret;
    }

    long three(int target, int coin1, int coin2, int coin3) {
        // coin1 is always 1

        long ret = 0L;

        int limit = target - coin2 - coin3;
        for(int i = 1; i <= limit; ++i) {
            ret = (ret + two(target - i, coin2, coin3)) % mod;
        }
        return ret;
    }

public:
    int numberOfWays(int n) {
        long ans = n == 4 || n == 8 ? 1L : 0L;

        // one
        for(int i = 0; i <= 8; i += 4) {
            ans = (ans + one(n-i, 1)) % mod;
            ans = (ans + one(n-i, 2)) % mod;
            ans = (ans + one(n-i, 6)) % mod;
        }

        // two
        // memset(mem,-1,sizeof mem);
        for(int i = 0; i <= 8; i += 4) {
            ans = (ans + two(n-i, 1, 2)) % mod;
            ans = (ans + two(n-i, 1, 6)) % mod;
            ans = (ans + two(n-i, 2, 6)) % mod;
        }
        /*
        // three top down
        for(int i = 0; i <= 8; i += 4)
            ans = (ans + three(n-i, 1, 2, 6)) % mod;
        */

        // three bottom up
        for(int i = 0; i <= 8; i += 4) {
            int target = n - i;
            for(int j = target - 6; j >= 3; j -= 6) {
                long f = j / 2;
                if( j % 2 )
                    ans = (ans + f) % mod;
                else
                    ans = (ans + (f-1L)) % mod;
            }
        }

        return ans;
    }
};
