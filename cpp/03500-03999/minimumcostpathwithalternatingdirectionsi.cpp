
// 3596. Minimum Cost Path with Alternating Directions I
// https://leetcode.com/problems/minimum-cost-path-with-alternating-directions-i/




/* constraints given
   1 <= m, n <= 1e6
   but return is int
   MAX_INT               2147483647
   just entering dest 1000000000000 = 1000000 * 1000000
   just entering the last cell in max grid would exceed the return space,
   let alone the sum of getting there
   so there must be something else here, some trick?
   there are only 3 grid sizes with an answer
 */
class Solution {
private:

public:
    int minCost(int m, int n) {
        // m = 1, n = 1 -> ans 1
        // m = 2, n = 1 -> ans 3
        // m = 1, n = 2 -> ans 3
        // all others don't have an answer respectively ans = -1;

        if( m == 1 && n == 1 )
            return 1;
        else if( (m == 2 && n == 1) || (m == 1 && n == 2) )
            return 3;
        else
            return -1;
    }
};
