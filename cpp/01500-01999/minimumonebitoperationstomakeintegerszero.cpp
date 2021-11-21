// 1611. Minimum One Bit Operations to Make Integers Zero
// https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/


class Solution {
public:
    int minimumOneBitOperations(int n) {
        // 0 <= n <= 10e9

        // https://en.wikipedia.org/wiki/Gray_code
        // Decimal  Binary  Gray
        // 0        0000 	0000
        // 1 	    0001    0001
        // ...
        // 4 	    0100 	0110
        // 5        0101    0111
        // 6 	    0110    0101
        // ...
        // Example: input decimal 6
        // decimal 6 in binary is 0110
        // take that 0110 and translate to Gray Code
        // 0110 Gray is 4 decimal, hence our answer is four
        // it takes 4 moves using Gray code to get from 0000 to Gray 0110 -> '4'
        // hence it takes the same number moves to go opposite 0110 to 0000

        // from Wikipedia
        // https://en.wikipedia.org/wiki/Gray_code#Converting_to_and_from_Gray_code
        // uint GrayToBinary32(uint num)
        n ^= n >> 16;
        n ^= n >>  8;
        n ^= n >>  4;
        n ^= n >>  2;
        n ^= n >>  1;
        return n;
    }
};
