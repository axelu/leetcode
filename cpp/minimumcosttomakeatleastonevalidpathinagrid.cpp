
// 1368. Minimum Cost to Make at Least One Valid Path in a Grid
// https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/




class Solution {
private:
    // Dijkstra's algorithm
    int shortestPath(int n, vector<array<int,2>> G[], int s, int d) {

        // min heap
        priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;

        // distances
        int A[n+1];
        for(int i = 0; i < n+1; ++i) A[i] = 1000000;

        // push our source vertex into priority queue
        pq.push({0,s});
        // set distance to our source vertex itself to 0
        A[s] = 0;

        int u,v,weight;
        while(!pq.empty()) {

            u = pq.top()[1];
            pq.pop();

            vector<array<int,2>>::iterator it;
            for(it = G[u].begin(); it != G[u].end(); ++it) {
                v = (*it)[0];
                weight = (*it)[1];

                //  If there is shorter path to v through u.
                if( A[v] > A[u] + weight ) {
                    // Updating distance of v
                    A[v] = A[u] + weight;
                    pq.push({A[v], v});
                }
            }
        }

        return A[d];
    }


public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // cout << "m " << m << " n " << n << endl;

        // cell value             1   2   3   4
        // directions             R   L   D   U
        int dirR[5]  = { INT_MIN, 0,  0,  1, -1};
        int dirC[5]  = { INT_MIN, 1, -1,  0,  0};


        int N = m*n;
        vector<array<int,2>> G[N];

        int i,j,u,v,i_new,j_new,cost,add;

        // grid to graph
        for(i = 0; i < m; ++i) {
            for(j = 0; j < n; ++j) {

                u = i*n+j;

                // explore all 4 directions
                for(int k = 1; k < 5; ++k) {

                    i_new = i+dirR[k];
                    if( i_new < 0 || i_new == m )
                        continue;

                    j_new = j+dirC[k];
                    if( j_new < 0 || j_new == n )
                        continue;

                    v = i_new*n+j_new;

                    // cost u -> v
                    cost = k == grid[i][j] ? 0 : 1;

                    // cout << "graph u " << u << " v " << v << " cost " << cost << endl;

                    G[u].push_back({v,cost});
                }
            }
        }

        return shortestPath(N,G,0,N-1);
    }
};
