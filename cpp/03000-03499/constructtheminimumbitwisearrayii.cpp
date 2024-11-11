
// 3315. Construct the Minimum Bitwise Array II
// https://leetcode.com/problems/construct-the-minimum-bitwise-array-ii/




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
