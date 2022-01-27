
// 782. Transform to Chessboard
// https://leetcode.com/problems/transform-to-chessboard/







class Solution {
private:
    int n,starting0,starting1;

    void printBinary(int x) {
        for(int i = n-1; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }


    int minSwaps(vector<int> rows, vector<int> cols, int topLeft) {
        /*
        cout << "minSwaps topLeft " << topLeft << endl;
        cout << "rows" << endl;
        for(int i = 0; i < n; ++i) {
            printBinary(rows[i]);cout<<endl;
        }
        cout << "cols" << endl;
        for(int j = 0; j < n; ++j) {
            printBinary(cols[j]);cout<<endl;
        }
        */

        // in order for us to swap rows,
        // there must be something to swap with

        // rows to swap
        vector<int> a; // row indexes that should start with topLeft, but don't
        vector<int> b; // row indexes that start with topLeft, but shouldn't
        for(int i = 0; i < n; ++i) {
            // even rows, includes top row
            if( i % 2 == 0 )
                if( (rows[i] & 1U) != topLeft )
                    a.push_back(i);
            if( i % 2 == 1 )
                if( (rows[i] & 1U) == topLeft )
                    b.push_back(i);
        }

        int ret = INT_MAX;
        // we can only swap if a and b have same number elements, including 0
        if( a.size() == b.size() ) {
            //cout << "rows to swap " << a.size() << endl;

            for(int i = 0; i < a.size(); ++i)
                swap(rows[a[i]],rows[b[i]]);
            // regenerate cols
            int col;
            for(int j = 0; j < n; ++j) {        // cols
                col = 0;
                for(int i = 0; i < n; ++i)      // rows
                    if( (rows[i]>>j) & 1U )
                        col |= (1U<<i);
                cols[j] = col;
            }
            /*
            cout << "after row swapping" << endl;
            cout << "rows" << endl;
            for(int i = 0; i < n; ++i) {
                printBinary(rows[i]);cout<<endl;
            }
            cout << "cols" << endl;
            for(int j = 0; j < n; ++j) {
                printBinary(cols[j]);cout<<endl;
            }
            */

            // moving on to cols
            int moves = min(swapCols(rows,cols,0),swapCols(rows,cols,1));
            //cout << "moves " << moves << endl;
            if( moves != INT_MAX )
                ret = a.size() + moves;
        }
        return ret;
    }

    int swapCols(vector<int> rows, vector<int> cols, int topLeft) {
        //cout << "swapCols topLeft " << topLeft << endl;

        // cols to swap
        vector<int> a; // col indexes that should start with topLeft, but don't
        vector<int> b; // col indexes that start with topLeft, but shouldn't
        for(int j = 0; j < n; ++j) {
            // even col, includes left col
            if( j % 2 == 0 )
                if( (cols[j] & 1U) != topLeft )
                    a.push_back(j);
            if( j % 2 == 1 )
                if( (cols[j] & 1U) == topLeft )
                    b.push_back(j);
        }

        int ret = INT_MAX;
        // we can only swap if a and b have same number elements, including 0
        if( a.size() == b.size() ) {
            //cout << "cols to swap " << a.size() << endl;
            ret = a.size();

            for(int j = 0; j < a.size(); ++j)
                swap(cols[a[j]],cols[b[j]]);
            /*
            cout << "after col swapping" << endl;
            cout << "cols" << endl;
            for(int j = 0; j < n; ++j) {
                printBinary(cols[j]);cout<<endl;
            }
            */

            // check if valid chessboard
            int col0 = topLeft ? starting1 : starting0;
            int col1 = topLeft ? starting0 : starting1;
            //cout << "col0 " << col0 << endl;
            //cout << "col1 " << col1 << endl;

            for(int j = 0; j < n; ++j) {
                if( j % 2 == 0 & cols[j] != col0 ) {
                    ret = INT_MAX;
                    break;
                }
                if( j % 2 == 1 & cols[j] != col1 ) {
                    ret = INT_MAX;
                    break;
                }
            }
            //cout << "valid chessboard " << (ret != INT_MAX) << endl;
        }
        return ret;
    }

public:
    int movesToChessboard(vector<vector<int>>& board) {
        // n x n matrix, 2 <= n <= 30, board[i][j] is either 0 or 1
        n = board.size();

        // translate rows and cols to integers
        // rows
        vector<int> rows(n);
        int row;
        for(int i = 0; i < n; ++i) {        // rows
            row = 0;
            for(int j = 0; j < n; ++j)      // cols
                if( board[i][j] == 1 )
                    row |= (1U<<j);
            rows[i] = row;
        }
         // cols
        vector<int> cols(n);
        int col;
        for(int j = 0; j < n; ++j) {        // cols
            col = 0;
            for(int i = 0; i < n; ++i)      // rows
                if( board[i][j] == 1 )
                    col |= (1U<<i);
            cols[j] = col;
        }

        starting0 = 0;
        for(int i = 1; i < n; i += 2)
            starting0 |= (1U<<i);

        starting1 = 0;
        for(int i = 0; i < n; i += 2)
            starting1 |= (1U<<i);


        int ans = min(minSwaps(rows,cols,0),minSwaps(rows,cols,1));
        return ans == INT_MAX ? -1 : ans;
    }
};
