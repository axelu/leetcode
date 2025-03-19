
// 3452. Sum of Good Numbers
// https://leetcode.com/problems/sum-of-good-numbers/




class Solution {
public:
    int sumOfGoodNumbers(vector<int>& nums, int k) {
        int n = nums.size();

        int ans = 0;

        for(int i = 0; i < n; ++i) {
            bool left_good = true;
            if( i-k >=0 && nums[i-k] >= nums[i] )
                left_good = false;

            bool right_good = true;
            if( i+k < n && nums[i+k] >= nums[i] )
                right_good = false;

            if( left_good && right_good )
                ans += nums[i];
        }

        return ans;
    }
};
