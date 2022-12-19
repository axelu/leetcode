
// 233. Number of Digit One
// https://leetcode.com/problems/number-of-digit-one/



class Solution {
public:
    int countDigitOne(int n) {
        if( n == 0 )
            return 0;
        if( n < 10 )
            return 1;


        string s = to_string(n);
        int s_sz = s.size();

        long base = 1;
        long pre  = s[s_sz-1] == '0' ? 0 : 1;
        long f    = 10;
        long nbr  = s[s_sz-1]-'0';

        long t;

        // from right to left
        for(int i = s_sz-2; i >= 0; --i) {
            int digit = s[i]-'0';

            if( digit == 0 ) // this cannot be the end
                t = f + 10 * base;
            else if( digit == 1 ) {
                t = (1 + nbr) + base + pre;
                pre = t;
            } else { // digit > 1
                t = f + digit*base + pre;
                pre = t;
            }

            nbr = f * digit + nbr;

            base = f + 10 * base;
            f *= 10;
        }

        return t;
    }
};
