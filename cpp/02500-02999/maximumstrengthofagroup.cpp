
// 2708. Maximum Strength of a Group
// https://leetcode.com/problems/maximum-strength-of-a-group/





class Solution {
public:
    long long maxStrength(vector<int>& nums) {
        // we are looking for the non-empty subsequence with max product
        // worst case 9*9*9*9*9*9*9*9*9*9*9*9*9 = 2541865828329
        int n = nums.size(); // 1 <= nums.length <= 13

        // brute force
        // worst case 2^13 - 1 = 8192

        long long ans = LLONG_MIN;
        for(int i = 1; i < pow(2,n); ++i) {

            long long t = 1;
            for(int j = 0; j < n; ++j) {
                if( (i>>j) & 1 ) {
                    t = t * (long long)nums[j];
                }
            }
            ans = max(ans,t);
        }

        return ans;
    }
};
