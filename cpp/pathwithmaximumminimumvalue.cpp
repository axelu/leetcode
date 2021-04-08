
// 1102. Path With Maximum Minimum Value
// https://leetcode.com/problems/path-with-maximum-minimum-value/



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
    int maximumMinimumPath(vector<vector<int>>& A) {
        int m = A.size();
        int n = A[0].size();

        int _parent[n*m]; parent = _parent;
        int seen[n*m];
        array<int,3> grid[n*m];
        int idx;
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j) {
                idx = i*n+j;
                parent[idx] = idx; // initially each node is connected to itself
                seen[idx] = 0;
                grid[idx] = {i,j,A[i][j]};
            }
        sort(grid,grid+m*n,[](const array<int,3>& a, const array<int,3>& b){
           return a[2]>b[2];  // sort by value desc
        });

        // union find
        // we visit the cell in descending order of their value and mark them as visited
        // then we check if a neighboring cell has already been visited and if so,
        // we connect (union-find) the current cell to that neighboring already visited cell
        // if a neighboring cell has already been visited, it is garuanteed that its value is
        // higher or equal to the current cell, making it the best path
        // on each iteration we check if begin (0,0) and end(n-1,m-1) are connected and if so
        // we can stop the the value of the current cell is the min that would be encountered
        // on that path of connected cells from begin to end
        int row,r,col,c,currentCellIdx,neighborCellIdx;
        vector<vector<int>> directions{{0,1},{0,-1},{1,0},{-1,0}};  // right, left, down, up
        for(int i = 0; i < m*n; ++i) {
            row = grid[i][0];
            col = grid[i][1];
            currentCellIdx = row * n + col;
            seen[currentCellIdx] = 1;

            // explore neighboring cells in all 4 directions
            for(int j = 0; j < 4; ++j) {
                r = row + directions[j][0];
                c = col + directions[j][1];
                neighborCellIdx = r * n + c;
                if( r >= 0 && r < m && c >= 0 && c < n && seen[neighborCellIdx] )
                    unite(currentCellIdx,neighborCellIdx);
            }
            // if we connected begin and end, then we are done
            if( findRoot(0) == findRoot(n*m-1) ) return grid[i][2];
        }

        return -1; // satisfy compiler
    }
};
