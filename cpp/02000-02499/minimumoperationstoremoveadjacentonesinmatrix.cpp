
// 2123. Minimum Operations to Remove Adjacent Ones in Matrix
// https://leetcode.com/problems/minimum-operations-to-remove-adjacent-ones-in-matrix/


// https://en.wikipedia.org/wiki/Bipartite_graph
// https://en.wikipedia.org/wiki/Maximum_cardinality_matching
// https://en.wikipedia.org/wiki/Vertex_cover
// https://en.wikipedia.org/wiki/Hopcroft%E2%80%93Karp_algorithm
// https://cp-algorithms.com/graph/kuhn_maximum_bipartite_matching.html

class Solution {
private:
    int m,n;

    // directions   R  D  L  U
    int dirR[4] = { 0, 1, 0,-1};
    int dirC[4] = { 1, 0,-1, 0};

    void explore(vector<vector<int>>& grid, int u, int seen[],
                 vector<vector<int>>& A, int& a, vector<vector<int>>& B, int& b, char c) {

        // cout << "explore u " << u << " a " << a << " b " << b << " c " << c << endl;

        // seen[u] = 1;

        int a_idx, b_idx;
        if( c == 'A' ) {
            seen[u] = a;
            A.push_back({});
            a_idx = a-1;
            ++a;
        } else {
            seen[u] = b;
            B.push_back({});
            b_idx = b-1;
            ++b;
        }

        int i = u / n;
        int j = u % n;
        // cout << "i " << i << " j " << j << endl;

        // explore all four directions
        for(int k = 0; k < 4; ++k) {
            int i_new = i + dirR[k];
            if( i_new < 0 || i_new == m )
                continue;

            int j_new = j + dirC[k];
            if( j_new < 0 || j_new == n )
                continue;

            // cout << "i_new " << i_new << " j_new " << j_new << endl;

            if( grid[i_new][j_new] == 0 )
                continue;

            int v = i_new * n + j_new; // == seenIdx
            // cout << v << endl;
            if( seen[v] ) {
                // add edge from us to previously discovered node
                if( c == 'A' ) {
                    A[a_idx].push_back(seen[v]);
                } else {
                    B[b_idx].push_back(seen[v]);
                }
                continue;
            }

            if( c == 'A' ) {
                // add edge from us to found cell
                A[a_idx].push_back(b);
                // add edge from found cell to us
                // B.push_back({a_idx+1});

                explore(grid,v,seen,A,a,B,b,'B');
            } else {
                // add edge from us to found cell
                B[b_idx].push_back(a);
                // add edge from found cell to us
                // A.push_back({b_idx+1});

                explore(grid,v,seen,A,a,B,b,'A');
            }
        }

        return;
    }

    bool try_kuhn(vector<vector<int>>& g, int v, vector<int>& mt, vector<bool>& used) {
        if( used[v-1] )
            return false;

        used[v-1] = true;

        for(int to : g[v-1]) {
            if( mt[to-1] == -1 || try_kuhn(g,mt[to-1],mt,used) ) {
                mt[to-1] = v;
                return true;
            }
        }
        return false;
    }


public:
    int minimumOperations(vector<vector<int>>& grid) {
       /* from the hints
        *     Consider each cell containing a 1 as a vertex whose neighbors
        *     are the cells 4-directionally connected to it.
        *     The grid then becomes a bipartite graph.
        *     find the smallest set of vertices such that every edge in the graph has an endpoint in this set.
        *     If you remove every vertex in this set from the graph, then all the 1’s will be disconnected.
        *     The "smallest set of vertices such that every edge in the graph has an endpoint in this set"
        *     is also referred to as the 'minimum vertex cover' -> Kőnig's theorem.
        *     This 'minimum vertex cover' is also equal the 'maximum cardinality matching' aka
        *     maximum number of edges with the property that none of the edges share an endpoint.
        *
        *     so algorithm based on that:
        *         - create a undirected graph with one or more connected components between the 1s
        *         - for each connected component
        *             - divide into side U and V -> bipartite graph
        *             - find the minimum vertex cover aka maximum matching in taht bipartite graph
        *               using like Hopcroft-Karp-Karzanov or Kuhn's alogrithm
        */

        m = grid.size();
        n = grid[0].size();

        int ans = 0;


        int seen[m*n];memset(seen,0,sizeof seen);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( grid[i][j] == 1 ) {
                    int u = i * n + j;
                    if( !seen[u] ) {

                        vector<vector<int>> A;
                        int a = 1;
                        vector<vector<int>> B;
                        int b = 1;

                        // A.push_back({});
                        explore(grid,u,seen,A,a,B,b,'A');
                        // cout << A.size() << " " << B.size() << endl;

                        // minimum vertex cover
                        // bipartite graph A is one side, B the other
                        // vertices in A and B numbered independently starting at 1
                        int A_sz = A.size();
                        int B_sz = B.size();
                        vector<int> mt;
                        vector<bool> used;

                        mt.assign(B_sz,-1);
                        for(int v = 1; v <= A_sz; ++v) {
                            used.assign(A_sz,false);
                            try_kuhn(A,v,mt,used);
                        }
                        for(int i = 0; i < B_sz; ++i)
                            if (mt[i] != -1)
                                ++ans;
                        // cout << ans << endl;
                    }
                }
            }
        }

        return ans;
    }
};
