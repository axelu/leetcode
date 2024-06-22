
// 2965. Find Missing and Repeated Values
// https://leetcode.com/problems/find-missing-and-repeated-values/




class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        int n = grid.size(); // 2 <= n == grid.length == grid[i].length <= 50

        int a = -1;
        int cnt[n*n+1];memset(cnt,0,sizeof cnt);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                ++cnt[grid[i][j]];
                if( cnt[grid[i][j]] == 2 )
                    a = grid[i][j];
            }
        }
        int b = -1;
        for(int i = 1; i <= n*n; ++i) {
            if( cnt[i] == 0 ) {
                b = i;
                break;
            }
        }

        return {a,b};
    }
};
