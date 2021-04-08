
// 722. Remove Comments
// https://leetcode.com/problems/remove-comments/




class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        int n = source.size();
        vector<string> ans;
        if( n == 0 ) return ans;

        int mode = 0; // 0 not inside a block comment, 1 inside a block comment
        string line, newLine = "";
        int m;
        for(int i = 0; i < n; ++i) {
            line = source[i];
            m = line.size();
            for(int j = 0; j < m; ++j) {

                /* If we start a block comment and we aren't in a block,
                 * then we will skip over the next two characters and
                 * change our state to be in a block. */
                if( j < m-1 && line[j] == '/' && line[j+1] == '*' ) {
                    if( mode == 0 ) {
                        mode = 1; // block mode
                        ++j;
                        continue;
                    }
                }

                /* If we end a block comment and we are in a block,
                 * then we will skip over the next two characters
                 * and change our state to be *not* in a block. */
                if( j < m-1 && line[j] == '*' && line[j+1] == '/' ) {
                    if( mode == 1 ) {
                        mode = 0; // not block mode
                        ++j;
                        continue;
                    }
                }

                /* If we start a line comment and we aren't in a block,
                 * then we will ignore the rest of the line. */
                if( j < m-1 && line[j] == '/' && line[j+1] == '/' ) {
                    if( mode == 0 ) {
                        break;
                    }
                }

                /* If we aren't in a block comment
                 * (and it wasn't the start of a comment),
                 * we will record the character we are at. */
                if( mode == 0 ) newLine += line[j];
            }
            // if we aren't in a block, record newLine
            if( mode == 0 && !newLine.empty() ) {
                ans.push_back(newLine);
                newLine = "";
            }
        }

        return ans;
    }
};
