
// 3550. Smallest Index With Digit Sum Equal to Index
// https://leetcode.com/problems/smallest-index-with-digit-sum-equal-to-index/



class Solution {
private:
    int get_digit_sum(int i) {
        int ret = 0;
        while (i)
        {
            int rem = i % 10;
            ret += rem;
            i /= 10;
        }
        return ret;
    }

public:
    int smallestIndex(vector<int>& nums) {
        int n = nums.size();

        int ans = -1;

        for (int i = n-1; i >= 0; --i)
        {
            if ( i == get_digit_sum(nums[i]))
                ans = i;
        }

        return ans;
    }
};
