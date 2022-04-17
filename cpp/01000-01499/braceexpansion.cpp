
// 1087. Brace Expansion
// https://leetcode.com/problems/brace-expansion/



class Solution {
private:
    void rec(vector<string>& l, int n, int i, string& t, vector<string>& ans) {
        if( i == n ) {
            ans.push_back(t);
            return;
        }

        for(int k = 0; k < l[i].size(); ++k) {
            t.push_back(l[i][k]);
            rec(l,n,i+1,t,ans);
            // backtrack
            t.pop_back();
        }
    }

public:
    vector<string> expand(string s) {
        vector<string> l;
        int m = 0; // 0 outside brace, 1 inside braces
        for(int k = 0; k < s.size(); ++k) {
            if( s[k] == '{' ) {
                l.push_back("");
                m = 1;
            } else if( s[k] == '}' ) {
                m = 0;
            } else if( m == 0 ) {
                l.push_back({s[k]});
            } else if( m == 1 && s[k] != ',' ) {
                l.back().push_back(s[k]);
            }
        }

        int n = l.size();
        string t = "";
        vector<string> ans;
        rec(l,n,0,t,ans);
        sort(ans.begin(),ans.end());

        return ans;
    }
};
