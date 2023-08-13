
// 2814. Minimum Time Takes to Reach Destination Without Drowning
// https://leetcode.com/problems/minimum-time-takes-to-reach-destination-without-drowning/





class Solution {
public:
    int minimumSeconds(vector<vector<string>>& land) {
        int m = land.size();    // rows
        int n = land[0].size(); // cols

        int s_i, s_j; // start i,j
        int d_i, d_j; // destination i,j

        // flood cells
        // directions   R  D  L  U
        int dirR[4] = { 0, 1, 0,-1};
        int dirC[4] = { 1, 0,-1, 0};

        queue<array<int,3>> q;
        vector<vector<int>> grid(m,vector<int>(n,100000));
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( land[i][j] == "X" ) {           // stone
                    grid[i][j] = -1;
                } else if( land[i][j] == "S" ) {    // start
                    s_i = i;
                    s_j = j;
                } else if( land[i][j] == "D" ) {    // destination
                    d_i = i;
                    d_j = j;
                    grid[i][j] = -2;                // destination will never be flooded
                } else if( land[i][j] == "*" ) {
                    q.push({i,j,0});
                    grid[i][j] = 0;
                }
            }
        }
        while( !q.empty() ) {
            queue<array<int,3>> q_new;
            while( !q.empty() ) {
                int i = q.front()[0];
                int j = q.front()[1];
                int step = q.front()[2];
                q.pop();

                for(int k = 0; k < 4; ++k) {
                    int i_new = i + dirR[k];
                    if( i_new < 0 || i_new == m )
                        continue;
                    int j_new = j + dirC[k];
                    if( j_new < 0 || j_new == n )
                        continue;

                    if( grid[i_new][j_new] <= step + 1 )
                        continue;

                    grid[i_new][j_new] = step + 1;
                    q_new.push({i_new, j_new, step + 1});
                }
            }
            q = q_new;
        }
        /*
        // debug
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
        */

        // BFS
        q.push({s_i,s_j,0});
        bool seen[m][n];memset(seen,false,sizeof seen);
        while( !q.empty() ) {
                int i = q.front()[0];
                int j = q.front()[1];
                int step = q.front()[2];
                q.pop();

                if( i == d_i && j == d_j )
                    return step;

                for(int k = 0; k < 4; ++k) {
                    int i_new = i + dirR[k];
                    if( i_new < 0 || i_new == m )
                        continue;
                    int j_new = j + dirC[k];
                    if( j_new < 0 || j_new == n )
                        continue;

                    if( grid[i_new][j_new] == -1 || (grid[i_new][j_new] != -2 && grid[i_new][j_new] <= step + 1) )
                        continue;

                    if( seen[i_new][j_new] )
                        continue;

                    seen[i_new][j_new] = true;
                    q.push({i_new, j_new, step + 1});
                }
        }

        return -1;
    }
};
