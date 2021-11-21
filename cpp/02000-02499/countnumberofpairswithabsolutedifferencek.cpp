
// 2006. Count Number of Pairs With Absolute Difference K
// https://leetcode.com/problems/count-number-of-pairs-with-absolute-difference-k/





class Solution {
public:
    int countKDifference(vector<int>& nums, int k) {
        int n = nums.size();
        if( n == 1 )
            return 0;

        int ans = 0;

        for(int i = 0; i < n-1; ++i)
            for(int j = i+1; j < n; ++j)
                if( abs(nums[i]-nums[j]) == k )
                    ++ans;

        return ans;
    }
};
