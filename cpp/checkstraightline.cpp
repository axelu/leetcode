
// 1232. Check If It Is a Straight Line
// https://leetcode.com/problems/check-if-it-is-a-straight-line/


class Solution {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        auto n = coordinates.size();
        if( n == 2 ) return true;

        int x0 = coordinates[0][0];
        int y0 = coordinates[0][1];
        int x1 = coordinates[1][0] - x0;
        int y1 = coordinates[1][1] - y0;
        int x2,y2;
        for(int i = 2; i < n; ++i) {
            x2 = coordinates[i][0] - x0;
            y2 = coordinates[i][1] - y0;
            if( abs(x1 * y2 - x2 * y1) != 0 ) return false;
            // we are only dealing with int's, otherwise consider
            // if( abs(x1 * y2 - x2 * y1) > 1e-9 ) return false;
        }
        return true;
    }
};
