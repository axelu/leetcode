
// 330. Patching Array
// https://leetcode.com/problems/patching-array/
// day 29 August 2021 challenge
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/617/week-5-august-29th-august-31st/3956/




// based on solution approach
class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        int ans = 0;

        int i = 0;
        long miss = 1; // long to avoid integer overflow
        while(miss <= n) {
            if( i < nums.size() && nums[i] <= miss) { // miss is covered
                miss += (long)nums[i];
                ++i;
            } else {                                    // patch miss to the array
                miss += miss;
                ++ans;                                // increase the answer
            }
        }
        return ans;
    }
};
