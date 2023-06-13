
// 2598. Smallest Missing Non-negative Integer After Operations
// https://leetcode.com/problems/smallest-missing-non-negative-integer-after-operations/




class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int value) {
        int n = nums.size();

        // count integers in nums with remainder 0,1,2,...,value-1
        int cnt[value];memset(cnt,0,sizeof cnt);

        for(int i = 0; i < n; ++i) {
            int rem = abs(nums[i]) % value;
            if( nums[i] < 0 && rem != 0 )
                rem = value - rem;
            ++cnt[rem];
        }

        int i = 0;
        for(; i < n; ++i) {
            int rem = i % value;
            if( cnt[rem] == 0 )
                break;
            --cnt[rem];
        }

        return i;
    }
};
