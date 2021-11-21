
// 1190. Reverse Substrings Between Each Pair of Parentheses
// https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/




class Solution {
public:
    string reverseParentheses(string s) {
        int n = s.size();

        deque<char> stck;
        queue<char> t;

        for(int i = 0; i < n; ++i) {
            if( s[i] == ')' ) {
                while( stck.back() != '(' ) {
                    t.push(stck.back());
                    stck.pop_back();
                }
                stck.pop_back();
                while( !t.empty() ) {
                    stck.push_back(t.front());
                    t.pop();
                }
            } else {
                stck.push_back(s[i]);
            }
        }

        string ans = "";
        while( !stck.empty() ) {
            ans.push_back(stck.front());
            stck.pop_front();
        }

        return ans;
    }
};
