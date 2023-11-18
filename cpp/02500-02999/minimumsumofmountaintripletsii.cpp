
// 2909. Minimum Sum of Mountain Triplets II
// https://leetcode.com/problems/minimum-sum-of-mountain-triplets-ii/






class Solution {
public:
    int minimumSum(vector<int>& nums) {
        int n = nums.size();

        int mnl2r[n];
        mnl2r[0] = -1;
        mnl2r[1] = nums[0];
        for(int i = 2; i < n; ++i)
            mnl2r[i] = min(mnl2r[i-1],nums[i-1]);

        int mnr2l[n];
        mnr2l[n-1] = -1;
        mnr2l[n-2] = nums[n-1];
        for(int i = n-3; i >= 0; --i)
            mnr2l[i] = min(mnr2l[i+1],nums[i+1]);

        int ans = INT_MAX;
        for(int i = 1; i < n-1; ++i)
            if( mnl2r[i] < nums[i] && mnr2l[i] < nums[i] )
                ans = min(ans, mnl2r[i] + nums[i] + mnr2l[i]);

        return ans != INT_MAX ? ans : -1;
    }
};
