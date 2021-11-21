
// 1763. Longest Nice Substring
// https://leetcode.com/problems/longest-nice-substring/


class Solution {
private:
    bool isNice(string& s, int b, int e) {
        int lo[26]; memset(lo,0,sizeof lo);
        int up[26]; memset(up,0,sizeof up);
        int i;
        for(i = b; i <= e; ++i)
            if( s[i] >= 97 ) ++lo[s[i]-'a'];
            else ++up[s[i]-'A'];
        for(i = 0; i < 26; ++i)
            if( lo[i] != 0 && up[i] == 0 ||
                lo[i] == 0 && up[i] != 0 )
                return false;
        return true;
    }
public:
    string longestNiceSubstring(string& s) {
        int n = s.size();
        if( n == 1 ) return "";

        // brute force
        string ans = "";
        for(int i = 0; i < n-1; ++i)
            for(int j = i+1; j < n; ++j)
                if( isNice(s,i,j) && j-i+1 > ans.size() )
                    ans = s.substr(i,j-i+1);
        return ans;
    }
};
