
// 3242. Design Neighbor Sum Service
// https://leetcode.com/problems/design-neighbor-sum-service/



class neighborSum {
private:
    pair<int,int> * dic;
    vector<vector<int>> * arr2d;
    int n;
public:
    neighborSum(vector<vector<int>>& grid) {
        n = grid.size(); // n x n 2D array grid
        dic = new pair<int,int>[n*n];
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                dic[grid[i][j]] = {i,j};
        arr2d = &grid;
    }

    int adjacentSum(int value) {
        int i = dic[value].first;
        int j = dic[value].second;
        int sum = 0;
        // right
        if( j < n-1 )
            sum += arr2d->at(i).at(j+1);
        // down
        if( i < n-1 )
            sum += arr2d->at(i+1).at(j);
        // left
        if( j > 0 )
            sum += arr2d->at(i).at(j-1);
        // up
        if( i > 0 )
            sum += arr2d->at(i-1).at(j);

        return sum;
    }

    int diagonalSum(int value) {
        int i = dic[value].first;
        int j = dic[value].second;
        int sum = 0;

        // up right
        if( i > 0 && j < n-1 )
            sum += arr2d->at(i-1).at(j+1);
        // down right
        if( i < n-1 && j < n-1 )
            sum += arr2d->at(i+1).at(j+1);
        // down left
        if( i < n-1 && j > 0 )
            sum += arr2d->at(i+1).at(j-1);
        // up left
        if( i > 0 && j > 0 )
            sum += arr2d->at(i-1).at(j-1);

        return sum;
    }
};

/**
 * Your neighborSum object will be instantiated and called as such:
 * neighborSum* obj = new neighborSum(grid);
 * int param_1 = obj->adjacentSum(value);
 * int param_2 = obj->diagonalSum(value);
 */
