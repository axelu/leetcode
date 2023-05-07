
// 2348. Number of Zero-Filled Subarrays
// https://leetcode.com/problems/number-of-zero-filled-subarrays/




class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        int n = nums.size();

        long long ans = 0;

        long long l = 0;
        for(int i = 0; i < n; ++i) {
            // cout << "i " << i << " nums[" << i << "] " << nums[i] << " l " << l << endl;

            if( nums[i] == 0 ) {
                ++l;
            } else if( l != 0 ) {
                ans += l * (l + 1)/2;
                l = 0;
            }
        }
        // finish up
        ans += l * (l + 1)/2;

        return ans;
    }
};
