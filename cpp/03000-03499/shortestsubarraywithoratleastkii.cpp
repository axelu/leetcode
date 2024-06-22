
// 3097. Shortest Subarray With OR at Least K II
// https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-ii/




class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();

        int ans = INT_MAX;

        // sliding window
        int cnt[30];memset(cnt,0,sizeof cnt); // counting set bits, 0 <= nums[i] <= 1e9 -> 30bits max
        int a = 0;                            // result of OR in window
        int i = 0;                            // left index
        for(int j = 0; j < n; ++j) {          // right index
            // cout << "i " << i << " j " << j << endl;
            for(int b = 0; b < 30; ++b) {
                if( nums[j] & (1<<b) ) {
                    ++cnt[b];
                    a |= (1<<b);
                }
            }
            // cout << "a before shrinking " << a << endl;

            // shrink the window
            while( a >= k && i <= j ) {
                ans = min(ans, j - i + 1);
                for(int b = 0; b < 30; ++b) {
                    if( nums[i] & (1<<b) ) {
                        --cnt[b];
                        if( cnt[b] == 0 )
                            a &= ~(1<<b);
                    }
                }
                ++i;
            }
        }

        return ans != INT_MAX ? ans : -1;
    }
};
