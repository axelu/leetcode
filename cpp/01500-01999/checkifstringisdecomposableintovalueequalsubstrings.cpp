
// 1933. Check if String Is Decomposable Into Value-Equal Substrings
// https://leetcode.com/problems/check-if-string-is-decomposable-into-value-equal-substrings/




class Solution {
public:
    bool isDecomposable(string s) {
        int n = s.size();
        if( n < 2 )
            return false;
        if( n == 2 )
            return s[0] == s[1];
        if( n % 3 != 2 )
            return false;

        char prev = s[0];
        int cnt = 1,rem3;
        bool sub2 = false;
        for(int i = 1; i < n; ++i) {

            if( s[i] != prev ) {
                rem3 = cnt%3;
                if( rem3 == 0 ) {
                    continue;
                } else if(rem3 == 2) {
                    if( sub2 )
                        return false;
                    sub2 = true;
                } else {
                    return false;
                }
                prev = s[i];
                cnt = 0;
            }
            ++cnt;
            if( i == n-1 ) {
                rem3 = cnt%3;
                if( rem3 == 0 ) {
                    continue;
                } else if(rem3 == 2) {
                    if( sub2 )
                        return false;
                    sub2 = true;
                } else {
                    return false;
                }
            }
        }

        return true;
    }
};
