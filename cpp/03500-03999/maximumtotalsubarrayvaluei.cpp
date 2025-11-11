
// 3689. Maximum Total Subarray Value I
// https://leetcode.com/problems/maximum-total-subarray-value-i/



class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int mn = 1e9 + 1;
        int mx = -1;
        for(int x: nums) {
            mn = min(mn, x);
            mx = max(mx, x);
        }
        return (long long)k * (long long)(mx - mn);
    }
};
