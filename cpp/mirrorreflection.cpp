
// 858. Mirror Reflection
// https://leetcode.com/problems/mirror-reflection/
// day 17 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/566/week-3-november-15th-november-21st/3534/



class Solution {
public:
    int mirrorReflection(int p, int q) {
        // great solution to let the box grow vertically while counting number of reflections
        // the figure in below post says it all
        // https://leetcode.com/problems/mirror-reflection/discuss/939143/C%2B%2B-Geometry-mirror-game

        int m = 1; // extension count of room
        int n = 1; // reflection count of laser ray
        while(m * p != n * q) {
            n++;
            m = n * q / p;
        }
        if( m % 2 == 0 && n % 2 == 1 ) return 0;
        if( m % 2 == 1 && n % 2 == 1 ) return 1;
        if( m % 2 == 1 && n % 2 == 0 ) return 2;
        return -1;
    }
};
