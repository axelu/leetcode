
// 2536. Increment Submatrices by One
// https://leetcode.com/problems/increment-submatrices-by-one/



class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {

        vector<vector<int>> ans(n,vector<int>(n,0));

        for(int k = 0; k < queries.size(); ++k) {

            for(int i = queries[k][0]; i <= queries[k][2]; ++i) {

                ++ans[i][queries[k][1]];

                if( queries[k][3] + 1 < n )
                    --ans[i][queries[k][3] + 1];
            }
        }

        for(int i = 0; i < n; ++i) {
            for(int j = 1; j < n; ++j) {

                ans[i][j] = ans[i][j-1] + ans[i][j];

            }
        }




        return ans;
    }
};
