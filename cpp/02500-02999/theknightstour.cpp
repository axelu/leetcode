
// 2664. The Knight’s Tour
// https://leetcode.com/problems/the-knights-tour/



class Solution {
private:
    int m, n;

    // directions   0  1  2  3  4  5  6  7
    int dirR[8] = {-1,-2,-2,-1, 1, 2, 2, 1};
    int dirC[8] = {-2,-1, 1, 2, 2, 1,-1,-2};

    bool explore(int i, int j, vector<array<int,2>>& path, vector<vector<bool>>& seen) {
        seen[i][j] = true;
        path.push_back({i,j});

        if( path.size() == m*n )
            return true;

        // explore all knight moves
        for(int k = 0; k < 8; ++k) {
            int i_new = i + dirR[k];
            if( i_new < 0 || i_new >= m )
                continue;
            int j_new = j + dirC[k];
            if( j_new < 0 || j_new >= n )
                continue;

            if( seen[i_new][j_new] )
                continue;

            if( explore(i_new, j_new, path, seen) )
                return true;
        }

        // backtrack
        seen[i][j] = false;
        path.pop_back();
        return false;
    }

public:
    vector<vector<int>> tourOfKnight(int m, int n, int r, int c) {
        // m rows
        this->m = m;
        // n cols
        this->n = n;

        vector<array<int,2>> path;
        vector<vector<bool>> seen(m,vector<bool>(n,false));
        explore(r, c, path, seen);

        vector<vector<int>> ans(m,vector<int>(n));
        for(int i = 0; i < m*n; ++i)
            ans[path[i][0]][path[i][1]] = i;

        return ans;
    }
};
