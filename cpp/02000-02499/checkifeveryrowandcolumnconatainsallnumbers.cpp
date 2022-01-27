
// 2133. Check if Every Row and Column Contains All Numbers
// https://leetcode.com/problems/check-if-every-row-and-column-contains-all-numbers/



class Solution {
public:
    bool checkValid(vector<vector<int>>& matrix) {
        int n = matrix.size(); // n == matrix.length == matrix[i].length
        
        int row_cnt[n+1];
        int col_cnt[n][n+1];memset(col_cnt,0,sizeof col_cnt);
        
        for(int i = 0; i < n; ++i) {
            memset(row_cnt,0,sizeof row_cnt);
            for(int j = 0; j < n; ++j) {
                if( ++row_cnt[matrix[i][j]] == 2 )
                    return false;
                if( ++col_cnt[j][matrix[i][j]] == 2 )
                    return false;
            }
        }
        
        return true;
    }
};
