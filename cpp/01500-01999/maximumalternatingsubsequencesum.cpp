
// 1911. Maximum Alternating Subsequence Sum
// https://leetcode.com/problems/maximum-alternating-subsequence-sum/




class Solution {
private:
    long long rec(vector<int>& nums, int i, int even, long long mem[][2]) {
        // even 1 even, 0 odd
        if( i == nums.size() )
            return 0;

        if( mem[i][even] != -1 )
            return mem[i][even];

        // we have a choice
        // include nums[i] or not
        long long a = rec(nums,i+1,even,mem);

        long long b = rec(nums,i+1,!even,mem);
        if( even )
            b += nums[i];
        else
            b -= nums[i];

        return mem[i][even] = max(a,b);
    }
public:
    long long maxAlternatingSum(vector<int>& nums) {

        long long mem[100000][2];memset(mem,-1,sizeof mem);
        return rec(nums,0,1,mem);
    }
};
