
// 1992. Find All Groups of Farmland
// https://leetcode.com/problems/find-all-groups-of-farmland




class Solution {
private:
    // directions left, down, right, up
    vector<int> dirR = {0,-1,0,1};
    vector<int> dirC = {1,0,-1,0};

    int m,n;

    void explore(vector<vector<int>>& land, int i, int j, int& xb, int& yr, int seen[]) {
        // bottom right corner
        xb = max(xb,i);
        yr = max(yr,j);

        // explore all four directions
        int i_new,j_new;
        for(int k = 0; k < 4; ++k) {
            i_new = i + dirR[k];
            if( i_new < 0 || i_new == m )
                continue;

            j_new = j + dirC[k];
            if( j_new < 0 || j_new == n )
                continue;

            if( land[i_new][j_new] == 0 ) // forested land
                continue;

            int seenIdx = i_new*n+j_new;  // farm land we have seen before
            if( seen[seenIdx] )
                continue;

            seen[seenIdx] = 1;
            explore(land,i_new,j_new,xb,yr,seen);
        }
    }
public:
    vector<vector<int>> findFarmland(vector<vector<int>>& land) {
        m = land.size();
        n = land[0].size();

        vector<vector<int>> ans;

        int seen[m*n];memset(seen,0,sizeof seen);
        int seenIdx,xt,yl,xb,yr;
        for(int i = 0; i < m; ++i) {        // rows
            for(int j = 0; j < n; ++j) {    // cols
                seenIdx = i*n+j;
                if( land[i][j] == 1 && !seen[seenIdx] ) { // farmland we have not seen
                    seen[seenIdx] = 1;
                    xt = i;xb = i;
                    yl = j;yr = j;
                    explore(land,i,j,xb,yr,seen);
                    ans.push_back({xt,yl,xb,yr});
                }
            }
        }

        return ans;
    }
};
