
// 3434. Maximum Frequency After Subarray Operation
// https://leetcode.com/problems/maximum-frequency-after-subarray-operation/





class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int n = nums.size(); // 1 <= nums[i] <= 50; 1 <= k <= 50

        // we can divide nums into a left and right
        // adjust most frequent [0,i], and count k [i+1,n-1]
        // 0                              n
        // -------------i-----------------
        //  adjust         count k
        // or
        // count k [0,i], and adjust most frequent [i+1,n-1]
        // 0                              n
        // -------------i-----------------
        //  count k         adjust
        // those two cases are easy
        // but we could also adjust a subarray in the middle
        // 0                              n
        // --------i---------j-----------
        //  count k   adjust   count k

        // prefix sum to determine k count to left and right of our sliding window
        vector<int> prefixSum(n+1,0);
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + (nums[i-1] == k);

        // w/o performing any operation, we have at least prefixSum[n] k
        int ans = prefixSum[n];

        // if 0 k in nums, then our answer is the most freqent element
        int cnt[51];memset(cnt,0,sizeof cnt);
        int mx_cnt = 0;
        if( ans == 0 ) {
            for(int i = 0; i < n; ++i) {
                ++cnt[nums[i]];
                mx_cnt = max(mx_cnt, cnt[nums[i]]);
            }
            return mx_cnt;
        }

        // 0                              n
        // -------------i-----------------
        //  adjust         count k
        for(int i = 0; i < n; ++i) {
            ++cnt[nums[i]];
            mx_cnt = max(mx_cnt, cnt[nums[i]]);
            int k_right = prefixSum[n] - prefixSum[i+1];
            ans = max(ans, mx_cnt + k_right);
        }
        // reset
        memset(cnt,0,sizeof cnt);
        mx_cnt = 0;
        // 0                              n
        // -------------i-----------------
        //  count k         adjust
        for(int i = n-1; i >= 0; --i) {
            ++cnt[nums[i]];
            mx_cnt = max(mx_cnt, cnt[nums[i]]);
            int k_left = prefixSum[i];
            ans = max(ans, mx_cnt + k_left);
        }

        vector<int> indicies[51];
        for(int i = 0; i < n; ++i)
            indicies[nums[i]].push_back(i);

        for(int x = 0; x <= 50; ++x) {
            if( x == k || indicies[x].empty() )
                continue;

            // sliding window
            int x_cnt = 0;
            int l = 0;
            for(int r = 0; r < indicies[x].size(); ++r) {
                ++x_cnt;

                int i = indicies[x][l];
                int j = indicies[x][r];

                int k_window = prefixSum[j+1] - prefixSum[i];
                // shrink the window
                while( k_window >= x_cnt ) {
                    --x_cnt;
                    ++l;
                    i = indicies[x][l];
                    k_window = prefixSum[j+1] - prefixSum[i];
                }
                int k_left  = prefixSum[i];
                int k_right = prefixSum[n] - prefixSum[j+1];
                ans = max(ans, k_left + x_cnt + k_right);
            }
        }

        return ans;
    }
};
