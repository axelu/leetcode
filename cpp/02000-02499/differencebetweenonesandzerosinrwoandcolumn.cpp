
// 2482. Difference Between Ones and Zeros in Row and Column
// https://leetcode.com/problems/difference-between-ones-and-zeros-in-row-and-column/



/*
 * let m be the number of rows and
 * let n be the number of cols
 * diff[i][j] = onesRowi + onesColj - zerosRowi - zerosColj
 * diff[i][j] = onesRowi + onesColj - (n-onesRowi) - (m-onesColj)
 * diff[i][j] = 2*onesRowi + 2*onesColj - n - m
 */
class Solution {
public:
    vector<vector<int>> onesMinusZeros(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int onesRow[m];memset(onesRow,0,sizeof onesRow);
        int onesCol[n];memset(onesCol,0,sizeof onesCol);

        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if( grid[i][j] == 1 ) {
                    ++onesRow[i];
                    ++onesCol[j];
                }

        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                grid[i][j] = 2*onesRow[i] + 2*onesCol[j] - n - m;

        return grid;
    }
};
