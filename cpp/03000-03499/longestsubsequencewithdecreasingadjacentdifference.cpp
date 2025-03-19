
// 3409. Longest Subsequence With Decreasing Adjacent Difference
// https://leetcode.com/problems/longest-subsequence-with-decreasing-adjacent-difference/


class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size(); // 2 <= n

        // 1 <= nums[i] <= 300

        auto [it_gmn, it_gmx] = minmax_element(begin(nums), end(nums));
        int gmn = *it_gmn;
        int gmx = *it_gmx;
            
        int dp[301][301];
        for(int i = gmn; i <= gmx; ++i)
            for(int j = 0; j <= gmx; ++j)
                dp[i][j] = 1;

        int ans = 1;

        bool seen[301]; memset(seen,false,sizeof seen);
        seen[nums[0]] = true;
        int lmn = nums[0], lmx = nums[0];
        for(int i = 1; i < n; ++i) {
            int x = nums[i];

            int j_mx = max(abs(lmx-x), abs(x-lmn));

            int new_mx = 2;
            for(int j = j_mx; j >= 0; --j) {
                if( x + j <= gmx && seen[x+j] ) {
                    int idx = x+j;
                    new_mx = max(new_mx, dp[idx][j]+1);
                }
                if( j > 0 && x - j >= gmn && seen[x-j] ) {
                    int idx = x-j;
                    new_mx = max(new_mx, dp[idx][j]+1);
                }
                dp[x][j] = new_mx;
                ans = max(ans, new_mx);
            }

            seen[x] = true;
            lmx = max(lmx, x);
            lmn = min(lmn, x);
        }

        return ans;
    }
};


