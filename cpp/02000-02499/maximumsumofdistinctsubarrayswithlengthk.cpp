
// 2461. Maximum Sum of Distinct Subarrays With Length K
// https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/




class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();

        // int cnt[100001];memset(cnt,0,sizeof cnt);
        vector<int> cnt(100001,0);
        long long sum = 0;
        long long mx = 0;
        int non_unique = 0;

        // sliding window
        int i = 0;
        for(int j = 0; j < n; ++j) {
            sum = sum + nums[j];
            ++cnt[nums[j]];
            if( cnt[nums[j]] == 2 )
                ++non_unique;
            if( j - i + 1 == k ) {
                if( non_unique == 0 ) {
                    if( sum > mx ) {
                        mx = sum;
                    }
                }
                sum = sum - nums[i];
                --cnt[nums[i]];
                if( cnt[nums[i]] == 1 )
                    --non_unique;
                ++i;
            }
        }

        return mx;
    }
};
