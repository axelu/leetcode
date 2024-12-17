
// 3364. Minimum Positive Sum Subarray 
// https://leetcode.com/problems/minimum-positive-sum-subarray/




class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n = nums.size(); // 1 <= nums.length <= 100

        // brute force of small constraint
        int ans = INT_MAX;
        for(int length = l; length <= r; ++ length) {
            int sum = 0;
            int i = 0;
            for(int j = 0; j < n; ++j) {
                sum += nums[j];
                if( j - i + 1 == length ) {
                    // cout << "i " << i << " j " << j << " sum " << sum << endl;
                    if( sum > 0 )
                        ans = min(ans, sum);
                    sum -= nums[i];
                    ++i;
                }
            }
        }

        return ans != INT_MAX ? ans : -1;
    }
};
