
// 3153. Sum of Digit Differences of All Pairs
// https://leetcode.com/problems/sum-of-digit-differences-of-all-pairs/






class Solution {
public:
    long long sumDigitDifferences(vector<int>& nums) {
        long long nums_sz = nums.size();

        // formula number of pairs n * (n-1)/2

        // count digits at each position
        int n = to_string(nums[0]).size();
        long long cnt[10][n];memset(cnt,0,sizeof cnt);
        for(int x: nums) {
            int i = n-1;
            for(int i = n-1; i >= 0; --i) {
                ++cnt[x % 10][i];
                x /= 10;
            }
        }

        long long ans = 0LL;
        for(int i = 0; i < n; ++i) {
            long long k = nums_sz;
            for(int j = 0; j < 10; ++j) {
                k -= cnt[j][i];
                ans += cnt[j][i] * k;
            }
        }

        return ans;
    }
};
