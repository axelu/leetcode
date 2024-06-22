
// 3178. Find the Child Who Has the Ball After K Seconds
// https://leetcode.com/problems/find-the-child-who-has-the-ball-after-k-seconds/

/* n = 4
      ----------- ----------- ----------- ----------- -----------
       0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 
k = 3  x  x  x
k = 5  x  x  x  x  x
             x
k = 7  x  x  x  x  x  x  x
       x  x  x  


let rem = k % (n-1)

       0  1  2  3  0  1  2  3  0  1  2  3  0  1  2  3  0  1  2  3
      ----------- ----------- ----------- ----------- -----------
       0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 
          1  2  3  6  5  4        7  8  9 12 11 10       13 14 15 
rem       1  2  0  0  2  1        1  2  0  0  2  1        1  2  0

 */
class Solution {
public:
    int numberOfChild(int n, int k) {
        if( k <= n-1 )
            return k;
        
        int rem = k % (n-1);
        if( rem == 0 ) {
            // we are either at index 0 OR at index n-1
            int f = k / (n-1);
            return f % 2 ? n-1 : 0;
        
        } else {
            int f = k / (n-1);
            return f % 2 ? n - 1 - rem : rem;
        }
    }
};
