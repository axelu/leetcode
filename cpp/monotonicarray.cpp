
// 896. Monotonic Array
// https://leetcode.com/problems/monotonic-array/


class Solution {
public:
    bool isMonotonic(vector<int>& A) {
        int n = A.size();
        if( n == 1 ) return true;

        int isIncreasing = -1;
        int isDecreasing = -1;
        for(int i = 1; i < n; ++i) {
            if( A[i-1] == A[i] ) continue;
            if( A[i-1] < A[i] ) {
                if( isIncreasing == -1 ) {
                    isIncreasing = 1;
                    isDecreasing = 0;
                } else if( isIncreasing == 0 ) {
                    return false;
                }
            } else {
                if( isDecreasing == -1 ) {
                    isIncreasing = 0;
                    isDecreasing = 1;
                } else if( isDecreasing == 0 ) {
                    return false;
                }
            }
        }
        return true;
    }
};
