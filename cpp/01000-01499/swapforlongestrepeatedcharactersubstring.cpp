
// 1156. Swap For Longest Repeated Character Substring
// https://leetcode.com/problems/swap-for-longest-repeated-character-substring/




/* for a given char:
 *    measure the length of each group
 *    if one group only, we are done
 *    if there is an adjacent group
 *       if the gap is one char
 *          if there is a third group
 *              steal a char for the third group to combine both
 *          else
 *              steal 1st char from left or last char from right group to combine both
 *              Note: edge case if both or one of those is only one char long.
 *       else
 *          steal a char from another group extending the current group by one
 */
class Solution {
public:
    int maxRepOpt1(string text) {
        int n = text.size();
        if( n == 1 )
            return 1;

        vector<array<int,2>> groups[26]; // list of intervals[start,end] for given char

        int cnt = 1;
        for(int i = 1; i < n; ++i) {
            if( text[i] == text[i-1] ) {
                ++cnt;
            } else {
                groups[text[i-1]-'a'].push_back({i-cnt,i-1});
                cnt = 1;
            }
        }
        // finish
        groups[text[n-1]-'a'].push_back({n-cnt,n-1});

        int ans = 0;

        for(int i = 0; i < 26; ++i) {
            int grp_sz = groups[i].size();
            for(int j = 0; j < grp_sz; ++j) {

                // length of current group
                int cur_start = groups[i][j][0];
                int cur_end   = groups[i][j][1];
                int cur_size  = cur_end - cur_start + 1;
                ans = grp_sz > 1 ? max(ans, cur_size + 1) : max(ans, cur_size);

                // is there a next group?
                if( j < grp_sz-1 ) {
                    // is the gap exactly one?
                    int nxt_start = groups[i][j+1][0];
                    if( nxt_start - cur_end == 2 ) {
                        int nxt_end   = groups[i][j+1][1];
                        int nxt_size  = nxt_end - nxt_start + 1;
                        ans = grp_sz > 2 ? max(ans, cur_size + 1 + nxt_size) : max(ans, cur_size + nxt_size);
                    }
                }

            }
        }

        return ans;
    }
};
