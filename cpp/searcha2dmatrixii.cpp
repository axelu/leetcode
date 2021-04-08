

// 240. Search a 2D Matrix II
// https://leetcode.com/problems/search-a-2d-matrix-ii/
// day 23 February 2021 challenge
// https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/587/week-4-february-22nd-february-28th/3650/



class Solution {
private:
    int M,N;

    // binary search
    bool searchMatrix(vector<vector<int>>& matrix, int& target, int rl, int cl, int rh, int ch) {
        // cout << rl << " " << cl << " " << rh << " " << ch << endl;
        if( rl > rh || cl > ch ) return false;

        int midr = rl + ((rh - rl)/2);
        int midc = cl + ((ch - cl)/2);

        int val = matrix[midr][midc];
        // cout << "mid " << midr << " " << midc << " " << val << endl;
        if( val == target ) {
            return true;
        } else if( val > target ) {
            // look left and up
            if( searchMatrix(matrix,target,rl,cl,midr,midc-1) ) return true;
            // look in the column above us
            if( searchMatrix(matrix,target,rl,midc,midr-1,midc) ) return true;
        } else {
            // val < target
            // look to down and right
            if( searchMatrix(matrix,target,midr+1,midc,rh,ch) ) return true;
            // look in the row to our right
            if( searchMatrix(matrix,target,midr,midc+1,midr,ch) ) return true;
        }
        // if we are still here, the value we are looking for could be
        // above and right
        if( searchMatrix(matrix,target,rl,midc+1,midr-1,ch) ) return true;
        // below and left
        return searchMatrix(matrix,target,midr+1,cl,rh,midc-1);
    }

public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        M = matrix.size();
        N = matrix[0].size();

        return searchMatrix(matrix,target,0,0,M-1,N-1);
    }
};
