
// 371. Sum of Two Integers
// https://leetcode.com/problems/sum-of-two-integers/



class Solution {
public:
    int getSum(int a, int b) {

        while( b != 0 ) {
            // first get all the bits where bit in a and b is set
            // this is what we need to carry forward
            // (carry forward means shift left by 1)
            // example 1+1
            //      2^2 2^1 2^0
            //   1   0   0   1
            // + 1   0   0   1
            // = 2   0   1   0

            unsigned int c = a & b; // this is what we need to carry forward
                                    // meaning shift to the left

            // now we need to get all bits that are either set in a OR b
            a = a ^ b;

            // now shift our carry
            b = c << 1;

            // repeat till nothing more to shift
        }

        return a;
    }
};
