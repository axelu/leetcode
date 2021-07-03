
// 1730. Shortest Path to Get Food
// https://leetcode.com/problems/shortest-path-to-get-food/



class Solution {
public:
    int getFood(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int i,j;

        // where is our location and
        // is there any food at all in the grid?
        int r = -1,c;
        bool hasFood = false;
        for(i = 0; i < m; ++i) {
            for(j = 0; j < n; ++j) {
                if( grid[i][j] == '*' ) {
                    r = i; c = j;
                }
                if( grid[i][j] == '#' ) {
                    hasFood = true;
                }
            }
        }
        if( !hasFood ) return -1; // no food in the entire grid

        // directions
        int dirR[4] = {0,1,0,-1};
        int dirC[4] = {1,0,-1,0};


        // BFS
        queue<array<int,3>> q;
        int seen[m*n];memset(seen,0,sizeof seen);
        q.push({r,c,0});
        seen[r*n+c] = 1;
        int i_new,j_new,step,k,seenIdx;
        while(!q.empty()) {
            i    = q.front()[0];
            j    = q.front()[1];
            step = q.front()[2];
            q.pop();
            // explore all 4 directions
            for(int k = 0; k < 4; ++k) {

                i_new = i+dirR[k];
                if( i_new < 0 || i_new >= m )
                    continue;

                j_new = j+dirC[k];
                if( j_new < 0 || j_new >= n )
                    continue;

                // did we arrive at food?
                if( grid[i_new][j_new] == '#' )
                    return step+1;

                // is it a path?
                if( grid[i_new][j_new] == 'X' )
                    continue;

                seenIdx = i_new*n+j_new;
                // have we seen this cell before?
                if( seen[seenIdx] )
                    continue;

                seen[seenIdx] = 1;
                q.push({i_new,j_new,step+1});
            }
        }
        return -1;
    }
};
