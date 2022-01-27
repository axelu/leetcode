
// 778. Swim in Rising Water
// https://leetcode.com/problems/swim-in-rising-water/






class Solution {
private:
    // directions
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};


   // Dijkstra's algorithm adapted
    int shortestPath(vector<vector<int>>& grid, int m, int n, int limit) {

        // min heap
        priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;

        // distances
        int A[m*n+1];
        for(int i = 0; i < m*n+1; ++i) A[i] = 1000000;

        int s = 0; // source vertex always 0 in this case

        // push our source vertex into priority queue
        pq.push({0,s});
        // set distance to our source vertex itself to 0
        A[s] = 0;

        int u,v,weight,i,j,i_new,j_new;
        while(!pq.empty()) {

            u = pq.top()[1];
            pq.pop();

            i = u/n;
            j = u%n;

            // explore in all four directions
            for(int k = 0; k < 4; ++k) {

                i_new = i+dirR[k];
                if( i_new < 0 || i_new >= m )
                    continue;

                j_new = j+dirC[k];
                if( j_new < 0 || j_new >= n )
                    continue;

                v = i_new*n+j_new;

                if( grid[i_new][j_new] > limit )
                    continue;

                weight = grid[i_new][j_new] > grid[i][j] ? grid[i_new][j_new] - grid[i][j] : 0;

                //  If there is shorter path to v through u.
                if( A[v] > A[u] + weight ) {
                    // Updating distance of v
                    A[v] = A[u] + weight;
                    pq.push({A[v], v});
                }
            }
        }

        return A[(m-1)*n+(n-1)];
    }

    // binary search
    int search(vector<vector<int>>& grid, int m, int n, int s, int e) {

        if( s > e ) return -1;

        int mid = s + ((e - s)/2);
        int res = shortestPath(grid,m,n,mid);
        if( res < 1000000 ) {
            // can we do better?
            int t = search(grid,m,n,s,mid-1);
            return t != -1 ? t : mid;
        } else {
            return search(grid,m,n,mid+1,e);
        }
    }

public:
    int swimInWater(vector<vector<int>>& grid) {
        // N x N grid
        // 2 <= N <= 50
        int N = grid.size();

        // our solution is in the range [grid[0][0],m*n-1] inclusive
        return search(grid,N,N,grid[0][0],N*N-1);
    }
};
