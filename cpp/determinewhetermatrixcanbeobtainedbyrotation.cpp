
// 1886. Determine Whether Matrix Can Be Obtained By Rotation
// https://leetcode.com/problems/determine-whether-matrix-can-be-obtained-by-rotation/




class Solution {
private:

    // taken from https://leetcode.com/problems/rotate-image/
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size(); // matrix[i].length == n
        if( n == 1 ) return;   // 1 <= n <= 10

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
public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        if( mat == target )
            return true;

        rotate(mat); // 90deg
        if( mat == target )
            return true;

        rotate(mat); // 180deg
        if( mat == target )
            return true;

        rotate(mat); // 270deg
        if( mat == target )
            return true;


        return false;
    }
};
