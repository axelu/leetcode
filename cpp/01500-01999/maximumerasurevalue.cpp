
// 1695. Maximum Erasure Value
// https://leetcode.com/problems/maximum-erasure-value/
// day 28 May 2021
// https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/601/week-4-may-22nd-may-28th/3758/



class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 ) return nums[0];

        int mem[10001];memset(mem,-1,sizeof mem);  // holds position of index
        int l = 0;                                 // left index
        int t = nums[0];
        mem[nums[0]] = 0;
        int p;
        int ans = 0;
        for(int i = 1; i < n; ++i) {              // right index
            t += nums[i];
            if( mem[nums[i]] != -1 ) {
                p = mem[nums[i]];
                // advance left index to mem[nums[i]]+1
                while( l < p+1 ) {
                    t -= nums[l];
                    mem[nums[l]] = -1;
                    ++l;
                }
            }
            mem[nums[i]] = i;
            ans = max(ans,t);
        }

        return ans;
    }
};
