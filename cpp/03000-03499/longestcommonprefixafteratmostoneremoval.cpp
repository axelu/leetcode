
// 3460. Longest Common Prefix After at Most One Removal
// https://leetcode.com/problems/longest-common-prefix-after-at-most-one-removal/




/* we need to remove the 1st char from s
   where that char is different that char in t





 */
class Solution {
public:
    int longestCommonPrefix(string s, string t) {
        int s_sz = s.size();
        int t_sz = t.size();

        int i = 0;
        int j = 0;
        bool removed = false;
        for( ; i < s_sz && j < t_sz; ) {

            if( s[i] == t[j] ) {
                ++i;
                ++j;
                continue;
            } else {
                if( !removed ) {
                    removed = true;
                    ++i;
                    continue;
                } else {
                    break;
                }
            }
        }

        return removed ? i-1 : i;
    }
};
