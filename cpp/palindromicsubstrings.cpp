
// 647. Palindromic Substrings
// https://leetcode.com/problems/palindromic-substrings/


class Solution {
public:
    int countSubstrings(string s) {
        size_t n = s.size();
        if( n == 0 ) return 0;
        if( n == 1 ) return 1;
        if( n == 2 ) return s[0] == s[1] ? 3 : 2;

        int mem[1000][1000];
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                mem[i][j] =  i == j ? 1 : 0;

        // sliding over string with length 2 to N
        int b, e, ans = n;
        for(int l = 2; l <= n; ++l) {
            for(int i = 0; i <= n-l; ++i) {
                if( l == 2 && s[i] == s[i+1] ) {
                    mem[i][i+1] = 1;
                    ++ans;
                    continue;
                }
                b = i+1;
                e = i+l-2;
                if( s[i] == s[i+l-1] && mem[b][e] ) {
                    mem[i][i+l-1] = 1;
                    ++ans;
                }
            }
        }

       return ans;
    }
};
