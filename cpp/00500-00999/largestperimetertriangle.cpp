
// 976. Largest Perimeter Triangle
// https://leetcode.com/problems/largest-perimeter-triangle/

class Solution {
public:
    int largestPerimeter(vector<int>& A) {
        sort(begin(A),end(A));
        size_t n = A.size();

        auto p = upper_bound(begin(A),end(A),0); // first idx with value > 0
        if( p == end(A) ) return 0;
        int fp = distance(begin(A),p);
        if( n - fp < 3 ) return 0;

        // base case
        if( n == 3 )
            return A[0] + A[1] <= A[2] ? 0 : A[0] + A[1] + A[2];

        int c;
        for(int i = n-1; i >= fp+2; --i) {
            c = A[i];
            for(int j = i-1; j >= fp+1; --j) {
                // at this point there must be a value A[j-1] > c - A[j]
                // as we are greedy, it must be the largest
                if( A[j-1] > c-A[j] ) return A[j-1]+A[j]+c;
            }
        }

        return 0;
    }
};
