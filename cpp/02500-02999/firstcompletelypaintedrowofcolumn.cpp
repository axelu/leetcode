
// 2661. First Completely Painted Row or Column
// https://leetcode.com/problems/first-completely-painted-row-or-column/



class Solution {
public:
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        int m = mat.size();     // rows
        int n = mat[0].size();  // cols

        pair<int,int> dic[m*n+1];
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                dic[mat[i][j]] = {i,j};

        int row_sum[m];memset(row_sum,0,sizeof row_sum);
        int col_sum[n];memset(col_sum,0,sizeof col_sum);

        int k = 0;
        for(; k < m*n; ++k) {
            auto p = dic[arr[k]];
            // row
            ++row_sum[p.first];
            if( row_sum[p.first] == n )
                break;
            ++col_sum[p.second];
            if( col_sum[p.second] == m )
                break;
        }

        return k;
    }
};
