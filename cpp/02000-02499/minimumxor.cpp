
// 2429. Minimize XOR
// https://leetcode.com/problems/minimize-xor/



class Solution {
private:
    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

public:
    int minimizeXor(int num1, int num2) {
        int setbits_num1 = countSetBits(num1);
        int setbits_num2 = countSetBits(num2);

        if( setbits_num1 == setbits_num2 ) {
            return num1;

        } else if( setbits_num1 > setbits_num2 ) {
            // fill in the setbits in x from left to right
            int x = 0;
            for(int i = 29; setbits_num2 > 0 && i >= 0; --i) {
                if( (num1 >> i) & 1 ) {
                    x |= 1 << i;
                    --setbits_num2;
                }
            }
            return x;

        } else { // setbits_num1 < setbits_num2
            // fill in all not set bits from right to left
            int x = num1;
            int k = setbits_num2 - setbits_num1;
            for(int i = 0; k > 0 && i <= 29; ++i) {
                if( !((num1 >> i) & 1) ) {
                    x |= 1 << i;
                    --k;
                }
            }
            return x;
        }
    }
};
