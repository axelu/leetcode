
// 2233. Maximum Product After K Increments
// https://leetcode.com/problems/maximum-product-after-k-increments/




class Solution {
public:
    int maximumProduct(vector<int>& nums, int k) {
        int n = nums.size();
        if( n == 1 )
            return nums[0] + k;

        sort(nums.begin(),nums.end());

        int i = 0;
        while( k > 0 ) {

            if( i == 0 ) {
                ++nums[0];
                --k;
                ++i;
            } else {
                if( nums[i] >= nums[i-1] ) {
                    i = 0;
                } else {
                    ++nums[i];
                    --k;
                    ++i;
                }
            }

            if( i == n )
                i = 0;
        }

        long mod = 1000000007;

        long ans = 1;

        for(int i = 0; i < n; ++i)
            ans = (ans * nums[i]) % mod;

        return ans;
    }
};
