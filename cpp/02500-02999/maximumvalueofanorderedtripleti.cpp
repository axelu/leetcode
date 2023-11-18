
// 2873. Maximum Value of an Ordered Triplet I
// https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-i/




class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        int n = nums.size(); // 3 <= nums.length <= 100

        long long ans = 0;

        // brute force
        for(int i = 0; i < n-2; ++i) {
            for(int j = i+1; j < n-1; ++j) {
                if( nums[i] < nums[j] )
                    continue;
                long long nums_i_minus_nums_j = nums[i] - nums[j];
                for(int k = j+1; k < n; ++k) {
                    long long t = nums_i_minus_nums_j * (long long)nums[k];
                    ans = max(ans,t);
                }
            }
        }

        return ans;
    }
};
