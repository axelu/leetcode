
// 1036. Matrix Cells in Distance Order
// https://leetcode.com/problems/matrix-cells-in-distance-order/


class Solution {
public:
    vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {
        multimap<int,vector<int>> m;
        int dist;
        for(int i = 0; i < R; ++i)
            for(int j = 0; j < C; ++j) {
                dist = abs(i - r0) + abs(j - c0);
                m.insert({dist,{i,j}});
            }

        vector<vector<int>> ans(R*C);
        int i = 0;
        for(auto it = m.begin(); it != m.end(); ++it) {
            ans[i] = it->second;
            ++i;
        }

        return ans;
    }
};
