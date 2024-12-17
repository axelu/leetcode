
// 3370. Smallest Number With All Set Bits
// https://leetcode.com/problems/smallest-number-with-all-set-bits/




class Solution {
public:
    int smallestNumber(int n) {
        // 1 <= n <= 1000

        int x = 1;
        while ( ((x * 2) - 1) < n ) {
            x = (x * 2);
        }

        return x*2 - 1;
    }
};
