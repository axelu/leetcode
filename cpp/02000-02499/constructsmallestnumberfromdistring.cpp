
// 2375. Construct Smallest Number From DI String
// https://leetcode.com/problems/construct-smallest-number-from-di-string/



class Solution {
private:
    string ans;

    void rec(string& s, string& pattern, int n, int i, int taken[]) {
        if( s.size() == n+1 ) {
            if( s < ans )
                ans = s;
            return;
        }

        // brute force
        for(char c = '1'; c <= '9'; ++c)
            if( taken[c-'1'] == 0 ) {

                if( ( pattern[i] == 'I' && c > s[i] ) ||
                    ( pattern[i] == 'D' && c < s[i] ) ) {

                    s = s + c;
                    taken[c-'1'] = 1;
                    rec(s,pattern,n,i+1,taken);
                    taken[c-'1'] = 0;
                    s.pop_back();
                }
            }

        return;
    }

public:
    string smallestNumber(string pattern) {
        int n = pattern.size();

        ans = "AAAAAAAAA";

        string s = "";
        int taken[9];memset(taken,0,sizeof taken);
        for(char c = '1'; c <= '9'; ++c) {
            s = s + c;
            taken[c-'1'] = 1;
            rec(s,pattern,n,0,taken);
            taken[c-'1'] = 0;
            s.pop_back();
        }

        return ans;
    }
};
