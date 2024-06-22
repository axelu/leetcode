
// 564. Find the Closest Palindrome
// https://leetcode.com/problems/find-the-closest-palindrome/




class Solution {
private:
    long long next_smaller_palindrome(long long x) {
        // returns greatest palindromic number less than x
        // it is guaranteed that smallest x is 1
        --x;

        if( x == 10LL )
            return 9LL;

        string str_x = to_string(x);
        int n = str_x.size();
        if( n == 1 )
            return x;

        string str_p(n,'#');
        for(int i = 0, j = n-1; i <= j; ++i,--j) {
            str_p[i] = str_x[i];
            str_p[j] = str_x[i];
        }
        long long p = stoll(str_p);
        if( p <= x )
            return p;

        int t = n / 2;
        if( n % 2 )
            ++t;

        string s(t,'#');
        for(int i = 0; i < t; ++i)
            s[i] = str_x[i];
        long long s_int = stoll(s);
        --s_int;
        s = to_string(s_int);
        if( s.size() < t ) {
            str_p.resize(n-1);
            for(int i = 0; i < n-1; ++i)
                str_p[i] = '9';
            p = stoll(str_p);
            return p;
        }

        for(int i = 0, j = n-1; i <= j; ++i,--j) {
            str_p[i] = s[i];
            str_p[j] = s[i];
        }
        p = stoll(str_p);

        return p;
    }

    long long next_greater_palindrome(long long x) {
        // returns smallest palindromic number greater than x
        // it is guaranteed that largets x is 999999999999999999
        ++x;

        string str_x = to_string(x);
        int n = str_x.size();
        if( n == 1 )
            return x;

        string str_p(n,'#');
        for(int i = 0, j = n-1; i <= j; ++i,--j) {
            str_p[i] = str_x[i];
            str_p[j] = str_x[i];
        }
        long long p = stoll(str_p);
        if( p >= x )
            return p;

        int t = n / 2;
        if( n % 2 )
            ++t;

        string s(t,'#');
        for(int i = 0; i < t; ++i)
            s[i] = str_x[i];
        long long s_int = stoll(s);
        ++s_int;
        s = to_string(s_int);
        for(int i = 0, j = n-1; i <= j; ++i,--j) {
            str_p[i] = s[i];
            str_p[j] = s[i];
        }
        p = stoll(str_p);

        return p;
    }

public:
    string nearestPalindromic(string n) {
        // LLONG_MAX 9223372036854775807
        // 1e18      1000000000000000000
        // 1e18 - 1   999999999999999999

        long long int_n = stoll(n);
        long long a = next_smaller_palindrome(int_n);
        long long b = next_greater_palindrome(int_n);

        long long an = int_n - a;
        long long bn = b - int_n;
        if( an < bn )
            return to_string(a);
        else if( bn < an )
            return to_string(b);
        else
            return to_string(a);
    }
};
