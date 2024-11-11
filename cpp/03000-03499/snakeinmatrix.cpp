
// 3248. Snake in Matrix
// https://leetcode.com/problems/snake-in-matrix/





class Solution {
public:
    int finalPositionOfSnake(int n, vector<string>& commands) {
        int i = 0;
        int j = 0;

        for(string& dir: commands) {
            if( dir == "RIGHT" )
                ++j;
            else if( dir == "DOWN" )
                ++i;
            else if( dir == "LEFT" )
                --j;
            else // dir == "UP"
                --i;
        }

        return i*n + j;
    }
};
