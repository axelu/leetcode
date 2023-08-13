
// 2116. Check if a Parentheses String Can Be Valid
// https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/




class Solution {
public:
    bool canBeValid(string s, string locked) {
        int n = s.size(); // s.size() == locked.size()
        if( n % 2 )
            return false;

        // s[i] is either an opening parenthesis or a closing parenthesis
        // locked[i] is either 0 or 1
        // s locked action
        // -+------+-----------------------------------
        // (   0     try match an opening parenthesis, if not, add a closing parenthesis to expected unlocked
        // (   1     add a closing parenthesis to expected locked
        // )   0     try match an opening parenthesis, if not, add a closing parenthesis to expected unlocked
        // )   1     we have to match an opening parentheses

        stack<int> lcked;   // indicies of locked opening parenthesis
        stack<int> unlcked; // indicies of unlocked parenthesis
        for(int i = 0; i < n; ++i) {
            if( locked[i] == '0' ) {
                unlcked.push(i);

            } else if( s[i] == '(' ) {
                lcked.push(i);

            } else { // s[i] == ')'
                // we must to balance a locked closing parenthesis
                if( lcked.empty() && unlcked.empty() )
                    return false;
                else if( !lcked.empty() )
                    lcked.pop();
                else
                    unlcked.pop();
            }
        }
        // what is left is to balance locked opening parenthesis
        while( !lcked.empty() ) {
            // we have to have had an unlocked position to the right
            if( unlcked.empty() || unlcked.top() < lcked.top() )
                return false;

            lcked.pop();
            unlcked.pop();
        }

        return true;
    }
};
