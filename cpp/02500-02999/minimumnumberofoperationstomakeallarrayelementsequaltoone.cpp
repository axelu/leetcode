
// 2654. Minimum Number of Operations to Make All Array Elements Equal to 1
// https://leetcode.com/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/





class Solution {
private:
    // TODO we could use https://en.wikipedia.org/wiki/Binary_GCD_algorithm
    // recursive function to return gcd of a and b
    long long gcd(long long int a, long long int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();

        // we either need at last one nums[i] == 1 or
        // a GCD between adjacent elements to be 1

        int cnt1 = 0;
        long long _gcd = nums[0];
        for(int i = 0; i < n; ++i) {
            if( nums[i] == 1 )
                ++cnt1;

            if( i > 0 && cnt1 == 0 && _gcd != 1 )
                _gcd = gcd(_gcd,nums[i]);

        }

        if( cnt1 > 0 )
            return n - cnt1;

        if( _gcd != 1 )
            return -1;

        // brute force
        // _gcd will be 1 at one point
        int mx = n;
        for(int i = 0; i < n-1; ++i) {
            _gcd = nums[i];
            int j = i + 1;
            for(; j < n; ++j) {
                _gcd = gcd(_gcd,nums[j]);
                if( _gcd == 1 )
                    break;
            }
            if( _gcd == 1 )
                mx = min(mx, j - i + 1);
        }

        return n + mx - 2;
    }
};
