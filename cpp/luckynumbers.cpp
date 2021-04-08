
// Lucky Numbers in a Matrix
// https://leetcode.com/problems/lucky-numbers-in-a-matrix/

class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
        auto m = matrix.size();
        auto n = matrix[0].size();
        if( m == 1 && n == 1 ) return {matrix[0][0]};

        int mnr[50];
        int mxc[50];
        for(int i = 0; i < n; ++i) mxc[i] = 0;

        for(int i = 0; i < m; ++i) {
            mnr[i] = *min_element(begin(matrix[i]),end(matrix[i]));
            for(int j = 0; j < n; ++j)
                mxc[j] = max(mxc[j],matrix[i][j]);
        }

        vector<int> r;
        for(int i = 0; i < m; ++i)
            if(find(mxc,mxc+n,mnr[i]) != mxc+n) r.push_back(mnr[i]);

        return r;
    }
};
