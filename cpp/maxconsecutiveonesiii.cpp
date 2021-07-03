
// 1004. Max Consecutive Ones III
// https://leetcode.com/problems/max-consecutive-ones-iii/
// day 29 June 2021 challenge
// https://leetcode.com/explore/challenge/card/june-leetcoding-challenge-2021/607/week-5-june-29th-june-30th/3796/




class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();


        int ans = 0;

        // sliding window
        int windowsize      = 0;
        int windowstartidx  = 0;
        int windowzeros     = 0; // number of 0s in the window
        bool has1           = false;

        for(int i = 0; i < n; ++i) {
            ++windowsize;

            if( nums[i] == 0 )
                ++windowzeros;
            else
                has1 = true;

            if( windowzeros > k ) {
                // shrink the window
                while( windowsize > 0 ) {
                    if( windowstartidx >= n ) break;
                    if( nums[windowstartidx] == 0 )
                        --windowzeros;
                    ++windowstartidx;
                    --windowsize;
                    if( windowzeros <= k ) break;
                }
            }

            ans = max(ans,windowsize);
        }

        return !has1 ? k : ans;
    }
};
