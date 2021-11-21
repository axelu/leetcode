
// 128. Longest Consecutive Sequence
// https://leetcode.com/problems/longest-consecutive-sequence/
// day 6 June 2021 challenge
// https://leetcode.com/explore/challenge/card/june-leetcoding-challenge-2021/603/week-1-june-1st-june-7th/3769/





class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if( n == 0 ) return 0;
        if( n == 1 ) return 1;

        int i;

        unordered_set<int> us;
        for(i = 0; i < n; ++i)
            us.insert(nums[i]);

        int ans = 1;
        int curCnt,curNum;
        for(i = 0; i < n; ++i) {
            // don't start from the current element if it is alredy part of a sequence
           if( !us.count(nums[i]-1) ) {
                curCnt = 1;
                curNum = nums[i];
                // start going up
                while( us.count(curNum+1) ) {
                    ++curNum;
                    ++curCnt;
                }
                ans = max(ans,curCnt);
           }
        }
        return ans;
    }
};
