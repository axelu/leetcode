
// 678. Valid Parenthesis String
// https://leetcode.com/problems/valid-parenthesis-string/


class Solution {
private:
    int mem[101][101];

    bool rec(string& s, int i, int j) {
        if( i == s.size() )
            return j == 0 ? true : false;

        if( mem[i][j] != -1 )
            return mem[i][j];

        bool ret = false;

        // we have a choice if the current char == '*'
        //    interpret as '(' or ')' or ''
        if( s[i] == '*' ) {
            ret = rec(s,i+1,j);           // interpret * as ''
            if( !ret ) {
                ret = rec(s,i+1,j+1);     // interpret * as '('
                if( !ret && j > 0 ) {
                    ret = rec(s,i+1,j-1); // interpret * as ')'
                }
            }

        } else if( s[i] == '(' ) {
            ret = rec(s,i+1,j+1);

        } else if( j > 0 ) {
            ret = rec(s,i+1,j-1);
        }

        return mem[i][j] = ret;
    }
public:
    bool checkValidString(string s) {

        // whenever we encounter a '(' we would add a ')' to our expectation
        // whenever we encounter a ')' we would consume from our expectation
        // a * we can interpret as '(' or ')' or ''
        // -> as we would only add ')' to our stack as expectation, we can
        //    simply just us a counter instead

        memset(mem,-1,sizeof mem);
        return rec(s,0,0);
    }
};
