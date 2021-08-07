
// 915. Partition Array into Disjoint Intervals
// https://leetcode.com/problems/partition-array-into-disjoint-intervals/
// day 22 July 2021 challenge
// https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/611/week-4-july-22nd-july-28th/3823/




class Solution {
public:
    int partitionDisjoint(vector<int>& nums) {
        int n = nums.size(); // 2 <= nums.length <= 30000

        // idea: we will slide over nums and keep track of the max
        //    on the left side and lookup the min of the right side
        //    if max left >= min right, we have found our answer
        //    we need a fast way of looking up the min of the right side

        int mn[n];
        int t = INT_MAX;
        int i;
        for(i = n-1; i >= 1; --i) {
            t = min(t,nums[i]);
            mn[i] = t;
        }

        t = INT_MIN;
        for(i = 0; i < n-1; ++i) {
            t = max(t,nums[i]);
            if( t <= mn[i+1] )
                break;
        }

        return i+1;
    }
};
