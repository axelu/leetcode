
// 1553. Minimum Number of Days to Eat N Oranges
// https://leetcode.com/problems/minimum-number-of-days-to-eat-n-oranges/





/*    2     2     2     2     2     2     2     2 ...
 *       3        3        3        3        3    ...
 * 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 ...
 */
class Solution {
private:

    unordered_map<int,long> mem;

    long rec(long i) {
        // cout << i << endl;

        if( i == 3 || i == 2 )
            return 2;
        if( i == 1 )
            return 1;

        if( mem[i] != 0L )
            return mem[i];

        // we have a choice
        //    if n is divisible by 3 eat 2 * (n / 3) OR
        //    if n is divisible by 2 eat n / 2 OR
        //    eat 1 orange

        long a = 1L + (i%3) + rec(i/3);
        long b = 1L + (i%2) + rec(i/2);

        return mem[i] = min(a,b);
    }

public:
    int minDays(int n) {

        return rec(n);
    }
};
