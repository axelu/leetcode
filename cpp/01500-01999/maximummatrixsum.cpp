
// 1975. Maximum Matrix Sum
// https://leetcode.com/problems/maximum-matrix-sum/




class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        // observation
        // we can always move the negatives such that
        //    if there are two, we can make them positive;
        //    in fact, if there is an even number of negative,
        //    we can make all of them positive
        // if there as an odd number, we are stuck with one
        // negative at the end, we can that to be the smallest
        // number closest to 0
        // if we have a zero in the matrix, we can turn all
        // numbers into positives

        int n = matrix.size(); // matrix.length == matrix[i].length

        long long ans = 0;

        bool has_zero = false;
        int cnt_negatives = 0;
        int mn = 100001;

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                int x = matrix[i][j];

                if( x < 0 )
                    ++cnt_negatives;
                if( x == 0 )
                    has_zero = true;

                long long t = abs(x);

                ans = ans + t;

                if( t > 0 && t < mn )
                    mn = t;
            }
        }

        // because we are multiplying by -1, we need to subtract it twice
        if( !has_zero && cnt_negatives % 2 == 1 )
            ans -= 2 * mn;

        return ans;
    }
};
