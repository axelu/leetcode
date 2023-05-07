
// 2439. Minimize Maximum of Array
// https://leetcode.com/problems/minimize-maximum-of-array/




class Solution {
public:
    int minimizeArrayValue(vector<int>& nums) {

        // per solution approach

        long long ans = 0;
        long long prefixSum = 0;

        for(int i = 0; i < nums.size(); ++i) {
            prefixSum += nums[i];
            ans = max(ans, (prefixSum + i) / (i + 1));
        }

        return ans;
    }
};
