
// 3471. Find the Largest Almost Missing Integer
// https://leetcode.com/problems/find-the-largest-almost-missing-integer/





class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size(); // 1 <= n <= 50; 0 <= nums[i] <= 50

        int cnt[51];memset(cnt,0,sizeof cnt);
        for(int x: nums)
            ++cnt[x];

        if( k == n ) {
            for(int i = 50; i >= 0; --i)
                if( cnt[i] != 0 )
                    return i;

            return -1;
        }

        if( k == 1 ) {
            for(int i = 50; i >= 0; --i)
                if( cnt[i] == 1 )
                    return i;

            return -1;
        }

        // if a solution exists, then its either nums[0] or nums[n-1]
        int a = -1;
        if( cnt[nums[0]] == 1 )
            a = nums[0];
        int b = -1;
        if( cnt[nums[n-1]] == 1 )
            b = nums[n-1];

        return max(a, b);
    }
};
