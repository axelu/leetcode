
// 1556. Thousand Seperator
// https://leetcode.com/problems/thousand-separator/

class Solution {
public:
    string thousandSeparator(int n) {
        if( n == 0 ) return "0";

        string r;
        int c = 0;
        while( n > 0 ) {
            if( c != 0 && c % 3 == 0 ) r.insert(r.begin(),'.');
            int rem = n % 10;
            r.insert(r.begin(), rem + '0');
            n /= 10;
            ++c;
        }

        return r;
    }
};
