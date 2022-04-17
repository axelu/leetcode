
// 772. Basic Calculator III
// https://leetcode.com/problems/basic-calculator-iii/


// see 227. Basic Calculator II https://leetcode.com/problems/basic-calculator-ii/

class Solution {
private:
    void solv(deque<string>& o, string t) {
        if( o.empty() || o.back() == "+" || o.back() == "-" ) {
            // push operand
            o.push_back(t);
        } else {
            // o.top() == "*" || o.top() == "/"
            // get operation
            string op = o.back();
            o.pop_back();
            // get operand
            string od = o.back();
            o.pop_back();
            // execute operation
            long long a = stoll(od);
            long long b = stoll(t);
            long long r = op == "*" ? a * b : a / b;
            // push operand
            o.push_back(to_string(r));
        }
    }

    string calculate(string& s, int n, int& i) {

        deque<string> o; // operands and operations

        long long a, b, r;
        string t = "", op, od;
        char c;
        for(; i < n; ++i) {
            c = s[i];
            if( isdigit(c) ) {
                t += c;
            } else if( c != '(' && c != ')' ) {
                // c is an operation
                // t contains a number
                // top of stack is an operation unless stack is empty
                solv(o,t);
                // push operation and clear t
                t = c; // to convert c to string
                o.push_back(t);
                t = "";
            } else if( c == '(' ) {
                // opening parenthesis come after an operation OR
                // after another opening parenthesis OR at i = 0;
                ++i;
                t = calculate(s,n,i);
            } else if( c == ')' ) {
                break;
            }
        }

        // finish up
        if( o.empty() )
            return t;

        solv(o,t);

        // deque contains either 1 element OR
        // a +/- b +/- c ... +/- n with at least 3 elements (operand operation operand)
        od = o.front();
        o.pop_front();
        a = stoll(od);
        while( !o.empty() ) {
            op = o.front();
            o.pop_front();
            od = o.front();
            o.pop_front();
            b = stoll(od);
            a = op == "+" ? a + b : a - b;
        }

        return to_string(a);
    }

public:
    int calculate(string s) {
        int n = s.size();
        int i = 0;
        return stoi(calculate(s,n,i));
    }
};
