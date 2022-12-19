
// 2256. Minimum Average Difference
// https://leetcode.com/problems/minimum-average-difference/



class Solution {
public:
    int minimumAverageDifference(vector<int>& nums) {
        int n = nums.size();

        long prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + nums[i-1];

        int ans = 0;
        int mn = INT_MAX;
        for(int i = 0; i < n; ++i) {
            int a1 = prefixSum[i+1]/(i+1);
            int a2 = n-i-1 > 0 ? (prefixSum[n] - prefixSum[i+1])/(n-i-1) : 0;
            int t = abs(a1-a2);
            if( t < mn ) {
                mn = t;
                ans = i;
            }
        }

        return ans;
    }
};
