
// 301. Remove Invalid Parentheses
// https://leetcode.com/problems/remove-invalid-parentheses/




class Solution {
private:
    void remove(string& s) {
        // remove leading closing parentheses
        for(auto it = s.begin(); it != s.end();) {
            if( *it == ')' )
                it = s.erase(it);
            else if( *it == '(' )
                break;
            else
                ++it;
        }
        // remove trailing opening parentheses
        for(int i = s.size()-1; i >= 0; --i) {
            if( s[i] == '(' ) {
                auto it = s.begin();
                advance(it,i);
                s.erase(it);
            } else if( s[i] == ')' ) {
                break;
            }
        }
    }

    pair<int,int> balanced(string& s) {
        int open = 0, close = 0;
        for(int i = 0; i < s.size(); ++i) {
            if( s[i] == '(' )
                ++open;
            else if( s[i] == ')' ) {
                if( open > 0 ) {
                    --open;
                } else {
                    ++close;
                }
            }
        }
        return {open,close};
    }

    unordered_set<string> seen;

    void genSubsequences(string& s, int i, string& substring, int remOpen, int remClose,
                         vector<string>& ans) {

        if( i == s.size() ) {
            auto b = balanced(substring);
            if( b.first == 0 && b.second == 0 &&
                seen.find(substring) == seen.end() ) {

                seen.insert(substring);
                ans.push_back(substring);
            }
        } else {
            // we have a choice

            // don't include char at current index
            if( s[i] == '(' && remOpen > 0 )
                genSubsequences(s,i+1,substring,remOpen-1,remClose,ans);
            if( s[i] == ')' && remClose > 0 )
                genSubsequences(s,i+1,substring,remOpen,remClose-1,ans);

            // include char at current index
            substring.push_back(s[i]);
            genSubsequences(s,i+1,substring,remOpen,remClose,ans);
            substring.pop_back(); // backtrack
        }
        return;
    }

public:
    vector<string> removeInvalidParentheses(string s) {
        // we cannot recover from leading closing parentheses nor
        // from trailing opening parentheses, so remove them
        remove(s);

        int n = s.size();

        // balanced parentheses?
        pair<int,int> b = balanced(s);
        if( b.first == 0 && b.second == 0 )
            return {s};

        vector<string> ans;
        string substring = "";
        genSubsequences(s,0,substring,b.first,b.second,ans);
        return ans;
    }
};
