
// 2784. Check if Array is Good
// https://leetcode.com/problems/check-if-array-is-good/




class Solution {
public:
    bool isGood(vector<int>& nums) {
        int n = nums.size() - 1;

        int cnt[n+1];memset(cnt,0,sizeof cnt);
        for(int i = 0; i <= n; ++i) {
            if( nums[i] > n )
                return false;
            ++cnt[nums[i]];
            if( (nums[i] < n && cnt[nums[i]] != 1) || cnt[nums[i]] > 2 )
                return false;
        }

        return true;
    }
};
