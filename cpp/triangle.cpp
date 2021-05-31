
// 120. Triangle
// https://leetcode.com/problems/triangle/
// day 21 April 2021 challenge
// https://leetcode.com/explore/challenge/card/april-leetcoding-challenge-2021/595/week-3-april-15th-april-21st/3715/





class Solution {
private:
    int getNumberNodes(int n) {
        int t = 0;
        for(int k = 0; k < n; ++k) {
            // k+1 = number of tokens in row k (0-indexed);
            t += k+1;
        }
        return t;
    }

    int getIdx(int i, int j) {
        int t = 0;
        for(int k = 0; k <= i; ++k) {
            // k+1 = number of tokens in row k (0-indexed);
            t += k+1;
        }
        return t-i-1+j;
    }

    int dfs(vector<vector<int>>& triangle, int n, int i, int j, int mem[]) {
        if( i == n )
             return 0;

        int idx = getIdx(i,j);
        if( mem[idx] != INT_MAX ) return mem[idx];

        // left
        int l = dfs(triangle,n,i+1,j,mem);
        // right
        int r = dfs(triangle,n,i+1,j+1,mem);

        return mem[idx] = triangle[i][j] + min(l,r);
    }
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        int t = getNumberNodes(n);

        int mem[t];
        for(int i = 0; i < t; ++i) mem[i] = INT_MAX;

        return dfs(triangle,n,0,0,mem);
     }
};
