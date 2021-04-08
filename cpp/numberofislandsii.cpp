
// 305. Number of Islands II
// https://leetcode.com/problems/number-of-islands-ii/




class Solution {
private:
    int M,N;
    // queue<int> path;

    /*
    void resetSeen(int seen[]) {
        while( !path.empty() ) {
            seen[path.front()] = 0;
            path.pop();
        }
    }
    */

    void annex(int row, int col, vector<vector<int>>& grid, int seen[], int islandId) {
        if( grid[row][col] == 0 ) return; // water
        int seenIdx = row*N+col;
        if( seen[seenIdx] == 1 ) return;  // land we have seen before
        seen[seenIdx] = 1;                // mark land as seen
        // path.push(seenIdx);
        grid[row][col] = islandId;        // annex

        // right
        if( col < N-1 ) annex(row,col+1,grid,seen,islandId);
        // down
        if( row < M-1 ) annex(row+1,col,grid,seen,islandId);
        // left
        if( col > 0 ) annex(row,col-1,grid,seen,islandId);
        // up
        if( row > 0 ) annex(row-1,col,grid,seen,islandId);
    }
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        int k = positions.size();
        if( k == 1 ) return {1};

        M = m;
        N = n;
        int row,col;
        vector<vector<int>> grid = vector(m,vector<int>(n,0));
        int seen[M*N]; memset(seen,0,sizeof seen);
        int islandIdPool = 0;
        int islandId = 0;
        bool hasAdjacentLand;
        vector<int> ans(k,0);
        for(int l = 0; l < k; ++l) {
            row = positions[l][0];
            col = positions[l][1];
            if( grid[row][col] != 0 ) {
                ans[l] = ans[l-1];
                continue;
            }
            // either we added an island OR
            // we expanded an existing island OR
            // we connected 2 or 3 or 4 islands into 1 and
            // with that reduced the number of islands by 1, 2 or 3 respectively
            hasAdjacentLand = false;
            int combined = 0;
            // right
            if( col < N-1 ) {
                if( grid[row][col+1] != 0 ) {
                    hasAdjacentLand = true;
                    islandId = grid[row][col+1];
                }
            }
            // down
            if( row < M-1 ) {
                if( grid[row+1][col] != 0 ) {
                    if( hasAdjacentLand ) {
                        if( islandId != grid[row+1][col] ) {
                            // annex the adjacent island
                            annex(row+1,col,grid,seen,islandId);
                            memset(seen,0,sizeof seen);
                            // resetSeen(seen);
                            ++combined;
                        }
                    } else {
                        hasAdjacentLand = true;
                        islandId = grid[row+1][col];
                    }
                }
            }
            // left
            if( col > 0 ) {
                if( grid[row][col-1] != 0 ) {
                    if( hasAdjacentLand ) {
                        if( islandId != grid[row][col-1] ) {
                            // annex the adjacent island
                            annex(row,col-1,grid,seen,islandId);
                            memset(seen,0,sizeof seen);
                            // resetSeen(seen);
                            ++combined;
                        }
                    } else {
                        hasAdjacentLand = true;
                        islandId = grid[row][col-1];
                    }
                }
            }
            // up
            if( row > 0 ) {
                if( grid[row-1][col] != 0 ) {
                    if( hasAdjacentLand ) {
                        if( islandId != grid[row-1][col] ) {
                            // annex the adjacent island
                            annex(row-1,col,grid,seen,islandId);
                            memset(seen,0,sizeof seen);
                            // resetSeen(seen);
                            ++combined;
                        }
                    } else {
                        hasAdjacentLand = true;
                        islandId = grid[row-1][col];
                    }
                }
            }
            if( !hasAdjacentLand ) {
                islandId = islandIdPool == 0 ? INT_MIN : islandIdPool+1;
                islandIdPool = islandId;
                ans[l] = l == 0 ? 1 : ans[l-1]+1;
            } else {
                ans[l] = ans[l-1] - combined;
            }
            grid[row][col] = islandId;
        }
        return ans;
    }
};
