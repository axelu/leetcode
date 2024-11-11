
// 3201. Find the Maximum Length of Valid Subsequence I
// https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-i/


class Solution {
public:
    int maximumLength(vector<int>& nums) {
        // even + even = even, odd + odd = even, odd + even = odd, even + odd = odd
        // even even even ...
        // odd odd odd ...
        // even odd even odd ...
        // odd even odd even ...

        int n = nums.size();
        if( n == 2 )
            return 2;

        int a = 0; // all even
        int b = 0; // all odd
        int firsteven = -1;
        int firstodd  = -1;
        for(int i = 0; i < n; ++i) {
            if( nums[i] % 2 == 0 ) {
                ++a;
                if( firsteven == -1 )
                    firsteven = i;
            } else {
                ++b;
                if( firstodd == -1 )
                    firstodd = i;
            }
        }

        int c = 0; // even odd even odd
        int f = 0;
        for(int i = 0; i < n; ++i) {
            if( f == 0 ) {
                // looking for even
                if( nums[i] % 2 == 0 ) {
                    ++c;
                    f = 1;
                }
            } else {
                // looking for odd
                if( nums[i] % 2 == 1 ) {
                    ++c;
                    f = 0;
                }
            }
        }
        int d = 0; // odd even odd even
        f = 1;
        for(int i = 0; i < n; ++i) {
            if( f == 0 ) {
                // looking for even
                if( nums[i] % 2 == 0 ) {
                    ++d;
                    f = 1;
                }
            } else {
                // looking for odd
                if( nums[i] % 2 == 1 ) {
                    ++d;
                    f = 0;
                }
            }
        }

        return max({a,b,c,d});
    }
};
