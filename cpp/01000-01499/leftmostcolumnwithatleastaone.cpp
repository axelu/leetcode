
// 1428. Leftmost Column with at Least a One
// https://leetcode.com/problems/leftmost-column-with-at-least-a-one/
// day 1 Oct 2021 challenge






/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int row, int col);
 *     vector<int> dimensions();
 * };
 */

class Solution {
public:
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        vector<int> dimensions = binaryMatrix.dimensions();
        int m = dimensions[0]; // rows
        int n = dimensions[1]; // cols

        int ans = n;


        int i = 0;   // row idx
        int j = n-1; // row idx
        int t;
        while(true) {
            t = binaryMatrix.get(i,j);
            if( t == 1 ) {
                // move left
                ans = j;
                if( j == 0 )
                    break;
                --j;
            } else {
                // t == 0
                // move down
                ++i;
                if( i == m )
                    break;
            }
        }

        return ans == n ? -1 : ans;
    }
};
