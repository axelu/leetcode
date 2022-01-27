
// 856. Score of Parentheses
// https://leetcode.com/problems/score-of-parentheses/
// day 24 February 2021 challenge
// https://leetcode.com/explore/featured/card/february-leetcoding-challenge-2021/587/week-4-february-22nd-february-28th/3651/




class Solution {
private:
    int rec(int& idx, string& S) {
        ++idx;
        if( S[idx] == ')' ) return 1;
        int ans = 0;
        while( S[idx] != ')' ) {
            ans += rec(idx,S);
            ++idx;
        }
        return 2 * ans;
    }
public:
    int scoreOfParentheses(string S) {
        int n = S.size();

        int ans = 0;
        int idx = 0; // 2 <= S.length <= 50
        while( idx < n ) {
            ans += rec(idx,S);
            ++idx;
        }
        return ans;
    }
};
