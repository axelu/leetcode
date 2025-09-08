
// 3612. Process String with Special Operations I
// https://leetcode.com/problems/process-string-with-special-operations-i/

class Solution {
public:
    string processStr(string s) {
        int n = s.size();

        // s: lowercase English letters, *, #, and %

        string result = "";

        for(int i = 0; i < n; ++i) {
            char c = s[i];
            if( c == '*' ) {
                if( !result.empty() )
                    result.pop_back();
            } else if( c == '#' ) {
                if( !result.empty() ) {
                    string addend = result;
                    result += addend;
                }
            } else if( c == '%' ) {
                if( !result.empty() ) {
                    reverse(result.begin(), result.end());
                }
            } else {
                result.push_back(c);
            }
        }

        return result;
    }
};
