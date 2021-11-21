
// 296. Best Meeting Point
// https://leetcode.com/problems/best-meeting-point/




class Solution {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols
        int i,j;

        // find all buildings
        vector<int> r;
        vector<int> c;
        for(i = 0; i < m; ++i) {
            for(j = 0; j < n; ++j) {
                if( grid[i][j] == 1 ) {
                    r.push_back(i);
                    c.push_back(j);
                }
            }
        }

        // meet at the median
        int nbrBldgs = r.size();
        sort(r.begin(),r.end()); int rmed = r[nbrBldgs/2];
        sort(c.begin(),c.end()); int cmed = c[nbrBldgs/2];
        int ans = 0;
        for(i = 0; i < nbrBldgs; ++i) {
            ans += abs(rmed-r[i]);
            ans += abs(cmed-c[i]);
        }

        return ans;
    }
};
