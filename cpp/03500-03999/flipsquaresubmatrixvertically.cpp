
// 3643. Flip Square Submatrix Vertically
// https://leetcode.com/problems/flip-square-submatrix-vertically/


class Solution {
public:
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {

        int t,b,tmp;
        for(int j = y; j < y+k; ++j) {
            t = x;
            b = x+k-1;
            while(t < b) {
                tmp = grid[t][j];
                grid[t][j] = grid[b][j];
                grid[b][j] = tmp;
                ++t;
                --b;
            }
        }

        return grid;
    }
};
