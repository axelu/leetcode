
// 3448. Count Substrings Divisible By Last Digit
// https://leetcode.com/problems/count-substrings-divisible-by-last-digit/





/* 0 if we are at an index i where s[i] == '0'
 *    ignore
 *
 * 1 if we are at an index i where s[i] == '1'
 *     any substring ending at i is divisible, we need to
 *     discounts 0's
 *      01234567
 *     "32050051"
 *             *
 *     answer if we are at i = 7:
 *     i + 1 substrings end at i, we saw 3 zeros => (7+1) - 3 = 5
 *
 * 2 if we are at an index i where s[i] == '2'
 *     same math as if it would be 1
 *
 * 3 if we are at an index i where s[i] == '3'
 *     A number is divisible by 3 if and only if
 *     the sum of its digits is divisible by 3.
 *     How many end at i where this constraint is true?
 *
 * 4 if we are at an index i where s[i] == '4'
       if last two digits form a number devisible by 4
       and of course 4 itself
 *
 * 5 if we are at an index i where s[i] == '5'
 *     same math as if it would be 1, or 2
 *
 * 6 if we are at an index i where s[i] == '6'
 *    A number is divisible by 6 = 2 × 3 if and only if
 *    it is divisible by 2 and by 3.
 *
 * 7 if we are at an index i where s[i] == '7'
 *    see below, was able to come up with all others but 7
 *    adopted another solution
 *
 * 8 if we are at an index i where s[i] == '8'
 *    A number is divisible by 8 if and only if
 *    its last three digits form a number divisible by 8.
 *    There are alternative rules
 *
 * 9 if we are at an index i where s[i] == '9'
 *    A number is divisible by 9 if and only if
 *   the sum of its digits is divisible by 9.
 */

class Solution {
private:
    long long modPow(long long a, long long x, long long MOD) {
        // return a^x mod MOD
        long long res = 1;
        while(x>0) {
            if( x & 1 ) res = (res*a) % MOD;
            a = (a*a) % MOD;
            x >>= 1;
        }
        return res;
    }

    long long modInverse(long long a, long long MOD) {
        // return modular multiplicative of: a mod MOD
        return modPow(a,MOD-2, MOD);
    }


public:
    long long countSubstrings(string s) {
        int n = s.size(); // 1 <= s.length <= 1e5; s consists of digits only

        /*
        auto v = primeFactors(253);
        for(int pf: v)
            cout << pf << " ";
        cout << endl;
        */

        long long ans = 0LL;

        // 1, 2, 4, 5 and 8
        for(int i = 0; i < n; ++i) {
            int c = s[i] - '0';
            if( c == 1 || c == 2 || c == 5 ) {
                long long t = (i+1);
                ans += t;
            }
            if( c == 4 ) {
                ++ans; // our 4 itself
                if( i > 0 && (((10 * (int)(s[i-1] - '0')) + 4) % 4) == 0 )
                    ans += i;
            }
            if( c == 8 ) {
                ++ans; // our 8 itself
                if( i > 0 ) {
                    int a = (10 * (int)(s[i-1] - '0')) + 8;
                    if( a % 8 == 0 )
                        ++ans;
                }
                if( i > 1 ) {
                    int a = (100 * (int)(s[i-2] - '0')) + (10 * (int)(s[i-1] - '0')) + 8;
                     if( a % 8 == 0 )
                        ans += i-1;
                }
            }
        }

        // 3, 6 and 9
        // pass 1 prefix sum right to left 0 indexed
        vector<int> prefixSumrl(n);
        prefixSumrl[n-1] = s[n-1] - '0';
        for(int i = n-2; i >= 0; --i)
            prefixSumrl[i] = prefixSumrl[i+1] + (int)(s[i] - '0');
        // pass 2 left to right
        vector<int> rem3(3,0);
        vector<int> rem6(6,0);
        vector<int> rem9(9,0);
        for(int i = 0; i < n; ++i) {
            int c = s[i] - '0';

            int _rem3 = prefixSumrl[i] % 3;
            ++rem3[_rem3];
            if( c == 3 )
                ans += rem3[_rem3];

            int _rem6 = prefixSumrl[i] % 6;
            ++rem6[_rem6];
            if( c == 6 ) {
                ans += rem6[_rem6];
                // we know its also divisible by 2
                // so we need to also count divisble by 3
                int _rem63 = (_rem6 + 3) % 6;
                ans += rem6[_rem63];
            }

            int _rem9 = prefixSumrl[i] % 9;
            ++rem9[_rem9];
            if( c == 9 )
                ans += rem9[_rem9];
        }

        // 7
        // Because 10 is identical to 3 (mod 7) and 3 has a cycle of 6 mod 7, precompute prefix remainders mod 7
        // maintain a 2D frequency table based on index mod 6 to adjust for the power-of-10 effect
        /*
        for(int i = 0; i < 6; ++i)
            cout << i << ":" << modInverse(pow(10,i), 7) << " ";
        cout << endl;
        // output 0:1 1:5 2:4 3:6 4:2 5:3
        */
        /*
        // pass 1 calc 'prefix remainder' for mod 7
        vector<int> prefixRem7(n);
        prefixRem7[0] = ((int)(s[0] - '0')) % 7;
        for(int i = 1; i < n; ++i) {
            int c = s[i] - '0';
            prefixRem7[i] = ((10 * prefixRem7[i-1]) + c) % 7;
        }
        // pass 2
        // frequence array for remainder count
        vector<vector<long long>> freq7(6, vector<long long>(7,0));
        for(int i = 0; i < n; ++i) {
            int c = s[i] - '0';

            if( c == 7 ) {
                if( prefixRem7[i] == 0 )
                    ++ans;
                for (int m = 0; m < 6; ++m) {
                    int idx = ((i % 6) - m + 6) % 6;
                    int req = (prefixRem7[i] * modInverse(pow(10,m), 7)) % 7;
                    ans += freq7[idx][req];
                }
            }
            ++freq7[i % 6][prefixRem7[i]];
        }
        */
        // TODO we could initialize once modPow10(100001) globally
        vector<int> modPow10(n+1);
        modPow10[0] = 1;
        for(int i = 1; i <= n; ++i)
            modPow10[i] = (10 * modPow10[i-1]) % 7;

        vector<int> prefixRem7(n+1);
        prefixRem7[0] = 0;
        vector<int> rem7(7,0);
        rem7[0] = 1;
        for(int i = 0; i < n; ++i) {
            int c = s[i] - '0';

            prefixRem7[i+1] = ((10 * prefixRem7[i]) + c) % 7;
            int _rem7 = ((long long)prefixRem7[i+1] * modInverse(modPow10[i+1],7)) % 7;

            if( c == 7 ) {
                ans += rem7[_rem7];
            }

            ++rem7[_rem7];
        }

        return ans;
    }
};
