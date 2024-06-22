
// 2997. Minimum Number of Operations to Make Array XOR Equal to K
// https://leetcode.com/problems/minimum-number-of-operations-to-make-array-xor-equal-to-k/




class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        int n = nums.size();

        // 0 <= nums[i] <= 1e6
        // 0 <=    k    <= 1e6
        // 1e6 -> decimal 1000000 -> binary 11110100001001000000 (20 digits)

        int cnt[20];memset(cnt,0,sizeof cnt);
        for(int x: nums)
            for(int i = 0; i < 20; ++i)
                if( x & (1<<i) )
                    ++cnt[i];

        int ans = 0;
        for(int i = 0; i < 20; ++i)
            if( k & (1<<i) ) {
                if( cnt[i] % 2 == 0 )
                    ++ans;

            } else {
                if( cnt[i] % 2 == 1 )
                    ++ans;
            }

        return ans;
    }
};
