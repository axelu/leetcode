
// 2852. Sum of Remoteness of All Cells
// https://leetcode.com/problems/sum-of-remoteness-of-all-cells/




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

    /*
	void unite(int p, int c) {
		p = findRoot(p);
		c = findRoot(c);
        if( p == c ) return;
		parent[c] = p;
	}
    */
    int unite(int p, int c) {
		p = findRoot(p);
		c = findRoot(c);
        if( p == c )
            return p;
		parent[c] = p;
        return p;
	}

    // connected components
    unordered_map<int,pair<int,long long>> ccs; // id, {number nodes, sum of node values}

    int N;

    // directions  R  D  L  U
    int dirR[4] = { 0, 1, 0,-1};
    int dirC[4] = { 1, 0,-1, 0};

    void dfs(vector<vector<int>>& grid, int u, int src, bool seen[]) {
        seen[u] = true;
        int i = u / N;
        int j = u % N;

        if( src != -1 ) {
            int p = unite(src,u);
            ++ccs[p].first;
            ccs[p].second += grid[i][j];
        }

        // explore all four directions
        for(int k = 0; k < 4; ++k) {
            int i_new = i + dirR[k];
            if( i_new < 0 || i_new == N )
                continue;
            int j_new = j + dirC[k];
            if( j_new < 0 || j_new == N )
                continue;

            if( grid[i_new][j_new] == -1 )
                continue;

            int v = i_new * N + j_new;
            if( seen[v] )
                continue;

            dfs(grid,v,u,seen);
        }
    }

public:
    long long sumRemoteness(vector<vector<int>>& grid) {
        N = grid.size(); // n x n grid

        int _parent[N*N];parent = _parent;
        for(int i = 0; i < N*N; ++i)
            _parent[i] = i; // initially each node is connected to itself

        bool seen[N*N];memset(seen,false,sizeof seen);
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                int u = i * N + j;
                if( grid[i][j] != -1 && !seen[u] ) {
                    // a new connected component
                    ccs[u] = {1,grid[i][j]};
                    dfs(grid,u,-1,seen);
                }
            }
        }

        long long cctotal = 0LL;
        for(auto& pp: ccs)
            cctotal += pp.second.second;

        long long ans = 0LL;
        for(auto& pp: ccs) {
            // number of nodes in our current component
            int nbr_nodes = pp.second.first;
            // sum of node values in our current component
            long long ccsum = pp.second.second;

            ans += nbr_nodes * (cctotal - ccsum);
        }

        return ans;
    }
};
