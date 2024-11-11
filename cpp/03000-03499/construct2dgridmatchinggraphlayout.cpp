
// 3311. Construct 2D Grid Matching Graph Layout
// https://leetcode.com/problems/construct-2d-grid-matching-graph-layout/





/* the indegree will tell us how to arrange the nodes
 *    if they are all in a row (or column) then we have only indegree 1 (the ends) and indegree 2
 * 2 nodes have only one possible arrangements
 * 3 nodes have only on possible arrangements
 * 4 nodes could be a square (all nodes with indegree of 2) or a row (or column) with 2x indegree 2 (middle 2) and 2x indegree 1 (the ends)
 *     indegree 2 (there should be 4x), those are corners
 *     indegree 3, those are our edes
 *     indegree 4, those are pieces in the middle
 *
 */
class Solution {
public:
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {
        // 2 <= n <= 50000
        if( n == 2 )
            return {{0,1}};

        vector<int> g[n];
        int mx_indegree = 0;
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            g[u].push_back(v);
            g[v].push_back(u);

            mx_indegree = max(mx_indegree, (int)g[u].size());
            mx_indegree = max(mx_indegree, (int)g[v].size());
        }

        if( mx_indegree == 2 && n == 4 ) {
            // we could have a row OR a sqare
            int u = -1;
            for(int i = 0; i < n; ++i) {
                if( g[i].size() == 1 ) {
                    // end cell we will use as the start
                    u = i;
                    break;
                }
            }
            if( u == -1 ) {
                // we have a 2x2 square
                vector<vector<int>> grid(2,vector<int>(2));
                grid[0][0] = 0;
                bool seen[4]; memset(seen,false,sizeof seen);
                seen[0] = true;
                grid[0][1] = g[0][0];
                seen[g[0][0]] = true;
                grid[1][0] = g[0][1];
                seen[g[0][1]] = true;
                for(int i = 1; i < 4; ++i)
                    if( !seen[i] )
                        grid[1][1] = i;
                return grid;
            }
        }

        if( mx_indegree == 2 ) {
            // 1 row (or 1 column arrangement) OR
            // edge case when n = 4, we could have a sqare arrangement, handled before
            int u = -1;
            for(int i = 0; i < n; ++i) {
                if( g[i].size() == 1 ) {
                    // end cell we will use as the start
                    u = i;
                    break;
                }
            }
            vector<vector<int>> grid(1,vector<int>(n));
            grid[0][0] = u;
            int row_idx = 1;
            bool seen[n]; memset(seen,false,sizeof seen);
            seen[u] = true;

            while( row_idx < n ) {
                if( !seen[g[u][0]] )
                    u = g[u][0];
                else
                    u = g[u][1];
                grid[0][row_idx++] = u;
                seen[u] = true;
            }

            return grid;
        }

        if( mx_indegree == 3 ) {
            // 2 row (or 2 column) arrangement
            bool seen[n]; memset(seen,false,sizeof seen);
            // identify a corner
            // let c0 be the grid[0][0]
            int c0;
            for(int i = 0; i < n; ++i) {
                if( g[i].size() == 2 ) {
                    // corner cell we will use as the start
                    c0 = i;
                    break;
                }
            }
            seen[c0] = true;
            // identify corner c1 grid[1][0]
            int c1;
            for(int i = 0; i < n; ++i) {
                if( !seen[i] && g[i].size() == 2 && ( g[i][0] == c0 || g[i][1] == c0 )) {
                    // corner cell we will use as the start
                    c1 = i;
                    break;
                }
            }
            seen[c1] = true;
            // build row0 and row1 in parallel
            vector<int> r0; r0.push_back(c0);
            vector<int> r1; r1.push_back(c1);
            int u0 = c0;
            int u1 = c1;
            n -= 2;
            while( n ) {
                // row 0
                for(int k = 0; k < g[u0].size(); ++k) {
                    int v = g[u0][k];
                    if( !seen[v] ) {
                        r0.push_back(v);
                        seen[v] = true;
                        u0 = v;
                        break;
                    }
                }
                // row 1
                for(int k = 0; k < g[u1].size(); ++k) {
                    int v = g[u1][k];
                    if( !seen[v] ) {
                        r1.push_back(v);
                        seen[v] = true;
                        u1 = v;
                        break;
                    }
                }
                n -= 2;
            }

            return {r0,r1};
        }


        vector<vector<int>> grid;

        // we will build row by row
        // identify a corner
        int c0;
        for(int i = 0; i < n; ++i) {
            if( g[i].size() == 2 ) {
                // corner cell we will use as the start
                c0 = i;
                break;
            }
        }
        bool seen[n]; memset(seen,false,sizeof seen);
        // build the 1st row
        seen[c0] = true;
        vector<int> r;
        r.push_back(c0);
        int u = c0;
        while( true ) {
            for(int k = 0; k < g[u].size(); ++k) {
                int v = g[u][k];
                if( !seen[v] && (g[v].size() == 2 || g[v].size() == 3) ) {
                    r.push_back(v);
                    seen[v] = true;
                    u = v;
                    break;
                }
            }
            if( g[u].size() == 2 )
                break;
        }
        grid.push_back(r);
        // build rows
        int col_cnt = r.size();
        int row_cnt = n / col_cnt;
        for(int i = 0; i < row_cnt-1; ++i) {
            r.clear();
            for(int j = 0; j < col_cnt; ++j) {
                u = grid[i][j];
                for(int k = 0; k < g[u].size(); ++k) {
                    int v = g[u][k];
                    if( !seen[v] ) {
                        r.push_back(v);
                        seen[v] = true;
                    }
                }
            }
            grid.push_back(r);
        }

        return grid;

    }
};




/*

2
[[0,1]]
3
[[0,2],[0,1]]
4
[[0,1],[0,2],[1,3],[2,3]]
5
[[0,1],[1,3],[2,3],[2,4]]
9
[[0,1],[0,4],[0,5],[1,7],[2,3],[2,4],[2,5],[3,6],[4,6],[4,7],[6,8],[7,8]]
10
[[0,1],[1,3],[2,3],[2,4],[4,9],[2,6],[3,5],[1,8],[0,7],[6,9],[5,6],[5,8],[7,8]]
9
[[0,1],[0,6],[0,8],[1,2],[1,5],[1,7],[2,4],[2,6],[3,5],[3,7],[4,5],[7,8]]
15
[[0,3],[0,7],[0,14],[1,8],[1,13],[2,6],[2,12],[3,8],[3,11],[3,13],[4,5],[4,6],[4,11],[4,12],[5,10],[5,14],[6,9],[7,13],[8,9],[9,11],[10,12],[11,14]]

*/
