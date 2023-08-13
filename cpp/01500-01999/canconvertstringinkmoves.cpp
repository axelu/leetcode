
// 1540. Can Convert String in K Moves
// https://leetcode.com/problems/can-convert-string-in-k-moves/




/* abcdefghijklmnopqrstuvwxyz
 */
class Solution {
public:
    bool canConvertString(string s, string t, int k) {
        int s_sz = s.size();
        int t_sz = t.size();

        if( s_sz != t_sz )
            return false;

        int seen[26];
        for(int i = 0; i < 26; ++i)
            seen[i] = i;

        for(int j = 0; j < s_sz; ++j) {
            // if s[j] != t[j], then we have to make the equal
            if( s[j] != t[j] ) {
                int diff = t[j] - s[j];
                if( diff < 0 )
                    diff += 26;
                // cout << "s[j] " << s[j] << " t[j] " << t[j] << " diff " << diff << endl;
                if( seen[diff] <= k )
                    seen[diff] += 26;
                else
                    return false;
            }
        }

        return true;
    }
};
