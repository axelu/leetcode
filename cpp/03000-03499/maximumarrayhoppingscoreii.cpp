
// 3221. Maximum Array Hopping Score II
// https://leetcode.com/problems/maximum-array-hopping-score-ii/



class Solution {
public:
    long long maxScore(vector<int>& nums) {
        int n = nums.size();

        // based on hint in problem: It’s always optimal to jump to index j with the maximum value.

        if( n == 2 )
            return nums[1];

        int suffixMax[n];
        suffixMax[n-1] = n;
        suffixMax[n-2] = n-1;
        for(int i = n-3; i >= 0; --i) {
            if( nums[i+1] >= nums[suffixMax[i+1]] )
                suffixMax[i] = i+1;
            else
                suffixMax[i] = suffixMax[i+1];
        }

        long long ans = 0LL;

        int i = 0;
        while( i < n-1 ) {
            int j = suffixMax[i];
            ans += (long long)(j-i) * (long long)nums[j];
            i = j;
        }

        return ans;
    }
};
