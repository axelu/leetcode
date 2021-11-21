
// 238. Product of Array Except Self
// https://leetcode.com/problems/product-of-array-except-self/





class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();

        int i;
        int suffix[n]; // intentially not n+1
        suffix[n-1] = 1;
        for(i = n-2; i >= 0; --i)
           suffix[i] = suffix[i+1]*nums[i+1];

        vector<int> ans(n);
        ans[0] = suffix[0];

        int prefix[n]; // intentially not n+1
        prefix[0] = 1;
        for(i = 1; i < n; ++i) {
            prefix[i] = prefix[i-1]*nums[i-1];
            ans[i] = prefix[i]*suffix[i];
        }

        return ans;
    }
};
