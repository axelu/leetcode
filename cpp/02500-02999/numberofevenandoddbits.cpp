
// 2595. Number of Even and Odd Bits
// https://leetcode.com/problems/number-of-even-and-odd-bits/



class Solution {
public:
    vector<int> evenOddBit(int n) {

        int even = 0;
        int odd  = 0;

        for(int i =  0; i < 31; ++i)
            if( (n >> i) & 1 ) {
                if( i % 2 == 0 )
                    ++even;
                else
                    ++odd;
            }

        return {even,odd};
    }
};
