
// 2495. Number of Subarrays Having Even Product
// https://leetcode.com/problems/number-of-subarrays-having-even-product/



class Solution {
public:
    long long evenProduct(vector<int>& nums) {
        // product becomes even if one factor is even
        // hence all we need to do is remember last seen even number

        int n = nums.size();

        long long ans = 0;

        int j = -1; // index of last seen even number
        for(int i = 0; i < n; ++i) {

            if( nums[i] % 2 == 0 )
                j = i;

            if( j > -1 )
                ans += j + 1;

        }

        return ans;
    }
};
