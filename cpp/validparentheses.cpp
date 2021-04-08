#include <iostream>
#include <cassert>

#include <string>
#include <stack>

// Valid Parentheses
// https://leetcode.com/problems/valid-parentheses/

using namespace std;

class Solution {
public:
    bool isValid(string s) {
       if ( s.empty() ) return true;
       if ( s.size() % 2 == 1 ) return false; // has to be even

       stack<char> t;
       for(auto c : s) {
            if ( c == '(' ) {
                t.push(')');
            } else if ( c == '{' ) {
                t.push('}');
            } else if ( c == '[' ) {
                t.push(']');
            } else if ( !t.empty() ) {
                if ( c == t.top() ) {
                    t.pop();
                } else {
                    return false;
                }
            } else {
                return false;
            }
       }

       return ( t.empty() ) ? true : false;
    }
};

int main() {

    Solution s;

    assert(s.isValid("") == true);
    assert(s.isValid("()") == true);
    assert(s.isValid("()[]{}") == true);
    assert(s.isValid("(]") == false);
    assert(s.isValid("([)]") == false);
    assert(s.isValid("{[]}") == true);
    assert(s.isValid("){") == false);




    return 0;
}
