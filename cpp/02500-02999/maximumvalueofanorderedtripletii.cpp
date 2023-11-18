
// 2874. Maximum Value of an Ordered Triplet II
// https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/





class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        int n = nums.size();

        int curr_mx_i = -1;
        long long mx_i[n]; // largest nums[i] in range[0,i] inclusive
        for(int i = 0; i < n; ++i) {
            if( nums[i] > curr_mx_i )
                curr_mx_i = nums[i];
            mx_i[i] = curr_mx_i;
        }

        int curr_mx_k = -1;
        long long mx_k[n];
        for(int k = n-1; k >= 0; --k) {
            if( nums[k] > curr_mx_k )
                curr_mx_k = nums[k];
            mx_k[k] = curr_mx_k;
        }

        long long ans = 0;
        for(int j = 1; j < n-1; ++j)
            ans = max(ans, (mx_i[j-1] - nums[j]) * mx_k[j+1]);

        return ans;
    }
};
