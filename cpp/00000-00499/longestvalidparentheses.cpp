
// 32. Longest Valid Parentheses
// https://leetcode.com/problems/longest-valid-parentheses/
// day 3 April 2021 challenge
// https://leetcode.com/explore/featured/card/april-leetcoding-challenge-2021/593/week-1-april-1st-april-7th/3695/



class Solution {
public:
    int longestValidParentheses(string s) {
        int ans = 0;
        int n = s.size();
        if( n < 2 ) return ans;

        stack<int> stck;
        stck.push(-1);
        for(int i = 0; i < s.size(); ++i) {
            if( s[i] == '(' ) {
                stck.push(i);
            } else {
                stck.pop();
                if( stck.empty() ) {
                    stck.push(i);
                } else {
                    ans = max(ans,i-stck.top());
                }
            }
        }
        return ans;
    }
};
