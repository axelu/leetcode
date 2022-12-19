
// 2167. Minimum Time to Remove All Cars Containing Illegal Goods
// https://leetcode.com/problems/minimum-time-to-remove-all-cars-containing-illegal-goods/




/*
 * example
 * from right to left
 *  1   1   1   1   1   1   0   0   0   1   0   0   0   1   0
 * 15  14  13  12  11  10   6   6   6   6   2   2   2   2   0  cost to delete from the right
 * 16  14  12  10   8   6   4   4   4   4   2   2   2   2   0  cost to delete in middle
 * at any position we take the better (lower) cost
 */
class Solution {
private:
public:
    int minimumTime(string& s) {
        int n = s.size();

        // operations:
        // A  Remove a train car from the left,  cost: 1 unit of time.
        // B  Remove a train car from the right, cost: 1 unit of time.
        // C  Remove a train car from anywhere in the sequence, cost: 2 units of time.

        // left to right => operations A and C
        // we know that it takes i+1 units to remove [0,i] inclusive, which is one option
        // at any point along the way we can switch to removing from the middle for the cost of 2
        // if the car is legal, no need to remove it
        int lft[n]; // min cost to remove all illegal cars between [0,i] inclusive
        lft[0] = s[0] == '1' ? 1 : 0;
        for(int i = 1; i < n; ++i)
            if( s[i] == '1') {
                lft[i] = min(i+1, lft[i-1] + 2);
            } else {
                lft[i] = lft[i-1];
            }

        if( lft[n-1] == 0 ) // no illegal cars at all
            return 0;

        // right to left => operations B and C
        // otherwise same as before in reverse
        int rgt[n]; // min cost to remove all illegal cars between [i,n-1] inclusive
        rgt[n-1] = s[n-1] == '1' ? 1 : 0;
        for(int i = n-2; i >= 0; --i)
            if( s[i] == '1' ) {
                rgt[i] = min(n-i, rgt[i+1] + 2);
            } else {
                rgt[i] = rgt[i+1];
            }

        int ans = min(lft[n-1],rgt[0]);
        for(int i = 0; i < n-1; ++i)
            ans = min(ans, lft[i] + rgt[i+1]);

        return ans;
    }
};
