
// 1001. Grid Illumination
// https://leetcode.com/problems/grid-illumination/






/* a lamp is iluminated if there is a lamp in its row, col or its 'diagonal' that is turned on
 * in regards to diagonals
 * there are the ones that run from:  top left  to  down right (lets call them t) and
 * the ones that run from:           down left  to    up right (lets call them d)
 * how to identify the diagonals?
 *   top left  to  down right
 *   row - col
 *              0  1  2  3
 *           0  0 -1 -2 -3
 *           1  1  0 -1 -2
 *           2  2  1  0 -1
 *           3  3  2  1  0
 *
 *   down left  to    up right
 *   row - col
 *              0  1  2  3
 *              3  2  1  0 reversed column index
 *           0 -3 -2 -1  0
 *           1 -2 -1  0  1
 *           2 -1  0  1  2
 *           3  0  1  2  3
 *
 */
class Solution {
public:
    vector<int> gridIllumination(int n, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
        // n x n grid -> n rows and n cols

        unordered_map<int,int> by_row;
        unordered_map<int,int> by_col;
        unordered_map<int,int> by_t;
        unordered_map<int,int> by_d;

        unordered_set<long> seen; // same lamp could be in lamps multiple times
        for(auto& v: lamps) {
            int i = v[0];
            int j = v[1];
            long idx = i * (long)n + j;
            if( !seen.insert(idx).second )
                continue;

            ++by_row[i];

            ++by_col[j];

            int rowminuscol = i - j;
            ++by_t[rowminuscol];

            int j_rev = (n-1) - j;
            int rowminuscolrev = i - j_rev;
            ++by_d[rowminuscolrev];
        }

        // 8 directions, starting North, then clockwise
        // directions  U UR  R DR  D DL  L UL
        int dirR[] = {-1,-1, 0, 1, 1, 1, 0,-1};
        int dirC[] = { 0, 1, 1, 1, 0,-1,-1,-1};

        int q_sz = queries.size();
        vector<int> ans(q_sz,0);
        for(int k = 0; k < q_sz; ++k) {
            int i = queries[k][0];
            int j = queries[k][1];
            long idx = i * (long)n + j;
            int rowminuscol = i - j;
            int j_rev = (n-1) - j;
            int rowminuscolrev = i - j_rev;

            if( by_row[i] != 0 || by_col[j] != 0 || by_t[rowminuscol] != 0 || by_d[rowminuscolrev] != 0 )
                ans[k] = 1;

            // turn off all lamps that were and are still turned on beginning with current lamp
            if( seen.erase(idx) != 0 ) {
                --by_row[i];
                --by_col[j];
                --by_t[rowminuscol];
                --by_d[rowminuscolrev];
            }
            for(int o = 0; o < 8; ++o) {
                int i_new = i + dirR[o];
                if( i_new < 0 || i_new == n )
                    continue;
                int j_new = j + dirC[o];
                if( j_new < 0 || j_new == n )
                    continue;

                long idx_new = i_new * (long)n + j_new;
                if( seen.erase(idx_new) != 0 ) {
                    --by_row[i_new];
                    --by_col[j_new];

                    int rowminuscol_new = i_new - j_new;
                    --by_t[rowminuscol_new];

                    int j_new_rev = (n-1) - j_new;
                    int rowminuscolrev_new = i_new - j_new_rev;
                    --by_d[rowminuscolrev_new];
                }
            }
        }

        return ans;
    }
};
