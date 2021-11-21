
// 413. Arithmetic Slices
// https://leetcode.com/problems/arithmetic-slices/
// day 18 February 2021 challenge
// https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/586/week-3-february-15th-february-21st/3644/

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int n = A.size();
        if( n < 3 ) return 0;

        int ans = 0;
        long d,d1,d2;
        int l,j;
        for(int i = 0; i < n-2; ++i) {
            d  = (long)A[i] - (long)A[i+1];   // diff between A[i]   and A[i+1]
            d1 = (long)A[i+1] - (long)A[i+2]; // diff between A[i+1] and A[i+2]
            if( d != d1 )
                continue;
            ++ans;
            l = 4;
            j = i+3;
            while( j < n ) {
                d2 = (long)A[j-1] - (long)A[j];
                if( d2 != d ) {
                    i = j-2; // will advance because of loop
                    break;
                }
                ans += l-2;
                ++j;
                ++l;
                if( j == n ) i = j-1;
            }
        }

        return ans;
    }
};
