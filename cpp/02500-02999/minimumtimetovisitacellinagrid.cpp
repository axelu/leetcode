
// 2577. Minimum Time to Visit a Cell In a Grid
// https://leetcode.com/problems/minimum-time-to-visit-a-cell-in-a-grid/





/* lets say we arrive at some cell at time 5 and can enter an adjacent cell at time 10
 *   we could go back and forth to some adjacent cell that we came from to let time pass
 *   we will be able to enter the adjacent cell exactly at time 10: 10 - 5 is odd
 * lets say we arrive at some cell at time 6 and can enter an adjacent cell at time 10
 *   we could go back and forth to some adjacent cell that we came from to let time pass
 *   we will be able to enter the adjacent cell exactly at time 11: 10 - 6 is even
 * BUT
 * lets say we arrive at some cell at time 6 and can enter an adjacent cell at time 11
 *   the earliest we could proceed to the adjacent cell is time 11
 * lets say we arrive at some cell at time 5 and can enter an adjacent cell at time 11
 *   the earliest we could proceed to the adjacent cell is time 12
 * the point is: arriving at a given cell earlier is not necessarily giving us a better result
 */
class Solution {
public:
    int minimumTime(vector<vector<int>>& grid) {
        int m = grid.size();    // rows 2 <= m <= 1000
        int n = grid[0].size(); // cols 2 <= n <= 1000
        // 4 <= m * n <= 100000

        // as long as we can move from [0,0] we will have a solution
        if( grid[0][1] > 1 && grid[1][0] > 1 )
            return -1;

        // directions   R  D  L  U
        int dirR[4] = { 0, 1, 0,-1};
        int dirC[4] = { 1, 0,-1, 0};

        struct cmp {
            public:
            bool operator()(const array<int,3>& a, const array<int,3>& b) {
                return a[2] > b[2];
            }
        };

        int ans_odd = INT_MAX;
        int ans_even = INT_MAX;


        int seen[m][n][2];memset(seen,0,sizeof seen);
        priority_queue<array<int,3>,vector<array<int,3>>,cmp> pq;
        pq.push({0,0,0}); // i,j,time of arrival
        seen[0][0][0] = 1;
        while( !pq.empty() ) {

            auto arr = pq.top();
            int i = arr[0];
            int j = arr[1];
            int t = arr[2];
            // cout << "i " << i << " j " << j << " t " << t << endl;
            if( i == m-1 && j == n-1 ) {
                if( t % 2 )
                    ans_odd = t;
                else
                    ans_even = t;

                if( seen[i][j][0] && seen[i][j][1] )
                    break;
            }

            pq.pop();

            // explore all four directions
            for(int k = 0; k < 4; ++k) {
                int i_new = i + dirR[k];
                if( i_new < 0 || i_new == m )
                    continue;
                int j_new = j + dirC[k];
                if( j_new < 0 || j_new == n )
                    continue;

                int t_new = t + 1;
                // cout << "i_new " << i_new << " j_new " << j_new << " t_new " << t_new << endl;
                int min_time = grid[i_new][j_new];
                int t_enter;
                if( min_time <= t_new ) {
                    // we could proceed to grid[i_new][j_new] at t_new
                    t_enter = t_new;
                } else {
                    // we need to pace back and forth to where we came from
                    // when we entered grid[i][j] to 'wait'
                    int diff = min_time - t;  // 2 <= diff
                    if( diff % 2 ) {
                        // we will be able to enter at min_time
                        t_enter = min_time;
                    } else {
                        // we will be able to enter at min_time + 1
                        t_enter = min_time + 1;
                    }
                }

                if( seen[i_new][j_new][t_enter % 2] )
                    continue;

                seen[i_new][j_new][t_enter % 2] = 1;
                pq.push({i_new,j_new,t_enter});
            }
        }

        return min(ans_odd,ans_even);
    }
};
