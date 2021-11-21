
// 416. Partition Equal Subset Sum
// https://leetcode.com/problems/partition-equal-subset-sum/
// day 27 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/567/week-4-november-22nd-november-28th/3545/



class Solution {
private:
    vector<vector<int>> dp;
    bool dfs(vector<int> &nums, int n, int subSetSum) {
        if( subSetSum == 0 ) return true;
        if( n == 0 || subSetSum < 0 ) return false;

        if( dp[n][subSetSum] != -1 ) return dp[n][subSetSum];
        bool result = dfs(nums,n-1,subSetSum-nums[n - 1]) || dfs(nums,n-1,subSetSum);
        return dp[n][subSetSum] = result;
    }

public:
    bool canPartition(vector<int>& nums) {
        size_t n = nums.size();
        if( n <= 1 ) return false;
        int sum = accumulate(begin(nums),end(nums),0);
        if( sum % 2 != 0 ) return false;
        int sum2 = sum/2;

        dp = vector(n+1,vector<int>(sum2+1,-1));
        return dfs(nums,n-1,sum2);
    }
};
