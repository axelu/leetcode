
// 1653. Minimum Deletions to Make String Balanced
// https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/


class Solution {
public:
    int minimumDeletions(string s) {
        size_t n = s.size();
        if( n == 1 ) return 0;

        int i;
        int k = 0;

        // counting a's after
        int as[n];
        for(i = n-1; i >= 0; --i) {
            as[i] = k;
            if( 'a' == s[i] ) ++k;
        }

        int r = 100001;
        k = 0;
        for( i = 0; i < n; ++i ) {
            r = min(r,k+as[i]);
            if( 'b' == s[i] ) ++k;
        }

        return r;
    }
};
