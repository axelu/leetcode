
// 3648. Minimum Sensors to Cover Grid
// https://leetcode.com/problems/minimum-sensors-to-cover-grid/


/*
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
  0
  1
  2       x      |      x      |
  3
  4
  5
  6
  7
  8
  9
 */
class Solution {
public:
    int minSensors(int n, int m, int k) {
        int cover = 2 * k + 1;

        int _n = n / cover;
        if( n % cover != 0 )
            ++_n;
        int _m = m / cover;
        if( m % cover != 0 )
            ++_m;

        return _n * _m;
    }
};
