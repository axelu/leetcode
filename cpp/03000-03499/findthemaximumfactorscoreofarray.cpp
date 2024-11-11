
// 3334. Find the Maximum Factor Score of Array
// https://leetcode.com/problems/find-the-maximum-factor-score-of-array/





class Solution {
private:
    // recursive function to return gcd of a and b
    long long gcd(long long int a, long long int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

    // function to return Least Common Multiple (LCM) of two numbers
    // LCM definition:
    // LCM of two numbers is the smallest number which can be divided by both numbers
    long long lcm(long a, long b) {
        return (a / gcd(a,b)) * b;
    }

public:
    long long maxScore(vector<int>& nums) {
        int n = nums.size(); // 1 <= nums.length <= 100

        // LCM and GCD of a single number are the number itself.
        if( n == 1 )
            return nums[0] * nums[0];


        // from right to left

        long long gcd_r[n];
        long long lcm_r[n];

        gcd_r[n-1] = nums[n-1]; // gcd[i..n-1]
        lcm_r[n-1] = nums[n-1]; // lcm[i..n-1]
        for(int i = n-2; i >= 0; --i) {
            gcd_r[i] = gcd(gcd_r[i+1], nums[i]);
            lcm_r[i] = lcm(lcm_r[i+1], nums[i]);
        }

        long long ans = gcd_r[0] * lcm_r[0];

        // from left to right

        long long _lcm = nums[0];
        long long _gcd = nums[0];
        ans = max(ans, gcd_r[1] * lcm_r[1]);

        for(int i = 1; i < n; ++i) {
            if( i == n-1 ) {
                ans = max(ans, _lcm * _gcd);
            } else {
                long long lcm_t = lcm(_lcm, lcm_r[i+1]);
                long long gcd_t = gcd(_gcd, gcd_r[i+1]);
                ans = max(ans, lcm_t * gcd_t);
            }
            _lcm = lcm(_lcm, nums[i]);
            _gcd = gcd(_gcd, nums[i]);
        }

        return ans;
    }
};
