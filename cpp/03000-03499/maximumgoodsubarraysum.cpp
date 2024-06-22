
// 3026. Maximum Good Subarray Sum
// https://leetcode.com/problems/maximum-good-subarray-sum/





class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        // 1 <= k <= 1e9
        int n = nums.size();

        // let us construct a prefixSum array
        // for each nums[i], let's record in min and max prefixSum

        long long prefixSum[n+1];
        prefixSum[0] = 0LL;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + (long long)nums[i-1];

        long long ans = LLONG_MIN;

        unordered_map<int,array<long long,2>> val_prefixSum; // nums[i], {min prefixSum, max prefixSum}
        for(int i = 0; i < n; ++i) {
            // nums[i] + k
            auto f = val_prefixSum.find(nums[i]+k);
            if( f != val_prefixSum.end() ) {
                auto [ps_min,ps_max] = f->second;
                ans = max(ans, prefixSum[i+1] - ps_min);
                ans = max(ans, prefixSum[i+1] - ps_max);
            }
            // nums[i] - k
            f = val_prefixSum.find(nums[i]-k);
            if( f != val_prefixSum.end() ) {
                auto [ps_min,ps_max] = f->second;
                ans = max(ans, prefixSum[i+1] - ps_min);
                ans = max(ans, prefixSum[i+1] - ps_max);
            }

            auto p = val_prefixSum.insert({nums[i],{prefixSum[i],prefixSum[i]}});
            if( !p.second ) {
                if( prefixSum[i] < p.first->second[0] ) {
                    p.first->second[0] = prefixSum[i];
                }
                if( prefixSum[i] > p.first->second[1] ) {
                    p.first->second[1] = prefixSum[i];
                }
            }
        }

        return ans != LLONG_MIN ? ans : 0LL;
    }
};
