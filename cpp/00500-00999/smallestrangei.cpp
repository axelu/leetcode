
// 908. Smallest Range I
// https://leetcode.com/problems/smallest-range-i/



class Solution {
public:
    int smallestRangeI(vector<int>& A, int K) {
        size_t n = A.size();
        if( n == 1 ) return 0;

        const auto [mn, mx] = minmax_element(begin(A), end(A));
        int d = (*mx-*mn)- 2*K;
        return d <= 0 ? 0 : d;
    }
};
