
// 2843. Count Symmetric Integers
// https://leetcode.com/problems/count-symmetric-integers/



class Solution {
private:
    bool is_symetric(int n) {
        int digit[5];
        int cnt = 0;

        while( n > 0 ) {
            digit[cnt] = n % 10;
            ++cnt;
            n /= 10;
        }

        if( cnt % 2 )
            return false;

        int h0 = 0, h1 = 0;
        for(int i = 0; i < cnt; ++i) {
            if( i < cnt/2 )
                h0 += digit[i];
            else
                h1 += digit[i];
        }

        return h0 == h1;
    }
public:
    int countSymmetricIntegers(int low, int high) {
        // 2 * n digits -> even number of digits
        // 1 <= low <= high <= 10000

        int ans = 0;
        for(int i = low; i <= high; ++i) {
            if( is_symetric(i) )
                ++ans;
        }

        return ans;
    }
};
