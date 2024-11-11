
// 3314. Construct the Minimum Bitwise Array I
// https://leetcode.com/problems/construct-the-minimum-bitwise-array-i/




/* prime numbers 1-1000
 * 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997
 * 168 prime numbers
 */

class Solution {
private:
    pair<int,int> getleftmostsetbitandrightmostunsetbit(int x) {
        int rightmostunsetbit = -1;
        int i = 0;
        while( x ) {
           if( rightmostunsetbit == -1 && !(x & 1) )
                rightmostunsetbit = i;
            x >>= 1;
            ++i;
        }
        int leftmostsetbit = i - 1;
        if( rightmostunsetbit == -1 )
            rightmostunsetbit = i;
        return {leftmostsetbit, rightmostunsetbit};
    }

public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        // nums is an array of prime integers
        int n = nums.size();

        vector<int> ans(n);

        // what happens if we add 1 two a number?
        // the rightmost unset bit will be set and all bits to its right become unset.
        // prime numbers are odd except 2, so all primes > 2 have the 0 bit set

        // ans[i] | (ans[i] + 1) == nums[i] where ans[i] is minimize


        for(int i = 0; i < n; ++i) {
            if( nums[i] == 2 ) {
                ans[i] = -1;
            } else {
                auto [leftmostsetbit, rightmostunsetbit] = getleftmostsetbitandrightmostunsetbit(nums[i]);
                if( rightmostunsetbit > leftmostsetbit ) {

                    // example 7
                    // 7 binary  111
                    //           011   <- (7>>1) = 3
                    //           100   <- 3 + 1  = 4
                    // 3 | 4 = 7

                    ans[i] = (nums[i]>>1);

                } else {

                    // we need to clear the (rightmostunsetbit - 1) bit
                    // example 23
                    // 23 binary 10111  <- leftmostsetbit = 4, rightmostunsetbit = 3
                    //           10011  <- clear the (rightmostunsetbit - 1) = 19
                    //           10100  <- 19 + 1 = 20
                    // 19 | 20 = 23

                    ans[i] = nums[i] & ~(1 << (rightmostunsetbit - 1)); // unset bit
                }
            }
        }


        return ans;
    }
};
