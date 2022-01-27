
// 645. Set Mismatch
// https://leetcode.com/problems/set-mismatch/
// day 2 March 2021 challenge
// https://leetcode.com/explore/featured/card/march-leetcoding-challenge-2021/588/week-1-march-1st-march-7th/3658/



class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        // 2 <= nums.length <= 104
        // 1 <= nums[i] <= 104

        int n = nums.size();
        sort(nums.begin(),nums.end());
        int mis = -1, dup = -1;
        if( nums[0] != 1 ) mis = 1;
        if( nums[n-1] != n ) mis = n;
        for(int i = 1; i < n; ++i) {
            if( nums[i] == nums[i-1] ) {
                dup = nums[i];
            }
            else if( nums[i] != nums[i-1]+1 ) {
                mis = nums[i-1]+1;
            }
            if( mis != -1 && dup != -1 ) break;
        }
        return {dup,mis};
    }
};
