
// 3712. Sum of Elements With Frequency Divisible by K
// https://leetcode.com/problems/sum-of-elements-with-frequency-divisible-by-k/


class Solution {
public:
    int sumDivisibleByK(vector<int>& nums, int k) {
        // 1 <= nums[i] <= 100
        int cnt[101];memset(cnt,0,sizeof cnt);

        for(int x: nums)
            ++cnt[x];

        int ans = 0;

        for(int i = 1; i <= 100; ++i) {
            if( cnt[i] != 0 && cnt[i] % k == 0 ) {
                ans += cnt[i] * i;
            }
        }

        return ans;
    }
};
