
// 2337. Move Pieces to Obtain a String
// https://leetcode.com/problems/move-pieces-to-obtain-a-string/



class Solution {
public:
    bool canChange(string start, string target) {
        // it can be achieved if the number of consecutive Ls and Rs is the same

        int n = start.size(); // start.size() == target.size()

        int i = 0;  // index in start
        int j = 0;  // index in target
        for(; i < n; ++i) {
            if( start[i] == '_' )
                continue;

            while( j < n && target[j] == '_' )
                ++j;

            if( j == n || start[i] != target[j] )
                return false;

            if( target[j] == 'L' ) {
                if( i < j )
                    return false;
            } else {
                if( i > j )
                    return false;
            }

            ++j;
        }
        // finish up
        for(; j < n; ++j) {
            if( target[j] != '_' )
                return false;
        }

        return true;
    }
};
