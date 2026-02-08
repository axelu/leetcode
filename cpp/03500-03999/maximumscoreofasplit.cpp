
// 3788. Maximum Score of a Split
// https://leetcode.com/problems/maximum-score-of-a-split/


class Solution {
public:
    long long maximumScore(vector<int>& nums) {
        int n = nums.size();

        long long sum = accumulate(begin(nums), end(nums), 0LL);
        long long mx_score = LLONG_MIN;
        long long mn = LLONG_MAX;
        for(int i = n-2; i >= 0; --i) {
            sum = sum - (long long)nums[i+1];
            mn = min(mn, (long long)nums[i+1]);
            long long score = sum - mn;
            mx_score = max(mx_score, score);
        }

        return mx_score;
    }
};
