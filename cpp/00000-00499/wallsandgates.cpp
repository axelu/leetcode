
// 286. Walls and Gates
// https://leetcode.com/problems/walls-and-gates/



class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        int m = rooms.size();
        int n = rooms[0].size();

        // four directions
        int dirR[4] = {0,1,0,-1};
        int dirC[4] = {1,0,-1,0};

        queue<array<int,3>> q;
        int seen[m*n];
        int i,j,k,r,c,r_new,c_new,d;
        for(i = 0; i < m; ++i) {
            for(j = 0; j < n; ++j) {
                if( rooms[i][j] == 0 ) { // gate

                    // BFS starting from gate
                    memset(seen,0,sizeof seen);
                    q.push({i,j,0});
                    while(!q.empty()) {
                        r = q.front()[0];
                        c = q.front()[1];
                        d = q.front()[2];
                        q.pop();

                        // explore all 4 directions
                        for(k = 0; k < 4; ++k) {

                            r_new = r+dirR[k];
                            if( r_new < 0 || r_new == m )
                                continue;

                            c_new = c+dirC[k];
                            if( c_new < 0 || c_new == n )
                                continue;

                            // another gate or a wall?
                            if( rooms[r_new][c_new] == 0 || rooms[r_new][c_new] == -1 )
                                continue;

                            // cell we have seen before?
                            if( seen[r_new*n+c_new] )
                                continue;

                            // is the cell closer to another gate?
                            // if so, the we don't explore any further from here
                            if( rooms[r_new][c_new] <= d+1 )
                                continue;

                            rooms[r_new][c_new] = d+1;
                            seen[r_new*n+c_new] = 1;
                            q.push({r_new,c_new,d+1});
                        }
                    }
                }
            }
        }
    }
};
