
// 2841. Maximum Sum of Almost Unique Subarray
// https://leetcode.com/problems/maximum-sum-of-almost-unique-subarray/




class Solution {
public:
    long long maxSum(vector<int>& nums, int m, int k) {
        int n = nums.size();

        long long ans = 0LL;
        long long sum = 0LL;
        int unique = 0;
        unordered_map<int,int> um;

        // sliding window
        int i = 0;                   // left index
        for(int j = 0; j < n; ++j) { // right index
            sum = sum + nums[j];
            ++um[nums[j]];
            if( um[nums[j]] == 1 )
                ++unique;

            int l = j - i + 1;
            if( l == k ) {
                if( unique >= m )
                    ans = max(ans,sum);

                sum = sum - nums[i];
                --um[nums[i]];
                if( um[nums[i]] == 0 )
                    --unique;
                ++i;
            }
        }

        return ans;
    }
};
