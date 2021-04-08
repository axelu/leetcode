
// https://leetcode.com/problems/crawler-log-folder/

class Solution {
public:
    int minOperations(vector<string>& logs) {
        int depth = 0;
        for(string s: logs) {
            if( s == "../" ) {
                if( depth != 0 ) --depth;
            } else if ( s != "./" ) {
                ++depth;
            }
        }
        return depth;
    }
};
