
// 1646. Get Maximum in Generated Array
// https://leetcode.com/problems/get-maximum-in-generated-array/

class Solution {
public:
    int getMaximumGenerated(int n) {
        if( n == 0 ) return 0;
        if( n == 1 ) return 1;

        int nums[n+1];
        nums[0] = 0;
        nums[1] = 1;

        int k;
        for(int i = 0; i <= n; ++i) {

            k = 2*i;
            if( k > n ) break;
            nums[k] = nums[i];

            k = 2*i+1;
            if( k > n ) break;
            nums[k] = nums[i] + nums[i+1];

        }

        return *max_element(nums,nums+n+1);
    }
};
