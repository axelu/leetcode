
// 1317. Convert Integer to the Sum of Two No-Zero Integers
// https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/


class Solution {
private:
    bool isNoZeroInt(int i) {
        int rem;
        while( i > 0 ) {
            rem = i % 10;
            if( rem == 0 ) return false;
            i /= 10;
        }
        return true;
    }
public:
    vector<int> getNoZeroIntegers(int n) {
        vector<int> r(2);
        int a,b;
        for(int i = 1; i < n; ++i) {
            a = i;
            b = n - a;
            if( isNoZeroInt(a) && isNoZeroInt(b) ) {
                r[0] = a;
                r[1] = b;
                break;
            }
        }
        return r;
    }
};
