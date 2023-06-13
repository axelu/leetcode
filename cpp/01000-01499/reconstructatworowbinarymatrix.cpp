
// 1253. Reconstruct a 2-Row Binary Matrix
// https://leetcode.com/problems/reconstruct-a-2-row-binary-matrix/



/* let v[2][n] be the anser
   if colsum[i] == 2, then v[0][i] = 1 and v[1][i] = 1
   if colsum[i] == 0, then v[0][i] = 0 and v[1][i] = 0
   if colsum[i] == 1, then we have a choice
     either v[0][i] = 0 and v[1][i] = 1
     or     v[0][i] = 1 and v[1][i] = 0
 */
class Solution {
public:
    vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int>& colsum) {
        int n = colsum.size();

        // for there to be a solution the following must be true:
        // upper + lower == sum of colsum[0,n-1];
        int _upper = upper;
        int _lower = lower;
        int sum = 0;
        for(int i = 0; i < n; ++i) {
            sum += colsum[i];
            if( colsum[i] == 2 ) {
                --_upper;
                --_lower;
            }
        }
        if( upper + lower != sum ||
            _upper < 0 ||
            _lower < 0 )
            return {};

        // not counting where colsum[i] == 2
        // we know we need to place _upper 1s into v[0] and _lower 1s into v[1]

        vector<vector<int>> v(2,vector<int>(n,0));
        for(int i = 0; i < n; ++i) {
            if( colsum[i] == 2 ) {
                v[0][i] = 1;
                v[1][i] = 1;
            } else if( colsum[i] == 1 ) {
                if( _upper > 0 ) {
                    v[0][i] = 1;
                    --_upper;
                } else {
                    v[1][i] = 1;
                }
            }
        }

        return v;
    }
};
