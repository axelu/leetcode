
// 762. Prime Number of Set Bits in Binary Representation
// https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/




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
    int countPrimeSetBits(int L, int R) {
        int ans = 0, nbrSetBits;
        for(; L <= R; ++L) {
            nbrSetBits = countSetBits(L);
            if( nbrSetBits == 2 ||
                nbrSetBits == 3 ||
                nbrSetBits == 5 ||
                nbrSetBits == 7 ||
                nbrSetBits == 11 ||
                nbrSetBits == 13 ||
                nbrSetBits == 17 ||
                nbrSetBits == 19 ) ++ans;
        }
        return ans;
    }
};
