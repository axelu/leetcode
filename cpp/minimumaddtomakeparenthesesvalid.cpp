
// 921. Minimum Add to Make Parentheses Valid
// https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/



class Solution {
public:
    int minAddToMakeValid(string S) {
        int n = S.size();
        if( n < 2 ) return n;

        stack<char> stck;
        int i;
        int ans = 0;
        for(i = 0; i < n; ++i) {
            if( S[i] == '(' ) {
                stck.push(')');
            } else {
                if( stck.empty() || stck.top() != ')' ) {
                    ++ans;
                } else {
                    stck.pop();
                }
            }
        }
        return ans+stck.size();
    }
};
