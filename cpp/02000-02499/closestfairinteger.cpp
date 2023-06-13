
// 2417. Closest Fair Integer
// https://leetcode.com/problems/closest-fair-integer/




// test case: n = 438146780, ans -> 1000001111

class Solution {
private:
    pair<bool,pair<int,int>> isfair(int x) {
        int odd = 0;
        int even = 0;

        while( x > 0 ) {
            if( (x % 10) % 2 ) {
                ++odd;
            } else {
                ++even;
            }
            x /= 10;
        }

        return {odd == even,{odd,even}};
    }

public:
    int closestFair(int n) {
        auto p = isfair(n);

        while( !p.first ) {
            int t = p.second.first + p.second.second;
            if( t % 2 ) {
                n = pow(10,t);
                p = isfair(n);
                continue;
            }
            ++n;
            p = isfair(n);
        }

        return n;
    }
};
