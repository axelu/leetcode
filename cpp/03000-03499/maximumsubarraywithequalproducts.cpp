
// 3411. Maximum Subarray With Equal Products
// https://leetcode.com/problems/maximum-subarray-with-equal-products/





// LCM and GCD of a single number are the number itself.
// prod worst case: 1e100
// gcd is between 1 and 10
// lcm like if nums [1,2,3,4,5,6,7,8,9,10] then lcm 2520
// so we can cutoff prod (via mod) to avoid integer overflow, it will not me reachable

class Solution {
private:

public:
    int maxLength(vector<int>& nums) {
        int n = nums.size(); // 2 <= n <= 100

        int ans = 1;

        for(int i = 0; i < n; ++i) {
            long prod = nums[i];
            int _gcd = nums[i];
            int _lcm = nums[i];
            for(int j = i+1; j < n; ++j) {
                prod = (prod * (long)nums[j]) % 1000000007;
                _gcd = gcd(_gcd, nums[j]);
                _lcm = lcm(_lcm, nums[j]);
                // cout << "j " << j << " prod " << prod << " _gcd " << _gcd << " _lcm " << _lcm << endl;
                if( prod == _lcm * _gcd && j-i+1 > ans )
                    ans = j-i+1;
            }
        }

        return ans;
    }
};
