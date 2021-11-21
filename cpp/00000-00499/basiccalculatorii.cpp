
// 227. Basic Calculator II
// https://leetcode.com/problems/basic-calculator-ii/
// day 24 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/567/week-4-november-22nd-november-28th/3542/


class Solution {
public:
    int calculate(string s) {
        deque<string> o; // operands and operations
        
        long long a, b, r;
        string t = "", op, od;
        for(char c : s) {
            if( isdigit(c) ) {
                t += c;
            } else if ( !isblank(c) ) {
                // t contains a number
                // top of stack is an operation unless stack is empty
                if( o.empty() || o.back() == "+" || o.back() == "-" ) {
                    // push operand
                    o.push_back(t);
                } else {
                    // o.top() == "*" || o.top() == "/"
                    // get operation
                    op = o.back();
                    o.pop_back();
                    // get operand
                    od = o.back();
                    o.pop_back();
                    // execute operation
                    a = stoll(od);
                    b = stoll(t);
                    r = op == "*" ? a * b : a / b;
                    // push operand
                    o.push_back(to_string(r));
                }
                // push operation
                t = c;
                o.push_back(t);
                t = "";
            }
        }
        
        // finish up
        if( o.empty() ) {
            return stoi(t);   
        } else if( o.back() == "+" || o.back() == "-" ) {
            // push operand
            o.push_back(t);
        } else {
            // o.top() == "*" || o.top() == "/"
            // get operation
            op = o.back();
            o.pop_back();
            // get operand
            od = o.back();
            o.pop_back();
            // execute operation
            a = stoll(od);
            b = stoll(t);
            r = op == "*" ? a * b : a / b;
            // push operand
            o.push_back(to_string(r));
        }
        
        // deque contains either 1 element OR a +/- b +/- c ... +/- n with at least 3 elements (operand operation operand)
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
        
        return a;
    }
};
