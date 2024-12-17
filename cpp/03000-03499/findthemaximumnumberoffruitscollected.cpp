
// 3363. Find the Maximum Number of Fruits Collected
// https://leetcode.com/problems/find-the-maximum-number-of-fruits-collected/





class Solution {
private:

    // we could be more efficient with memory
    // we never cross over the half of i or j respectively
    int mem[1000][1000];



    int rec1(vector<vector<int>>& fruits, int n, int i, int j) {
        // cout << "rec1 i " << i << " j " << j << endl;
        // processes child that started out at [0, n-1]
        // don't doublecount n-1, n-1
        if( i == n-1 && j == n-1 )
            return 0;

        if( mem[i][j] != -1 )
            return mem[i][j];

        // we definitely need to move down aka i+1
        int i_new = i + 1;

        // we have a choice
        //     move j+1 (down right) (if we can) OR
        //     move j ([just] down) (if we can) OR
        //     move j-1 (down left) (if we can)

        // down right
        int a = -2000000;
        if( j + 1 < n ) // don't step outside
            a = rec1(fruits, n, i_new, j+1);

        // down
        int b = -2000000;
        if( (i_new == n-1 && j == n-1) || (i_new != n-1 && j != i_new) )  // don't step on diagonal, except n-1, n-1
            b = rec1(fruits, n, i_new, j);

        // down left
        int c = -2000000;
        if( j - 1 > i_new )
            c = rec1(fruits, n, i_new, j-1);


        return mem[i][j] = fruits[i][j] + max({a, b, c});
    }

    int rec2(vector<vector<int>>& fruits, int n, int i, int j) {
        // cout << "rec2 i " << i << " j " << j << endl;
        // processes child that started out at [n-1, 0]
        // don't doublecount n-1, n-1
        if( i == n-1 && j == n-1 )
            return 0;

        if( mem[i][j] != -1 )
            return mem[i][j];

        // we definitely need to move right aka j+1
        int j_new = j + 1;

        // we have a choice
        //     move i+1 (down right) (if we can) OR
        //     move i ([just] right) (if we can) OR
        //     move i-1 (up right) (if we can)

        // down right
        int a = -2000000;
        if( i + 1 < n ) // don't step outside
            a = rec2(fruits, n, i+1, j_new);

        // right
        int b = -2000000;
        if( (i == n-1 && j_new == n-1) || (j_new != n-1 && j_new != i) )  // don't step on diagonal, except n-1, n-1
            b = rec2(fruits, n, i, j_new);

        // up right
        int c = -2000000;
        if( i - 1 > j_new )
            c = rec2(fruits, n, i-1, j_new);


        return mem[i][j] = fruits[i][j] + max({a, b, c});
    }


public:
    int maxCollectedFruits(vector<vector<int>>& fruits) {
        int n = fruits.size(); // n x n matrix

        // the child at 0,0 can only go down the diagonal
        // otherwise it will not reach n-1,n-1 in n-1 moves

        // the other two children, at each move must
        // make progress towards n-1,n-1, meaning, again,
        // in order for them to make it in n-1 moves to n-1,n-1
        // the child at n-1,0 cannot move vertically and
        // the child at 0,n-1 cannot move horizontally
        // neither child can cross the diagonal, because, again,
        // in order for them to make it in n-1 moves to n-1,n-1
        // if n % 2 aka n is odd, one could reach the diagonal
        // and start moving towards n-1,n-1, but there is
        // no point in doing that, because the child at 0,0
        // will harvest the diagonal


        // harvest diagonal aka process child at 0,0
        int a = 0;
        for(int i = 0; i < n; ++i)
            a += fruits[i][i];
        // cout << "res child 0,0  " << a << endl;

        // process child at 0,n-1
        memset(mem,-1,sizeof mem);
        int b = rec1(fruits, n, 0, n-1);
        // cout << "res child 0,n-1 " << b << endl;

        // process child at n-1,0
        memset(mem,-1,sizeof mem);
        int c = rec2(fruits, n, n-1, 0);
        // cout << "res child n-1,0 " << c << endl;

        return a + b + c;
    }
};
