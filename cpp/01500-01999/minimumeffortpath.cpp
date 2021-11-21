
// 1631. Path With Minimum Effort
// https://leetcode.com/problems/path-with-minimum-effort/



class Solution {
private:
    int n,m;
    vector<vector<int>> * pHeights;
    int visited[100][100]; // path under current exploration [row][col]

    bool hike(int i, int j, int k) {
        if( i == n-1 && j == m-1 )
            return true;

        visited[i][j] = 1; // mark current path

        int currentHeight = (*pHeights)[i][j];
        int heightdif; // height difference between current cell and target

        bool r = false;
        // down
        if( i+1 < n && !visited[i+1][j] ) {
            heightdif = abs((*pHeights)[i+1][j] - currentHeight);
            if( heightdif <= k ) r = hike(i+1,j,k);
        }
        // up
        if( !r && i-1 >= 0 && !visited[i-1][j] ) {
            heightdif = abs((*pHeights)[i-1][j] - currentHeight);
            if( heightdif <= k ) r = hike(i-1,j,k);
        }
        // right
        if( !r && j+1 < m && !visited[i][j+1] ) {
            heightdif = abs((*pHeights)[i][j+1] - currentHeight);
            if( heightdif <= k ) r = hike(i,j+1,k);
        }
        // left
        if( !r && j-1 >= 0 && !visited[i][j-1] ) {
            heightdif = abs((*pHeights)[i][j-1] - currentHeight);
            if( heightdif <= k )  r = hike(i,j-1,k);
        }
        return r;
    }

    int search(int s, int e) {
        // crossing begin and end
        if( s > e || e < s )
            return 1000000;

        int k = s + ((e - s)/2);

        for(int i = 0; i < n; ++i)
           for(int j = 0; j < m; ++j)
               visited[i][j] = 0;

        return hike(0,0,k) ? min(k,search(s,k-1)) : search(k+1,e);
    }

public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        n = heights.size();                 // rows
        m = heights[0].size();              // columns
        if( n == 1 && m == 1 ) return 0;    // base case

        // baseline max right -> down
        int baseline = 0;
        for(int j = 1; j < m; ++j)
            baseline = max(baseline,abs(heights[0][j-1]-heights[0][j]));
        for(int i = 1; i < n; ++i)
            baseline = max(baseline,abs(heights[i-1][m-1]-heights[i][m-1]));

        if( baseline == 0 || n == 1 || m == 1 ) return baseline;

        pHeights = &heights;

        // solution is between [0,baseline] inclusive
        return search(0,baseline);
    }
};
