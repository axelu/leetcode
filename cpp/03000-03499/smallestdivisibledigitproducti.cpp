
// 3345. Smallest Divisible Digit Product I
// https://leetcode.com/problems/smallest-divisible-digit-product-i/




class Solution {
public:
    int smallestNumber(int n, int t) {

        // brute force
        // we will assume that it will halt

        for(int i = n; i < 100000; ++i) { // 100000 arbitrary

            int x = i;
            int p = 1;
            while( x ) {
                p *= (x % 10);
                x /= 10;
            }
            if( p % t == 0 )
                return i;
        }

        return -1;
    }
};
