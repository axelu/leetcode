
// 1582. Special Positions in a Binary Matrix
// https://leetcode.com/problems/special-positions-in-a-binary-matrix/


class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        auto n = mat.size();        // = number rows
        auto p = mat[0].size();     // = number columns

        if( n == 1 && p == 1 )
            return ( mat[0][0] == 1 ) ? 1 : 0;

        vector<int> r(n, 0);        // number of 1's per row
        vector<int> c(p, 0);        // number of 1's per colum
        vector<pair<int,int>> ones; // coordinates of 1's

        for(int k = 0; k < p; ++k) {    // columns
            for(int i = 0; i < n; ++i) {// rows
                if ( mat[i][k] == 1 ) {
                    ++r[i];
                    ++c[k];
                    ones.push_back(make_pair(i,k));
                }
            }
        }

        int sum = 0;
        for(auto co : ones)
            if( r[co.first] == 1 && c[co.second] == 1 ) ++sum;

        return sum;
    }
};
