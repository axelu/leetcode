
// 247. Strobogrammatic Number II
// https://leetcode.com/problems/strobogrammatic-number-ii/


class Solution {
private:
    void rec(string& s, int n, int l, int r, vector<string>& ans) {
        if( l == r ) {
            s[l] = '0'; ans.push_back(s);
            s[l] = '1'; ans.push_back(s);
            s[l] = '8'; ans.push_back(s);
        } else if( l+1 == r ) {
            if( n > 2 ) {
                s[l] = '0'; s[r] = '0'; ans.push_back(s);
            }
            s[l] = '1'; s[r] = '1'; ans.push_back(s);
            s[l] = '8'; s[r] = '8'; ans.push_back(s);
            s[l] = '6'; s[r] = '9'; ans.push_back(s);
            s[l] = '9'; s[r] = '6'; ans.push_back(s);
        } else {
            if( l > 0 ) {
                s[l] = '0'; s[r] = '0'; rec(s,n,l+1,r-1,ans);
            }
            s[l] = '1'; s[r] = '1'; rec(s,n,l+1,r-1,ans);
            s[l] = '8'; s[r] = '8'; rec(s,n,l+1,r-1,ans);
            s[l] = '6'; s[r] = '9'; rec(s,n,l+1,r-1,ans);
            s[l] = '9'; s[r] = '6'; rec(s,n,l+1,r-1,ans);
        }
    }

public:
    vector<string> findStrobogrammatic(int n) {
        vector<string> ans;
        string s(n,'a');
        rec(s,n,0,n-1,ans);
        return ans;
    }
};
