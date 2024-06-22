
// 479. Largest Palindrome Product
// https://leetcode.com/problems/largest-palindrome-product/




class Solution {
private:
    bool isPalindrome(unsigned long long x) {

        if ( x < 0ULL ) return false;
        if ( x < 10ULL ) return true;

        unsigned long long o = x;
        unsigned long long r = 0;
        while ( x > 0ULL ) {

            r = (r * 10ULL) + (x % 10ULL);
            x /= 10ULL;

        }
        return ( r == o ) ? true : false;
    }

    int reverse(int x) {
        int r = 0;

        while( x > 0 ) {
            int rem = x % 10;
            r = r * 10 + rem;
            x /= 10;
        }

        return r;
    }

public:
    int largestPalindrome(int n) {
        // 1 <= n <= 8

        /*
        unsigned long long a = 99999999; // 1e8 - 1
        unsigned long long b = 99999999; // 1e8 - 1
        unsigned long long c = a * b;   // c = 9999999800000001
        cout << c << endl;              //     9999999800000001
        cout << ULLONG_MAX << endl;     // 18446744073709551615
        cout << LLONG_MAX << endl;      //  9223372036854775807
        cout << LONG_MAX << endl;       //  9223372036854775807
        */

        // brute force to see pattern
        /*
        unsigned long long ans = 0;
        unsigned long long f, x, y;
        unsigned long long s = 9999;
        for(unsigned long long d = s; d > s/10ULL; --d)
            for(unsigned long long e = s; e > s/10ULL; --e) {
                f = d * e;
                if( isPalindrome(f) && f > ans) {
                    x = d;
                    y = e;
                    ans = f;
                }
            }
        cout << ans << endl; // still need to take modulo 1337
        cout << x << endl;
        cout << y << endl;
        // n = 1 -> x = 9, y = 1, ans =  9 % 1337 = 9
        // n = 2 -> x = 99, y = 91, ans = 9009 % 1337 = 987
        // n = 3 -> x = 993, y = 913, ans = 906609 % 1337 = 123
        // n = 4 -> x = 9999, y = 9901; ans = 99000099 % 1337 = 597
        // n = 5 -> x = 99979, y = 99681, ans = 9966006699 % 137 = 677
        // n = 6 -> x = 999999, y = 999001, ans = 999000000999 % 1337 = 1218
        // n = 7 -> x = 9998017, y = 9997647, ans = 99956644665999 % 1337 = 877
        // n = 8 -> x = 99999999, y = 99990001, ans = 9999000000009999 % 1337 = 475
        */

        if( n == 1 )
            return 9;

        const long mod = 1337L;

        // let us construct the possible palindromes starting from the largest
        // then we will try to divide starting from the largest possible factor till we find a divisor resulting 0 remainder
        // the divisor has to be equal or larger then sqrt(palindrome)
        long offset = pow(10, n);
        long mx = offset - 1;     // cout << "mx " << mx << endl;
        long mn = pow(10, n-1);   // cout << "mn " << mn << endl;
        for(long a = mx; a >= mn; --a) {
            long palindrome = a * offset + reverse(a);
            // cout << palindrome << endl;

            for(long i = mx; i * i >= palindrome; --i)
                if( palindrome % i == 0L ) {
                    cout << palindrome << endl;
                    cout << i << endl;
                    cout << palindrome / i << endl;
                    return palindrome % mod;
                }
        }

        return -1; // we should never get here
    }
};
