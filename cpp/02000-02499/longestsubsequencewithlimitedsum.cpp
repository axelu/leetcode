
// 2389. Longest Subsequence With Limited Sum
// https://leetcode.com/problems/longest-subsequence-with-limited-sum/




class Solution {
public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();
        sort(nums.begin(),nums.end());

        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1]+nums[i-1];

        int k = queries.size();
        vector<int> ans(k);
        for(int i = 0; i < k; ++i) {
            int target = queries[i];

            // binary search greatest element less than target or equal target
            int s = 0;
            int e = n+1;
            int mid;
            while(s < e) {
                mid = s + ((e-s)/2);
                if( prefixSum[mid] > target )
                    e = mid;
                else
                    s = mid+1;
            }
            if( (s < n+1 && prefixSum[s] > target) || s == n+1 )
                --s;

            ans[i] = s;
        }

        return ans;
    }
};
