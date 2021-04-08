
// Search a 2D Matrix
// day 16 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/561/week-3-october-15th-october-21st/3497/
// https://leetcode.com/problems/search-a-2d-matrix/


class Solution {
private:
    bool row(int br, int er, const int& n,
             const vector<vector<int>>& matrix, const int& target) {
        // cout << br << " " << er << endl;
        if( er < br || br > er ) return false;

        auto rw = br + ((er - br) / 2);
        int rwbv = matrix[rw][0]; // row begin value
        int rwev = matrix[rw][n]; // row end value
        if( target == rwbv || target == rwev ) return true;

        bool r;
        if ( target < rwbv ) {
            // check lower rows
            r = row(br,rw-1,n,matrix,target);
        } else if (target > rwev) {
            // check higher rows
            r = row(rw+1,er,n,matrix,target);
        } else {
            // target > rwbv && target < rwev
            // target 'could' be in this row
            if( n < 2 ) {
                r = false;
            } else {
                auto e = prev(matrix[rw].end());
                auto p = find(next(begin(matrix[rw])),e,target);
                r = p == e ? false : true;
            }
        }

        return r;
    }
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        auto m = matrix.size();
        if( m == 0 ) return false;

        auto n = matrix[0].size();
        if( n == 0 ) return false;

        int mxbw = matrix[0][0]; // matrix begin value
        if( m == 1 && n == 1 ) {
            if( target == mxbw) {
                return true;
            } else {
                return false;
            }
        }
        if( target < mxbw || target > matrix[m-1][n-1] ) return false;

        bool r = row(0,m-1,n-1,matrix,target);

        return r;
    }
};
