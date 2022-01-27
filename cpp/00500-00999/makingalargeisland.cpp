
// 827. Making A Large Island
// https://leetcode.com/problems/making-a-large-island/



class Solution {
private:
    int N;
    bool hasWater;
    bool hasLand;
    int ans;

    int explore(int row, int col, vector<vector<int>>& grid, int seen[], int id) {
        if( grid[row][col] == 0 ) { // water
            hasWater = true;
            return 0;
        }
        int seenIdx = row*N+col;
        if( seen[seenIdx] == 1 ) return 0;    // land we have seen before
        seen[seenIdx] = 1;                    // mark land as seen
        grid[row][col] = id;                  // mark land w/ island id

        int area = 1;
        // right
        if( col < N-1 ) area += explore(row,col+1,grid,seen,id);
        // down
        if( row < N-1 ) area += explore(row+1,col,grid,seen,id);
        // left
        if( col > 0 ) area += explore(row,col-1,grid,seen,id);
        // up
        if( row > 0 ) area += explore(row-1,col,grid,seen,id);

        return area;
    }

    void explore2(int row, int col, vector<vector<int>>& grid, int seen[], int id, vector<int>& areas) {
        if( grid[row][col] == 0 ) { // water
            // look around to determine if filling this water with land
            // would create a bridge to 1,2 or 3 islands
            int area = areas[id+2147483648]; // area of the island we came from
            set<int> seenIslands;
            int islandIdx;
            // right
            if( col < N-1 && grid[row][col+1] != 0 && grid[row][col+1] != id ) {
                islandIdx = grid[row][col+1]+2147483648;
                area += areas[islandIdx];
                seenIslands.insert(islandIdx);
            }
            // down
            if( row < N-1 && grid[row+1][col] != 0 && grid[row+1][col] != id ) {
                islandIdx = grid[row+1][col]+2147483648;
                if( seenIslands.find(islandIdx) == seenIslands.end() ) {
                    area += areas[islandIdx];
                    seenIslands.insert(islandIdx);
                }
            }
            // left
            if( col > 0 && grid[row][col-1] != 0 && grid[row][col-1] != id ) {
                islandIdx = grid[row][col-1]+2147483648;
                if( seenIslands.find(islandIdx) == seenIslands.end() ) {
                    area += areas[islandIdx];
                    seenIslands.insert(islandIdx);
                }
            }
            // up
            if( row > 0 && grid[row-1][col] != 0 && grid[row-1][col] != id ) {
                islandIdx = grid[row-1][col]+2147483648;
                if( seenIslands.find(islandIdx) == seenIslands.end() ) {
                    area += areas[islandIdx];
                    seenIslands.insert(islandIdx);
                }
            }

            ans = max(ans,area+1);
            return;
        }
        int seenIdx = row*N+col;
        if( seen[seenIdx] == 1 ) return; // land we have seen before
        seen[seenIdx] = 1;               // mark land as seen

        // right
        if( col < N-1 ) explore2(row,col+1,grid,seen,id,areas);
        // down
        if( row < N-1 ) explore2(row+1,col,grid,seen,id,areas);
        // left
        if( col > 0 ) explore2(row,col-1,grid,seen,id,areas);
        // up
        if( row > 0 ) explore2(row-1,col,grid,seen,id,areas);
    }

public:
    int largestIsland(vector<vector<int>>& grid) {
        N = grid.size(); // grid.length == grid[i].length
        if( N == 1 ) return 1;

        // if there is no island, we can make an island of size 1
        // if there is no water ( aka there is one island and its area is equal m*n), we return the area
        // otherwise we either make the largest island larger OR
        // we can connect 1,2,3 or 4 islands to make one island that is larger than the
        // largest island (if the largest island is not in fact part of that "bridge")

        ans = 0;

        // pass1
        vector<int> areas;
        int area;
        hasWater = false;
        hasLand = false;
        int islandId = INT_MIN;
        int seen[N*N]; memset(seen,0,sizeof seen);
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                if( grid[i][j] == 1 && seen[i*N+j] == 0 ) { // land we have NOT seen before
                    hasLand = true;
                    area = explore(i,j,grid,seen,islandId);
                    ans = max(ans,area);
                    areas.push_back(area);
                    ++islandId;
                }
        if( !hasLand ) return 1;        // no island, so we can convert 1 water cell to land
        if( !hasWater ) return area;    // 1 island that fills the grid
        int nbrIslands = areas.size();
        if( nbrIslands == 1 && areas[0] == N*N-1 ) return N*N; // 1 island and 1 cell of water left

        // pass2
        ++ans; // we could make the largest island larger by 1
        memset(seen,0,sizeof seen);
        islandId = INT_MIN; // islands will be rediscovered in the same order
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                if( grid[i][j] != 0 && seen[i*N+j] == 0 ) { // land we have NOT seen before
                    explore2(i,j,grid,seen,islandId,areas);
                    ++islandId;
                }


        return ans;
    }
};
