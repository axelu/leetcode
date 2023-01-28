
// 2275. Largest Combination With Bitwise AND Greater Than Zero
// https://leetcode.com/problems/largest-combination-with-bitwise-and-greater-than-zero/



class Solution {
public:
    int largestCombination(vector<int>& candidates) {
        // 1 <= candidates[i] <= 10^7
        // 10^7 -> base 2: 100110001001011010000000 -> 24 bits

        int ans = 0;

        int cnt[24];memset(cnt,0,sizeof cnt);

        for(int x: candidates) {
            for(int i = 0; i < 24; ++i) {
                if( (x >> i) & 1 ) {
                    ++cnt[i];
                    if( cnt[i] > ans )
                        ans = cnt[i];
                }
            }
        }

        return ans > 0 ? ans : 1;
    }
};
