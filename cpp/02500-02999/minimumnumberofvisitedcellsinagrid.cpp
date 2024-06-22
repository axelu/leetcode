
// 2617. Minimum Number of Visited Cells in a Grid
// https://leetcode.com/problems/minimum-number-of-visited-cells-in-a-grid/





class Solution {
private:
    int * parent;

    int findRoot(int i) {
		// chase parent of current element until it reaches root

        while(parent[i] != i) {
            // path compression
            // set each i to point to its grandparent
            // (thereby halving the path length), where i
            // is the node which comes in between path,
            // while computing root
            parent[i] = parent[parent[i]] ;
            i = parent[i];
        }
		return i;
	}

	void unite(int p, int c) {
		p = findRoot(p);
		c = findRoot(c);
        if( p == c ) return;
		parent[c] = p;
	}

public:
    int minimumVisitedCells(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols
        if( m*n == 1 )
            return 1;

        // let us determine if [m-1,n-1] is even reachable via DFS
        // let us use Disjoint Set
        // [0,0] and [m-1,n-1] need to be part of the same connected component (CC)
        // in other words both have the same parent in the end, which is 0
        int _parent[m*n]; parent = _parent;
        for(int i = 0; i < m*n; ++i)
            parent[i] = i; // initially each node is connected to itself

        int seen[m*n];memset(seen,0,sizeof seen);
        seen[0] = 3;
        for(int i = 0; i < m && !seen[m*n-1]; ++i) {
            for(int j = 0; j < n && !seen[m*n-1]; ++j) {
                int maxJump = grid[i][j];
                if( maxJump == 0 )
                    continue;

                int u = i * n + j;
                // cout << "at " << u << endl;
                if( !seen[u] )
                    continue;

                // go down
                int i_max = min(m - 1, i + maxJump);
                for(int i_new = i_max; i_new >= i+1; --i_new) {
                    if( grid[i_new][j] == 0 && (i_new != m-1 || j != n-1) )
                        continue;
                    int v = i_new * n + j;
                    if( seen[v] & 1 )
                        break;
                    if( !seen[v] ) {
                        // cout << "  uniting " << u << " " << v << endl;
                        unite(u,v);
                        if( v == m*n-1 )
                            break;
                    }
                    seen[v] |= 1;
                }
                if( seen[m*n-1] )
                    break;

                // go right
                int j_max = min(n - 1, j + maxJump);
                for(int j_new = j_max; j_new >= j+1; --j_new) {
                    if( grid[i][j_new] == 0 && (i != m-1 || j_new != n-1) )
                        continue;
                    int v = i * n + j_new;
                    if( seen[v] & 2 )
                        break;
                    if( !seen[v] ) {
                        // cout << "  uniting " << u << " " << v << endl;
                        unite(u,v);
                        if( v == m*n-1 )
                            break;
                    }
                    seen[v] |= 2;
                }
            }
        }

        if( findRoot(m * n - 1) != 0 )
            return -1;

        // lets treat the grid as the definition of a
        // directed acyclic graph (DAG) and run
        // Dijkstra's algorithm

        priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;

        // distances
        int A[m*n];
        for(int i = 0; i < m*n; ++i)
            A[i] = 1000000;

        // push our source vertex s into priority queue
        int s = 0;
        pq.push({0,s});
        // set distance to our source vertex itself to 1, as we are counting visited cells
        A[s] = 1;

        int u,v;
        int weight = 1;
        while( !pq.empty() ) {

            u = pq.top()[1];
            pq.pop();

            int i = u / n;
            int j = u % n;
            int maxJump = grid[i][j];

            // go down
            int i_max = min(m - 1, i + maxJump);
            for(int i_new = i_max; i_new >= i+1; --i_new) {
                if( i_new == m-1 && j == n-1 )
                    return A[u] + weight;
                if( grid[i_new][j] == 0 )
                    continue;
                v = i_new * n + j;
                if( A[v] > A[u] + weight ) {
                    // Updating distance of v
                    A[v] = A[u] + weight;
                    pq.push({A[v], v});
                }
            }
            // go right
            int j_max = min(n - 1, j + maxJump);
            for(int j_new = j_max; j_new >= j+1; --j_new) {
                if( i == m-1 && j_new == n-1 )
                    return A[u] + weight;
                if( grid[i][j_new] == 0 )
                    continue;
                v = i * n + j_new;
                if( A[v] > A[u] + weight ) {
                    // Updating distance of v
                    A[v] = A[u] + weight;
                    pq.push({A[v], v});
                }
            }
        }

        return -1;
    }
};
