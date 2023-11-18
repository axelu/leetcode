
// 2824. Count Pairs Whose Sum is Less than Target
// https://leetcode.com/problems/count-pairs-whose-sum-is-less-than-target/


class Solution {
public:
    int countPairs(vector<int>& nums, int target) {
        int n = nums.size();
        // brute force
        
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = i+1; j < n; ++j)
                if( nums[i] + nums[j] < target )
                    ++ans;
        
        return ans;
    }
};
