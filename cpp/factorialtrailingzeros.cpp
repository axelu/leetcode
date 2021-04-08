

// Factorial Trailing Zero's
// https://leetcode.com/problems/factorial-trailing-zeroes/


class Solution {
public:
    int trailingZeroes(int n) {
        int r = 0;

        // keep dividing by 5
        for (long long int i = 5; n / i >= 1; i *= 5)
            r += n / i;

        return r;
    }
};
