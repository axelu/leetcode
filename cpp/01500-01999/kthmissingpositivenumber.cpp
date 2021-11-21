
// 1539. Kth Missing Positive Number
// https://leetcode.com/problems/kth-missing-positive-number/


class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {

        int c = 0;

        for(auto it = arr.begin(); it != arr.end(); ++it) {
            if( it - arr.begin() == 0 ) {
                if( *it > 1 ) {
                    if( *it > k ) {
                        return k;
                    } else {
                        c = *it - 1;
                    }
                }
                continue;
            }
            int d = *it - *(it - 1);
            if( d > 1 ) {
                if( c + d - 1 == k ) {
                    return *it - 1;
                } else if ( c + d - 1 < k ) {
                    c += d - 1;
                } else {
                    return *(it - 1) + k - c;
                }
            }
        }

        return *(arr.end() - 1) + k - c;
    }
};
