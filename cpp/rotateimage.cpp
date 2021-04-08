
// 48. Rotate Image
// https://leetcode.com/problems/rotate-image/



class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size(); // matrix[i].length == n
        if( n == 1 ) return;   // 1 <= n <= 20

        int src_row,src_col;
        int tgt_row,tgt_col;
        int s,t;
        int brko = n-1, brki; // breaks: outer break and inner break
        for(int i = 0; i <= n/2-1; ++i) {  // row
            brki = brko;
            for(int j = i; j < n-1; ++j) { // col
                if( brki == 0 ) break;

                // make 4 moves

                // move 1
                src_row = i;
                src_col = j;
                tgt_row = src_col;
                tgt_col = n-1-src_row;
                t = matrix[tgt_row][tgt_col]; // park the target
                matrix[tgt_row][tgt_col] = matrix[src_row][src_col];

                // move 2
                src_row = tgt_row;
                src_col = tgt_col;
                tgt_row = src_col;
                tgt_col = n-1-src_row;
                s = t;
                t = matrix[tgt_row][tgt_col]; // park the target
                matrix[tgt_row][tgt_col] = s;

                // move 3
                src_row = tgt_row;
                src_col = tgt_col;
                tgt_row = src_col;
                tgt_col = n-1-src_row;
                s = t;
                t = matrix[tgt_row][tgt_col]; // park the target
                matrix[tgt_row][tgt_col] = s;

                // move 4
                src_row = tgt_row;
                src_col = tgt_col;
                tgt_row = i;
                tgt_col = j;
                matrix[tgt_row][tgt_col] = t;

                --brki;
            }
            brko -= 2;
        }
    }
};
