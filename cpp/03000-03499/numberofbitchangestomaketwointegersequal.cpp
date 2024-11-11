
// 3226. Number of Bit Changes to Make Two Integers Equal
// https://leetcode.com/problems/number-of-bit-changes-to-make-two-integers-equal/




class Solution {
public:
    int minChanges(int n, int k) {

        int ans = 0;

        while( n ) {

            if( n & 1 ) {
                if( !(k & 1) )
                    ++ans;
            } else {
                if( k & 1 )
                    return -1;
            }
            n = n >> 1;
            k = k >> 1;
        }

        return k == 0 ? ans : -1;
    }
};
