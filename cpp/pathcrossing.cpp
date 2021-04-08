
// Path Crossing
// https://leetcode.com/problems/path-crossing/


class Solution {
public:
    bool isPathCrossing(string path) {
        if( path.size() == 1 ) return false;

        set<pair<int,int>> pts;
        int x = 0;
        int y = 0;
        pts.insert({x,y});
        for(char c : path) {
            switch (c) {
                case 'N': ++y;
                          break;
                case 'S': --y;
                          break;
                case 'E': --x;
                          break;
                case 'W': ++x;
                          break;
            }
            if ( !pts.insert({x,y}).second ) return true;
        }

       return false;
    }
};
