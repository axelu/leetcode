
// 319. Bulb Switcher
// https://leetcode.com/problems/bulb-switcher/



class Solution {
public:
    int bulbSwitch(int n) {
        if( n == 0 ) return 0;
        if( n < 3 )  return 1;

        int b = 1; // number of bulbs
        int d = 1; // difference
        int r = 0; // number of rounds = number of light bulbs turned on
        while(true) {
            d += 2;
            b += d;
            ++r;
            if( n == b ) return r+1;
            if( n <  b ) break;
        }
        return r;
    }
};
