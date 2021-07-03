
// 1901. Find a Peak Element II
// https://leetcode.com/problems/find-a-peak-element-ii/





class Solution {
private:
    int m,n;

    vector<int> colMx[500];
    vector<int> rowMx[500];

    vector<int> getColMax(vector<vector<int>>& mat, int col) {
        // returns the max value in the given column and the
        // row in which the max value lies: max,row

        if( col < 0 || col >= n )
            return {-1,-1};

        if( colMx[col][0] )
            return colMx[col];

        int mx = 0;
        int rw;
        for(int i = 0; i < m; ++i) {
            if( mat[i][col] > mx ) {
                mx = mat[i][col];
                rw = i;
            }
        }

        return colMx[col] = {mx,rw};
    }

    vector<int> getRowMax(vector<vector<int>>& mat, int row) {
        // returns the max value in the given row and the
        // column in which the max value lies: max,col

        if( row < 0 || row >= m )
            return {-1,-1};

        if( rowMx[row][0] )
            return rowMx[row];

        int mx = 0;
        int cl;
        for(int j = 0; j < n; ++j) {
            if( mat[row][j] > mx ) {
                mx = mat[row][j];
                cl = j;
            }
        }

        return rowMx[row] = {mx,cl};
    }

    vector<int> searchCols(vector<vector<int>>& mat, int sc, int ec) {
        // sc = start column, ec = end column
        if( sc > ec ) return {-1,-1};

        int midc = sc + ((ec-sc)/2);
        // cout << "searchCols sc " << sc << " ec " << ec << " midc " << midc << endl;

        vector<int> mxlftc = getColMax(mat,midc-1);
        vector<int> mxmidc = getColMax(mat,midc);
        vector<int> mxrgtc = getColMax(mat,midc+1);

        /*
        cout << " mxlftc " << mxlftc[0] << endl;
        cout << " mxmidc " << mxmidc[0] << endl;
        cout << " mxrgtc " << mxrgtc[0] << endl;
        */

        if( mxmidc[0] >= mxlftc[0] && mxmidc[0] >= mxrgtc[0] )
            return {mxmidc[1],midc};

        if( mxlftc[0] >= mxmidc[0] && mxlftc[0] >= mxrgtc[0]) {
            return searchCols(mat,sc,midc);
        }

        return searchCols(mat,midc,ec);
    }

    vector<int> searchRows(vector<vector<int>>& mat, int sr, int er) {
        // sr = start row, er = end row
        if( sr > er ) return {-1,-1};

        int midr = sr + ((er-sr)/2);
        // cout << "searchRows sr " << sr << " er " << er << " midr " << midr << endl;

        vector<int> mxtopr = getRowMax(mat,midr-1);
        vector<int> mxmidr = getRowMax(mat,midr);
        vector<int> mxbtmr = getRowMax(mat,midr+1);

        /*
        cout << " mxtopr " << mxtopr[0] << endl;
        cout << " mxmidr " << mxmidr[0] << endl;
        cout << " mxbtmr " << mxbtmr[0] << endl;
        */

        if( mxmidr[0] >= mxtopr[0] && mxmidr[0] >= mxbtmr[0] )
            return {midr,mxmidr[1]};

        if( mxtopr[0] >= mxmidr[0] && mxtopr[0] >= mxbtmr[0]) {
            return searchRows(mat,sr,midr);
        }

        return searchRows(mat,midr,er);
    }


public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        m = mat.size();    // rows = height
        n = mat[0].size(); // cols = width

        for(int i = 0; i < 500; ++i) {
            colMx[i] = {0,0};
            rowMx[i] = {0,0};
        }

        if( m == 1 ) {
            return {0,getRowMax(mat,0)[1]};
        }
        if( n == 1 ) {
            return {getColMax(mat,0)[1],0};
        }



        if( n > m )
            return searchCols(mat,-1,n); // width > height -> split by columns
        return searchRows(mat,-1,m);
    }
};
