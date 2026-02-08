
// 3782. Last Remaining Integer After Alternating Deletion Operations
// https://leetcode.com/problems/last-remaining-integer-after-alternating-deletion-operations/


/*
    if n is even, we can simply divide by 2 and get the nbr of remaining elements
    if n is odd, we divide by 2 and add 1 to get the nbr of remaining elements
 */
class Solution {
private:

public:
    long long lastInteger(long long n) {
        if( n == 1 )
            return 1;

        // we will track the left most and right most
        // based on op1 or op2 operating on an even or odd nbr of elements
        // we know which will survive

        long long rem = n; // nbr of remaining elements
        bool op = false;
        long long f = 1;
        long long l = 1;
        long long r = n;
        while( rem != 1 ) {
            //          ----- survivor --------
            // rem  op  left        right
            // even  1  leftmost    rightmost-1
            // odd   1  leftmost    rightmost
            // even  2  leftmost+1  rightmost
            // odd   2  leftmost    rightmost
            int a = rem % 2;
            if( !op ) { // we are doing op1
                if( a == 0 ) {
                    r -= f;
                } else {
                    // do nothing
                }
            } else  {   // we are doing op2
                if( a == 0 ) {
                    l += f;
                } else {
                    // do nothing
                }
            }
            rem = rem / 2 + a;
            op = !op;
            f *= 2;
        }
        // cout << "l " << l << " r " << r << endl;

        return l; // l == r at this point
    }
};
