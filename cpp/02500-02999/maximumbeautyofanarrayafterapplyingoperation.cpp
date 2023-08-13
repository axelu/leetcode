
// 2779. Maximum Beauty of an Array After Applying Operation
// https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/





class Solution {
public:
    int maximumBeauty(vector<int>& nums, int k) {
        int n = nums.size();
        if( n == 1 )
            return 1;

        int ans = 1;
        sort(nums.begin(),nums.end());

        int j = 0;
        for(int i = 0; i < n; ++i) {
            int mx = nums[i] + 2*k;

            while( j+1 < n && nums[j+1] <= mx )
                ++j;

            ans = max(ans, j-i+1);
        }

        return ans;
    }
};
