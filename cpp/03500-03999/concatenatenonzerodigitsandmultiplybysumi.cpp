
// 3754. Concatenate Non-Zero Digits and Multiply by Sum I
// https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-i/



class Solution {
public:
    long long sumAndMultiply(int n) {
        if( n == 0 )
            return 0LL;

        string s = "";
        long long sum = 0LL;
        while( n ) {
            int rem = n % 10;
            if( rem != 0 )
                s.push_back('0'+rem);
            sum += rem;
            n /= 10;
        }
        reverse(begin(s), end(s));

        return stoll(s) * sum;
    }
};
