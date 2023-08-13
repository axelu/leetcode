
// 2749. Minimum Operations to Make the Integer Zero
// https://leetcode.com/problems/minimum-operations-to-make-the-integer-zero/




class Solution {
private:
    int countSetBits(long i) {
        unsigned int count = 0;
        while(i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

public:
    int makeTheIntegerZero(int num1, int num2) {
        if( num2 >= num1 )
            return -1;

        long _num1 = num1;
        int ops = 0; // nbr operations
        while(true) {
            ++ops;

            // operation: num1 = num1 - ((2^i) + num2) with i in range [0,60] inclusive
            // so if at each step we remove num2 from num1,
            // we can check if we are able to get the remaining num1 to 0 with only
            // subtracting powers of 2 within less or equal number of current operations

            _num1 -= num2;
            if( _num1 < 0 )
                break;

            // min steps needed is number of set bits in _num1
            int setbits = countSetBits(_num1);
            // max steps needed is _num1 itself, as we could remove 2^0 = 1 step by step
            // hence
            if( setbits <= ops && ops <= _num1 )
                return ops;
        }

        return -1;
    }
};
