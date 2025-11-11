
// 3701. Compute Alternating Sum
// https://leetcode.com/problems/compute-alternating-sum/


class Solution {
public:
    int alternatingSum(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        for(int i = 0; i < n; ++i)
            if( i % 2 == 0 )
                sum += nums[i];
            else
                sum -= nums[i];
        return sum;
    }
};
