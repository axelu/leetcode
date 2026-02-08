
// 3823. Reverse Letters Then Special Characters in a String
// https://leetcode.com/problems/reverse-letters-then-special-characters-in-a-string/



class Solution {
public:
    string reverseByType(string s) {
        int n = s.size();

        stack<char> lower;
        stack<char> special;
        for(int i = 0; i < n; ++i) {
            if( islower(s[i]) )
                lower.push(s[i]);
            else
                special.push(s[i]);
        }
        for(int i = 0; i < n; ++i) {
            if( islower(s[i]) ) {
                s[i] = lower.top();
                lower.pop();
            } else {
                s[i] = special.top();
                special.pop();
            }
        }

        return s;
    }
};
