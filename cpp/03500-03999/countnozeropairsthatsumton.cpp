
// 3704. Count No-Zero Pairs That Sum to N
// https://leetcode.com/problems/count-no-zero-pairs-that-sum-to-n/


class Solution {
private:
    vector<int> int2vector(long long num) {
        vector<int> ret;
        while( num > 0 ) {
            ret.push_back(num % 10LL);
            num /= 10LL;
        }
        // reverse(begin(ret),end(ret));
        return ret;
    }

    // pos a_sz b_sz carry
    long long mem[16][17][17][2];

    long long rec(vector<int>& nums, int n, int pos, int a_sz, int b_sz, bool carry) {
        // int n = nums.size();
        if( pos == n )
            return (long long)!carry;

        if( mem[pos][a_sz][b_sz][carry] != -1LL )
            return mem[pos][a_sz][b_sz][carry];

        // if we are at a pos >= a_sz, then we are done with a, we set the a digit to 0
        // same applies for b
        int a_begin_digit = 0;
        int a_end_digit = 0;
        if( pos < a_sz ) {
            a_begin_digit = 1;
            a_end_digit = 9;
        }
        int b_begin_digit = 0;
        int b_end_digit = 0;
        if( pos < b_sz ) {
            b_begin_digit = 1;
            b_end_digit = 9;
        }

        long long ret = 0LL;

        for(int a_digit = a_begin_digit; a_digit <= a_end_digit; ++a_digit) {
            for(int b_digit = b_begin_digit; b_digit <= b_end_digit; ++b_digit) {
                int digit_sum = a_digit + b_digit + carry;
                int digit = digit_sum % 10;
                if( digit == nums[pos] ) {
                    bool carry_new = digit_sum >= 10;
                    ret += rec(nums, n, pos+1, a_sz, b_sz, carry_new);
                }
            }
        }

        return mem[pos][a_sz][b_sz][carry] = ret;
    }

public:
    long long countNoZeroPairs(long long n) {
        // 2 <= n <= 1e15
        // worst case 1e15 = 1000000000000000 16 digits

        // idea
        //    n = a + b
        //    at most a + b have as many digits as n
        //    we try 1..9 at each digit for a and b
        //    if we have a digit pair that sums to the digit
        //    at the current position in n, we move on to next position
        //    we do that from right to left and make sure we carry

        // for easier processing, we return digits in reversed order
        // so we can go left to right
        vector<int> nums = int2vector(n);
        int nums_sz = nums.size();

        long long ans = 0LL;

        memset(mem,-1LL,sizeof mem);
        for(int a_sz = 1; a_sz <= nums_sz; ++a_sz)      // length of a
            for(int b_sz = 1; b_sz <= nums_sz; ++b_sz)  // length of b
                ans += rec(nums, nums_sz, 0, a_sz, b_sz, 0);

        return ans;
    }
};
