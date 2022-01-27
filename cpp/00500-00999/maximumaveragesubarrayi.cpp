
// 643. Maximum Average Subarray I
// https://leetcode.com/problems/maximum-average-subarray-i/


class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size();
        double ans = numeric_limits<double>::lowest();
        double sum = 0.0;
        for(int i = 0; i < n; ++i) {
            if( i < k ) {
                sum += nums[i];
                continue;
            }
            ans = max(ans,sum/k);
            sum -= nums[i-k];
            sum += nums[i];
        }
        ans = max(ans,sum/k);
        return ans;
    }
};
