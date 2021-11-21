
// 2017. Grid Game
// https://leetcode.com/problems/grid-game/



class Solution {
public:
    long long gridGame(vector<vector<int>>& grid) {
        int m = 2;              // rows
        int n = grid[0].size(); // cols

        // the 1st robot will always collect grid[0][0] and grid[1][n-1]
        grid[0][0]   = 0;
        grid[1][n-1] = 0;

        // the question to answer is: at which index[0,n-1] does robot 1 go from row 0 to row 1
        //   it will have to to do that at index i where
        //   max(prefix1[i],prefix[n]-prefix[i+1]) is the minimum

        long long prefix0[n+1]; // prefix sum row 0
        prefix0[0] = 0LL;
        long long prefix1[n+1]; // prefix sum row 1
        prefix1[0] = 0LL;

        for(int i = 1; i <= n; ++i) {
            prefix0[i] = prefix0[i-1]+(long long)grid[0][i-1];
            prefix1[i] = prefix1[i-1]+(long long)grid[1][i-1];
        }

        // debug
        /*
        // prefix sum row 0
        for(int i = 0; i <= n; ++i)
            cout << prefix0[i] << " ";
        cout << endl;
        // prefix sum row 1
        for(int i = 0; i <= n; ++i)
            cout << prefix1[i] << " ";
        cout << endl;
        */


        long long ans = LLONG_MAX;
        for(int i = 0; i < n; ++i)
            ans = min(ans,max(prefix1[i],prefix0[n]-prefix0[i+1]));

        return ans;
    }
};
