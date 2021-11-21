
// 485. Max Consecutive Ones
// https://leetcode.com/problems/max-consecutive-ones/


class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        int cnt = 0;
        for(int i = 0; i < n; ++i) {
            if( nums[i] == 1 ) {
                ++cnt;
                if( i == n-1 ) ans = max(ans,cnt);
            } else if( i > 0 && nums[i-1] == 1 ) {
                // end of window
                ans = max(ans,cnt);
                cnt = 0;
            }
        }
        return ans;
    }
};
