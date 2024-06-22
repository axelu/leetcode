
// 3010. Divide an Array Into Subarrays With Minimum Cost I
// https://leetcode.com/problems/divide-an-array-into-subarrays-with-minimum-cost-i/






class Solution {
public:
    int minimumCost(vector<int>& nums) {
        int n = nums.size();

        int a = nums[0];
        int b = INT_MAX;
        int c = INT_MAX;
        for(int i = 1; i < n; ++i) {
            if( nums[i] < b ) {
                c = b;
                b = nums[i];
            } else if( nums[i] < c ) {
                c = nums[i];
            }
        }

        return a + b + c;
    }
};
