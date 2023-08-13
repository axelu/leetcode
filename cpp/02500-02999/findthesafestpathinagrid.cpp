
// 2812. Find the Safest Path in a Grid
// https://leetcode.com/problems/find-the-safest-path-in-a-grid/




class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        // quick check
        if( grid[0][0] == 1 || grid[n-1][n-1] == 1 )
            return 0;

        int mat[n][n];memset(mat,-1,sizeof mat);

        queue<array<int,2>> q;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                if( grid[i][j] == 1 ) {
                    q.push({i,j});
                    mat[i][j] = 0;
                }

        // directions   R  D  L  U
        int dirR[4] = { 0, 1, 0,-1};
        int dirC[4] = { 1, 0,-1, 0};

        while( !q.empty() ) {

            queue<array<int,2>> q_new;
            while( !q.empty() ) {
                int i = q.front()[0];
                int j = q.front()[1];
                q.pop();
                for(int k = 0; k < 4; ++k) {
                    int i_new = i + dirR[k];
                    if( i_new < 0 || i_new == n )
                        continue;

                    int j_new = j + dirC[k];
                    if( j_new < 0 || j_new == n )
                        continue;

                    if( mat[i_new][j_new] != -1 )
                        continue;

                    mat[i_new][j_new] = mat[i][j] + abs(i - i_new) + abs(j - j_new);
                    q_new.push({i_new,j_new});
                }
            }
            q = q_new;
        }

        auto cmp = [](const array<int,3>& a, const array<int,3>& b){
            return a[0] < b[0];
        };
        priority_queue<array<int,3>,vector<array<int,3>>,decltype(cmp)> pq(cmp);
        bool seen[n][n];memset(seen,false,sizeof seen);
        pq.push({mat[0][0],0,0});
        while( !pq.empty() ) {
            int safeness = pq.top()[0];
            int i = pq.top()[1];
            int j = pq.top()[2];
            pq.pop();

            if( i == n-1 && j == n-1 )
                return safeness;

            for(int k = 0; k < 4; ++k) {
                int i_new = i + dirR[k];
                if( i_new < 0 || i_new == n )
                    continue;

                int j_new = j + dirC[k];
                if( j_new < 0 || j_new == n )
                    continue;

                if( seen[i_new][j_new] )
                    continue;

                seen[i_new][j_new] = true;

                pq.push({min(safeness,mat[i_new][j_new]),i_new,j_new});
            }
        }

        return 0; // satisfy compiler
    }
};
