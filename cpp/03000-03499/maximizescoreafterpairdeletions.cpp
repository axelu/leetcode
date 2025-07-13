
// 3496. Maximize Score After Pair Deletions
// https://leetcode.com/problems/maximize-score-after-pair-deletions/




class Solution {
public:
    int maxScore(vector<int>& nums) {
        int n = nums.size(); // 1 <= nums.length <= 1e5; -1e4 <= nums[i] <= 1e4

        int sum = accumulate(begin(nums), end(nums), 0);

        if( n % 2 ) {
            int mn = *min_element(begin(nums), end(nums));
            return sum - mn;
        }

        int mn_pair = INT_MAX;
        for(int i = 0; i <= n-2; ++i) {
            if( nums[i] + nums[i+1] < mn_pair ) {
                mn_pair = nums[i] + nums[i+1];
            }
        }
        return sum - mn_pair;
    }
};
