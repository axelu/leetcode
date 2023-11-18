
// 2892. Minimizing Array After Replacing Pairs With Their Product
// https://leetcode.com/problems/minimizing-array-after-replacing-pairs-with-their-product/




class Solution {
public:
    int minArrayLength(vector<int>& v, int k) {
        // if we have a nums[i] == 0, then our answer is 1
        const auto [mn,mx] = minmax_element(begin(v), end(v));
        if( *mn == 0 )
            return 1;
        if( *mn == 1 && *mx == 1 )
            return 1;

        // remove consecutive 1s
        vector<int> nums{v[0]};
        for(auto it = next(begin(v)); it != end(v); ++it) {
            if( *it != 1 || *prev(it) != 1 )
                nums.push_back(*it);
        }

        int n = nums.size();
        if( n <= 1 )
            return 1;

        // dp[j] is answer for up to element j inclusive
        int dp[n];
        dp[0] = 1;
        for(int j = 1; j < n; ++j) { // right index
            if( nums[j] > k ) {
                dp[j] = dp[j-1] + 1;
                continue;
            }

            dp[j] = INT_MAX;

            // lets try to combine nums[j] as long as we can with elements to the left
            int i = j-1;             // left index
            long p = nums[j];
            while( i >= 0 ) {
                p = p * nums[i];
                if( p > k ) {
                    // we cannot combine with nums[j]
                    dp[j] = min(dp[j], dp[i] + 1);
                    break;
                } else { // p <= k
                    // we can combine with nums[i]
                    // meaning range [i,j] could become 1 element
                    if( i == 0 ) {
                        dp[j] = 1;
                    } else {
                        dp[j] = min(dp[j], dp[i-1] + 1);
                    }
                }
                --i;
            }
        }

        return dp[n-1];
    }
};
