
// 1780. Check if Number is a Sum of Powers of Three
// https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three/

class Solution {
public:
    bool checkPowersOfThree(int n) {
        // 1 <= n <= 10^7

        int p3[15];
        int k = 1;
        for(int i = 0; i < 15; ++i) {
            p3[i] = k;
            k *= 3;
        }

        int t;
        for(int i = 1; i < 32768; ++i) {
            t = 0;
            for(int j = 0; j < 15; ++j)
                if( (i >> j) & 1 ) {
                    t += p3[j];
                    if( t >= n )
                        break;
                }
            if( t == n )
                return true;
        }

        return false;
    }
};
