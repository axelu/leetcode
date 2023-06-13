
// 2090. K Radius Subarray Averages
// https://leetcode.com/problems/k-radius-subarray-averages/




class Solution {
public:
    vector<int> getAverages(vector<int>& nums, int k) {
        if( k == 0 )
            return nums;

        int n = nums.size();
        int l = 2 * k + 1;
        vector<int> ans(n,-1);
        if( l > n )
            return ans;

        // sliding window
        long sum = 0L;
        int i = 0; // left index
        for(int j = 0; j < n; ++j) {

            sum += nums[j];
            if( j - i + 1 == l ) {
                ans[j-k] = sum/l;
                sum -= nums[i];
                ++i;
            }
        }

        return ans;
    }
};
