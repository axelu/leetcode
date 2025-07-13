
// 3536. Maximum Product of Two Digits
// https://leetcode.com/problems/maximum-product-of-two-digits/


class Solution {
public:
    int maxProduct(int n) {
        vector<int> nums;
        while( n ) {
            nums.push_back(n % 10);
            n /= 10;
        }

        int ans = 0;

        int nums_sz = nums.size();
        for(int i = 0; i < nums_sz; ++i)
            for(int j = i+1; j < nums_sz; ++j)
                ans = max(ans, nums[i] * nums[j]);

        return ans;
    }
};
