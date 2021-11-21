
// 376. Wiggle Subsequence
// https://leetcode.com/problems/wiggle-subsequence
// day 18 March 2021 challenge
// https://leetcode.com/explore/challenge/card/march-leetcoding-challenge-2021/590/week-3-march-15th-march-21st/3676/



class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 ) return 1;
        if( n == 2 ) return nums[0] == nums[1] ? 1 : 2;

        int up   = -1; // last move
        int down = -1; // last move
        int ans  =  1;
        for(int i = 1; i < n; ++i) {
            if( up == -1 && down == -1 ) {
                if( nums[i-1] < nums[i] ) {
                    up = 1;
                    ++ans;
                } else if( nums[i-1] > nums[i] ) {
                    down = 1;
                    ++ans;
                }
            } else if( up == 1 ) {
                // we are looking for a down move
                if( nums[i-1] > nums[i] ) {
                    ++ans;
                    up = 0;
                    down = 1;
                }
            } else {
                 // we are looking for an up move
                if( nums[i-1] < nums[i] ) {
                    ++ans;
                    up = 1;
                    down = 0;
                }
            }
        }
        return ans;
    }
};
