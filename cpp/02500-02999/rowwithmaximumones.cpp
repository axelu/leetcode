
// 2643. Row With Maximum Ones
// https://leetcode.com/problems/row-with-maximum-ones/

class Solution {
public:
    vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {
        int m = mat.size();     // rows
        int n = mat[0].size();  // cols

        int cnt = 0;    // max count of 1s in row
        int row = 0;    // row in which max count has 1st been seen

        for(int i = 0; i < m; ++i) {
            int t = 0;
            for(int j = 0; j < n; ++j)
                if( mat[i][j] == 1 )
                    ++t;

            if( t > cnt ) {
                cnt = t;
                row = i;
                t = 0;
            }
        }

        return {row,cnt};
    }
};
