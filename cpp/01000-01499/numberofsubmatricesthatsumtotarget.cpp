
// 1074. Number of Submatrices That Sum to Target
// https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/
// day 17 April 2021 challenge
// https://leetcode.com/explore/featured/card/april-leetcoding-challenge-2021/595/week-3-april-15th-april-21st/3711/




class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();    // rows
        int n = matrix[0].size(); // cols

        int i,j,k;

        int ps[m+1][n+1]; // 2D prefix sum
        for(i = 0; i <= m; ++i) {
            for(j = 0; j <= n; ++j) {
                if( i == 0 || j == 0 ) {
                    ps[i][j] = 0;
                    continue;
                }
                ps[i][j] = ps[i][j-1] + ps[i-1][j] - ps[i-1][j-1] + matrix[i-1][j-1];
            }
        }

        int ans = 0;
        int sum;
        unordered_map<int,int> um;
        unordered_map<int,int>::iterator f;
        for(int i = 1; i <= m; ++i) {           // upper row
            for(int j = i; j <= m; ++j) {       // lower row
                um.clear();
                um.insert({0,1});               // our 0 column
                for(int k = 1; k <= n; ++k) { // column
                    // 1D prefix sum for the current span of rows
                    sum = ps[j][k] - ps[i-1][k];

                    // add subarrays which sum up to (sum - target)
                    f = um.find(sum-target);
                    if( f != um.end() )
                        ans += f->second;

                    // remember 1D prefix sum for the current span for rows
                    f = um.find(sum);
                    if( f == um.end() ) {
                        um.insert({sum,1});
                    } else {
                        ++f->second;
                    }
                }
            }
        }

        return ans;
    }
};
