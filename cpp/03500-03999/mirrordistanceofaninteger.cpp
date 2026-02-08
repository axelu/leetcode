
// 3783. Mirror Distance of an Integer
// https://leetcode.com/problems/mirror-distance-of-an-integer/



class Solution {
public:
    int mirrorDistance(int n) {
        int x = n;
        int rev = 0;
        while( x ) {
            int rem = x % 10;
            rev = rev * 10 + rem;
            x /= 10;
        }

        return abs(n-rev);
    }
};
