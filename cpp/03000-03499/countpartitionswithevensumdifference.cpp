
// 3432. Count Partitions with Even Sum Difference
// https://leetcode.com/problems/count-partitions-with-even-sum-difference/




class Solution {
public:
    int countPartitions(vector<int>& nums) {
        int n = nums.size();

        int sum = accumulate(nums.begin(), nums.end(), 0);

        int ans = 0;

        int left = 0;

        for(int i = 0; i < n-1; ++i) {
            left += nums[i];
            int right = sum - left;

            int diff = abs(left - right);
            if( diff % 2 == 0 )
                ++ans;

        }

        return ans;
    }
};
