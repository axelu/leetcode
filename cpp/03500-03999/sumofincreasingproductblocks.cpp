
// 3792. Sum of Increasing Product Blocks
// https://leetcode.com/problems/sum-of-increasing-product-blocks/


// initialize once
long res[1001];
bool init = false;

class Solution {
public:
    int sumOfBlocks(int n) {
        // 1 <= n <= 1000

        // block product           running sum
        // 1     1         = 1     1
        // 2     2*3       = 6     7
        // 3     4*5*6     = 120   127
        // 4     7*8*9*10  = 5047  5167
        // ...

        if( !init ) {
            const long mod = 1000000007;

            // brute force
            long ans = 0;
            long f = 1;
            for(int i = 1; i <= 1000; ++i) {
                long p = 1;
                for(int j = 1; j <= i; ++j) {
                    p = (p * f) % mod;
                    f = (f + 1) % mod;
                }
                // cout << "i " << i << " p " << p << endl;
                ans = (ans + p) % mod;
                res[i] = ans;
            }

            init = true;
        }

        return res[n];
    }
};
