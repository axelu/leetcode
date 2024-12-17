
// 3375. Minimum Operations to Make Array Values Equal to K
// https://leetcode.com/problems/minimum-operations-to-make-array-values-equal-to-k/





class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        int n = nums.size();

        sort(nums.begin(), nums.end());
        if( nums[0] < k )
            return -1;

        if( n == 1)
            return nums[0] > k ? 1 : 0;

        int ans = 0;

        for(int i = n-2; i >= 0; --i) {
            if( nums[i] != nums[i+1] ) {
                // we would be setting all nums[i+1,n-1] to nums[i]
                ++ans;
            }
            if( nums[i] == k )
                break;
        }
        if( nums[0] != k )
            ++ans;

        return ans;
    }
};
