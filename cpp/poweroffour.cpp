
// 342. Power of Four
// https://leetcode.com/problems/power-of-four/submissions/




class Solution {
private:
    string convertToBase4(int n) {
        string r;
        while( n > 0 ) {
            r.insert(r.begin(), '0' + n % 4);
            n /= 4;
        }
        return r;
    }

public:
    bool isPowerOfFour(int n) {
        if( n < 1 ) return false;
        return regex_match(convertToBase4(n), regex("^10*$"));
    }
};
