
// 3749. Evaluate Valid Expression
// https://leetcode.com/problems/evaluate-valid-expressions/



class Solution {
private:
    long long rec(string& expression, int& pos) {
        int n = expression.size();

        long long ret = 0LL;

        // pos is either start of an operation or start of an integer literal
        if( isdigit(expression[pos]) || expression[pos] == '-' ) {
            // integer literal
            // collect the minus sign if there is one
            long long m = 1LL;
            if( expression[pos] == '-' ) {
                m = -1LL;
                ++pos;
            }
            // collect all digits
            while( pos < n && isdigit(expression[pos]) ) {
                ret = ret * 10LL + (long long)(expression[pos]-'0');
                ++pos;
            }
            ret *=  m;

        } else {
            // operation
            char op = expression[pos];
            pos = pos + 4;
            // collect operand 0
            long long o0 = rec(expression, pos);
            // collect operand 1
            long long o1 = rec(expression, pos);
            // perform op
            switch (op) {
                case 'a': ret = o0 + o1; break;
                case 's': ret = o0 - o1; break;
                case 'm': ret = o0 * o1; break;
                case 'd': ret = o0 / o1; break;
            }
        }

        ++pos;
        return ret;
    }

public:
    long long evaluateExpression(string& expression) {
        int n = expression.size();
        int pos = 0;

        // edge case
        if( isdigit(expression[pos]) || expression[pos] == '-' ) {
            // collect the minus sign if there is one
            long long m = 1LL;
            if( expression[pos] == '-' ) {
                m = -1LL;
                ++pos;
            }
            // collect all digits
            long long o = 0LL;
            while( pos < n ) {
                o = o * 10LL + (long long)(expression[pos]-'0');
                ++pos;
            }
            o = o * m;

            return o;
        }

        return rec(expression, pos);
    }
};
