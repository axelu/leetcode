
// 462. Minimum Moves to Equal Array Elements II
// https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/
// day 19 May 2021 challenge
// https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/600/week-3-may-15th-may-21st/3748/



class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 ) return 0;

        sort(nums.begin(),nums.end());
        int med = nums[n/2]; // median
        int ans = 0;
        for(int i = 0; i < n; ++i)
            ans += abs(med-nums[i]);

        return ans;
    }
};
