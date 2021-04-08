
// 1337. The K Weakest Rows in a Matrix
// https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/


class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        auto m = mat.size();
        auto n = mat[0].size();

        vector<vector<int>> o;
        int rs;
        for(int i = 0; i < m; ++i) {
            rs = 0;
            for(int j = 0; j < n; ++j) {
                if( mat[i][j] == 0 ) break;
                ++rs;
            }
            o.push_back({rs,i});
        }
        sort(begin(o),end(o));

        vector<int> r;
        for(int i = 0; i < k; ++i)
            r.push_back(o[i][1]);

        return r;
    }
};
