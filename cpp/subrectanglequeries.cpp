
// 1476. Subrectangle Queries
// https://leetcode.com/problems/subrectangle-queries/




class SubrectangleQueries {
private:
    int m,n;
    int * grid;
public:
    SubrectangleQueries(vector<vector<int>>& rectangle) {
        m = rectangle.size();
        n = rectangle[0].size();
        grid = new int[m*n];
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                grid[i*n+j] = rectangle[i][j];
    }

    void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue) {
        for(int i = row1; i <= row2; ++i)
            for(int j = col1; j <= col2; ++j)
                grid[i*n+j] = newValue;
    }

    int getValue(int row, int col) {
        return grid[row*n+col];
    }
};

/**
 * Your SubrectangleQueries object will be instantiated and called as such:
 * SubrectangleQueries* obj = new SubrectangleQueries(rectangle);
 * obj->updateSubrectangle(row1,col1,row2,col2,newValue);
 * int param_2 = obj->getValue(row,col);
 */
