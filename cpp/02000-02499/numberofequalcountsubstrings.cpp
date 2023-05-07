
// 2067. Number of Equal Count Substrings
// https://leetcode.com/problems/number-of-equal-count-substrings/





/* from the problem description:
 *   A substring of s is said to be an equal count substring if,
 *   for each unique letter in the substring, it appears exactly
 *   count times in the substring
 *
 *   so lets say count = 5
 *      if we slide a window of length = 5 accross s and have 1 unique char in it
 *         then we have an equal count substring
 *      if we slide a window of length = 10 accross s and have 2 unique chars in it
 *         then we have an equal count substring
 *   and so on
 */

class Solution {
public:
    int equalCountSubstrings(string s, int count) {
        int n = s.size();

        int ans = 0;

        // sliding window of length that is a multiple of count

        for(int k = 1; count * k <= n; ++k) {
            int l = count * k;

            if( l > count * 26 )
                break;

            int cnt[26];memset(cnt,0,sizeof cnt);
            int unique_char_cnt = 0;        // number of unique chars with count occurences in window
            int i = 0;                      // left index
            for(int j = 0; j < n; ++j) {    // right index
                ++cnt[s[j]-'a'];
                if( cnt[s[j]-'a'] == count )
                    ++unique_char_cnt;
                else if( cnt[s[j]-'a'] == count + 1 )
                    --unique_char_cnt;


                if( j - i + 1 == l ) {
                    // if( unique_char_cnt * count == l ) {
                    if( unique_char_cnt == k ) {
                        // cout << "found an equal count substring l " << l << " i " << i << " j " << j << " " << s.substr(i,l) << " ";
                        // cout << "unique_char_cnt " << unique_char_cnt << endl;
                        ++ans;
                    }

                    --cnt[s[i]-'a'];
                    if( cnt[s[i]-'a'] == count - 1 )
                        --unique_char_cnt;
                    else if( cnt[s[i]-'a'] == count )
                        ++unique_char_cnt;
                    ++i;
                }
            }
        }

        return ans;
    }
};
