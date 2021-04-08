
// 1021. Remove Outermost Parentheses
// https://leetcode.com/problems/remove-outermost-parentheses/



class Solution {
public:
    string removeOuterParentheses(string S) {
        size_t n = S.size();
        string ans = "";
        if( n <= 2 ) return ans;

        int cnt = 0;
        char c;
        for(int i = 0; i < n; ++i) {
            c = S[i];
            if( (cnt != 0 && c == '(') || (cnt != 1 && c == ')') )
                ans += c;
            cnt += c == '(' ? 1 : -1;
        }
        return ans;
    }
};
