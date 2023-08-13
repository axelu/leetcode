
// 2745. Construct the Longest New String
// https://leetcode.com/problems/construct-the-longest-new-string/



/* x * "AA"
 * y * "BB"
 * z * "AB"
 *
 * we cannot combine: "AA"+"AA", "AA"+"AB", "AB"+"BB", "BB"+"BB"
 * we can combine:    "AA"+"BB", "BB"+"AA", BB"+"AB", "AB"+"AA", "AB"+"AB"
 *
 * 3*51*51*51 = 397953
 */
class Solution {
private:
    int mem[3][51][51][51];

    int rec(int last, int x, int y, int z) {
        if( x == 0 && y == 0 && z == 0 )
            return 0;

        if( mem[last][x][y][z] != -1 )
            return mem[last][x][y][z];

        int ret = 0;

        if( last == 0 ) { // placed AA before
            if( y > 0 )
                ret = max(ret, 2 + rec(1,x,y-1,z));

        } else if( last == 1 ) { // placed BB before
            if( x > 0 )
                ret = max(ret, 2 + rec(0,x-1,y,z));
            if( z > 0 )
                ret = max(ret, 2 + rec(2,x,y,z-1));

        } else { // last == 2    // placed AB before
            if( x > 0 )
                ret = max(ret, 2 + rec(0,x-1,y,z));
            if( z > 0 )
                ret = max(ret, 2 + rec(2,x,y,z-1));
        }

        return mem[last][x][y][z] = ret;
    }
public:
    int longestString(int x, int y, int z) {
        memset(mem,-1,sizeof mem);

        int ans = 0;
        if( x > 0 )
            ans = 2 + rec(0,x-1,y,z);
        if( y > 0 )
            ans = max(ans, 2 + rec(1,x,y-1,z));
        if( z > 0 )
            ans = max(ans, 2 + rec(2,x,y,z-1));

        return ans;
    }
};
