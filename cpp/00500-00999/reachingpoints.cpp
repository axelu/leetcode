
// 780. Reaching Points
// https://leetcode.com/problems/reaching-points/





// credit to https://leetcode.com/problems/reaching-points/discuss/816596/EXPLANATION-or-For-math-dummies-like-me

class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {

        /*
        // approach #3: work backwards [TLE]
        while( tx >= sx && ty >= sy ) {
            if( sx == tx && sy == ty )
                return true;
            if( tx > ty )
                tx -= ty;
            else
                ty -= tx;
        }
        return false;
        */

        // apprach #4: work backwards modulo variant
        while( tx >= sx && ty >= sy ) {
            if( tx == ty )
                break;

            if( tx > ty ) {
                if( ty > sy )
                    tx %= ty;
                else
                    return (tx - sx) % ty == 0;

            } else {
                if( tx > sx )
                    ty %= tx;
                else
                    return (ty - sy) % tx == 0;
            }
        }

        return (tx == sx && ty == sy);
    }
};
