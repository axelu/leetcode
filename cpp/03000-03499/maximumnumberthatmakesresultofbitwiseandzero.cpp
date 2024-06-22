
// 3125. Maximum Number That Makes Result of Bitwise AND Zero
// https://leetcode.com/problems/maximum-number-that-makes-result-of-bitwise-and-zero/





class Solution {
private:
    int leftmostbit(long long x) {
        // x > 0
        int ret;
        for(int i = 63; ; --i)
            if( (x >> i) & 1LL )
                return i;

        return -1;
    }

public:
    long long maxNumber(long long n) {
        // 1 <= n <= 1e15
        // 1e15 = 1000000000000000 -> binary 11100011010111111010100100110001101000000000000000 50 digits

        if( n == 1LL )
            return 0;

        int _leftmostbit = leftmostbit(n);
        return pow(2, _leftmostbit) - 1LL;
    }
};
