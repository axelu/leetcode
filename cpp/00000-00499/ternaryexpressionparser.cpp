
// 439. Ternary Expression Parser
// https://leetcode.com/problems/ternary-expression-parser/




class Solution {
    char rec(string& expression, int n, int& pos) {

        // ternary expression a?b:c


        char a = expression[pos];
        if( pos == n-1 )
            return a;

        ++pos;
        if( expression[pos] == ':' ) {
            ++pos;
            return a;
        }

        // we are at '?'
        ++pos;
        char b = rec(expression,n,pos);
        char c = rec(expression,n,pos);

        return a == 'T' ? b : c;
    }


    public:
    string parseTernary(string& expression) {
        int n = expression.size();

        int pos = 0;
        string s(1,rec(expression,n,pos));
        return s;
    }
};
