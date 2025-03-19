
// 3392. Count Subarrays of Length Three With a Condition
// https://leetcode.com/problems/count-subarrays-of-length-three-with-a-condition/





class Solution {
public:
    int countSubarrays(vector<int>& nums) {
        int n = nums.size();

        int ans = 0;

        for(int i = 0, j = 2; j < n; ++i, ++j) {
            int a = nums[i] + nums[j];
            if( 2 * a == nums[i+1] )
                ++ans;
        }

        return ans;
    }
};
