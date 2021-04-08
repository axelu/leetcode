
// 5. Longest Palindromic Substring
// https://leetcode.com/problems/longest-palindromic-substring/


class Solution {
public:
    string longestPalindrome(string& s) {
        size_t n = s.size();
        if( n == 1 ) return s;
        if( n == 2 ) return s[0] == s[1] ? s : s.substr(1,1); // s.substr(0,1) also accepted

        int mem[1000][1000];
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                mem[i][j] =  i == j ? 1 : 0;

        // sliding over string with length 2 to N
        int b,e,lb = n-1,mx = 1;
        for(int l = 2; l <= n; ++l) {
            for(int i = 0; i <= n-l; ++i) {
                if( l == 2 && s[i] == s[i+1] ) {
                    mem[i][i+1] = 1;
                    mx = l;
                    lb = i;
                    continue;
                }
                b = i+1;
                e = i+l-2;
                if( s[i] == s[i+l-1] && mem[b][e] ) {
                    mem[i][i+l-1] = 1;
                    mx = l;
                    lb = i;
                }
            }
        }

       return s.substr(lb,mx);
    }
};
