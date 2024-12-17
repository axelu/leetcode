
// 3353. Minimum Total Operations
// https://leetcode.com/problems/minimum-total-operations/






class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();

        // default ans = n-1;
        int ans = n-1;

        // every time we encounter a consecutive number we can deduct 1
        for(int i = 1; i < n; ++i)
            if( nums[i] == nums[i-1] )
                --ans;

        return ans;
    }
};
