
// 779. K-th Symbol in Grammar
// https://leetcode.com/problems/k-th-symbol-in-grammar/




class Solution {
public:
    int kthGrammar(int n, int k) {

        int val = 0; // 1st row is 0

        while( true) {
            --n;
            if( n == 0 )
                break;

            // number nodes in target row k
            int nodes = pow(2,n);

            if( k > nodes/2 ) {
                // go right
                val =  !val;
                k -= nodes/2;
            }
            // no adjustment needed going left
        }

        return val;
    }
};
