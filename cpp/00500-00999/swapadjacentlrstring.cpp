
// 777. Swap Adjacent in LR String
// https://leetcode.com/problems/swap-adjacent-in-lr-string/






/* L and R cannot cross
 * L can move to the left
 * R can move to the right
 */

class Solution {
public:
    bool canTransform(string start, string end) {
        int n = start.size(); // start.size() == end.size()
        int src_idx = 0;
        int tgt_idx = 0;

        while( tgt_idx < n ) {
            // advance in target till we hit something other than X
            while( tgt_idx < n && end[tgt_idx] == 'X' )
                ++tgt_idx;

            if( tgt_idx == n )
                continue;

            if( src_idx == tgt_idx ) {
                if( start[src_idx] == end[tgt_idx] ) {
                    ++src_idx;
                    ++tgt_idx;
                    continue;
                } else if( end[tgt_idx] == 'R' ) {
                    return false;
                }
            }

            if( end[tgt_idx] == 'R' ) {
                // we need to treat Rs as a group
                // advacne tgt_idx as long as we have an R
                int r_cnt_tgt = 0;
                while( tgt_idx < n && end[tgt_idx] == 'R' ) {
                    ++r_cnt_tgt;
                    ++tgt_idx;
                }

                // we need to catch up src_idx
                int r_cnt_src = 0;
                for(; src_idx < tgt_idx; ++src_idx) {
                    if( start[src_idx] == 'L' )
                        return false;
                    if( start[src_idx] == 'R' )
                        ++r_cnt_src;
                }
                if( r_cnt_src != r_cnt_tgt )
                    return false;

            } else { // target[tgt_idx] == 'L'
                // we need to catch up src_idx
                for(; src_idx < n; ++src_idx) {
                    if( start[src_idx] == 'R' )
                        return false;
                    if( start[src_idx] == 'L' )
                        break;
                }
                if( src_idx < tgt_idx || src_idx == n )
                    return false;
                if( src_idx == tgt_idx ) {
                    continue;
                }
                start[src_idx] = 'X';
                src_idx = tgt_idx + 1;
                ++tgt_idx;

            }
        }

        for(; src_idx < n; ++src_idx)
            if( start[src_idx] != 'X' )
                return false;

        return true;
    }
};
