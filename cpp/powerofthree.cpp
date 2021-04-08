
// Power of Three
// https://leetcode.com/problems/power-of-three/


class Solution {
public:
    bool isPowerOfThree(int n) {
        if( n < 1 ) return false;
        return regex_match(convertToBase3(n), regex("^10*$"));
    }
private:
    string convertToBase3(int n) {
        string r;
        while( n > 0 ) {
            r.insert(r.begin(), '0' + n % 3);
            n /= 3;
        }
        return r;
    }
};
