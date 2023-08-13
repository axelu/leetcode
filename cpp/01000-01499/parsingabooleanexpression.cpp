
// 1106. Parsing A Boolean Expression
// https://leetcode.com/problems/parsing-a-boolean-expression/





class Solution {
private:
    bool parseBoolExpr(string& expr, int& i) {
        // cout << "i " << i << endl;
        if( expr[i] == 't' ) {
            ++i;
            return true;
        } else if( expr[i] == 'f' ) {
            ++i;
            return false;
        }

        char op = expr[i];
        // operation is followed by an open parenthesis
        i += 2;
        stack<bool> stck;
        while(true) {
            if( expr[i] == 't' ) {
                stck.push(true);
                ++i;
            } else if( expr[i] == 'f' ) {
                stck.push(false);
                ++i;
            } else if( expr[i] == ',' ) {
                ++i;
            } else if( expr[i] == ')' ) {
                ++i;
                break;
            } else {
                // expr[i] either '!', '&' or '|'
                stck.push(parseBoolExpr(expr,i));
            }
        }

        // evaluate the stack
        if( op == '!' ) {
            // if the operation is '!' our stack should only have one element
            return !stck.top();
        } else {
            if( op == '&' ) {
                while( !stck.empty() ) {
                    if( stck.top() == false )
                        return false;
                    stck.pop();
                }
                return true;
            } else { // op == '|'
                while( !stck.empty() ) {
                    if( stck.top() == true )
                        return true;
                    stck.pop();
                }
                return false;
           }
        }
    }

public:
    bool parseBoolExpr(string expression) {
        int i = 0;
        return parseBoolExpr(expression,i);
    }
};
