
// 803. Bricks Falling When Hit
// https://leetcode.com/problems/bricks-falling-when-hit/


class Solution {
private:

    int * parent;
    int * size;

    // disjoint-set union-find, tracks size of component also
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
        size[p] += size[c]; // add size of child to parent
	}

public:
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        int m = grid.size();        // rows
        int n = grid[0].size();     // cols


        // we are introducing an additional top node above row 0, to
        // which we will connect all nodes i in grid[0][i] which are 1
        int _parent[m*n+1]; parent = _parent;
        int _size[m*n+1]; size = _size;
        for(int i = 0; i < m*n+1; ++i) {
            parent[i] = i;  // initially each node is connected to itself only
            size[i] = 1;    // initially each set has a size of one
        }


        // disjoint-set does NOT support un-union aka delete
        // our hits would be an un-union, so in order to turn them into a union,
        // we will advance our hits to the end and then process them
        // in reverse order
        vector<vector<int>> _grid = grid;       // copy our grid
        for(int i = 0; i < hits.size(); ++i)
            _grid[hits[i][0]][hits[i][1]] = 0;  // apply hits to copied grid


        int u;
        for(int i = 0; i < m; ++i)              // row
            for(int j = 0; j < n; ++j)          // col
                if( _grid[i][j] == 1 ) {
                    int u = i*n+j;

                    if( i == 0 )    // connect node in row 0 to our extra top node
                        unite(m*n,u);

                    if( i > 0 && _grid[i-1][j] == 1 )
                        unite((i-1)*n+j,u);

                    if( j > 0 && _grid[i][j-1] == 1 )
                        unite(i*n+(j-1),u);
                }


        // four directions right, down, left, up
        int dirR[4] = {0,1,0,-1};
        int dirC[4] = {1,0,-1,0};

        vector<int> ans(hits.size(),0);

        int i,i_new,j,j_new,sz,t;
        // process hits in reverse
        for(int o = hits.size()-1; o >= 0; --o) {
            i = hits[o][0]; // row
            j = hits[o][1]; // col

            // current size of component connected
            // to top node (minus 1 to account for our extra node)
            sz = size[findRoot(m*n)]-1;

            if( grid[i][j] == 1 ) {
                u = i*n+j;

                // explore all directions
                for(int k = 0; k < 4; ++k) {
                    i_new = i + dirR[k];
                    if( i_new < 0 || i_new == m )
                        continue;

                    j_new = j + dirC[k];
                    if( j_new < 0 || j_new == n )
                        continue;

                    if( _grid[i_new][j_new] == 0 )
                        continue;

                    unite(u,i_new*n+j_new);
                }

                if( i == 0 )    // connect row 0 to top node
                    unite(m*n,u);

                _grid[i][j] = 1; // reverse the hit

                // new size of component connected
                // to top node (minus 1 to account for our extra node)
                t = size[findRoot(m*n)] - 1 - sz - 1;
                if( t > 0 )
                    ans[o] = t;
            }
        }

        return ans;
    }
};
