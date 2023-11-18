
// 2923. Find Champion I
// https://leetcode.com/problems/find-champion-i/





class Solution {
public:
    int findChampion(vector<vector<int>>& grid) {
        int n = grid.size(); // n x n matrix

        int indegree[n];memset(indegree,0,sizeof indegree);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < i; ++j)
                if( grid[i][j] == 1 ) {
                    ++indegree[j];
                } else {
                    ++indegree[i];
                }

        for(int i = 0; i < n; ++i)
            if( indegree[i] == 0 )
                return i;

        return -1;
    }
};
