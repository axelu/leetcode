
// 1678. Goal Parser Interpretation
// https://leetcode.com/problems/goal-parser-interpretation/




class Solution {
public:
    string interpret(string command) {
        size_t n = command.size();
        if( n == 1 ) return "G";

        string r = "";
        for(int i = 0; i < n; ++i) {
            if( command[i] == 'G' ) {
                r += "G";
            } else if( command[i] == '(' ) {
                if( command[i+1] == ')' ) {
                    r += "o";
                    ++i;
                } else {
                    r += "al";
                    i += 3;
                }
            }
        }

        return r;
    }
};
