
// 3568. Minimum Moves to Clean the Classroom
// https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/





class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        // if there is litter that is blocked by obstacles
        // and hence that litter cannot be reached, there
        // is no solution
        // if there is litter further away then energy
        // from S or any R, then there is no solution

        int m = classroom.size();    // rows
        int n = classroom[0].size(); // cols

        // count litter
        int litter = 0;
        // find starting point
        int start_i, start_j; // it is guaranteed to have one start

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( classroom[i][j] == 'L' ) {
                    // change litter to a 'litter index'
                    classroom[i][j] = litter + '0';
                    ++litter;
                } else if( classroom[i][j] == 'S' ) {
                    start_i = i;
                    start_j = j;
                }
            }
        }

        // edge case
        if( litter == 0 )
            return 0;

        int fullmask = pow(2,litter)-1;

        //  0  1     2       3      4
        // {i, j, mask, energy, steps}
        auto cmp = [](const vector<int>& a, const vector<int>& b){
            if( a[4] > b[4] ) {
                return true;
            } else if( a[4] == b[4] ) {
                if( a[3] < b[3] ) {
                    return true;
                }
            }
            return false;
        };
        priority_queue<vector<int>,vector<vector<int>>,decltype(cmp)> pq(cmp);
        pq.push({start_i, start_j, 0, energy, 0});

        int best_energy[20][20][1024]; // i, j, mask
        memset(best_energy,-1,sizeof best_energy);
        best_energy[start_i][start_j][0] = energy;

        // directions   R  D  L  U
        int dirR[4] = { 0, 1, 0,-1};
        int dirC[4] = { 1, 0,-1, 0};

        while( !pq.empty() ) {

            int i = pq.top()[0];
            int j = pq.top()[1];
            int mask = pq.top()[2];
            int energy_remaining = pq.top()[3];
            int steps = pq.top()[4];
            pq.pop();

            // if current cell has litter and
            // we have not collected it, then
            // collect the litter
            // Note: it is guaranteed that classroom[i][j] != 'X'
            if( classroom[i][j] != 'S' && classroom[i][j] != 'R' && classroom[i][j] != '.' ) {
                int litter_index = classroom[i][j] - '0';
                mask |= (1<<litter_index);
            }
            if( mask == fullmask )
                return steps;

            // if current cell has energy,
            // reset our energy
            if( classroom[i][j] == 'R' )
                energy_remaining = energy;

            if( energy_remaining == 0 )
                continue;

            // explore all 4 directions
            for(int k = 0; k < 4; ++k) {
                int i_new = i + dirR[k];
                if( i_new < 0 || i_new == m )
                    continue;

                int j_new = j + dirC[k];
                if( j_new < 0 || j_new == n )
                    continue;

                // cannot step on obstacle
                if( classroom[i_new][j_new] == 'X' )
                    continue;

                // doesn't make sense to return to a cell
                // with the same litter collected, unless
                // we gained some energy
                if( energy_remaining-1 <= best_energy[i_new][j_new][mask] )
                    continue;

                best_energy[i_new][j_new][mask] = energy_remaining-1;

                pq.push({i_new, j_new, mask, energy_remaining-1, steps+1});
            }
        }

        return -1;
    }
};


/* test cases
["S.", "XL"]
2
["LS", "RL"]
4
["L.S", "RXL"]
3
["L.L", "LXS"]
3
[".", "S", "X", "L"]
1
["RRLXX", "X.RSL"]
8
["RRL.", "LSXX", "RL.L", "LLL.", "L..."]
15
["SR"]
1

[".R.L", "SXX.", "..LX", "LX.X", "LRRL"]
12
["LSRXL", "RRLRX", "XRRL.", "X.XRL", "RXLXR"]
21
["SXRLR", "R...X", "R.XLR", ".LRL.", "LLR.R"]
22
["LXL..", ".SXLL", "RLLLX", "X.R.R", "RLRXX"]
17
[".LR.X.", "RRL.L.", "XRL.RX", "RXXXLX", "LRL.LR", "RRXXS."]
17
*/
