
// 629. K Inverse Pairs Array
// https://leetcode.com/problems/k-inverse-pairs-array/
// day 19 Jun 2021 challenge
// https://leetcode.com/explore/challenge/card/june-leetcoding-challenge-2021/605/week-3-june-15th-june-21st/3784/






// solution approach #4
class Solution {
public:
    int kInversePairs(int n, int k) {

        int mem[n+1][k+1];memset(mem,0,sizeof mem);
        int mod = 1000000007;

        for(int i = 1; i <= n; ++i) {
            for(int j = 0; j <= k; ++j) {
                if( j == 0 ) {
                    mem[i][j] = 1;
                } else {
                    int val = (mem[i-1][j] + mod - ((j - i) >= 0 ? mem[i - 1][j - i] : 0)) % mod;
                    mem[i][j] = (mem[i][j - 1] + val) % mod;
                }
            }
        }
        return ((mem[n][k] + mod - (k > 0 ? mem[n][k-1] : 0)) % mod);
    }
};
